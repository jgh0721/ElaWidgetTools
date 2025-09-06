#ifndef ELALISTVIEWSTYLE_H
#define ELALISTVIEWSTYLE_H

#include <QProxyStyle>

#include "ElaDef.h"
class ElaListViewStyle : public QProxyStyle
{
    Q_OBJECT
    Q_PROPERTY_CREATE(int, ItemHeight)
    Q_PROPERTY_CREATE(bool, IsTransparent)
    Q_PROPERTY_CREATE(ElaListViewType::ElaIconViewSize, IconViewSize)

public:
    explicit ElaListViewStyle(QStyle* style = nullptr);
    ~ElaListViewStyle();
    void drawPrimitive(PrimitiveElement element, const QStyleOption* option, QPainter* painter, const QWidget* widget = nullptr) const override;
    void drawControl(ControlElement element, const QStyleOption* option, QPainter* painter, const QWidget* widget = nullptr) const override;
    QSize sizeFromContents(ContentsType type, const QStyleOption* option, const QSize& size, const QWidget* widget) const override;


    // 아이콘 크기별 픽셀 크기 반환
    int getIconPixelSize() const;

    // 아이콘 크기별 아이템 크기 계산
    QSize getItemSizeForIconMode() const;

    // 아이콘 크기별 레이아웃 스타일 판단
    bool isVerticalLayout() const; // true: 아이콘 위/텍스트 아래, false: 아이콘 왼쪽/텍스트 오른쪽

private:
    ElaThemeType::ThemeMode _themeMode;
    int _leftPadding{11};
};

#endif // ELALISTVIEWSTYLE_H
