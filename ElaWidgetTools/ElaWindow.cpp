#include "ElaWindow.h"

#include "ElaApplication.h"
#include "ElaCentralStackedWidget.h"
#include "ElaEventBus.h"
#include "ElaMenu.h"
#include "ElaNavigationBar.h"
#include "ElaNavigationRouter.h"
#include "ElaTheme.h"
#include "ElaWindowStyle.h"
#include "private/ElaAppBarPrivate.h"
#include "private/ElaNavigationBarPrivate.h"
#include "private/ElaWindowPrivate.h"
#include <QApplication>
#include <QDockWidget>
#include <QHBoxLayout>
#include <QPropertyAnimation>
#include <QResizeEvent>
#include <QScreen>
#include <QStackedWidget>
#include <QStyleOption>
#include <QTimer>
#include <QToolBar>
#include <QVBoxLayout>
Q_PROPERTY_CREATE_Q_CPP(ElaWindow, int, ThemeChangeTime)
Q_PROPERTY_CREATE_Q_CPP(ElaWindow, ElaNavigationType::NavigationDisplayMode, NavigationBarDisplayMode)
Q_PROPERTY_CREATE_Q_CPP(ElaWindow, ElaWindowType::StackSwitchMode, StackSwitchMode)
Q_TAKEOVER_NATIVEEVENT_CPP(ElaWindow, d_func()->_appBar);
ElaWindow::ElaWindow(QWidget* parent, Qt::WindowFlags f)
    : QMainWindow{parent, f}, d_ptr(new ElaWindowPrivate())
{
    Q_D(ElaWindow);
    d->q_ptr = this;
    d->_pStackSwitchMode = ElaWindowType::StackSwitchMode::Popup;
    setProperty("ElaBaseClassName", "ElaWindow");
    resize(1020, 680); // 默认宽高

    d->_pThemeChangeTime = 700;
    d->_pNavigationBarDisplayMode = ElaNavigationType::NavigationDisplayMode::Auto;
    connect(this, &ElaWindow::pNavigationBarDisplayModeChanged, d, &ElaWindowPrivate::onDisplayModeChanged);

    // 自定义AppBar
    d->_appBar = new ElaAppBar(this);
    connect(d->_appBar, &ElaAppBar::routeBackButtonClicked, this, []() {
        ElaNavigationRouter::getInstance()->navigationRouteBack();
    });
    connect(d->_appBar, &ElaAppBar::closeButtonClicked, this, &ElaWindow::closeButtonClicked);
    // 导航栏
    d->_navigationBar = new ElaNavigationBar(this);
    // 返回按钮状态变更
    connect(ElaNavigationRouter::getInstance(), &ElaNavigationRouter::navigationRouterStateChanged, this, [d](bool isEnable) {
        d->_appBar->setRouteBackButtonEnable(isEnable);
    });

    // 转发用户卡片点击信号
    connect(d->_navigationBar, &ElaNavigationBar::userInfoCardClicked, this, &ElaWindow::userInfoCardClicked);
    // 转发点击信号
    connect(d->_navigationBar, &ElaNavigationBar::navigationNodeClicked, this, &ElaWindow::navigationNodeClicked);
    // 跳转处理
    connect(d->_navigationBar, &ElaNavigationBar::navigationNodeClicked, d, &ElaWindowPrivate::onNavigationNodeClicked);
    // 新增窗口
    connect(d->_navigationBar, &ElaNavigationBar::navigationNodeAdded, d, &ElaWindowPrivate::onNavigationNodeAdded);
    // 移除窗口
    connect(d->_navigationBar, &ElaNavigationBar::navigationNodeRemoved, d, &ElaWindowPrivate::onNavigationNodeRemoved);
    // 在新窗口打开
    connect(d->_navigationBar, &ElaNavigationBar::pageOpenInNewWindow, this, &ElaWindow::pageOpenInNewWindow);

    // 导航中心堆栈窗口
    d->_navigationCenterStackedWidget = new ElaCentralStackedWidget(this);
    d->_navigationCenterStackedWidget->setContentsMargins(0, 0, 0, 0);
    QWidget* navigationCentralWidget = new QWidget(this);
    navigationCentralWidget->setObjectName("ElaWindowNavigationCentralWidget");
    navigationCentralWidget->setStyleSheet("#ElaWindowNavigationCentralWidget{background-color:transparent;}");
    navigationCentralWidget->installEventFilter(this);
    d->_centerLayout = new QHBoxLayout(navigationCentralWidget);
    d->_centerLayout->setSpacing(0);
    d->_centerLayout->addWidget(d->_navigationBar);
    d->_centerLayout->addWidget(d->_navigationCenterStackedWidget);
    d->_centerLayout->setContentsMargins(d->_contentsMargins, 0, 0, 0);

    // 事件总线
    d->_focusEvent = new ElaEvent("WMWindowClicked", "onWMWindowClickedEvent", d);
    d->_focusEvent->registerAndInit();

    // 展开导航栏
    connect(d->_appBar, &ElaAppBar::navigationButtonClicked, d, &ElaWindowPrivate::onNavigationButtonClicked);

    // 主题变更动画
    d->_themeMode = eTheme->getThemeMode();
    connect(eTheme, &ElaTheme::themeModeChanged, d, &ElaWindowPrivate::onThemeModeChanged);
    connect(d->_appBar, &ElaAppBar::themeChangeButtonClicked, d, &ElaWindowPrivate::onThemeReadyChange);
    d->_isInitFinished = true;

    // 中心堆栈窗口
    d->_centerStackedWidget = new ElaCentralStackedWidget(this);
    d->_centerStackedWidget->setIsTransparent(true);
    d->_centerStackedWidget->addWidget(navigationCentralWidget);
    setCentralWidget(d->_centerStackedWidget);
    setObjectName("ElaWindow");
    setStyleSheet("#ElaWindow{background-color:transparent;}");
    setStyle(new ElaWindowStyle(style()));

    //延时渲染
    QTimer::singleShot(1, this, [=] {
        QPalette palette = this->palette();
        palette.setBrush(QPalette::Window, ElaThemeColor(d->_themeMode, WindowBase));
        this->setPalette(palette);
    });
    eApp->syncWindowDisplayMode(this);
    connect(eApp, &ElaApplication::pWindowDisplayModeChanged, this, [=]() {
        d->onThemeModeChanged(d->_themeMode);
    });
}

