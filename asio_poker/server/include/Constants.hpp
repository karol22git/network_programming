#pragma once
#include <string>
#include <map>
const unsigned int deck_size = 52;
const unsigned int pocket_cards = 2;
const unsigned int flop_size = 3;
const unsigned int extra_cards_size = 2;
const unsigned int start_cash = 500;
const unsigned int quorum = 2;
const unsigned int start_money = 500;
const unsigned int big_blind = 20;
const unsigned int small_blind = big_blind/2;
const std::string resource_dir = "../resources/";
const std::string otherside_card_file = "back.png";
enum Color {
    pik = 1,
    kier,
    trefl,
    karo
};

enum Stage {
    PRE_FLOP_STAGE = 1,
    FLOP_STAGE,
    TURN_STAGE,
    RIVER_STAGE,
    END_GAME = 5
};

enum MessageType :int {
    POCKET_CARDS = 1,
    FLOP,
    ANOTHER_CARD,
    RAISE,
    CALL,
    PASS,
    TURN,
    MSG_EXIT,
    FORCED,
    SMALL_BLIND,
    BIG_BLIND,
    ACCEPT_CALL,
    STAKE,
    POT,
    SHOW_CARDS,
    SOLO_WIN,
    MULTI_WIN,
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
        {"[PASS]",MessageType::PASS},
        {"[TURN]",MessageType::TURN},
        {"[EXIT]", MessageType::MSG_EXIT},
        {"[FORCED]", MessageType::FORCED},
        {"[SMALL_BLIND", MessageType::SMALL_BLIND},
        {"[BIG_BLIND]", MessageType::BIG_BLIND},
        {"[ACCEPT_CALL]",MessageType::ACCEPT_CALL},
        {"[STAKE]",MessageType::STAKE},
        {"[POT]",MessageType::POT},
        {"[SHOW_CARDS]",MessageType::SHOW_CARDS},
        {"[SOLO_WIN]",MessageType::SOLO_WIN},
        {"[MULTI_WIN]", MessageType::MULTI_WIN},
    };

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
    int toInt() const {
        int suite;
        switch(color) {
            case pik:
                suite = 0;
                break;
            case kier:
                suite = 1;
                break;
            case trefl:
                suite = 2;
                break;
            case karo:
                suite = 3;
                break;
            default:
                suite = 0;
        }
        auto rank = val -2;
        return 4*rank + suite;
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