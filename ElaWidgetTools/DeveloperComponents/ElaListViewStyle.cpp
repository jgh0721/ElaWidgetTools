#include "ElaListViewStyle.h"

#include <QPainter>
#include <QPainterPath>
#include <QStyleOption>

#include "ElaListView.h"
#include "ElaTheme.h"
ElaListViewStyle::ElaListViewStyle(QStyle* style)
{
    _pItemHeight = 35;
    _pIsTransparent = false;
    _pIconViewSize = ElaListViewType::SmallIcon;
    _themeMode = eTheme->getThemeMode();
    connect(eTheme, &ElaTheme::themeModeChanged, this, [=](ElaThemeType::ThemeMode themeMode) {
        _themeMode = themeMode;
    });
}

ElaListViewStyle::~ElaListViewStyle()
{
}

void ElaListViewStyle::drawPrimitive(PrimitiveElement element, const QStyleOption* option, QPainter* painter, const QWidget* widget) const
{
    switch (element)
    {
    case QStyle::PE_PanelItemViewItem:
    {
        // Item背景
        if (const QStyleOptionViewItem* vopt = qstyleoption_cast<const QStyleOptionViewItem*>(option))
        {
            painter->save();
            painter->setRenderHint(QPainter::Antialiasing);
            QRect itemRect = vopt->rect;
            itemRect.adjust(0, 2, 0, -2);
            QPainterPath path;
            path.addRoundedRect(itemRect, 4, 4);
            if (vopt->state & QStyle::State_Selected)
            {
                if (vopt->state & QStyle::State_MouseOver)
                {
                    // 选中时覆盖
                    painter->fillPath(path, ElaThemeColor(_themeMode, BasicSelectedHoverAlpha));
                }
                else
                {
                    // 选中
                    painter->fillPath(path, ElaThemeColor(_themeMode, BasicSelectedAlpha));
                }
            }
            else
            {
                if (vopt->state & QStyle::State_MouseOver)
                {
                    // 覆盖时颜色
                    painter->fillPath(path, ElaThemeColor(_themeMode, BasicHoverAlpha));
                }
            }
            painter->restore();
        }
        return;
    }
    case QStyle::PE_PanelItemViewRow:
    {
        // Item背景隔行变色
        if (const QStyleOptionViewItem* vopt = qstyleoption_cast<const QStyleOptionViewItem*>(option))
        {
            if (vopt->features == QStyleOptionViewItem::Alternate)
            {
                painter->save();
                painter->setRenderHint(QPainter::Antialiasing);
                painter->setPen(Qt::NoPen);
                painter->setBrush(ElaThemeColor(_themeMode, BasicAlternating));
                painter->drawRect(vopt->rect);
                painter->restore();
            }
        }
        return;
    }
    case QStyle::PE_Widget:
    {
        return;
    }
    default:
    {
        break;
    }
    }
    QProxyStyle::drawPrimitive(element, option, painter, widget);
}

