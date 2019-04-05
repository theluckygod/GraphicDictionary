#pragma once
#include <vector>
#include <string>
using namespace std;

class Tokenizer
{
public:
	static vector<string> Parse(string line, string sprt)
	{
		vector<string> tokens;
		int startPos = 0, count, lensprt = sprt.length();
		size_t foundPos, tempPos;
		
		foundPos = line.find(sprt, startPos);

		while (foundPos != string::npos)
		{
			count = foundPos - startPos;
			if (count > 0)	tokens.push_back(line.substr(startPos, count));
			startPos = foundPos + lensprt;

			foundPos = line.find(sprt, startPos);
		}

		count = line.length() - startPos;
		tokens.push_back(line.substr(startPos, count));

		return tokens;
	}
};