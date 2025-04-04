#ifndef ELAFRAMEPRIVATE_H
#define ELAFRAMEPRIVATE_H

#include <QObject>

#include "Def.h"

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
    bool _isEnableMica;
};

#endif // ELAWIDGETPRIVATE_H
