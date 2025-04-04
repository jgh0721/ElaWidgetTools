#ifndef ELATABLEVIEWPRIVATE_H
#define ELATABLEVIEWPRIVATE_H

#include <QObject>

#include "stdafx.h"

class ElaTableView;
class ElaTableWidget;
class ElaTableViewStyle;
class ElaTableViewPrivate : public QObject
{
    Q_OBJECT
    Q_D_CREATE(ElaTableView)
public:
    explicit ElaTableViewPrivate(QObject* parent = nullptr);
    ~ElaTableViewPrivate();

private:
    ElaTableViewStyle* _tableViewStyle{nullptr};
};

class ElaTableWidgetPrivate : public QObject
{
    Q_OBJECT
    Q_D_CREATE( ElaTableWidget )
public:
    explicit ElaTableWidgetPrivate( QObject* parent = nullptr );
    ~ElaTableWidgetPrivate();

private:
    ElaTableViewStyle* _tableViewStyle{ nullptr };
};

#endif // ELATABLEVIEWPRIVATE_H
