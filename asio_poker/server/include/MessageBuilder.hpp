#pragma once
#include <string>
#include <vector>
class MessageBuilder {
    public:
        MessageBuilder();
        MessageBuilder& SetHeader(const std::string&);
        MessageBuilder& SetParams(const std::string&);
        std::string Build() const;
    private:
        std::string header;
        //std::string params;
        std::vector<std::string> params;
};