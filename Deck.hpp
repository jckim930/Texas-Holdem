//
// Created by Justin Kim
//

#ifndef DECK_HPP
#define DECK_HPP

#include "Card.hpp"
#include "52Cards.hpp"
#include <random>
#include <algorithm>
#include <iostream>
#include <vector>
#include <chrono>
#include <memory>

/*
 * Justin Kim
 * CSC 382
 * PokerHand
 * Deck.hpp
 * Stores Card objects in a vector called deck
 * vector<Card> deck
 * Passes shared_ptr to the Card objects in the deck
 */


class Deck {
private:
    std::vector<Card> deck;
    unsigned n{0};
    unsigned seed;
public:
    Deck() {
        seed = std::chrono::system_clock::now().time_since_epoch().count();
        deck;
    }

    Card removeCard() {
        return deck[n--];
    }

    void shuffle() {
        std::shuffle(deck.begin(), deck.end(), std::default_random_engine(seed));
    }

    void printDeck() const {
        for (auto current : deck) {
            std::cout << current.toString() << std::endl;
        }
    }

    void resetDeck() {
        n = 51;
        shuffle();
    }

    // Returns how many cards are "left" in the deck
    // "n" is a counter for the top most card
    int getDeckSize() const {
        return n - 1;
    }

    void initDeck() {
        deck.push_back(C2);
        deck.push_back(C3);
        deck.push_back(C4);
        deck.push_back(C5);
        deck.push_back(C6);
        deck.push_back(C7);
        deck.push_back(C8);
        deck.push_back(C9);
        deck.push_back(C10);
        deck.push_back(CJ);
        deck.push_back(CQ);
        deck.push_back(CK);
        deck.push_back(CA);

        deck.push_back(D2);
        deck.push_back(D3);
        deck.push_back(D4);
        deck.push_back(D5);
        deck.push_back(D6);
        deck.push_back(D7);
        deck.push_back(D8);
        deck.push_back(D9);
        deck.push_back(D10);
        deck.push_back(DJ);
        deck.push_back(DQ);
        deck.push_back(DK);
        deck.push_back(DA);

        deck.push_back(H2);
        deck.push_back(H3);
        deck.push_back(H4);
        deck.push_back(H5);
        deck.push_back(H6);
        deck.push_back(H7);
        deck.push_back(H8);
        deck.push_back(H9);
        deck.push_back(H10);
        deck.push_back(HJ);
        deck.push_back(HQ);
        deck.push_back(HK);
        deck.push_back(HA);

        deck.push_back(S2);
        deck.push_back(S3);
        deck.push_back(S4);
        deck.push_back(S5);
        deck.push_back(S6);
        deck.push_back(S7);
        deck.push_back(S8);
        deck.push_back(S9);
        deck.push_back(S10);
        deck.push_back(SJ);
        deck.push_back(SQ);
        deck.push_back(SK);
        deck.push_back(SA);
        n = 51;
    }
};


#endif //POKERHAND_DECK_HPP
