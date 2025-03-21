#ifndef ELAWIDGETTOOLSDESIGNER_HPP
#define ELAWIDGETTOOLSDESIGNER_HPP

#include <QtUiPlugin/QDesignerCustomWidgetInterface>

///////////////////////////////////////////////////////////////////////////////
///

class ElaWidgetToolsDesignerPlugin : public QObject,
                                     public QDesignerCustomWidgetCollectionInterface
{
    Q_OBJECT
    Q_INTERFACES(QDesignerCustomWidgetCollectionInterface)
#if (QT_VERSION >= QT_VERSION_CHECK(5, 0, 0))
    Q_PLUGIN_METADATA(IID "org.qt-project.Qt.QDesignerCustomWidgetCollectionInterface")
#endif
public:
    ElaWidgetToolsDesignerPlugin(QObject *parent = nullptr);
    QList<QDesignerCustomWidgetInterface*> customWidgets() const;

private:
    QList<QDesignerCustomWidgetInterface *> m_extensions;
};

///////////////////////////////////////////////////////////////////////////////
///

#define DECLARE_ELAWIDGET_PLUGIN( Name )                        \
    class Name##Plugin : public QObject,                        \
                 public QDesignerCustomWidgetInterface          \
    {                                                           \
        Q_OBJECT                                                \
        Q_INTERFACES(QDesignerCustomWidgetInterface)            \
    public:                                                     \
        Name##Plugin(QObject *parent = 0);                      \
        bool isContainer() const;                               \
        bool isInitialized() const;                             \
        QIcon icon() const;                                     \
        QString domXml() const;                                 \
        QString group() const;                                  \
        QString includeFile() const;                            \
        QString name() const;                                   \
        QString toolTip() const;                                \
        QString whatsThis() const;                              \
        QWidget *createWidget(QWidget *parent);                 \
        void initialize(QDesignerFormEditorInterface *core);    \
    private:                                                    \
        bool                            initialized;            \
        QDesignerFormEditorInterface*   m_core;                 \
    }

#define DEFINE_BASE_CONSTRUCTOR( Name ) \
    Name##Plugin::Name##Plugin(QObject* Parent ) : QObject(Parent), m_core(0) { initialized = false; }
#define DEFINE_BASE_INITIALIZE( Name ) \
    void Name##Plugin::initialize(QDesignerFormEditorInterface* core) { if( initialized ) return; initialized = true; m_core = core; }
#define DEFINE_BASE_IS_INITIALIZE( Name ) \
    bool Name##Plugin::isInitialized() const { return initialized; }
#define DEFINE_BASE_NAME( Name ) \
    QString Name##Plugin::name() const { return QStringLiteral( #Name ); }
#define DEFINE_BASE_GROUP( Name ) \
    QString Name##Plugin::group() const { return QStringLiteral( "ElaWidgetTools" ); }
#define DEFINE_BASE_CREATE( Name ) \
    QWidget* Name##Plugin::createWidget(QWidget* Parent ) { return new Name(Parent); }
#define DEFINE_BASE_IS_CONTAINER( Name, Is ) \
    bool Name##Plugin::isContainer() const { return Is; }
#define DEFINE_BASE_WHATS_THIS( Name, Desc ) \
    QString Name##Plugin::whatsThis() const { return QStringLiteral( Desc ); }
#define DEFINE_BASE_TOOLTIP( Name ) \
    QString Name##Plugin::toolTip() const { return QStringLiteral( "class" #Name ); }
#define DEFINE_BASE_INCLUDE( Name ) \
    QString Name##Plugin::includeFile() const { return QStringLiteral( #Name ".h" ); }
#define DEFINE_BASE_ICON( Name, Icon ) \
    QIcon Name##Plugin::icon() const { return QIcon( Icon ); }
#define DEFINE_BASE_XML( Name, Value, Width, Height ) \
    QString Name##Plugin::domXml() const {                          \
        const auto ClassName = QStringLiteral( #Name );             \
    }

#define DEFINE_BASE(Name) \
    DEFINE_BASE_CONSTRUCTOR(Name)       \
    DEFINE_BASE_INITIALIZE(Name)        \
    DEFINE_BASE_IS_INITIALIZE(Name)     \
    DEFINE_BASE_NAME(Name)              \
    DEFINE_BASE_GROUP(Name)             \
    DEFINE_BASE_CREATE(Name)            \
    DEFINE_BASE_TOOLTIP(Name)           \
    DEFINE_BASE_INCLUDE(Name)

DECLARE_ELAWIDGET_PLUGIN( ElaAcrylicUrlCard );

DECLARE_ELAWIDGET_PLUGIN( ElaBreadcrumbBar );

DECLARE_ELAWIDGET_PLUGIN( ElaCalendarPicker );
DECLARE_ELAWIDGET_PLUGIN( ElaCheckBox );
DECLARE_ELAWIDGET_PLUGIN( ElaComboBox );

DECLARE_ELAWIDGET_PLUGIN( ElaLineEdit );
DECLARE_ELAWIDGET_PLUGIN( ElaListView );
DECLARE_ELAWIDGET_PLUGIN( ElaListWidget );

DECLARE_ELAWIDGET_PLUGIN( ElaTableView );
DECLARE_ELAWIDGET_PLUGIN( ElaTableWidget );
DECLARE_ELAWIDGET_PLUGIN( ElaToggleButton );
DECLARE_ELAWIDGET_PLUGIN( ElaToggleSwitch );
DECLARE_ELAWIDGET_PLUGIN( ElaTreeView );

#endif //ELAWIDGETTOOLSDESIGNER_HPP
