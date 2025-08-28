#include "ElaPushButton.h"

#include <QPainter>
#include <QPainterPath>

#include "ElaTheme.h"
#include "private/ElaPushButtonPrivate.h"
Q_PROPERTY_CREATE_Q_CPP(ElaPushButton, int, BorderRadius)
Q_PROPERTY_CREATE_Q_CPP(ElaPushButton, QColor, LightDefaultColor)
Q_PROPERTY_CREATE_Q_CPP(ElaPushButton, QColor, DarkDefaultColor)
Q_PROPERTY_CREATE_Q_CPP(ElaPushButton, QColor, LightAlternateColor)
Q_PROPERTY_CREATE_Q_CPP(ElaPushButton, QColor, DarkAlternateColor)
Q_PROPERTY_CREATE_Q_CPP(ElaPushButton, QColor, LightHoverColor)
Q_PROPERTY_CREATE_Q_CPP(ElaPushButton, QColor, DarkHoverColor)
Q_PROPERTY_CREATE_Q_CPP(ElaPushButton, QColor, LightPressColor)
Q_PROPERTY_CREATE_Q_CPP(ElaPushButton, QColor, DarkPressColor)
Q_PROPERTY_CREATE_Q_CPP(ElaPushButton, QColor, LightTextColor)
Q_PROPERTY_CREATE_Q_CPP(ElaPushButton, QColor, DarkTextColor)
Q_PROPERTY_CREATE_Q_CPP(ElaPushButton, QColor, LightDisabledTextColor)
Q_PROPERTY_CREATE_Q_CPP(ElaPushButton, QColor, DarkDisabledTextColor)
Q_PROPERTY_CREATE_Q_CPP(ElaPushButton, QColor, LightDisabledColor)
Q_PROPERTY_CREATE_Q_CPP(ElaPushButton, QColor, DarkDisabledColor)
Q_PROPERTY_CREATE_Q_CPP(ElaPushButton, bool, NoEffectButton)
ElaPushButton::ElaPushButton(QWidget* parent)
    : QPushButton(parent), d_ptr(new ElaPushButtonPrivate())
{
    Q_D(ElaPushButton);
    d->q_ptr = this;
    d->_pBorderRadius = 3;
    d->_themeMode = eTheme->getThemeMode();
    d->_pLightDefaultColor = ElaThemeColor(ElaThemeType::Light, BasicBase);
    d->_pDarkDefaultColor = ElaThemeColor(ElaThemeType::Dark, BasicBase);
    d->_pLightAlternateColor = ElaThemeColor(ElaThemeType::Light, BasicBaseAlternate);
    d->_pDarkAlternateColor = ElaThemeColor(ElaThemeType::Dark, BasicBaseAlternate);
    d->_pLightHoverColor = ElaThemeColor(ElaThemeType::Light, BasicHover);
    d->_pDarkHoverColor = ElaThemeColor(ElaThemeType::Dark, BasicHover);
    d->_pLightPressColor = ElaThemeColor(ElaThemeType::Light, BasicPress);
    d->_pDarkPressColor = ElaThemeColor(ElaThemeType::Dark, BasicPress);
    d->_pLightTextColor = ElaThemeColor(ElaThemeType::Light, BasicText);
    d->_pDarkTextColor = ElaThemeColor(ElaThemeType::Dark, BasicText);
    d->_pLightDisabledTextColor = ElaThemeColor(ElaThemeType::Light, BasicTextDisable);
    d->_pDarkDisabledTextColor = ElaThemeColor(ElaThemeType::Dark, BasicTextDisable);
    d->_pLightDisabledColor = ElaThemeColor(ElaThemeType::Light, BasicDisable);
    d->_pDarkDisabledColor = ElaThemeColor(ElaThemeType::Dark, BasicDisable);
    d->_pNoEffectButton = false;
    setMouseTracking(true);
    setFixedHeight(38);
    QFont font = this->font();
    font.setPixelSize(15);
    setFont(font);
    setObjectName("ElaPushButton");
    setStyleSheet("ElaPushButton{background-color:transparent;}");
    connect(eTheme, &ElaTheme::themeModeChanged, this, [=](ElaThemeType::ThemeMode themeMode) {
        d->_themeMode = themeMode;
    });
}

