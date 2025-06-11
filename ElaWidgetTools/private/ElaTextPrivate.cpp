#include "ElaTextPrivate.h"

#include "ElaText.h"
#include "ElaTheme.h"
#include <QTimer>

ElaTextPrivate::ElaTextPrivate(QObject* parent)
    : QObject{parent}
{
}

ElaTextPrivate::~ElaTextPrivate()
{
}

void ElaTextPrivate::onThemeChanged(ElaThemeType::ThemeMode themeMode)
{
    Q_Q(ElaText);
    _themeMode = themeMode;
    if (q->isVisible())
    {
        _changeTheme();
    }
    else
    {
        QTimer::singleShot(1, this, [=] {
            _changeTheme();
        });
    }
}

void ElaTextPrivate::_changeTheme()
{
    Q_Q(ElaText);
    QPalette palette = q->palette();
    if( eTheme->getThemeMode() == ElaThemeType::Light )
        palette.setColor( QPalette::WindowText, _pLightTextColor.isValid() ? _pLightTextColor : Qt::black );
    if( eTheme->getThemeMode() == ElaThemeType::Dark )
        palette.setColor( QPalette::WindowText, _pDarkTextColor.isValid() ? _pDarkTextColor : Qt::white );
    q->setPalette(palette);
}
