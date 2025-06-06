#include "ElaText.h"

#include <QContextMenuEvent>
#include <QPainter>

#include "ElaTheme.h"
#include "private/ElaTextPrivate.h"
ElaText::ElaText(QWidget* parent)
    : QLabel(parent), d_ptr(new ElaTextPrivate())
{
    Q_D(ElaText);
    d->q_ptr = this;
    d->_pTextStyle = ElaTextType::NoStyle;
    d->_pElaIcon = ElaIconType::None;
    d->_pTextColor = eTheme->getThemeColor( eTheme->getThemeMode(), ElaThemeType::BasicText );
    setObjectName("ElaText");
    setStyleSheet("#ElaText{background-color:transparent;}");
    QFont textFont = font();
    textFont.setLetterSpacing(QFont::AbsoluteSpacing, d->_textSpacing);
    textFont.setPixelSize(28);
    setFont(textFont);
    setWordWrap(true);
    d->_themeMode = eTheme->getThemeMode();
    d->onThemeChanged(eTheme->getThemeMode());

    connect(eTheme, &ElaTheme::themeModeChanged, d, &ElaTextPrivate::onThemeChanged);
    connect( this, &ElaText::pTextColorChanged, [d](){d->onThemeChanged(d->_themeMode);} );
}

ElaText::ElaText(QString text, QWidget* parent)
    : ElaText(parent)
{
    setText(text);
}

ElaText::ElaText(QString text, int pixelSize, QWidget* parent)
    : ElaText(text, parent)
{
    QFont font = this->font();
    font.setPixelSize(pixelSize);
    setFont(font);
}

ElaText::~ElaText()
{
}

void ElaText::setIsWrapAnywhere(bool isWrapAnywhere)
{
    Q_D(ElaText);
    setWordWrap(isWrapAnywhere);
    d->_isWrapAnywhere = isWrapAnywhere;
}

bool ElaText::getIsWrapAnywhere() const
{
    Q_D(const ElaText);
    return d->_isWrapAnywhere;
}

void ElaText::setTextPixelSize(int size)
{
    QFont font = this->font();
    font.setPixelSize(size);
    setFont(font);
}

int ElaText::getTextPixelSize() const
{
    return this->font().pixelSize();
}

void ElaText::setTextPointSize(int size)
{
    QFont font = this->font();
    font.setPointSize(size);
    setFont(font);
}

int ElaText::getTextPointSize() const
{
    return this->font().pointSize();
}

void ElaText::setTextStyle(ElaTextType::TextStyle textStyle)
{
    Q_D(ElaText);
    QFont textFont = font();
    d->_pTextStyle = textStyle;
    switch (textStyle)
    {
    case ElaTextType::NoStyle:
    {
        break;
    }
    case ElaTextType::Caption:
    {
        textFont.setPixelSize(12);
        break;
    }
    case ElaTextType::Body:
    {
        textFont.setPixelSize(13);
        break;
    }
    case ElaTextType::BodyStrong:
    {
        textFont.setPixelSize(13);
        textFont.setWeight(QFont::DemiBold);
        break;
    }
    case ElaTextType::Subtitle:
    {
        textFont.setPixelSize(20);
        textFont.setWeight(QFont::DemiBold);
        break;
    }
    case ElaTextType::Title:
    {
        textFont.setPixelSize(28);
        textFont.setWeight(QFont::DemiBold);
        break;
    }
    case ElaTextType::TitleLarge:
    {
        textFont.setPixelSize(40);
        textFont.setWeight(QFont::DemiBold);
        break;
    }
    case ElaTextType::Display:
    {
        textFont.setPixelSize(48);
        textFont.setWeight(QFont::DemiBold);
        break;
    }
    }
    setFont(textFont);
}

ElaTextType::TextStyle ElaText::getTextStyle() const
{
    Q_D(const ElaText);
    return d->_pTextStyle;
}

void ElaText::setElaIcon(ElaIconType::IconName elaIcon)
{
    Q_D(ElaText);
    d->_pElaIcon = elaIcon;
    update();
    Q_EMIT pElaIconChanged();
}

ElaIconType::IconName ElaText::getElaIcon() const
{
    Q_D(const ElaText);
    return d->_pElaIcon;
}

void ElaText::setTextColor( QColor TextColor )
{
    Q_D(ElaText);
    d->_pTextColor = TextColor;
}

QColor ElaText::getTextColor() const
{
    Q_D(const ElaText);
    return d->_pTextColor;
}

void ElaText::paintEvent(QPaintEvent* event)
{
    Q_D(ElaText);
    if (d->_pElaIcon != ElaIconType::None)
    {
        QPainter painter(this);
        painter.save();
        painter.setRenderHints(QPainter::SmoothPixmapTransform | QPainter::Antialiasing | QPainter::TextAntialiasing);
        QFont iconFont = QFont("ElaAwesome");
        iconFont.setPixelSize(this->font().pixelSize());
        painter.setFont(iconFont);
        if( d->_pTextColor.isValid() == true )
            painter.setPen( d->_pTextColor );
        else
            painter.setPen(ElaThemeColor(d->_themeMode, BasicText));
        painter.drawText(rect(), Qt::AlignCenter, QChar((unsigned short)d->_pElaIcon));
        painter.restore();
    }
    else
    {
        if (wordWrap() && d->_isWrapAnywhere)
        {
            QPainter painter(this);
            painter.save();
            painter.setRenderHints(QPainter::Antialiasing | QPainter::TextAntialiasing);
            if( d->_pTextColor.isValid() == true )
                painter.setPen( d->_pTextColor );
            else
                painter.setPen(ElaThemeColor(d->_themeMode, BasicText));
            painter.drawText(rect(), Qt::AlignLeft | Qt::AlignVCenter | Qt::TextWordWrap | Qt::TextWrapAnywhere, text());
            painter.restore();
        }
        else
        {
            QLabel::paintEvent(event);
        }
    }
}
