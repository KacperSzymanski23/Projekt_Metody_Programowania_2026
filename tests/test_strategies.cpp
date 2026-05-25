#include <catch2/catch_test_macros.hpp>

#include "alphaBetaStrategy.h"
#include "boardExt.h"
#include "minMaxStrategy.h"
#include "myexceptions.h"

/**
 * @brief Funkcja pomocnicza do wczytywania planszy
 *
 * @param board Plansza
 * @param cells Kolejne znaki znajdujące się na planszy
 */

static void loadBoard(TicTacToe::Board<> &board, const char *cells) {
		const size_t N{board.size()};
		for (size_t row{}; row < N; ++row) {
				for (size_t col{}; col < N; ++col) {
						const char CELL{cells[(row * N) + col]};
						board(col, row) = CELL == '0' ? '\0' : CELL;
				}
		}
}

/**
 * @brief Testy dla klasy MinMaxStrategy
 *
 */
TEST_CASE("MinMaxStrategy: invalid symbol throws InvalidSymbolException", "[minmax]") {
		TicTacToe::BoardExt<> b{3};
		TicTacToe::MinMaxStrategy s;
		REQUIRE_THROWS_AS(s.chooseMove(b, 'Z'), MyExceptions::InvalidSymbolException);
		REQUIRE_THROWS_AS(s.chooseMove(b, '0'), MyExceptions::InvalidSymbolException);
}

TEST_CASE("MinMaxStrategy: full board throws InvalidMoveException", "[minmax]") {
		TicTacToe::BoardExt<> b{3};
		// X O X
		// O X O
		// O X O - brak zwycięzców, plansza jest pełna
		loadBoard(b, "XOXOXOOXO");
		TicTacToe::MinMaxStrategy s;
		REQUIRE_THROWS_AS(s.chooseMove(b, 'X'), MyExceptions::InvalidMoveException);
}

/**
 * @brief Testy dla klasy MinMaxStrategy, dla natychmiastowej wygranej / blokady
 *
 */
TEST_CASE("MinMaxStrategy: takes the single winning move for X (row)", "[minmax]") {
		// X _ X  ->  X musi zagrać (1,0) aby wygrać w wierszu 0
		// O O 0
		// 0 0 0
		TicTacToe::BoardExt<> b{3};
		loadBoard(b, "X0XOO0000"); // row0=X0X  row1=OO0  row2=000
		TicTacToe::MinMaxStrategy s;
		const TicTacToe::Move M = s.chooseMove(b, 'X');
		REQUIRE(M.x() == 1U);
		REQUIRE(M.y() == 0U);
}

TEST_CASE("MinMaxStrategy: blocks O from winning on a column", "[minmax]") {
		// X O 0
		// 0 O 0
		// 0 0 0  ->  X musi zablokować (1,2)
		TicTacToe::BoardExt<> b{3};
		loadBoard(b, "XO00O0000"); // row0=XO0  row1=0O0  row2=000
		TicTacToe::MinMaxStrategy s;
		const TicTacToe::Move M = s.chooseMove(b, 'X');
		REQUIRE(M.x() == 1U);
		REQUIRE(M.y() == 2U);
}

TEST_CASE("MinMaxStrategy: takes winning move on main diagonal", "[minmax]") {
		// X O X
		// O X O
		// O 0 0  ->  tylko (2,2) wygrywa diagonalnie wszystkie inne wiersze remis

		TicTacToe::BoardExt<> b{3};
		loadBoard(b, "XOXOXOO00"); // row0=XOX  row1=OXO  row2=O..
		TicTacToe::MinMaxStrategy s;
		const TicTacToe::Move M = s.chooseMove(b, 'X');
		REQUIRE(M.x() == 2U);
		REQUIRE(M.y() == 2U);
}

/**
 * @brief Testy dla klasy AlphaBetaStrategy - błędne symbole
 *
 */
TEST_CASE("AlphaBetaStrategy: invalid symbol throws InvalidSymbolException", "[alphabeta]") {
		TicTacToe::BoardExt<> b{3};
		TicTacToe::AlphaBetaStrategy s;
		REQUIRE_THROWS_AS(s.chooseMove(b, '!'), MyExceptions::InvalidSymbolException);
		REQUIRE_THROWS_AS(s.chooseMove(b, 'x'), MyExceptions::InvalidSymbolException);
}

