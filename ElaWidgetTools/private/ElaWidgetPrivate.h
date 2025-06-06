#ifndef ELAWIDGETPRIVATE_H
#define ELAWIDGETPRIVATE_H

#include <QObject>

#include "Def.h"
class ElaWidget;
class ElaWidgetBase;
class ElaAppBar;
class ElaWidgetBasePrivate : public QObject
{
    Q_OBJECT
    Q_D_CREATE( ElaWidgetBase )
public:
    explicit ElaWidgetBasePrivate( QObject* parent = nullptr );
    ~ElaWidgetBasePrivate() override;

private:
    ElaThemeType::ThemeMode _themeMode;
    ElaApplicationType::WindowDisplayMode _windowDisplayMode;
};

class ElaWidgetPrivate : public QObject
{
    Q_OBJECT
    Q_D_CREATE(ElaWidget)
public:
    explicit ElaWidgetPrivate(QObject* parent = nullptr);
    ~ElaWidgetPrivate() override;

private:
    ElaThemeType::ThemeMode _themeMode;
    ElaApplicationType::WindowDisplayMode _windowDisplayMode;
    ElaAppBar* _appBar{nullptr};
};

#endif // ELAWIDGETPRIVATE_H
