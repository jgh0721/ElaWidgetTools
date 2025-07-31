#ifndef ELASUGGESTBOX_H
#define ELASUGGESTBOX_H

#include <QVariantMap>
#include <QWidget>
#include <QColor>

#include "Def.h"
#include "stdafx.h"

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
    ~ElaSuggestBox();
    void setPlaceholderText(const QString& placeholderText);
    QString getPlaceholderText() const;

    QString addSuggestion(const QString& suggestText, const QVariantMap& suggestData = {});
    QString addSuggestion(ElaIconType::IconName icon, const QString& suggestText, const QVariantMap& suggestData = {});
    void removeSuggestion(const QString& suggestKey);
    void removeSuggestion(int index);
    void clearSuggestions();

    QString text() const;
    void clearText();
    ElaLineEdit* lineEdit() const;

Q_SIGNALS:
    Q_SIGNAL void suggestionReturnPressed();
    Q_SIGNAL void suggestionEditingFinished();
    Q_SIGNAL void suggestionClicked(const QString& suggestText, const QVariantMap& suggestData);
};

#endif // ELASUGGESTBOX_H
