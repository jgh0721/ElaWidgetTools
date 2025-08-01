#include "ElaSuggestBox.h"

#include <QAction>
#include <QDebug>
#include <QHBoxLayout>
#include <QLineEdit>
#include <QListView>
#include <QMap>
#include <QPainter>
#include <QPainterPath>
#include <QVBoxLayout>

#include "ElaBaseListView.h"
#include "ElaIcon.h"
#include "ElaLineEdit.h"
#include "ElaScrollBar.h"
#include "ElaSuggestBoxSearchViewContainer.h"
#include "ElaSuggestDelegate.h"
#include "ElaSuggestModel.h"
#include "ElaTheme.h"
#include "private/ElaSuggestBoxPrivate.h"

Q_PROPERTY_CREATE_Q_CPP(ElaSuggestBox, int, BorderRadius)
Q_PROPERTY_CREATE_Q_CPP(ElaSuggestBox, Qt::CaseSensitivity, CaseSensitivity)
ElaSuggestBox::ElaSuggestBox(QWidget* parent)
    : QWidget{parent}, d_ptr(new ElaSuggestBoxPrivate())
{
    Q_D(ElaSuggestBox);
    setFixedSize(280, 35);
    d->q_ptr = this;
    d->_pBorderRadius = 6;
    d->_pCaseSensitivity = Qt::CaseInsensitive;
    d->_searchEdit = new ElaLineEdit(this);
    d->_searchEdit->setFixedHeight(35);
    d->_searchEdit->setPlaceholderText(tr("查找功能"));
    d->_searchEdit->setClearButtonEnabled(true);
    d->_lightSearchAction = new QAction(ElaIcon::getInstance()->getElaIcon(ElaIconType::MagnifyingGlass), "Search", this);
    d->_darkSearchAction = new QAction(ElaIcon::getInstance()->getElaIcon(ElaIconType::MagnifyingGlass, QColor(0xFF, 0xFF, 0xFF)), "Search", this);

    d->_themeMode = eTheme->getThemeMode();
    connect(eTheme, &ElaTheme::themeModeChanged, d, &ElaSuggestBoxPrivate::onThemeModeChanged);
    if (d->_themeMode == ElaThemeType::Light)
    {
        d->_searchEdit->addAction(d->_lightSearchAction, QLineEdit::TrailingPosition);
    }
    else
    {
        d->_searchEdit->addAction(d->_darkSearchAction, QLineEdit::TrailingPosition);
    }

    connect(d->_lightSearchAction, &QAction::triggered, this, [=](bool checked) {
        //qDebug() << "Search";
    });

    connect(d->_darkSearchAction, &QAction::triggered, this, [=](bool checked) {
        //qDebug() << "Search";
    });
    QVBoxLayout* mainLayout = new QVBoxLayout(this);
    mainLayout->setSpacing(0);
    mainLayout->setContentsMargins(0, 0, 0, 0);
    mainLayout->addWidget(d->_searchEdit);
    d->_searchViewBaseWidget = new ElaSuggestBoxSearchViewContainer(window());
    d->_shadowLayout = new QVBoxLayout(d->_searchViewBaseWidget);
    d->_shadowLayout->setContentsMargins(0, 0, 0, 0);
    d->_searchView = new ElaBaseListView(d->_searchViewBaseWidget);
    ElaScrollBar* floatVScrollBar = new ElaScrollBar(d->_searchView->verticalScrollBar(), d->_searchView);
    floatVScrollBar->setIsAnimation(true);
    d->_searchViewBaseWidget->resize(292, 300);
    d->_shadowLayout->addWidget(d->_searchView);
    d->_searchModel = new ElaSuggestModel(this);
    d->_searchDelegate = new ElaSuggestDelegate(this);
    d->_searchView->setModel(d->_searchModel);
    d->_searchView->setItemDelegate(d->_searchDelegate);
    d->_searchViewBaseWidget->hide();
    connect(d->_searchEdit, &ElaLineEdit::textEdited, d, &ElaSuggestBoxPrivate::onSearchEditTextEdit);
    connect(d->_searchEdit, &ElaLineEdit::focusIn, d, &ElaSuggestBoxPrivate::onSearchEditTextEdit);
    connect(d->_searchEdit, &ElaLineEdit::returnPressed, this, &ElaSuggestBox::suggestionReturnPressed );
    connect(d->_searchEdit, &ElaLineEdit::editingFinished, this, &ElaSuggestBox::suggestionEditingFinished );
    connect(d->_searchView, &ElaBaseListView::clicked, d, &ElaSuggestBoxPrivate::onSearchViewClicked);

    // 焦点事件
    connect(d->_searchEdit, &ElaLineEdit::wmFocusOut, this, [d]() {
        d->_startCloseAnimation();
    });
}

