#include "ElaPlainTextEditPrivate.h"
#include "ElaApplication.h"
#include "ElaPlainTextEdit.h"
#include <QTimer>
ElaPlainTextEditPrivate::ElaPlainTextEditPrivate(QObject* parent)
    : QObject{parent}
{
}

ElaPlainTextEditPrivate::~ElaPlainTextEditPrivate()
{
}

void ElaPlainTextEditPrivate::onWMWindowClickedEvent(QVariantMap data)
{
    Q_Q(ElaPlainTextEdit);
    ElaAppBarType::WMMouseActionType actionType = data.value("WMClickType").value<ElaAppBarType::WMMouseActionType>();
    if (actionType == ElaAppBarType::WMLBUTTONDOWN)
    {
        if (!q->toPlainText().isEmpty() && q->hasFocus())
        {
            q->clearFocus();
        }
    }
    else if (actionType == ElaAppBarType::WMLBUTTONUP || actionType == ElaAppBarType::WMNCLBUTTONDOWN)
    {
        if (ElaApplication::containsCursorToItem(q) || (actionType == ElaAppBarType::WMLBUTTONUP && !q->toPlainText().isEmpty()))
        {
            return;
        }
        if (q->hasFocus())
        {
            q->clearFocus();
        }
    }
}

void ElaPlainTextEditPrivate::onThemeChanged(ElaThemeType::ThemeMode themeMode)
{
    Q_Q(ElaPlainTextEdit);
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

void ElaPlainTextEditPrivate::_changeTheme()
{
    Q_Q(ElaPlainTextEdit);
    if (_themeMode == ElaThemeType::Light)
    {
        QPalette palette;
        if( _pTextColor.isValid() == false )
            palette.setColor(QPalette::Text, Qt::black);
        else
            palette.setColor(QPalette::Text, _pTextColor);
        if( _pPlaceHolderTextColor.isValid() == false )
            palette.setColor(QPalette::PlaceholderText, QColor(0x00, 0x00, 0x00, 128));
        else
            palette.setColor(QPalette::PlaceholderText, _pPlaceHolderTextColor);
        q->setPalette(palette);
    }
    else
    {
        QPalette palette;
        if( _pTextColor.isValid() == false )
            palette.setColor(QPalette::Text, Qt::white);
        else
            palette.setColor(QPalette::Text, _pTextColor);
        if( _pPlaceHolderTextColor.isValid() == false )
            palette.setColor(QPalette::PlaceholderText, QColor(0xBA, 0xBA, 0xBA));
        else
            palette.setColor(QPalette::PlaceholderText, _pPlaceHolderTextColor);
        q->setPalette(palette);
    }
}
