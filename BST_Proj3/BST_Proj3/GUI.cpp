#include <Windows.h>
#include <string>
#include < stdio.h >
#include "BST.cpp"


#define FILE_MENU_NEW 1
#define FILE_MENU_OPEN 2
#define FILE_MENU_EXIT 3
#define ENTER_BUTTON 4


using namespace std;

LRESULT CALLBACK WindowProcedure(HWND, UINT, WPARAM, LPARAM);

void AddMenus(HWND hWnd);
void AddControls(HWND hWnd);


HMENU hMenu;
HWND hID, hOut1, hOut2, hOut3, hOut4, hOut5, hOut6, hOut7, hOut8;

int main(HINSTANCE hInst, HINSTANCE hPrevInst, LPSTR atgs, int ncmdshow) {



	WNDCLASSW wc = { 0 };

	wc.hbrBackground = (HBRUSH)COLOR_WINDOW;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hInstance = hInst;
	wc.lpszClassName = L"myWindowClass";
	wc.lpfnWndProc = WindowProcedure;

	if (!RegisterClassW(&wc))
		return -1;

	CreateWindowW(L"myWindowClass", L"T.H.S", WS_OVERLAPPEDWINDOW | WS_VISIBLE, 100, 100, 500, 500, NULL, NULL, NULL, NULL);

	MSG msg = { 0 };

	while (GetMessage(&msg, NULL, NULL, NULL)) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return 0;
}

LRESULT CALLBACK WindowProcedure(HWND hWnd, UINT msg, WPARAM wp, LPARAM lp) {
	BST static t;
	int static count = 0;
	if (count == 0) {
		vector<vector<string>> data = t.readFile(".\\100000 Sales Records.csv");
		t.insert(data);
		count++;
	}
	switch (msg) {
	case WM_COMMAND:
		switch (wp) {

		case FILE_MENU_EXIT:
			DestroyWindow(hWnd);
			break;
		case FILE_MENU_NEW:
			MessageBeep(MB_ICONINFORMATION);
			break;
		case ENTER_BUTTON:
			wchar_t ID[20];

			string region, country, unitsSold, unitPrice, unitCost, totalRevenue, totalCost, totalProfit;



			GetWindowText(hID, ID, 20);
			wstring ws(ID);
			string stringID(ws.begin(), ws.end());
			vector<string> resultVec = t.search(stoi(stringID));
			if (resultVec.size() == 0) {
				string result1Str("INVALID STRING");

				wstring wide_string = wstring(result1Str.begin(), result1Str.end());
				const wchar_t* result1 = wide_string.c_str();

				SetWindowText(hOut1, result1);

				string result2Str("");

				wstring wide_string1 = wstring(result2Str.begin(), result2Str.end());
				const wchar_t* result2 = wide_string1.c_str();

				SetWindowText(hOut2, result2);
				SetWindowText(hOut3, result2);
				SetWindowText(hOut4, result2);
				SetWindowText(hOut5, result2);
				SetWindowText(hOut6, result2);
				SetWindowText(hOut7, result2);
				SetWindowText(hOut8, result2);

				break;
			}
			else {
				region = resultVec[0];
				country = resultVec[1];
				unitsSold = resultVec[2];
				unitPrice = resultVec[3];
				unitCost = resultVec[4];
				totalRevenue = resultVec[5];
				totalCost = resultVec[6];
				totalProfit = resultVec[7];


				string result1Str("Region: " + region);

				wstring wide_string = wstring(result1Str.begin(), result1Str.end());
				const wchar_t* result1 = wide_string.c_str();

				SetWindowText(hOut1, result1);

				string result2Str("Country: " + country);

				wstring wide_string1 = wstring(result2Str.begin(), result2Str.end());
				const wchar_t* result2 = wide_string1.c_str();

				SetWindowText(hOut2, result2);

				string result3Str("Units Sold: " + unitsSold);

				wstring wide_string2 = wstring(result3Str.begin(), result3Str.end());
				const wchar_t* result3 = wide_string2.c_str();

				SetWindowText(hOut3, result3);

				string result4Str("Unit Price: " + unitPrice);

				wstring wide_string3 = wstring(result4Str.begin(), result4Str.end());
				const wchar_t* result4 = wide_string3.c_str();

				SetWindowText(hOut4, result4);

				string result5Str("Unit Cost: " + unitCost);

				wstring wide_string4 = wstring(result5Str.begin(), result5Str.end());
				const wchar_t* result5 = wide_string4.c_str();

				SetWindowText(hOut5, result5);

				string result6Str("Total Revenue: " + totalRevenue);

				wstring wide_string5 = wstring(result6Str.begin(), result6Str.end());
				const wchar_t* result6 = wide_string5.c_str();

				SetWindowText(hOut6, result6);

				string result7Str("Total Cost: " + totalCost);

				wstring wide_string6 = wstring(result7Str.begin(), result7Str.end());
				const wchar_t* result7 = wide_string6.c_str();

				SetWindowText(hOut7, result7);

				string result8Str("Total Profit: " + totalProfit);

				wstring wide_string7 = wstring(result8Str.begin(), result8Str.end());
				const wchar_t* result8 = wide_string7.c_str();

				SetWindowText(hOut8, result8);

				break;
			}
		}



		break;
	case WM_CREATE:

		AddControls(hWnd);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProcW(hWnd, msg, wp, lp);
	}
}

