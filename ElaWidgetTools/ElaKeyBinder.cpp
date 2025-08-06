#include "ElaKeyBinder.h"
#include "ElaContentDialog.h"
#include "ElaKeyBinderContainer.h"
#include "ElaKeyBinderPrivate.h"
#include "ElaTheme.h"
#include <QMouseEvent>
#include <QPainter>
#include <utility>

#include "ElaPushButton.h"
Q_PROPERTY_CREATE_Q_CPP( ElaKeyBinder, int, BorderRadius )

ElaKeyBinder::ElaKeyBinder(QWidget* parent)
    : QLabel(parent), d_ptr(new ElaKeyBinderPrivate())
{
    Q_D(ElaKeyBinder);
    d->q_ptr = this;
    d->_pBorderRadius = 5;
    _pNotSetText = tr("  按键: ") + tr("未绑定") + "      ";
    _pSetText = tr("  按键: ");
    setFixedHeight(35);
    setMouseTracking(true);
    setStyleSheet("#ElaKeyBinder{background-color:transparent;}");
    QFont textFont = font();
    textFont.setLetterSpacing(QFont::AbsoluteSpacing, 0.5);
    textFont.setPixelSize(15);
    setFont(textFont);
    d->_binderContainer = new ElaKeyBinderContainer(this);
    d->_binderDialog = new ElaContentDialog(window());
    d->_binderDialog->setCentralWidget(d->_binderContainer);
    d->_binderDialog->setLeftButtonText(tr("取消"));
    d->_binderDialog->setMiddleButtonText(tr("重置"));
    d->_binderDialog->setRightButtonText(tr("确认"));
    connect(d->_binderDialog, &ElaContentDialog::middleButtonClicked, this, [=]() {
        d->_binderContainer->logOrResetHistoryData(false);
    });
    connect(d->_binderDialog, &ElaContentDialog::rightButtonClicked, this, [=]() {
        d->_binderContainer->saveBinderChanged();
        setKeySequenceText( d->_binderContainer->getBinderKeyText() );
    });
    d->onThemeChanged(eTheme->getThemeMode());
    connect(eTheme, &ElaTheme::themeModeChanged, d, &ElaKeyBinderPrivate::onThemeChanged);

    setKeySequenceText( "" );
}

ElaKeyBinder::~ElaKeyBinder()
{
}

void ElaKeyBinder::setSetText( QString SetText )
{
    Q_D(const ElaKeyBinder);
    _pSetText = SetText;
    if( d->_binderContainer )
        setKeySequenceText( d->_binderContainer->getBinderKeyText() );
}

QString ElaKeyBinder::getSetText() const
{
    return _pSetText;
}

void ElaKeyBinder::setNotSetText( QString NotSetText )
{
    Q_D(const ElaKeyBinder);
    _pNotSetText = NotSetText;
    if( d->_binderContainer )
        setKeySequenceText( d->_binderContainer->getBinderKeyText() );
}

QString ElaKeyBinder::getNotSetText() const
{
    return _pNotSetText;
}

void ElaKeyBinder::setBinderCaption( QString BinderCaption )
{
    Q_D( ElaKeyBinder );
    d->setCaption( BinderCaption );
    pBinderCaptionChanged();
}

QString ElaKeyBinder::getBinderCaption() const
{
    Q_D( const ElaKeyBinder );
    return d->_pBinderCaption;
}

ElaContentDialog* ElaKeyBinder::contentDialog() const
{
    Q_D( const ElaKeyBinder );
    return d->_binderDialog;
}

void ElaKeyBinder::setBinderKeyText(QString binderKeyText)
{
    Q_D(ElaKeyBinder);
    d->_binderContainer->setBinderKeyText(binderKeyText);
    setKeySequenceText( binderKeyText );
}

QString ElaKeyBinder::getBinderKeyText() const
{
    Q_D(const ElaKeyBinder);
    return d->_binderContainer->getBinderKeyText();
}

void ElaKeyBinder::setNativeVirtualBinderKey(quint32 binderKey)
{
    Q_D(ElaKeyBinder);
    d->_binderContainer->setNativeVirtualBinderKey(binderKey);
}

quint32 ElaKeyBinder::getNativeVirtualBinderKey() const
{
    Q_D(const ElaKeyBinder);
    return d->_binderContainer->getNativeVirtualBinderKey();
}

bool ElaKeyBinder::event(QEvent* event)
{
    switch (event->type())
    {
    case QEvent::Enter:
    case QEvent::Leave:
    {
        update();
        break;
    }
    default:
    {
        break;
    }
    }
    return QLabel::event(event);
}

void ElaKeyBinder::mouseReleaseEvent(QMouseEvent* event)
{
    Q_D(ElaKeyBinder);
    if (event->button() == Qt::LeftButton)
    {
        d->_binderDialog->show();
        d->_binderContainer->setFocus();
        d->_binderContainer->logOrResetHistoryData(true);
    }
    QLabel::mouseReleaseEvent(event);
}

void ElaKeyBinder::paintEvent(QPaintEvent* event)
{
    Q_D(ElaKeyBinder);
    QPainter painter(this);
    painter.save();
    painter.setRenderHints(QPainter::Antialiasing | QPainter::TextAntialiasing);
    painter.setPen(ElaThemeColor(d->_themeMode, BasicBorder));
    painter.setBrush(underMouse() ? ElaThemeColor(d->_themeMode, BasicHover) : Qt::transparent);
    QRect borderRect = rect();
    borderRect.adjust(1, 1, -1, -1);
    painter.drawRoundedRect(borderRect, d->_pBorderRadius, d->_pBorderRadius);
    // 图标绘制
    QFont iconFont = QFont("ElaAwesome");
    iconFont.setPixelSize(16);
    painter.setFont(iconFont);
    painter.setPen(ElaThemeColor(d->_themeMode, BasicText));
    QRect iconRect = rect();
    iconRect.adjust(0, 0, -10, 0);
    painter.drawText(iconRect, Qt::AlignVCenter | Qt::AlignRight, QChar((unsigned short)ElaIconType::Pencil));
    painter.restore();
    QLabel::paintEvent(event);
}

void ElaKeyBinder::setKeySequenceText( const QString& Text )
{
    if( Text.isEmpty() == true )
        setText( _pNotSetText );
    else
        setText( _pSetText + Text +  "      ");
}
