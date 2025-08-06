#include "ElaKeyBinderPrivate.h"
#include "ElaKeyBinder.h"
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

void ElaKeyBinderPrivate::setCaption( const QString& caption )
{
    _pBinderCaption = caption;
    if( _binderContainer == nullptr ) return;
    _binderContainer->setCaption( caption );
}

void ElaKeyBinderPrivate::_changeTheme()
{
    Q_Q(ElaKeyBinder);
    QPalette palette = q->palette();
    if (_themeMode == ElaThemeType::Light)
    {
        palette.setColor(QPalette::WindowText, Qt::black);
        q->setPalette(palette);
    }
    else
    {
        palette.setColor(QPalette::WindowText, Qt::white);
        q->setPalette(palette);
    }
}
