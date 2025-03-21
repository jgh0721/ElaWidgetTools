#ifndef ELALISTWIDGET_H
#define ELALISTWIDGET_H

#include <QListWidget>

#include "stdafx.h"

class ElaListWidgetPrivate;

class ELA_EXPORT ElaListWidget : public QListWidget
{
    Q_OBJECT
    Q_Q_CREATE(ElaListWidget)
    Q_PROPERTY_CREATE_Q_H(int, ItemHeight)
    Q_PROPERTY_CREATE_Q_H(bool, IsTransparent)
public:
    explicit ElaListWidget(QWidget* parent = nullptr);
    ~ElaListWidget() override;
};
 
#endif // ELALISTVIEW_H
