#pragma once
#include <QString>

#ifdef FRAMEWORK_EXPORTS
#define FRAMEWORK_EXPORT Q_DECL_EXPORT
#else
#define FRAMEWFRAMEWORK_EXPORTS Q_DECL_IMPORT
#endif

class FRAMEWORK_EXPORT VersionCompatibility
{
public:
    // Version checking methods
    static bool isCompatible(const QString &currentVersion, const QString &requiredVersion);
    static QString getCurrentQGCVersion();
    static bool checkMinimumVersion(const QString &minimumVersion="5.0.0");

    // New methods for compatibility
    static bool isQGC5Plus();
    static int getMajorVersion();
    static int getMinorVersion();
    static int getPatchVersion();

    // Plugin compatibility checking
    static bool isPluginCompatible();
    static QString getCompatibilityReport();

    // Runtime initialization
    static void initialize();
    static bool isInitialized();

private:
    static bool m_initialized;
    static QString m_cachedVersion;
    static int m_majorVersion;
    static int m_minorVersion;
    static int m_patchVersion;

    // Helper methods
    static void parseVersion(const QString &version);
    static QString detectQGCVersion();
};
