#pragma once
#include <string>
#include <sstream>
#include <vector>

std::vector<std::string> split_string(const std::string& str, char delim) noexcept {
	std::vector<std::string> ret;
	std::istringstream ss(str);
	std::string item;

	while (std::getline(ss, item, delim))
		ret.push_back(item);

	return ret;
}

class text_scanner_t {
public:
	text_scanner_t() noexcept = default;
	explicit text_scanner_t(const std::string& text) noexcept { load(text); }

	void load(const std::string& text) noexcept {
		std::istringstream ss(text);
		std::string line;

		while (std::getline(ss, line))
			lines.push_back(line);
	}

	std::string build() const noexcept {
		std::ostringstream ss;

		for (const std::string& line : lines)
			ss << line << '\n';

		return ss.str();
	}

	void add(const std::string& key, const std::string& value) noexcept {
		std::string new_line = key + "|" + value;
		lines.push_back(new_line);
	}

	void set(const std::string& key, const std::string& value, std::size_t index = 0) noexcept {
		for (std::string& line : lines) {
			auto data = split_string(line, '|');

			if (data.size() < (index + 2))
				continue;

			if (data[0] == key) {
				data[1 + index] = value;

				line = data[0];
				for (std::size_t i = 1; i < data.size(); ++i)
					line += '|' + data[i];

				return;
			}
		}
	}

	// todo: make work with others than strings
	//template <typename value_type>
	//void set(const std::string& key, value_type value, std::size_t index = 0) noexcept {
	//	for (std::string& line : lines) {
	//		auto data = split_string(line, '|');

	//		if (data.size() < 2)
	//			continue;

	//		if (data[0] == key) {
	// 
	//			return;
	//		}
	//	}
	//}

	std::string get(const std::string& key, std::size_t index = 0) const noexcept {
		for (const std::string& line : lines) {
			auto data = split_string(line, '|');

			if (data.size() < (index + 2))
				continue;

			if (data[0] == key)
				return data[1 + index];
		}
		return {};
	}

	bool has(const std::string& key) const noexcept {
		for (const std::string& line : lines) {
			auto data = split_string(line, '|');

			if (data.empty())
				continue;

			if (data[0] == key)
				return true;
		}
		return false;
	}

	void remove(const std::string& key, std::size_t index = 0) noexcept {
		auto it = std::find_if(lines.begin(), lines.end(), 
			[&](const std::string& line) {
				auto data = split_string(line, '|');
				if (!data.empty() && data[0] == key)
					return true;
			});

		if (it != lines.end())
			lines.erase(it);
	}

private:

	std::vector<std::string> lines;
};
