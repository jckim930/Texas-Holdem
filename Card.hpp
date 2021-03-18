/*
 * Programmer: Justin Kim
 * Class: CSC 382
 */
#ifndef CARD_HPP_
#define CARD_HPP_

#include <string>

/*
 * Justin Kim
 * CSC 382
 * PokerHand
 * Card.hpp
 */


// Model the Suit of a Poker Card
enum class Suit {
    CLUBS, DIAMONDS, HEARTS, SPADES
};

enum class Rank {
    DEUCE = 2, THREE = 3, FOUR = 4, FIVE = 5, SIX = 6, SEVEN = 7,
    EIGHT = 8, NINE = 9, TEN = 10,
    JACK = 11, QUEEN = 12, KING = 13, ACE = 14
};

class Card {
private:
    Suit suit;
    Rank rank;
public:
    Card(const Rank rank, const Suit suit) {
        this->rank = rank;
        this->suit = suit;
    }

    Rank getRank() const {
        return rank;
    }

    Suit getSuit() const {
        return suit;
    }

    int getValue() const {
        return static_cast<int>(rank);
    }

    std::string toString() const {
        auto const club{"\xe2\x99\xa3"};
        auto const diamond{"\xe2\x99\xa6"};
        auto const heart{"\xe2\x99\xa5"};
        auto const spade{"\xe2\x99\xa0"};

        std::string value;

        if (getValue() > 10) {
            if (getValue() == 11)
                value = "J";
            else if (getValue() == 12)
                value = "Q";
            else if (getValue() == 13)
                value = "K";
            else
                value = "A";
        } else {
            value = std::to_string(getValue());
        }

        if (suit == Suit::CLUBS) {
            return value + club;
        } else if (suit == Suit::DIAMONDS) {
            return value + diamond;
        } else if (suit == Suit::HEARTS) {
            return value + heart;
        } else {
            return value + spade;
        }
    }

    bool operator<(const Card &other) const {
        return this->getValue() < other.getValue();
    }

    bool operator<(const int num) const {
        return this->getValue() < num;
    }

    bool operator>(const Card &other) const {
        return this->getValue() > other.getValue();
    }

    bool operator>(const int num) const {
        return this->getValue() > num;
    }

    bool operator==(const Card &other) const {
        return this->getValue() == other.getValue();
    }

    bool operator==(const int num) const {
        return this->getValue() == num;
    }

    int operator+(const Card &other) {
        return this->getValue() + other.getValue();
    }

    int operator+(const int num) {
        return this->getValue() + num;
    }

    int operator-(const Card &other) {
        return this->getValue() - other.getValue();
    }

    int operator-(int num) {
        return this->getValue() - num;
    }
};

#endif