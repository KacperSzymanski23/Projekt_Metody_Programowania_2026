#include <catch2/catch_test_macros.hpp>

#include "boardExt.h"
#include "myexceptions.h"

#include <sstream>

/**
 * @brief Testy dla konstruktora klasy BoardExt
 *
 */
TEST_CASE("BoardExt: size() returns the correct value", "[board]") {
		TicTacToe::BoardExt<> b{3};
		REQUIRE(b.size() == 3U);

		TicTacToe::BoardExt<> b5{5};
		REQUIRE(b5.size() == 5U);
}

TEST_CASE("BoardExt: size < 3 throws InvalidArgumentException", "[board]") {
		REQUIRE_THROWS_AS(TicTacToe::BoardExt<>(2U), MyExceptions::InvalidArgumentException);
		REQUIRE_THROWS_AS(TicTacToe::BoardExt<>(0U), MyExceptions::InvalidArgumentException);
}

/**
 * @brief Testy dla inicjalizacja klasy BoardExt
 *
 */
TEST_CASE("BoardExt: all cells are '0' after construction", "[board]") {
		TicTacToe::BoardExt<> b{3};
		for (size_t row{}; row < 3U; ++row) {
				for (size_t col = 0; col < 3U; ++col) {
						REQUIRE(b(col, row) == '.');
				}
		}
}

TEST_CASE("BoardExt: full() returns false on a fresh empty board", "[board]") {
		TicTacToe::BoardExt<> b{3};
		REQUIRE_FALSE(b.full());
}

/**
 * @brief Testy dla operator() klasy BoardExt
 *
 */
TEST_CASE("BoardExt: operator() read/write round-trip", "[board]") {
		TicTacToe::BoardExt<> b{3};
		b(0U, 0U) = 'X';
		b(2U, 1U) = 'O';

		REQUIRE(b(0U, 0U) == 'X');
		REQUIRE(b(2U, 1U) == 'O');
		REQUIRE(b(1U, 1U) == '.'); // puste pole
}

TEST_CASE("BoardExt: out-of-range mutable access throws", "[board]") {
		TicTacToe::BoardExt<> b{3};
		REQUIRE_THROWS_AS(b(3U, 0U), MyExceptions::InvalidArgumentException);
		REQUIRE_THROWS_AS(b(0U, 3U), MyExceptions::InvalidArgumentException);
}

TEST_CASE("BoardExt: out-of-range const access throws", "[board]") {
		const TicTacToe::BoardExt<> CB{3};
		REQUIRE_THROWS_AS(CB(3U, 0U), MyExceptions::InvalidArgumentException);
		REQUIRE_THROWS_AS(CB(0U, 3U), MyExceptions::InvalidArgumentException);
}

/**
 * @brief Testy dla metody full() i clear()
 *
 */
TEST_CASE("BoardExt: full() returns true when every cell is occupied", "[board]") {
		TicTacToe::BoardExt<> b{3};
		for (size_t row{}; row < 3U; ++row) {
				for (size_t col = 0; col < 3U; ++col) {
						b(col, row) = 'X';
				}
		}
		REQUIRE(b.full());
}

TEST_CASE("BoardExt: full() returns false when one cell remains empty", "[board]") {
		TicTacToe::BoardExt<> b{3};
		for (size_t row{}; row < 3U; ++row) {
				for (size_t col{}; col < 3U; ++col) {
						b(col, row) = 'X';
				}
		}
		b(2U, 2U) = '.';
		REQUIRE_FALSE(b.full());
}

TEST_CASE("BoardExt: clear() resets all cells to '0'", "[board]") {
		TicTacToe::BoardExt<> b{3};
		b(0U, 0U) = 'X';
		b(1U, 1U) = 'O';
		b(2U, 2U) = 'X';
		b.clear();

		for (size_t row{}; row < 3U; ++row) {
				for (size_t col{}; col < 3U; ++col) {
						REQUIRE(b(col, row) == '.');
				}
		}
		REQUIRE_FALSE(b.full());
}

TEST_CASE("BoardExt: clear() on already-empty board is a no-op", "[board]") {
		TicTacToe::BoardExt<> b{3};
		REQUIRE_NOTHROW(b.clear());
		REQUIRE_FALSE(b.full());
}

/**
 * @brief Testy dla operator<<
 *
 */
TEST_CASE("operator<<: streams board rows separated by newlines", "[board]") {
		TicTacToe::BoardExt<> b{3};
		b(0U, 0U) = 'X';
		b(1U, 0U) = 'O';
		b(2U, 0U) = 'X';
		// wiersze 1 i 2 będą puste, '0'

		std::ostringstream oss;
		oss << static_cast<const TicTacToe::Board<> &>(b);
		const std::string RESULT = oss.str();

		REQUIRE(RESULT.find("XOX") != std::string::npos);
		REQUIRE(RESULT.find("...") != std::string::npos);
}

TEST_CASE("operator<<: empty board outputs only dots", "[board]") {
		TicTacToe::BoardExt<> b{3};
		std::ostringstream oss;
		oss << static_cast<const TicTacToe::Board<> &>(b);
		const std::string RESULT = oss.str();

		REQUIRE(RESULT.find('X') == std::string::npos);
		REQUIRE(RESULT.find('O') == std::string::npos);
}

/**
 * @brief Testy dla klasy BoardExt dla dużych tablic
 *
 */
TEST_CASE("BoardExt: 5x5 board construction and access", "[board]") {
		TicTacToe::BoardExt<> b{5};
		REQUIRE(b.size() == 5U);
		b(4U, 4U) = 'O';
		REQUIRE(b(4U, 4U) == 'O');
		REQUIRE_THROWS_AS(b(5U, 0U), MyExceptions::InvalidArgumentException);
}
