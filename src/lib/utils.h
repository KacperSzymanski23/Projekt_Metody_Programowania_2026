#include "board.h"

namespace Utils {

		inline bool hasWon(const TicTacToe::Board<char> &board, char symbol) noexcept {
				const size_t BOARD_SIZE = board.size();

				for (size_t row{}; row < BOARD_SIZE; ++row) {
						bool win{true};
						for (std::size_t col = 0; col < BOARD_SIZE; ++col) {
								if (board(col, row) != symbol) {
										win = false;
										break;
								}
						}
						if (win) {
								return true;
						}
				}

				for (size_t column{}; column < BOARD_SIZE; ++column) {
						bool win{true};
						for (std::size_t row = 0; row < BOARD_SIZE; ++row) {
								if (board(column, row) != symbol) {
										win = false;
										break;
								}
						}
						if (win) {
								return true;
						}
				}

				{
						bool win{true};
						for (size_t i{}; i < BOARD_SIZE; ++i) {
								if (board(i, i) != symbol) {
										win = false;
										break;
								}
						}
						if (win) {
								return true;
						}
				}

				{
						bool win{true};
						for (size_t i{}; i < BOARD_SIZE; ++i) {
								if (board(i, BOARD_SIZE - 1U - i) != symbol) {
										win = false;
										break;
								}
						}
						if (win) {
								return true;
						}
				}

				return false;
		}

		inline char getOpponent(char symbol) noexcept {
				return symbol == 'X' ? 'O' : 'X';
		}

} // namespace Utils