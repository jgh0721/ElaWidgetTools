#include <QtPlugin>
#include "ElaWidgetToolsDesigner.hpp"
#include <QDesignerFormEditorInterface>
#include <QDesignerFormWindowManagerInterface>
#include <QDesignerFormWindowInterface>
#include <QDesignerPropertyEditorInterface>
#include <QFile>
#include <QMetaEnum>
#include <QSettings>

#include "ElaAcrylicUrlCard.h"
#include "ElaApplication.h"

#include "ElaBreadcrumbBar.h"

#include "ElaCalendar.h"
#include "ElaCalendarPicker.h"
#include "ElaCheckBox.h"
#include "ElaComboBox.h"
#include "ElaCentralStackedWidget.h"

#include "ElaDockWidget.h"
#include "ElaDoubleSpinBox.h"
#include "ElaDrawerArea.h"
#include "ElaDxgi.h"

#include "ElaFrame.h"

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

#include "ElaPivot.h"
#include "ElaPlainTextEdit.h"
#include "ElaPopularCard.h"
#include "ElaProgressBar.h"
#include "ElaProgressRing.h"
#include "ElaPromotionCard.h"
#include "ElaPushButton.h"

#include "ElaRadioButton.h"
#include "ElaReminderCard.h"
#include "ElaRoller.h"

#include "ElaScrollArea.h"
#include "ElaScrollPageArea.h"
#include "ElaSlider.h"
#include "ElaSpinBox.h"
#include "ElaSuggestBox.h"

#include "ElaTabBar.h"
#include "ElaTableView.h"
#include "ElaTableWidget.h"
#include "ElaTabWidget.h"
#include "ElaTableView.h"
#include "ElaText.h"
#include "ElaTheme.h"
#include "ElaToggleButton.h"
#include "ElaToggleSwitch.h"
#include "ElaToolBar.h"
#include "ElaToolButton.h"
#include "ElaTreeView.h"
#include "ElaTreeWidget.h"

#include "ElaWidget.h"
#include "ElaWindow.h"

#include "QMessageBox"

const auto ElaWidgetToolsTheme = QStringLiteral("ElaWidgetToolsTheme.ini");

///////////////////////////////////////////////////////////////////////////////
///

ElaWidgetToolsDesignerPlugin::ElaWidgetToolsDesignerPlugin(QObject *parent)
: QObject(parent)
{
    eApp->init( ElaWidgetToolsTheme );

    m_extensions
    << new ElaAcrylicUrlCardPlugin(this)

    << new ElaBreadcrumbBarPlugin(this)

    << new ElaCalendarPlugin(this)
    << new ElaCalendarPickerPlugin(this)
    << new ElaCheckBoxPlugin(this)
    << new ElaComboBoxPlugin(this)
    << new ElaCentralStackedWidgetPlugin(this)

    << new ElaDockWidgetPlugin(this)
    << new ElaDoubleSpinBoxPlugin(this)

    << new ElaFramePlugin(this)

    << new ElaIconButtonPlugin(this)
    << new ElaImageCardPlugin(this)
    << new ElaInteractiveCardPlugin(this)

    << new ElaLCDNumberPlugin(this)
    << new ElaLineEditPlugin(this)
    << new ElaListViewPlugin(this)
    << new ElaListWidgetPlugin(this)

    << new ElaMessageButtonPlugin(this)
    << new ElaMultiSelectComboBoxPlugin(this)

    << new ElaPivotPlugin(this)
    << new ElaPlainTextEditPlugin(this)
    << new ElaPopularCardPlugin(this)
    << new ElaProgressBarPlugin(this)
    << new ElaProgressRingPlugin(this)
    << new ElaPushButtonPlugin(this)

    << new ElaRadioButtonPlugin(this)
    << new ElaReminderCardPlugin(this)
    << new ElaRollerPlugin(this)

    << new ElaScrollAreaPlugin(this)
    << new ElaScrollPageAreaPlugin(this)
    << new ElaSliderPlugin(this)
    << new ElaSpinBoxPlugin(this)
    << new ElaSuggestBoxPlugin(this)

    << new ElaTabBarPlugin(this)
    << new ElaTableViewPlugin(this)
    << new ElaTableWidgetPlugin(this)
    << new ElaTabWidgetPlugin(this)
    << new ElaTextPlugin(this)
    << new ElaToggleButtonPlugin(this)
    << new ElaToggleSwitchPlugin(this)
    << new ElaToolBarPlugin(this)
    << new ElaToolButtonPlugin(this)
    << new ElaTreeViewPlugin(this)
    << new ElaTreeWidgetPlugin(this)

    << new ElaWidgetPlugin(this)
    << new ElaWindowPlugin(this)
    ;
}

