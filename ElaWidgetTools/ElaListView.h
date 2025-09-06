#ifndef ELALISTVIEW_H
#define ELALISTVIEW_H

#include <QListView>

#include "ElaProperty.h"
#include "ElaDef.h"

class ElaListViewPrivate;
class ELA_EXPORT ElaListView : public QListView
{
    Q_OBJECT
    Q_Q_CREATE(ElaListView)
    Q_PROPERTY_CREATE_Q_H(int, ItemHeight)
    Q_PROPERTY_CREATE_Q_H(bool, IsTransparent)
    Q_PROPERTY_CREATE_Q_H(ElaListViewType::ElaIconViewSize, IconViewSize)
public:
    explicit ElaListView(QWidget* parent = nullptr);
    ~ElaListView();

    // 아이콘 크기별 실제 픽셀 크기 반환
    int getIconPixelSize() const;
};

#endif // ELALISTVIEW_H
