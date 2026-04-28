#include "ElaCalendarPickerPrivate.h"

#include <QDate>
#include <QGuiApplication>
#include <QPropertyAnimation>
#include <QScreen>

#include "ElaCalendar.h"
#include "ElaCalendarPicker.h"
#include "ElaCalendarPickerContainer.h"
ElaCalendarPickerPrivate::ElaCalendarPickerPrivate(QObject* parent)
    : QObject{parent}
{
}

ElaCalendarPickerPrivate::~ElaCalendarPickerPrivate()
{
}

void ElaCalendarPickerPrivate::onCalendarPickerClicked()
{
    Q_Q(ElaCalendarPicker);
    QPoint endPoint(q->mapToGlobal(QPoint((q->width() - _calendarPickerContainer->width()) / 2, q->height() + 5)));
    int startYOffset = -10;

    // 현재 위젯이 위치한 스크린의 가용 영역을 확인합니다.
#if QT_VERSION >= QT_VERSION_CHECK(5, 14, 0)
    QScreen* screen = q->screen();
#else
    QScreen* screen = QGuiApplication::screenAt(q->mapToGlobal(QPoint(0, 0)));
#endif
    if (screen)
    {
        // 캘린더 컨테이너가 화면 하단 영역을 벗어나는지 검사
        if (endPoint.y() + _calendarPickerContainer->height() > screen->availableGeometry().bottom())
        {
            // 공간이 부족한 경우 피커 위젯의 상단으로 위치를 재조정합니다.
            endPoint = q->mapToGlobal(QPoint((q->width() - _calendarPickerContainer->width()) / 2, -_calendarPickerContainer->height() - 5));
            startYOffset = 10;
        }
    }

    QPropertyAnimation* showAnimation = new QPropertyAnimation(_calendarPickerContainer, "pos");
    showAnimation->setEasingCurve(QEasingCurve::OutCubic);
    showAnimation->setDuration(250);
    // 나타나는 애니메이션의 시작점 또한 캘린더가 열리는 방향에 맞춰 보정합니다.
    showAnimation->setStartValue(QPoint(endPoint.x(), endPoint.y() + startYOffset));
    showAnimation->setEndValue(endPoint);
    _calendarPickerContainer->show();
    showAnimation->start(QAbstractAnimation::DeleteWhenStopped);
}

void ElaCalendarPickerPrivate::onCalendarSelectedDateChanged()
{
    Q_Q(ElaCalendarPicker);
    Q_EMIT q->selectedDateChanged(_calendar->getSelectedDate());
    if (_calendarPickerContainer->isVisible())
    {
        _calendarPickerContainer->hide();
    }
}
