#ifndef ELAINTERACTIVECARD_H
#define ELAINTERACTIVECARD_H

#include <QPixmap>
#include <QPushButton>

#include "ElaDef.h"
#include "ElaProperty.h"

class ElaInteractiveCardPrivate;
class ELA_EXPORT ElaInteractiveCard : public QPushButton
{
    Q_OBJECT
    Q_Q_CREATE(ElaInteractiveCard)
    Q_PROPERTY_CREATE_Q_H(int, BorderRadius)
    Q_PROPERTY_CREATE_Q_H(QString, Title);
    Q_PROPERTY_CREATE_Q_H(QString, SubTitle);
    Q_PROPERTY_CREATE_Q_H(int, TitlePixelSize);
    Q_PROPERTY_CREATE_Q_H(int, SubTitlePixelSize);
    Q_PROPERTY_CREATE_Q_H(int, TitleSpacing);
    Q_PROPERTY_CREATE_Q_H(QPixmap, CardPixmap);
    Q_PROPERTY_CREATE_Q_H(QSize, CardPixmapSize);
    Q_PROPERTY_CREATE_Q_H(int, CardPixmapBorderRadius)
    Q_PROPERTY_CREATE_Q_H(ElaCardPixType::PixMode, CardPixMode);
    Q_PROPERTY_CREATE_Q_H(QColor, TitleDarkColor);
    Q_PROPERTY_CREATE_Q_H(QColor, TitleLightColor);
    Q_PROPERTY_CREATE_Q_H(QColor, SubTitleDarkColor);
    Q_PROPERTY_CREATE_Q_H(QColor, SubTitleLightColor);

public:
    explicit ElaInteractiveCard(QWidget* parent = nullptr);
    ~ElaInteractiveCard();
    void setCardPixmapSize(int width, int height);

protected:
    void paintEvent(QPaintEvent* event) override;

private:
    QColor titleColor() const;
    QColor subTitleColor() const;
};

#endif // ELAINTERACTIVECARD_H
