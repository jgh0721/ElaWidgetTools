#include "ElaApplication.h"

#include "ElaTheme.h"
#include "ElaWinShadowHelper.h"
#include "private/ElaApplicationPrivate.h"
#include <QApplication>
#include <QCursor>
#include <QFile>
#include <QFontDatabase>
#include <QMetaEnum>
#include <QSettings>
#include <QWidget>
#include <QTranslator>
#include <utility>

Q_SINGLETON_CREATE_CPP(ElaApplication)
ElaApplication::ElaApplication(QObject* parent)
    : QObject{parent}, d_ptr(new ElaApplicationPrivate())
{
    Q_D(ElaApplication);
    d->q_ptr = this;
    d->_pElaMicaImagePath = ":/include/Image/MicaBase.png";
    d->_pWindowDisplayMode = ElaApplicationType::Normal;
    d->_themeMode = eTheme->getThemeMode();
    connect(eTheme, &ElaTheme::themeModeChanged, d, &ElaApplicationPrivate::onThemeModeChanged);
}

ElaApplication::~ElaApplication()
{
}

void ElaApplication::setWindowDisplayMode(ElaApplicationType::WindowDisplayMode windowDisplayType)
{
    Q_D(ElaApplication);
    auto lastDisplayMode = d->_pWindowDisplayMode;
    if (lastDisplayMode == windowDisplayType)
    {
        return;
    }
    if (lastDisplayMode == ElaApplicationType::ElaMica)
    {
        d->_resetAllMicaWidget();
    }
    switch (windowDisplayType)
    {
    case ElaApplicationType::Normal:
    {
        break;
    }
    case ElaApplicationType::ElaMica:
    {
        d->_pWindowDisplayMode = windowDisplayType;
        d->_initMicaBaseImage(QImage(d->_pElaMicaImagePath));
        break;
    }
    default:
    {
        break;
    }
    }
#ifdef Q_OS_WIN
    for (auto widget: d->_micaWidgetList)
    {
        ElaWinShadowHelper::getInstance()->setWindowDisplayMode(widget, windowDisplayType, lastDisplayMode);
        ElaWinShadowHelper::getInstance()->setWindowThemeMode(widget->winId(), d->_themeMode == ElaThemeType::Light);
    }
#endif
    if (windowDisplayType != ElaApplicationType::ElaMica)
    {
        d->_pWindowDisplayMode = windowDisplayType;
        Q_EMIT pWindowDisplayModeChanged();
    }
}

ElaApplicationType::WindowDisplayMode ElaApplication::getWindowDisplayMode() const
{
    Q_D(const ElaApplication);
    return d->_pWindowDisplayMode;
}

void ElaApplication::setElaMicaImagePath(QString micaImagePath)
{
    Q_D(ElaApplication);
    d->_pElaMicaImagePath = std::move(micaImagePath);
    d->_initMicaBaseImage(QImage(d->_pElaMicaImagePath));
    Q_EMIT pElaMicaImagePathChanged();
}

QString ElaApplication::getElaMicaImagePath() const
{
    Q_D(const ElaApplication);
    return d->_pElaMicaImagePath;
}

