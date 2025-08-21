#ifndef ELATEXT_H
#define ELATEXT_H

#include <QLabel>

#include "ElaDef.h"
#include "ElaProperty.h"
class ElaTextPrivate;
class ELA_EXPORT ElaText : public QLabel
{
    Q_OBJECT
    Q_Q_CREATE(ElaText)
    Q_PROPERTY_CREATE_Q_H(bool, IsWrapAnywhere)
    Q_PROPERTY_CREATE_Q_H(int, TextPixelSize)
    Q_PROPERTY_CREATE_Q_H(int, TextPointSize)
    Q_PROPERTY_CREATE_Q_H(ElaTextType::TextStyle, TextStyle)
    Q_PROPERTY_CREATE_Q_H(ElaIconType::IconName, ElaIcon)
    Q_PROPERTY_CREATE_Q_H(QColor, LightTextColor)
    Q_PROPERTY_CREATE_Q_H(QColor, DarkTextColor)
public:
    explicit ElaText(QWidget* parent = nullptr);
    explicit ElaText(QString text, QWidget* parent = nullptr);
    explicit ElaText(QString text, int pixelSize, QWidget* parent = nullptr);
    ~ElaText() override;

protected:
    void paintEvent(QPaintEvent* event) override;

private:
    QColor retrieveTextColor() const;
};

#endif // ELATEXT_H
