#include "ElaCheckBox.h"

#include "ElaCheckBoxStyle.h"
ElaCheckBox::ElaCheckBox(QWidget* parent)
    : QCheckBox(parent)
{
    _pBorderRadius = 3;
    setMouseTracking(true);
    setObjectName("ElaCheckBox");
    setStyle(new ElaCheckBoxStyle(style()));
    QFont font = this->font();
    font.setPixelSize(15);
    setFont(font);
}

ElaCheckBox::ElaCheckBox(const QString& text, QWidget* parent)
    : ElaCheckBox(parent)
{
    setText(text);
}

ElaCheckBox::~ElaCheckBox()
{
}

void ElaCheckBox::setLightTextColor(QColor color)
{
    const auto Style = qobject_cast<ElaCheckBoxStyle*>(style());
    Q_ASSERT(Style != nullptr);
    Style->setLightTextColor(color);
    Q_EMIT pLightTextColorChanged();
}

QColor ElaCheckBox::getLightTextColor() const
{
    const auto Style = qobject_cast<ElaCheckBoxStyle*>(style());
    Q_ASSERT(Style != nullptr);
    return Style->getLightTextColor();
}

void ElaCheckBox::setDarkTextColor(QColor color)
{
    const auto Style = qobject_cast<ElaCheckBoxStyle*>(style());
    Q_ASSERT(Style != nullptr);
    Style->setDarkTextColor(color);
    Q_EMIT pDarkTextColorChanged();
}

QColor ElaCheckBox::getDarkTextColor() const
{
    const auto Style = qobject_cast<ElaCheckBoxStyle*>(style());
    Q_ASSERT(Style != nullptr);
    return Style->getDarkTextColor();
}
