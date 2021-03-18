#ifndef POKERHAND_PLAYER_HPP
#define POKERHAND_PLAYER_HPP

#include "PokerHand.hpp"
#include "Card.hpp"
#include "52Cards.hpp"
#include <vector>
#include <string>
#include <iomanip>
#include <sstream>
/*
 * Justin Kim
 * CSC 382
 * PokerHand
 * Player.hpp
 */

class Player {
private:
    std::string name;
    std::vector<Card> playerHand;
    double balance;
    PokerHand playerBestHand;
public:
    Player(double amount, std::string name) {
        balance = amount;
        this->name = name;
        playerHand = {};
        playerBestHand;
    }
    // balance functions-----------------------------------------------------------------------
    void addBalance(double amount) {
        balance += amount;
    }

    void removeBalance(double amount) {
        balance -= amount;
    }

    double getBalance() const {
        return balance;
    }

    std::string balanceToString() const{
        std::string retString = "$";
        std::stringstream stream;
        stream << std::fixed << std::setprecision(2) << getBalance();
        retString += stream.str();
        return retString;
    }
    // end of balance functions----------------------------------------------------------------

    // hand functions--------------------------------------------------------------------------
    void addToHand(Card card) {
        playerHand.push_back(card);
    }

    std::vector<Card> getHand() {
        return playerHand;
    }
    // end of hand functions-------------------------------------------------------------------

    Card getFirstCard() {
        auto retCard = playerHand[0];
        return retCard;
    }

    Card getSecondCard() {
        auto retCard = playerHand[1];
        return retCard;
    }

    void setBestHand(std::vector<Card> community) {

        auto temp = PokerHand(community);
        if (playerBestHand.isEmpty())
            playerBestHand = temp;

        // Changing only a single card in object <PokerHand> temp
        for (auto i = 0; i < 2; i++) {
            for (auto j = 0; j < 5; j++) {
                temp = PokerHand(community);
                temp.getHand()[j] = playerHand[i];
                temp.sortHand();
                temp.setHandValues();
                temp.setHandRank();
                temp.setHighCards();
                if (playerBestHand < temp) {
                    playerBestHand = temp;
                }
            }
        }

        // Changing two cards in PokerHand temp
        for (auto i = 0; i < 4; i++) {
            for (auto j = (i + 1); j < 4; j++) {
                temp = PokerHand(community);
                temp.getHand()[i] = playerHand[0];
                temp.getHand()[j] = playerHand[1];
                temp.sortHand();
                temp.setHandValues();
                temp.setHandRank();
                temp.setHighCards();
                if (playerBestHand < temp)
                    playerBestHand = temp;
            }
        }
    }
    /*
     * returns a string representation of the bestHand
     *
     */
    std::string toStringBestHand() {
        std::string retString;
        auto temp = playerBestHand.getBestHand();
        for (auto i = 0; i < temp.size(); i++) {
            retString += temp[i].toString();
            retString += " ";
        }
        return retString;
    }

    std::string toStringHand() {
        std::string retString = "";
        retString += playerHand[0].toString();
        retString += " ";
        retString += playerHand[1].toString();
        return retString;
    }

    PokerHand getBestHand() const {
        return playerBestHand;
    }

    std::string getName() const {
        return name;
    }

    void reset() {
        playerHand = {};
        playerBestHand = PokerHand();
    }
};

#endif