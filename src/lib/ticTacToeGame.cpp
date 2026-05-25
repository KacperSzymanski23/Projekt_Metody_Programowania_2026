#include "ticTacToeGame.h"
#include "myexceptions.h"
#include "utils.h"

namespace TicTacToe {

		TicTacToeGame::TicTacToeGame(Board<char> *board, Strategy *xStrategy, Strategy *oStrategy)
			: m_board(board)
			, m_xStrategy(xStrategy)
			, m_oStrategy(oStrategy)
			, m_currentTurnSymbol('X') {

				if (board == nullptr) {
						throw std::invalid_argument("Board cannot be nullptr");
				}
				if (xStrategy == nullptr) {
						throw std::invalid_argument("X strategy cannot be nullptr");
				}
				if (oStrategy == nullptr) {
						throw std::invalid_argument("O strategy cannot be nullptr");
				}
		}

		bool TicTacToeGame::makeMove(Move move, char symbol) {
				if (symbol != 'X' && symbol != 'O') {
						throw MyExceptions::InvalidArgumentException("Symbol must be X or O");
				}

				if (finished()) {
						throw MyExceptions::InvalidArgumentException("Move cannot be made after game is finished");
				}

				const size_t BOARD_SIZE{m_board->size()};

				if (move.x() >= BOARD_SIZE || move.y() >= BOARD_SIZE) {
						throw MyExceptions::InvalidArgumentException("Move coordinates out of range");
				}

				if ((*m_board)(move.x(), move.y()) != '\0') {
						return false;
				}

				(*m_board)(move.x(), move.y()) = symbol;

				m_currentTurnSymbol = Utils::getOpponent(symbol);

				return true;
		}

		void TicTacToeGame::play() {
				if (m_board->isEmpty()) {
						m_currentTurnSymbol = 'X';
				}

				while (!finished()) {
						Strategy *strategy = m_currentTurnSymbol == 'X' ? m_xStrategy : m_oStrategy;
						const Move MOVE = strategy->chooseMove(*m_board, m_currentTurnSymbol);

						makeMove(MOVE, m_currentTurnSymbol);
				}
		}

		bool TicTacToeGame::finished() const {
				return winner() != '\0';
		}

		char TicTacToeGame::winner() const {
				if (Utils::hasWon(*m_board, 'X')) {
						return 'X';
				}

				if (Utils::hasWon(*m_board, 'O')) {
						return 'O';
				}

				if (m_board->full()) {
						return 'D';
				}

				return '\0';
		}

		void TicTacToeGame::changeStrategy(char symbol, Strategy *strategy) {
				if (symbol != 'X' && symbol != 'O') {
						throw MyExceptions::InvalidArgumentException("Symbol must be X or O");
				}

				if (strategy == nullptr) {
						throw MyExceptions::InvalidArgumentException("Strategy cannot be nullptr");
				}

				if (symbol == 'X') {
						m_xStrategy = strategy;
				} else {
						m_oStrategy = strategy;
				}
		}

} // namespace TicTacToe