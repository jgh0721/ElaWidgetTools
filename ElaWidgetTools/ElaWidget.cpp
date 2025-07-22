#include "ElaWidget.h"

#include "ElaApplication.h"
#include "ElaTheme.h"
#include "private/ElaWidgetPrivate.h"
#include <QApplication>
#include <QCloseEvent>
#include <QHBoxLayout>
#include <QPainter>
#include <QScreen>
#include <QTimer>
#include <QVBoxLayout>

Q_TAKEOVER_NATIVEEVENT_CPP(ElaWidget, d_func()->_appBar);

ElaWidgetBase::ElaWidgetBase( QWidget* parent, Qt::WindowFlags f )
    : QWidget{ parent, f }, d_ptr( new ElaWidgetBasePrivate() )
{
    Q_D( ElaWidgetBase );
    d->q_ptr = this;
    setWindowTitle( "ElaWidget" );
    setObjectName( "ElaWidget" );
#if (QT_VERSION < QT_VERSION_CHECK(6, 5, 3) || QT_VERSION > QT_VERSION_CHECK(6, 6, 1))
    setStyleSheet("ElaWidget{background-color:transparent;}");
#endif

    // 主题
    d->_themeMode = eTheme->getThemeMode();
    connect( eTheme, &ElaTheme::themeModeChanged, this, [=]( ElaThemeType::ThemeMode themeMode ) {
        d->_themeMode = themeMode;
        update();
    } );

    d->_windowDisplayMode = eApp->getWindowDisplayMode();
    connect(eApp, &ElaApplication::pWindowDisplayModeChanged, this, [=]() {
        d->_windowDisplayMode = eApp->getWindowDisplayMode();
        update();
    });
    eApp->syncWindowDisplayMode(this);
}

ElaWidgetBase::~ElaWidgetBase()
{
}

void ElaWidgetBase::paintEvent( QPaintEvent* event )
{
    Q_D( ElaWidgetBase );
#if (QT_VERSION >= QT_VERSION_CHECK(6, 5, 3) && QT_VERSION <= QT_VERSION_CHECK(6, 6, 1))
    if (d->_windowDisplayMode != ElaApplicationType::WindowDisplayMode::ElaMica)
#else
    if (d->_windowDisplayMode == ElaApplicationType::WindowDisplayMode::Normal)
#endif
    {
        QPainter painter( this );
        painter.save();
        painter.setRenderHints( QPainter::Antialiasing | QPainter::TextAntialiasing );
        painter.setPen( Qt::NoPen );
        painter.setBrush( ElaThemeColor( d->_themeMode, WindowBase ) );
        painter.drawRect( rect() );
        painter.restore();
    }
    QWidget::paintEvent( event );
}

ElaWidget::ElaWidget(QWidget* parent, Qt::WindowFlags f)
    : QWidget{parent, f}, d_ptr(new ElaWidgetPrivate())
{
    Q_D(ElaWidget);
    d->q_ptr = this;
    resize(500, 500); // 默认宽高
    setWindowTitle("ElaWidget");
    setObjectName("ElaWidget");
#if (QT_VERSION < QT_VERSION_CHECK(6, 5, 3) || QT_VERSION > QT_VERSION_CHECK(6, 6, 1))
    setStyleSheet("#ElaWidget{background-color:transparent;}");
#endif
    // 自定义AppBar
    d->_appBar = new ElaAppBar(this);
    d->_appBar->setIsStayTop(true);
    d->_appBar->setWindowButtonFlags(ElaAppBarType::StayTopButtonHint | ElaAppBarType::MinimizeButtonHint | ElaAppBarType::MaximizeButtonHint | ElaAppBarType::CloseButtonHint);
    connect(d->_appBar, &ElaAppBar::routeBackButtonClicked, this, &ElaWidget::routeBackButtonClicked);
    connect(d->_appBar, &ElaAppBar::navigationButtonClicked, this, &ElaWidget::navigationButtonClicked);
    connect(d->_appBar, &ElaAppBar::themeChangeButtonClicked, this, &ElaWidget::themeChangeButtonClicked);
    connect(d->_appBar, &ElaAppBar::closeButtonClicked, this, &ElaWidget::closeButtonClicked);

    // 主题
    d->_themeMode = eTheme->getThemeMode();
    connect(eTheme, &ElaTheme::themeModeChanged, this, [=](ElaThemeType::ThemeMode themeMode) {
        d->_themeMode = themeMode;
        update();
    });

    d->_windowDisplayMode = eApp->getWindowDisplayMode();
    connect(eApp, &ElaApplication::pWindowDisplayModeChanged, this, [=]() {
        d->_windowDisplayMode = eApp->getWindowDisplayMode();
        update();
    });
    eApp->syncWindowDisplayMode(this);
}

