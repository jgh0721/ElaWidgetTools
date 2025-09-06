#include "ElaListView.h"

#include <QMouseEvent>

#include "ElaListViewPrivate.h"
#include "ElaListViewStyle.h"
#include "ElaScrollBar.h"
ElaListView::ElaListView(QWidget* parent)
    : QListView(parent), d_ptr(new ElaListViewPrivate())
{
    Q_D(ElaListView);
    d->q_ptr = this;
    setObjectName("ElaListView");
    setStyleSheet("ElaListView{background-color:transparent;}");
    d->_listViewStyle = new ElaListViewStyle(style());
    setStyle(d->_listViewStyle);
    setMouseTracking(true);
    setVerticalScrollBar(new ElaScrollBar(this));
    setHorizontalScrollBar(new ElaScrollBar(this));
    this->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    this->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    setHorizontalScrollMode(QAbstractItemView::ScrollPerPixel);
    setVerticalScrollMode(QAbstractItemView::ScrollPerPixel);

    // 기본 아이콘 크기 설정
    setIconViewSize(ElaListViewType::SmallIcon);
}

ElaListView::~ElaListView()
{
    Q_D(ElaListView);
    delete d->_listViewStyle;
}

void ElaListView::setItemHeight(int itemHeight)
{
    Q_D(ElaListView);
    if (itemHeight > 0)
    {
        d->_listViewStyle->setItemHeight(itemHeight);
        doItemsLayout();
    }
}

int ElaListView::getItemHeight() const
{
    Q_D(const ElaListView);
    return d->_listViewStyle->getItemHeight();
}

void ElaListView::setIsTransparent(bool isTransparent)
{
    Q_D(ElaListView);
    d->_listViewStyle->setIsTransparent(isTransparent);
    update();
}

bool ElaListView::getIsTransparent() const
{
    Q_D(const ElaListView);
    return d->_listViewStyle->getIsTransparent();
}


void ElaListView::setIconViewSize(ElaListViewType::ElaIconViewSize IconViewSize)
{
    Q_D(ElaListView);
    d->_listViewStyle->setIconViewSize(IconViewSize);
    doItemsLayout();
    update();
}

ElaListViewType::ElaIconViewSize ElaListView::getIconViewSize() const
{
    Q_D(const ElaListView);
    return d->_listViewStyle->getIconViewSize();
}

int ElaListView::getIconPixelSize() const
{
    Q_D(const ElaListView);
    return d->_listViewStyle->getIconPixelSize();
}