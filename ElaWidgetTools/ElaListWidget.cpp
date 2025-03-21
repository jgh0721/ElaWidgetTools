#include "ElaListWidget.h"

#include <QMouseEvent>

#include "ElaListViewPrivate.h"
#include "ElaListViewStyle.h"
#include "ElaScrollBar.h"

ElaListWidget::ElaListWidget(QWidget* parent)
    : QListWidget(parent), d_ptr(new ElaListWidgetPrivate())
{
    Q_D(ElaListWidget);
    d->q_ptr = this;
    setObjectName("ElaListWidget");
    setStyleSheet("ElaListWidget{background-color:transparent;}");
    d->_listViewStyle = new ElaListViewStyle(style());
    setStyle(d->_listViewStyle);
    setMouseTracking(true);
    setVerticalScrollBar(new ElaScrollBar(this));
    setHorizontalScrollBar(new ElaScrollBar(this));
    this->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    this->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    setHorizontalScrollMode(QAbstractItemView::ScrollPerPixel);
    setVerticalScrollMode(QAbstractItemView::ScrollPerPixel);
}

ElaListWidget::~ElaListWidget()
{
}

void ElaListWidget::setItemHeight( int itemHeight )
{
    Q_D( ElaListWidget );
    if( itemHeight > 0 )
    {
        d->_listViewStyle->setItemHeight( itemHeight );
        doItemsLayout();
    }
}

int ElaListWidget::getItemHeight() const
{
    Q_D( const ElaListWidget );
    return d->_listViewStyle->getItemHeight();
}

void ElaListWidget::setIsTransparent( bool isTransparent )
{
    Q_D( ElaListWidget );
    d->_listViewStyle->setIsTransparent( isTransparent );
    update();
}

bool ElaListWidget::getIsTransparent() const
{
    Q_D( const ElaListWidget );
    return d->_listViewStyle->getIsTransparent();
}
