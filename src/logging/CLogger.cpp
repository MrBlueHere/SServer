/**
* @author Ladislav Floriš
* @date 05.05.20
*/

#include "CLogger.h"

using namespace std;

CLogger::CLogger(std::string logFormat, LogLevel level, bool headerOnly)
: m_logFormat(move(logFormat)), m_logLevel(level), m_headerOnly(headerOnly)
{ }

bool CLogger::ShouldMessageGetLogged(LogLevel level) const {
    return m_logLevel <= level;
}
