/**
* @author Ladislav Floriš
* @date 05.05.20
*/

#include "CConfiguration.h"
#include <sstream>
#include <cmath>

using namespace std;

bool CConfiguration::ReadConfigurationFromFile(const std::string &src) {
    // validate file exists, proper format, ...

    // read file

    // initialize member variables


    return false;
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
        result += (num * pow(2, power));
        power += 8;
    }
    return result;
}
