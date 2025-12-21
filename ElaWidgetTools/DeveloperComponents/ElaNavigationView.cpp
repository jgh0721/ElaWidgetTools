#include "ElaNavigationView.h"

#include <QDebug>
#include <QHeaderView>
#include <QModelIndex>
#include <QMouseEvent>
#include <QPainter>
#include <QScrollBar>
#include <QScroller>
#include <QStyledItemDelegate>
#include <QPainterPath>

#include "ElaMenu.h"
#include "ElaNavigationModel.h"
#include "ElaNavigationNode.h"
#include "ElaNavigationStyle.h"
#include "ElaScrollBar.h"
#include "ElaToolTip.h"
#include "ElaTheme.h"

class NavigationPageDelegate : public QStyledItemDelegate
{
public:
    using QStyledItemDelegate::QStyledItemDelegate;

    void paint( QPainter* p, const QStyleOptionViewItem& option, const QModelIndex& index ) const override
    {
        QStyleOptionViewItem opt( option );
        initStyleOption( &opt, index );

        auto* model = qobject_cast< ElaNavigationModel* >( const_cast< QAbstractItemModel* >( index.model() ) );
        auto* node = static_cast< ElaNavigationNode* >( index.internalPointer() );
        const bool isSelected = ( model && node && node == model->getSelectedNode() );
        const bool isHover = ( !isSelected && ( opt.state & QStyle::State_MouseOver ) );
        const auto themeMode = eTheme->getThemeMode();

        const int BarX = opt.rect.left() + 3;
        const int BarWidth = 3;
        const int IconSize = qMax( opt.decorationSize.isValid() ? opt.decorationSize.width() : 24, 24 );
        const int GapIconText = 8;

        const int sbw = opt.widget ? opt.widget->style()->pixelMetric( QStyle::PM_ScrollBarExtent, nullptr, opt.widget ) : 16;

        const int BadgeZoneWidth = 24;
        const int BadgeRightGap = sbw + 2;

        const int IconLeft = ( opt.rect.left() + 2 ) + BarWidth + 4;
        const QRect capsule = opt.rect.adjusted( 0, 0, 0, 0 );

        p->save();
        p->setRenderHints( QPainter::Antialiasing | QPainter::SmoothPixmapTransform | QPainter::TextAntialiasing );

        // 1. 캡슐 배경 제작
        if( isSelected || isHover )
        {
            QPainterPath path; path.addRoundedRect( capsule, 8, 8 );
            const QColor bg = isSelected ? ElaThemeColor( themeMode, BasicSelectedAlpha ) : ElaThemeColor( themeMode, BasicHoverAlpha );
            p->fillPath( path, bg );
        }

        // 2. 좌측 포커스 바 제작
        if( isSelected )
        {
            p->setPen( Qt::NoPen );
            p->setBrush( ElaThemeColor( themeMode, PrimaryNormal ) );
            p->drawRoundedRect( QRectF( BarX, capsule.y() + 10, BarWidth, capsule.height() - 20 ), 3, 3 );
        }
        // 3. 아이콘 제작
        const QRect iconRect( IconLeft, capsule.y() + ( capsule.height() - IconSize ) / 2, IconSize, IconSize );
        const QIcon ico = qvariant_cast< QIcon >( index.data( Qt::DecorationRole ) );
        if( ico.isNull() == true )
        {
            if (node->getAwesome() != ElaIconType::None)
            {
                p->save();
                QFont iconFont = QFont("ElaAwesome");
                iconFont.setPixelSize(17);
                p->setFont(iconFont);
                p->drawText(QRect(iconRect.x(), iconRect.y(), iconRect.width(), iconRect.height()), Qt::AlignCenter,
                            QChar(( unsigned short )node->getAwesome()));
                p->restore();
            }
        }
        else
        {
            const qreal dpr = p->device()->devicePixelRatioF();
            QPixmap pm = ico.pixmap( QSize( qRound( IconSize * dpr ), qRound( IconSize * dpr ) ) );
            pm.setDevicePixelRatio( dpr );
            p->drawPixmap( iconRect, pm );
        }
        // 4. 텍스트 제작
        const int textLeft = iconRect.right() + GapIconText;
        const int badgeReserve = BadgeRightGap + BadgeZoneWidth;
        QRect textRc( textLeft, opt.rect.y(), qMax( 0, opt.rect.width() - textLeft - badgeReserve ), opt.rect.height() );

        p->setPen( ElaThemeColor( themeMode, BasicText ) );
        p->setFont( opt.font );
        const QString title = node ? node->getNodeTitle() : QString();
        const QString elided = QFontMetrics( opt.font ).elidedText( title, Qt::ElideRight, textRc.width() );
        p->drawText( textRc, Qt::AlignVCenter | Qt::AlignLeft, elided );

        if( node )
        {
            const int keyPoints = node->getKeyPoints();   // 노드의 KeyPoints = 안 읽은 메시지 수

            // 0 이하면 배지 표시 안 함
            if( keyPoints > 0 )
            {
                const int BadgeW = 16;
                const int BadgeH = 16;

                QRect smallBadge( iconRect.left() + 12, iconRect.top() - 4, BadgeW, BadgeH );

                p->save();
                p->setRenderHint( QPainter::Antialiasing );

                p->setBrush( QColor( "#EE3838" ) );
                p->setPen( Qt::NoPen );
                p->drawEllipse( smallBadge );

                p->setPen( Qt::white );
                QFont font = opt.font;
                font.setPointSize( 8 );
                p->setFont( font );

                QString badgeText;
                if( keyPoints > 99 )
                    badgeText = "99";
                else
                    badgeText = QString::number( keyPoints );

                p->drawText( smallBadge, Qt::AlignHCenter|Qt::AlignTop, badgeText );
                p->restore();
            }
        }

        // 5. 읽지 않은 메시지 배지 제작
        {
            QRect BigBadge( opt.rect.right() - BadgeRightGap - BadgeZoneWidth, opt.rect.y(), BadgeZoneWidth, opt.rect.height() );

            QStyleOptionViewItem badgeOpt( opt );
            badgeOpt.state &= ~( QStyle::State_Selected | QStyle::State_MouseOver | QStyle::State_HasFocus );
            badgeOpt.text.clear();
            badgeOpt.icon = QIcon();
            badgeOpt.backgroundBrush = Qt::NoBrush;

            p->save();
            p->setClipRect( BigBadge );
            QStyledItemDelegate::paint( p, badgeOpt, index );
            p->restore();
        }
        p->restore();
    }

