#pragma once
// listens for commands from shared pipe

#include <stdio.h>
#include <string.h>
#include <sys/poll.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <string>
#include <thread>
#include <future>
#include <chrono>
#include <iostream>

using std::string;
using std::thread;

using namespace std::chrono_literals;

class commandListener{
    const char* sharedPipe = "/tmp/sharedPipe";
    const static int maxLen = 128;
    
    std::future<string> fut;
    
    char writeStr[maxLen];
    
public:
    commandListener();
    void listen();
    void sendListener();
};

