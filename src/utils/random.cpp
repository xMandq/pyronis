#include <utils/random.hpp>

std::string random::random_str(std::string::size_type length) noexcept {
	constexpr std::string_view chars =
		"0123456789"
		"abcdefghijklmnopqrstuvwxyz"
		"ABCDEFGHIJKLMNOPQRSTUVWXYZ";

	std::string ret;
	ret.reserve(length);

	while (length--)
		ret.push_back(chars[random_num(chars.size() - 1)]);

	return ret;
}
