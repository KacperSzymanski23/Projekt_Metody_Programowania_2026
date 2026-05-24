#ifndef MY_EXCEPTIONS_H
#define MY_EXCEPTIONS_H

// STD
#include <stdexcept>
#include <string>

namespace MyExceptions {
		class InvalidArgumentException : public std::invalid_argument {
			  public:
				explicit InvalidArgumentException(const std::string &message)
					: std::invalid_argument(message) {
				}
		};

		class InvalidMoveException : public std::logic_error {
			  public:
				explicit InvalidMoveException(const std::string &message)
					: std::logic_error(message) {
				}
		};

		class InvalidSymbolException : public std::invalid_argument {
			  public:
				explicit InvalidSymbolException(const std::string &message)
					: std::invalid_argument(message) {
				}
		};

		class GameAlreadyOverException : public std::logic_error {
			  public:
				explicit GameAlreadyOverException(const std::string &message)
					: std::logic_error(message) {
				}
		};
} // namespace MyExceptions

#endif /* MY_EXCEPTIONS_H */