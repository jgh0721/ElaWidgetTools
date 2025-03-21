#ifndef ELALISTVIEWPRIVATE_H
#define ELALISTVIEWPRIVATE_H

#include <QObject>

#include "stdafx.h"

class ElaListView;
class ElaListWidget;
class ElaListViewStyle;
class ElaListViewPrivate : public QObject
{
    Q_OBJECT
    Q_D_CREATE(ElaListView)
public:
    explicit ElaListViewPrivate(QObject* parent = nullptr);
    ~ElaListViewPrivate();

private:
    ElaListViewStyle* _listViewStyle{nullptr};
};

class ElaListWidgetPrivate : public QObject
{
    Q_OBJECT
    Q_D_CREATE(ElaListWidget)
public:
    explicit ElaListWidgetPrivate(QObject* parent = nullptr);
    ~ElaListWidgetPrivate() override;

private:
    ElaListViewStyle* _listViewStyle{nullptr};
};


#endif // ELALISTVIEWPRIVATE_H
