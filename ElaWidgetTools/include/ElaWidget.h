#ifndef ELAWIDGET_H
#define ELAWIDGET_H

#include <QPointer>
#include <qeventloop.h>
#include <QWidget>

#include "Def.h"
#include "ElaAppBar.h"
#include "ElaColorDialog.h"
class ElaWidgetPrivate;
class ElaWidgetBasePrivate;
class ELA_EXPORT ElaWidgetBase : public QWidget
{
    Q_OBJECT
    Q_Q_CREATE(ElaWidgetBase)
public:
    explicit ElaWidgetBase( QWidget* parent = nullptr, Qt::WindowFlags f = Qt::WindowFlags() );
    ~ElaWidgetBase() override;

protected:
    virtual void paintEvent( QPaintEvent* event ) override;
};

class ELA_EXPORT ElaWidget : public QWidget
{
    Q_OBJECT
    Q_Q_CREATE(ElaWidget)
    Q_PROPERTY_CREATE_Q_H(bool, IsStayTop)
    Q_PROPERTY_CREATE_Q_H(bool, IsFixedHorizontalSize)
    Q_PROPERTY_CREATE_Q_H(bool, IsFixedVerticalSize)
    Q_PROPERTY_CREATE_Q_H(bool, IsDefaultClosed)
    Q_PROPERTY_CREATE_Q_H(int, AppBarHeight)
    Q_TAKEOVER_NATIVEEVENT_H
public:
    explicit ElaWidget(QWidget* parent = nullptr, Qt::WindowFlags f = Qt::WindowFlags());
    ~ElaWidget() override;
    void moveToCenter();

    ElaAppBar* appBar() const;
    void setWindowButtonFlag(ElaAppBarType::ButtonType buttonFlag, bool isEnable = true);
    void setWindowButtonFlags(ElaAppBarType::ButtonFlags buttonFlags);
    ElaAppBarType::ButtonFlags getWindowButtonFlags() const;

    // 창이 생성되고 일정한 시간이 경과하면 창이 닫히도록 합니다. 설정 값이 <=0 0 이라면 기능을 사용하지 않습니다.
    void                                            SetAutoCloseTimer( int timerSecs );
    // 창이 자동으로 닫힐 때 까지의 설정된 시간( 초단위 )
    // 해당 기능을 사용하지 않는 다면 0 반환
    int                                             GetAutoCloseTimer();
    void                                            ResetAutoCloseTimer();

    Q_INVOKABLE virtual void                        accept();
    Q_INVOKABLE virtual void                        done( int result );
    Q_INVOKABLE virtual int                         exec();
    Q_INVOKABLE virtual void                        reject();
    int                                             result();
    void                                            setResult( int result );
private:
    void                                            closeDialog( int r );
public slots:
    bool                                            Refresh() { return doRefresh(); };
    int                                             ResultCode() const;
    void                                            SetResultCode(QDialog::DialogCode resultCode);
    void                                            CloseUI();
    void                                            ShowUI();
    int                                             ExecUI();
    void                                            HideUI();

Q_SIGNALS:
    Q_SIGNAL void routeBackButtonClicked();
    Q_SIGNAL void navigationButtonClicked();
    Q_SIGNAL void themeChangeButtonClicked();
    Q_SIGNAL void closeButtonClicked();
    Q_SIGNAL void languageChanged();

    // exec 로 실행된 후, accept, done, reject 등이 호출되었을 때 발생한다.
    Q_SIGNAL void accepted();
    Q_SIGNAL void finished(int result);
    Q_SIGNAL void rejected();
protected:
    void showEvent(QShowEvent* event) override;
    bool _isInitUI = false;
    virtual bool doInitUI() { return true; }
    virtual bool doRefresh() { return true; }
    virtual void showEventUI( QShowEvent* event) {};
    int resultCode_ = QDialog::Rejected;
    QPointer<QEventLoop> eventLoop_;
    void changeEvent(QEvent* event) override;
    virtual void doChangeUILanguage() {};
    Q_INVOKABLE void                                slotAutoCloseTimer();
    // true, 또는 false 를 반환하여 타이머가 만료되었을 때 창을 닫을지 결정한다.
    virtual bool                                    doSlotAutoCloseTimer( int& result );
    // 창이 표시된 후 자동으로 닫히는 기능에 대한 타이머
    QTimer*                                         _clsAutoCloseTimer = nullptr;
    // 창이 표시된 후 일정시간 후 자동으로 닫히는지 여부
    bool                                            _isUseAutoCloseTimer = false;
    // 창이 표시된 후 자동으로 닫힐 때 까지의 시간
    int                                             _nAutoCloseIntervalMs = 0;

    void paintEvent(QPaintEvent* event) override;
    void closeEvent(QCloseEvent* event) override;
    void hideEvent(QHideEvent* event) override;
};

#endif // ELAWIDGET_H
