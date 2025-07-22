#include "ElaToggleButton.h"

#include <QEvent>
#include <QPainter>
#include <QPainterPath>
#include <QPropertyAnimation>

#include "ElaTheme.h"
#include "private/ElaToggleButtonPrivate.h"
Q_PROPERTY_CREATE_Q_CPP(ElaToggleButton, int, BorderRadius)
Q_PROPERTY_CREATE_Q_CPP(ElaToggleButton, QString, Text)

Q_PROPERTY_CREATE_Q_CPP(ElaToggleButton, QColor, TextColor)
Q_PROPERTY_CREATE_Q_CPP(ElaToggleButton, QColor, TextSelectedColor)
Q_PROPERTY_CREATE_Q_CPP(ElaToggleButton, QColor, TextDisabledColor)

Q_PROPERTY_CREATE_Q_CPP(ElaToggleButton, QColor, BackgroundColor)
Q_PROPERTY_CREATE_Q_CPP(ElaToggleButton, QColor, BackgroundPressedColor)
Q_PROPERTY_CREATE_Q_CPP(ElaToggleButton, QColor, BackgroundHighlightedColor)
Q_PROPERTY_CREATE_Q_CPP(ElaToggleButton, QColor, BackgroundDisabledColor)

Q_PROPERTY_CREATE_Q_CPP(ElaToggleButton, QColor, SelectedBackgroundColor)
Q_PROPERTY_CREATE_Q_CPP(ElaToggleButton, QColor, SelectedBackgroundPressedColor)
Q_PROPERTY_CREATE_Q_CPP(ElaToggleButton, QColor, SelectedBackgroundHighlightedColor)
Q_PROPERTY_CREATE_Q_CPP(ElaToggleButton, QColor, SelectedBackgroundDisabledColor)
ElaToggleButton::ElaToggleButton(QWidget* parent)
    : QWidget(parent), d_ptr(new ElaToggleButtonPrivate())
{
    Q_D(ElaToggleButton);
    d->q_ptr = this;
    d->_pBorderRadius = 3;
    d->_themeMode = eTheme->getThemeMode();
    d->_pToggleAlpha = 0;
    setMouseTracking(true);
    setFixedSize(80, 32);
    QFont font = this->font();
    font.setPixelSize(15);
    setFont(font);
    setObjectName("ElaToggleButton");
    setStyleSheet("ElaToggleButton{background-color:transparent;}");
    connect(eTheme, &ElaTheme::themeModeChanged, this, [=](ElaThemeType::ThemeMode themeMode) {
        d->_themeMode = themeMode;
    });
}

ElaToggleButton::ElaToggleButton(QString text, QWidget* parent)
    : ElaToggleButton(parent)
{
    Q_D(ElaToggleButton);
    d->_pText = text;
}

ElaToggleButton::~ElaToggleButton()
{
}

void ElaToggleButton::setIsToggled(bool isToggled)
{
    Q_D(ElaToggleButton);
    d->_isToggled = isToggled;
    d->_pToggleAlpha = isToggled ? 255 : 0;
    d->_isAlphaAnimationFinished = true;
    update();
    Q_EMIT toggled(isToggled);
}

bool ElaToggleButton::getIsToggled() const
{
    Q_D(const ElaToggleButton);
    return d->_isToggled;
}

bool ElaToggleButton::event(QEvent* event)
{
    switch (event->type())
    {
    case QEvent::Enter:
    case QEvent::Leave:
    {
        update();
        break;
    }
    default:
    {
        break;
    }
    }
    return QWidget::event(event);
}

void ElaToggleButton::mousePressEvent(QMouseEvent* event)
{
    Q_D(ElaToggleButton);
    d->_isPressed = true;
    update();
    QWidget::mouseReleaseEvent(event);
}

void ElaToggleButton::mouseReleaseEvent(QMouseEvent* event)
{
    Q_D(ElaToggleButton);
    d->_isPressed = false;
    d->_isAlphaAnimationFinished = false;
    d->_isToggled = !d->_isToggled;
    QPropertyAnimation* alphaAnimation = new QPropertyAnimation(d, "pToggleAlpha");
    connect(alphaAnimation, &QPropertyAnimation::valueChanged, this, [=](const QVariant& value) {
        update();
    });
    connect(alphaAnimation, &QPropertyAnimation::finished, this, [=]() {
        d->_isAlphaAnimationFinished = true;
    });
    alphaAnimation->setDuration(250);
    alphaAnimation->setStartValue(d->_pToggleAlpha);
    if (d->_isToggled)
    {
        alphaAnimation->setEndValue(255);
    }
    else
    {
        alphaAnimation->setEndValue(0);
    }
    alphaAnimation->start(QAbstractAnimation::DeleteWhenStopped);
    Q_EMIT this->toggled(d->_isToggled);
    QWidget::mouseReleaseEvent(event);
}

