﻿#ifndef ELACONTENTDIALOG_H
#define ELACONTENTDIALOG_H
#include <QAbstractNativeEventFilter>
#include <QDialog>

#include "stdafx.h"

class ElaPushButton;
class ElaText;
class ElaContentDialogPrivate;
class ELA_EXPORT ElaContentDialog : public QDialog
{
    Q_OBJECT
    Q_Q_CREATE(ElaContentDialog)
public:
    explicit ElaContentDialog(QWidget* parent = nullptr);
    ~ElaContentDialog() override;
    Q_SLOT virtual void onLeftButtonClicked();
    Q_SLOT virtual void onMiddleButtonClicked();
    Q_SLOT virtual void onRightButtonClicked();
    void setCentralWidget(QWidget* centralWidget);

    ElaText* getDefaultTitle();
    ElaText* getDefaultSubTitle();

    ElaPushButton* getLeftButton();
    ElaPushButton* getMiddleButton();
    ElaPushButton* getRightButton();

    void setLeftButtonText(QString text);
    void setMiddleButtonText(QString text);
    void setRightButtonText(QString text);

    void close();
Q_SIGNALS:
    Q_SIGNAL void leftButtonClicked( bool* isClose = nullptr );
    Q_SIGNAL void middleButtonClicked( bool* isClose = nullptr );
    Q_SIGNAL void rightButtonClicked( bool* isClose = nullptr );

protected:
    virtual void showEvent(QShowEvent* event) override;
    virtual void paintEvent(QPaintEvent* event) override;
    virtual void keyPressEvent(QKeyEvent* event) override;
#ifdef Q_OS_WIN
#if QT_VERSION >= QT_VERSION_CHECK(6, 0, 0)
    virtual bool nativeEvent(const QByteArray& eventType, void* message, qintptr* result) override;
#else
    virtual bool nativeEvent(const QByteArray& eventType, void* message, long* result) override;
#endif
#endif
};

#endif // ELACONTENTDIALOG_H
