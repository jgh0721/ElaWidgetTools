#ifndef ELATHEMEPRIVATE_H
#define ELATHEMEPRIVATE_H

#include <QColor>
#include <QMap>
#include <QObject>

#include "ElaDef.h"
class ElaTheme;
class ElaThemePrivate : public QObject
{
    Q_OBJECT
    Q_D_CREATE(ElaTheme)
public:
    explicit ElaThemePrivate(QObject* parent = nullptr);
    ~ElaThemePrivate();

private:
    ElaThemeType::ThemeMode _themeMode{ElaThemeType::Light};
    QColor _lightThemeColorList[ElaThemeType::MaxThemeColor + 1];
    QColor _darkThemeColorList[ElaThemeType::MaxThemeColor + 1];
    QString _fontFamily;
    quint32 _fontSizePx;
    void _initThemeColor();
};

#endif // ELATHEMEPRIVATE_H
