#include "../include/MessageBuilder.hpp"


MessageBuilder::MessageBuilder(): header("") {}

MessageBuilder& MessageBuilder::SetHeader(const std::string& _header) {
    this->header = _header;
    return *this;
}

MessageBuilder& MessageBuilder::SetParams(const std::string& _params) {
    //this->params= _params;
    //return *this;
    params.push_back(_params);
}

std::string MessageBuilder::Build() const{
    std::string result = header +"[";
    for(auto c: params) result = result +"{" + c +"}";
    result  += "]";
    return result;
}