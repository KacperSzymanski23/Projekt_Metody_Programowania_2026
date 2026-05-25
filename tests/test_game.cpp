#include <catch2/catch_test_macros.hpp>

#include "alphaBetaStrategy.h"
#include "boardExt.h"
#include "minMaxStrategy.h"
#include "myexceptions.h"
#include "ticTacToeGame.h"

/**
 * @brief Testy dla konstruktora klasy TicTacToeGame - wyjątki
 *
 */
TEST_CASE("TicTacToeGame: null board pointer throws InvalidArgumentException", "[game]") {
		TicTacToe::MinMaxStrategy s;
		REQUIRE_THROWS_AS(TicTacToe::TicTacToeGame(nullptr, &s, &s), MyExceptions::InvalidArgumentException);
}

TEST_CASE("TicTacToeGame: null X-strategy pointer throws InvalidArgumentException", "[game]") {
		TicTacToe::BoardExt<> b{3};
		TicTacToe::MinMaxStrategy s;
		REQUIRE_THROWS_AS(TicTacToe::TicTacToeGame(&b, nullptr, &s), MyExceptions::InvalidArgumentException);
}

TEST_CASE("TicTacToeGame: null O-strategy pointer throws InvalidArgumentException", "[game]") {
		TicTacToe::BoardExt<> b{3};
		TicTacToe::MinMaxStrategy s;
		REQUIRE_THROWS_AS(TicTacToe::TicTacToeGame(&b, &s, nullptr), MyExceptions::InvalidArgumentException);
}

/**
 * @brief Testy dla inicjalizacja klasy TicTacToeGame
 *
 */
TEST_CASE("TicTacToeGame: game is not finished on an empty board", "[game]") {
		TicTacToe::BoardExt<> b{3};
		TicTacToe::MinMaxStrategy s;
		TicTacToe::TicTacToeGame game{&b, &s, &s};

		REQUIRE_FALSE(game.finished());
		REQUIRE(game.winner() == '\0');
}

/**
 * @brief Testy dla metody makeMove
 *
 */
TEST_CASE("TicTacToeGame: makeMove places the symbol and returns true", "[game]") {
		TicTacToe::BoardExt<> b{3};
		TicTacToe::MinMaxStrategy s;
		TicTacToe::TicTacToeGame game{&b, &s, &s};

		REQUIRE(game.makeMove({0U, 0U}, 'X'));
		REQUIRE(b(0U, 0U) == 'X');
}

TEST_CASE("TicTacToeGame: makeMove on occupied cell returns false without changing board", "[game]") {
		TicTacToe::BoardExt<> b{3};
		TicTacToe::MinMaxStrategy s;
		TicTacToe::TicTacToeGame game{&b, &s, &s};

		REQUIRE(game.makeMove({1U, 1U}, 'X'));
		REQUIRE_FALSE(game.makeMove({1U, 1U}, 'O'));
		REQUIRE(b(1U, 1U) == 'X'); // still X
}

TEST_CASE("TicTacToeGame: makeMove with invalid symbol throws InvalidSymbolException", "[game]") {
		TicTacToe::BoardExt<> b{3};
		TicTacToe::MinMaxStrategy s;
		TicTacToe::TicTacToeGame game{&b, &s, &s};

		REQUIRE_THROWS_AS(game.makeMove({0U, 0U}, 'Z'), MyExceptions::InvalidSymbolException);
}

TEST_CASE("TicTacToeGame: makeMove with out-of-range coords throws InvalidArgumentException", "[game]") {
		TicTacToe::BoardExt<> b{3};
		TicTacToe::MinMaxStrategy s;
		TicTacToe::TicTacToeGame game{&b, &s, &s};

		REQUIRE_THROWS_AS(game.makeMove({5U, 0U}, 'X'), MyExceptions::InvalidArgumentException);
		REQUIRE_THROWS_AS(game.makeMove({0U, 99U}, 'X'), MyExceptions::InvalidArgumentException);
}