ElaWindow::~ElaWindow()
{
    eApp->syncWindowDisplayMode(this, false);
}

void ElaWindow::setIsStayTop(bool isStayTop)
{
    Q_D(ElaWindow);
    d->_appBar->setIsStayTop(isStayTop);
    Q_EMIT pIsStayTopChanged();
}

bool ElaWindow::getIsStayTop() const
{
    return d_ptr->_appBar->getIsStayTop();
}

void ElaWindow::setIsFixedHorizontalSize(bool IsFixedHorizontalSize)
{
    Q_D(ElaWindow);
    d->_appBar->setIsFixedHorizontalSize(IsFixedHorizontalSize);
    Q_EMIT pIsFixedHorizontalSizeChanged();
}

bool ElaWindow::getIsFixedHorizontalSize() const
{
    return d_ptr->_appBar->getIsFixedHorizontalSize();
}

void ElaWindow::setIsFixedVerticalSize(bool IsFixedVerticalSize)
{
    Q_D(ElaWindow);
    d->_appBar->setIsFixedVerticalSize(IsFixedVerticalSize);
    Q_EMIT pIsFixedVerticalSizeChanged();
}

bool ElaWindow::getIsFixedVerticalSize() const
{
    return d_ptr->_appBar->getIsFixedVerticalSize();
}

void ElaWindow::setIsDefaultClosed(bool isDefaultClosed)
{
    Q_D(ElaWindow);
    d->_appBar->setIsDefaultClosed(isDefaultClosed);
    Q_EMIT pIsDefaultClosedChanged();
}

bool ElaWindow::getIsDefaultClosed() const
{
    return d_ptr->_appBar->getIsDefaultClosed();
}

void ElaWindow::setAppBarHeight(int appBarHeight)
{
    Q_D(ElaWindow);
    d->_appBar->setAppBarHeight(appBarHeight);
    Q_EMIT pAppBarHeightChanged();
}

int ElaWindow::getAppBarHeight() const
{
    Q_D(const ElaWindow);
    return d->_appBar->getAppBarHeight();
}

QWidget* ElaWindow::getCustomWidget() const
{
    Q_D(const ElaWindow);
    return d->_appBar->getCustomWidget();
}

