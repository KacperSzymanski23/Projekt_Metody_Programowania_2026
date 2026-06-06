#include "board.h"
// Tracy
#include <tracy/Tracy.hpp>

namespace Utils {

		inline bool hasWon(const TicTacToe::Board<char> &board, char symbol) noexcept {
				ZoneScoped;

				const size_t BOARD_SIZE = board.size();

				bool win{};

				for (size_t row{}; row < BOARD_SIZE; ++row) {
						win = true;
						for (size_t column{}; column < BOARD_SIZE; ++column) {
								if (board(column, row) != symbol) {
										win = false;
										break;
								}
						}
						if (win) {
								return true;
						}
				}

				for (size_t column{}; column < BOARD_SIZE; ++column) {
						win = true;
						for (size_t row{}; row < BOARD_SIZE; ++row) {
								if (board(column, row) != symbol) {
										win = false;
										break;
								}
						}
						if (win) {
								return true;
						}
				}

				win = true;
				for (size_t i{}; i < BOARD_SIZE; ++i) {
						if (board(i, i) != symbol) {
								win = false;
								break;
						}
				}
				if (win) {
						return true;
				}

				win = true;
				for (size_t i{}; i < BOARD_SIZE; ++i) {
						if (board(i, BOARD_SIZE - 1U - i) != symbol) {
								win = false;
								break;
						}
				}
				return win;
		}

		inline char getOpponent(char symbol) noexcept {
				return symbol == 'X' ? 'O' : 'X';
		}

} // namespace Utils