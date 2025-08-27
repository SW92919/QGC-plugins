#include "version_compatibility.h"
#include <QVersionNumber>
#include <QDebug>
#include <QCoreApplication>

// Static member initialization
bool VersionCompatibility::m_initialized=false;
QString VersionCompatibility::m_cachedVersion=QString();
int VersionCompatibility::m_majorVersion=0;
int VersionCompatibility::m_minorVersion=0;
int VersionCompatibility::m_patchVersion=0;

void VersionCompatibility::initialize()
{
    if (m_initialized)
    {
        return;
    }

    m_cachedVersion=detectQGCVersion();
    parseVersion(m_cachedVersion);
    m_initialized=true;

    qDebug()<< "Version Compatibility initialized for QGC version:" <<m_cachedVersion;
    qDebug()<< "Is QGC 5.0+ compatible:"<<isQGC5Plus();
}

bool VersionCompatibility::isInitialized()
{
    return m_initialized;
}



bool VersionCompatibility::isCompatible(const QString &currentVersion, const QString &requiredVersion)
{
    QVersionNumber current=QVersionNumber::fromString(currentVersion);
    QVersionNumber required=QVersionNumber::fromString(requiredVersion);
    return current>=required;
}

QString VersionCompatibility::getCurrentQGCVersion()
{
    if (!m_initialized)
    {
        initialize();
    }
    return m_cachedVersion;
}

QString VersionCompatibility::detectQGCVersion()
{
    // Method 1: Try to get from compile-time defines
#ifdef QGC_VERSION_MAJOR
    #ifdef QGC_VERSION_MINOR
        #ifdef QGC_VERSION_PATCH
            return QString("%1.%2.%3").arg(QGC_VERSION_MAJOR).arg(QGC_VERSION_MINOR).arg(QGC_VERSION_PATCH);
        #else
            return QString("%1.%2.0").arg(QGC_VERSION_MAJOR).arg(QGC_VERSION_MINOR);
        #endif
    #else
        return QString("%1.0.0").arg(QGC_VERSION_MAJOR);
    #endif
#endif
    // Method 2: Try to get from QGC runtime (if available)
    // this would need actual QGC API integration
    // For now, we'll use a default compatible version

    // Method 3: Environment variable fallback
    QString envVersion=qEnvironmentVariable("QGC_VERSION");
    if(!envVersion.isEmpty())
    {
        return envVersion;
    }

    // Method 4: Default to minimum compatible version
    qWarning()<<"Could not detect QGC version, defaulting to 5.0.0";
    return "5.0.0";
}

void VersionCompatibility::parseVersion(const QString &version)
{
    QVersionNumber versionNumber=QVersionNumber::fromString(version);
    m_majorVersion=versionNumber.majorVersion();
    m_minorVersion=versionNumber.minorVersion();
    m_patchVersion=versionNumber.microVersion();
}

bool VersionCompatibility::checkMinimumVersion(const QString &minimumVersion)
{
    return isCompatible(getCurrentQGCVersion(), minimumVersion);
}

bool VersionCompatibility::isQGC5Plus()
{
    if (!m_initialized)
    {
        initialize();
    }
    return m_majorVersion>=5;
}

int VersionCompatibility::getMajorVersion()
{
    if (!m_initialized)
    {
        initialize();
    }
    return m_majorVersion;
}

int VersionCompatibility::getMinorVersion()
{
    if (!m_initialized)
    {
        initialize();
    }
    return m_minorVersion;
}

int VersionCompatibility::getPatchVersion()
{
    if(!m_initialized)
    {
        initialize();
    }
    return m_patchVersion;
}

bool VersionCompatibility::isPluginCompatible()
{
    if (!isQGC5Plus())
    {
        qWarning()<<"Plugin requires QGC 5.0+, current version:"<<getCurrentQGCVersion();
        return false;
    }
    return true;
}

QString VersionCompatibility::getCompatibilityReport()
{
    if(!m_initialized)
    {
        initialize();
    }

    QString report;
    report+=QString("QGC Version: %1\n").arg(m_cachedVersion);
    report+=QString("Major: %1, Minor: %2, Patch: %3\n").arg(m_majorVersion).arg(m_minorVersion).arg(m_patchVersion);
    report+=QString("QGC 5.0+ Compatible: %1\n").arg(isQGC5Plus()?"Yes":"No");
    report+=QString("Plugin Compatible: %1\n").arg(isPluginCompatible()?"Yes":"No");

    return report;
}
