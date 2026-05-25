#ifndef TIC_TAC_TOE_GAME_H
#define TIC_TAC_TOE_GAME_H

#include "board.h"
#include "strategy.h"

namespace TicTacToe {
		class TicTacToeGame {
			  public:
				TicTacToeGame(Board<char> *board, Strategy *xStrategy, Strategy *oStrategy);
				~TicTacToeGame() = default;

				TicTacToeGame(const TicTacToeGame &) = delete;
				TicTacToeGame &operator=(const TicTacToeGame &) = delete;
				TicTacToeGame(TicTacToeGame &&) = delete;
				TicTacToeGame &operator=(TicTacToeGame &&) = delete;

				bool makeMove(Move move, char symbol);
				void play();

				[[nodiscard]] bool finished() const;
				[[nodiscard]] char winner() const;

				void changeStrategy(char symbol, Strategy *strategy);

			  private:
				Board<char> *m_board;

				Strategy *m_xStrategy;
				Strategy *m_oStrategy;

				char m_currentTurnSymbol;
		};
} // namespace TicTacToe

#endif /* TIC_TAC_TOE_GAME_H */