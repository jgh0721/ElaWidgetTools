#include <QtPlugin>
#include "ElaWidgetToolsDesigner.hpp"
#include <QDesignerFormEditorInterface>
#include <QDesignerFormWindowManagerInterface>
#include <QDesignerFormWindowInterface>
#include <QDesignerPropertyEditorInterface>

#include "ElaAcrylicUrlCard.h"
#include "ElaBreadcrumbBar.h"
#include "ElaCalendarPicker.h"
#include "ElaCheckBox.h"
#include "ElaComboBox.h"
#include "ElaIcon.h"
#include "ElaIconButton.h"
#include "ElaLineEdit.h"
#include "ElaListView.h"
#include "ElaListWidget.h"
#include "ElaTableView.h"
#include "ElaTabWidget.h"
#include "ElaTabBar.h"
#include "ElaRoller.h"
#include "ElaSuggestBox.h"
#include "ElaTableView.h"
#include "ElaTableWidget.h"
#include "ElaText.h"
#include "ElaToggleButton.h"
#include "ElaToggleSwitch.h"
#include "ElaTreeView.h"
#include "ElaPlainTextEdit.h"
#include "ElaProgressBar.h"

///////////////////////////////////////////////////////////////////////////////
///

ElaWidgetToolsDesignerPlugin::ElaWidgetToolsDesignerPlugin(QObject *parent)
: QObject(parent)
{
    m_extensions
        << new ElaAcrylicUrlCardPlugin(this)
        << new ElaBreadcrumbBarPlugin(this)
        << new ElaCalendarPickerPlugin(this)
        << new ElaCheckBoxPlugin(this)
        << new ElaComboBoxPlugin(this)
        << new ElaLineEditPlugin(this)
        << new ElaListViewPlugin(this)
        << new ElaListWidgetPlugin(this)
        << new ElaTableViewPlugin(this)
        << new ElaTableWidgetPlugin(this)
        << new ElaToggleButtonPlugin(this)
        << new ElaToggleSwitchPlugin(this)
        << new ElaTreeViewPlugin(this)
        ;
}

QList<QDesignerCustomWidgetInterface*> ElaWidgetToolsDesignerPlugin::customWidgets() const
{
    return m_extensions;
}

///////////////////////////////////////////////////////////////////////////////
///

DEFINE_BASE(ElaAcrylicUrlCard)
DEFINE_BASE_ICON( ElaAcrylicUrlCard, QStringLiteral(":res/TreeView.png") )
DEFINE_BASE_WHATS_THIS(ElaAcrylicUrlCard, "ElaAcrylicUrlCard on ElaWidgetTools")
DEFINE_BASE_IS_CONTAINER(ElaAcrylicUrlCard, false )