ElaWidget::~ElaWidget()
{
    eApp->syncWindowDisplayMode(this, false);
}

void ElaWidget::setIsStayTop(bool isStayTop)
{
    Q_D(ElaWidget);
    d->_appBar->setIsStayTop(isStayTop);
}

bool ElaWidget::getIsStayTop() const
{
    return d_ptr->_appBar->getIsStayTop();
}

void ElaWidget::setIsFixedHorizontalSize(bool isFixedSize)
{
    Q_D(ElaWidget);
    d->_appBar->setIsFixedHorizontalSize(isFixedSize);
}

bool ElaWidget::getIsFixedHorizontalSize() const
{
    return d_ptr->_appBar->getIsFixedHorizontalSize();
}

void ElaWidget::setIsFixedVerticalSize(bool isFixedSize)
{
    Q_D(ElaWidget);
    d->_appBar->setIsFixedVerticalSize(isFixedSize);
}

bool ElaWidget::getIsFixedVerticalSize() const
{
    return d_ptr->_appBar->getIsFixedVerticalSize();
}

void ElaWidget::setIsDefaultClosed(bool isDefaultClosed)
{
    Q_D(ElaWidget);
    d->_appBar->setIsDefaultClosed(isDefaultClosed);
    Q_EMIT pIsDefaultClosedChanged();
}

bool ElaWidget::getIsDefaultClosed() const
{
    Q_D(const ElaWidget);
    return d->_appBar->getIsDefaultClosed();
}

void ElaWidget::setAppBarHeight(int appBarHeight)
{
    Q_D(ElaWidget);
    d->_appBar->setAppBarHeight(appBarHeight);
    Q_EMIT pAppBarHeightChanged();
}

int ElaWidget::getAppBarHeight() const
{
    Q_D(const ElaWidget);
    return d->_appBar->getAppBarHeight();
}

void ElaWidget::moveToCenter()
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

ElaAppBar* ElaWidget::appBar() const
{
    const Q_D(ElaWidget);
    return d->_appBar;
}

void ElaWidget::setWindowButtonFlag(ElaAppBarType::ButtonType buttonFlag, bool isEnable)
{
    Q_D(ElaWidget);
    d->_appBar->setWindowButtonFlag(buttonFlag, isEnable);
}

void ElaWidget::setWindowButtonFlags(ElaAppBarType::ButtonFlags buttonFlags)
{
    Q_D(ElaWidget);
    d->_appBar->setWindowButtonFlags(buttonFlags);
}

ElaAppBarType::ButtonFlags ElaWidget::getWindowButtonFlags() const
{
    return d_ptr->_appBar->getWindowButtonFlags();
}

