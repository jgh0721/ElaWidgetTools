#ifndef ELAFRAME_H
#define ELAFRAME_H

#include <QWidget>
#include <QtWidgets/qframe.h>

#include "Def.h"

class ElaFramePrivate;
class ELA_EXPORT ElaFrame : public QFrame
{
    Q_OBJECT
    Q_Q_CREATE(ElaFrame)
public:
    explicit ElaFrame( QWidget* Parent = 0 );
    ~ElaFrame() override;
protected:
    void paintEvent( QPaintEvent* event ) override;
};

#endif
