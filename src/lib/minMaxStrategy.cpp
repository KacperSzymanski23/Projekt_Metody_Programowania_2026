#include "minMaxStrategy.h"
#include "board.h"
#include "myexceptions.h"
#include "utils.h"

namespace TicTacToe {
		Move MinMaxStrategy::chooseMove(Board<char> &board, char symbol) {
				if (symbol != 'X' && symbol != 'O') {
						throw MyExceptions::InvalidSymbolException("Symbol must be X or O");
				}
				if (board.full()) {
						throw MyExceptions::InvalidMoveException("Board is full");
				}

				int32_t bestScore{std::numeric_limits<int32_t>::min()};
				size_t bestColumn{};
				size_t bestRow{};

				bool found{false};

				const size_t BOARD_SIZE = board.size();

				for (size_t row{}; row < BOARD_SIZE; ++row) {
						for (size_t column{}; column < BOARD_SIZE; ++column) {
								if (board(column, row) == '\0') {
										board(column, row) = symbol;

										const int32_t SCORE = minimax(board, symbol, false);

										board(column, row) = '\0';

										if (SCORE > bestScore || !found) {
												bestScore = SCORE;
												bestColumn = column;
												bestRow = row;
												found = true;
										}
								}
						}
				}

				if (!found) {
						throw MyExceptions::InvalidArgumentException("No possible move found");
				}

				return {bestColumn, bestRow};
		}

		int32_t MinMaxStrategy::evaluate(const Board<char> &board, char forSymbol) {
				if (Utils::hasWon(board, forSymbol)) {
						return 1;
				}

				if (Utils::hasWon(board, forSymbol == 'X' ? 'O' : 'X')) {
						return -1;
				}

				return 0;
		}

		int32_t MinMaxStrategy::minimax(Board<char> &board, char symbol, bool isMaximizing) {
				const int32_t SCORE = evaluate(board, symbol);

				if (SCORE != 0 || board.full()) {
						return SCORE;
				}

				const size_t BOARD_SIZE = board.size();
				const char CURRENT_SYMBOL = isMaximizing ? symbol : Utils::getOpponent(symbol);

				if (isMaximizing) {
						int32_t best = std::numeric_limits<int32_t>::min();
						for (size_t row{}; row < BOARD_SIZE; ++row) {
								for (size_t column{}; column < BOARD_SIZE; ++column) {
										if (board(column, row) == '\0') {
												board(column, row) = CURRENT_SYMBOL;

												best = std::max(best, minimax(board, symbol, false));

												board(column, row) = '\0';
										}
								}
						}
						return best;
				}

				int32_t best = std::numeric_limits<int32_t>::max();
				for (size_t row{}; row < BOARD_SIZE; ++row) {
						for (size_t column{}; column < BOARD_SIZE; ++column) {
								if (board(column, row) == '\0') {
										board(column, row) = CURRENT_SYMBOL;

										best = std::min(best, minimax(board, symbol, true));

										board(column, row) = '\0';
								}
						}
				}

				return best;
		}
} // namespace TicTacToe