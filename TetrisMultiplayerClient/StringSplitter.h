#pragma once
#include <string>
#include <vector>
#include <sstream>

static class StringSplitter
{
public:
	static std::vector<std::string> &split(const std::string &s, char delim, std::vector<std::string> &elems);
	static std::vector<std::string> split(const std::string &s, char delim);
};

