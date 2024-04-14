#pragma once
#include <string>
#include <random>
#include <limits>

namespace random {
	template <typename T = std::size_t>
	inline T random_num(T min, T max) noexcept {
		thread_local std::default_random_engine generator(std::random_device{}());
		std::uniform_int_distribution<T> distribution(min, max);
		return distribution(generator);
	}

	template <typename T = std::size_t>
	inline T random_num(T max) noexcept {
		return random_num<T>(std::numeric_limits<T>::lowest(), max);
	}

	std::string random_str(std::string::size_type length) noexcept;
}