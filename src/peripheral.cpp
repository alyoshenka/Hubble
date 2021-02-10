#include "peripheral.h"

#include <iostream>

string peripheral::getTerminalOutput(string cmd)
{
    std::cout << "getting output from: " << cmd << std::endl;

#if ON_RPI
    char buffer[128];
    string res = "";
    FILE *stream = popen(cmd.c_str(), "r");
    if (!stream)
    {
        std::cerr << "popen failed" << std::endl;
        return "";
    }

    // read to end
    while (!feof(stream))
    {
        if (NULL != fgets(buffer, 128, stream))
        {
            res += buffer;
        }
    }

    pclose(stream);
    return res;
#endif

    // nothing to return
    return "";
}

void peripheral::queryViaThread()
{
    std::cout << "querying peripheral via thread" << std::endl;
#if ON_RPI
    fut = std::async(std::launch::async, [this] {
        this->query();
    });
    return;
#endif
    query();
}