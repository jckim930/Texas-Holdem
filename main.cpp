#include <string>
#include <iostream>
#include <vector>
#include <algorithm>
#include <memory>
#include <iomanip>
#include <sstream>
#include "52Cards.hpp"
#include "Deck.hpp"
#include "Card.hpp"
#include "Player.hpp"
/*
 * Justin Kim
 * CSC 382
 * PokerHand
 * main.cpp
 * main.cpp coordinates the Poker Game
 */
int numberOfPlayers() {
    int number{0};
    std::cout << "How many players? ";
    std::cin >> number;
    std::cout << std::endl;
    return number;
}
void makePlayers(int num, std::vector<Player> &players) {
    for (auto i = 0; i < num; i++) {
        auto player = Player(100.00, std::to_string(i + 1));
        players.push_back(player);
    }
}
/*
 * Deals two cards to each player from the deck
 * players is the vector containing shared_ptrs to Player objects
 */

void dealCards(Deck &deck, std::vector<Player> &players) {
    for (auto i = 0; i < 2; i++) {
        for (auto j = 0; j < players.size(); j++) {
            auto card = deck.removeCard();
            players[j].addToHand(card);
        }
    }
}

void dealCommunityCards(Deck &deck, std::vector<Card> &community) {
    community = {};
    for (auto i = 0; i < 5; i++) {
        community.push_back(deck.removeCard());
    }
}

void printCommunity(std::vector<Card> &community) {
    std::string retString = "Community Cards: ";
    for (auto i = 0; i < 5; i++) {
        retString += community[i].toString();
        retString += " ";
    }
    std::cout << retString << std::endl;
}

void ante(std::vector<Player> &players) {
    for (auto i = 0; i < players.size(); i++) {
        players[i].removeBalance(2.00);
    }
}
void printPlayersInfo(std::vector<Player> &players) {
    for (auto i = 0; i < players.size(); i++) {
        std::string balance = "Player ";
        std::string bestHand = "   Best hand: ";
        balance += players[i].getName();
        balance += " ";
        balance += players[i].balanceToString();
        balance += " - ";
        balance += players[i].toStringHand();

        bestHand += players[i].toStringBestHand();
        bestHand += "    ";
        bestHand += players[i].getBestHand().toStringHandRank();
        std::cout << balance << std::endl;
        std::cout << bestHand << std::endl;
        std::cout << std::endl;
    }
}
/*
 * returns a vector with the winning Players' names
 */
std::vector<std::string> computeWinners(std::vector<Player> &players) {
    std::vector<std::string> winnerNames;
    Player winner = players[0];
    // Finds the best hand
    for (auto i = 1; i < players.size(); i++) {
        if (winner.getBestHand() < players[i].getBestHand())
            winner = players[i];
    }
    // Creates a vector of the Players with the best hand
    for (auto i = 0; i < players.size(); i++) {
        if (winner.getBestHand() == players[i].getBestHand())
            winnerNames.push_back(players[i].getName());
    }
    return winnerNames;
}
/*
 * Adds the winnings to the Players
 */
void addBalanceToWinners(std::vector<Player> &players, std::vector<std::string> &winners, double pot) {
    for (auto i = 0; i < players.size(); i++) {
        for (auto name : winners) {
            if (name == players[i].getName())
                players[i].addBalance(pot / winners.size());
        }
    }
}
/*
 * Prints out the winners
 */
void printWinners(std::vector<Player> &players, std::vector<std::string> &winners) {
    if (winners.size() == 1) {
        std::cout << "Winner: Player " << winners[0] << " " << players[std::stoi(winners[0]) - 1].balanceToString() << std::endl;
        std::cout << "++++++++++++++++++++++++++++++++++++" << std::endl;
        std::cout << players[std::stoi(winners[0]) - 1 ].toStringBestHand() << "   " << players[std::stoi(winners[0]) - 1].getBestHand().toStringHandRank() << std::endl;
        std::cout << std::endl;

    } else {
        std::cout << "Winning hands (tie)" << std::endl;
        std::cout << "++++++++++++++++++++++++++++++++++++" << std::endl;
        for (auto i = 0; i < winners.size(); i++) {
            std::cout <<  players[std::stoi(winners[i]) - 1].toStringBestHand() << " ";
            std::cout << players[std::stoi(winners[i]) - 1].getBestHand().toStringHandRank();
            std::cout << " Player " << winners[i];
            std::cout << " " << players[std::stoi(winners[i]) - 1].balanceToString() << std::endl;
        }
    }
}

int main() {
    Deck deck;
    deck.initDeck();
    deck.shuffle();

    int number = numberOfPlayers();

    std::vector<Player> players = {};
    std::vector<Card> community = {};
    std::vector<Player> winners = {};
    makePlayers(number, players);

    double pot = number * 2.00;
    bool play = true;
    std::string ans = "y";

    while (play) {
        deck.resetDeck();
        dealCards(deck, players);
        dealCommunityCards(deck, community);
        for (auto i = 0; i < players.size(); i++) {
            players[i].setBestHand(community);
        }
        ante(players);
        printCommunity(community);
        std::cout << "++++++++++++++++++++++++++++++++++++" << std::endl;
        printPlayersInfo(players);
        std::vector<std::string>winners = computeWinners(players);
        addBalanceToWinners(players, winners, pot);
        printWinners(players, winners);
        for (auto i = 0; i < players.size(); i++) {
            players[i].reset();
        }

        std::cout << "Play another game? " << std::endl;
        std::cin >> ans;
        if (ans != "y")
            play = false;
    }

    return 0;
}