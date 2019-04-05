#pragma once
#include <iostream>
#include <Windows.h>
#include <conio.h>
#include <string>
#include <fstream>
#include <ctime>

#include "HashTable.h"
#include "RBTree.h"
#include "Word.h"
using namespace std;

// Thông số console
#define CONSOLEFULLWIDTH 689 //
#define CONSOLEFULLHEIGHT 391 //
#define WIDTHFULLPIXELNUMBER 82 //
#define HEIGHTFULLPIXELNUMBER 22 //

// Thông số màu
#define KHUNGCOLOR 100 //
#define NENKHUNGCOLOR 34 // 160
#define DICTKHUNGCOLOR 68 //
#define NOIDUNGKHUNGCOLOR 62 // 56
#define HIGHLIGHTNOIDUNGKHUNGCOLOR 83 //  89

#define SEARCHNENCOLOR 233 // 238
#define SEARCHTHONGBAOCOLOR 236 //
#define SEARCHKHUNGCOLOR 159 // 238 153

#define ADDNENCOLOR 249 // 102 110
#define ADDTHONGBAOCOLOR 252 // 
#define ADDKHUNGCOLOR 110 // 

#define FIXNENCOLOR 207 // 202
#define FIXTHONGBAOCOLOR 206 //
#define FIXKHUNGCOLOR 235 //

#define REMOVENENCOLOR 155 // 153
#define REMOVETHONGBAOCOLOR 156 //
#define REMOVEKHUNGCOLOR 11 //

#define SAVENENCOLOR 143 // 136
#define SAVETHONGBAOCOLOR 140 // 136

#define EXPORTNENCOLOR 26 // 17
#define EXPORTKHUNGCOLOR 185 // 17
#define EXPORTTHONGBAOCOLOR 28 // 17

// Char
#define STRINGKHUNG (char *)"                                                                                  "
#define STRINGNENKHUNG (char *)"                                                                              "
#define STRINGSEARCHKHUNG (char*) "                                                                       "

// Thông số dictionary
#define DICTIONARYFILENAME (string) "dictionary.txt"

// Thông số trạng thái chương trình
#define STATECONTINUE 1
#define STATEEXIT -1
#define STATEPREVIOUS 0



// Hàm cài đặt console
void resizeConsole(int width, int height); // Thay đổi kích thước console
void FixConsoleWindow();// Ngăn phóng to, thu nhỏ màn hình
void textcolor(int color); // Hàm tô màu
void GotoXY(int x, int y);  // Di chuyển con trỏ console
void Nocursortype(); // Ẩn con trỏ

// Hàm tô màu
void ToMauToanBo(int x, int y, char* ch, int color); // Vẽ chuỗi str với màu color lên vị trí (x, y) cho toàn bộ vị trí
void ToMauToanBo(int x, int y, char ch, int color);
void ToMauKhungKetQuaSearch(int x, int y, string ch, int color);


// Hàm điều khiển chương trinh
void BatPhimKetThuc();
void ChuyenCanh(int CHUYENCANHCOLOR);
int HienThiMenu();
int HienThiSearch(const HashTable<RBTree<Word>, Word> &);
int HienThiRemove(HashTable<RBTree<Word>, Word>&);
int HienThiAdd(HashTable<RBTree<Word>, Word>&);
int HienThiFix(HashTable<RBTree<Word>, Word>&);
int HienThiSave(const HashTable<RBTree<Word>, Word> &);
int HienThiExport(const HashTable<RBTree<Word>, Word> &);
void ChuyenCanh(int MAUCHUYEN);

// Hàm nhập
string NhapKhungKeywordSearch();
string NhapKhungKeywordRemove();
string NhapKhungKeywordAdd();
string NhapKhungMeaningAdd();
string NhapKhungUsageAdd();
string NhapKhungKeywordFix();
string NhapKhungMeaningFix();
string NhapKhungUsageFix();
string NhapKhungDuongDanExport();

// Hàm load cho dictionary
void loadDictionary(string fileName, HashTable<RBTree<Word>, Word>& dictionary);