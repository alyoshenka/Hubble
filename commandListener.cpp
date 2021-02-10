#include "commandListener.h"

commandListener::commandListener(errorDisplay* errorDisp) {

     // rw-rw-rw
     mkfifo(sharedPipe, 0666);
     
     newM = false;
     
     eDisp = errorDisp;
}

void commandListener::listen(){
    try{
        std::future_status status = fut.wait_for(0ms);
        if(std::future_status::ready != status) { return; }
        if(!fut.valid()){
            
            printf("fut not valid\n");
            eDisp->addErrString("fut not valid");
            
            return;
        }

        // message
        string msg = fut.get();
        
        std::cout << "CommandCenter: " << msg << std::endl;
        eDisp->addErrString("CommandCenter: " + msg);
        
        // respond
        int fd = open(sharedPipe, O_WRONLY);
        string res = "you sent " + msg;
        strcpy(writeStr, res.c_str());
        write(fd, writeStr, strlen(writeStr) + 1);
        close(fd);
        
        newM = true;
        currentMessage = msg;
        
        sendListener();
    } catch(const std::future_error& e){
        
        printf("future error %i\n", e.code());
        eDisp->addErrString("future error");
    }
} 

string getInput(int maxLen, const char* pName){
    char msg[maxLen];
    // read
    int fd = open(pName, O_RDONLY);
    read(fd, &msg, maxLen);
    close(fd);
    
    return string(msg);
}

void commandListener::sendListener(){
    printf("Sending listener\n");
    eDisp->addErrString("Sending listener");
    
    // magic number bad
    fut = std::async(std::launch::async, getInput, 80, sharedPipe);
}

void commandListener::stopListener(){
    int fd = open(sharedPipe, O_WRONLY);
    char* res = "closing graphics";
    write(fd, res, strlen(res) + 1);
    close(fd);
}

string commandListener::getMessage(){
    newM = false;
    return currentMessage;
}

bool commandListener::newMessage(){
    return newM;
}