void ElaToggleButton::paintEvent(QPaintEvent* event)
{
    Q_D(ElaToggleButton);
    QPainter painter(this);
    painter.setRenderHints(QPainter::Antialiasing | QPainter::TextAntialiasing);

    painter.save();
    QRect foregroundRect(1, 1, width() - 2, height() - 2);
    if (d->_isAlphaAnimationFinished)
    {
        if (d->_isToggled)
        {
            painter.setPen(ElaThemeColor(d->_themeMode, BasicBorder));
            painter.setBrush(retrieveBackgroundColor());
        }
        else
        {
            painter.setPen(ElaThemeColor(d->_themeMode, BasicBorder));
            painter.setBrush(retrieveBackgroundColor());
        }
    }
    else
    {
        painter.setPen(Qt::NoPen);
        QColor toggleColor = retrieveBackgroundColor();
        toggleColor.setAlpha(d->_pToggleAlpha);
        painter.setBrush(toggleColor);
    }
    painter.drawRoundedRect(foregroundRect, d->_pBorderRadius, d->_pBorderRadius);
    // 底边线绘制
    if (!d->_isPressed && !d->_isToggled)
    {
        painter.setPen(ElaThemeColor(d->_themeMode, BasicBaseLine));
        painter.drawLine(foregroundRect.x() + d->_pBorderRadius, height() - 1, foregroundRect.x() + foregroundRect.width() - d->_pBorderRadius, height() - 1);
    }

    //文字绘制
    painter.setPen(retrieveTextColor());
    painter.drawText(foregroundRect, Qt::AlignCenter | Qt::TextHideMnemonic, d->_pText);
    painter.restore();
}

QColor ElaToggleButton::retrieveTextColor()
{
    Q_D(ElaToggleButton);
    if( isEnabled() )
    {
        if( d->_isToggled )
        {
            if( d->_pTextSelectedColor.isValid() == true )
                return d->_pTextSelectedColor;
            return ElaThemeColor(d->_themeMode, BasicTextInvert);
        }

        if( d->_pTextColor.isValid() == true )
            return d->_pTextColor;
        return ElaThemeColor(d->_themeMode, BasicText);
    }

    if( d->_pTextDisabledColor.isValid() == true )
        return d->_pTextDisabledColor;
    return ElaThemeColor(d->_themeMode, BasicTextDisable);
}

QColor ElaToggleButton::retrieveBackgroundColor()
{
    Q_D(ElaToggleButton);
    if(d->_isAlphaAnimationFinished)
    {
        if(d->_isToggled)
        {
            if( isEnabled() )
            {
                if( d->_isPressed)
                {
                    if( d->_pSelectedBackgroundPressedColor.isValid() == true )
                        return d->_pSelectedBackgroundPressedColor;
                    return ElaThemeColor(d->_themeMode, PrimaryPress);
                }

                if( underMouse() )
                {
                    if( d->_pSelectedBackgroundHighlightedColor.isValid() == true )
                        return d->_pSelectedBackgroundHighlightedColor;
                    return ElaThemeColor(d->_themeMode, PrimaryHover);
                }

                if( d->_pSelectedBackgroundColor.isValid() == true )
                    return d->_pSelectedBackgroundColor;
                return ElaThemeColor(d->_themeMode, PrimaryNormal);
            }

            if( d->_pBackgroundDisabledColor.isValid() == true )
                return d->_pBackgroundDisabledColor;
            return ElaThemeColor(d->_themeMode, BasicDisable);
        }

        if( isEnabled() )
        {
            if(d->_isPressed)
            {
                if( d->_pBackgroundPressedColor.isValid() == true )
                    return d->_pBackgroundPressedColor;
                return ElaThemeColor(d->_themeMode, BasicPress);
            }

            if( underMouse() )
            {
                if( d->_pBackgroundHighlightedColor.isValid() == true )
                    return d->_pBackgroundHighlightedColor;
                return ElaThemeColor(d->_themeMode, BasicHover);
            }

            if( d->_pBackgroundColor.isValid() == true )
                return d->_pBackgroundColor;
            return ElaThemeColor(d->_themeMode, BasicBase);
        }

        if( d->_pBackgroundDisabledColor.isValid() == true )
            return d->_pBackgroundDisabledColor;
        return ElaThemeColor(d->_themeMode, BasicDisable);
    }

    if( d->_pSelectedBackgroundColor.isValid() == true )
        return d->_pSelectedBackgroundColor;
    return ElaThemeColor(d->_themeMode, PrimaryNormal);
}
