#ifndef ELASUGGESTBOX_H
#define ELASUGGESTBOX_H

#include <QVariantMap>
#include <QWidget>
#include <QColor>

#include "ElaDef.h"
#include "ElaProperty.h"

class ElaLineEdit;
class ElaSuggestBoxPrivate;
class ELA_EXPORT ElaSuggestBox : public QWidget
{
    Q_OBJECT
    Q_Q_CREATE(ElaSuggestBox)
    Q_PROPERTY_CREATE_Q_H(int, BorderRadius)
    Q_PROPERTY_CREATE_Q_H(Qt::CaseSensitivity, CaseSensitivity)
    Q_PROPERTY_CREATE_Q_H(QColor, TextColor)
    Q_PROPERTY_CREATE_Q_H(QColor, PlaceHolderTextColor)
public:
    explicit ElaSuggestBox(QWidget* parent = nullptr);
    ~ElaSuggestBox() override;
    void setPlaceholderText(const QString& placeholderText);
    QString getPlaceholderText() const;
    void setFixedSize(const QSize& size);
    void setFixedSize(int w, int h);
    void setFixedHeight(int h);

    struct ELA_EXPORT SuggestData {
        Q_PRIVATE_CREATE(ElaIconType::IconName, ElaIcon)
        Q_PRIVATE_CREATE(QString, SuggestText)
        Q_PRIVATE_CREATE(QString, SuggestKey)
        Q_PRIVATE_CREATE(QVariantMap, SuggestData)
    public:
        explicit SuggestData();
        explicit SuggestData(ElaIconType::IconName icon, const QString& suggestText, const QVariantMap& suggestData = {});
        ~SuggestData();
    };
    QString addSuggestion(const QString& suggestText, const QVariantMap& suggestData = {});
    QString addSuggestion(ElaIconType::IconName icon, const QString& suggestText, const QVariantMap& suggestData = {});
    QString addSuggestion(const ElaSuggestBox::SuggestData& suggestData);
    QStringList addSuggestion(const QList<ElaSuggestBox::SuggestData>& suggestDataList);

    void removeSuggestion(const QString& suggestKey);
    void removeSuggestion(int index);
    void clearSuggestion();

    QString text() const;
    void clearText();
    ElaLineEdit* lineEdit() const;

Q_SIGNALS:
    Q_SIGNAL void suggestionReturnPressed();
    Q_SIGNAL void suggestionEditingFinished();
    Q_SIGNAL void suggestionClicked(const ElaSuggestBox::SuggestData& suggestData);
};

#endif // ELASUGGESTBOX_H
