#include <QtPlugin>
#include "ElaWidgetToolsDesigner.hpp"
#include <QDesignerFormEditorInterface>
#include <QDesignerFormWindowManagerInterface>
#include <QDesignerFormWindowInterface>
#include <QDesignerPropertyEditorInterface>

#include "ElaAcrylicUrlCard.h"
#include "ElaBreadcrumbBar.h"
#include "ElaCheckBox.h"
#include "ElaCalendarPicker.h"
#include "ElaTreeView.h"
#include "ElaLineEdit.h"
#include "ElaComboBox.h"
#include "ElaIconButton.h"
#include "ElaListView.h"
#include "ElaTableView.h"
#include "ElaTabWidget.h"
#include "ElaTabBar.h"
#include "ElaRoller.h"
#include "ElaSuggestBox.h"
#include "ElaText.h"
#include "ElaToggleButton.h"
#include "ElaToggleSwitch.h"
#include "ElaPlainTextEdit.h"
#include "ElaProgressBar.h"

///////////////////////////////////////////////////////////////////////////////
///

ElaWidgetToolsDesignerPlugin::ElaWidgetToolsDesignerPlugin(QObject *parent)
: QObject(parent)
{
    m_extensions
    << new ElaCheckBoxPlugin(this)
    << new ElaLineEditPlugin(this)
    << new ElaTreeViewPlugin(this)
    ;
}

QList<QDesignerCustomWidgetInterface*> ElaWidgetToolsDesignerPlugin::customWidgets() const
{
    return m_extensions;
}

///////////////////////////////////////////////////////////////////////////////
///

DEFINE_BASE(ElaCheckBox)
DEFINE_BASE_ICON( ElaCheckBox, QStringLiteral(":res/TreeView.png") )
DEFINE_BASE_WHATS_THIS(ElaCheckBox, "ElaCheckBox on ElaWidgetTools")
DEFINE_BASE_IS_CONTAINER(ElaCheckBox, false )

QString ElaCheckBoxPlugin::domXml() const
{
    QString className = QStringLiteral("ElaCheckBox");
    return QStringLiteral("<ui language=\"c++\">\n"
           " <widget class=\"" "%1" "\" name=\"elacheckbox\">\n"
           "  <property name=\"geometry\">\n"
           "   <rect>\n"
           "    <x>0</x>\n"
           "    <y>0</y>\n"
           "    <width>80</width>\n"
           "    <height>21</height>\n"
           "   </rect>\n"
           "  </property>\n"
           "  <property name=\"toolTip\" >\n"
           "   <string>Advanced DataGrid for Qt</string>\n"
           "  </property>\n"
           "  <property name=\"whatsThis\" >\n"
           "   <string>Advanced DataGrid for Qt.</string>\n"
           "  </property>\n"
           " </widget>\n"
           "</ui>\n").arg(className);
}

///////////////////////////////////////////////////////////////////////////////
///

DEFINE_BASE(ElaLineEdit)
DEFINE_BASE_ICON( ElaLineEdit, QStringLiteral(":res/TreeView.png") )
DEFINE_BASE_WHATS_THIS(ElaLineEdit, "ElaLineEdit on ElaWidgetTools")
DEFINE_BASE_IS_CONTAINER(ElaLineEdit, false )

QString ElaLineEditPlugin::domXml() const
{
    QString className = QStringLiteral("ElaLineEdit");
    return QStringLiteral("<ui language=\"c++\">\n"
           " <widget class=\"" "%1" "\" name=\"elalineedit\">\n"
           "  <property name=\"geometry\">\n"
           "   <rect>\n"
           "    <x>0</x>\n"
           "    <y>0</y>\n"
           "    <width>300</width>\n"
           "    <height>200</height>\n"
           "   </rect>\n"
           "  </property>\n"
           "  <property name=\"toolTip\" >\n"
           "   <string>Advanced DataGrid for Qt</string>\n"
           "  </property>\n"
           "  <property name=\"whatsThis\" >\n"
           "   <string>Advanced DataGrid for Qt.</string>\n"
           "  </property>\n"
           " </widget>\n"
           "</ui>\n").arg(className);
}

///////////////////////////////////////////////////////////////////////////////
///

DEFINE_BASE(ElaTreeView)
DEFINE_BASE_ICON( ElaTreeView, QStringLiteral(":res/TreeView.png") )
DEFINE_BASE_WHATS_THIS(ElaTreeView, "ElaTreeView on ElaWidgetTools")
DEFINE_BASE_IS_CONTAINER(ElaTreeView, false )

QString ElaTreeViewPlugin::domXml() const
{
    QString className = QStringLiteral("ElaTreeView");
    return QStringLiteral("<ui language=\"c++\">\n"
           " <widget class=\"" "%1" "\" name=\"elatreeview\">\n"
           "  <property name=\"geometry\">\n"
           "   <rect>\n"
           "    <x>0</x>\n"
           "    <y>0</y>\n"
           "    <width>300</width>\n"
           "    <height>200</height>\n"
           "   </rect>\n"
           "  </property>\n"
           "  <property name=\"toolTip\" >\n"
           "   <string>Advanced DataGrid for Qt</string>\n"
           "  </property>\n"
           "  <property name=\"whatsThis\" >\n"
           "   <string>Advanced DataGrid for Qt.</string>\n"
           "  </property>\n"
           " </widget>\n"
           "</ui>\n").arg(className);
}
