#include "ini.h"
#include <iostream>

namespace Ini {

Section& Document::AddSection(string name) {
	return sections[name];
}

const Section& Document::GetSection(const string& name) const {
	auto it = sections.find(name);
	if (it == end(sections)) {
		throw out_of_range("Section not found");
	}
	return it->second;
}

size_t Document::SectionCount() const {
	return sections.size();
}

pair<string_view, string_view> parseString(const string_view& str) {
	string_view key, value;

	const auto keyBeginPos = str.find_first_not_of(' ');
	const auto equalPos = str.find('=');
	key = str.substr(keyBeginPos, equalPos - keyBeginPos);
	value = str.substr(equalPos + 1);

	return {key, value};
}

Document Load(istream& input) {
	Document doc;

	Section* section = nullptr;
	for (string line; getline(input, line);) {
		string_view str(line);
		if (str.find('[') != str.npos) {
			auto openBracketPos = str.find_first_of('[');
			++openBracketPos;
			auto closeBracketPos = str.find_first_of(']');
			auto sectionName =
					str.substr(openBracketPos, closeBracketPos - openBracketPos);
			section = &doc.AddSection(string(sectionName));
		} else if (str.find('=') != str.npos) {
			const auto [key, value] = parseString(str);
					section->insert({string(key), string(value)});
		}
	}
	return doc;
}

} // end namespace Ini