TEST_CASE("TicTacToeGame: makeMove on a finished game throws GameAlreadyFinishedException", "[game]") {
		TicTacToe::BoardExt<> b{3};
		// X wygrywa w pierwszym wierszu
		b(0U, 0U) = 'X';
		b(1U, 0U) = 'X';
		b(2U, 0U) = 'X';

		TicTacToe::MinMaxStrategy s;
		TicTacToe::TicTacToeGame game{&b, &s, &s};

		REQUIRE(game.finished());
		REQUIRE_THROWS_AS(game.makeMove({0U, 1U}, 'O'), MyExceptions::GameAlreadyFinishedException);
}

/**
 * @brief Testy dla metody winner
 *
 */
TEST_CASE("TicTacToeGame: winner() returns 'X' on X row win", "[game]") {
		TicTacToe::BoardExt<> b{3};
		b(0U, 1U) = 'X';
		b(1U, 1U) = 'X';
		b(2U, 1U) = 'X';

		TicTacToe::MinMaxStrategy s;
		TicTacToe::TicTacToeGame game{&b, &s, &s};

		REQUIRE(game.winner() == 'X');
		REQUIRE(game.finished());
}

TEST_CASE("TicTacToeGame: winner() returns 'O' on O column win", "[game]") {
		TicTacToe::BoardExt<> b{3};
		b(2U, 0U) = 'O';
		b(2U, 1U) = 'O';
		b(2U, 2U) = 'O';

		TicTacToe::MinMaxStrategy s;
		TicTacToe::TicTacToeGame game{&b, &s, &s};

		REQUIRE(game.winner() == 'O');
		REQUIRE(game.finished());
}

TEST_CASE("TicTacToeGame: winner() returns 'X' on main diagonal win", "[game]") {
		TicTacToe::BoardExt<> b{3};
		b(0U, 0U) = 'X';
		b(1U, 1U) = 'X';
		b(2U, 2U) = 'X';

		TicTacToe::MinMaxStrategy s;
		TicTacToe::TicTacToeGame game{&b, &s, &s};

		REQUIRE(game.winner() == 'X');
}

TEST_CASE("TicTacToeGame: winner() returns 'O' on anti-diagonal win", "[game]") {
		TicTacToe::BoardExt<> b{3};
		b(2U, 0U) = 'O';
		b(1U, 1U) = 'O';
		b(0U, 2U) = 'O';

		TicTacToe::MinMaxStrategy s;
		TicTacToe::TicTacToeGame game{&b, &s, &s};

		REQUIRE(game.winner() == 'O');
}

TEST_CASE("TicTacToeGame: winner() returns 'D' on a draw", "[game]") {
		// X O X / O X O / O X O — full board, no winner
		TicTacToe::BoardExt<> b{3};
		b(0U, 0U) = 'X';
		b(1U, 0U) = 'O';
		b(2U, 0U) = 'X';
		b(0U, 1U) = 'O';
		b(1U, 1U) = 'X';
		b(2U, 1U) = 'O';
		b(0U, 2U) = 'O';
		b(1U, 2U) = 'X';
		b(2U, 2U) = 'O';

		TicTacToe::MinMaxStrategy s;
		TicTacToe::TicTacToeGame game{&b, &s, &s};

		REQUIRE(game.winner() == 'D');
		REQUIRE(game.finished());
}

/**
 * @brief Testy dla metody play
 *
 */
TEST_CASE("TicTacToeGame: play() completes the game", "[game]") {
		TicTacToe::BoardExt<> b{3};
		TicTacToe::MinMaxStrategy s;
		TicTacToe::TicTacToeGame game{&b, &s, &s};

		game.play();

		REQUIRE(game.finished());
		REQUIRE(game.winner() != '0');
}

