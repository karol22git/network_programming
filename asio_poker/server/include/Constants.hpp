#pragma once
#include <string>
#include <map>
const unsigned int deck_size = 52;
const unsigned int pocket_cards = 2;
const unsigned int flop_size = 3;
const unsigned int extra_cards_size = 2;
const unsigned int start_cash = 500;
const unsigned int quorum = 2;
enum Color {
    pik = 1,
    kier,
    trefl,
    karo
};

enum MessageType {
    POCKET_CARDS = 1,
    FLOP,
    ANOTHER_CARD,
    RAISE,
    CALL,
    PASS,
    MSG_ERROR
};

inline Color GetCardColor(int i) {
    switch(i) {
        case 1: return Color::pik;
        case 2: return Color::kier;
        case 3: return Color::trefl;
        case 4: return Color::karo;
        default:
            return Color::pik;
    }
}

inline MessageType GetMessageType(const std::string& msg) {
    static const std::map<std::string, MessageType> tmpMap  = {
        {"[POCKET_CARDS]", MessageType::POCKET_CARDS},
        {"[FLOP]",MessageType::FLOP},
        {"[ANOTHER_CARD]",MessageType::ANOTHER_CARD},
        {"[RAISE]",MessageType::RAISE},
        {"[CALL]",MessageType::CALL},
        {"[PASS]",MessageType::PASS}};

    for(const auto& [key,value]: tmpMap) {
        if(msg.find(key) != std::string::npos) return value;
    }
    return MessageType::MSG_ERROR;
}

struct Card {
    Color color;
    int val;
    Card(std::string s) {
        if(s[0] == 'A') color = Color::pik;
        else if(s[0] == 'B') color = Color::kier;
        else if(s[0] == 'C') color = Color::trefl;
        else color = Color::karo;
        val = std::stoi(s.substr(1));
    }
    Card(Color c, int value) : color(c), val(value) {}
    Card() {}
    std::string toString() const {
        std::string col;
        switch (color) {
            case 1:
                col = "A";
                break;
            case 2:
                col = "B";
                break;
            case 3:
                col = "C";
                break;
            case 4:
                col = "D";
                break;
            default:
                break;
        }
        return col + std::to_string(val);
    }
};

enum Hands {
    Poker_krolewski = 1,
    Poker,
    Kareta,
    Full,
    Kolor,
    Strit,
    Trojka,
    Dwie_pary,
    Para,
    Wysoka_karta = 10
};

struct Messages {
    const std::string CONNECTION_MESSAGE = "[CONNECTION]";
    const std::string REFUSE_CONNECTION = "[REFUSECONNECTION]";
    const std::string ACCEPTED = "[ACCEPTED]";
};