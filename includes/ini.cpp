#include "ini.h"
#include <iostream>

using namespace std;

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


Document Load(istream& input) {
	Document doc;
	string str;
	while (getline(input, str)) {
		if (str[0] == '[') {
			Section& section = doc.AddSection(string(++begin(str), --end(str)));
			while (getline(input, str)) {
				if (str.size() == 0 || str[0] == ' ') break;
				auto pos = str.find('=');
				//string key(str.substr(0, pos));
				section[str.substr(0, pos - 1)] = str.substr(++pos);
			}
		} else {
			throw invalid_argument("Not INI format");
		}
	}
	return doc;
}

} // end namespace Ini
