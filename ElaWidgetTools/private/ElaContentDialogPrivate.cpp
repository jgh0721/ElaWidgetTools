#include "ElaContentDialogPrivate.h"

#include "ElaContentDialog.h"
#include "ElaMaskWidget.h"
ElaContentDialogPrivate::ElaContentDialogPrivate(QObject* parent)
    : QObject{parent}
{
}

ElaContentDialogPrivate::~ElaContentDialogPrivate()
{
}

void ElaContentDialogPrivate::_doCloseAnimation(bool isAccept)
{
    Q_Q(ElaContentDialog);
    if( _maskWidget != nullptr )
        _maskWidget->doMaskAnimation(0);
    isAccept ? q->accept() : q->reject();
}
