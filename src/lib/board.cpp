#include "board.h"

namespace TicTacToe {
		std::ostream &operator<<(std::ostream &output, const Board<char> &board) {
				const size_t BOARD_SIZE = board.size();

				for (size_t y = 0; y < BOARD_SIZE; y++) {
						for (size_t x = 0; x < BOARD_SIZE; x++) {
								output << board(x, y);
						}
						output << '\n';
				}
				return output;
		}
} // namespace TicTacToe