void ElaListViewStyle::drawControl(ControlElement element, const QStyleOption* option, QPainter* painter, const QWidget* widget) const
{
    switch (element)
    {
    case QStyle::CE_ShapedFrame:
    {
        // viewport视口外的其他区域背景
        if (!_pIsTransparent)
        {
            QRect frameRect = option->rect;
            frameRect.adjust(1, 1, -1, -1);
            painter->save();
            painter->setRenderHints(QPainter::Antialiasing);
            painter->setPen(ElaThemeColor(_themeMode, PopupBorder));
            painter->setBrush(ElaThemeColor(_themeMode, BasicBaseAlpha));
            painter->drawRoundedRect(frameRect, 3, 3);
            painter->restore();
        }
        return;
    }
    case QStyle::CE_ItemViewItem:
    {
        if (const QStyleOptionViewItem* vopt = qstyleoption_cast<const QStyleOptionViewItem*>(option))
        {
            // 背景绘制
            this->drawPrimitive(QStyle::PE_PanelItemViewItem, option, painter, widget);

            // 内容绘制
            QRect itemRect = option->rect;
            painter->save();
            painter->setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform | QPainter::TextAntialiasing);
            const QListView* listView = dynamic_cast<const QListView*>(widget);
            QListView::ViewMode viewMode = listView->viewMode();
            // QRect checkRect = proxy()->subElementRect(SE_ItemViewItemCheckIndicator, vopt, widget);
            QRect iconRect = proxy()->subElementRect(SE_ItemViewItemDecoration, vopt, widget);
            QRect textRect = proxy()->subElementRect(SE_ItemViewItemText, vopt, widget);

            if( viewMode == QListView::ListMode )
            {
                iconRect.adjust(_leftPadding, 0, 0, 0);
                textRect.adjust(_leftPadding, 0, 0, 0);
            }
            else if (viewMode == QListView::IconMode)
            {
                int iconSize = getIconPixelSize();
                int padding = 4;

                if (isVerticalLayout())
                {
                    // 세로 레이아웃: 아이콘 위, 텍스트 아래

                    // 아이콘을 아이템 상단 중앙에 배치
                    iconRect = QRect(itemRect.x() + (itemRect.width() - iconSize) / 2,
                                   itemRect.y() + padding,
                                   iconSize, iconSize);

                    // 텍스트를 아이콘 아래쪽에 배치
                    int textTop = iconRect.bottom() + padding;
                    int textHeight = itemRect.bottom() - textTop - padding;

                    textRect = QRect(itemRect.x() + padding,
                                   textTop,
                                   itemRect.width() - 2 * padding,
                                   textHeight);
                }
                else
                {
                    // 가로 레이아웃 (SmallIcon): 아이콘 왼쪽, 텍스트 오른쪽
                    iconRect = QRect(itemRect.x() + padding,
                                   itemRect.y() + (itemRect.height() - iconSize) / 2,
                                   iconSize, iconSize);

                    textRect = QRect(iconRect.right() + padding,
                                   itemRect.y() + padding,
                                   itemRect.right() - iconRect.right() - 2 * padding,
                                   itemRect.height() - 2 * padding);
                }
            }

            // 图标绘制
            if (!vopt->icon.isNull())
            {
                QIcon::Mode mode = QIcon::Normal;
                if (!(vopt->state.testFlag(QStyle::State_Enabled)))
                {
                    mode = QIcon::Disabled;
                }
                else if (vopt->state.testFlag(QStyle::State_Selected))
                {
                    mode = QIcon::Selected;
                }
                QIcon::State state = vopt->state & QStyle::State_Open ? QIcon::On : QIcon::Off;
                vopt->icon.paint(painter, iconRect, vopt->decorationAlignment, mode, state);
            }
            // 文字绘制
            if (!vopt->text.isEmpty())
            {
                painter->setPen(ElaThemeColor(_themeMode, BasicText));
                if( viewMode == QListView::ListMode )
                {
                    painter->drawText(textRect, vopt->displayAlignment, vopt->text);
                }
                else
                {
                    if (isVerticalLayout())
                    {
                        // 세로 레이아웃: 텍스트 중앙 정렬, 필요시 줄임표
                        QFontMetrics fm(vopt->font);
                        QString elidedText = vopt->text;

                        // 아이콘 크기에 따른 텍스트 처리
                        if (_pIconViewSize == ElaListViewType::ElaIconViewSize::MediumIcon)
                        {
                            // Medium 아이콘: 한 줄로 제한
                            elidedText = fm.elidedText(vopt->text, Qt::ElideRight, textRect.width());
                            painter->drawText(textRect, Qt::AlignHCenter | Qt::AlignTop, elidedText);
                        }
                        else
                        {
                            // Large, ExtraLarge 아이콘: 여러 줄 허용
                            painter->drawText(textRect, Qt::AlignHCenter | Qt::AlignTop | Qt::TextWordWrap, vopt->text);
                        }
                    }
                    else
                    {
                        // 가로 레이아웃 (SmallIcon): 왼쪽 정렬
                        QFontMetrics fm(vopt->font);
                        QString elidedText = fm.elidedText(vopt->text, Qt::ElideRight, textRect.width());
                        painter->drawText(textRect, Qt::AlignLeft | Qt::AlignVCenter, elidedText);
                    }
                }
            }
            // 选中特效
            if (vopt->state.testFlag(QStyle::State_Selected) && viewMode == QListView::ListMode)
            {
                if( viewMode == QListView::ListMode )
                {
                    int heightOffset = itemRect.height() / 4;
                    painter->setPen(Qt::NoPen);
                    painter->setBrush(ElaThemeColor(_themeMode, PrimaryNormal));
                    painter->drawRoundedRect(QRectF(itemRect.x() + 3, itemRect.y() + heightOffset, 3, itemRect.height() - 2 * heightOffset), 3, 3);
                }
                else if( viewMode == QListView::IconMode )
                {
                    // Icon 모드: 테두리 강조
                    painter->setPen(QPen(ElaThemeColor(_themeMode, PrimaryNormal), 2));
                    painter->setBrush(Qt::NoBrush);
                    QRect highlightRect = itemRect;
                    highlightRect.adjust(1, 1, -1, -1);
                    painter->drawRoundedRect(highlightRect, 6, 6);
                }
            }
            painter->restore();
        }

        return;
    }
    default:
    {
        break;
    }
    }
    QProxyStyle::drawControl(element, option, painter, widget);
}