    QSize sizeHint( const QStyleOptionViewItem& option, const QModelIndex& index ) const override
    {
        QSize size = QStyledItemDelegate::sizeHint( option, index );
        size.setHeight( 40 );
        return size;
    }
};

ElaNavigationView::ElaNavigationView(QWidget* parent)
    : QTreeView(parent)
{
    setObjectName("ElaNavigationView");
    setStyleSheet("ElaNavigationView{background-color:transparent;}");
    setAnimated(true);
    setHeaderHidden(true);
    setRootIsDecorated(false);
    setExpandsOnDoubleClick(false);
    setAutoScroll(false);
    setMouseTracking(true);
    setSelectionMode(QAbstractItemView::NoSelection);

    // 滚动条设置
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    ElaScrollBar* vScrollBar = new ElaScrollBar(this);
    connect(vScrollBar, &ElaScrollBar::rangeAnimationFinished, this, [=]() {
        doItemsLayout();
    });
    setVerticalScrollBar(vScrollBar);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollMode(QAbstractItemView::ScrollPerPixel);
    ElaScrollBar* floatVScrollBar = new ElaScrollBar(vScrollBar, this);
    floatVScrollBar->setIsAnimation(true);
    floatVScrollBar->installEventFilter(this);

    _navigationStyle = new ElaNavigationStyle(this->style());
    _navigationStyle->setNavigationView(this);
    setStyle(_navigationStyle);
    setIconSize( QSize( 24, 24 ) );
    setItemDelegate( new NavigationPageDelegate( this ) );
    QScroller::grabGesture(this->viewport(), QScroller::LeftMouseButtonGesture);
    QScroller* scroller = QScroller::scroller(this->viewport());
    QScrollerProperties properties = scroller->scrollerProperties();
    properties.setScrollMetric(QScrollerProperties::MousePressEventDelay, 0);
    properties.setScrollMetric(QScrollerProperties::HorizontalOvershootPolicy, QScrollerProperties::OvershootAlwaysOff);
    properties.setScrollMetric(QScrollerProperties::VerticalOvershootPolicy, QScrollerProperties::OvershootAlwaysOn);
    properties.setScrollMetric(QScrollerProperties::OvershootDragResistanceFactor, 0.35);
    properties.setScrollMetric(QScrollerProperties::OvershootScrollTime, 0.5);
    properties.setScrollMetric(QScrollerProperties::FrameRate, QScrollerProperties::Fps60);
    scroller->setScrollerProperties(properties);

    connect(scroller, &QScroller::stateChanged, this, [=](QScroller::State newstate) {
        if (newstate == QScroller::Pressed)
        {
            _navigationStyle->setPressIndex(indexAt(mapFromGlobal(QCursor::pos())));
            viewport()->update();
        }
        else if (newstate == QScroller::Scrolling || newstate == QScroller::Inactive)
        {
            _navigationStyle->setPressIndex(QModelIndex());
        }
    });

    setContextMenuPolicy(Qt::CustomContextMenu);
    connect(this, &ElaNavigationView::customContextMenuRequested, this, &ElaNavigationView::onCustomContextMenuRequested);
}

