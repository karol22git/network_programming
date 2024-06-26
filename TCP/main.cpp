#include "Network.hpp"
#include "Segment.hpp"
#include "States.hpp"
#include "HeaderGenerator.hpp"
#include "Clock.hpp"
#include <iostream>
int main(int argc, char* argv[]) {
    std::shared_ptr network = Network::GetInstance();
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
    return 0;
}