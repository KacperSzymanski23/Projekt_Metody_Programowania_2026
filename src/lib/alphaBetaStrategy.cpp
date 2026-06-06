#include "alphaBetaStrategy.h"
#include "myexceptions.h"
#include "utils.h"
// STD
#include <limits>
// Tracy
#include <tracy/Tracy.hpp>

namespace TicTacToe {
		Move AlphaBetaStrategy::chooseMove(Board<char> &board, char symbol) {
				ZoneScoped;

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

				constexpr int32_t ALPHA_INIT = std::numeric_limits<int32_t>::min();
				constexpr int32_t BETA_INIT = std::numeric_limits<int32_t>::max();

				const size_t BOARD_SIZE = board.size();

				for (size_t row{}; row < BOARD_SIZE; ++row) {
						for (size_t column{}; column < BOARD_SIZE; ++column) {
								if (board(column, row) == '.') {
										board(column, row) = symbol;

										const int32_t SCORE = alphaBeta(board, symbol, false, ALPHA_INIT, BETA_INIT);

										board(column, row) = '.';

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
						throw MyExceptions::InvalidArgumentException("No move found");
				}

				return {bestColumn, bestRow};
		}

		int32_t AlphaBetaStrategy::evaluate(const Board<char> &board, char forSymbol) {
				ZoneScoped;

				if (Utils::hasWon(board, forSymbol)) {
						return 1;
				}

				if (Utils::hasWon(board, Utils::getOpponent(forSymbol))) {
						return -1;
				}

				return 0;
		}

		int32_t AlphaBetaStrategy::alphaBeta(Board<char> &board, char symbol, bool isMaximizing, int32_t alpha, int32_t beta) {
				ZoneScoped;

				const int32_t SCORE = evaluate(board, symbol);

				if (SCORE != 0 || board.full()) {
						return SCORE;
				}

				const size_t BOARD_SIZE = board.size();
				const char CURRENT_SYMBOL = isMaximizing ? symbol : Utils::getOpponent(symbol);

				if (isMaximizing) {
						int32_t bestScore{std::numeric_limits<int32_t>::min()};

						for (size_t row{}; row < BOARD_SIZE; ++row) {
								for (size_t column{}; column < BOARD_SIZE; ++column) {
										if (board(column, row) == '.') {
												board(column, row) = CURRENT_SYMBOL;

												const int32_t TEMP_SCORE = alphaBeta(board, symbol, false, alpha, beta);

												board(column, row) = '.';

												bestScore = std::max(bestScore, TEMP_SCORE);
												alpha = std::max(alpha, bestScore);

												if (beta <= alpha) {
														return bestScore;
												}
										}
								}
						}

						return bestScore;
				}

				int32_t bestScore{std::numeric_limits<int32_t>::max()};

				for (size_t row{}; row < BOARD_SIZE; ++row) {
						for (size_t column{}; column < BOARD_SIZE; ++column) {
								if (board(column, row) == '.') {
										board(column, row) = CURRENT_SYMBOL;

										const int32_t TEMP_SCORE = alphaBeta(board, symbol, true, alpha, beta);

										board(column, row) = '.';

										bestScore = std::min(bestScore, TEMP_SCORE);
										beta = std::min(beta, bestScore);

										if (beta <= alpha) {
												return bestScore;
										}
								}
						}
				}

				return bestScore;
		}
} // namespace TicTacToe