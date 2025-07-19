#pragma once
#include <string>
const unsigned int deck_size = 52;
const unsigned int pocket_cards = 2;
enum Color {
    pik = 1,
    kier,
    trefl,
    karo
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

struct Card {
    Color color;
    int val;
    Card(Color c, int value) : color(c), val(value) {}
    Card() {}
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