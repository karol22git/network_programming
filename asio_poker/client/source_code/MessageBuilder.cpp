#include "../include/MessageBuilder.hpp"


MessageBuilder::MessageBuilder(): header("") {}

MessageBuilder& MessageBuilder::SetHeader(const std::string& _header) {
    this->header = _header;
    return *this;
}

MessageBuilder& MessageBuilder::SetParams(const std::string& _params) {
    params.push_back(_params);
    return *this;
}

MessageBuilder& MessageBuilder::SetId(const unsigned int _id) {
    this->id = std::to_string(_id);
    return *this;
}

std::string MessageBuilder::Build() const{
    std::string result = header + "|" + id + "|[";
    for(auto c: params) result = result +"{" + c +"}";
    result  += "]";
    return result;
}