QSize ElaListViewStyle::sizeFromContents(ContentsType type, const QStyleOption* option, const QSize& size, const QWidget* widget) const
{
    switch (type)
    {
    case QStyle::CT_ItemViewItem:
    {
        QSize itemSize = QProxyStyle::sizeFromContents(type, option, size, widget);
        const QListView* listView = dynamic_cast<const QListView*>(widget);
        QListView::ViewMode viewMode = listView->viewMode();
        if (viewMode == QListView::ListMode)
        {
            itemSize.setWidth(itemSize.width() + _leftPadding);
            itemSize.setHeight(_pItemHeight);
        }
        else if( viewMode == QListView::IconMode )
        {
            itemSize = getItemSizeForIconMode();
        }
        return itemSize;
    }
    default:
    {
        break;
    }
    }
    return QProxyStyle::sizeFromContents(type, option, size, widget);
}

int ElaListViewStyle::getIconPixelSize() const
{
    switch (_pIconViewSize)
    {
        case ElaListViewType::ElaIconViewSize::SmallIcon:
            return 16;
        case ElaListViewType::ElaIconViewSize::MediumIcon:
            return 32;
        case ElaListViewType::ElaIconViewSize::LargeIcon:
            return 48;
        case ElaListViewType::ElaIconViewSize::ExtraLargeIcon:
            return 64;
        default:
            return 48;
    }
}

QSize ElaListViewStyle::getItemSizeForIconMode() const
{
    int iconSize = getIconPixelSize();
    int padding = 4;

    switch (_pIconViewSize)
    {
        case ElaListViewType::ElaIconViewSize::SmallIcon:
            // 작은 아이콘: 가로 레이아웃 (List 모드와 비슷)
            return QSize(200, iconSize + 2 * padding);

        case ElaListViewType::ElaIconViewSize::MediumIcon:
            // 보통 아이콘: 세로 레이아웃, 컴팩트
            return QSize(iconSize + 24, iconSize + 32);

        case ElaListViewType::ElaIconViewSize::LargeIcon:
            // 큰 아이콘: 세로 레이아웃, 표준 간격
            return QSize(iconSize + 32, iconSize + 48);

        case ElaListViewType::ElaIconViewSize::ExtraLargeIcon:
            // 매우 큰 아이콘: 세로 레이아웃, 큰 간격
            return QSize(iconSize + 40, iconSize + 60);

        default:
            return QSize(80, 80);
    }
}

bool ElaListViewStyle::isVerticalLayout() const
{
    return _pIconViewSize != ElaListViewType::ElaIconViewSize::SmallIcon;
}