QList<QDesignerCustomWidgetInterface*> ElaWidgetToolsDesignerPlugin::customWidgets() const
{
    return m_extensions;
}

QString createWidgetXml( const QString& ClassName, const QString& DefaultWidgetName, QSize DefaultSize )
{
    return QStringLiteral( R"(
<ui language="c++">
    <widget class="%1" name="%2">
        <property name="geometry">
            <rect>
                <x>0</x>
                <y>0</y>
                <width>%3</width>
                <height>%4</height>
            </rect>
        </property>
        <property name="font">
            <font>
                <family>%5</family>
                <pointsize>-1</pointsize>
            </font>
        </property>
    </widget>
</ui>
    )" )
    .arg( ClassName ).arg( DefaultWidgetName )
    .arg( DefaultSize.width() ).arg( DefaultSize.height() )
    .arg( eTheme->getFontFamily() );
}

///////////////////////////////////////////////////////////////////////////////
///

DEFINE_BASE(ElaAcrylicUrlCard)
DEFINE_BASE_ICON( ElaAcrylicUrlCard, QStringLiteral(":res/TreeView.png") )
DEFINE_BASE_WHATS_THIS(ElaAcrylicUrlCard, "ElaAcrylicUrlCard on ElaWidgetTools")
DEFINE_BASE_IS_CONTAINER(ElaAcrylicUrlCard, false )

QString ElaAcrylicUrlCardPlugin::domXml() const
{
    const auto className = QStringLiteral("ElaAcrylicUrlCard");
    return createWidgetXml( className, className.toLower(), QSize( 100, 50 ) );
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
    return createWidgetXml( className, className.toLower(), QSize( 150, 36 ) );
}

///////////////////////////////////////////////////////////////////////////////
///

DEFINE_BASE(ElaCalendar)
DEFINE_BASE_ICON( ElaCalendar, ElaIcon::getInstance()->getElaIcon( ElaIconType::Calendar ) )
DEFINE_BASE_WHATS_THIS(ElaCalendar, "ElaCalendar on ElaWidgetTools")
DEFINE_BASE_IS_CONTAINER(ElaCalendar, false )

QString ElaCalendarPlugin::domXml() const
{
    QString className = QStringLiteral("ElaCalendar");
    return createWidgetXml( className, className.toLower(), QSize( 305, 340 ) );
}

///////////////////////////////////////////////////////////////////////////////
///

DEFINE_BASE(ElaCalendarPicker)
DEFINE_BASE_ICON( ElaCalendarPicker, ElaIcon::getInstance()->getElaIcon( ElaIconType::Calendar ) )
DEFINE_BASE_WHATS_THIS(ElaCalendarPicker, "ElaCalendarPicker on ElaWidgetTools")
DEFINE_BASE_IS_CONTAINER(ElaCalendarPicker, false )

QString ElaCalendarPickerPlugin::domXml() const
{
    QString className = QStringLiteral("ElaCalendarPicker");
    return createWidgetXml( className, className.toLower(), QSize( 120, 30 ) );
}

///////////////////////////////////////////////////////////////////////////////
///

DEFINE_BASE(ElaCheckBox)
DEFINE_BASE_ICON( ElaCheckBox, ElaIcon::getInstance()->getElaIcon( ElaIconType::Check ) )
DEFINE_BASE_WHATS_THIS(ElaCheckBox, "ElaCheckBox on ElaWidgetTools")
DEFINE_BASE_IS_CONTAINER(ElaCheckBox, false )

