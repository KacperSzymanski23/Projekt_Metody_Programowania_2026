#include "alphaBetaStrategy.h"
#include "boardExt.h"
#include "minMaxStrategy.h"
#include "ticTacToeGame.h"
// STD
#include <cstdint>
#include <iostream>

int32_t main(int32_t argc, char const *argv[]) {
		TicTacToe::Board<> *b = new TicTacToe::BoardExt<>(3);
		TicTacToe::Strategy *s1 = new TicTacToe::MinMaxStrategy();
		TicTacToe::Strategy *s2 = new TicTacToe::AlphaBetaStrategy();
		TicTacToe::TicTacToeGame *g = new TicTacToe::TicTacToeGame(b, s1, s2);

		g->play();
		std::cout << *b << '\n';
		std::cout << g->winner() << '\n';

		g->changeStrategy('X', s2);
		b->clear();
		g->play();
		std::cout << *b << '\n';
		std::cout << g->winner() << '\n';

		delete g;
		delete s2;
		delete s1;
		delete b;

		return 0;
}
