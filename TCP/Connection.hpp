#pragma once
#include <utility>
#include <list>
#include <memory>
#include "Segment.hpp"
class host;

class Connection {
    public:
        Connection(Connection&) = delete;
        static std::shared_ptr<Connection> GetInstance();

    private:
        std::list<Segment> bytestream;
        static std::shared_ptr<Connection> connection_;// = nullptr;
};