QString ElaCheckBoxPlugin::domXml() const
{
    QString className = QStringLiteral("ElaCheckBox");
    return createWidgetXml( className, className.toLower(), QSize( 100, 22 ) );
}

///////////////////////////////////////////////////////////////////////////////
///

DEFINE_BASE(ElaComboBox)
DEFINE_BASE_ICON( ElaComboBox, ElaIcon::getInstance()->getElaIcon( ElaIconType::CameraPolaroid ) )
DEFINE_BASE_WHATS_THIS(ElaComboBox, "ElaComboBox on ElaWidgetTools")
DEFINE_BASE_IS_CONTAINER(ElaComboBox, false )

QString ElaComboBoxPlugin::domXml() const
{
    QString className = QStringLiteral("ElaComboBox");
    return createWidgetXml( className, className.toLower(), QSize( 100, 22 ) );
}

///////////////////////////////////////////////////////////////////////////////
///

DEFINE_BASE(ElaCentralStackedWidget)
DEFINE_BASE_ICON( ElaCentralStackedWidget, ElaIcon::getInstance()->getElaIcon( ElaIconType::BoxesStacked ) )
DEFINE_BASE_WHATS_THIS(ElaCentralStackedWidget, "ElaCentralStackedWidget on ElaWidgetTools")
DEFINE_BASE_IS_CONTAINER(ElaCentralStackedWidget, true )

QString ElaCentralStackedWidgetPlugin::domXml() const
{
    QString className = QStringLiteral("ElaCentralStackedWidget");
    return createWidgetXml( className, className.toLower(), QSize( 100, 22 ) );
}

///////////////////////////////////////////////////////////////////////////////
///

DEFINE_BASE(ElaDockWidget)
DEFINE_BASE_ICON( ElaDockWidget, QStringLiteral(":res/TreeView.png") )
DEFINE_BASE_WHATS_THIS(ElaDockWidget, "ElaDockWidget on ElaWidgetTools")
DEFINE_BASE_IS_CONTAINER(ElaDockWidget, true )

QString ElaDockWidgetPlugin::domXml() const
{
    QString className = QStringLiteral("ElaDockWidget");
    return createWidgetXml( className, className.toLower(), QSize( 200, 200 ) );
}

///////////////////////////////////////////////////////////////////////////////
///

DEFINE_BASE(ElaDoubleSpinBox)
DEFINE_BASE_ICON( ElaDoubleSpinBox, QStringLiteral(":res/TreeView.png") )
DEFINE_BASE_WHATS_THIS(ElaDoubleSpinBox, "ElaDoubleSpinBox on ElaWidgetTools")
DEFINE_BASE_IS_CONTAINER(ElaDoubleSpinBox, false )

QString ElaDoubleSpinBoxPlugin::domXml() const
{
    QString className = QStringLiteral("ElaDoubleSpinBox");
    return createWidgetXml( className, className.toLower(), QSize( 120, 30 ) );
}

///////////////////////////////////////////////////////////////////////////////
///

DEFINE_BASE(ElaFrame)
DEFINE_BASE_ICON( ElaFrame, QStringLiteral(":res/TreeView.png") )
DEFINE_BASE_WHATS_THIS(ElaFrame, "ElaFrame on ElaWidgetTools")
DEFINE_BASE_IS_CONTAINER(ElaFrame, true )

QString ElaFramePlugin::domXml() const
{
    QString className = QStringLiteral("ElaFrame");
    return createWidgetXml( className, className.toLower(), QSize( 200, 200 ) );
}

///////////////////////////////////////////////////////////////////////////////
///

DEFINE_BASE(ElaIconButton)
DEFINE_BASE_ICON( ElaIconButton, QStringLiteral(":res/TreeView.png") )
DEFINE_BASE_WHATS_THIS(ElaIconButton, "ElaIconButton on ElaWidgetTools")
DEFINE_BASE_IS_CONTAINER(ElaIconButton, false )

QString ElaIconButtonPlugin::domXml() const
{
    QString className = QStringLiteral("ElaIconButton");
    return createWidgetXml( className, className.toLower(), QSize( 32, 32 ) );
}

