#include <iostream>
#include "CServer.h"
#include "logging/LogType.h"

using namespace std;

int main(int argc, char **argv) {
    CServer server{};

    CConfiguration config{};
    string configPath;
    if (argc > 1) {
        configPath = argv[1];

        // Read the configuration and validate it
        try {
            config.ReadConfigurationFromFile(configPath);
        }
        catch (exception & e) {
            cout << e.what() << endl;
            return 1;
        }
    }
    // todo: uncomment
    /*else {
        cout << "Are you sure that you want to run the server with default settings?\n"
                "yes/no" << endl;
        string response;
        cin >> response;
        if (response == "No" || response == "no" || response == "n" || response == "N")
            return 0;
    }*/

    if (server.Startup(config))
        return server.Listen();

    // Server failed to start
    cout << "Server failed to start" << endl;

    return 1;
}