void ElaWidget::SetAutoCloseTimer( int timerSecs )
{
    /*!
        타이머 시간 설정
            UI 를 표시한 후 일정시간이 흐른 후 화면이 자동으로 닫히는 시간을 설정한다.

        #. 화면에 UI 가 표시 중이다.
        ##. 설정시간 > 0
        ###. 타이머를 중지시킨 후 즉시 타이머를 시작시킴
        ##. 설정시간 == 0
        ###. 타이머 중지
        #. 화면에 UI 가 표시 중이지 않음
        ##. 설정시간 > 0
        ###. 타이머 생성, 슬롯 설정, 타이머 싱글샷 설정 => ShowEvent 에서 타이머를 시작시킨다
        ##. 설정시간 == 0
        ###. 타이머 중지
    */

    do
    {
        // 설정 시간이 같다면 아무 것도 하지 않음
        if( (timerSecs * 1000) == _nAutoCloseIntervalMs )
            break;

        // 기존 타이머를 중지한 후 설정을 시작한다.
        // 타이머를 중지시키는 경우에는 (timerSecs == 0) 별도의 코드가 필요없음
        ResetAutoCloseTimer();
        Q_ASSERT( _clsAutoCloseTimer == nullptr );

        // 타이머를 중지시키는 목적이라면 종료
        if( timerSecs <= 0 )
            break;

        // 타이머 설정 ( 공통 동작 ) 수행
        _clsAutoCloseTimer = new QTimer( this );
        _clsAutoCloseTimer->moveToThread( qApp->thread() );

        Q_ASSERT( _clsAutoCloseTimer != nullptr );
        connect( _clsAutoCloseTimer, SIGNAL( timeout() ), this, SLOT( slotAutoCloseTimer() ) );
        _nAutoCloseIntervalMs = timerSecs * 1000;
        _clsAutoCloseTimer->setInterval( _nAutoCloseIntervalMs );
        _isUseAutoCloseTimer = true;
        // UI 가 화면에 보이고부터 닫히기 전까지의 시간을 계산해야하기 때문에 start 는 showEvent 에서 호출한다.
        // start 를 호출했을 때 기존에 동작중이었다면 자동으로 재설정된다.

        // 현재 UI 가 표시중이라면 즉시 타이머를 시작시킴
        if( isVisible() == true )
            _clsAutoCloseTimer->start();

    } while (false);
}

int ElaWidget::GetAutoCloseTimer()
{
    if( _isUseAutoCloseTimer == false )
        return 0;

    return _nAutoCloseIntervalMs / 1000;
}

void ElaWidget::ResetAutoCloseTimer()
{
    if( _isUseAutoCloseTimer == false || _clsAutoCloseTimer == nullptr )
        return;

    Q_ASSERT( _clsAutoCloseTimer != nullptr );

    _nAutoCloseIntervalMs = 0;
    _clsAutoCloseTimer->stop();
    _isUseAutoCloseTimer = false;

    if( _clsAutoCloseTimer != nullptr )
    {
        delete _clsAutoCloseTimer;
        _clsAutoCloseTimer = nullptr;
    }
}

int ElaWidget::ResultCode() const
{
    return resultCode_;
}

void ElaWidget::SetResultCode( QDialog::DialogCode resultCode )
{
    resultCode_ = resultCode;
}

void ElaWidget::CloseUI()
{
    close();
}

void ElaWidget::ShowUI()
{
    raise();
    activateWindow();
    show();
}

void ElaWidget::HideUI()
{
    hide();
}

void ElaWidget::showEvent( QShowEvent* event )
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

    QWidget::showEvent( event );
}

void ElaWidget::changeEvent( QEvent* event )
{
    if( event->type() == QEvent::LanguageChange )
    {
        doChangeUILanguage();
        Q_EMIT languageChanged();
    }

    QWidget::changeEvent( event );
}

void ElaWidget::slotAutoCloseTimer()
{
    int result = 0;
    if( doSlotAutoCloseTimer( result ) == true )
    {
        resultCode_ = result;
        CloseUI();
    }
}

bool ElaWidget::doSlotAutoCloseTimer( int& result )
{
    result = 0;
    return true;
}

void ElaWidget::paintEvent(QPaintEvent* event)
{
    Q_D(ElaWidget);
#if (QT_VERSION >= QT_VERSION_CHECK(6, 5, 3) && QT_VERSION <= QT_VERSION_CHECK(6, 6, 1))
    if (d->_windowDisplayMode != ElaApplicationType::WindowDisplayMode::ElaMica)
#else
    if (d->_windowDisplayMode == ElaApplicationType::WindowDisplayMode::Normal)
#endif
    {
        QPainter painter(this);
        painter.save();
        painter.setRenderHints(QPainter::Antialiasing | QPainter::TextAntialiasing);
        painter.setPen(Qt::NoPen);
        painter.setBrush(ElaThemeColor(d->_themeMode, WindowBase));
        painter.drawRect(rect());
        painter.restore();
    }
    QWidget::paintEvent(event);
}
