#ifndef ELAWIDGETTOOLS_SRC_ELAKEYBINDER_H_
#define ELAWIDGETTOOLS_SRC_ELAKEYBINDER_H_

#include "ElaDef.h"
#include <QLabel>

class ElaContentDialog;
class ElaKeyBinderPrivate;
class ELA_EXPORT ElaKeyBinder : public QLabel
{
    Q_OBJECT
    Q_Q_CREATE(ElaKeyBinder)
    Q_PROPERTY_CREATE_Q_H(int, BorderRadius)
    Q_PROPERTY_CREATE_Q_H(QString, BinderKeyText)
    Q_PROPERTY_CREATE_Q_H(quint32, NativeVirtualBinderKey)
    Q_PROPERTY_CREATE_Q_H(QString, BinderCaption)
    Q_PROPERTY_CREATE_Q_H(QString, SetText)
    Q_PROPERTY_CREATE_Q_H(QString, NotSetText)
public:
    explicit ElaKeyBinder(QWidget* parent = nullptr);
    ~ElaKeyBinder();

    ElaContentDialog* contentDialog() const;
Q_SIGNALS:
    Q_SIGNAL void binderKeyTextChanged(QString binderKeyText);
    Q_SIGNAL void nativeVirtualBinderKeyChanged(quint32 binderKey);

protected:
    virtual bool event(QEvent* event) override;
    virtual void mouseReleaseEvent(QMouseEvent* event) override;
    virtual void paintEvent(QPaintEvent* event) override;

private:
    void setKeySequenceText( const QString& Text );

    QString _pSetText;
    QString _pNotSetText;
};

#endif//ELAWIDGETTOOLS_SRC_ELAKEYBINDER_H_
