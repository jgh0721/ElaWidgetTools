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
    QPalette palette = q->palette();
    if( eTheme->getThemeMode() == ElaThemeType::Light )
        palette.setColor( QPalette::WindowText, _pLightTextColor.isValid() ? _pLightTextColor : ElaThemeColor(_themeMode, BasicText) );
    if( eTheme->getThemeMode() == ElaThemeType::Dark )
        palette.setColor( QPalette::WindowText, _pDarkTextColor.isValid() ? _pDarkTextColor : ElaThemeColor(_themeMode, BasicText) );
    q->setPalette(palette);
}
