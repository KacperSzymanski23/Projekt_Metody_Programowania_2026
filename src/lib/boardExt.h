#ifndef BOARD_EXT_H
#define BOARD_EXT_H

#include "board.h"
#include "myexceptions.h"
// STD
#include <algorithm>
#include <vector>

namespace TicTacToe {

		template <typename T = char>
		class BoardExt : public Board<T> {
			  public:
				explicit BoardExt(size_t size)
					: m_n(size)
					, m_fields(size * size, static_cast<T>(NULL)) {
						if (size < 3U) {
								throw MyExceptions::InvalidArgumentException("Board size must be at least 3");
						}
				}

				~BoardExt() override = default;

				BoardExt(const BoardExt &board) noexcept = default;
				BoardExt &operator=(const BoardExt &board) = default;
				BoardExt(BoardExt &&board) = default;
				BoardExt &operator=(BoardExt &&board) noexcept = default;

				[[nodiscard]] size_t size() const override {
						return m_n;
				}

				[[nodiscard]] bool full() const override {
						return std::none_of(m_fields.cbegin(), m_fields.cend(), [](T field) { return field == static_cast<T>(NULL); });
				}

				void clear() override {
						std::fill(m_fields.begin(), m_fields.end(), static_cast<T>(NULL));
				}

				T &operator()(size_t x, size_t y) override {
						validateCoordinates(x, y);
						return m_fields.at(x + (y * m_n));
				}

				T operator()(size_t x, size_t y) const override {
						validateCoordinates(x, y);
						return m_fields.at(x + (y * m_n));
				}

			  private:
				size_t m_n;
				std::vector<T> m_fields;

				void validateCoordinates(size_t x, size_t y) const {
						if (x >= m_n || y >= m_n) {
								throw MyExceptions::InvalidArgumentException("Board coordinates out of range");
						}
				}
		};
} // namespace TicTacToe

#endif /* BOARD_EXT_H */