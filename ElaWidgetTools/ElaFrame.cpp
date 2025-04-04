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

    d->_isEnableMica = eApp->getIsEnableMica();
    connect( eApp, &ElaApplication::pIsEnableMicaChanged, this, [=]() {
        d->_isEnableMica = eApp->getIsEnableMica();
        update();
    } );
    eApp->syncMica( this );
}

ElaFrame::~ElaFrame()
{
}

void ElaFrame::paintEvent( QPaintEvent* event )
{
    Q_D( ElaFrame );
    if( !d->_isEnableMica )
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
