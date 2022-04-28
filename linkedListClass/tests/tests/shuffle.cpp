#include "executable.h"
#include "Card.h"
#include <sstream>
#include <list>
#include <vector>

std::list<Card> unshuffle(const List<Card> & deck) {
    static Typegen t(RAND221_SEED);
    std::vector<bool> flips(deck.size());
    for(auto it = flips.rbegin(); it != flips.rend(); it++) {
        *it = t.get<int>() % 2 == 0;
    }

    std::list<Card> unshuffled;
    List<Card> shuffled = deck;
    for(auto it = flips.cbegin(); it != flips.cend(); it++) {
        if(*it) {
            unshuffled.push_front(shuffled.front());
            shuffled.pop_front();
        } else {
            unshuffled.push_front(shuffled.back());
            shuffled.pop_back();
        }
    }

    return unshuffled;
}

TEST(shuffle) {
    Typegen t;
    size_t constexpr N_SUITES = 4;

    {
        std::stringstream ss(FULL_DECK);
        List<Card> deck = buildDeck(ss);
        std::list<Card> unshuffled = unshuffle(shuffle(deck));

        auto it = unshuffled.cbegin();
        size_t i = 0;

        size_t constexpr CARDS_IN_SUITE = 13;
        Rank constexpr RANK_START = 1;
        while(it != unshuffled.cend()) {
            ASSERT_TRUE(it->suit == static_cast<Suit>(i / CARDS_IN_SUITE));
            ASSERT_TRUE(it->rank == static_cast<Rank>(i % CARDS_IN_SUITE + RANK_START));

            it++;
            i++;
        }

        ASSERT_EQ(CARDS_IN_SUITE * N_SUITES, i);
    }

    {
        std::stringstream ss(FACE_CARDS_DECK);
        List<Card> deck = buildDeck(ss);
        std::list<Card> unshuffled = unshuffle(shuffle(deck));

        auto it = unshuffled.cbegin();
        size_t i = 0;

        size_t constexpr CARDS_IN_SUITE = 3;
        Rank constexpr RANK_START = 11;
        while(it != unshuffled.cend()) {
            ASSERT_TRUE(it->suit == static_cast<Suit>(i / CARDS_IN_SUITE));
            ASSERT_TRUE(it->rank == static_cast<Rank>(i % CARDS_IN_SUITE + RANK_START));

            it++;
            i++;
        }

        ASSERT_EQ(CARDS_IN_SUITE * N_SUITES, i);
    }

}