///////////////////////////////////////////////////////////////////////////////
///

DEFINE_BASE(ElaImageCard)
DEFINE_BASE_ICON( ElaImageCard, QStringLiteral(":res/TreeView.png") )
DEFINE_BASE_WHATS_THIS(ElaImageCard, "ElaImageCard on ElaWidgetTools")
DEFINE_BASE_IS_CONTAINER(ElaImageCard, false )

QString ElaImageCardPlugin::domXml() const
{
    QString className = QStringLiteral("ElaImageCard");
    return createWidgetXml( className, className.toLower(), QSize( 350, 260 ) );
}

///////////////////////////////////////////////////////////////////////////////
///

DEFINE_BASE(ElaInteractiveCard)
DEFINE_BASE_ICON( ElaInteractiveCard, QStringLiteral(":res/TreeView.png") )
DEFINE_BASE_WHATS_THIS(ElaInteractiveCard, "ElaInteractiveCard on ElaWidgetTools")
DEFINE_BASE_IS_CONTAINER(ElaInteractiveCard, false )

QString ElaInteractiveCardPlugin::domXml() const
{
    QString className = QStringLiteral("ElaInteractiveCard");
    return createWidgetXml( className, className.toLower(), QSize( 350, 260 ) );
}

///////////////////////////////////////////////////////////////////////////////
///

DEFINE_BASE(ElaLCDNumber)
DEFINE_BASE_ICON( ElaLCDNumber, QStringLiteral(":res/TreeView.png") )
DEFINE_BASE_WHATS_THIS(ElaLCDNumber, "ElaLCDNumber on ElaWidgetTools")
DEFINE_BASE_IS_CONTAINER(ElaLCDNumber, false )

QString ElaLCDNumberPlugin::domXml() const
{
    QString className = QStringLiteral("ElaLCDNumber");
    return createWidgetXml( className, className.toLower(), QSize( 120, 20 ) );
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
    return createWidgetXml( className, className.toLower(), QSize( 120, 20 ) );
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
    return createWidgetXml( className, className.toLower(), QSize( 300, 200 ) );
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
    return createWidgetXml( className, className.toLower(), QSize( 300, 200 ) );
}

///////////////////////////////////////////////////////////////////////////////
///

DEFINE_BASE(ElaMessageButton)
DEFINE_BASE_ICON( ElaMessageButton, QStringLiteral(":res/TreeView.png") )
DEFINE_BASE_WHATS_THIS(ElaMessageButton, "ElaMessageButton on ElaWidgetTools")
DEFINE_BASE_IS_CONTAINER(ElaMessageButton, false )

QString ElaMessageButtonPlugin::domXml() const
{
    QString className = QStringLiteral("ElaMessageButton");
    return createWidgetXml( className, className.toLower(), QSize( 80, 38 ) );
}

///////////////////////////////////////////////////////////////////////////////
///

DEFINE_BASE(ElaMultiSelectComboBox)
DEFINE_BASE_ICON( ElaMultiSelectComboBox, QStringLiteral(":res/TreeView.png") )
DEFINE_BASE_WHATS_THIS(ElaMultiSelectComboBox, "ElaMultiSelectComboBox on ElaWidgetTools")
DEFINE_BASE_IS_CONTAINER(ElaMultiSelectComboBox, false )

QString ElaMultiSelectComboBoxPlugin::domXml() const
{
    QString className = QStringLiteral("ElaMultiSelectComboBox");
    return createWidgetXml( className, className.toLower(), QSize( 140, 36 ) );
}

///////////////////////////////////////////////////////////////////////////////
///

DEFINE_BASE(ElaPivot)
DEFINE_BASE_ICON( ElaPivot, QStringLiteral(":res/TreeView.png") )
DEFINE_BASE_WHATS_THIS(ElaPivot, "ElaPivot on ElaWidgetTools")
DEFINE_BASE_IS_CONTAINER(ElaPivot, false )

