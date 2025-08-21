#ifndef ELAFRAMEPRIVATE_H
#define ELAFRAMEPRIVATE_H

#include <QObject>

#include "ElaDef.h"

class ElaFrame;
class ElaFramePrivate : public QObject
{
    Q_OBJECT
    Q_D_CREATE( ElaFrame )
public:
    explicit ElaFramePrivate( QObject* parent = nullptr );
    ~ElaFramePrivate() override;

private:
    ElaThemeType::ThemeMode _themeMode;
    ElaApplicationType::WindowDisplayMode _windowDisplayMode;
};

#endif // ELAWIDGETPRIVATE_H
