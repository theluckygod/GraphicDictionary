#include "Word.h"
#include "Tokenizer.h"

Word::Word(const string& kw, const string& mn, const string& usg)
{
	m_keyword = kw;
	m_meaning = mn;
	m_usage = usg;
}
Word::~Word()
{
	m_keyword.clear();
	m_meaning.clear();
	m_usage.clear();
}

bool Word::operator>(const Word& orther) const
{
	char demBoStr1 = 0, demBoStr2 = 0;
	if (m_keyword[0] == '-' || m_keyword[0] == '\'')
	{
		demBoStr1++;
		if (m_keyword[1] == '\'') demBoStr1++;
	}
	if (orther.m_keyword[0] == '-' || orther.m_keyword[0] == '\'')
	{
		demBoStr2++;
		if (orther.m_keyword[1] == '\'') demBoStr2++;
	}
	string str1 = m_keyword.substr(demBoStr1, m_keyword.length() - demBoStr1);
	string str2 = orther.m_keyword.substr(demBoStr2, orther.m_keyword.length() - demBoStr2);
	if (str1[0] >= 'A' && str1[0] <= 'Z') str1[0] -= 'A' - 'a';
	if (str2[0] >= 'A' && str2[0] <= 'Z') str2[0] -= 'A' - 'a';
	
	return str1 > str2;
}
bool Word::operator<(const Word& orther) const
{
	char demBoStr1 = 0, demBoStr2 = 0;
	if (m_keyword[0] == '-' || m_keyword[0] == '\'')
	{
		demBoStr1++;
		if (m_keyword[1] == '\'') demBoStr1++;
	}
	if (orther.m_keyword[0] == '-' || orther.m_keyword[0] == '\'')
	{
		demBoStr2++;
		if (orther.m_keyword[1] == '\'') demBoStr2++;
	}
	string str1 = m_keyword.substr(demBoStr1, m_keyword.length() - demBoStr1);
	string str2 = orther.m_keyword.substr(demBoStr2, orther.m_keyword.length() - demBoStr2);
	if (str1[0] >= 'A' && str1[0] <= 'Z') str1[0] -= 'A' - 'a';
	if (str2[0] >= 'A' && str2[0] <= 'Z') str2[0] -= 'A' - 'a';
	
	return str1 < str2;
}
bool Word::operator==(const Word& orther) const
{
	return m_keyword == orther.m_keyword;
}

int Word::convertToInt() const
{
	int res = 0, exp = 931;
	char ch;
	for (int i = 0, length = m_keyword.length(); i < length; i++)
	{
		ch = tolower(m_keyword[i]);
		if (ch >= 'a' && ch <= 'z')
		{
			res += (ch - 'a' + 1) * exp;
			exp /= 30;
			if (exp == 0) break;
		}
	}
	return res;
}

ostream& operator<<(ostream& out, const Word& w)
{
	out << w.m_keyword << "  " << w.m_meaning << endl;
	if (w.m_usage != strnull) out << w.m_usage << endl;
	return out;
}

string Word::ToString() const
{
	stringstream writer;
	writer << m_keyword << "  " << m_meaning << endl;
	if (m_usage != strnull) writer << m_usage << endl;
	return writer.str();
}


int Word::isWord(const string& src)
{
	if (src.find(strsprt) == string::npos || src.find(strsprt) == 0) return -1;
	if (src.find(notword) == 0 && src.find(spcword) == string::npos) return 0;
	return 1;
}

Word* Word::Parse(string src, string src2)
{
	try
	{
		string sprt = "  ";

		vector<string> tokens = Tokenizer::Parse(src, sprt);
		
		Word* w = new Word(tokens[0], tokens[1], src2);
		return w;
	}
	catch (...)
	{
		return nullptr;
	}
}