QString ElaPivotPlugin::domXml() const
{
    QString className = QStringLiteral("ElaPivot");
    return createWidgetXml( className, className.toLower(), QSize( 300, 40 ) );
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
    return createWidgetXml( className, className.toLower(), QSize( 150, 36 ) );
}

///////////////////////////////////////////////////////////////////////////////
///

DEFINE_BASE(ElaPopularCard)
DEFINE_BASE_ICON( ElaPopularCard, QStringLiteral(":res/TreeView.png") )
DEFINE_BASE_WHATS_THIS(ElaPopularCard, "ElaPopularCard on ElaWidgetTools")
DEFINE_BASE_IS_CONTAINER(ElaPopularCard, false )

QString ElaPopularCardPlugin::domXml() const
{
    QString className = QStringLiteral("ElaPopularCard");
    return createWidgetXml( className, className.toLower(), QSize( 300, 200 ) );
}

///////////////////////////////////////////////////////////////////////////////
///

DEFINE_BASE(ElaProgressBar)
DEFINE_BASE_ICON( ElaProgressBar, QStringLiteral(":res/TreeView.png") )
DEFINE_BASE_WHATS_THIS(ElaProgressBar, "ElaProgresBar on ElaWidgetTools")
DEFINE_BASE_IS_CONTAINER(ElaProgressBar, false )

QString ElaProgressBarPlugin::domXml() const
{
    QString className = QStringLiteral("ElaProgressBar");
    return createWidgetXml( className, className.toLower(), QSize( 150, 16 ) );
}

///////////////////////////////////////////////////////////////////////////////
///

DEFINE_BASE(ElaProgressRing)
DEFINE_BASE_ICON( ElaProgressRing, QStringLiteral(":res/TreeView.png") )
DEFINE_BASE_WHATS_THIS(ElaProgressRing, "ElaProgressRing on ElaWidgetTools")
DEFINE_BASE_IS_CONTAINER(ElaProgressRing, false )

QString ElaProgressRingPlugin::domXml() const
{
    QString className = QStringLiteral("ElaProgressRing");
    return createWidgetXml( className, className.toLower(), QSize( 70, 70 ) );
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
    return createWidgetXml( className, className.toLower(), QSize( 80, 38 ) );
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
    return createWidgetXml( className, className.toLower(), QSize( 120, 38 ) );
}

///////////////////////////////////////////////////////////////////////////////
///

DEFINE_BASE(ElaReminderCard)
DEFINE_BASE_ICON( ElaReminderCard, QStringLiteral(":res/TreeView.png") )
DEFINE_BASE_WHATS_THIS(ElaReminderCard, "ElaReminderCard on ElaWidgetTools")
DEFINE_BASE_IS_CONTAINER(ElaReminderCard, false )

QString ElaReminderCardPlugin::domXml() const
{
    QString className = QStringLiteral("ElaReminderCard");
    return createWidgetXml( className, className.toLower(), QSize( 300, 200 ) );
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
    return createWidgetXml( className, className.toLower(), QSize( 80, 60 ) );
}

///////////////////////////////////////////////////////////////////////////////
///

DEFINE_BASE(ElaScrollArea)
DEFINE_BASE_ICON( ElaScrollArea, QStringLiteral(":res/TreeView.png") )
DEFINE_BASE_WHATS_THIS(ElaScrollArea, "ElaScrollArea on ElaWidgetTools")
DEFINE_BASE_IS_CONTAINER(ElaScrollArea, false )

QString ElaScrollAreaPlugin::domXml() const
{
    QString className = QStringLiteral("ElaScrollArea");
    return createWidgetXml( className, className.toLower(), QSize( 300, 200 ) );
}

///////////////////////////////////////////////////////////////////////////////
///

DEFINE_BASE(ElaScrollPageArea)
DEFINE_BASE_ICON( ElaScrollPageArea, QStringLiteral(":res/TreeView.png") )
DEFINE_BASE_WHATS_THIS(ElaScrollPageArea, "ElaScrollPageArea on ElaWidgetTools")
DEFINE_BASE_IS_CONTAINER(ElaScrollPageArea, false )

QString ElaScrollPageAreaPlugin::domXml() const
{
    QString className = QStringLiteral("ElaScrollPageArea");
    return createWidgetXml( className, className.toLower(), QSize( 300, 200 ) );
}

