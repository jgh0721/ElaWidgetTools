#ifndef ELATREEVIEWPRIVATE_H
#define ELATREEVIEWPRIVATE_H

#include <QObject>

#include "stdafx.h"

class ElaTreeView;
class ElaTreeWidget;
class ElaTreeViewStyle;
class ElaTreeViewPrivate : public QObject
{
    Q_OBJECT
    Q_D_CREATE(ElaTreeView)
public:
    explicit ElaTreeViewPrivate(QObject* parent = nullptr);
    ~ElaTreeViewPrivate();

private:
    ElaTreeViewStyle* _treeViewStyle{nullptr};
};

class ElaTreeWidgetPrivate : public QObject
{
    Q_OBJECT
    Q_D_CREATE( ElaTreeWidget )
public:
    explicit ElaTreeWidgetPrivate( QObject* parent = nullptr );
    ~ElaTreeWidgetPrivate();

private:
    ElaTreeViewStyle* _treeViewStyle{ nullptr };
};

#endif // ELATREEVIEWPRIVATE_H
