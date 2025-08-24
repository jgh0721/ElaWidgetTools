#ifndef ELAFRAMEWORK_ELADIALOG_H
#define ELAFRAMEWORK_ELADIALOG_H

#include "ElaAppBar.h"
#include "ElaDef.h"
#include <QDialog>
#include <QScopedPointer>

class QTimer;
class ElaDialogPrivate;
class ELA_EXPORT ElaDialog : public QDialog
{
    Q_OBJECT
    Q_Q_CREATE(ElaDialog)
    Q_PROPERTY_CREATE_Q_H(bool, IsStayTop)
    Q_PROPERTY_CREATE_Q_H(bool, IsFixedHorizontalSize)
    Q_PROPERTY_CREATE_Q_H(bool, IsFixedVerticalSize)
    Q_PROPERTY_CREATE_Q_H(bool, IsDefaultClosed)
    Q_PROPERTY_CREATE_Q_H(int, AppBarHeight)
    Q_TAKEOVER_NATIVEEVENT_H
public:
    explicit ElaDialog(QWidget* parent = nullptr, Qt::WindowFlags flags = Qt::Dialog);
    ~ElaDialog() override;

    ElaAppBar*                          appBar() const;
    void                                setWindowButtonFlag(ElaAppBarType::ButtonType buttonFlag, bool isEnable = true);
    void                                setWindowButtonFlags(ElaAppBarType::ButtonFlags buttonFlags);
    ElaAppBarType::ButtonFlags          getWindowButtonFlags() const;
    void                                moveToCenter();

public slots:
    bool                                Refresh() { return doRefresh(); };
    void                                ShowUI();
    int                                 ExecUI();
    void                                HideUI();
    /*!
        창을 닫습니다.

        doCloseUI 를 호출하여 자식 클래스에게 창을 닫기 전 정리 작업의 기회를 제공한다.
    */
    void                                CloseUI();
    int                                 ResultCode() const { return _resultCode; }
    void                                SetResultCode( int result ) { _resultCode = result; }

    // 창이 생성되고 일정한 시간이 경과하면 창이 닫히도록 합니다. 설정 값이 <=0 0 이라면 기능을 사용하지 않습니다.
    void                                SetAutoCloseTimer( int timerSecs );
    // 창이 자동으로 닫힐 때 까지의 설정된 시간( 초단위 )
    // 해당 기능을 사용하지 않는 다면 0 반환
    int                                 GetAutoCloseTimer();
    void                                ResetAutoCloseTimer();

Q_SIGNALS:
    Q_SIGNAL void                       routeBackButtonClicked();
    Q_SIGNAL void                       navigationButtonClicked();
    Q_SIGNAL void                       themeChangeButtonClicked();
    Q_SIGNAL void                       closeButtonClicked();
    Q_SIGNAL void                       languageChanged();

protected slots:
    void                                slotAutoCloseTimer();

protected:
    virtual bool                        doInitUI() { return true;}
    // CloseUI 에 의해 호출되며 자식 클래스에서 UI 를 닫을 때 추가적인 동작을 수행할 수 있는 기회를 제공한다.
    // @return true , 이후 실제로 close 가 호출되어 창이 닫힌다.
    // @return false, 창을 닫기 위한 동작이 실패한 것으로 간주되어 이후 동작을 수행하지 않는다.
    virtual bool                        doCloseUI() { return true; }
    virtual bool                        doRefresh() { return true; }
    virtual bool                        doChangeUILanguage() { return true;}
    // true, 또는 false 를 반환하여 타이머가 만료되었을 때 창을 닫을지 결정한다.
    virtual bool                        doSlotAutoCloseTimer( int& result ) { result = 0; return true; };
    // 파생 클래스는 doShowEventUI 를 오버라이드 하여 사용하며, 부모클래스의 showEvent 는 호출할 필요 없음
    virtual void                        doShowEventUI( QShowEvent* ev ) {};

    void                                showEvent( QShowEvent* event ) override;
    void                                changeEvent(QEvent* event) override;
    void                                paintEvent(QPaintEvent* event) override;
private:

    bool                                _isInitUI = false;

    // 창이 표시된 후 자동으로 닫히는 기능에 대한 타이머
    QTimer*                             _clsAutoCloseTimer{ nullptr };
    // 창이 표시된 후 일정시간 후 자동으로 닫히는지 여부
    bool                                _isUseAutoCloseTimer{false};
    // 창이 표시된 후 자동으로 닫힐 때 까지의 시간
    int                                 _nAutoCloseIntervalMs{0};

    // 창이 닫힐 때 반환할 결과코드 기본값 = 0
    int                                 _resultCode = 0;

};

#endif //ELAFRAMEWORK_ELADIALOG_H
