/**
* @author Ladislav Floriš
* @date 09.05.20
*/

#include "CConsoleLogger.h"
#include <iostream>
#include <string>

using namespace std;

void CConsoleLogger::Log(const string & text) {
    cout << text << endl;
}