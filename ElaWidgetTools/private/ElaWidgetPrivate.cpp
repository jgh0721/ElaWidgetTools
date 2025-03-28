#include "ElaWidgetPrivate.h"

#include "ElaWidget.h"

ElaWidgetBasePrivate::ElaWidgetBasePrivate( QObject* parent )
    : QObject{ parent }
{
}

ElaWidgetBasePrivate::~ElaWidgetBasePrivate()
{
}

ElaWidgetPrivate::ElaWidgetPrivate(QObject* parent)
    : QObject{parent}
{
}

ElaWidgetPrivate::~ElaWidgetPrivate()
{
}
