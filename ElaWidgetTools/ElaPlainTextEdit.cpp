#include "ElaPlainTextEdit.h"

#include <QClipboard>
#include <QGuiApplication>
#include <QMimeData>
#include <QPainter>
#include <QPropertyAnimation>

#include "ElaEventBus.h"
#include "ElaMenu.h"
#include "ElaPlainTextEditPrivate.h"
#include "ElaPlainTextEditStyle.h"
#include "ElaScrollBar.h"
#include "ElaTheme.h"
ElaPlainTextEdit::ElaPlainTextEdit(QWidget* parent)
    : QPlainTextEdit(parent), d_ptr(new ElaPlainTextEditPrivate())
{
    Q_D(ElaPlainTextEdit);
    d->q_ptr = this;
    setObjectName("ElaPlainTextEdit");
    setStyleSheet("#ElaPlainTextEdit{background-color:transparent;}");
    setHorizontalScrollBar(new ElaScrollBar(this));
    setVerticalScrollBar(new ElaScrollBar(this));
    setMouseTracking(true);
    // 事件总线
    d->_focusEvent = new ElaEvent("WMWindowClicked", "onWMWindowClickedEvent", d);
    d->_focusEvent->registerAndInit();

    d->_style = new ElaPlainTextEditStyle(style());
    setStyle(d->_style);
    d->onThemeChanged(eTheme->getThemeMode());
    connect(eTheme, &ElaTheme::themeModeChanged, d, &ElaPlainTextEditPrivate::onThemeChanged);
}

ElaPlainTextEdit::ElaPlainTextEdit(const QString& text, QWidget* parent)
    : ElaPlainTextEdit(parent)
{
    setPlainText(text);
}

ElaPlainTextEdit::~ElaPlainTextEdit()
{
}

void ElaPlainTextEdit::setTextColor( QColor TextColor )
{
    Q_D(ElaPlainTextEdit);
    d->_pTextColor = TextColor;
    d->onThemeChanged( eTheme->getThemeMode() );
}

QColor ElaPlainTextEdit::getTextColor() const
{
    Q_D(const ElaPlainTextEdit);
    return d->_pTextColor;
}

void ElaPlainTextEdit::setPlaceHolderTextColor( QColor PlaceHolderTextColor )
{
    Q_D(ElaPlainTextEdit);
    d->_pPlaceHolderTextColor = PlaceHolderTextColor;
    d->onThemeChanged( eTheme->getThemeMode() );
}

QColor ElaPlainTextEdit::getPlaceHolderTextColor() const
{
    Q_D(const ElaPlainTextEdit);
    return d->_pPlaceHolderTextColor;
}

void ElaPlainTextEdit::focusInEvent(QFocusEvent* event)
{
    Q_D(ElaPlainTextEdit);
    if (event->reason() == Qt::MouseFocusReason)
    {
        QPropertyAnimation* markAnimation = new QPropertyAnimation(d->_style, "pExpandMarkWidth");
        connect(markAnimation, &QPropertyAnimation::valueChanged, this, [=](const QVariant& value) {
            update();
        });
        markAnimation->setDuration(300);
        markAnimation->setEasingCurve(QEasingCurve::InOutSine);
        markAnimation->setStartValue(d->_style->getExpandMarkWidth());
        markAnimation->setEndValue(width() / 2 - 3);
        markAnimation->start(QAbstractAnimation::DeleteWhenStopped);
    }
    QPlainTextEdit::focusInEvent(event);
}

void ElaPlainTextEdit::focusOutEvent(QFocusEvent* event)
{
    Q_D(ElaPlainTextEdit);
    if (event->reason() != Qt::PopupFocusReason)
    {
        QPropertyAnimation* markAnimation = new QPropertyAnimation(d->_style, "pExpandMarkWidth");
        connect(markAnimation, &QPropertyAnimation::valueChanged, this, [=](const QVariant& value) {
            update();
        });
        markAnimation->setDuration(300);
        markAnimation->setEasingCurve(QEasingCurve::InOutSine);
        markAnimation->setStartValue(d->_style->getExpandMarkWidth());
        markAnimation->setEndValue(0);
        markAnimation->start(QAbstractAnimation::DeleteWhenStopped);
    }
    QPlainTextEdit::focusOutEvent(event);
}

void ElaPlainTextEdit::contextMenuEvent(QContextMenuEvent* event)
{
    ElaMenu* menu = new ElaMenu(this);
    menu->setMenuItemHeight(27);
    menu->setAttribute(Qt::WA_DeleteOnClose);
    QAction* action = nullptr;
    if (!isReadOnly())
    {
        action = menu->addElaIconAction(ElaIconType::ArrowRotateLeft, tr("撤销"), QKeySequence::Undo);
        action->setEnabled(isUndoRedoEnabled() ? document()->isUndoAvailable() : false);
        connect(action, &QAction::triggered, this, &ElaPlainTextEdit::undo);

        action = menu->addElaIconAction(ElaIconType::ArrowRotateRight, tr("恢复"), QKeySequence::Redo);
        action->setEnabled(isUndoRedoEnabled() ? document()->isRedoAvailable() : false);
        connect(action, &QAction::triggered, this, &ElaPlainTextEdit::redo);
        menu->addSeparator();
    }
#ifndef QT_NO_CLIPBOARD
    if (!isReadOnly())
    {
        action = menu->addElaIconAction(ElaIconType::KnifeKitchen, tr("剪切"), QKeySequence::Cut);
        action->setEnabled(!isReadOnly() && !textCursor().selectedText().isEmpty());
        connect(action, &QAction::triggered, this, &ElaPlainTextEdit::cut);
    }

    action = menu->addElaIconAction(ElaIconType::Copy, tr("复制"), QKeySequence::Copy);
    action->setEnabled(!textCursor().selectedText().isEmpty());
    connect(action, &QAction::triggered, this, &ElaPlainTextEdit::copy);

    if (!isReadOnly())
    {
        action = menu->addElaIconAction(ElaIconType::Paste, tr("粘贴"), QKeySequence::Paste);
        action->setEnabled(!isReadOnly() && !QGuiApplication::clipboard()->text().isEmpty());
        connect(action, &QAction::triggered, this, &ElaPlainTextEdit::paste);
    }
#endif
    if (!isReadOnly())
    {
        action = menu->addElaIconAction(ElaIconType::DeleteLeft, tr("删除"));
        action->setEnabled(!isReadOnly() && !toPlainText().isEmpty() && !textCursor().selectedText().isEmpty());
        connect(action, &QAction::triggered, this, [=](bool checked) {
            if (!textCursor().selectedText().isEmpty())
            {
                textCursor().deleteChar();
            }
        });
    }
    if (!menu->isEmpty())
    {
        menu->addSeparator();
    }
    action = menu->addAction(tr("全选"));
    action->setShortcut(QKeySequence::SelectAll);
    action->setEnabled(!toPlainText().isEmpty() && !(textCursor().selectedText() == toPlainText()));
    connect(action, &QAction::triggered, this, &ElaPlainTextEdit::selectAll);
    menu->popup(event->globalPos());
    this->setFocus();
}
