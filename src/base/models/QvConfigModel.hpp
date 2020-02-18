#pragma once
#include "3rdparty/x2struct/x2struct.hpp"
#include "base/models/CoreObjectModels.hpp"
#include "base/models/QvConfigIdentifier.hpp"
#include <chrono>

const int QV2RAY_CONFIG_VERSION = 9;

namespace Qv2ray::base::config
{
    struct QvBarLine {
        QString Family;
        bool Bold, Italic;
        int ColorA, ColorR, ColorG, ColorB;
        int ContentType;
        double Size;
        QString Message;
        QvBarLine(): Family("Consolas"), Bold(true), Italic(false), ColorA(255), ColorR(255), ColorG(255), ColorB(255),
            ContentType(0), Size(9), Message("") { }
        XTOSTRUCT(O(Bold, Italic, ColorA, ColorR, ColorG, ColorB, Size, Family, Message, ContentType))
    };

    struct QvBarPage {
        int OffsetYpx;
        QList<QvBarLine> Lines;
        QvBarPage(): OffsetYpx(5) { }
        XTOSTRUCT(O(OffsetYpx, Lines))
    };

    struct Qv2rayToolBarConfig {
        QList<QvBarPage> Pages;
        XTOSTRUCT(O(Pages))
    };

    struct Qv2rayPACConfig {
        bool enablePAC;
        int port;
        QString localIP;
        bool useSocksProxy;
        Qv2rayPACConfig(): enablePAC(false), port(8989), useSocksProxy(false) { }
        XTOSTRUCT(O(enablePAC, port, localIP, useSocksProxy))
    };

    struct Qv2rayForwardProxyConfig {
        bool enableForwardProxy;
        QString type;
        QString serverAddress;
        int port;
        bool useAuth;
        QString username;
        QString password;
        Qv2rayForwardProxyConfig(): enableForwardProxy(false), type("http"), serverAddress("127.0.0.1"), port(8008),
            useAuth(false), username(), password() { }
        XTOSTRUCT(O(enableForwardProxy, type, serverAddress, port, useAuth, username, password))
    };

    struct Qv2rayInboundsConfig {
        QString listenip;
        bool setSystemProxy;
        Qv2rayPACConfig pacConfig;

        // SOCKS
        bool useSocks;
        int socks_port;
        bool socks_useAuth;
        bool socksUDP;
        QString socksLocalIP;
        objects::AccountObject socksAccount;
        // HTTP
        bool useHTTP;
        int http_port;
        bool http_useAuth;
        objects::AccountObject httpAccount;

        Qv2rayInboundsConfig():
            listenip("127.0.0.1"), setSystemProxy(false), pacConfig(),
            useSocks(true), socks_port(1088), socks_useAuth(false), socksUDP(true), socksLocalIP("127.0.0.1"), socksAccount(),
            useHTTP(true), http_port(8888), http_useAuth(false), httpAccount() {}

        XTOSTRUCT(O(setSystemProxy, pacConfig, listenip, useSocks, useHTTP, socks_port, socks_useAuth, socksAccount, socksUDP, socksLocalIP, http_port, http_useAuth, httpAccount))
    };

    struct Qv2rayUIConfig {
        QString theme;
        QString language;
        bool useDarkTheme;
        bool useDarkTrayIcon;
        int maximumLogLines;
        Qv2rayUIConfig() : theme("Fusion"), language("en_US"), useDarkTheme(false), useDarkTrayIcon(true), maximumLogLines(500) { }
        XTOSTRUCT(O(theme, language, useDarkTheme, useDarkTrayIcon, maximumLogLines))
    };

    struct Qv2rayConnectionConfig {
        bool bypassCN;
        bool enableProxy;
        bool withLocalDNS;
        QList<QString> dnsList;
        Qv2rayForwardProxyConfig forwardProxyConfig;
        Qv2rayConnectionConfig() : bypassCN(true), enableProxy(true), withLocalDNS(false), dnsList(QStringList() << "8.8.4.4" << "1.1.1.1") { }
        XTOSTRUCT(O(bypassCN, enableProxy, withLocalDNS, dnsList, forwardProxyConfig))
    };

    struct Qv2rayAPIConfig {
        bool enableAPI;
        int statsPort;
        Qv2rayAPIConfig(): enableAPI(true), statsPort(15490) { }
        XTOSTRUCT(O(enableAPI, statsPort))
    };

    struct Qv2rayConfig {
        int config_version;
        bool tProxySupport;
        int logLevel;
        //
        QString v2CorePath;
        QString v2AssetsPath;
        QString ignoredVersion;
        QString autoStartId;
        //
        // Key = groupId, connectionId, subscriptionId
        QMap<QString, QvGroupObject> groups;
        QMap<QString, QvSubscriptionObject> subscriptions;
        /// Connections are used privately.
        QMap<QString, QvConnectionObject> connections;
        //
        Qv2rayUIConfig uiConfig;
        Qv2rayAPIConfig apiConfig;
        Qv2rayToolBarConfig toolBarConfig;
        Qv2rayInboundsConfig inboundConfig;
        Qv2rayConnectionConfig connectionConfig;

        Qv2rayConfig():
            config_version(QV2RAY_CONFIG_VERSION),
            tProxySupport(false),
            logLevel(),
            v2CorePath(),
            v2AssetsPath(),
            ignoredVersion(),
            groups(),
            subscriptions(),
            connections(),
            uiConfig(), apiConfig(), toolBarConfig(), inboundConfig(), connectionConfig() { }

        XTOSTRUCT(O(config_version, ignoredVersion,
                    tProxySupport,
                    logLevel, uiConfig,
                    v2CorePath, v2AssetsPath,
                    groups, connections, subscriptions,
                    autoStartId, inboundConfig, connectionConfig, toolBarConfig, apiConfig))
    };
}
