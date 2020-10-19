#include "commandListener.h"

commandListener::commandListener() {

     // rw-rw-rw
     mkfifo(sharedPipe, 0666);
}

void commandListener::listen(){
    try{
        std::future_status status = fut.wait_for(0ms);
        if(std::future_status::ready != status) { return; }
        if(!fut.valid()){
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
        
        sendListener();
    } catch(const std::future_error& e){
        printf("future error %i\n", e.code());
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
    // magic number bad
    fut = std::async(std::launch::async, getInput, 80, sharedPipe);
}

void commandListener::stopListener(){
    int fd = open(sharedPipe, O_WRONLY);
    char* res = "closing graphics";
    write(fd, res, strlen(res) + 1);
    close(fd);
}


