#include "ElaFrame.h"
#include "Private/ElaFramePrivate.h"

#include "ElaTheme.h"
#include "ElaApplication.h"

#include <QPainter>

ElaFrame::ElaFrame( QWidget* Parent )
    : QFrame{ Parent }, d_ptr( new ElaFramePrivate() )
{
    Q_D( ElaFrame );
    d->q_ptr = this;
    setWindowTitle( "ElaFrame" );
    setObjectName( "ElaFrame" );

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

ElaFrame::~ElaFrame()
{
}

void ElaFrame::paintEvent( QPaintEvent* event )
{
    Q_D( ElaFrame );
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
    else
    {
        QFrame::paintEvent( event );
    }
}
