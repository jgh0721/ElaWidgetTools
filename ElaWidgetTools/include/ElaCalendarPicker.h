#ifndef ELACALENDARPICKER_H
#define ELACALENDARPICKER_H

#include <QPushButton>

#include "stdafx.h"
class ElaCalendarPickerPrivate;
class ELA_EXPORT ElaCalendarPicker : public QPushButton
{
    Q_OBJECT
    Q_Q_CREATE(ElaCalendarPicker)
    Q_PROPERTY_CREATE_Q_H(int, BorderRadius)
    Q_PROPERTY_CREATE_Q_H(QDate, SelectedDate)
    Q_PROPERTY_CREATE_Q_H(QDate, MinimumDate)
    Q_PROPERTY_CREATE_Q_H(QDate, MaximumDate)
    Q_PROPERTY_CREATE_Q_H(QString, DateFormat)
public:
    explicit ElaCalendarPicker(QWidget* parent = nullptr);
    ~ElaCalendarPicker();

Q_SIGNALS:
    Q_SIGNAL void selectedDateChanged(QDate date);

protected:
    virtual void paintEvent(QPaintEvent* event) override;
};

#endif // ELACALENDARPICKER_H
