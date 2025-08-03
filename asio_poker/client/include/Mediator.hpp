#include "UdpClient.hpp"
#include "ActionPanel.hpp"
#include <memory>
class Mediator{
    public:
        static void Init();
        static Mediator& GetInstance();
        Mediator(const Mediator&) = delete;
        Mediator& operator=(const Mediator&) = delete;
        static Mediator* instance;
        void SetClient(std::shared_ptr<UdpClient>);
        void SetActionPanel(ActionPanel*);
    private:
        Mediator();
        std::shared_ptr<UdpClient> client;
        ActionPanel* actionPanel;

};