void AddMenus(HWND hWnd) {
	hMenu = CreateMenu();
	HMENU hFileMenu = CreateMenu();
	HMENU hSubMenu = CreateMenu();

	AppendMenu(hSubMenu, MF_STRING, NULL, L"SubMenuItem");

	AppendMenu(hFileMenu, MF_STRING, FILE_MENU_NEW, L"New");
	AppendMenu(hFileMenu, MF_POPUP, (UINT_PTR)hSubMenu, L"Open SubMenu");
	AppendMenu(hFileMenu, MF_SEPARATOR, NULL, NULL);
	AppendMenu(hFileMenu, MF_STRING, FILE_MENU_EXIT, L"EXIT");

	AppendMenu(hMenu, MF_POPUP, (UINT_PTR)hFileMenu, L"File");
	AppendMenu(hMenu, MF_STRING, NULL, L"Help");

	SetMenu(hWnd, hMenu);
}

void AddControls(HWND hWnd) {
	CreateWindowW(L"static", L"Enter Order ID:", WS_VISIBLE | WS_CHILD, 200, 75, 100, 50, hWnd, NULL, NULL, NULL);
	CreateWindowW(L"static", L"SALES RECORDS DATABASE", WS_VISIBLE | WS_CHILD | SS_CENTER, 200, 15, 100, 50, hWnd, NULL, NULL, NULL);

	hID = CreateWindowW(L"edit", L"", WS_VISIBLE | WS_CHILD | SS_CENTER | WS_BORDER, 175, 97, 150, 25, hWnd, NULL, NULL, NULL);

	CreateWindowW(L"Button", L"Enter", WS_VISIBLE | WS_CHILD | WS_BORDER, 200, 134, 100, 50, hWnd, (HMENU)ENTER_BUTTON, NULL, NULL);

	hOut1 = CreateWindowW(L"edit", L"", WS_VISIBLE | WS_CHILD, 75, 200, 350, 25, hWnd, NULL, NULL, NULL);
	hOut2 = CreateWindowW(L"edit", L"", WS_VISIBLE | WS_CHILD, 75, 225, 350, 25, hWnd, NULL, NULL, NULL);
	hOut3 = CreateWindowW(L"edit", L"", WS_VISIBLE | WS_CHILD, 75, 250, 350, 25, hWnd, NULL, NULL, NULL);
	hOut4 = CreateWindowW(L"edit", L"", WS_VISIBLE | WS_CHILD, 75, 275, 350, 25, hWnd, NULL, NULL, NULL);
	hOut5 = CreateWindowW(L"edit", L"", WS_VISIBLE | WS_CHILD, 75, 300, 350, 25, hWnd, NULL, NULL, NULL);
	hOut6 = CreateWindowW(L"edit", L"", WS_VISIBLE | WS_CHILD, 75, 325, 350, 25, hWnd, NULL, NULL, NULL);
	hOut7 = CreateWindowW(L"edit", L"", WS_VISIBLE | WS_CHILD, 75, 350, 350, 25, hWnd, NULL, NULL, NULL);
	hOut8 = CreateWindowW(L"edit", L"", WS_VISIBLE | WS_CHILD, 75, 375, 350, 25, hWnd, NULL, NULL, NULL);
}
