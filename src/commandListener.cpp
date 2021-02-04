#include "commandListener.h"

commandListener::commandListener()
{

// rw-rw-rw
#if ON_RPI
    mkfifo(sharedPipe, 0666);
#endif

    newM = false;
}

void commandListener::listen()
{
#if ON_RPI
    try
    {
        std::future_status status = fut.wait_for(0ms);
        if (std::future_status::ready != status)
        {
            return;
        }
        if (!fut.valid())
        {
            printf("fut not valid\n");
            return;
        }

        // message
        string msg = fut.get();
        std::cout << "CommandCenter: " << msg << std::endl;

        // respond
        int fd = open(sharedPipe, O_WRONLY);
        string res = "you sent " + msg;
        strcpy(writeStr, res.c_str());
        write(fd, writeStr, strlen(writeStr) + 1);
        close(fd);

        newM = true;
        currentMessage = msg;

        sendListener();
    }
    catch (const std::future_error &e)
    {
        printf("future error %i\n", e.code());
    }
#endif
}

string getInput(int maxLen, const char *pName)
{
#if ON_RPI
    char msg[maxLen];
    // read
    int fd = open(pName, O_RDONLY);
    read(fd, &msg, maxLen);
    close(fd);

    return string(msg);
#endif
    return "";
}

void commandListener::sendListener()
{
    printf("Sending listener\n");
#if ON_RPI
    // magic number bad
    fut = std::async(std::launch::async, getInput, 80, sharedPipe);
#endif
}

void commandListener::stopListener()
{
#if ON_RPI
    int fd = open(sharedPipe, O_WRONLY);
    char *res = "closing graphics";
    write(fd, res, strlen(res) + 1);
    close(fd);
#endif
}

string commandListener::getMessage()
{
    newM = false;
    return currentMessage;
}

bool commandListener::newMessage()
{
    return newM;
}
