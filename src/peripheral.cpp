#include "peripheral.h"

#include <iostream>

string peripheral::getTerminalOutput(string cmd)
{
#if ON_RPI
#if periph_debug
    std::cout << "getting output from: " << cmd << std::endl;
#endif periph_debug
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

#if periph_debug
    std::cout << "result from " << cmd << ": " << res << std::endl;
#endif periph_debug
    return res;
#endif

#if periph_debug
    std::cout << "nothing to return" << std::endl;
#endif periph_debug

    return "";
}

void peripheral::queryViaThread()
{
#if periph_debug
    std::cout << "querying peripheral via thread" << std::endl;
#endif periph_debug

#if ON_RPI
    fut = std::async(std::launch::async, [this] {
        this->query();
    });
    return;
#endif
    query();
}
