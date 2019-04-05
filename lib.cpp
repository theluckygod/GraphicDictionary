#include "lib.h"

// Hàm cài đặt console
void resizeConsole(int width, int height) // Thay đổi kích thước console
{
	HWND console = GetConsoleWindow();
	RECT r;
	GetWindowRect(console, &r);
	MoveWindow(console, r.left, r.top, width, height, TRUE);
}
void FixConsoleWindow() // Ngăn phóng to, thu nhỏ màn hình
{
	HWND consoleWindow = GetConsoleWindow();
	LONG style = GetWindowLong(consoleWindow, GWL_STYLE);
	style = style & ~(WS_MAXIMIZEBOX) & ~(WS_THICKFRAME);
	SetWindowLong(consoleWindow, GWL_STYLE, style);
}
void textcolor(int color) // Hàm tô màu
{
	HANDLE mau;
	mau = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(mau, color);
}
void GotoXY(int x, int y)  // Di chuyển con trỏ console
{
	COORD coord;
	coord.X = x;
	coord.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}
void Nocursortype() // Ẩn con trỏ
{
	CONSOLE_CURSOR_INFO Info;
	Info.bVisible = FALSE;
	Info.dwSize = 20;
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &Info);
}

// Hàm tô màu
void ToMauToanBo(int x, int y, char* str, int color) // Vẽ chuỗi str với màu color lên vị trí (x, y) cho toàn bộ vị trí
{
	if (x >= 0 && x < WIDTHFULLPIXELNUMBER && y >= 0 && y < HEIGHTFULLPIXELNUMBER)
	{
		GotoXY(x, y);
		textcolor(color);
		std::cout << str;
		GotoXY(0, 0);
	}
}
void ToMauToanBo(int x, int y, char ch, int color) // Vẽ chuỗi str với màu color lên vị trí (x, y) cho toàn bộ vị trí
{
	if (x >= 0 && x < WIDTHFULLPIXELNUMBER && y >= 0 && y < HEIGHTFULLPIXELNUMBER)
	{
		GotoXY(x, y);
		textcolor(color);
		std::cout << ch;
		GotoXY(0, 0);
	}
}
void ToMauKhungKetQuaSearch(int x, int y, string ch, int color)
{
	const int MAXLENGTH = 670;
	if (ch.length() > MAXLENGTH)// ngắt bớt đáp án quá dài
	{
		ch = ch.substr(0, MAXLENGTH);
		ch[ch.length() - 3] = ch[ch.length() - 2] = ch[ch.length() - 1] = '.';
	}

	GotoXY(x, y); // In đáp án
	textcolor(color);
	int XDA = x, YDA = y, iDA = 0;
	while (1)
	{
		XDA++;
		if (ch[iDA] == 0) break;// In hết đáp án
		if (ch[iDA] == '\n')
		{
			XDA = x; YDA++;
			GotoXY(XDA, YDA);
			iDA++;
		}
		else std::cout << ch[iDA++];
		if (XDA >= 74) // GIOIHANX = 74
		{
			XDA = x;
			GotoXY(XDA, ++YDA);
		}
	}
}

