#ifndef ELAAPPBAR_H
#define ELAAPPBAR_H

#include <QLabel>
#include <QWidget>

#include "Def.h"
#include "stdafx.h"

#ifdef Q_OS_WIN
#if QT_VERSION >= QT_VERSION_CHECK(6, 0, 0)
#define Q_TAKEOVER_NATIVEEVENT_H virtual bool nativeEvent(const QByteArray& eventType, void* message, qintptr* result) override;
#else
#define Q_TAKEOVER_NATIVEEVENT_H virtual bool nativeEvent(const QByteArray& eventType, void* message, long* result) override;
#endif
#else
#define Q_TAKEOVER_NATIVEEVENT_H
#endif

#ifdef Q_OS_WIN
#define ELAAPPBAR_HANDLE(ElaAppBar)                                           \
    if (ElaAppBar)                                                            \
    {                                                                         \
        int ret = ElaAppBar->takeOverNativeEvent(eventType, message, result); \
        if (ret == -1)                                                        \
        {                                                                     \
            return QWidget::nativeEvent(eventType, message, result);          \
        }                                                                     \
        return (bool)ret;                                                     \
    }                                                                         \
    return QWidget::nativeEvent(eventType, message, result);
#endif

#ifdef Q_OS_WIN
#if QT_VERSION >= QT_VERSION_CHECK(6, 0, 0)
#define Q_TAKEOVER_NATIVEEVENT_CPP(CLASS, ElaAppBar)                                     \
    bool CLASS::nativeEvent(const QByteArray& eventType, void* message, qintptr* result) \
    {                                                                                    \
        ELAAPPBAR_HANDLE(ElaAppBar)                                                      \
    }
#else
#define Q_TAKEOVER_NATIVEEVENT_CPP(CLASS, ElaAppBar)                                  \
    bool CLASS::nativeEvent(const QByteArray& eventType, void* message, long* result) \
    {                                                                                 \
        ELAAPPBAR_HANDLE(ElaAppBar)                                                   \
    }
#endif
#else
#define Q_TAKEOVER_NATIVEEVENT_CPP(CLASS, ElaAppBar)
#endif

class ElaText;
class ElaAppBarPrivate;
class ELA_EXPORT ElaAppBar : public QWidget
{
    Q_OBJECT
    Q_Q_CREATE(ElaAppBar)
    Q_PROPERTY_CREATE_Q_H(bool, IsStayTop)
    Q_PROPERTY_CREATE_Q_H(bool, IsFixedHorizontalSize)
    Q_PROPERTY_CREATE_Q_H(bool, IsFixedVerticalSize)
    Q_PROPERTY_CREATE_Q_H(bool, IsDefaultMin)
    Q_PROPERTY_CREATE_Q_H(bool, IsDefaultMax)
    Q_PROPERTY_CREATE_Q_H(bool, IsDefaultClosed)
    Q_PROPERTY_CREATE_Q_H(bool, IsOnlyAllowMinAndClose)
    Q_PROPERTY_CREATE_Q_H(int, AppBarHeight)
    Q_PROPERTY_CREATE_Q_H(int, CustomWidgetMaximumWidth)
    Q_PROPERTY_CREATE_Q_H(QSize, IconSize)
public:
    explicit ElaAppBar(QWidget* parent = nullptr);
    ~ElaAppBar() override;

    void setCustomWidget(ElaAppBarType::CustomArea customArea, QWidget* customWidget);
    QWidget* getCustomWidget() const;

    void setCustomMenu(QMenu* customMenu);
    QMenu* getCustomMenu() const;

    void setWindowButtonFlag(ElaAppBarType::ButtonType buttonFlag, bool isEnable = true);
    void setWindowButtonFlags(ElaAppBarType::ButtonFlags buttonFlags);
    ElaAppBarType::ButtonFlags getWindowButtonFlags() const;

    QLabel *    iconLabel() const;
    ElaText*    titleLabel() const;

    void setRouteBackButtonEnable(bool isEnable);

    void closeWindow();
#ifdef Q_OS_WIN
#if QT_VERSION >= QT_VERSION_CHECK(6, 0, 0)
    int takeOverNativeEvent(const QByteArray& eventType, void* message, qintptr* result);
#else
    int takeOverNativeEvent(const QByteArray& eventType, void* message, long* result);
#endif
#endif
Q_SIGNALS:
    Q_SIGNAL void routeBackButtonClicked();
    Q_SIGNAL void navigationButtonClicked();
    Q_SIGNAL void themeChangeButtonClicked();
    Q_SIGNAL void minButtonClicked();
    Q_SIGNAL void maxButtonClicked();
    Q_SIGNAL void closeButtonClicked();
    Q_SIGNAL void customWidgetChanged();
    Q_SIGNAL void customMenuChanged();
    Q_SIGNAL void languageChanged();
protected:
    bool eventFilter(QObject* obj, QEvent* event) override;
    void changeEvent(QEvent* event) override;
    virtual void doChangeUILanguage() {};
};

#endif // ELAAPPBAR_H
