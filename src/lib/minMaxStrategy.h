#ifndef MIN_MAX_STRATEGY_H
#define MIN_MAX_STRATEGY_H

#include "strategy.h"

// 1 = win, -1 = lose, 0 = draw
namespace TicTacToe {
		class MinMaxStrategy : public Strategy {
			  public:
				MinMaxStrategy() = default;
				~MinMaxStrategy() override = default;

				Move chooseMove(Board<char> &board, char symbol) override;

			  private:
				int32_t evaluate(const Board<char> &board, char forSymbol);
				int32_t minimax(Board<char> &board, char symbol, bool isMaximizing);
		};
} // namespace TicTacToe

#endif /* MIN_MAX_STRATEGY_H */