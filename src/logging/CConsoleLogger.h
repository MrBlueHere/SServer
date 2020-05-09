/**
* @author Ladislav Floriš
* @date 09.05.20
*/

#pragma once

#include "CLogger.h"
#include <string>

class CConsoleLogger : public CLogger {
public:
    void Log(const std::string &) override;
};


