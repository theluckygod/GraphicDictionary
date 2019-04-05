#include "lib.h"
using namespace std;


void main()
{
	try
	{
		// Không dụng vào
		resizeConsole(CONSOLEFULLWIDTH, CONSOLEFULLHEIGHT);
		FixConsoleWindow();
		Nocursortype();

		HashTable<RBTree<Word>, Word> dictionary;
		int dieukhien = STATEPREVIOUS;
		std::cout << "Loading...";
		loadDictionary(DICTIONARYFILENAME, dictionary);
		ChuyenCanh(NENKHUNGCOLOR);

		do
		{
			// Vẽ khung
			ToMauToanBo(0, 0, STRINGKHUNG, KHUNGCOLOR);
			ToMauToanBo(0, HEIGHTFULLPIXELNUMBER - 1, STRINGKHUNG, KHUNGCOLOR);
			for (int i = 1; i < HEIGHTFULLPIXELNUMBER - 1; i++)
			{
				ToMauToanBo(0, i, (char *)"  ", KHUNGCOLOR);
				ToMauToanBo(WIDTHFULLPIXELNUMBER - 2, i, (char *)"  ", KHUNGCOLOR);
				ToMauToanBo(2, i, STRINGNENKHUNG, NENKHUNGCOLOR);
			}


			//
			switch (HienThiMenu())
			{
			case 0:
				dieukhien = STATEEXIT;
				break;
			case 1:
				ChuyenCanh(SEARCHNENCOLOR);
				dieukhien = HienThiSearch(dictionary);
				if(dieukhien == STATEPREVIOUS) BatPhimKetThuc();
				break;
			case 2:
				ChuyenCanh(ADDNENCOLOR);
				dieukhien = HienThiAdd(dictionary);
				if (dieukhien == STATEPREVIOUS) BatPhimKetThuc();
				break;
			case 3:
				ChuyenCanh(FIXNENCOLOR);
				dieukhien = HienThiFix(dictionary);
				if (dieukhien == STATEPREVIOUS) BatPhimKetThuc();
				break;
			case 4:
				ChuyenCanh(REMOVENENCOLOR);
				dieukhien = HienThiRemove(dictionary);
				if (dieukhien == STATEPREVIOUS) BatPhimKetThuc();
				break;
			case 5:
				ChuyenCanh(SAVENENCOLOR);
				dieukhien = HienThiSave(dictionary);
				if (dieukhien == STATEPREVIOUS) BatPhimKetThuc();
				break;
			case 6:
				ChuyenCanh(EXPORTNENCOLOR);
				dieukhien = HienThiExport(dictionary);
				if (dieukhien == STATEPREVIOUS) BatPhimKetThuc();
				break;
			}


			ChuyenCanh(NENKHUNGCOLOR);
		} while (dieukhien == STATEPREVIOUS);
	}
	catch (string error)
	{
		cerr << error;
	}
	catch (...)
	{
		cerr << "Loi nao do!\n";
	}
	
	//// Phím kết thúc
	//if (_kbhit())
	//{
	//	_getch();
	//	while (_kbhit())
	//	{
	//		_getch();
	//	}
	//}
	//while (1)
	//{
	//	if (_kbhit()) break;
	//}
}