ElaSuggestBox::~ElaSuggestBox()
{
}

void ElaSuggestBox::setPlaceholderText(const QString& placeholderText)
{
    Q_D(ElaSuggestBox);
    d->_searchEdit->setPlaceholderText(placeholderText);
}

QString ElaSuggestBox::getPlaceholderText() const
{
    const Q_D(ElaSuggestBox);
    return d->_searchEdit->placeholderText();
}

void ElaSuggestBox::setTextColor(QColor textColor)
{
    Q_D(ElaSuggestBox);
    d->_searchEdit->setTextColor(textColor);
    d->_pTextColor = std::move(textColor);
    Q_EMIT pTextColorChanged();
}

QColor ElaSuggestBox::getTextColor() const
{
    Q_D(const ElaSuggestBox);
    return d->_pTextColor;
}

void ElaSuggestBox::setPlaceHolderTextColor(QColor placeholderTextColor)
{
    Q_D(ElaSuggestBox);
    d->_searchEdit->setPlaceHolderTextColor(placeholderTextColor);
    d->_pPlaceHolderTextColor = std::move(placeholderTextColor);
    Q_EMIT pPlaceHolderTextColorChanged();
}

QColor ElaSuggestBox::getPlaceHolderTextColor() const
{
    Q_D(const ElaSuggestBox);
    return d->_pPlaceHolderTextColor;
}

QString ElaSuggestBox::addSuggestion(const QString& suggestText, const QVariantMap& suggestData)
{
    Q_D(ElaSuggestBox);
    ElaSuggestion* suggest = new ElaSuggestion(this);
    suggest->setSuggestText(suggestText);
    suggest->setSuggestData(suggestData);
    d->_suggestionVector.append(suggest);
    return suggest->getSuggestKey();
}

QString ElaSuggestBox::addSuggestion(ElaIconType::IconName icon, const QString& suggestText, const QVariantMap& suggestData)
{
    Q_D(ElaSuggestBox);
    ElaSuggestion* suggest = new ElaSuggestion(this);
    suggest->setElaIcon(icon);
    suggest->setSuggestText(suggestText);
    suggest->setSuggestData(suggestData);
    d->_suggestionVector.append(suggest);
    return suggest->getSuggestKey();
}

void ElaSuggestBox::removeSuggestion(const QString& suggestKey)
{
    Q_D(ElaSuggestBox);
    foreach (auto suggest, d->_suggestionVector)
    {
        if (suggest->getSuggestKey() == suggestKey)
        {
            d->_suggestionVector.removeOne(suggest);
            suggest->deleteLater();
        }
    }
}

void ElaSuggestBox::removeSuggestion(int index)
{
    Q_D(ElaSuggestBox);
    if (index >= d->_suggestionVector.count())
    {
        return;
    }
    ElaSuggestion* suggest = d->_suggestionVector[index];
    d->_suggestionVector.removeOne(suggest);
    suggest->deleteLater();
}

void ElaSuggestBox::clearSuggestions()
{
    Q_D(ElaSuggestBox);
    for( auto suggest : d->_suggestionVector )
        suggest->deleteLater();
    d->_suggestionVector.clear();
}

QString ElaSuggestBox::text() const
{
    const Q_D(ElaSuggestBox);
    return d->_searchEdit->text();
}

void ElaSuggestBox::clearText()
{
    Q_D(ElaSuggestBox);
    d->_searchEdit->clear();
}

ElaLineEdit* ElaSuggestBox::lineEdit() const
{
    Q_D(const ElaSuggestBox);
    return d->_searchEdit;
}
