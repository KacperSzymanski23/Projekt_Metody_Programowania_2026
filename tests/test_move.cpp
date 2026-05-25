#include <catch2/catch_test_macros.hpp>

#include "move.h"

/**
 * @brief Testy dla klasy Move
 *
 */

TEST_CASE("Move: stores x and y coordinates correctly", "[move]") {
		const TicTacToe::Move M{2U, 5U};
		REQUIRE(M.x() == 2U);
		REQUIRE(M.y() == 5U);
}

TEST_CASE("Move: zero coordinates are valid", "[move]") {
		const TicTacToe::Move M{0U, 0U};
		REQUIRE(M.x() == 0U);
		REQUIRE(M.y() == 0U);
}

TEST_CASE("Move: large coordinates are stored without truncation", "[move]") {
		const TicTacToe::Move M{100U, 999U};
		REQUIRE(M.x() == 100U);
		REQUIRE(M.y() == 999U);
}

TEST_CASE("Move: x and y are independent", "[move]") {
		const TicTacToe::Move M{7U, 3U};
		REQUIRE(M.x() == 7U);
		REQUIRE(M.y() == 3U);
}
