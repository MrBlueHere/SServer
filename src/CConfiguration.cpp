/**
* @author Ladislav Floriš
* @date 05.05.20
*/

#include "CConfiguration.h"
#include <sstream>
#include <cmath>
#include <fstream>
#include <cstdlib>

using namespace std;

const set<std::string> CConfiguration::m_validParameters =
        {"IPAddress", "UseIPv6", "Port", "ShutdownUrl", "MaxConnections", "LogType", "LogLevel", "LogFormat", "HeaderOnly", "LogFile", "ServerDirectory"};

/// Default constructor with default config settings
CConfiguration::CConfiguration()
: m_ipAddress("127.0.0.1"), m_useIPv6(false), m_port(8080), m_shutdownUrl("/shutdown"), m_maxConnections(10),
m_logType(Console), m_logLevel(Info), m_logFormat("[@logLevel@] | received:@time@ | @message@"), m_headersOnly(false), m_logFile("log.txt"),
m_serverDirectory("examples")
{ }

void CConfiguration::ReadConfigurationFromFile(const std::string &configFilePath) {
    ifstream configFile;
    configFile.open(configFilePath);
    if (!configFile.is_open())
        throw runtime_error("Could not open config file");

    string line;
    size_t position = 0;
    char delimiter = '=';
    char comment = '#';

    string arg, val;
    while(getline(configFile, line))
    {
        // If this is a comment
        if (line.find(comment) == 0)
            continue;

        // Is a blank line
        if(line.find_first_not_of(' ') == string::npos)
            continue;

        position = line.find(delimiter);
        arg = line.substr(0, position);

        // Check if argument is valid
        auto search = m_validParameters.find(arg);
        if (search == m_validParameters.end())
            throw runtime_error("Config file doesn't have a correct format");

        val = line.substr(position + 1, line.length());

        SetConfigParam(arg, val);
    }
}

void CConfiguration::SetConfigParam(const string &arg, string &val) {
    if (arg == "IPAddress") {
        m_ipAddress = val;
        return;
    }
    else if (arg == "Port") {
        char * p;
        int converted = strtol(val.c_str(), &p, 10);
        if (!*p) {
            m_port = converted;
            return;
        }
    }
    else if (arg == "ShutdownUrl") {
        m_shutdownUrl = val;
        return;
    }
    else if (arg == "MaxConnections") {
        char * p;
        int converted = strtol(val.c_str(), &p, 10);
        if (!*p) {
            m_maxConnections = converted;
            return;
        }
    }
    else if (arg == "LogType") {
        if (val == LogTypeToString(Console) || val == LogTypeToString(File)) {
            m_logType = StringToLogType(val);
            return;
        }
    }
    else if (arg == "LogLevel") {
        if (val == LogLevelToString(Info) || val == LogLevelToString(Warn) || val == LogLevelToString(Error)) {
            m_logLevel = StringToLogLevel(val);
            return;
        }
    }
    else if (arg == "LogFormat") {
        m_logFormat = val;
        return;
    }
    else if (arg == "HeaderOnly") {
        if (val == "true") {
            m_headersOnly = true;
            return;
        }
        else if (val == "false") {
            m_headersOnly = false;
            return;
        }
    }
    else if (arg == "LogFile") {
        m_logFile = val;
        return;
    }
    else if (arg == "ServerDirectory") {
        m_serverDirectory = val;
        return;
    }
    else if (arg == "UseIPv6") {
        if (val == "true") {
            m_useIPv6 = true;
            return;
        }
        else if (val == "false") {
            m_useIPv6 = false;
            return;
        }
    }

    stringstream oss;
    oss << "Invalid value: " << val << " for parameter: " << arg;
    string var = oss.str();
    throw runtime_error(var);
}
