//
// Created by Justin on 4/7/2019.
//
#include "catch.hpp"
#include "52Cards.hpp"
#include "PokerHand.hpp"
#include <iostream>
#include <string>
#include "Deck.hpp"
#include <algorithm>
#include <chrono>

TEST_CASE("PrintAllCards") {
    Deck deck;
    Card dealt = deck.dealCard();
    std::cout << dealt.toString();
    REQUIRE(51 == deck.getDeckSize());
    REQUIRE(S2 == dealt);
    deck.addCard(dealt);
    REQUIRE(52 == deck.getDeckSize());
    REQUIRE(S2 == deck.dealCard());
}
