#include <string>
#include <future> // async

#include "config.h"

using std::string;

// queries for peripheral data
class peripheral
{
protected:
#if ON_RPI
    std::future<void> fut;
#endif

public:
    // get terminal response to cmd
    static string getTerminalOutput(string cmd);
    // query the peripheral
    virtual void query() = 0;
    // query the peripheral on a non-blockign thread
    void queryViaThread();
};