TEST_CASE("AlphaBetaStrategy: full board throws InvalidMoveException", "[alphabeta]") {
		TicTacToe::BoardExt<> b{3};
		loadBoard(b, "XOXOXOOXO");
		TicTacToe::AlphaBetaStrategy s;
		REQUIRE_THROWS_AS(s.chooseMove(b, 'O'), MyExceptions::InvalidMoveException);
}

/**
 * @brief Testy dla klasy AlphaBetaStrategy - natychmiastowe wygrane / blokady
 *
 */
TEST_CASE("AlphaBetaStrategy: takes the only remaining cell (sole valid move)", "[alphabeta]") {
		// O O 0
		// X X O
		// X O X  ->  tylko (2,0) jest puste, O gra (2, 0) i wygrywa
		TicTacToe::BoardExt<> b{3};
		loadBoard(b, "OO0XXOXOX");
		TicTacToe::AlphaBetaStrategy s;
		const TicTacToe::Move M = s.chooseMove(b, 'O');
		REQUIRE(M.x() == 2U);
		REQUIRE(M.y() == 0U);
}

TEST_CASE("AlphaBetaStrategy: X wins col0 and blocks O anti-diagonal", "[alphabeta]") {
		// X X O
		// X O 0    dwa puste pola: (2,1) i (0,2)
		// 0 X O
		// O może wygrać djagonalnie (2,0)-(1,1)-(0,2).
		// X gra (0,2): wypełniając col 0 (X wygrywa!) i blokuje O.

		TicTacToe::BoardExt<> b{3};
		loadBoard(b, "XXOXO00XO"); // row0=XXO  row1=XO.  row2=0XO
		TicTacToe::AlphaBetaStrategy s;
		const TicTacToe::Move M = s.chooseMove(b, 'X');
		REQUIRE(M.x() == 0U);
		REQUIRE(M.y() == 2U);
}

TEST_CASE("AlphaBetaStrategy: takes the single winning move for O (column)", "[alphabeta]") {
		// 0 O X
		// X O O  ->  O gra (1,2) wypełnia column 1 i wygrywa
		// X 0 X      (0,0) może pozwolić X wygrać w column 0 w następnej turze (score -1).
		TicTacToe::BoardExt<> b{3};
		loadBoard(b, "0OXXOOX0X"); // row0=0OX  row1=XOO  row2=X0X
		TicTacToe::AlphaBetaStrategy s;
		const TicTacToe::Move M = s.chooseMove(b, 'O');
		REQUIRE(M.x() == 1U);
		REQUIRE(M.y() == 2U);
}

/**
 * @brief MinMax vs AlphaBeta — porównanie wyników dla pustej planszy
 *
 */
TEST_CASE("Both strategies choose a valid empty cell on fresh 3x3", "[equivalence]") {
		TicTacToe::BoardExt<> b{3};
		TicTacToe::MinMaxStrategy mm;
		TicTacToe::AlphaBetaStrategy ab;

		const TicTacToe::Move MM_MOVE = mm.chooseMove(b, 'X');
		const TicTacToe::Move AB_MOVE = ab.chooseMove(b, 'X');

		REQUIRE(b(MM_MOVE.x(), MM_MOVE.y()) == '\0');
		REQUIRE(b(AB_MOVE.x(), AB_MOVE.y()) == '\0');
}

TEST_CASE("MinMax first move on 3x3 is within board bounds", "[minmax]") {
		TicTacToe::BoardExt<> b{3};
		TicTacToe::MinMaxStrategy s;
		const TicTacToe::Move M = s.chooseMove(b, 'O');
		REQUIRE(M.x() < 3U);
		REQUIRE(M.y() < 3U);
}

TEST_CASE("AlphaBeta first move on 3x3 is within board bounds", "[alphabeta]") {
		TicTacToe::BoardExt<> b{3};
		TicTacToe::AlphaBetaStrategy s;
		const TicTacToe::Move M = s.chooseMove(b, 'O');
		REQUIRE(M.x() < 3U);
		REQUIRE(M.y() < 3U);
}
