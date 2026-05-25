#ifndef BOARD_H
#define BOARD_H

// STD
#include <cstddef>
#include <ostream>

namespace TicTacToe {

		template <typename T = char>
		class Board {
			  public:
				Board() = default;
				Board(const Board &) = default;
				Board &operator=(const Board &) = default;
				Board(Board &&) = default;
				Board &operator=(Board &&) = default;
				virtual ~Board() = default;

				[[nodiscard]] virtual size_t size() const = 0;
				[[nodiscard]] virtual bool full() const = 0;

				[[nodiscard]] virtual T operator()(size_t x, size_t y) const = 0;
				virtual T &operator()(size_t x, size_t y) = 0;

				friend std::ostream &operator<<(std::ostream &output, const Board &board);

				virtual void clear() = 0;

				[[nodiscard]] virtual bool isEmpty() const = 0;
		};
} // namespace TicTacToe

#endif /* BOARD_H */