///////////////////////////////////////////////////////////////////////////////
///

DEFINE_BASE(ElaSlider)
DEFINE_BASE_ICON( ElaSlider, QStringLiteral(":res/TreeView.png") )
DEFINE_BASE_WHATS_THIS(ElaSlider, "ElaSlider on ElaWidgetTools")
DEFINE_BASE_IS_CONTAINER(ElaSlider, false )

QString ElaSliderPlugin::domXml() const
{
    QString className = QStringLiteral("ElaSlider");
    return createWidgetXml( className, className.toLower(), QSize( 150, 16 ) );
}

///////////////////////////////////////////////////////////////////////////////
///

DEFINE_BASE(ElaSpinBox)
DEFINE_BASE_ICON( ElaSpinBox, QStringLiteral(":res/TreeView.png") )
DEFINE_BASE_WHATS_THIS(ElaSpinBox, "ElaSpinBox on ElaWidgetTools")
DEFINE_BASE_IS_CONTAINER(ElaSpinBox, false )

QString ElaSpinBoxPlugin::domXml() const
{
    QString className = QStringLiteral("ElaSpinBox");
    return createWidgetXml( className, className.toLower(), QSize( 120, 30 ) );
}

///////////////////////////////////////////////////////////////////////////////
///

DEFINE_BASE(ElaSuggestBox)
DEFINE_BASE_ICON( ElaSuggestBox, QStringLiteral(":res/TreeView.png") )
DEFINE_BASE_WHATS_THIS(ElaSuggestBox, "ElaSuggestBox on ElaWidgetTools")
DEFINE_BASE_IS_CONTAINER(ElaSuggestBox, false )

QString ElaSuggestBoxPlugin::domXml() const
{
    QString className = QStringLiteral("ElaSuggestBox");
    return createWidgetXml( className, className.toLower(), QSize( 120, 30 ) );
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
    return createWidgetXml( className, className.toLower(), QSize( 150, 30 ) );
}

///////////////////////////////////////////////////////////////////////////////
///

DEFINE_BASE(ElaTableView)
DEFINE_BASE_ICON( ElaTableView, ElaIcon::getInstance()->getElaIcon( ElaIconType::Table ) )
DEFINE_BASE_WHATS_THIS(ElaTableView, "ElaTableView on ElaWidgetTools")
DEFINE_BASE_IS_CONTAINER(ElaTableView, false )

QString ElaTableViewPlugin::domXml() const
{
    QString className = QStringLiteral("ElaTableView");
    return createWidgetXml( className, className.toLower(), QSize( 300, 200 ) );
}

///////////////////////////////////////////////////////////////////////////////
///

DEFINE_BASE(ElaTableWidget)
DEFINE_BASE_ICON( ElaTableWidget, ElaIcon::getInstance()->getElaIcon( ElaIconType::Table ) )
DEFINE_BASE_WHATS_THIS(ElaTableWidget, "ElaTableWidget on ElaWidgetTools")
DEFINE_BASE_IS_CONTAINER(ElaTableWidget, false )

QString ElaTableWidgetPlugin::domXml() const
{
    QString className = QStringLiteral("ElaTableWidget");
    return createWidgetXml( className, className.toLower(), QSize( 300, 200 ) );
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
    return createWidgetXml( className, className.toLower(), QSize( 300, 200 ) );
}

///////////////////////////////////////////////////////////////////////////////
///

DEFINE_BASE(ElaText)
DEFINE_BASE_ICON( ElaText, ElaIcon::getInstance()->getElaIcon( ElaIconType::Text ) )
DEFINE_BASE_WHATS_THIS(ElaText, "ElaText on ElaWidgetTools")
DEFINE_BASE_IS_CONTAINER(ElaText, false )

QString ElaTextPlugin::domXml() const
{
    QString className = QStringLiteral("ElaText");
    return createWidgetXml( className, className.toLower(), QSize( 100, 30 ) );
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
    return createWidgetXml( className, className.toLower(), QSize( 80, 30 ) );
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
    return createWidgetXml( className, className.toLower(), QSize( 80, 30 ) );
}

