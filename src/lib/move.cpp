#include "move.h"

namespace TicTacToe {

		Move::Move(size_t x, size_t y)
			: m_x(x)
			, m_y(y) {
		}

		size_t Move::x() const {
				return m_x;
		}

		size_t Move::y() const {
				return m_y;
		}

} // namespace TicTacToe