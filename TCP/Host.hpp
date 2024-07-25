#pragma once
#include "Network.hpp"
#include "States.hpp"
#include "DataTypes.hpp"
#include "Datagram.hpp"
#include "HeaderGenerator.hpp"
#include "Clock.hpp"
#include <queue>
#include <thread>
#include <list>
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

class Host {
    public:
        Host(std::string, _16bits);
        void OpenForConnectionPassively();
        void OpenForConnectionActively(std::string, _16bits);
        void HandleDatagram(struct Datagram);
        void SetState(States);
        void FetchDataFromNetwork();
        void CheckForReceivedData();
        void ProceedThreeWayHandshake(struct Datagram);
    private:
        void ProceedDatagram(struct Datagram);
        struct TransmissionControlBlock tcb;
        std::string ip;
        _16bits port;
        std::thread sender;
        std::thread receiver;
        bool isConnectionEstablished = false;
        std::shared_ptr<Network> endpoint;
        std::list<Segment> connection;
        std::queue<struct Datagram> datagrams;
        int initial_sequance_number;
        std::unique_ptr<HeaderGenerator> generator;
        std::unique_ptr<Clock> clock; 
        States state = States::CLOSED;
};