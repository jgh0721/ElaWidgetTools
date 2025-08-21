#ifndef ELAPUSHBUTTON_H
#define ELAPUSHBUTTON_H

#include <QPushButton>

#include "ElaProperty.h"
class ElaPushButtonPrivate;
class ELA_EXPORT ElaPushButton : public QPushButton
{
    Q_OBJECT
    Q_Q_CREATE(ElaPushButton)
    Q_PROPERTY_CREATE_Q_H(int, BorderRadius)
    Q_PROPERTY_CREATE_Q_H(QColor, LightDefaultColor)
    Q_PROPERTY_CREATE_Q_H(QColor, DarkDefaultColor)
    Q_PROPERTY_CREATE_Q_H(QColor, LightAlternateColor)
    Q_PROPERTY_CREATE_Q_H(QColor, DarkAlternateColor)
    Q_PROPERTY_CREATE_Q_H(QColor, LightHoverColor)
    Q_PROPERTY_CREATE_Q_H(QColor, DarkHoverColor)
    Q_PROPERTY_CREATE_Q_H(QColor, LightPressColor)
    Q_PROPERTY_CREATE_Q_H(QColor, DarkPressColor)
    Q_PROPERTY_CREATE_Q_H(QColor, LightTextColor)
    Q_PROPERTY_CREATE_Q_H(QColor, DarkTextColor)
    Q_PROPERTY_CREATE_Q_H(QColor, LightDisabledTextColor)
    Q_PROPERTY_CREATE_Q_H(QColor, DarkDisabledTextColor)
    Q_PROPERTY_CREATE_Q_H(QColor, LightDisabledColor)
    Q_PROPERTY_CREATE_Q_H(QColor, DarkDisabledColor)
    Q_PROPERTY_CREATE_Q_H(bool, NoEffectButton)
public:
    explicit ElaPushButton(QWidget* parent = nullptr);
    explicit ElaPushButton(QString text, QWidget* parent = nullptr);
    ~ElaPushButton();

protected:
    virtual void mousePressEvent(QMouseEvent* event) override;
    virtual void mouseReleaseEvent(QMouseEvent* event) override;
    virtual void paintEvent(QPaintEvent* event) override;

private:
    QColor retrieveTextColor() const;
    QColor retrieveBackgroundColor() const;
};

#endif // ELAPUSHBUTTON_H
