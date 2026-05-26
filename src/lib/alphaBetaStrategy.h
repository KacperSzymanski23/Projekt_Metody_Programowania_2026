#ifndef ALPHA_BETA_STRATEGY_H
#define ALPHA_BETA_STRATEGY_H

#include "strategy.h"

namespace TicTacToe {
		class AlphaBetaStrategy : public Strategy {
			  public:
				AlphaBetaStrategy() = default;
				~AlphaBetaStrategy() override = default;
				Move chooseMove(Board<char> &board, char symbol) override;

			  private:
				static int32_t evaluate(const Board<char> &board, char forSymbol);
				int32_t alphaBeta(Board<char> &board, char symbol, bool isMaximizing, int32_t alpha, int32_t beta);
		};
} // namespace TicTacToe

#endif /* ALPHA_BETA_STRATEGY_H */