void ElaApplication::init( const QString& ConfigFilePath, bool IsPlugin )
{
    Q_INIT_RESOURCE(ElaWidgetTools);
    if(IsPlugin == false)
        QApplication::setAttribute(Qt::AA_DontCreateNativeWidgetSiblings);
    QFontDatabase::addApplicationFont(":/include/Font/ElaAwesome.ttf");
    //默认字体
    if( QFile::exists( ":/translations/ElaWidgetTools_ko.qm" ) == true )
    {
        if( ko == nullptr )
        {
            ko = new QTranslator;
            ko->load( QLocale::Korean, ":/translations/ElaWidgetTools_ko.qm" );
        }
    }

    if( QFile::exists( ":/translations/ElaWidgetTools_en.qm" ) == true )
    {
        en = new QTranslator();
        en->load( QLocale::English, ":/translations/ElaWidgetTools_en.qm" );
    }

    int Theme = -1;
    const auto ThemeColorEnum = QMetaEnum::fromType<ElaThemeType::ThemeColor>();

    QFont font = qApp->font();

    if( QFile::exists( ConfigFilePath ) == true )
    {
        QSettings Settings( ConfigFilePath, QSettings::IniFormat );
        Settings.beginGroup( "Common" );
        const auto Font = Settings.value("Font", "Microsoft YaHei" ).toString();
        const auto FontSize = Settings.value("FontSize", 13 ).toInt();
        const auto Th = Settings.value("Apply", "Auto" );

        if( Th.isValid() == true && Th.toString().compare( "Light", Qt::CaseInsensitive ) == 0 )
            Theme = ElaThemeType::Light;
        if( Th.isValid() == true && Th.toString().compare( "Dark", Qt::CaseInsensitive ) == 0 )
            Theme = ElaThemeType::Dark;
        if( Th.isValid() == false )
            Settings.setValue( "Apply", "Auto" );
        Settings.endGroup();

        const auto pfnApplyThemeColor = [&Settings, ThemeColorEnum]( const QString& Section, ElaThemeType::ThemeMode Mode ) {
            Settings.beginGroup( Section );
            for( int idx = 0; idx < ThemeColorEnum.keyCount(); ++idx )
            {
                const auto Key = ThemeColorEnum.key( idx );
                if( Key == nullptr )
                    continue;

                const auto En = static_cast<ElaThemeType::ThemeColor>( ThemeColorEnum.keyToValue( Key ) );
                const auto Value = QColor::fromString( Settings.value( Key ).toString() );
                if( Value.isValid() == false )
                {
                    Settings.setValue( Key, eTheme->getThemeColor( Mode, En ).name( QColor::HexRgb ) );
                    continue;
                }

                eTheme->setThemeColor( Mode, En, Value );
            }
            Settings.endGroup();
        };

        pfnApplyThemeColor( "Light", ElaThemeType::Light );
        pfnApplyThemeColor( "Dark", ElaThemeType::Dark );

        font.setFamily( Font );
        font.setPixelSize( FontSize );
        font.setHintingPreference( QFont::PreferFullHinting );
    }
    else
    {
        font.setPixelSize(13);
        font.setFamily("Microsoft YaHei");
        font.setHintingPreference(QFont::PreferNoHinting);
    }

    eTheme->setFontFamily( font.family() );
    eTheme->setFontSize( font.pixelSize() );

    qApp->setFont(font);
#ifdef Q_OS_WIN
    eWinHelper->initWinAPI();
#endif
    if( Theme >= 0 )
        eTheme->setThemeMode( static_cast<ElaThemeType::ThemeMode>(Theme) );
}

void ElaApplication::syncWindowDisplayMode(QWidget* widget, bool isSync)
{
    Q_D(ElaApplication);
    if (!widget)
    {
        return;
    }
    if (isSync)
    {
        d->_micaWidgetList.append(widget);
        widget->installEventFilter(d);
    }
    else
    {
        d->_micaWidgetList.removeOne(widget);
        widget->removeEventFilter(d);
    }
    switch (d->_pWindowDisplayMode)
    {
    case ElaApplicationType::Normal:
    case ElaApplicationType::ElaMica:
    {
        if (isSync)
        {
            if (d->_pWindowDisplayMode == ElaApplicationType::WindowDisplayMode::ElaMica)
            {
                d->_updateMica(widget, false);
            }
        }
        break;
    }
    default:
    {
#ifdef Q_OS_WIN
        if (isSync)
        {
            ElaWinShadowHelper::getInstance()->setWindowDisplayMode(widget, d->_pWindowDisplayMode, ElaApplicationType::Normal);
            ElaWinShadowHelper::getInstance()->setWindowThemeMode(widget->winId(), d->_themeMode == ElaThemeType::Light);
        }
        else
        {
            ElaWinShadowHelper::getInstance()->setWindowDisplayMode(widget, ElaApplicationType::Normal, d->_pWindowDisplayMode);
            ElaWinShadowHelper::getInstance()->setWindowThemeMode(widget->winId(), true);
        }
#endif
        break;
    }
    }
}

bool ElaApplication::containsCursorToItem(QWidget* item)
{
    if (!item || !item->isVisible())
    {
        return false;
    }
    auto itemRect = QRect(item->mapToGlobal(QPoint(0, 0)), item->size());
    if (itemRect.contains(QCursor::pos()))
    {
        return true;
    }
    return false;
}

void ElaApplication::switchLanguageTo( const QString& Lang )
{
    if( Lang.compare( "ko", Qt::CaseInsensitive ) == 0 ||
        Lang.compare( "korea", Qt::CaseInsensitive ) == 0 ||
        Lang.compare( "korean", Qt::CaseInsensitive ) == 0 )
    {
        if( en != nullptr )
            qApp->removeTranslator(en);

        if( ko != nullptr && ko->isEmpty() == false )
            qApp->installTranslator( ko );
    }

    if( Lang.compare( "en", Qt::CaseInsensitive ) == 0 ||
        Lang.compare( "english", Qt::CaseInsensitive ) == 0 )
    {
        if( ko != nullptr )
            qApp->removeTranslator(ko);

        if( en != nullptr && en->isEmpty() == false )
            qApp->installTranslator( en );
    }
}
