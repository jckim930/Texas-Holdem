cmake_minimum_required(VERSION 3.13)
project(PokerHand)

set(CMAKE_CXX_STANDARD 14)


include_directories(/Users/Justin/CLionProjects)


add_executable(PokerHand Card.hpp 52Cards.hpp Deck.hpp Player.hpp PokerHand.hpp main.cpp)