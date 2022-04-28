#include <string>
#include <sstream>

#include "Card.h"

int rand221(void) {
    return rand();
}

// You may want to write the following three functions, but they are not required

// std::istream& operator>>(std::istream& in, Suit& suit) {
//    
// }

// Rank to_rank(const std::string& string) {
//    
// }

std::istream& operator>>(std::istream& in, Card& card) {
    std::string r;
    std::string s;

    getline(in,s,' ');
    if (s == "spades"){
        card.suit = Suit::SPADES;
    } else if (s == "diamonds"){
        card.suit = Suit::DIAMONDS;
    } else if (s == "clubs"){
        card.suit = Suit::CLUBS;
    } else {
        card.suit = Suit::HEARTS;
    }
    

    getline(in,r,'\n');
    if (r == "jack"){
        card.rank = 11;
    } else if (r == "queen"){
        card.rank = 12;
    } else if (r == "king"){
        card.rank = 13;
    } else if (r == "ace"){
        card.rank = 1;
    } else {
        card.rank = std::stoi(r);
    }
    return in;
}

List<Card> buildDeck(std::istream& file) {
    List<Card> deck;
    
    std::string line;
    Card card;
    while (getline(file, line)){
        if (!line.empty()){
            std::istringstream str{line};
            if (str >> card){
                deck.push_back(card);
            }
        }
    }


    return deck;
}

List<Card> shuffle(const List<Card>& deck) {
    List <Card> newDeck;

    for (const Card& card : deck){
        if (rand221() % 2 == 0){ //if even
            newDeck.push_front(card);
        } else{ //if odd
            newDeck.push_back(card);
        }
    }
    return newDeck;


}