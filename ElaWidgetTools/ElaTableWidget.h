#ifndef ELATABLEWIDGET_H
#define ELATABLEWIDGET_H

#include <QTableWidget>

#include "ElaProperty.h"

class ElaTableViewPrivate;
class ElaTableWidgetPrivate;
class ElaToolTip;

class ELA_EXPORT ElaTableWidget : public QTableWidget
{
    Q_OBJECT
    Q_Q_CREATE( ElaTableWidget )
    Q_PROPERTY_CREATE_Q_H( int, HeaderMargin )
public:
    explicit ElaTableWidget( QWidget* parent = nullptr );
    ~ElaTableWidget();

    void addTooltipColumn( int column );
    void removeTooltipColumn( int column );

Q_SIGNALS:
    Q_SIGNAL void tableViewShow();
    Q_SIGNAL void tableViewHide();

protected:
    virtual void showEvent( QShowEvent* event ) override;
    virtual void hideEvent( QHideEvent* event ) override;
    virtual void mouseMoveEvent( QMouseEvent* event ) override;
    virtual void leaveEvent( QEvent* event ) override;

private:

    QSet< int > setTooltipColumns;
    ElaToolTip* Tooltip = nullptr;
    QModelIndex TooltipIdx;
};

#endif // ELATABLEVIEW_H
