#include "ElaDialog.h"

#include "private/ElaDialogPrivate.h"

#include <QEvent>
#include <QThread>
#include <QTimer>
#include <QScreen>
#include <QApplication>
#include <QCloseEvent>
#include <QPainter>

#include "ElaApplication.h"
#include "ElaTheme.h"

Q_TAKEOVER_NATIVEEVENT_CPP( ElaDialog, d_func()->_appBar );

ElaDialog::ElaDialog( QWidget* parent, Qt::WindowFlags flags )
    : QDialog(parent, flags & ~Qt::FramelessWindowHint), d_ptr(new ElaDialogPrivate())
{
    Q_D(ElaDialog);
    d->q_ptr = this;

    setWindowTitle("ElaDialog");
    setObjectName("ElaDialog");
#if (QT_VERSION < QT_VERSION_CHECK(6, 5, 3) || QT_VERSION > QT_VERSION_CHECK(6, 6, 1))
    setStyleSheet("ElaDialog{background-color:transparent;}");
#endif
    // 自定义AppBar
    d->_appBar = new ElaAppBar(this);
    setIsStayTop( false );
    d->_appBar->setWindowButtonFlags(ElaAppBarType::MinimizeButtonHint | ElaAppBarType::MaximizeButtonHint | ElaAppBarType::CloseButtonHint);
    connect(d->_appBar, &ElaAppBar::routeBackButtonClicked, this, &ElaDialog::routeBackButtonClicked);
    connect(d->_appBar, &ElaAppBar::navigationButtonClicked, this, &ElaDialog::navigationButtonClicked);
    connect(d->_appBar, &ElaAppBar::themeChangeButtonClicked, this, &ElaDialog::themeChangeButtonClicked);
    connect(d->_appBar, &ElaAppBar::closeButtonClicked, this, &ElaDialog::closeButtonClicked);

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

ElaDialog::~ElaDialog()
{
    eApp->syncWindowDisplayMode(this, false);
}

void ElaDialog::setIsStayTop(bool isStayTop)
{
    Q_D(ElaDialog);
    d->_appBar->setIsStayTop(isStayTop);
}

bool ElaDialog::getIsStayTop() const
{
    return appBar()->getIsStayTop();
}

void ElaDialog::setIsFixedHorizontalSize(bool isFixedSize)
{
    appBar()->setIsFixedHorizontalSize(isFixedSize);
}

bool ElaDialog::getIsFixedHorizontalSize() const
{
    return appBar()->getIsFixedHorizontalSize();
}

void ElaDialog::setIsFixedVerticalSize(bool isFixedSize)
{
    appBar()->setIsFixedVerticalSize(isFixedSize);
}

bool ElaDialog::getIsFixedVerticalSize() const
{
    return appBar()->getIsFixedVerticalSize();
}

void ElaDialog::setIsDefaultClosed(bool isDefaultClosed)
{
    Q_D(ElaDialog);
    d->_appBar->setIsDefaultClosed(isDefaultClosed);
    Q_EMIT pIsDefaultClosedChanged();
}

bool ElaDialog::getIsDefaultClosed() const
{
    Q_D(const ElaDialog);
    return d->_appBar->getIsDefaultClosed();
}

void ElaDialog::setAppBarHeight(int appBarHeight)
{
    Q_D(ElaDialog);
    d->_appBar->setAppBarHeight(appBarHeight);
    Q_EMIT pAppBarHeightChanged();
}

int ElaDialog::getAppBarHeight() const
{
    return appBar()->getAppBarHeight();
}

ElaAppBar* ElaDialog::appBar() const
{
    Q_D(const ElaDialog);
    return d->_appBar;
}

void ElaDialog::setWindowButtonFlag(ElaAppBarType::ButtonType buttonFlag, bool isEnable)
{
    Q_D(ElaDialog);
    appBar()->setWindowButtonFlag(buttonFlag, isEnable);
}

void ElaDialog::setWindowButtonFlags(ElaAppBarType::ButtonFlags buttonFlags)
{
    Q_D(ElaDialog);
    appBar()->setWindowButtonFlags(buttonFlags);
}

ElaAppBarType::ButtonFlags ElaDialog::getWindowButtonFlags() const
{
    return appBar()->getWindowButtonFlags();
}

void ElaDialog::moveToCenter()
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

void ElaDialog::ShowUI()
{
    raise();
    activateWindow();
    show();
}

int ElaDialog::ExecUI()
{
    raise();
    activateWindow();
    return exec();
}

void ElaDialog::HideUI()
{
    hide();
}

void ElaDialog::CloseUI()
{
    if( doCloseUI() == false )
        return;

    done( _resultCode );
}

void ElaDialog::SetAutoCloseTimer( int timerSecs )
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
        _clsAutoCloseTimer->moveToThread( thread() );

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

int ElaDialog::GetAutoCloseTimer()
{
    if( _isUseAutoCloseTimer == false )
        return 0;

    return _nAutoCloseIntervalMs / 1000;
}

void ElaDialog::ResetAutoCloseTimer()
{
    if( _isUseAutoCloseTimer == false || _clsAutoCloseTimer == nullptr )
        return;

    _nAutoCloseIntervalMs = 0;
    _isUseAutoCloseTimer = false;

    Q_ASSERT( _clsAutoCloseTimer != nullptr );
    if( _clsAutoCloseTimer == nullptr )
        return;

    _clsAutoCloseTimer->stop();
    delete _clsAutoCloseTimer;
    _clsAutoCloseTimer = nullptr;
}

void ElaDialog::slotAutoCloseTimer()
{
    int result = _resultCode;
    if( doSlotAutoCloseTimer( result ) == true )
    {
        _resultCode = result;
        done( _resultCode );
    }
}

void ElaDialog::showEvent( QShowEvent* event )
{
    do
    {
        if( _isInitUI == false )
        {
            _isInitUI = doInitUI();
            if( _isInitUI == true )
                doRefresh();
        }

        if( _clsAutoCloseTimer != nullptr )
        {
            if( _clsAutoCloseTimer->isActive() == false )
            {
                if( _isUseAutoCloseTimer == true && _nAutoCloseIntervalMs > 1000 )
                {
                    QMetaObject::invokeMethod( _clsAutoCloseTimer, "start", Q_ARG( int, _nAutoCloseIntervalMs ) );
                }
            }
        }

        doShowEventUI( event );

    } while( false );

    QDialog::showEvent( event );
}

void ElaDialog::changeEvent( QEvent* event )
{
    if( event->type() == QEvent::LanguageChange )
    {
        doChangeUILanguage();
        Q_EMIT languageChanged();
    }

    QDialog::changeEvent( event );
}

void ElaDialog::paintEvent( QPaintEvent* event )
{
    Q_D(ElaDialog);
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
    QDialog::paintEvent( event );
}