ElaPushButton::ElaPushButton(QString text, QWidget* parent)
    : ElaPushButton(parent)
{
    setText(text);
}

ElaPushButton::~ElaPushButton()
{
}

void ElaPushButton::mousePressEvent(QMouseEvent* event)
{
    Q_D(ElaPushButton);
    d->_isPressed = true;
    QPushButton::mousePressEvent(event);
}

void ElaPushButton::mouseReleaseEvent(QMouseEvent* event)
{
    Q_D(ElaPushButton);
    d->_isPressed = false;
    QPushButton::mouseReleaseEvent(event);
}

void ElaPushButton::paintEvent(QPaintEvent* event)
{
    Q_D(ElaPushButton);
    QPainter painter(this);
    painter.setRenderHints(QPainter::SmoothPixmapTransform | QPainter::Antialiasing | QPainter::TextAntialiasing);
    // 高性能阴影
    if( d->_pNoEffectButton == false )
        eTheme->drawEffectShadow(&painter, rect(), d->_shadowBorderWidth, d->_pBorderRadius);

    // 背景绘制
    painter.save();
    QRect foregroundRect(d->_shadowBorderWidth, d->_shadowBorderWidth, width() - 2 * (d->_shadowBorderWidth), height() - 2 * d->_shadowBorderWidth);
    if (d->_themeMode == ElaThemeType::Light)
    {
        painter.setPen(ElaThemeColor(ElaThemeType::Light, BasicBorder));
        painter.setBrush(retrieveBackgroundColor());
    }
    else
    {
        painter.setPen(Qt::NoPen);
        painter.setBrush(retrieveBackgroundColor());
    }
    if( d->_pNoEffectButton == false )
    {
        painter.drawRoundedRect(foregroundRect, d->_pBorderRadius, d->_pBorderRadius);
        // 底边线绘制
        if (!d->_isPressed)
        {
            painter.setPen(ElaThemeColor(d->_themeMode, BasicBaseLine));
            painter.drawLine(foregroundRect.x() + d->_pBorderRadius, height() - d->_shadowBorderWidth, foregroundRect.width(), height() - d->_shadowBorderWidth);
        }
    }
    //文字绘制
    painter.setPen(retrieveTextColor());
    painter.drawText(foregroundRect, Qt::AlignCenter | Qt::TextShowMnemonic, text());
    painter.restore();
}

QColor ElaPushButton::retrieveTextColor() const
{
    Q_D(const ElaPushButton);

    if( d->_themeMode == ElaThemeType::Light )
    {
        if( isEnabled() == true )
            return d->_pLightTextColor;

        return d->_pLightDefaultColor;
    }

    if( isEnabled() == true )
        return d->_pDarkTextColor;

    return d->_pDarkDefaultColor;
}

QColor ElaPushButton::retrieveBackgroundColor() const
{
    Q_D(const ElaPushButton);

    if( d->_themeMode == ElaThemeType::Light )
    {
        if( isEnabled() == true )
        {
            if( d->_isPressed == true )
                return d->_pLightPressColor;

            if( underMouse() == true )
                return d->_pLightHoverColor;

            if( isDefault() == true )
                return d->_pLightDefaultColor;

            return d->_pLightAlternateColor;
        }

        return d->_pLightDisabledColor;
    }

    if( isEnabled() == true )
    {
        if( d->_isPressed == true )
            return d->_pDarkPressColor;

        if( underMouse() == true )
            return d->_pDarkHoverColor;

        if( isDefault() == true )
            return d->_pDarkDefaultColor;

        return d->_pDarkAlternateColor;
    }

    return d->_pDarkDisabledColor;
}
