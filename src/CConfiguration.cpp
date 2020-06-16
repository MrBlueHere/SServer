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

CConfiguration::CConfiguration()
: m_ipAddress("127.0.0.1"), m_useIPv6(false), m_port(8080), m_maxConnections(10), m_logType(Console),
  m_validParameters( {"IPAddress", "UseIPv6", "Port", "ShutdownUrl", "MaxConnections", "LogType", "LogFile", "ServerDirectory"} )
{ }

void CConfiguration::ReadConfigurationFromFile(const std::string &configFilePath) {
    ifstream configFile;
    configFile.open(configFilePath);
    if (!configFile.is_open())
        throw runtime_error("Could not open config file");

    string line;
    size_t position = 0;
    string delimiter = "=";
    string arg, val;
    while(getline(configFile, line))
    {
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
