#ifndef ELAPIVOTMODEL_H
#define ELAPIVOTMODEL_H

#include <QAbstractListModel>
#include <QStringList>

class ElaPivotModel : public QAbstractListModel
{
    Q_OBJECT
public:
    explicit ElaPivotModel(QObject* parent = nullptr);
    ~ElaPivotModel();

    void appendPivot(QString pivot);
    void removePivot(QString pivot);
    void setPivot( const QStringList& pivots);
    QStringList pivots() const;

    int getPivotListCount() const;

protected:
    int rowCount(const QModelIndex& parent = QModelIndex()) const override;
    QVariant data(const QModelIndex& index, int role) const override;

private:
    QStringList _pivotList;
};

#endif // ELAPIVOTMODEL_H
