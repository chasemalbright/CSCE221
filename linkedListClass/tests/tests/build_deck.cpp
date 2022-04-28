#include "executable.h"
#include "Card.h"
#include <sstream>

TEST(build_deck) {
    Typegen t;
    size_t constexpr N_SUITES = 4;

    {
        std::stringstream ss(FULL_DECK);
        List<Card> deck = buildDeck(ss);

        auto it = deck.cbegin();
        size_t i = 0;

        size_t constexpr CARDS_IN_SUITE = 13;
        Rank constexpr RANK_START = 1;
        while(it != deck.cend()) {
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

        auto it = deck.cbegin();
        size_t i = 0;

        size_t constexpr CARDS_IN_SUITE = 3;
        Rank constexpr RANK_START = 11;
        while(it != deck.cend()) {
            ASSERT_TRUE(it->suit == static_cast<Suit>(i / CARDS_IN_SUITE));
            ASSERT_TRUE(it->rank == static_cast<Rank>(i % CARDS_IN_SUITE + RANK_START));

            it++;
            i++;
        }

        ASSERT_EQ(CARDS_IN_SUITE * N_SUITES, i);
    }

}
