#include "ElaTableWidget.h"

#include <QHeaderView>
#include <QMouseEvent>

#include "DeveloperComponents/ElaTableViewStyle.h"
#include "ElaScrollBar.h"
#include "ElaToolTip.h"
#include "ElaTableViewPrivate.h"

ElaTableWidget::ElaTableWidget( QWidget* parent )
    : QTableWidget( parent ), d_ptr( new ElaTableWidgetPrivate() )
{
    Q_D( ElaTableWidget );
    d->q_ptr = this;
    setMouseTracking( true );
    setObjectName( "ElaTableView" );
    setStyleSheet(
        "#ElaTableView{background-color:transparent;}"
        "QHeaderView{background-color:transparent;border:0px;}" );
    setShowGrid( false );
    setVerticalScrollBar( new ElaScrollBar( this ) );
    setHorizontalScrollBar( new ElaScrollBar( this ) );
    this->setHorizontalScrollBarPolicy( Qt::ScrollBarAsNeeded );
    this->setVerticalScrollBarPolicy( Qt::ScrollBarAsNeeded );
    setHorizontalScrollMode( QAbstractItemView::ScrollPerPixel );
    setVerticalScrollMode( QAbstractItemView::ScrollPerPixel );
    d->_tableViewStyle = new ElaTableViewStyle( style() );
    setStyle( d->_tableViewStyle );
}

ElaTableWidget::~ElaTableWidget()
{
}

void ElaTableWidget::setHeaderMargin( int headerMargin )
{
    Q_D( ElaTableWidget );
    if( headerMargin >= 0 )
    {
        d->_tableViewStyle->setHeaderMargin( headerMargin );
        doItemsLayout();
    }
}

void ElaTableWidget::addTooltipColumn( int column )
{
    setTooltipColumns.insert( column );
    if( Tooltip == nullptr )
        Tooltip = new ElaToolTip( this );
}

void ElaTableWidget::removeTooltipColumn( int column )
{
    setTooltipColumns.remove( column );
}

int ElaTableWidget::getHeaderMargin() const
{
    Q_D( const ElaTableWidget );
    return d->_tableViewStyle->getHeaderMargin();
}

void ElaTableWidget::showEvent( QShowEvent* event )
{
    Q_EMIT tableViewShow();
    QTableWidget::showEvent( event );
}

void ElaTableWidget::hideEvent( QHideEvent* event )
{
    if( Tooltip != nullptr )
        Tooltip->hide();
    Q_EMIT tableViewHide();
    QTableWidget::hideEvent( event );
}

void ElaTableWidget::mouseMoveEvent( QMouseEvent* event )
{
    Q_D( ElaTableWidget );

    QModelIndex Idx;

    if( Tooltip != nullptr || selectionBehavior() == QAbstractItemView::SelectRows )
    {
        Idx = indexAt( event->pos() );
    }

    if( Tooltip != nullptr )
    {
        if( setTooltipColumns.contains( Idx.column() ) == true )
        {
            if( Idx != TooltipIdx )
            {
                TooltipIdx = Idx;
                const auto text = item( Idx.row(), Idx.column() )->text();
                Tooltip->setToolTip( text );
                Tooltip->hide();
                Tooltip->show();
            }
        }
        else
        {
            Tooltip->hide();
        }
    }

    if( selectionBehavior() == QAbstractItemView::SelectRows )
    {
        d->_tableViewStyle->setCurrentHoverRow( Idx.row() );
        update();
    }
    QTableWidget::mouseMoveEvent( event );
}

void ElaTableWidget::leaveEvent( QEvent* event )
{
    Q_D( ElaTableWidget );

    if( Tooltip != nullptr )
        Tooltip->hide();

    if( selectionBehavior() == QAbstractItemView::SelectRows )
    {
        d->_tableViewStyle->setCurrentHoverRow( -1 );
        update();
    }
    QTableWidget::leaveEvent( event );
}
