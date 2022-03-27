#pragma once

#include <istream>
#include <vector>
#include <string>
#include <unordered_map>
#include <map>

namespace Ini {

using Section = std::unordered_map<string, string>;

class Document {
public:
	Section& AddSection(std::string name);
	const Section& GetSection(const std::string& name) const;
	size_t SectionCount() const;

private:
	std::unordered_map<std::string, Section> sections;
};

Document Load(std::istream& input);

} // end namespace Ini
