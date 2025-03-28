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

#include "ElaDockWidget.h"
#include "ElaDoubleSpinBox.h"
#include "ElaDrawerArea.h"

#include "ElaFlowLayout.h"

#include "ElaIcon.h"
#include "ElaIconButton.h"
#include "ElaImageCard.h"
#include "ElaInteractiveCard.h"

#include "ElaKeyBinder.h"

#include "ElaLCDNumber.h"
#include "ElaLineEdit.h"
#include "ElaListView.h"
#include "ElaListWidget.h"

#include "ElaMessageButton.h"
#include "ElaMultiSelectComboBox.h"

#include "ElaPlainTextEdit.h"
#include "ElaPopularCard.h"
#include "ElaProgressBar.h"
#include "ElaPromotionCard.h"
#include "ElaPushButton.h"

#include "ElaRadioButton.h"
#include "ElaReminderCard.h"
#include "ElaRoller.h"

#include "ElaSlider.h"
#include "ElaSpinBox.h"
#include "ElaSuggestBox.h"

#include "ElaTabBar.h"
#include "ElaTableView.h"
#include "ElaTableWidget.h"
#include "ElaTabWidget.h"
#include "ElaTableView.h"
#include "ElaText.h"
#include "ElaToggleButton.h"
#include "ElaToggleSwitch.h"
#include "ElaToolBar.h"
#include "ElaToolButton.h"
#include "ElaTreeView.h"
#include "ElaWidget.h"

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

    << new ElaPlainTextEditPlugin(this)
    << new ElaPushButtonPlugin(this)

    << new ElaRadioButtonPlugin(this)

    << new ElaTabBarPlugin(this)
    << new ElaTabWidgetPlugin(this)
    << new ElaTableViewPlugin(this)
    << new ElaTableWidgetPlugin(this)
    << new ElaTextPlugin(this)
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

DEFINE_BASE(ElaPlainTextEdit)
DEFINE_BASE_ICON( ElaPlainTextEdit, QStringLiteral(":res/TreeView.png") )
DEFINE_BASE_WHATS_THIS(ElaPlainTextEdit, "ElaPlainTextEdit on ElaWidgetTools")
DEFINE_BASE_IS_CONTAINER(ElaPlainTextEdit, false )

QString ElaPlainTextEditPlugin::domXml() const
{
    QString className = QStringLiteral("ElaPlainTextEdit");
    return QStringLiteral("<ui language=\"c++\">\n"
           " <widget class=\"" "%1" "\" name=\"elaplaintextedit\">\n"
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

DEFINE_BASE(ElaPushButton)
DEFINE_BASE_ICON( ElaPushButton, QStringLiteral(":res/TreeView.png") )
DEFINE_BASE_WHATS_THIS(ElaPushButton, "ElaPushButton on ElaWidgetTools")
DEFINE_BASE_IS_CONTAINER(ElaPushButton, false )

QString ElaPushButtonPlugin::domXml() const
{
    QString className = QStringLiteral("ElaPushButton");
    return QStringLiteral("<ui language=\"c++\">\n"
           " <widget class=\"" "%1" "\" name=\"elapushbutton\">\n"
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

DEFINE_BASE(ElaRadioButton)
DEFINE_BASE_ICON( ElaRadioButton, QStringLiteral(":res/TreeView.png") )
DEFINE_BASE_WHATS_THIS(ElaRadioButton, "ElaRadioButton on ElaWidgetTools")
DEFINE_BASE_IS_CONTAINER(ElaRadioButton, false )

QString ElaRadioButtonPlugin::domXml() const
{
    QString className = QStringLiteral("ElaRadioButton");
    return QStringLiteral("<ui language=\"c++\">\n"
           " <widget class=\"" "%1" "\" name=\"elaradiobutton\">\n"
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

DEFINE_BASE(ElaRoller)
DEFINE_BASE_ICON( ElaRoller, QStringLiteral(":res/TreeView.png") )
DEFINE_BASE_WHATS_THIS(ElaRoller, "ElaRoller on ElaWidgetTools")
DEFINE_BASE_IS_CONTAINER(ElaRoller, false )

QString ElaRollerPlugin::domXml() const
{
    QString className = QStringLiteral("ElaRoller");
    return QStringLiteral("<ui language=\"c++\">\n"
           " <widget class=\"" "%1" "\" name=\"elaroller\">\n"
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

DEFINE_BASE(ElaTabBar)
DEFINE_BASE_ICON( ElaTabBar, ElaIcon::getInstance()->getElaIcon( ElaIconType::ListTree ) )
DEFINE_BASE_WHATS_THIS(ElaTabBar, "ElaTabBar on ElaWidgetTools")
DEFINE_BASE_IS_CONTAINER(ElaTabBar, false )

QString ElaTabBarPlugin::domXml() const
{
    QString className = QStringLiteral("ElaTabBar");
    return QStringLiteral("<ui language=\"c++\">\n"
           " <widget class=\"" "%1" "\" name=\"elatabbar\">\n"
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

DEFINE_BASE(ElaTabWidget)
DEFINE_BASE_ICON( ElaTabWidget, ElaIcon::getInstance()->getElaIcon( ElaIconType::ListTree ) )
DEFINE_BASE_WHATS_THIS(ElaTabWidget, "ElaTabWidget on ElaWidgetTools")
DEFINE_BASE_IS_CONTAINER(ElaTabWidget, true )

QString ElaTabWidgetPlugin::domXml() const
{
    QString className = QStringLiteral("ElaTabWidget");
    return QStringLiteral("<ui language=\"c++\">\n"
           " <widget class=\"" "%1" "\" name=\"elatabwidget\">\n"
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

DEFINE_BASE(ElaText)
DEFINE_BASE_ICON( ElaText, ElaIcon::getInstance()->getElaIcon( ElaIconType::ListTree ) )
DEFINE_BASE_WHATS_THIS(ElaText, "ElaText on ElaWidgetTools")
DEFINE_BASE_IS_CONTAINER(ElaText, false )

QString ElaTextPlugin::domXml() const
{
    QString className = QStringLiteral("ElaText");
    return QStringLiteral("<ui language=\"c++\">\n"
           " <widget class=\"" "%1" "\" name=\"elatext\">\n"
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