void ElaWindow::setCustomWidgetMaximumWidth(int width)
{
    Q_D(ElaWindow);
    d->_appBar->setCustomWidgetMaximumWidth(width);
    Q_EMIT pCustomWidgetMaximumWidthChanged();
}

int ElaWindow::getCustomWidgetMaximumWidth() const
{
    Q_D(const ElaWindow);
    return d->_appBar->getCustomWidgetMaximumWidth();
}

void ElaWindow::setIsCentralStackedWidgetTransparent(bool isTransparent)
{
    Q_D(ElaWindow);
    d->_navigationCenterStackedWidget->setIsTransparent(isTransparent);
}

bool ElaWindow::getIsCentralStackedWidgetTransparent() const
{
    Q_D(const ElaWindow);
    return d->_navigationCenterStackedWidget->getIsTransparent();
}

void ElaWindow::setIsAllowPageOpenInNewWindow(bool isAllowPageOpenInNewWindow)
{
    Q_D(ElaWindow);
    d->_navigationBar->setIsAllowPageOpenInNewWindow(isAllowPageOpenInNewWindow);
    Q_EMIT pIsAllowPageOpenInNewWindowChanged();
}

bool ElaWindow::getIsAllowPageOpenInNewWindow() const
{
    Q_D(const ElaWindow);
    return d->_navigationBar->getIsAllowPageOpenInNewWindow();
}

void ElaWindow::setNavigationBarWidth(int navigationBarWidth)
{
    Q_D(ElaWindow);
    d->_navigationBar->setNavigationBarWidth(navigationBarWidth);
    Q_EMIT pNavigationBarWidthChanged();
}

int ElaWindow::getNavigationBarWidth() const
{
    Q_D(const ElaWindow);
    return d->_navigationBar->getNavigationBarWidth();
}

void ElaWindow::setCurrentStackIndex(int currentStackIndex)
{
    Q_D(ElaWindow);
    if (currentStackIndex >= d->_centerStackedWidget->count() || currentStackIndex < 0 || currentStackIndex == d->_centralStackTargetIndex)
    {
        return;
    }
    d->_centralStackTargetIndex = currentStackIndex;
    QVariantMap routeData;
    routeData.insert("ElaCentralStackIndex", d->_centerStackedWidget->currentIndex());
    ElaNavigationRouter::getInstance()->navigationRoute(d, "onNavigationRouteBack", routeData);
    d->_centerStackedWidget->doWindowStackSwitch(d->_pStackSwitchMode, currentStackIndex, false);
    Q_EMIT pCurrentStackIndexChanged();
}

int ElaWindow::getCurrentStackIndex() const
{
    Q_D(const ElaWindow);
    return d->_centerStackedWidget->currentIndex();
}

void ElaWindow::moveToCenter()
{
    if (isMaximized() || isFullScreen())
    {
        return;
    }
#if QT_VERSION >= QT_VERSION_CHECK(5, 14, 0)
    auto geometry = screen()->availableGeometry();
#else
    auto geometry = qApp->screenAt(this->geometry().center())->geometry();
#endif
    setGeometry((geometry.left() + geometry.right() - width()) / 2, (geometry.top() + geometry.bottom() - height()) / 2, width(), height());
}

ElaAppBar* ElaWindow::appBar() const
{
    const Q_D(ElaWindow);
    return d->_appBar;
}

ElaNavigationBar* ElaWindow::navigationBar() const
{
    const Q_D(ElaWindow);
    return d->_navigationBar;
}

void ElaWindow::setCustomWidget(ElaAppBarType::CustomArea customArea, QWidget* widget)
{
    Q_D(ElaWindow);
    d->_appBar->setCustomWidget(customArea, widget);
    Q_EMIT customWidgetChanged();
}

void ElaWindow::setIsNavigationBarEnable(bool isVisible)
{
    Q_D(ElaWindow);
    d->_isNavigationEnable = isVisible;
    d->_navigationBar->setVisible(isVisible);
    d->_centerLayout->setContentsMargins(isVisible ? d->_contentsMargins : 0, 0, 0, 0);
    d->_navigationCenterStackedWidget->setIsHasRadius(isVisible);
}

bool ElaWindow::getIsNavigationBarEnable() const
{
    return d_ptr->_isNavigationEnable;
}

