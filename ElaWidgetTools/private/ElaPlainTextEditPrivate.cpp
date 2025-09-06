#include "ElaPlainTextEditPrivate.h"
#include "ElaApplication.h"
#include "ElaPlainTextEdit.h"
#include "ElaTheme.h"
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
    QPalette palette = q->palette();
    if (_themeMode == ElaThemeType::Light)
    {
        if( _pTextColor.isValid() == false )
            palette.setColor(QPalette::Text, ElaThemeColor(_themeMode, BasicText));
        else
            palette.setColor(QPalette::Text, _pTextColor);
        if( _pPlaceHolderTextColor.isValid() == false )
            palette.setColor(QPalette::PlaceholderText, QColor(0x00, 0x00, 0x00, 128));
        else
            palette.setColor(QPalette::PlaceholderText, _pPlaceHolderTextColor);
    }
    else
    {
        if( _pTextColor.isValid() == false )
            palette.setColor(QPalette::Text, ElaThemeColor(_themeMode, BasicText));
        else
            palette.setColor(QPalette::Text, _pTextColor);
        if( _pPlaceHolderTextColor.isValid() == false )
            palette.setColor(QPalette::PlaceholderText, QColor(0xBA, 0xBA, 0xBA));
        else
            palette.setColor(QPalette::PlaceholderText, _pPlaceHolderTextColor);
    }
    q->setPalette(palette);
}