QString ElaAcrylicUrlCardPlugin::domXml() const
{
    QString className = QStringLiteral("ElaAcrylicUrlCard");
    return QStringLiteral("<ui language=\"c++\">\n"
           " <widget class=\"" "%1" "\" name=\"elaarcylicurlcard\">\n"
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

DEFINE_BASE(ElaBreadcrumbBar)
DEFINE_BASE_ICON( ElaBreadcrumbBar, QStringLiteral(":res/TreeView.png") )
DEFINE_BASE_WHATS_THIS(ElaBreadcrumbBar, "ElaBreadcrumbBar on ElaWidgetTools")
DEFINE_BASE_IS_CONTAINER(ElaBreadcrumbBar, false )

QString ElaBreadcrumbBarPlugin::domXml() const
{
    QString className = QStringLiteral("ElaBreadcrumbBar");
    return QStringLiteral("<ui language=\"c++\">\n"
           " <widget class=\"" "%1" "\" name=\"elabreadcrumbar\">\n"
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

DEFINE_BASE(ElaCalendarPicker)
DEFINE_BASE_ICON( ElaCalendarPicker, QStringLiteral(":res/TreeView.png") )
DEFINE_BASE_WHATS_THIS(ElaCalendarPicker, "ElaCalendarPicker on ElaWidgetTools")
DEFINE_BASE_IS_CONTAINER(ElaCalendarPicker, false )

QString ElaCalendarPickerPlugin::domXml() const
{
    QString className = QStringLiteral("ElaCalendarPicker");
    return QStringLiteral("<ui language=\"c++\">\n"
           " <widget class=\"" "%1" "\" name=\"elacalendarpicker\">\n"
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

DEFINE_BASE(ElaComboBox)
DEFINE_BASE_ICON( ElaComboBox, QStringLiteral(":res/TreeView.png") )
DEFINE_BASE_WHATS_THIS(ElaComboBox, "ElaComboBox on ElaWidgetTools")
DEFINE_BASE_IS_CONTAINER(ElaComboBox, false )

QString ElaComboBoxPlugin::domXml() const
{
    QString className = QStringLiteral("ElaComboBox");
    return QStringLiteral("<ui language=\"c++\">\n"
           " <widget class=\"" "%1" "\" name=\"elacombobox\">\n"
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

DEFINE_BASE(ElaListView)
DEFINE_BASE_ICON( ElaListView, QStringLiteral(":res/TreeView.png") )
DEFINE_BASE_WHATS_THIS(ElaListView, "ElaListView on ElaWidgetTools")
DEFINE_BASE_IS_CONTAINER(ElaListView, false )

QString ElaListViewPlugin::domXml() const
{
    QString className = QStringLiteral("ElaListView");
    return QStringLiteral("<ui language=\"c++\">\n"
           " <widget class=\"" "%1" "\" name=\"elalistview\">\n"
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

DEFINE_BASE(ElaListWidget)
DEFINE_BASE_ICON( ElaListWidget, QStringLiteral(":res/TreeView.png") )
DEFINE_BASE_WHATS_THIS(ElaListWidget, "ElaListWidget on ElaWidgetTools")
DEFINE_BASE_IS_CONTAINER(ElaListWidget, false )

QString ElaListWidgetPlugin::domXml() const
{
    QString className = QStringLiteral("ElaListWidget");
    return QStringLiteral("<ui language=\"c++\">\n"
           " <widget class=\"" "%1" "\" name=\"elalistwidget\">\n"
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

DEFINE_BASE(ElaTableView)
DEFINE_BASE_ICON( ElaTableView, QStringLiteral(":res/TreeView.png") )
DEFINE_BASE_WHATS_THIS(ElaTableView, "ElaTableView on ElaWidgetTools")
DEFINE_BASE_IS_CONTAINER(ElaTableView, false )

QString ElaTableViewPlugin::domXml() const
{
    QString className = QStringLiteral("ElaTableView");
    return QStringLiteral("<ui language=\"c++\">\n"
           " <widget class=\"" "%1" "\" name=\"elatableview\">\n"
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

DEFINE_BASE(ElaTableWidget)
DEFINE_BASE_ICON( ElaTableWidget, QStringLiteral(":res/TreeView.png") )
DEFINE_BASE_WHATS_THIS(ElaTableWidget, "ElaTableWidget on ElaWidgetTools")
DEFINE_BASE_IS_CONTAINER(ElaTableWidget, false )

QString ElaTableWidgetPlugin::domXml() const
{
    QString className = QStringLiteral("ElaTableWidget");
    return QStringLiteral("<ui language=\"c++\">\n"
           " <widget class=\"" "%1" "\" name=\"elaTableWidget\">\n"
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

DEFINE_BASE(ElaToggleButton)
DEFINE_BASE_ICON( ElaToggleButton, QStringLiteral(":res/TreeView.png") )
DEFINE_BASE_WHATS_THIS(ElaToggleButton, "ElaTreeView on ElaWidgetTools")
DEFINE_BASE_IS_CONTAINER(ElaToggleButton, false )

QString ElaToggleButtonPlugin::domXml() const
{
    QString className = QStringLiteral("ElaToggleButton");
    return QStringLiteral("<ui language=\"c++\">\n"
           " <widget class=\"" "%1" "\" name=\"elatogglebutton\">\n"
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

DEFINE_BASE(ElaToggleSwitch)
DEFINE_BASE_ICON( ElaToggleSwitch, QStringLiteral(":res/TreeView.png") )
DEFINE_BASE_WHATS_THIS(ElaToggleSwitch, "ElaToggleSwitch on ElaWidgetTools")
DEFINE_BASE_IS_CONTAINER(ElaToggleSwitch, false )

QString ElaToggleSwitchPlugin::domXml() const
{
    QString className = QStringLiteral("ElaToggleSwitch");
    return QStringLiteral("<ui language=\"c++\">\n"
           " <widget class=\"" "%1" "\" name=\"elatoggleswitch\">\n"
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
DEFINE_BASE_ICON( ElaTreeView, ElaIcon::getInstance()->getElaIcon( ElaIconType::ListTree ) )
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
