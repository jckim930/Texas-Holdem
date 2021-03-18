#ifndef POKERHAND_HPP_
#define POKERHAND_HPP_

#include "52Cards.hpp"
#include "Card.hpp"
#include <string>
#include <iostream>
#include <vector>
#include <algorithm>
#include <memory>

enum class handRanking {
    HIGH_CARD, ONE_PAIR, TWO_PAIR, THREE_OF_A_KIND, STRAIGHT,
    FLUSH, FULL_HOUSE, FOUR_OF_A_KIND, STRAIGHT_FLUSH, ROYAL_FLUSH
};

/*
 * This Class has
 */
class PokerHand {
private:
    std::vector<Card> hand;
    handRanking rank;
    std::vector<int> handValues;
    std::vector<Card> bestHandHighCardOrder;
public:

    PokerHand(Card c1, Card c2, Card c3,
              Card c4, Card c5) {
        hand.push_back(c1);
        hand.push_back(c2);
        hand.push_back(c3);
        hand.push_back(c4);
        hand.push_back(c5);
        handValues = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

        sortHand();
        setHandValues();
        setHandRank();
        setHighCards();
    }

    PokerHand(std::vector<Card> cards) {
        for (auto card : cards) {
            auto newCard = card;
            hand.push_back(newCard);
        }
        handValues = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

        sortHand();
        setHandValues();
        setHandRank();
        setHighCards();
    }

    PokerHand() {
        hand = {};
        rank = handRanking::HIGH_CARD;
        handValues = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
        bestHandHighCardOrder = {};
    }

    void sortHand() {
        std::sort(hand.begin(), hand.end());
    }

    // Overload Operators
    //...................................................................................................
    bool operator == (const PokerHand &other) const {
        if (this->rank == other.rank) {
            for (int i = 0; i < 5; i++) {
                if (this->bestHandHighCardOrder[i].getValue() != other.bestHandHighCardOrder[i].getValue())
                    return false;
            }
            return true;
        }
        return false;
    }
    bool operator > (const PokerHand &other) const {
        return this->rank > other.rank;
    }
    bool operator < (const PokerHand &other) const {
        if (this->rank == other.rank) {
            for (int i = 0; i < 5; i++) {
                if (this->bestHandHighCardOrder[i].getValue() < other.bestHandHighCardOrder[i].getValue())
                    return true;
                else if (this->bestHandHighCardOrder[i].getValue() > other.bestHandHighCardOrder[i].getValue())
                    return false;
            }
        }
        return this->rank < other.rank;
    }
    //...................................................................................................


    // BOOLs to determine the rank of the hand (straight, flush. full house, etc)
    //...................................................................................................
    bool onePair() const {
        for (int i = 12; i >= 0; i--) {
            if (handValues[i] == 2)
                return true;
        }
        return false;
    }

    bool twoPair() const {
        int numberOfPairs = 0;
        for (int i = 12; i >= 0; i--) {
            if (handValues[i] == 2)
                numberOfPairs++;
        }
        return (numberOfPairs == 2);
    }

    bool threeOfAKind() const {
        for (auto i = 0; i < this->hand.size() - 2; i++) {
            if (this->hand[i].getValue() == this->hand[i+1].getValue() &&
                this->hand[i].getValue() == this->hand[i+2].getValue())
                return true;
        }
        return false;
    }

    bool straight() const {
        if (hand[0].getValue() == 2) {
            for (auto i = 1; i < 4; i++) {
                if ((hand[0].getValue() + i) != hand[i].getValue())
                    return false;
            }
            return hand[4].getValue() == 6 || hand[4].getValue() == 14;
        } else {
            for (auto i = 1; i < hand.size(); i++) {
                if (hand[0].getValue() != (hand[i].getValue() - i))
                    return false;
            }
        }
        return true;
    }

    bool flush() const {
        int count = 0;
        for (auto i = 1; i < hand.size(); i++) {
            if (hand[0].getSuit() != hand[i].getSuit())
                return false;
        }
        return true;
    }

    bool fullHouse() const {
        return (threeOfAKind() && onePair());
    }

    bool fourOfAKind() const {
        for (auto i = 0; i < hand.size() - 3; i++) {
            if (hand[i].getValue() == hand[i+1].getValue() &&
                hand[i].getValue() == hand[i+2].getValue() &&
                hand[i].getValue() == hand[i+3].getValue())
                return true;
        }
        return false;
    }

    bool straightFlush() const {
        return (straight() &&flush());
    }

    bool royalFlush() const {
        return (straightFlush() && hand[0].getValue() == 10);
    }
    //...................................................................................................

    // SETTERS
    //...................................................................................................
    void setHighCards () {
        bestHandHighCardOrder = {};
        switch (rank) {
            case handRanking::ROYAL_FLUSH:
                this->setHighCardStraights();
                break;
            case handRanking::STRAIGHT_FLUSH:
                this->setHighCardStraights();
                break;
            case handRanking::FOUR_OF_A_KIND:
                this->setFourOfAKindHighCard();
                break;
            case handRanking::FULL_HOUSE:
                this->setFullHouseHighCard();
                break;
            case handRanking::FLUSH:
                this->setFlushHighCard();
                break;
            case handRanking::STRAIGHT:
                this->setHighCardStraights();
                break;
            case handRanking::THREE_OF_A_KIND:
                this->setThreeOfAKindHighCard();
                break;
            case handRanking::TWO_PAIR:
                this->setTwoPairHighCard();
                break;
            case handRanking::ONE_PAIR:
                this->setOnePairHighCard();
                break;
            default:
                this->setHighCardStraights();
                break;
        }
    }
    void setHandValues() {
        handValues = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
        for (auto itr : hand){
            handValues[itr.getValue() - 2]++;
        }
    }
    void setHandRank() {
        if(royalFlush())
            rank = handRanking::ROYAL_FLUSH;
        else if(straightFlush())
            rank = handRanking::STRAIGHT_FLUSH;
        else if (fourOfAKind())
            rank = handRanking::FOUR_OF_A_KIND;
        else if (fullHouse())
            rank = handRanking::FULL_HOUSE;
        else if (flush())
            rank = handRanking::FLUSH;
        else if (straight())
            rank = handRanking::STRAIGHT;
        else if (threeOfAKind())
            rank = handRanking::THREE_OF_A_KIND;
        else if (twoPair())
            rank = handRanking::TWO_PAIR;
        else if (onePair())
            rank = handRanking::ONE_PAIR;
        else
            rank = handRanking::HIGH_CARD;
    }

