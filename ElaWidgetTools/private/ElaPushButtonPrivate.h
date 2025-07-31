#ifndef ELAPUSHBUTTONPRIVATE_H
#define ELAPUSHBUTTONPRIVATE_H

#include <QColor>
#include <QObject>

#include "Def.h"
#include "stdafx.h"
class ElaPushButton;
class ElaPushButtonPrivate : public QObject
{
    Q_OBJECT
    Q_D_CREATE(ElaPushButton)
    Q_PROPERTY_CREATE_D(int, BorderRadius)
    Q_PROPERTY_CREATE_D(QColor, LightDefaultColor)
    Q_PROPERTY_CREATE_D(QColor, DarkDefaultColor)
    Q_PROPERTY_CREATE_D(QColor, LightAlternateColor)
    Q_PROPERTY_CREATE_D(QColor, DarkAlternateColor)
    Q_PROPERTY_CREATE_D(QColor, LightHoverColor)
    Q_PROPERTY_CREATE_D(QColor, DarkHoverColor)
    Q_PROPERTY_CREATE_D(QColor, LightPressColor)
    Q_PROPERTY_CREATE_D(QColor, DarkPressColor)
    Q_PROPERTY_CREATE_D(QColor, LightTextColor)
    Q_PROPERTY_CREATE_D(QColor, DarkTextColor)
public:
    explicit ElaPushButtonPrivate(QObject* parent = nullptr);
    ~ElaPushButtonPrivate();

private:
    bool _isPressed{false};
    int _shadowBorderWidth{3};
    ElaThemeType::ThemeMode _themeMode;
};

#endif // ELAPUSHBUTTONPRIVATE_H