ElaNavigationView::~ElaNavigationView()
{
}

void ElaNavigationView::navigationNodeStateChange(QVariantMap data)
{
    this->_navigationStyle->navigationNodeStateChange(data);
}

void ElaNavigationView::onCustomContextMenuRequested(const QPoint& pos)
{
    if (!_pNavigationBarPrivate->_pIsAllowPageOpenInNewWindow)
    {
        return;
    }
    QModelIndex posIndex = indexAt(pos);
    if (!posIndex.isValid())
    {
        return;
    }
    ElaNavigationNode* posNode = static_cast<ElaNavigationNode*>(posIndex.internalPointer());
    if (!posNode->getIsExpanderNode())
    {
        ElaMenu menu;
        menu.setMenuItemHeight(27);
        QAction* openAction = menu.addElaIconAction(ElaIconType::ObjectGroup, tr("在新窗口中打开"));
        connect(openAction, &QAction::triggered, this, [=]() {
            Q_EMIT navigationOpenNewWindow(posNode->getNodeKey());
        });
        menu.exec(mapToGlobal(pos));
    }
}

void ElaNavigationView::mouseMoveEvent(QMouseEvent* event)
{
    _doCompactToolTip();
    QTreeView::mouseMoveEvent(event);
}

void ElaNavigationView::mouseDoubleClickEvent(QMouseEvent* event)
{
    _navigationStyle->setPressIndex(indexAt(event->pos()));
    viewport()->update();
    QTreeView::mouseDoubleClickEvent(event);
}

void ElaNavigationView::mouseReleaseEvent(QMouseEvent* event)
{
    QTreeView::mouseReleaseEvent(event);
    if (event->button() == Qt::LeftButton)
    {
        QModelIndex index = indexAt(event->pos());
        if (index.isValid())
        {
            Q_EMIT navigationClicked(index);
        }
        _navigationStyle->setPressIndex(QModelIndex());
    }
}

bool ElaNavigationView::eventFilter(QObject* watched, QEvent* event)
{
    switch (event->type())
    {
    case QEvent::MouseMove:
    case QEvent::HoverMove:
    {
        _doCompactToolTip();
        break;
    }
    default:
    {
        break;
    }
    }
    return QAbstractItemView::eventFilter(watched, event);
}

void ElaNavigationView::_doCompactToolTip()
{
    if (_pNavigationBarPrivate->_currentDisplayMode == ElaNavigationType::NavigationDisplayMode::Compact)
    {
        if (!_compactToolTip)
        {
            _compactToolTip = new ElaToolTip(this);
        }
        QModelIndex posIndex = indexAt(mapFromGlobal(QCursor::pos()));
        if (!posIndex.isValid())
        {
            _compactToolTip->hide();
            return;
        }
        ElaNavigationNode* posNode = static_cast<ElaNavigationNode*>(posIndex.internalPointer());
        _compactToolTip->setToolTip(posNode->getNodeTitle());
        _compactToolTip->updatePos();
        _compactToolTip->show();
    }
    else
    {
        if (_compactToolTip)
        {
            _compactToolTip->deleteLater();
            _compactToolTip = nullptr;
        }
    }
}
