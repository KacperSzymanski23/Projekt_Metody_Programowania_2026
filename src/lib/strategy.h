#ifndef STRATEGY_H
#define STRATEGY_H

#include "board.h"
#include "move.h"

namespace TicTacToe {

		class Strategy {
			  public:
				Strategy() = default;

				Strategy(const Strategy &) = default;
				Strategy &operator=(const Strategy &) = default;

				Strategy(Strategy &&) = default;
				Strategy &operator=(Strategy &&) = default;

				virtual ~Strategy() = default;

				virtual Move chooseMove(const Board &board, char symbol) = 0;
		};
} // namespace TicTacToe

#endif /* STRATEGY_H */