void ElaWindow::setUserInfoCardVisible(bool isVisible)
{
    Q_D(ElaWindow);
    d->_navigationBar->setUserInfoCardVisible(isVisible);
}

void ElaWindow::setUserInfoCardPixmap(QPixmap pix)
{
    Q_D(ElaWindow);
    d->_navigationBar->setUserInfoCardPixmap(pix);
}

void ElaWindow::setUserInfoCardTitle(QString title)
{
    Q_D(ElaWindow);
    d->_navigationBar->setUserInfoCardTitle(title);
}

void ElaWindow::setUserInfoCardSubTitle(QString subTitle)
{
    Q_D(ElaWindow);
    d->_navigationBar->setUserInfoCardSubTitle(subTitle);
}

ElaNavigationType::NodeOperateReturnType ElaWindow::addExpanderNode(QString expanderTitle, QString& expanderKey, ElaIconType::IconName awesome) const
{
    Q_D(const ElaWindow);
    return d->_navigationBar->addExpanderNode(expanderTitle, expanderKey, awesome);
}

ElaNavigationType::NodeOperateReturnType ElaWindow::addExpanderNode(QString expanderTitle, QString& expanderKey, QString targetExpanderKey, ElaIconType::IconName awesome) const
{
    Q_D(const ElaWindow);
    return d->_navigationBar->addExpanderNode(expanderTitle, expanderKey, targetExpanderKey, awesome);
}

ElaNavigationType::NodeOperateReturnType ElaWindow::addPageNode(QString pageTitle, QWidget* page, ElaIconType::IconName awesome) const
{
    Q_D(const ElaWindow);
    return d->_navigationBar->addPageNode(pageTitle, page, awesome);
}

ElaNavigationType::NodeOperateReturnType ElaWindow::addPageNode(QString pageTitle, QWidget* page, QString targetExpanderKey, ElaIconType::IconName awesome) const
{
    Q_D(const ElaWindow);
    return d->_navigationBar->addPageNode(pageTitle, page, targetExpanderKey, awesome);
}

ElaNavigationType::NodeOperateReturnType ElaWindow::addPageNode(QString pageTitle, QWidget* page, int keyPoints, ElaIconType::IconName awesome) const
{
    Q_D(const ElaWindow);
    return d->_navigationBar->addPageNode(pageTitle, page, keyPoints, awesome);
}

ElaNavigationType::NodeOperateReturnType ElaWindow::addPageNode(QString pageTitle, QWidget* page, QString targetExpanderKey, int keyPoints, ElaIconType::IconName awesome) const
{
    Q_D(const ElaWindow);
    return d->_navigationBar->addPageNode(pageTitle, page, targetExpanderKey, keyPoints, awesome);
}

ElaNavigationType::NodeOperateReturnType ElaWindow::addFooterNode(QString footerTitle, QString& footerKey, int keyPoints, ElaIconType::IconName awesome) const
{
    Q_D(const ElaWindow);
    return d->_navigationBar->addFooterNode(footerTitle, nullptr, footerKey, keyPoints, awesome);
}

ElaNavigationType::NodeOperateReturnType ElaWindow::addFooterNode(QString footerTitle, QWidget* page, QString& footerKey, int keyPoints, ElaIconType::IconName awesome) const
{
    Q_D(const ElaWindow);
    return d->_navigationBar->addFooterNode(footerTitle, page, footerKey, keyPoints, awesome);
}

void ElaWindow::addCentralWidget(QWidget* centralWidget)
{
    Q_D(ElaWindow);
    if (!centralWidget)
    {
        return;
    }
    d->_centerStackedWidget->addWidget(centralWidget);
}

QWidget* ElaWindow::getCentralWidget(int index) const
{
    Q_D(const ElaWindow);
    if (index >= d->_centerStackedWidget->count() || index < 1)
    {
        return nullptr;
    }
    return d->_centerStackedWidget->widget(index);
}

bool ElaWindow::getNavigationNodeIsExpanded(QString expanderKey) const
{
    Q_D(const ElaWindow);
    return d->_navigationBar->getNavigationNodeIsExpanded(expanderKey);
}

void ElaWindow::expandNavigationNode(QString expanderKey)
{
    Q_D(ElaWindow);
    d->_navigationBar->expandNavigationNode(expanderKey);
}