// Hàm điều khiển chương trinh
void BatPhimKetThuc()
{
	// Bắt phím để kết thúc
	if (_kbhit())
	{
		_getch();
		while (_kbhit())
		{
			_getch();
		}
	}
	while (1)
	{
		if (_kbhit()) break;
	}
}
void ChuyenCanh(int CHUYENCANHCOLOR)
{
	int xchan = 0, ychan = 0, i = 0, j = -1 + ychan;
	int NHIPCHUYEN = 0;
	while (1)
	{
		for (i = xchan, j++; i < WIDTHFULLPIXELNUMBER - xchan; i += 2)
		{
			ToMauToanBo(i, j, (char *)"  ", CHUYENCANHCOLOR);
			Sleep(NHIPCHUYEN);
		}
		for (i -= 2, j++; j < HEIGHTFULLPIXELNUMBER - ychan; j++)
		{
			ToMauToanBo(i, j, (char *)"  ", CHUYENCANHCOLOR);
			Sleep(NHIPCHUYEN);
		}
		for (j--; i >= xchan; i -= 2)
		{
			ToMauToanBo(i, j, (char *)"  ", CHUYENCANHCOLOR);
			Sleep(NHIPCHUYEN);
		}
		ychan++;
		for (i += 2, j--; j >= ychan; j--)
		{
			ToMauToanBo(i, j, (char *)"  ", CHUYENCANHCOLOR);
			Sleep(NHIPCHUYEN);
		}
		xchan += 2;
		if (xchan >= WIDTHFULLPIXELNUMBER / 2) break;
	}
}
int HienThiMenu()
{
	int starty = 10, startx = 26, luachon , luachondaluu;
	bool hasluachon = false;
	ToMauToanBo(startx, starty + 0, (char *)"                               ", NOIDUNGKHUNGCOLOR);
	ToMauToanBo(startx, starty + 1, (char *)"  1. Tra cuu nghia             ", NOIDUNGKHUNGCOLOR);
	ToMauToanBo(startx, starty + 2, (char *)"  2. Them mot tu vao tu dien   ", NOIDUNGKHUNGCOLOR);
	ToMauToanBo(startx, starty + 3, (char *)"  3. Sua nghia tu              ", NOIDUNGKHUNGCOLOR);
	ToMauToanBo(startx, starty + 4, (char *)"  4. Xoa tu                    ", NOIDUNGKHUNGCOLOR);
	ToMauToanBo(startx, starty + 5, (char *)"  5. Luu tu dien               ", NOIDUNGKHUNGCOLOR);
	ToMauToanBo(startx, starty + 6, (char *)"  6. Xuat tu dien ra file moi  ", NOIDUNGKHUNGCOLOR);
	ToMauToanBo(startx, starty + 7, (char *)"  0. Thoat                     ", NOIDUNGKHUNGCOLOR);
	ToMauToanBo(startx, starty + 8, (char *)"  Nhap lua chon(0-6):          ", NOIDUNGKHUNGCOLOR);
	ToMauToanBo(startx, starty + 9, (char *)"                               ", NOIDUNGKHUNGCOLOR);

	// Vẽ DICT
	// D
	ToMauToanBo(startx - 2, starty - 8, (char *)"      ", DICTKHUNGCOLOR);
	for(int i = 1; i < 5; i++) ToMauToanBo(startx - 2, starty - 8 + i, (char *)"  ", DICTKHUNGCOLOR);
	ToMauToanBo(startx - 2, starty - 8 + 5, (char *)"      ", DICTKHUNGCOLOR);
	ToMauToanBo(startx - 2 + 5, starty - 8 + 1, (char *)" ", DICTKHUNGCOLOR);
	ToMauToanBo(startx - 2 + 5, starty - 8 + 4, (char *)" ", DICTKHUNGCOLOR);
	for (int i = 1; i < 5; i++) ToMauToanBo(startx - 2 + 6, starty - 8 + i, (char *)"  ", DICTKHUNGCOLOR);
	// I
	ToMauToanBo(startx - 2 + 10, starty - 8, (char *)"      ", DICTKHUNGCOLOR);
	for (int i = 1; i < 5; i++) ToMauToanBo(startx - 2 + 12, starty - 8 + i, (char *)"  ", DICTKHUNGCOLOR);
	ToMauToanBo(startx - 2 + 10, starty - 8 + 5, (char *)"      ", DICTKHUNGCOLOR);
	// C
	ToMauToanBo(startx - 2 + 20, starty - 8, (char *)"      ", DICTKHUNGCOLOR);
	for (int i = 2; i < 4; i++) ToMauToanBo(startx - 2 + 18, starty - 8 + i, (char *)"  ", DICTKHUNGCOLOR);
	ToMauToanBo(startx - 2 + 20, starty - 8 + 5, (char *)"      ", DICTKHUNGCOLOR);
	ToMauToanBo(startx - 2 + 19, starty - 8 + 1, (char *)"  ", DICTKHUNGCOLOR);
	ToMauToanBo(startx - 2 + 19, starty - 8 + 4, (char *)"  ", DICTKHUNGCOLOR);
	 // T
	ToMauToanBo(startx - 2 + 28, starty - 8, (char *)"        ", DICTKHUNGCOLOR);
	ToMauToanBo(startx - 2 + 28, starty - 8 + 1, (char *)" ", DICTKHUNGCOLOR);
	ToMauToanBo(startx - 2 + 35, starty - 8 + 1, (char *)" ", DICTKHUNGCOLOR);
	for (int i = 1; i < 6; i++) ToMauToanBo(startx - 2 + 31, starty - 8 + i, (char *)"  ", DICTKHUNGCOLOR);


	while (1)
	{
		if (_kbhit())
		{
			luachon = ' '; // Xoá lựa chọn cũ
			luachon = _getch();
			if (luachon >= '0' && luachon <= '6')
			{
				hasluachon = true;
				luachondaluu = luachon;

				ToMauToanBo(startx, starty + 0, (char *)"                               ", NOIDUNGKHUNGCOLOR);
				ToMauToanBo(startx, starty + 1, (char *)"  1. Tra cuu nghia             ", NOIDUNGKHUNGCOLOR);
				ToMauToanBo(startx, starty + 2, (char *)"  2. Them mot tu vao tu dien   ", NOIDUNGKHUNGCOLOR);
				ToMauToanBo(startx, starty + 3, (char *)"  3. Sua nghia tu              ", NOIDUNGKHUNGCOLOR);
				ToMauToanBo(startx, starty + 4, (char *)"  4. Xoa tu                    ", NOIDUNGKHUNGCOLOR);
				ToMauToanBo(startx, starty + 5, (char *)"  5. Luu tu dien               ", NOIDUNGKHUNGCOLOR);
				ToMauToanBo(startx, starty + 6, (char *)"  6. Xuat tu dien ra file moi  ", NOIDUNGKHUNGCOLOR);
				ToMauToanBo(startx, starty + 7, (char *)"  0. Thoat                     ", NOIDUNGKHUNGCOLOR);
				ToMauToanBo(startx, starty + 8, (char *)"  Nhap lua chon(0-6):          ", NOIDUNGKHUNGCOLOR);
				ToMauToanBo(startx, starty + 9, (char *)"                               ", NOIDUNGKHUNGCOLOR);
				switch (luachon)
				{
				case '1':
					ToMauToanBo(startx, starty + 1, (char *)"  1. Tra cuu nghia             ", HIGHLIGHTNOIDUNGKHUNGCOLOR);
					break;
				case '2':
					ToMauToanBo(startx, starty + 2, (char *)"  2. Them mot tu vao tu dien   ", HIGHLIGHTNOIDUNGKHUNGCOLOR);
					break;
				case '3':
					ToMauToanBo(startx, starty + 3, (char *)"  3. Sua nghia tu              ", HIGHLIGHTNOIDUNGKHUNGCOLOR);
					break;
				case '4':
					ToMauToanBo(startx, starty + 4, (char *)"  4. Xoa tu                    ", HIGHLIGHTNOIDUNGKHUNGCOLOR);
					break;
				case '5':
					ToMauToanBo(startx, starty + 5, (char *)"  5. Luu tu dien               ", HIGHLIGHTNOIDUNGKHUNGCOLOR);
					break;
				case '6':
					ToMauToanBo(startx, starty + 6, (char *)"  6. Xuat tu dien ra file moi  ", HIGHLIGHTNOIDUNGKHUNGCOLOR);
					break;
				case '0':
					ToMauToanBo(startx, starty + 7, (char *)"  0. Thoat                     ", HIGHLIGHTNOIDUNGKHUNGCOLOR);
					break;
				}

				ToMauToanBo(startx + 22, starty + 8, (char)luachon, NOIDUNGKHUNGCOLOR); // In số lựa chọn đã chọn
			}
			if (luachon == 13 && hasluachon == true) // Phím enter
				break;
			if (luachon == 8) // Phím Backspace
			{
				ToMauToanBo(startx, starty + 0, (char *)"                               ", NOIDUNGKHUNGCOLOR);
				ToMauToanBo(startx, starty + 1, (char *)"  1. Tra cuu nghia             ", NOIDUNGKHUNGCOLOR);
				ToMauToanBo(startx, starty + 2, (char *)"  2. Them mot tu vao tu dien   ", NOIDUNGKHUNGCOLOR);
				ToMauToanBo(startx, starty + 3, (char *)"  3. Sua nghia tu              ", NOIDUNGKHUNGCOLOR);
				ToMauToanBo(startx, starty + 4, (char *)"  4. Xoa tu                    ", NOIDUNGKHUNGCOLOR);
				ToMauToanBo(startx, starty + 5, (char *)"  5. Luu tu dien               ", NOIDUNGKHUNGCOLOR);
				ToMauToanBo(startx, starty + 6, (char *)"  6. Xuat tu dien ra file moi  ", NOIDUNGKHUNGCOLOR);
				ToMauToanBo(startx, starty + 7, (char *)"  0. Thoat                     ", NOIDUNGKHUNGCOLOR);
				ToMauToanBo(startx, starty + 8, (char *)"  Nhap lua chon(0-6):          ", NOIDUNGKHUNGCOLOR);
				ToMauToanBo(startx, starty + 9, (char *)"                               ", NOIDUNGKHUNGCOLOR);

				ToMauToanBo(startx + 22, starty + 8, ' ', NOIDUNGKHUNGCOLOR);
				hasluachon = false;
			}
		}
	}
	return luachondaluu - '0';
}
int HienThiSearch(const HashTable<RBTree<Word>, Word>& dictionary)
{
	string keyword;
	Word* search, *temp;
	const int startx = 5, starty = 2;
	ToMauToanBo(startx, starty, (char*) "Nhap tu khoa:", SEARCHNENCOLOR);
	ToMauToanBo(startx, starty + 1, STRINGSEARCHKHUNG, SEARCHKHUNGCOLOR);
	ToMauToanBo(startx, starty + 2, STRINGSEARCHKHUNG, SEARCHKHUNGCOLOR); // Chữ ở đây
	ToMauToanBo(startx, starty + 3, STRINGSEARCHKHUNG, SEARCHKHUNGCOLOR);

	// Nhập
	keyword = NhapKhungKeywordSearch();

	if (keyword == (string)"EXIT")
	{
		return STATEEXIT;
	}
	else
	{
		// Search
		GotoXY(startx + 2, starty + 7);
		textcolor(SEARCHKHUNGCOLOR);

		for (int i = 0, len = keyword.length(); i < len; i++)
			if (keyword[i] >= 'A' && keyword[i] <= 'Z') keyword[i] = keyword[i] - ('A' - 'a');
		if (keyword[0] >= 'a' && keyword[0] <= 'z') keyword[0] = keyword[0] + ('A' - 'a');
		temp = new Word(keyword, strnull, strnull);

		search = dictionary.search(temp);

		delete temp;
		if (search == NULL) ToMauKhungKetQuaSearch(startx + 2, starty + 7, (string)"Khong co tu " + keyword + (string)"!", SEARCHTHONGBAOCOLOR);
		else
		{
			ToMauToanBo(startx, starty + 5, (char*) "Nghia va cach dung:", SEARCHNENCOLOR);
			for (int i = 1; i < 13; i++)
				ToMauToanBo(startx, starty + 5 + i, STRINGSEARCHKHUNG, SEARCHKHUNGCOLOR);

			ToMauKhungKetQuaSearch(startx + 2, starty + 7, search->ToString(), SEARCHKHUNGCOLOR);
		}

		// Ban muon tiep tuc
		return STATEPREVIOUS;
	}
}
int HienThiRemove(HashTable<RBTree<Word>, Word>& dictionary)
{
	string keyword;
	Word* search, *temp;
	const int startx = 5, starty = 2;
	ToMauToanBo(startx, starty, (char*) "Nhap tu khoa:", REMOVENENCOLOR);
	ToMauToanBo(startx, starty + 1, STRINGSEARCHKHUNG, REMOVEKHUNGCOLOR);
	ToMauToanBo(startx, starty + 2, STRINGSEARCHKHUNG, REMOVEKHUNGCOLOR); // Chữ ở đây
	ToMauToanBo(startx, starty + 3, STRINGSEARCHKHUNG, REMOVEKHUNGCOLOR);

	// Nhập
	keyword = NhapKhungKeywordRemove();

	if (keyword == (string)"EXIT")
	{
		return STATEEXIT;
	}
	else
	{
		if (keyword[0] >= 'a' && keyword[0] <= 'z') keyword[0] += 'A' - 'a';

		temp = new Word(keyword, strnull, strnull);
		search = dictionary.search(temp);
		if (search != NULL)
		{
			dictionary.remove(search);

			ToMauKhungKetQuaSearch(startx + 2, starty + 5, (string) "Xoa thanh cong!", REMOVETHONGBAOCOLOR);
		}
		else
		{
			ToMauKhungKetQuaSearch(startx + 2, starty + 5, (string) "Tu " + keyword + (string)" chua co!", REMOVETHONGBAOCOLOR);
			
		}
		delete temp;

		// Ban muon tiep tuc
		return STATEPREVIOUS;
	}
}
int HienThiAdd(HashTable<RBTree<Word>, Word>& dictionary)
{
	string keyword, meaning, usage;
	Word* search, *temp;
	const int startx = 5, starty = 2;
	ToMauToanBo(startx, starty, (char*) "Nhap tu khoa:", ADDNENCOLOR);
	ToMauToanBo(startx, starty + 1, STRINGSEARCHKHUNG, ADDKHUNGCOLOR);
	ToMauToanBo(startx, starty + 2, STRINGSEARCHKHUNG, ADDKHUNGCOLOR); // Chữ ở đây
	ToMauToanBo(startx, starty + 3, STRINGSEARCHKHUNG, ADDKHUNGCOLOR);

	// Nhập keyword
	keyword = NhapKhungKeywordAdd();

	if (keyword == (string)"EXIT")
	{
		return STATEEXIT;
	}

	// Nhập meaning
	ToMauToanBo(startx, starty + 5, (char*) "Nhap nghia cua tu:", ADDNENCOLOR);
	ToMauToanBo(startx, starty + 6, STRINGSEARCHKHUNG, ADDKHUNGCOLOR);
	ToMauToanBo(startx, starty + 7, STRINGSEARCHKHUNG, ADDKHUNGCOLOR); // Chữ ở đây
	ToMauToanBo(startx, starty + 8, STRINGSEARCHKHUNG, ADDKHUNGCOLOR);
	ToMauToanBo(startx, starty + 9, STRINGSEARCHKHUNG, ADDKHUNGCOLOR);
	ToMauToanBo(startx, starty + 10, STRINGSEARCHKHUNG, ADDKHUNGCOLOR);

	meaning = NhapKhungMeaningAdd();
	if (meaning == (string)"EXIT")
	{
		return STATEEXIT;
	}

	// Nhập usage
	ToMauToanBo(startx, starty + 12, (char*) "Nhap cach su dung:", ADDNENCOLOR);
	ToMauToanBo(startx, starty + 13, STRINGSEARCHKHUNG, ADDKHUNGCOLOR);
	ToMauToanBo(startx, starty + 14, STRINGSEARCHKHUNG, ADDKHUNGCOLOR); // Chữ ở đây
	ToMauToanBo(startx, starty + 15, STRINGSEARCHKHUNG, ADDKHUNGCOLOR);
	ToMauToanBo(startx, starty + 16, STRINGSEARCHKHUNG, ADDKHUNGCOLOR);

	usage = NhapKhungUsageAdd();
	if(usage == (string)"EXIT")	return STATEEXIT;
	else
	{
		// Add
		GotoXY(startx + 2, starty + 18);
		textcolor(ADDKHUNGCOLOR);

		if (keyword[0] >= 'a' && keyword[0] <= 'z') keyword[0] = keyword[0] + ('A' - 'a');
		temp = new Word(keyword, meaning, usage);

		search = dictionary.search(temp);

		if (search != NULL)
		{
			delete temp;
			ToMauToanBo(startx + 2, starty + 18, (char*) "Tu da co, them khong thanh cong!", ADDTHONGBAOCOLOR);
		}
		else
		{
			dictionary.add(temp);
			ToMauToanBo(startx + 2, starty + 18, (char*) "Them thanh cong!", ADDTHONGBAOCOLOR);
		}

		// Ban muon tiep tuc
		return STATEPREVIOUS;
	}
}
int HienThiFix(HashTable<RBTree<Word>, Word>& dictionary)
{
	string keyword, meaning, usage;
	Word* search, *temp;
	const int startx = 5, starty = 2;
	ToMauToanBo(startx, starty, (char*) "Nhap tu khoa:", FIXNENCOLOR);
	ToMauToanBo(startx, starty + 1, STRINGSEARCHKHUNG, FIXKHUNGCOLOR);
	ToMauToanBo(startx, starty + 2, STRINGSEARCHKHUNG, FIXKHUNGCOLOR); // Chữ ở đây
	ToMauToanBo(startx, starty + 3, STRINGSEARCHKHUNG, FIXKHUNGCOLOR);

	// Nhập keyword
	keyword = NhapKhungKeywordFix();

	if (keyword == (string)"EXIT")
	{
		return STATEEXIT;
	}

	// Nhập meaning
	ToMauToanBo(startx, starty + 5, (char*) "Nhap nghia cua tu:", FIXNENCOLOR);
	ToMauToanBo(startx, starty + 6, STRINGSEARCHKHUNG, FIXKHUNGCOLOR);
	ToMauToanBo(startx, starty + 7, STRINGSEARCHKHUNG, FIXKHUNGCOLOR); // Chữ ở đây
	ToMauToanBo(startx, starty + 8, STRINGSEARCHKHUNG, FIXKHUNGCOLOR);
	ToMauToanBo(startx, starty + 9, STRINGSEARCHKHUNG, FIXKHUNGCOLOR);
	ToMauToanBo(startx, starty + 10, STRINGSEARCHKHUNG, FIXKHUNGCOLOR);

	meaning = NhapKhungMeaningFix();
	if (meaning == (string)"EXIT")
	{
		return STATEEXIT;
	}

	// Nhập usage
	ToMauToanBo(startx, starty + 12, (char*) "Nhap cach su dung:", FIXNENCOLOR);
	ToMauToanBo(startx, starty + 13, STRINGSEARCHKHUNG, FIXKHUNGCOLOR);
	ToMauToanBo(startx, starty + 14, STRINGSEARCHKHUNG, FIXKHUNGCOLOR); // Chữ ở đây
	ToMauToanBo(startx, starty + 15, STRINGSEARCHKHUNG, FIXKHUNGCOLOR);
	ToMauToanBo(startx, starty + 16, STRINGSEARCHKHUNG, FIXKHUNGCOLOR);

	usage = NhapKhungUsageFix();
	if (usage == (string)"EXIT")	return STATEEXIT;
	else
	{
		// Fix
		GotoXY(startx + 2, starty + 18);
		textcolor(FIXKHUNGCOLOR);

		if (keyword[0] >= 'a' && keyword[0] <= 'z') keyword[0] = keyword[0] + ('A' - 'a');
		temp = new Word(keyword, meaning, usage);

		search = dictionary.search(temp);

		if (search != NULL)
		{
			dictionary.remove(temp);
			dictionary.add(temp);
			ToMauToanBo(startx + 2, starty + 18, (char*) "Cap nhat thanh cong!", FIXTHONGBAOCOLOR);

		}
		else
		{
			dictionary.add(temp);
			ToMauToanBo(startx + 2, starty + 18, (char*) "Tu chua co, da duoc them!", FIXTHONGBAOCOLOR);
		}

		// Ban muon tiep tuc
		return STATEPREVIOUS;
	}
}
int HienThiSave(const HashTable<RBTree<Word>, Word> & dictionary)
{
	ofstream out(DICTIONARYFILENAME);
	dictionary.inorderTravesal(out);
	out.close();
	const int startx = (WIDTHFULLPIXELNUMBER - strlen((char*) "Luu thanh cong!"))/2, starty = 2;
	ToMauToanBo(startx + 2, starty + 2, (char*) "Luu thanh cong!", SAVETHONGBAOCOLOR);

	// Ban muon tiep tuc
	return STATEPREVIOUS;
}
int HienThiExport(const HashTable<RBTree<Word>, Word> & dictionary)
{
	string filename;
	const int startx = 5, starty = 2;
	ToMauToanBo(startx, starty, (char*) "Nhap duong dan:", EXPORTNENCOLOR);
	ToMauToanBo(startx, starty + 1, STRINGSEARCHKHUNG, EXPORTKHUNGCOLOR);
	ToMauToanBo(startx, starty + 2, STRINGSEARCHKHUNG, EXPORTKHUNGCOLOR); // Chữ ở đây
	ToMauToanBo(startx, starty + 3, STRINGSEARCHKHUNG, EXPORTKHUNGCOLOR);

	// Nhập
	filename = NhapKhungDuongDanExport();

	if (filename == (string)"EXIT")
	{
		return STATEEXIT;
	}

	ofstream out(filename);
	dictionary.inorderTravesal(out);
	out.close();
	ToMauToanBo(startx + 2, starty + 6, (char*) "Xuat file thanh cong!", EXPORTTHONGBAOCOLOR);

	// Ban muon tiep tuc
	return STATEPREVIOUS;
}

