#ifndef ELAFOOTERMODEL_H
#define ELAFOOTERMODEL_H

#include <QAbstractListModel>
#include <QHash>
#include <QIcon>

#include "ElaDef.h"
class ElaNavigationNode;
class ElaFooterModel : public QAbstractListModel
{
    Q_OBJECT
    Q_PRIVATE_CREATE(ElaNavigationNode*, SelectedNode)
public:
    explicit ElaFooterModel(QObject* parent = nullptr);
    ~ElaFooterModel();
    ElaNavigationType::NodeResult addFooterNode(QString footerTitle, QString& footerKey, bool isHasFooterPage, int keyPoints = 0, ElaIconType::IconName awesome = ElaIconType::None);
    int getFooterNodeCount() const;
    ElaNavigationNode* getNavigationNode(QString footerKey);
    void removeNavigationNode(QString footerKey);
    void setFooterNodeIcon( const QString& footerKey, const QIcon& icon );

protected:
    int rowCount(const QModelIndex& parent = QModelIndex()) const override;
    QVariant data(const QModelIndex& index, int role) const override;

private:
    QList<ElaNavigationNode*> _footerNodeList;
    QHash<QString, QIcon> _footerIconMap;
};

#endif // ELAFOOTERMODEL_H
