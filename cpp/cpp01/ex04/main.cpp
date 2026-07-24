#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

static bool replaceAll(std::string& text, const std::string& s1, const std::string& s2)
{
	if (s1.empty())
		return false;

	size_t pos = 0;
	while ((pos = text.find(s1, pos)) != std::string::npos)
	{
		text = text.substr(0, pos) + s2 + text.substr(pos + s1.length());
		pos += s2.length();
	}
	return true;
}

static bool readFile(const std::string& fileName, std::string& content)
{
	std::ifstream input(fileName.c_str());
	if (!input.is_open())
		return false;

	std::ostringstream buffer;
	buffer << input.rdbuf();
	content = buffer.str();
	return true;
}

static bool writeFile(const std::string& fileName, const std::string& content)
{
	std::ofstream output(fileName.c_str());
	if (!output.is_open())
		return false;

	output << content;
	return true;
}

int main(int argc, char** argv)
{
	if (argc != 4)
	{
		std::cerr << "Error: expected 3 arguments" << std::endl;
		return 1;
	}

	const std::string fileName = argv[1];
	const std::string s1 = argv[2];
	const std::string s2 = argv[3];
	std::string content;

	if (!readFile(fileName, content))
	{
		std::cerr << "Error: cannot open input file" << std::endl;
		return 1;
	}
	if (!replaceAll(content, s1, s2))
	{
		std::cerr << "Error: s1 cannot be empty" << std::endl;
		return 1;
	}
	if (!writeFile(fileName + ".replace", content))
	{
		std::cerr << "Error: cannot create output file" << std::endl;
		return 1;
	}
	return 0;
}