// Load
void loadDictionary(string fileName, HashTable<RBTree<Word>, Word>& dictionary)
{
	ifstream in(fileName);
	if (!in) throw (string) "Loi doc file " + fileName + "!\n";

	bool has = false;
	int check;
	string read, oldString;
	Word* newWord = NULL;

	while (!in.eof())
	{
		if (!has) getline(in, read);
		if (read.length())
		{
			if (Word::isWord(read) == 1) // là từ mới
			{
				has = true;
				oldString = read;
				read.clear();
				while (!in.eof())
				{
					getline(in, read);
					if (read.length())
					{
						check = Word::isWord(read);
						if (check != -1)
						{
							if (check == 1) has = true;
							else has = false;
							break;
						}
					}
				}

				if (!has) newWord = Word::Parse(oldString, read);
				else newWord = Word::Parse(oldString, strnull);

				if (newWord != NULL)
				{
					dictionary.add(newWord);
				}
			}
		}
	}

	in.close();
}

// Hàm nhập
string NhapKhungKeywordSearch()
{
	string nhap;
	char doc;
	textcolor(SEARCHKHUNGCOLOR);
	const int startx = 7, starty = 4; // = startx + 2, starty + 2   trong HienThiSearch
	int currentx = startx;

	const int GioiHanX = WIDTHFULLPIXELNUMBER - 14; //

	GotoXY(currentx, starty);
	while (1)
	{
		if (_kbhit())
		{
			doc = 0; // Huỷ phím lưu

			doc = _getch();
			if (doc == ' ' || (doc >= 'a' && doc <= 'z') || (doc >= 'A' && doc <= 'Z') || (doc >= '0' && doc <= '9'))
			{
				currentx++;
				nhap.push_back(doc);
				// in ra màn hình
				if (currentx > GioiHanX + 6) GotoXY(GioiHanX + 5, starty);
					std::cout << doc;

				if (currentx >= GioiHanX + 6 + 1)
				{
					ToMauToanBo(GioiHanX + 2, starty, (char *)"...", SEARCHKHUNGCOLOR);
					GotoXY(GioiHanX + 5, starty);
				}
			}
			if (doc == 8) // Backspace
			{
				if (nhap.length() > 0)
				{
					doc = nhap[nhap.length() - 1];
					nhap.pop_back();

					if (currentx >= GioiHanX + 3)
					{
						currentx--;
						if (currentx > GioiHanX + 6)
						{
							ToMauToanBo(GioiHanX + 5, starty, nhap[nhap.length() - 1], SEARCHKHUNGCOLOR);
							GotoXY(GioiHanX + 5, starty);
						}
						else
						{
							if (currentx == GioiHanX + 6)
							{
								ToMauToanBo(GioiHanX + 2, starty, nhap[nhap.length() - 4], SEARCHKHUNGCOLOR);
								ToMauToanBo(GioiHanX + 3, starty, nhap[nhap.length() - 3], SEARCHKHUNGCOLOR);
								ToMauToanBo(GioiHanX + 4, starty, nhap[nhap.length() - 2], SEARCHKHUNGCOLOR);
								ToMauToanBo(GioiHanX + 5, starty, nhap[nhap.length() - 1], SEARCHKHUNGCOLOR);
								GotoXY(GioiHanX + 5, starty);
							}
							else
							{
								ToMauToanBo(currentx, starty, ' ', SEARCHKHUNGCOLOR);
								GotoXY(currentx, starty);
							}
						}
					}
					else // Trường hợp bình thường
					{
						currentx--;
						ToMauToanBo(currentx, starty, (char *) " ", SEARCHKHUNGCOLOR);
						GotoXY(currentx, starty);
					}
				
				}
			}
			if (doc == 13 && nhap.length() > 0) // Enter
				break;
			if (doc == 27) // Escape
			{
				std::cout << (char)7;
				//for (int y = 0; y < 7; y++)// In lại khung đáp án
				//{
				//	ToMauToanBo(6, 23 + y, STRINGSEARCHKHUNG, SEARCHTHONGBAOCOLOR);
				//}
				ToMauToanBo(startx, starty + 5, (char *) "Are you want to quit? Y\\N: ", SEARCHTHONGBAOCOLOR);

				while (1)
				{
					if (_kbhit())
					{
						doc = _getch();
						if (doc == 'Y' || doc == 'y')
						{
							nhap = "EXIT";
							break;
						}
						if (doc == 'N' || doc == 'n')
						{
							ToMauToanBo(startx - 2, starty + 5, STRINGSEARCHKHUNG, SEARCHNENCOLOR);
							textcolor(SEARCHKHUNGCOLOR);
							GotoXY(currentx, starty);

							break;
						}
					}
				}
				if (doc == 'Y' || doc == 'y') break;
			}
		}
	}
	return nhap;
}
string NhapKhungKeywordRemove()
{
	string nhap;
	char doc;
	textcolor(REMOVEKHUNGCOLOR);
	const int startx = 7, starty = 4; // = startx + 2, starty + 2   trong HienThiSearch
	int currentx = startx;

	const int GioiHanX = WIDTHFULLPIXELNUMBER - 14; //

	GotoXY(currentx, starty);
	while (1)
	{
		if (_kbhit())
		{
			doc = 0; // Huỷ phím lưu

			doc = _getch();
			if (doc == ' ' || (doc >= 'a' && doc <= 'z') || (doc >= 'A' && doc <= 'Z') || (doc >= '0' && doc <= '9'))
			{
				currentx++;
				nhap.push_back(doc);
				// in ra màn hình
				if (currentx > GioiHanX + 6) GotoXY(GioiHanX + 5, starty);
				std::cout << doc;

				if (currentx >= GioiHanX + 6 + 1)
				{
					ToMauToanBo(GioiHanX + 2, starty, (char *)"...", REMOVEKHUNGCOLOR);
					GotoXY(GioiHanX + 5, starty);
				}

			}
			if (doc == 8) // Backspace
			{
				if (nhap.length() > 0)
				{
					doc = nhap[nhap.length() - 1];
					nhap.pop_back();

					if (currentx >= GioiHanX + 3)
					{
						currentx--;
						if (currentx > GioiHanX + 6)
						{
							ToMauToanBo(GioiHanX + 5, starty, nhap[nhap.length() - 1], REMOVEKHUNGCOLOR);
							GotoXY(GioiHanX + 5, starty);
						}
						else
						{
							if (currentx == GioiHanX + 6)
							{
								ToMauToanBo(GioiHanX + 2, starty, nhap[nhap.length() - 4], REMOVEKHUNGCOLOR);
								ToMauToanBo(GioiHanX + 3, starty, nhap[nhap.length() - 3], REMOVEKHUNGCOLOR);
								ToMauToanBo(GioiHanX + 4, starty, nhap[nhap.length() - 2], REMOVEKHUNGCOLOR);
								ToMauToanBo(GioiHanX + 5, starty, nhap[nhap.length() - 1], REMOVEKHUNGCOLOR);
								GotoXY(GioiHanX + 5, starty);
							}
							else
							{
								ToMauToanBo(currentx, starty, ' ', REMOVEKHUNGCOLOR);
								GotoXY(currentx, starty);
							}
						}
					}
					else // Trường hợp bình thường
					{
						currentx--;
						ToMauToanBo(currentx, starty, (char *) " ", REMOVEKHUNGCOLOR);
						GotoXY(currentx, starty);
					}

				}
			}
			if (doc == 13 && nhap.length() > 0) // Enter
				break;
			if (doc == 27) // Escape
			{
				std::cout << (char)7;

				ToMauToanBo(startx, starty + 5, (char *) "Are you want to quit? Y\\N: ", REMOVETHONGBAOCOLOR);

				while (1)
				{
					if (_kbhit())
					{
						doc = _getch();
						if (doc == 'Y' || doc == 'y')
						{
							nhap = "EXIT";
							break;
						}
						if (doc == 'N' || doc == 'n')
						{
							ToMauToanBo(startx - 2, starty + 5, STRINGSEARCHKHUNG, REMOVENENCOLOR);
							textcolor(REMOVEKHUNGCOLOR);
							GotoXY(currentx, starty);

							break;
						}
					}
				}
				if (doc == 'Y' || doc == 'y') break;
			}
		}
	}
	return nhap;
}
string NhapKhungKeywordAdd()
{
	string nhap;
	char doc;
	textcolor(ADDKHUNGCOLOR);
	const int startx = 7, starty = 4; // = startx + 2, starty + 2   trong HienThiSearch
	int currentx = startx;

	const int GioiHanX = WIDTHFULLPIXELNUMBER - 14; //

	GotoXY(currentx, starty);
	while (1)
	{
		if (_kbhit())
		{
			doc = 0; // Huỷ phím lưu

			doc = _getch();
			if (doc == ' ' || (doc >= 'a' && doc <= 'z') || (doc >= 'A' && doc <= 'Z') || (doc >= '0' && doc <= '9'))
			{
				currentx++;
				nhap.push_back(doc);
				// in ra màn hình
				if (currentx > GioiHanX + 6) GotoXY(GioiHanX + 5, starty);
				std::cout << doc;

				if (currentx >= GioiHanX + 6 + 1)
				{
					ToMauToanBo(GioiHanX + 2, starty, (char *)"...", ADDKHUNGCOLOR);
					GotoXY(GioiHanX + 5, starty);
				}
			}
			if (doc == 8) // Backspace
			{
				if (nhap.length() > 0)
				{
					doc = nhap[nhap.length() - 1];
					nhap.pop_back();

					if (currentx >= GioiHanX + 3)
					{
						currentx--;
						if (currentx > GioiHanX + 6)
						{
							ToMauToanBo(GioiHanX + 5, starty, nhap[nhap.length() - 1], ADDKHUNGCOLOR);
							GotoXY(GioiHanX + 5, starty);
						}
						else
						{
							if (currentx == GioiHanX + 6)
							{
								ToMauToanBo(GioiHanX + 2, starty, nhap[nhap.length() - 4], ADDKHUNGCOLOR);
								ToMauToanBo(GioiHanX + 3, starty, nhap[nhap.length() - 3], ADDKHUNGCOLOR);
								ToMauToanBo(GioiHanX + 4, starty, nhap[nhap.length() - 2], ADDKHUNGCOLOR);
								ToMauToanBo(GioiHanX + 5, starty, nhap[nhap.length() - 1], ADDKHUNGCOLOR);
								GotoXY(GioiHanX + 5, starty);
							}
							else
							{
								ToMauToanBo(currentx, starty, ' ', ADDKHUNGCOLOR);
								GotoXY(currentx, starty);
							}
						}
					}
					else // Trường hợp bình thường
					{
						currentx--;
						ToMauToanBo(currentx, starty, (char *) " ", ADDKHUNGCOLOR);
						GotoXY(currentx, starty);
					}

				}
			}
			if (doc == 13 && nhap.length() > 0) // Enter
				break;
			if (doc == 27) // Escape
			{
				std::cout << (char)7;
				ToMauToanBo(startx, starty + 5, (char *) "Are you want to quit? Y\\N: ", ADDTHONGBAOCOLOR);

				while (1)
				{
					if (_kbhit())
					{
						doc = _getch();
						if (doc == 'Y' || doc == 'y')
						{
							nhap = "EXIT";
							break;
						}
						if (doc == 'N' || doc == 'n')
						{
							ToMauToanBo(startx - 2, starty + 5, STRINGSEARCHKHUNG, ADDNENCOLOR);
							textcolor(ADDKHUNGCOLOR);
							GotoXY(currentx, starty);

							break;
						}
					}
				}
				if (doc == 'Y' || doc == 'y') break;
			}
		}
	}
	return nhap;
}
string NhapKhungMeaningAdd()
{
	string nhap;
	char doc;
	textcolor(ADDKHUNGCOLOR);
	const int startx = 7, starty = 9; // = startx + 2, starty + 2   trong HienThiSearch
	const int maxrowy = 2;
	int currentx = startx, currenty = starty;

	const int GioiHanX = WIDTHFULLPIXELNUMBER - 14; //

	GotoXY(currentx, currenty);
	while (1)
	{
		if (_kbhit())
		{
			doc = 0; // Huỷ phím lưu

			doc = _getch();
			if (doc == ' ' || (doc >= 'a' && doc <= 'z') || (doc >= 'A' && doc <= 'Z') || (doc >= '0' && doc <= '9'))
			{
				currentx++;
				nhap.push_back(doc);
				// in ra màn hình
				if (currentx > GioiHanX + 6 && currenty == starty + maxrowy) GotoXY(GioiHanX + 5, starty + maxrowy);
				std::cout << doc;

				if (currentx >= GioiHanX + 6 && currenty < starty + maxrowy)
				{
					currentx = startx;
					GotoXY(currentx, ++currenty);
				}

				if (currentx >= GioiHanX + 6 + 1 && currenty == starty + maxrowy)
				{
					ToMauToanBo(GioiHanX + 2, starty + maxrowy, (char *)"...", ADDKHUNGCOLOR);
					GotoXY(GioiHanX + 5, starty + maxrowy);
				}
			}
			if (doc == 8) // Backspace
			{
				if (nhap.length() > 0)
				{
					doc = nhap[nhap.length() - 1];
					nhap.pop_back();

					if (currentx == startx)
					{
						currentx = GioiHanX + 5;
						currenty--;
						ToMauToanBo(currentx, currenty, ' ', ADDKHUNGCOLOR);
						GotoXY(currentx, currenty);
					}
					else
						if (currentx >= GioiHanX + 3 && currenty == starty + maxrowy)
						{
							currentx--;
							if (currentx > GioiHanX + 6)
							{
								ToMauToanBo(GioiHanX + 5, starty + maxrowy, nhap[nhap.length() - 1], ADDKHUNGCOLOR);
								GotoXY(GioiHanX + 5, starty + maxrowy);
							}
							else
							{
								if (currentx == GioiHanX + 6)
								{
									ToMauToanBo(GioiHanX + 2, starty + maxrowy, nhap[nhap.length() - 4], ADDKHUNGCOLOR);
									ToMauToanBo(GioiHanX + 3, starty + maxrowy, nhap[nhap.length() - 3], ADDKHUNGCOLOR);
									ToMauToanBo(GioiHanX + 4, starty + maxrowy, nhap[nhap.length() - 2], ADDKHUNGCOLOR);
									ToMauToanBo(GioiHanX + 5, starty + maxrowy, nhap[nhap.length() - 1], ADDKHUNGCOLOR);
									GotoXY(GioiHanX + 5, currenty);
								}
								else
								{
									ToMauToanBo(currentx, starty + maxrowy, ' ', ADDKHUNGCOLOR);
									GotoXY(currentx, currenty);
								}
							}
						}
						else // Trường hợp bình thường
						{
							currentx--;
							ToMauToanBo(currentx, currenty, (char *) " ", ADDKHUNGCOLOR);
							GotoXY(currentx, currenty);
						}

				}
			}
			if (doc == 13 && nhap.length() > 0) // Enter
				break;
			if (doc == 27) // Escape
			{
				std::cout << (char)7;
				ToMauToanBo(startx, starty + maxrowy + 3, (char *) "Are you want to quit? Y\\N: ", ADDTHONGBAOCOLOR);

				while (1)
				{
					if (_kbhit())
					{
						doc = _getch();
						if (doc == 'Y' || doc == 'y')
						{
							nhap = "EXIT";
							break;
						}
						if (doc == 'N' || doc == 'n')
						{
							ToMauToanBo(startx - 2, starty + maxrowy + 3, STRINGSEARCHKHUNG, ADDNENCOLOR);
							textcolor(ADDKHUNGCOLOR);
							GotoXY(currentx, currenty);

							break;
						}
					}
				}
				if (doc == 'Y' || doc == 'y') break;
			}
		}
	}
	return nhap;
}
string NhapKhungUsageAdd()
{
	string nhap;
	char doc;
	textcolor(ADDKHUNGCOLOR);
	const int startx = 7, starty = 16; // = startx + 2, starty + 2   trong HienThiSearch
	const int maxrowy = 1;
	int currentx = startx, currenty = starty;

	const int GioiHanX = WIDTHFULLPIXELNUMBER - 14; //

	GotoXY(currentx, currenty);
	while (1)
	{
		if (_kbhit())
		{
			doc = 0; // Huỷ phím lưu

			doc = _getch();
			if (doc == ' ' || (doc >= 'a' && doc <= 'z') || (doc >= 'A' && doc <= 'Z') || (doc >= '0' && doc <= '9'))
			{
				currentx++;
				nhap.push_back(doc);
				// in ra màn hình
				if (currentx > GioiHanX + 6 && currenty == starty + maxrowy) GotoXY(GioiHanX + 5, starty + maxrowy);
				std::cout << doc;

				if (currentx >= GioiHanX + 6 && currenty < starty + maxrowy)
				{
					currentx = startx;
					GotoXY(currentx, ++currenty);
				}

				if (currentx >= GioiHanX + 6 + 1 && currenty == starty + maxrowy)
				{
					ToMauToanBo(GioiHanX + 2, starty + maxrowy, (char *)"...", ADDKHUNGCOLOR);
					GotoXY(GioiHanX + 5, starty + maxrowy);
				}
			}
			if (doc == 8) // Backspace
			{
				if (nhap.length() > 0)
				{
					doc = nhap[nhap.length() - 1];
					nhap.pop_back();

					if (currentx == startx)
					{
						currentx = GioiHanX + 5;
						currenty--;
						ToMauToanBo(currentx, currenty, ' ', ADDKHUNGCOLOR);
						GotoXY(currentx, currenty);
					}
					else
						if (currentx >= GioiHanX + 3 && currenty == starty + maxrowy)
						{
							currentx--;
							if (currentx > GioiHanX + 6)
							{
								ToMauToanBo(GioiHanX + 5, starty + maxrowy, nhap[nhap.length() - 1], ADDKHUNGCOLOR);
								GotoXY(GioiHanX + 5, starty + maxrowy);
							}
							else
							{
								if (currentx == GioiHanX + 6)
								{
									ToMauToanBo(GioiHanX + 2, starty + maxrowy, nhap[nhap.length() - 4], ADDKHUNGCOLOR);
									ToMauToanBo(GioiHanX + 3, starty + maxrowy, nhap[nhap.length() - 3], ADDKHUNGCOLOR);
									ToMauToanBo(GioiHanX + 4, starty + maxrowy, nhap[nhap.length() - 2], ADDKHUNGCOLOR);
									ToMauToanBo(GioiHanX + 5, starty + maxrowy, nhap[nhap.length() - 1], ADDKHUNGCOLOR);
									GotoXY(GioiHanX + 5, currenty);
								}
								else
								{
									ToMauToanBo(currentx, starty + maxrowy, ' ', ADDKHUNGCOLOR);
									GotoXY(currentx, currenty);
								}
							}
						}
						else // Trường hợp bình thường
						{
							currentx--;
							ToMauToanBo(currentx, currenty, (char *) " ", ADDKHUNGCOLOR);
							GotoXY(currentx, currenty);
						}

				}
			}
			if (doc == 13) // Enter
				break;
			if (doc == 27) // Escape
			{
				std::cout << (char)7;
				ToMauToanBo(startx, starty + maxrowy + 3, (char *) "Are you want to quit? Y\\N: ", ADDTHONGBAOCOLOR);

				while (1)
				{
					if (_kbhit())
					{
						doc = _getch();
						if (doc == 'Y' || doc == 'y')
						{
							nhap = "EXIT";
							break;
						}
						if (doc == 'N' || doc == 'n')
						{
							ToMauToanBo(startx - 2, starty + maxrowy + 3, STRINGSEARCHKHUNG, ADDNENCOLOR);
							textcolor(ADDKHUNGCOLOR);
							GotoXY(currentx, currenty);

							break;
						}
					}
				}
				if (doc == 'Y' || doc == 'y') break;
			}
		}
	}
	return nhap;
}
string NhapKhungKeywordFix()
{
	string nhap;
	char doc;
	textcolor(FIXKHUNGCOLOR);
	const int startx = 7, starty = 4; // = startx + 2, starty + 2   trong HienThiSearch
	int currentx = startx;

	const int GioiHanX = WIDTHFULLPIXELNUMBER - 14; //

	GotoXY(currentx, starty);
	while (1)
	{
		if (_kbhit())
		{
			doc = 0; // Huỷ phím lưu

			doc = _getch();
			if (doc == ' ' || (doc >= 'a' && doc <= 'z') || (doc >= 'A' && doc <= 'Z') || (doc >= '0' && doc <= '9'))
			{
				currentx++;
				nhap.push_back(doc);
				// in ra màn hình
				if (currentx > GioiHanX + 6) GotoXY(GioiHanX + 5, starty);
				std::cout << doc;

				if (currentx >= GioiHanX + 6 + 1)
				{
					ToMauToanBo(GioiHanX + 2, starty, (char *)"...", SEARCHKHUNGCOLOR);
					GotoXY(GioiHanX + 5, starty);
				}
			}
			if (doc == 8) // Backspace
			{
				if (nhap.length() > 0)
				{
					doc = nhap[nhap.length() - 1];
					nhap.pop_back();

					if (currentx >= GioiHanX + 3)
					{
						currentx--;
						if (currentx > GioiHanX + 6)
						{
							ToMauToanBo(GioiHanX + 5, starty, nhap[nhap.length() - 1], FIXKHUNGCOLOR);
							GotoXY(GioiHanX + 5, starty);
						}
						else
						{
							if (currentx == GioiHanX + 6)
							{
								ToMauToanBo(GioiHanX + 2, starty, nhap[nhap.length() - 1], FIXKHUNGCOLOR);
								ToMauToanBo(GioiHanX + 3, starty, nhap[nhap.length() - 3], FIXKHUNGCOLOR);
								ToMauToanBo(GioiHanX + 4, starty, nhap[nhap.length() - 2], FIXKHUNGCOLOR);
								ToMauToanBo(GioiHanX + 5, starty, nhap[nhap.length() - 1], FIXKHUNGCOLOR);
								GotoXY(GioiHanX + 5, starty);
							}
							else
							{
								ToMauToanBo(currentx, starty, ' ', FIXKHUNGCOLOR);
								GotoXY(currentx, starty);
							}
						}
					}
					else // Trường hợp bình thường
					{
						currentx--;
						ToMauToanBo(currentx, starty, (char *) " ", FIXKHUNGCOLOR);
						GotoXY(currentx, starty);
					}

				}
			}
			if (doc == 13 && nhap.length() > 0) // Enter
				break;
			if (doc == 27) // Escape
			{
				std::cout << (char)7;
				ToMauToanBo(startx, starty + 5, (char *) "Are you want to quit? Y\\N: ", FIXTHONGBAOCOLOR);

				while (1)
				{
					if (_kbhit())
					{
						doc = _getch();
						if (doc == 'Y' || doc == 'y')
						{
							nhap = "EXIT";
							break;
						}
						if (doc == 'N' || doc == 'n')
						{
							ToMauToanBo(startx - 2, starty + 5, STRINGSEARCHKHUNG, FIXNENCOLOR);
							textcolor(FIXKHUNGCOLOR);
							GotoXY(currentx, starty);

							break;
						}
					}
				}
				if (doc == 'Y' || doc == 'y') break;
			}
		}
	}
	return nhap;
}
string NhapKhungMeaningFix()
{
	string nhap;
	char doc;
	textcolor(FIXKHUNGCOLOR);
	const int startx = 7, starty = 9; // = startx + 2, starty + 2   trong HienThiSearch
	const int maxrowy = 2;
	int currentx = startx, currenty = starty;

	const int GioiHanX = WIDTHFULLPIXELNUMBER - 14; //

	GotoXY(currentx, currenty);
	while (1)
	{
		if (_kbhit())
		{
			doc = 0; // Huỷ phím lưu

			doc = _getch();
			if (doc == ' ' || (doc >= 'a' && doc <= 'z') || (doc >= 'A' && doc <= 'Z') || (doc >= '0' && doc <= '9'))
			{
				currentx++;
				nhap.push_back(doc);
				// in ra màn hình
				if (currentx > GioiHanX + 6 && currenty == starty + maxrowy) GotoXY(GioiHanX + 5, starty + maxrowy);
				std::cout << doc;

				if (currentx >= GioiHanX + 6 && currenty < starty + maxrowy)
				{
					currentx = startx;
					GotoXY(currentx, ++currenty);
				}

				if (currentx >= GioiHanX + 6 + 1 && currenty == starty + maxrowy)
				{
					ToMauToanBo(GioiHanX + 2, starty + maxrowy, (char *)"...", FIXKHUNGCOLOR);
					GotoXY(GioiHanX + 5, starty + maxrowy);
				}
			}
			if (doc == 8) // Backspace
			{
				if (nhap.length() > 0)
				{
					doc = nhap[nhap.length() - 1];
					nhap.pop_back();

					if (currentx == startx)
					{
						currentx = GioiHanX + 5;
						currenty--;
						ToMauToanBo(currentx, currenty, ' ', FIXKHUNGCOLOR);
						GotoXY(currentx, currenty);
					}
					else
						if (currentx >= GioiHanX + 3 && currenty == starty + maxrowy)
						{
							currentx--;
							if (currentx > GioiHanX + 6)
							{
								ToMauToanBo(GioiHanX + 5, starty + maxrowy, nhap[nhap.length() - 1], FIXKHUNGCOLOR);
								GotoXY(GioiHanX + 5, starty + maxrowy);
							}
							else
							{
								if (currentx == GioiHanX + 6)
								{
									ToMauToanBo(GioiHanX + 2, starty + maxrowy, nhap[nhap.length() - 4], FIXKHUNGCOLOR);
									ToMauToanBo(GioiHanX + 3, starty + maxrowy, nhap[nhap.length() - 3], FIXKHUNGCOLOR);
									ToMauToanBo(GioiHanX + 4, starty + maxrowy, nhap[nhap.length() - 2], FIXKHUNGCOLOR);
									ToMauToanBo(GioiHanX + 5, starty + maxrowy, nhap[nhap.length() - 1], FIXKHUNGCOLOR);
									GotoXY(GioiHanX + 5, currenty);
								}
								else
								{
									ToMauToanBo(currentx, starty + maxrowy, ' ', FIXKHUNGCOLOR);
									GotoXY(currentx, currenty);
								}
							}
						}
						else // Trường hợp bình thường
						{
							currentx--;
							ToMauToanBo(currentx, currenty, (char *) " ", FIXKHUNGCOLOR);
							GotoXY(currentx, currenty);
						}

				}
			}
			if (doc == 13 && nhap.length() > 0) // Enter
				break;
			if (doc == 27) // Escape
			{
				std::cout << (char)7;
				ToMauToanBo(startx, starty + maxrowy + 3, (char *) "Are you want to quit? Y\\N: ", FIXTHONGBAOCOLOR);

				while (1)
				{
					if (_kbhit())
					{
						doc = _getch();
						if (doc == 'Y' || doc == 'y')
						{
							nhap = "EXIT";
							break;
						}
						if (doc == 'N' || doc == 'n')
						{
							ToMauToanBo(startx - 2, starty + maxrowy + 3, STRINGSEARCHKHUNG, FIXNENCOLOR);
							textcolor(FIXKHUNGCOLOR);
							GotoXY(currentx, currenty);

							break;
						}
					}
				}
				if (doc == 'Y' || doc == 'y') break;
			}
		}
	}
	return nhap;
}
string NhapKhungUsageFix()
{
	string nhap;
	char doc;
	textcolor(FIXKHUNGCOLOR);
	const int startx = 7, starty = 16; // = startx + 2, starty + 2   trong HienThiSearch
	const int maxrowy = 1;
	int currentx = startx, currenty = starty;

	const int GioiHanX = WIDTHFULLPIXELNUMBER - 14; //

	GotoXY(currentx, currenty);
	while (1)
	{
		if (_kbhit())
		{
			doc = 0; // Huỷ phím lưu

			doc = _getch();
			if (doc == ' ' || (doc >= 'a' && doc <= 'z') || (doc >= 'A' && doc <= 'Z') || (doc >= '0' && doc <= '9'))
			{
				currentx++;
				nhap.push_back(doc);
				// in ra màn hình
				if (currentx > GioiHanX + 6 && currenty == starty + maxrowy) GotoXY(GioiHanX + 5, starty + maxrowy);
				std::cout << doc;

				if (currentx >= GioiHanX + 6 && currenty < starty + maxrowy)
				{
					currentx = startx;
					GotoXY(currentx, ++currenty);
				}

				if (currentx >= GioiHanX + 6 + 1 && currenty == starty + maxrowy)
				{
					ToMauToanBo(GioiHanX + 2, starty + maxrowy, (char *)"...", FIXKHUNGCOLOR);
					GotoXY(GioiHanX + 5, starty + maxrowy);
				}
			}
			if (doc == 8) // Backspace
			{
				if (nhap.length() > 0)
				{
					doc = nhap[nhap.length() - 1];
					nhap.pop_back();

					if (currentx == startx)
					{
						currentx = GioiHanX + 5;
						currenty--;
						ToMauToanBo(currentx, currenty, ' ', FIXKHUNGCOLOR);
						GotoXY(currentx, currenty);
					}
					else
						if (currentx >= GioiHanX + 3 && currenty == starty + maxrowy)
						{
							currentx--;
							if (currentx > GioiHanX + 6)
							{
								ToMauToanBo(GioiHanX + 5, starty + maxrowy, nhap[nhap.length() - 1], FIXKHUNGCOLOR);
								GotoXY(GioiHanX + 5, starty + maxrowy);
							}
							else
							{
								if (currentx == GioiHanX + 6)
								{
									ToMauToanBo(GioiHanX + 2, starty + maxrowy, nhap[nhap.length() - 4], FIXKHUNGCOLOR);
									ToMauToanBo(GioiHanX + 3, starty + maxrowy, nhap[nhap.length() - 3], FIXKHUNGCOLOR);
									ToMauToanBo(GioiHanX + 4, starty + maxrowy, nhap[nhap.length() - 2], FIXKHUNGCOLOR);
									ToMauToanBo(GioiHanX + 5, starty + maxrowy, nhap[nhap.length() - 1], FIXKHUNGCOLOR);
									GotoXY(GioiHanX + 5, currenty);
								}
								else
								{
									ToMauToanBo(currentx, starty + maxrowy, ' ', FIXKHUNGCOLOR);
									GotoXY(currentx, currenty);
								}
							}
						}
						else // Trường hợp bình thường
						{
							currentx--;
							ToMauToanBo(currentx, currenty, (char *) " ", FIXKHUNGCOLOR);
							GotoXY(currentx, currenty);
						}

				}
			}
			if (doc == 13) // Enter
				break;
			if (doc == 27) // Escape
			{
				std::cout << (char)7;
				ToMauToanBo(startx, starty + maxrowy + 3, (char *) "Are you want to quit? Y\\N: ", FIXTHONGBAOCOLOR);

				while (1)
				{
					if (_kbhit())
					{
						doc = _getch();
						if (doc == 'Y' || doc == 'y')
						{
							nhap = "EXIT";
							break;
						}
						if (doc == 'N' || doc == 'n')
						{
							ToMauToanBo(startx - 2, starty + maxrowy + 3, STRINGSEARCHKHUNG, FIXNENCOLOR);
							textcolor(FIXKHUNGCOLOR);
							GotoXY(currentx, currenty);

							break;
						}
					}
				}
				if (doc == 'Y' || doc == 'y') break;
			}
		}
	}
	return nhap;
}
string NhapKhungDuongDanExport()
{
	string nhap;
	char doc;
	textcolor(EXPORTKHUNGCOLOR);
	const int startx = 7, starty = 4; // = startx + 2, starty + 2   trong HienThiSearch
	int currentx = startx;

	const int GioiHanX = WIDTHFULLPIXELNUMBER - 14; //

	GotoXY(currentx, starty);
	while (1)
	{
		if (_kbhit())
		{
			doc = 0; // Huỷ phím lưu

			doc = _getch();
			if (doc == ':'  || doc == '/' || doc == '-' || doc == '_' || doc == '.' || doc == ' ' || (doc >= 'a' && doc <= 'z') || (doc >= 'A' && doc <= 'Z') || (doc >= '0' && doc <= '9'))
			{
				currentx++;
				nhap.push_back(doc);
				// in ra màn hình
				if (currentx > GioiHanX + 6) GotoXY(GioiHanX + 5, starty);
				std::cout << doc;

				if (currentx >= GioiHanX + 6 + 1)
				{
					ToMauToanBo(GioiHanX + 2, starty, (char *)"...", EXPORTKHUNGCOLOR);
					GotoXY(GioiHanX + 5, starty);
				}
			}
			if (doc == 8) // Backspace
			{
				if (nhap.length() > 0)
				{
					doc = nhap[nhap.length() - 1];
					nhap.pop_back();

					if (currentx >= GioiHanX + 3)
					{
						currentx--;
						if (currentx > GioiHanX + 6)
						{
							ToMauToanBo(GioiHanX + 5, starty, nhap[nhap.length() - 1], EXPORTKHUNGCOLOR);
							GotoXY(GioiHanX + 5, starty);
						}
						else
						{
							if (currentx == GioiHanX + 6)
							{
								ToMauToanBo(GioiHanX + 2, starty, nhap[nhap.length() - 4], EXPORTKHUNGCOLOR);
								ToMauToanBo(GioiHanX + 3, starty, nhap[nhap.length() - 3], EXPORTKHUNGCOLOR);
								ToMauToanBo(GioiHanX + 4, starty, nhap[nhap.length() - 2], EXPORTKHUNGCOLOR);
								ToMauToanBo(GioiHanX + 5, starty, nhap[nhap.length() - 1], EXPORTKHUNGCOLOR);
								GotoXY(GioiHanX + 5, starty);
							}
							else
							{
								ToMauToanBo(currentx, starty, ' ', EXPORTKHUNGCOLOR);
								GotoXY(currentx, starty);
							}
						}
					}
					else // Trường hợp bình thường
					{
						currentx--;
						ToMauToanBo(currentx, starty, (char *) " ", EXPORTKHUNGCOLOR);
						GotoXY(currentx, starty);
					}

				}
			}
			if (doc == 13 && nhap.length() > 0) // Enter
				break;
			if (doc == 27) // Escape
			{
				std::cout << (char)7;
				//for (int y = 0; y < 7; y++)// In lại khung đáp án
				//{
				//	ToMauToanBo(6, 23 + y, STRINGEXPORTKHUNG, EXPORTTHONGBAOCOLOR);
				//}
				ToMauToanBo(startx, starty + 5, (char *) "Are you want to quit? Y\\N: ", EXPORTTHONGBAOCOLOR);

				while (1)
				{
					if (_kbhit())
					{
						doc = _getch();
						if (doc == 'Y' || doc == 'y')
						{
							nhap = "EXIT";
							break;
						}
						if (doc == 'N' || doc == 'n')
						{
							ToMauToanBo(startx - 2, starty + 5, STRINGSEARCHKHUNG, EXPORTNENCOLOR);
							textcolor(EXPORTKHUNGCOLOR);
							GotoXY(currentx, starty);

							break;
						}
					}
				}
				if (doc == 'Y' || doc == 'y') break;
			}
		}
	}
	return nhap;
}