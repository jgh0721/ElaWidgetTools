#include "ElaTreeWidget.h"

#include "ElaScrollBar.h"
#include "ElaTreeViewPrivate.h"
#include "ElaTreeViewStyle.h"

ElaTreeWidget::ElaTreeWidget( QWidget* parent )
    : QTreeWidget( parent ), d_ptr( new ElaTreeWidgetPrivate() )
{
    Q_D( ElaTreeWidget );
    d->q_ptr = this;
    setObjectName( "ElaTreeView" );
    setStyleSheet(
        "ElaTreeWidget{background-color:transparent;}"
        "QHeaderView{background-color:transparent;border:0px;}" );

    setAnimated( true );
    setMouseTracking( true );

    ElaScrollBar* hScrollBar = new ElaScrollBar( this );
    hScrollBar->setIsAnimation( true );
    connect( hScrollBar, &ElaScrollBar::rangeAnimationFinished, this, [=]() {
        doItemsLayout();
    } );
    setHorizontalScrollBar( hScrollBar );
    setHorizontalScrollBarPolicy( Qt::ScrollBarAsNeeded );

    ElaScrollBar* vScrollBar = new ElaScrollBar( this );
    vScrollBar->setIsAnimation( true );
    connect( vScrollBar, &ElaScrollBar::rangeAnimationFinished, this, [=]() {
        doItemsLayout();
    } );
    setVerticalScrollBar( vScrollBar );
    setVerticalScrollBarPolicy( Qt::ScrollBarAsNeeded );

    d->_treeViewStyle = new ElaTreeViewStyle( style() );
    setStyle( d->_treeViewStyle );
}

ElaTreeWidget::~ElaTreeWidget()
{
}

void ElaTreeWidget::setItemHeight( int itemHeight )
{
    Q_D( ElaTreeWidget );
    if( itemHeight > 0 )
    {
        d->_treeViewStyle->setItemHeight( itemHeight );
        doItemsLayout();
    }
}

int ElaTreeWidget::getItemHeight() const
{
    Q_D( const ElaTreeWidget );
    return d->_treeViewStyle->getItemHeight();
}

void ElaTreeWidget::setHeaderMargin( int headerMargin )
{
    Q_D( ElaTreeWidget );
    if( headerMargin >= 0 )
    {
        d->_treeViewStyle->setHeaderMargin( headerMargin );
        doItemsLayout();
    }
}

int ElaTreeWidget::getHeaderMargin() const
{
    Q_D( const ElaTreeWidget );
    return d->_treeViewStyle->getHeaderMargin();
}
