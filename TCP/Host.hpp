#include "States.hpp"

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

    private:

        void send();
        void receive();
        const std::string ip;
        const std::string port;
        std::thread sender;
        std::thread receiver;
        std::shared_ptr<Connection> endpoint;
        State state;
}