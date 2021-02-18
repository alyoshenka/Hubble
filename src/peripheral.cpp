#include "peripheral.h"

#include <iostream>

string peripheral::getTerminalOutput(string cmd)
{
#if ON_RPI
    std::cout << "getting output from: " << cmd << std::endl;
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
    
    std::cout << "result from " << cmd << ": " << res << std::endl;
    return res;
#endif

    std::cout << "nothing to return" << std::endl;
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
