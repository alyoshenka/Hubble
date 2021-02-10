#pragma once
// listens for commands from shared pipe

#include "config.h"

#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <string>
#include <thread>
#include <future>
#include <chrono>
#include <iostream>
#if ON_RPI
#include <sys/poll.h>
#include <unistd.h>
#endif

#include "errorDisplay.h"

using std::string;
#if ON_RPI
using std::thread;
#endif

using namespace std::chrono_literals;

class commandListener
{
    const char *sharedPipe = "/tmp/sharedPipe";
    const static int maxLen = 80;

#if ON_RPI
    std::future<string> fut;
#endif

    char writeStr[maxLen];
    bool newM;
    string currentMessage;
    errorDisplay *eDisp;

public:
    commandListener(errorDisplay *errorDisp);
    void listen();
    void sendListener();
    void stopListener();
    string getMessage();
    bool newMessage();
};
