#include "commandListener.h"

<<<<<<< HEAD:commandListener.cpp
commandListener::commandListener(errorDisplay* errorDisp) {

     // rw-rw-rw
     mkfifo(sharedPipe, 0666);
     
     newM = false;
     
     eDisp = errorDisp;
=======
commandListener::commandListener()
{

// rw-rw-rw
#if ON_RPI
    mkfifo(sharedPipe, 0666);
#endif

    newM = false;
>>>>>>> 7a245092389d4584eb22bd111eea983d92eac42c:src/commandListener.cpp
}

void commandListener::listen()
{
#if ON_RPI
    try
    {
        std::future_status status = fut.wait_for(0ms);
<<<<<<< HEAD:commandListener.cpp
        if(std::future_status::ready != status) { return; }
        if(!fut.valid()){
            
=======
        if (std::future_status::ready != status)
        {
            return;
        }
        if (!fut.valid())
        {
>>>>>>> 7a245092389d4584eb22bd111eea983d92eac42c:src/commandListener.cpp
            printf("fut not valid\n");
            eDisp->addErrString("fut not valid");
            
            return;
        }

        // message
        string msg = fut.get();
        
        std::cout << "CommandCenter: " << msg << std::endl;
<<<<<<< HEAD:commandListener.cpp
        eDisp->addErrString("CommandCenter: " + msg);
        
=======

>>>>>>> 7a245092389d4584eb22bd111eea983d92eac42c:src/commandListener.cpp
        // respond
        int fd = open(sharedPipe, O_WRONLY);
        string res = "you sent " + msg;
        strcpy(writeStr, res.c_str());
        write(fd, writeStr, strlen(writeStr) + 1);
        close(fd);

        newM = true;
        currentMessage = msg;

        sendListener();
<<<<<<< HEAD:commandListener.cpp
    } catch(const std::future_error& e){
        
=======
    }
    catch (const std::future_error &e)
    {
>>>>>>> 7a245092389d4584eb22bd111eea983d92eac42c:src/commandListener.cpp
        printf("future error %i\n", e.code());
        eDisp->addErrString("future error");
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
<<<<<<< HEAD:commandListener.cpp
    eDisp->addErrString("Sending listener");
    
=======
#if ON_RPI
>>>>>>> 7a245092389d4584eb22bd111eea983d92eac42c:src/commandListener.cpp
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
