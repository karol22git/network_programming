#include "Network.hpp"
#include "Segment.hpp"
#include "States.hpp"
#include "HeaderGenerator.hpp"
#include "Clock.hpp"
#include "Host.hpp"
#include <iostream>
#include <cstring>
int main(int argc, char* argv[]) {
    if(argc != 7) {
        std::cout<<"Usage <source ip> <source port> <1 - open actively / 2 - open pasively> <destination ip> <destination port> <amount of bytes to send"<<std::endl;
        return 0;
    }
    std::string ip = argv[1];
    int port = std::atoi(argv[2]);
    std::unique_ptr<Host> myHost = std::make_unique<Host>(ip,port);
    if(strcmp(argv[3], "1") == 0) {
        ip = argv[4];
        port = std::atoi(argv[5]);
        int bytes_to_be_send = std::atoi(argv[6]);
        myHost->PrepareDataToBeSend(bytes_to_be_send,ip,port);
        myHost->OpenForConnectionActively(ip,port);
    }
    else if (strcmp(argv[3], "2") == 0) {
        myHost->OpenForConnectionPassively();
    }
    else {
        std::cout<<argv[3]<<std::endl;
        std::cout<<" Usage <source ip> <source port> <1 - open actively / 2 - open pasively> <destination ip> <destination port>"<<std::endl;
        return 0;
    }
       // std::this_thread::sleep_for(std::chrono::milliseconds(5000));
    myHost->Wait();
    return 0;
}