///////////////////////////////////////////////////////////////////////////////
///

DEFINE_BASE(ElaToolBar)
DEFINE_BASE_ICON( ElaToolBar, ElaIcon::getInstance()->getElaIcon( ElaIconType::ListTree ) )
DEFINE_BASE_WHATS_THIS(ElaToolBar, "ElaToolBar on ElaWidgetTools")
DEFINE_BASE_IS_CONTAINER(ElaToolBar, true )

QString ElaToolBarPlugin::domXml() const
{
    QString className = QStringLiteral("ElaToolBar");
    return createWidgetXml( className, className.toLower(), QSize( 120, 30 ) );
}

///////////////////////////////////////////////////////////////////////////////
///

DEFINE_BASE(ElaToolButton)
DEFINE_BASE_ICON( ElaToolButton, ElaIcon::getInstance()->getElaIcon( ElaIconType::ListTree ) )
DEFINE_BASE_WHATS_THIS(ElaToolButton, "ElaToolButton on ElaWidgetTools")
DEFINE_BASE_IS_CONTAINER(ElaToolButton, false )

QString ElaToolButtonPlugin::domXml() const
{
    QString className = QStringLiteral("ElaToolButton");
    return createWidgetXml( className, className.toLower(), QSize( 80, 30 ) );
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
    return createWidgetXml( className, className.toLower(), QSize( 300, 200 ) );
}

///////////////////////////////////////////////////////////////////////////////
///

DEFINE_BASE(ElaTreeWidget)
DEFINE_BASE_ICON( ElaTreeWidget, ElaIcon::getInstance()->getElaIcon( ElaIconType::ListTree ) )
DEFINE_BASE_WHATS_THIS(ElaTreeWidget, "ElaTreeWidget on ElaWidgetTools")
DEFINE_BASE_IS_CONTAINER(ElaTreeWidget, false )

QString ElaTreeWidgetPlugin::domXml() const
{
    QString className = QStringLiteral("ElaTreeWidget");
    return createWidgetXml( className, className.toLower(), QSize( 300, 200 ) );
}

///////////////////////////////////////////////////////////////////////////////
///

DEFINE_BASE(ElaWidget)
DEFINE_BASE_ICON( ElaWidget, ElaIcon::getInstance()->getElaIcon( ElaIconType::ListTree ) )
DEFINE_BASE_WHATS_THIS(ElaWidget, "ElaWidget on ElaWidgetTools")
DEFINE_BASE_IS_CONTAINER(ElaWidget, true )

QString ElaWidgetPlugin::domXml() const
{
    QString className = QStringLiteral("ElaWidget");
    return createWidgetXml( className, className.toLower(), QSize( 300, 200 ) );
}

///////////////////////////////////////////////////////////////////////////////
///

DEFINE_BASE(ElaWindow)
DEFINE_BASE_ICON( ElaWindow, ElaIcon::getInstance()->getElaIcon( ElaIconType::ListTree ) )
DEFINE_BASE_WHATS_THIS(ElaWindow, "ElaWindow on ElaWidgetTools")
DEFINE_BASE_IS_CONTAINER(ElaWindow, true )

QString ElaWindowPlugin::domXml() const
{
    QString className = QStringLiteral("ElaWindow");
    return QStringLiteral(
            R"(
<ui language="c++" version="4.0">
    <author></author>
    <comment></comment>
    <exportmacro></exportmacro>
    <class>ElaWindow</class>
    <widget class="%1" name="elawindow" >
        <property name="geometry" >
            <rect>
                <x>0</x>
                <y>0</y>
                <width>800</width>
                <height>600</height>
            </rect>
        </property>
        <property name="windowTitle" >
            <string>ElaWindow</string>
        </property>
        <widget class="ElaMenuBar" name="menubar" />
        <widget class="ElaWidget" name="centralwidget" />
        <widget class="ElaStatusBar" name="statusbar" />
    </widget>
    <pixmapfunction></pixmapfunction>
    <connections/>
</ui>
)").arg( className );
}
