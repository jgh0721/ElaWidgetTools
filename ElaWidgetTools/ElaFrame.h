#ifndef ELAFRAME_H
#define ELAFRAME_H

#include <QWidget>
#include <QtWidgets/qframe.h>

#include "ElaDef.h"

class ElaFramePrivate;
class ELA_EXPORT ElaFrame : public QFrame
{
    Q_OBJECT
    Q_Q_CREATE(ElaFrame)
    Q_PROPERTY_CREATE_Q_H(QColor, BackgroundColor)
public:
    explicit ElaFrame( QWidget* Parent = 0 );
    ~ElaFrame() override;
protected:
    void paintEvent( QPaintEvent* event ) override;

private:
    QColor m_BackgroundColor;
};

#endif
