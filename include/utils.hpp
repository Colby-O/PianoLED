#ifndef UTILS_HPP_
#define UTILS_HPP_

#include <string_view>

namespace Utils {
	constexpr bool isDigit(char c) {
		return c >= '0' && c <= '9';
	}
};

#endif