void ElaWindow::collpaseNavigationNode(QString expanderKey)
{
    Q_D(ElaWindow);
    d->_navigationBar->collpaseNavigationNode(expanderKey);
}

void ElaWindow::removeNavigationNode(QString nodeKey) const
{
    Q_D(const ElaWindow);
    d->_navigationBar->removeNavigationNode(nodeKey);
}

int ElaWindow::getPageOpenInNewWindowCount(QString nodeKey) const
{
    Q_D(const ElaWindow);
    return d->_navigationBar->getPageOpenInNewWindowCount(nodeKey);
}

void ElaWindow::setNodeKeyPoints(QString nodeKey, int keyPoints)
{
    Q_D(ElaWindow);
    d->_navigationBar->setNodeKeyPoints(nodeKey, keyPoints);
}

int ElaWindow::getNodeKeyPoints(QString nodeKey) const
{
    Q_D(const ElaWindow);
    return d->_navigationBar->getNodeKeyPoints(nodeKey);
}

void ElaWindow::navigation(QString pageKey)
{
    Q_D(ElaWindow);
    d->_navigationBar->navigation(pageKey);
}

int ElaWindow::getCurrentNavigationIndex() const
{
    Q_D(const ElaWindow);
    return d->_navigationCenterStackedWidget->currentIndex();
}

QString ElaWindow::getCurrentNavigationPageKey() const
{
    Q_D(const ElaWindow);
    return d->_navigationCenterStackedWidget->currentWidget()->property("ElaPageKey").toString();
}

void ElaWindow::setWindowButtonFlag(ElaAppBarType::ButtonType buttonFlag, bool isEnable)
{
    Q_D(ElaWindow);
    d->_appBar->setWindowButtonFlag(buttonFlag, isEnable);
}

void ElaWindow::setWindowButtonFlags(ElaAppBarType::ButtonFlags buttonFlags)
{
    Q_D(ElaWindow);
    d->_appBar->setWindowButtonFlags(buttonFlags);
}

ElaAppBarType::ButtonFlags ElaWindow::getWindowButtonFlags() const
{
    return d_ptr->_appBar->getWindowButtonFlags();
}

void ElaWindow::closeWindow()
{
    Q_D(ElaWindow);
    d->_isWindowClosing = true;
    d->_appBar->closeWindow();
}

void ElaWindow::showEvent( QShowEvent* event )
{
    do
    {
        if( _isInitUI == false )
        {
            _isInitUI = doInitUI();
            if( _isInitUI == true )
                doRefresh();
        }

        showEventUI( event );

    } while (false);

    QMainWindow::showEvent( event );
}

void ElaWindow::changeEvent( QEvent* event )
{
    if( event->type() == QEvent::LanguageChange )
    {
        doChangeUILanguage();
        Q_EMIT languageChanged();
    }

    QMainWindow::changeEvent( event );
}

bool ElaWindow::eventFilter(QObject* watched, QEvent* event)
{
    Q_D(ElaWindow);
    switch (event->type())
    {
    case QEvent::Resize:
    {
        d->_doNavigationDisplayModeChange();
        break;
    }
    default:
    {
        break;
    }
    }
    return QMainWindow::eventFilter(watched, event);
}

QMenu* ElaWindow::createPopupMenu()
{
    ElaMenu* menu = nullptr;
    QList<QDockWidget*> dockwidgets = findChildren<QDockWidget*>();
    if (dockwidgets.size())
    {
        menu = new ElaMenu(this);
        for (int i = 0; i < dockwidgets.size(); ++i)
        {
            QDockWidget* dockWidget = dockwidgets.at(i);
            if (dockWidget->parentWidget() == this)
            {
                menu->addAction(dockwidgets.at(i)->toggleViewAction());
            }
        }
        menu->addSeparator();
    }

    QList<QToolBar*> toolbars = findChildren<QToolBar*>();
    if (toolbars.size())
    {
        if (!menu)
        {
            menu = new ElaMenu(this);
        }
        for (int i = 0; i < toolbars.size(); ++i)
        {
            QToolBar* toolBar = toolbars.at(i);
            if (toolBar->parentWidget() == this)
            {
                menu->addAction(toolbars.at(i)->toggleViewAction());
            }
        }
    }
    if (menu)
    {
        menu->setMenuItemHeight(28);
    }
    return menu;
}
