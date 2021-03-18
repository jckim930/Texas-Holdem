//
// Created by Justin on 4/7/2019.
//

#ifndef POKERHAND_DEALER_H
#define POKERHAND_DEALER_H

#include "52Cards.hpp"
#include "Card.hpp"
#include "Deck.hpp"
#include "Player.hpp"
#include "PokerHand.hpp"

class Dealer {
private:
    Deck *deck;
public:
    Dealer(Deck &deck) {
        this->deck = deck;
        shuffleDeck();
    }

    Card dealCard() {
        return deck.dealCard();
    }

    void dealPlayers() {
        for (auto i = 0; i < 2; i++) {
            for (auto player : players) {
                Card card = dealCard();
                player.addToHand(card);
            }
        }
    }

    void setCommunity() {
        //dealCard();
        for (auto i = 0; i < 3; i++) {
            community.push_back(dealCard());
        }
        for (auto i = 0; i < 2; i++) {
            //dealCard();
            community.push_back(dealCard());
        }
    }

    void setCommunityPokerHand() {
        communityPokerHand = PokerHand(community[0], community[1], community[2], community[3], community[4]);
    }

    void printCommunity() const{
        std::string retString = "Community Cards: ";
        for (auto card : community) {
            retString += card.toString();
            retString += " ";
        }
        std::cout << std::endl;
        std::cout << retString << std::endl;
    }

    handRanking getCommunityRank() const{
        return communityRank;
    }

    std::vector<Card> getCommunity() const{
        return community;
    }

    PokerHand getCommunityHand() const{
        return communityPokerHand;
    }

    double anteFromPlayers() {
        double ante = 2.00;
        double pot = ante * players.size();
        for (auto player : players) {
            player.loseMoney(ante);
        }
        return pot;
    }

    std::vector<Player> getPlayers() {
        return players;
    }

    void calculateBestHand() {
        PokerHand tempBestHand = getCommunity();
        for (auto player : players) {
            player.setBestHand(tempBestHand);
            std::vector<Card> tempVec;
            for (auto i = 0; i < player.getHand().size(); i++) {
                for (auto j = 0; j < getCommunity().size(); j++) {
                    tempVec = getCommunity();
                    tempVec[j] = player.getHand()[i];
                    PokerHand tempPokerHand(tempVec);
                    if (player.getBestHand() < tempPokerHand) {
                        player.setBestHand(tempPokerHand);
                    }
                }
            }
        }
    }


};

#endif //POKERHAND_DEALER_H
