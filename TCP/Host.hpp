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
#include <cstdlib>

#define RETRANSMISSION_TIME_OUT 5000
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
    _16bits destination_port;
    std::string destination_ip;
};
/*struct Connection {
    std::string source_ip;
    std::string destination_ip;
    _16bits source_port;
    _16bits destination_port;
};
*/

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
        void Wait();
        void GracefulConnectionRelease(struct Datagram);//std::string, _16bits, _32bits);
    private:
        void SendFinHeader(std::string, _16bits);
        void SendAckHeader(std::string, _16bits, _32bits);
        void ActiveGracefulConnectionRelease(std::string, _16bits);
        void TerminateConnection();
        void AcknowledgeSegment(_32bits);
        void CheckForRetransmission();
        void MarkAsSend(struct Datagram);
        void PrepareAcknowledgment(std::string, _16bits, _32bits);
        void ThreeWayHandshakeStageThree();
        void ThreeWayHandshakeStageOne(std::string, _16bits);
        void ThreeWayHandshakeStageTwo(std::string, _16bits);
        void UpdateSndNxt();
        void InitializeSequenceNumbers(_32bits);
        void InitializeIRS(_32bits);
        struct Datagram PrepareDatagram(std::string, std::string);
        void ProceedDatagram(struct Datagram);
        void OpenConnection();
        void PostDataOnNetwork();
        void ConnectinonHasBeenEstablished();
        struct TransmissionControlBlock tcb;
        std::string ip;
        _16bits port;
        std::thread sender;
        std::thread receiver;
        std::thread retransmiter;
        bool isConnectionEstablished = false;
        std::shared_ptr<Network> endpoint;
        std::queue<struct Datagram> datagrams;
        std::queue<struct Datagram> data_to_be_send;
        std::list<std::pair<struct Datagram, std::chrono::steady_clock::time_point>> data_to_be_acknowledgment;
        std::queue<struct Datagram> acknowledgments_for_data;
        std::unique_ptr<HeaderGenerator> generator;
        std::unique_ptr<Clock> clock; 
        std::unique_ptr<Console> console;
        States state = States::CLOSED;
        bool iHaveBeenActive = false;
};