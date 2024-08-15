#pragma once
#include "Network.hpp"
#include "States.hpp"
#include "DataTypes.hpp"
#include "Datagram.hpp"
#include "HeaderGenerator.hpp"
#include "Clock.hpp"
#include "Console.hpp"
#include <queue>
#include <thread>
#include <list>

#define MAXIMUM_SEGMENT_SIZE 64
#define HEADER_SIZE 32
//jeden oktet to 8 bitow, 
struct TransmissionControlBlock {
    int snd_una,
        snd_nxt,
        snd_wnd,
        snd_up,
        snd_wl1,
        snd_wl2,
        iss,
        rcv_nxt,
        rcv_wnd,
        rcv_up,
        irs;
};
struct Connection {
    std::string source_ip;
    std::string destination_ip;
    _16bits source_port;
    _16bits destination_port;
};
/*struct ConnectionStages {
    bool syn,
    synack,
    ack;
};*/

class Host {
    public:
        Host(std::string, _16bits);
        void OpenForConnectionPassively();
        void OpenForConnectionActively(std::string, _16bits);
        void HandleDatagram(struct Datagram);
        void SetState(States);
        void FetchDataFromNetwork();
        void CheckForReceivedData();
        States GetState();
        void PrepareDataToBeSend(int, std::string, _16bits);
    private:
        void ThreeWayHandshakeStageThree();
        void ThreeWayHandshakeStageOne(std::string, _16bits);
        void UpdateSndNxt();
        void InitializeSequenceNumbers(_32bits);
        struct Datagram PrepareDatagram(std::string, std::string);
        void ProceedDatagram(struct Datagram);
        void OpenConnection();
        void PostDataOnNetwork();
       // void PrepareToConnection();
        struct TransmissionControlBlock tcb;
        struct Connection connection_info;
        //struct ConnectionStages cStages;
        std::string ip;
        _16bits port;
        std::thread sender;
        std::thread receiver;
        bool isConnectionEstablished = false;
        std::shared_ptr<Network> endpoint;
        //std::list<Segment> connection;
        std::queue<struct Datagram> datagrams;
        std::queue<struct Datagram> data_to_be_send;
        //int initial_sequance_number;
        std::unique_ptr<HeaderGenerator> generator;
        std::unique_ptr<Clock> clock; 
        std::unique_ptr<Console> console;
        States state = States::CLOSED;
};