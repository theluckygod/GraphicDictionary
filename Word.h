#pragma once
#include <string>
#include <vector>
#include <sstream>
#define strnull (string)""
#define strsprt (string)"  "
#define notword (string)"Usage"
#define spcword (string)"Usage  n."
using namespace std;

class Word
{
private:
	string m_keyword, m_meaning, m_usage;
public:
	Word(const string&, const string&, const string&);
	~Word();

	int convertToInt() const;
	bool operator>(const Word&) const;
	bool operator<(const Word&) const;
	bool operator==(const Word&) const;

	friend ostream& operator<<(ostream&, const Word&);

	string ToString() const;

	static int isWord(const string& src);
	static Word* Parse(string src, string src2);
};