    void setHighCardStraights() {
        if (hand[0].getValue() == 2 && hand[4].getValue() == 14 && straight()) {
            for (int i = 3; i >= 0; i--) {
                bestHandHighCardOrder.push_back(hand[i]);
            }
            bestHandHighCardOrder.push_back(hand[4]);
        } else {
            for (int i = 4; i >= 0; i--) {
                bestHandHighCardOrder.push_back(hand[i]);
            }
        }
    }

    void setFourOfAKindHighCard() {
        // This for loop gets the value of the 4 of a kind
        if (hand[0] == hand[1] && hand[0] == hand[2] && hand[0] == hand[3]) {
            for (auto i = 0; i < 4; i++) {
                bestHandHighCardOrder.push_back(hand[i]);
            }
            bestHandHighCardOrder.push_back(hand[4]);
        } else {
            for (auto i = 1; i < 5; i++) {
                bestHandHighCardOrder.push_back(hand[i]);
            }
            bestHandHighCardOrder.push_back(hand[0]);
        }
    }

    void setFullHouseHighCard() {
        if (hand[0] == hand[1] && hand[0] == hand[2]) {
            for (auto i = 0; i < 3; i++) {
                bestHandHighCardOrder.push_back(hand[i]);
            }
            bestHandHighCardOrder.push_back(hand[4]);
            bestHandHighCardOrder.push_back(hand[3]);
        } else {
            for (auto i = 2; i < 5; i++) {
                bestHandHighCardOrder.push_back(hand[i]);
            }
            bestHandHighCardOrder.push_back(hand[1]);
            bestHandHighCardOrder.push_back(hand[0]);
        }
    }

    void setFlushHighCard() {
        for (int i = 4; i >= 0; i--) {
            bestHandHighCardOrder.push_back(hand[i]);
        }
    }

    void setThreeOfAKindHighCard() {
        if (hand[0] == hand[1] && hand[0] == hand[2]) {
            for (auto i = 0; i < 3; i++) {
                bestHandHighCardOrder.push_back(hand[i]);
            }
            bestHandHighCardOrder.push_back(hand[4]);
            bestHandHighCardOrder.push_back(hand[3]);
        } else if (hand[1] == hand[2] && hand[3] == hand[4]){
            for (auto i = 1; i < 4; i++) {
                bestHandHighCardOrder.push_back(hand[i]);
            }
            bestHandHighCardOrder.push_back(hand[4]);
            bestHandHighCardOrder.push_back(hand[0]);
        } else {
            for (auto i = 2; i < 5; i++) {
                bestHandHighCardOrder.push_back(hand[i]);
            }
            bestHandHighCardOrder.push_back(hand[1]);
            bestHandHighCardOrder.push_back(hand[0]);
        }
    }

    void setTwoPairHighCard() {
        int singleCardIndex = 0;
        for (auto i = 4; i > 0; i--) {
            if (hand[i] == hand[i - 1]) {
                bestHandHighCardOrder.push_back(hand[i]);
                bestHandHighCardOrder.push_back(hand[i - 1]);
                --i;
            } else
                singleCardIndex = i;
        }
        bestHandHighCardOrder.push_back(hand[singleCardIndex]);
    }

    void setOnePairHighCard() {
        int index1OfPair;
        int index2OfPair;
        for (auto i = 4; i > 0; i--) {
            if (hand[i] == hand[i - 1]) {
                bestHandHighCardOrder.push_back(hand[i]);
                bestHandHighCardOrder.push_back(hand[i - 1]);
                index1OfPair = i;
                index2OfPair = i - 1;
                break;
            }
        }
        for (auto i = 4; i >= 0; i--) {
            if (i != index1OfPair && i != index2OfPair) {
                bestHandHighCardOrder.push_back(hand[i]);
            }
        }
    }
    //.........................................................................................

    // GETTERS
    //..........................................................................................
    std::vector<int> getHandValues() const {
        return handValues;
    }
    handRanking getRank() const {
        return rank;
    }

    std::vector<Card>& getHand() {
        return hand;
    }

    std::vector<Card>& getBestHand() {
        setHighCards();
        return bestHandHighCardOrder;
    }

    std::string toStringHandRank() {
        switch (rank) {
            case handRanking::ROYAL_FLUSH:
                return "Royal Flush";
            case handRanking::STRAIGHT_FLUSH:
                return "Straight Flush";
            case handRanking::FOUR_OF_A_KIND:
                return "Four of a Kind";
            case handRanking::FULL_HOUSE:
                return "Full House";
            case handRanking::FLUSH:
                return "Flush";
            case handRanking::STRAIGHT:
                return "Straight";
            case handRanking::THREE_OF_A_KIND:
                return "Three of a Kind";
            case handRanking::TWO_PAIR:
                return "Two Pair";
            case handRanking::ONE_PAIR:
                return "One Pair";
            default:
                return "High Card";
        }
    }

    bool isEmpty() const {
        return hand.empty();
    }
};
#endif