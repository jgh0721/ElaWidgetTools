#ifndef ELATREEWIDGET_H
#define ELATREEWIDGET_H

#include <QTreeWidget>

#include "ElaProperty.h"

class ElaTreeWidgetPrivate;

class ELA_EXPORT ElaTreeWidget : public QTreeWidget
{
    Q_OBJECT
    Q_Q_CREATE(ElaTreeWidget)
    Q_PROPERTY_CREATE_Q_H(int, ItemHeight)
    Q_PROPERTY_CREATE_Q_H(int, HeaderMargin)
public:
    explicit ElaTreeWidget( QWidget* parent = nullptr );
    ~ElaTreeWidget();
};

#endif //ELATREEWIDGET_H
