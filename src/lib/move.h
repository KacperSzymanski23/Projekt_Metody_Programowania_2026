#ifndef MOVE_H
#define MOVE_H

// STD
#include <cstddef>

namespace TicTacToe {
		class Move {
			  public:
				Move(size_t x, size_t y);

				[[nodiscard]] size_t x() const;
				[[nodiscard]] size_t y() const;

			  private:
				size_t m_x;
				size_t m_y;
		};
} // namespace TicTacToe

#endif /* MOVE_H */