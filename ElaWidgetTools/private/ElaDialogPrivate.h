#ifndef ELADIALOGPRIVATE_H
#define ELADIALOGPRIVATE_H

#include <QObject>

#include "Def.h"
#include "stdafx.h"

class ElaAppBar;
class ElaDialog;
class ElaDialogPrivate : public QObject
{
    Q_OBJECT
    Q_D_CREATE(ElaDialog);
public:
    explicit ElaDialogPrivate(QObject* parent = nullptr);
    ~ElaDialogPrivate() override;

private:
    ElaThemeType::ThemeMode                 _themeMode;
    ElaApplicationType::WindowDisplayMode   _windowDisplayMode;
    ElaAppBar*                              _appBar{nullptr};
};

#endif // ELADIALOGPRIVATE_H