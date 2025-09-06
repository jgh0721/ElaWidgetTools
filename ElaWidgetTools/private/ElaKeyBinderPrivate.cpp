#include "ElaKeyBinderPrivate.h"
#include "ElaKeyBinder.h"
#include "ElaTheme.h"

#include <QTimer>

#include "ElaKeyBinderContainer.h"

ElaKeyBinderPrivate::ElaKeyBinderPrivate(QObject* parent)
    : QObject(parent)
{
    _pBinderCaption = tr("按下任意按键以进行绑定");
}

ElaKeyBinderPrivate::~ElaKeyBinderPrivate()
{
}

void ElaKeyBinderPrivate::onThemeChanged(ElaThemeType::ThemeMode themeMode)
{
    Q_Q(ElaKeyBinder);
    _themeMode = themeMode;
    QPalette palette = q->palette();
    palette.setColor(QPalette::WindowText, ElaThemeColor(_themeMode, BasicText));
    q->setPalette(palette);
}

void ElaKeyBinderPrivate::setCaption( const QString& caption )
{
    _pBinderCaption = caption;
    if( _binderContainer == nullptr ) return;
    _binderContainer->setCaption( caption );
}

