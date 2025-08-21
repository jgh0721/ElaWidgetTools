#ifndef ELATOGGLEBUTTON_H
#define ELATOGGLEBUTTON_H

#include <QPushButton>
#include <QColor>

#include "ElaProperty.h"
class ElaToggleButtonPrivate;
class ELA_EXPORT ElaToggleButton : public QWidget
{
    Q_OBJECT
    Q_Q_CREATE(ElaToggleButton)
    Q_PROPERTY_CREATE_Q_H(int, BorderRadius)
    Q_PROPERTY_CREATE_Q_H(QString, Text)
    Q_PROPERTY_CREATE_Q_H(QColor, TextColor)
    Q_PROPERTY_CREATE_Q_H(QColor, TextSelectedColor)
    Q_PROPERTY_CREATE_Q_H(QColor, TextDisabledColor)

    Q_PROPERTY_CREATE_Q_H(QColor, BackgroundColor)
    Q_PROPERTY_CREATE_Q_H(QColor, BackgroundPressedColor)
    Q_PROPERTY_CREATE_Q_H(QColor, BackgroundHighlightedColor)
    Q_PROPERTY_CREATE_Q_H(QColor, BackgroundDisabledColor)

    Q_PROPERTY_CREATE_Q_H(QColor, SelectedBackgroundColor)
    Q_PROPERTY_CREATE_Q_H(QColor, SelectedBackgroundPressedColor)
    Q_PROPERTY_CREATE_Q_H(QColor, SelectedBackgroundHighlightedColor)
    Q_PROPERTY_CREATE_Q_H(QColor, SelectedBackgroundDisabledColor)

public:
    explicit ElaToggleButton(QWidget* parent = nullptr);
    explicit ElaToggleButton(QString text, QWidget* parent = nullptr);
    ~ElaToggleButton();

    void setIsToggled(bool isToggled);
    bool getIsToggled() const;
Q_SIGNALS:
    Q_SIGNAL void toggled(bool checked);

protected:
    virtual bool event(QEvent* event) override;
    virtual void mousePressEvent(QMouseEvent* event) override;
    virtual void mouseReleaseEvent(QMouseEvent* event) override;
    virtual void paintEvent(QPaintEvent* event) override;

private:
    QColor retrieveTextColor();
    QColor retrieveBackgroundColor();

};

#endif // ELATOGGLEBUTTON_H
