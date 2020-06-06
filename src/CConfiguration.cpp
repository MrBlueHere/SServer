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

/// TODO: Support IPv6
unsigned int CConfiguration::IpAddressFromString(const std::string & addr) const {
    istringstream stream;
    stream.str(addr);

    unsigned int result = 0;
    unsigned int power = 0;

    while(stream.good())
    {
        string substr;
        getline(stream, substr, '.' );
        int num = stoi(substr, nullptr, 10);
        result += (unsigned  int)(num * pow(2, power));
        power += 8;
    }
    return result;
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

    stringstream oss;
    oss << "Invalid value: " << val << " for parameter: " << arg;
    string var = oss.str();
    throw runtime_error(var);
}