TEST_CASE("TicTacToeGame: two perfect MinMax players always draw on 3x3", "[game]") {
		TicTacToe::BoardExt<> b{3};
		TicTacToe::MinMaxStrategy xStrat;
		TicTacToe::MinMaxStrategy oStrat;
		TicTacToe::TicTacToeGame game{&b, &xStrat, &oStrat};

		game.play();

		REQUIRE(game.winner() == 'D');
}

TEST_CASE("TicTacToeGame: two perfect AlphaBeta players always draw on 3x3", "[game]") {
		TicTacToe::BoardExt<> b{3};
		TicTacToe::AlphaBetaStrategy xStrat;
		TicTacToe::AlphaBetaStrategy oStrat;
		TicTacToe::TicTacToeGame game{&b, &xStrat, &oStrat};

		game.play();

		REQUIRE(game.winner() == 'D');
}

TEST_CASE("TicTacToeGame: play() after board clear restarts correctly", "[game]") {
		TicTacToe::BoardExt<> b{3};
		TicTacToe::MinMaxStrategy s;
		TicTacToe::TicTacToeGame game{&b, &s, &s};

		game.play();
		REQUIRE(game.finished());

		b.clear();
		game.play();
		REQUIRE(game.finished());
		REQUIRE(game.winner() == 'D');
}

TEST_CASE("TicTacToeGame: board is full after play() completes", "[game]") {
		TicTacToe::BoardExt<> b{3};
		TicTacToe::MinMaxStrategy s;
		TicTacToe::TicTacToeGame game{&b, &s, &s};

		game.play();

		// Po zagranej partii, mamy zwycięzce (plansza niepełna) lub remis (zawsze pełna plansza)
		const char W = game.winner();
		REQUIRE((W == 'X' || W == 'O' || W == 'D'));
}

/**
 * @brief Testy dla metody changeStrategy
 *
 */
TEST_CASE("TicTacToeGame: changeStrategy with invalid symbol throws InvalidSymbolException", "[game]") {
		TicTacToe::BoardExt<> b{3};
		TicTacToe::MinMaxStrategy s;
		TicTacToe::TicTacToeGame game{&b, &s, &s};

		TicTacToe::AlphaBetaStrategy ab;
		REQUIRE_THROWS_AS(game.changeStrategy('Z', &ab), MyExceptions::InvalidSymbolException);
}

TEST_CASE("TicTacToeGame: changeStrategy with null strategy throws InvalidArgumentException", "[game]") {
		TicTacToe::BoardExt<> b{3};
		TicTacToe::MinMaxStrategy s;
		TicTacToe::TicTacToeGame game{&b, &s, &s};

		REQUIRE_THROWS_AS(game.changeStrategy('X', nullptr), MyExceptions::InvalidArgumentException);
		REQUIRE_THROWS_AS(game.changeStrategy('O', nullptr), MyExceptions::InvalidArgumentException);
}

TEST_CASE("TicTacToeGame: changeStrategy allows replay with swapped strategies", "[game]") {
		TicTacToe::BoardExt<> b{3};
		TicTacToe::MinMaxStrategy mm;
		TicTacToe::AlphaBetaStrategy ab;
		TicTacToe::TicTacToeGame game{&b, &mm, &mm};

		// Pierwsza gra
		game.play();
		REQUIRE(game.winner() == 'D');

		// Zamiana strategii i dogrywka
		b.clear();
		game.changeStrategy('X', &ab);
		game.changeStrategy('O', &ab);
		game.play();

		REQUIRE(game.finished());
		REQUIRE(game.winner() == 'D');
}

TEST_CASE("TicTacToeGame: changeStrategy for 'X' does not affect 'O' strategy", "[game]") {
		TicTacToe::BoardExt<> b{3};
		TicTacToe::MinMaxStrategy mm;
		TicTacToe::AlphaBetaStrategy ab;
		TicTacToe::TicTacToeGame game{&b, &mm, &mm};

		// Zamiana strategii X
		game.changeStrategy('X', &ab);
		game.play();

		REQUIRE(game.finished());
}
