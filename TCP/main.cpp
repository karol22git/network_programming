#include "Network.hpp"
#include "Segment.hpp"
#include "States.hpp"
#include "HeaderGenerator.hpp"
#include "Clock.hpp"
#include "Host.hpp"
#include <iostream>
#include <cstring>
int main(int argc, char* argv[]) {
    /*std::shared_ptr network = Network::GetInstance();
    struct Datagram new_datagram;
    new_datagram.ip = "127.0.0.1";
    //new_datagram.segment = ;
    struct Segment new_segment;
    new_segment.data = 100;
    //Header* h =  new Header(128);
    std::shared_ptr<Header> h = std::make_shared<Header>(128);
    new_segment.header = h;
    new_datagram.segment = new_segment;
    network->Post(new_datagram);
    */
    if(argc != 6) {
        std::cout<<"Usage <source ip> <source port> <1 - open actively / 2 - open pasively> <destination ip> <destination port>"<<std::endl;
        return 0;
    }
    std::string ip = argv[1];
    int port = std::atoi(argv[2]);
    std::unique_ptr<Host> myHost = std::make_unique<Host>(ip,port);
    if(strcmp(argv[3], "1") == 0) {
        ip = argv[4];
        port = std::atoi(argv[5]);
        myHost->OpenForConnectionActively(ip,port);
    
    }
    else if (strcmp(argv[3], "2") == 0) {
        myHost->OpenForConnectionPassively();
    }
    else {
        std::cout<<argv[3]<<std::endl;
        std::cout<<"kk Usage <source ip> <source port> <1 - open actively / 2 - open pasively> <destination ip> <destination port>"<<std::endl;
        return 0;
    }
        
    return 0;
}