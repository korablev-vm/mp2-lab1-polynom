#pragma comment(linker,"\"/manifestdependency:type='win32' \
name='Microsoft.Windows.Common-Controls' version='6.0.0.0' \
processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")

#include <Windows.h>
#include <memory>
#include <string>
#include "RBTree.h"
#include "ChainingHashTable.h"
#include "LinearArrayTable.h"
#include "LinkedListTable.h"
#include "RehashingHashTable.h"
#include "Polinom.h"
#include "SortedArrayTable.h"
#include "TableManager.h"
#include "postfix.h"

static int cPosY = 0;
static int cMaxY = 0;
Polinom new_polinom;
TPostfix<double, std::string>* postfix;
HFONT hFont = CreateFont(16, 0, 0, 0, FW_BOLD, FALSE, FALSE, FALSE, DEFAULT_CHARSET, OUT_OUTLINE_PRECIS,
	CLIP_DEFAULT_PRECIS, CLEARTYPE_QUALITY, VARIABLE_PITCH, "Arial");

bool checkOfKey(std::string str)
{
	if (str == "")
		return false;
	if (!((str.find_first_not_of("0123456789,") == std::string::npos)
		|| ((str.find_first_of("0123456789") > str.find_last_not_of("0123456789"))
			&& (str.find_first_of(".,<>?/|!@#$&={}[]:;\"'") == std::string::npos))))
		return false;
	return true;
}

static std::pair<bool, HWND> AddWindow(const std::string&& winClass, const std::string&& title, HWND hParentWnd, const WNDPROC callback)
{

	UnregisterClass(winClass.c_str(), GetModuleHandle(nullptr));

	WNDCLASSEX wc{ sizeof(WNDCLASSEX) };
	HWND hWindow{};
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hbrBackground = reinterpret_cast<HBRUSH>(GetStockObject(WHITE_BRUSH));
	wc.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wc.hIcon = LoadIcon(nullptr, IDI_APPLICATION);
	wc.hIconSm = LoadIcon(nullptr, IDI_APPLICATION);
	wc.lpfnWndProc = callback;
	wc.lpszClassName = winClass.c_str();
	wc.style = CS_VREDRAW | CS_HREDRAW;
	static RECT rc{};
	GetWindowRect(hParentWnd, &rc);

	const auto create_window = [&hWindow, &winClass, &title, &hParentWnd]() -> std::pair<bool, HWND>
	{

		hWindow = CreateWindow(winClass.c_str(), title.c_str(), WS_OVERLAPPEDWINDOW | WS_VSCROLL, rc.right, rc.top, 470, 150,
			hParentWnd, nullptr, nullptr, nullptr);
		if (!hWindow) return { false, nullptr };
		ShowWindow(hWindow, SW_SHOWDEFAULT);
		UpdateWindow(hWindow);
		return { true, hWindow };
	};

	if (!RegisterClassEx(&wc))
		return create_window();

	return create_window();
}

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE, PWSTR szCmdLine, int nCmdShow)
{
	WNDCLASSEX wc = { sizeof(WNDCLASSEX) };
	MSG msg{ 0 };
	static HWND hwnd{}, hChildWnd{};
	static std::pair<bool, HWND> hChild;
	static HWND button1{}, button2{};
	static HWND textBox1{}, textBox2{};

	static TableManager<std::string, Polinom> manager;

	auto unorderedTable = std::make_shared<TUnorderedTable<std::string, Polinom>>();
	auto sortedTable = std::make_shared<TSortedTable<std::string, Polinom>>();
	auto rehashingHashTable = std::make_shared<RehashingHashTable<std::string, Polinom>>();
	auto chainingHashTable = std::make_shared<ChainingHashTable<std::string, Polinom>>();
	auto linkedListTable = std::make_shared<TLinearListTable<std::string, Polinom>>();
	auto rbTreeTable = std::make_shared<RedBlackTree<std::string, Polinom>>();



	// Добавление таблиц в менеджер
	manager.addTable(unorderedTable);
	manager.addTable(sortedTable);
	manager.addTable(rehashingHashTable);
	manager.addTable(chainingHashTable);
	manager.addTable(linkedListTable);
	manager.addTable(rbTreeTable);


	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hbrBackground = reinterpret_cast<HBRUSH>(GetStockObject(WHITE_BRUSH));
	wc.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wc.hIcon = LoadIcon(nullptr, IDI_APPLICATION);
	wc.hIconSm = LoadIcon(nullptr, IDI_APPLICATION);
	wc.hInstance = hInstance;
	wc.lpfnWndProc = [](HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)->LRESULT
	{
		PAINTSTRUCT ps;
		HDC hdc;
		switch (uMsg)
		{
		case WM_CREATE:
		{
			std::string helloStr = "Hello!\nThis is a polynomial calculator, that provides the following options:\n - adding a polynom to the table;\n - removing a polynom from the table;\n - calculating an expression from polynoms and\n\t - calculating it at a point,\n\t - saving it as a new polynom;\n - selecting the active table (initially, it is an Unsorted Table).";
			MessageBox(hWnd, helloStr.c_str(), "Info", MB_ICONINFORMATION);
			HMENU hMenu = CreateMenu();
			AppendMenu(hMenu, MF_STRING, 1001, "Add");
			AppendMenu(hMenu, MF_STRING, 1002, "Delete");
			AppendMenu(hMenu, MF_STRING, 1003, "Count an expression");
			AppendMenu(hMenu, MF_STRING, 1004, "Change active table");
			SetMenu(hWnd, hMenu);

			SetScrollRange(hWnd, SB_VERT, 0, cMaxY, TRUE);
			SetScrollPos(hWnd, SB_VERT, cPosY, TRUE);
		}
		return 0;

		case WM_SIZE:
		{
			RECT rc{};
			GetClientRect(hWnd, &rc);
		}
		return 0;

		case WM_VSCROLL:
		{
			int nScrollCode = LOWORD(wParam);
			int nPos = HIWORD(wParam);
			switch (nScrollCode)
			{
			case SB_TOP:
				cPosY = 0;
				break;
			case SB_BOTTOM:
				cPosY = cMaxY;
				break;
			case SB_LINEUP:
				cPosY--;
				break;
			case SB_LINEDOWN:
				cPosY++;
				break;
			case SB_PAGEUP:
				cPosY -= 10;
				break;
			case SB_PAGEDOWN:
				cPosY += 10;
				break;
			case SB_THUMBTRACK:
				cPosY = nPos;
				break;
			}

			if (cPosY < 0)
				cPosY = 0;
			else if (cPosY > cMaxY)
				cPosY = cMaxY;

			SetScrollPos(hWnd, SB_VERT, cPosY, TRUE);
			InvalidateRect(hWnd, NULL, TRUE);
		}
		return 0;

		case WM_PAINT:
		{
			hdc = BeginPaint(hWnd, &ps);
			SelectObject(hdc, hFont);
			manager.display(hdc, cPosY);
			EndPaint(hWnd, &ps);
		}
		return 0;

		case WM_COMMAND:
		{
			switch (LOWORD(wParam))
			{
			case 1001:
			{
				if (hChildWnd) DestroyWindow(hChildWnd);
				hChild = AddWindow("AddWindowClass", "Add", hWnd, [](HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)->LRESULT
					{
						RECT rc{};
						PAINTSTRUCT childPs;
						HDC childHdc;
						switch (uMsg)
						{
						case WM_CREATE:
						{
							GetClientRect(hWnd, &rc);
							textBox1 = CreateWindow("EDIT", "", WS_CHILD | WS_VISIBLE | WS_BORDER, rc.left + 55, rc.top + 20, rc.right - 65,
								20, hWnd, reinterpret_cast<HMENU>(1212), nullptr, nullptr);
							textBox2 = CreateWindow("EDIT", "", WS_CHILD | WS_VISIBLE | WS_BORDER, rc.left + 55, rc.top + 60, rc.right - 65,
								20, hWnd, reinterpret_cast<HMENU>(1221), nullptr, nullptr);
							button1 = CreateWindow("BUTTON", "Ok", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, rc.right - 50, rc.bottom - 25, 40,
								20, hWnd, reinterpret_cast<HMENU>(1337), nullptr, nullptr);
						}
						return 0;
						case WM_PAINT:
						{
							GetClientRect(hWnd, &rc);
							childHdc = BeginPaint(hWnd, &childPs);
							SelectObject(childHdc, hFont);
							TextOut(childHdc, rc.left + 5, rc.top + 20, "Key:", 5);
							TextOut(childHdc, rc.left + 5, rc.top + 60, "Value:", 7);
							EndPaint(hWnd, &childPs);
						}
						return 0;
						case WM_SIZE:
						{
							GetClientRect(hWnd, &rc);
							SetWindowPos(textBox1, nullptr, rc.left + 55, rc.top + 20, rc.right - 65, 20,
								SWP_NOMOVE | SWP_NOZORDER | SWP_NOOWNERZORDER);
							SetWindowPos(textBox2, nullptr, rc.left + 55, rc.top + 60, rc.right - 65, 20,
								SWP_NOMOVE | SWP_NOZORDER | SWP_NOOWNERZORDER);
							SetWindowPos(button1, nullptr, rc.right - 50, rc.bottom - 25, 40, 20,
								SWP_NOZORDER | SWP_NOOWNERZORDER);
						}
						return 0;
						case WM_COMMAND:
						{
							switch (LOWORD(wParam))
							{
							case 1337:
								CHAR text1[255] = { 0 }, text2[255] = { 0 };
								GetWindowText(textBox1, text1, 255);
								GetWindowText(textBox2, text2, 255);
								if (checkOfKey(text1))
									manager.addAll(TRecord<std::string, Polinom>{text1, Polinom(text2)});
								else
									MessageBox(hWnd, "Key is wrong", "Error", MB_ICONINFORMATION);

								cMaxY += 20;
								SetScrollRange(hWnd, SB_VERT, 0, cMaxY, TRUE);
								RedrawWindow(hwnd, nullptr, nullptr, true);
								DestroyWindow(hWnd);
							}
							return 0;
						}
						return 0;
						case WM_DESTROY:
						{
							DestroyWindow(hWnd);
						}
						return 0;
						}
						return DefWindowProc(hWnd, uMsg, wParam, lParam);
					});
				hChildWnd = hChild.second;
			};
			return 0;
			case 1002:
			{
				if (hChildWnd) DestroyWindow(hChildWnd);
				hChild = AddWindow("DeleteWindowClass", "Delete", hWnd, [](HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)->LRESULT
					{
						RECT rc{};
						PAINTSTRUCT childPs;
						HDC childHdc;
						switch (uMsg)
						{
						case WM_CREATE:
						{
							GetClientRect(hWnd, &rc);
							textBox1 = CreateWindow("EDIT", "", WS_CHILD | WS_VISIBLE | WS_BORDER, rc.left + 55, (rc.bottom - 30) / 2 - 10,
								rc.right - 65, 20, hWnd, reinterpret_cast<HMENU>(1212), nullptr, nullptr);
							button1 = CreateWindow("BUTTON", "Ok", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, rc.right - 50, rc.bottom - 25,
								40, 20, hWnd, reinterpret_cast<HMENU>(1337), nullptr, nullptr);

						}
						return 0;
						case WM_PAINT:
						{
							GetClientRect(hWnd, &rc);
							childHdc = BeginPaint(hWnd, &childPs);
							SelectObject(childHdc, hFont);
							TextOut(childHdc, rc.left + 5, (rc.bottom - 30) / 2 - 10, "Key:", 5);
							EndPaint(hWnd, &childPs);
						}
						return 0;
						case WM_SIZE:
						{
							GetClientRect(hWnd, &rc);
							SetWindowPos(textBox1, nullptr, rc.left + 55, (rc.bottom - 30) / 2 - 10, rc.right - 65, 20,
								SWP_NOZORDER | SWP_NOOWNERZORDER);
							SetWindowPos(button1, nullptr, rc.right - 50, rc.bottom - 25, 40, 20, SWP_NOZORDER | SWP_NOOWNERZORDER);
						}
						return 0;
						case WM_COMMAND:
						{
							switch (LOWORD(wParam))
							{
							case 1337:
								CHAR text1[255] = { 0 }, text2[255] = { 0 };
								GetWindowText(textBox1, text1, 255);
								manager.removeAll(text1);

								RedrawWindow(hwnd, nullptr, nullptr, true);
								DestroyWindow(hWnd);
							}
							return 0;
						}
						return 0;
						case WM_DESTROY:
						{
							DestroyWindow(hWnd);
						}
						return 0;
						}
						return DefWindowProc(hWnd, uMsg, wParam, lParam);
					});
				hChildWnd = hChild.second;
			};
			return 0;
			case 1003:
			{
				if (hChildWnd) DestroyWindow(hChildWnd);
				hChild = AddWindow("CalculateWindowClass", "Count an expression", hWnd, [](HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)->LRESULT
					{
						RECT rc{};
						PAINTSTRUCT childPs;
						HDC childHdc;
						switch (uMsg)
						{
						case WM_CREATE:
						{
							MessageBox(hWnd, "Available operations:\n\"+\" - addition\n\"-\" - subtraction\n\"*\" - multiplication\n\"Diff(x,y)\" - differentiation x by y\n\"Integr(x,y)\" - integration x by y\n", "Info", MB_ICONINFORMATION);
							GetClientRect(hWnd, &rc);
							textBox1 = CreateWindow("EDIT", "", WS_CHILD | WS_VISIBLE | WS_BORDER, rc.left + 85, (rc.bottom - 30) / 2 - 10,
								rc.right - 95, 20, hWnd, reinterpret_cast<HMENU>(1212), nullptr, nullptr);
							button1 = CreateWindow("BUTTON", "Calculate at a point", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, rc.right - 145,
								rc.bottom - 25, 135, 20, hWnd, reinterpret_cast<HMENU>(1337), nullptr, nullptr);
							button2 = CreateWindow("BUTTON", "Save as new polinom", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, rc.right - 300,
								rc.bottom - 25, 145, 20, hWnd, reinterpret_cast<HMENU>(1373), nullptr, nullptr);

						}
						return 0;
						case WM_PAINT:
						{
							GetClientRect(hWnd, &rc);
							childHdc = BeginPaint(hWnd, &childPs);
							SelectObject(childHdc, hFont);
							TextOut(childHdc, rc.left + 5, (rc.bottom - 30) / 2 - 10, "Expression: ", 14);
							EndPaint(hWnd, &childPs);
						}
						return 0;
						case WM_SIZE:
						{
							GetClientRect(hWnd, &rc);
							SetWindowPos(textBox1, nullptr, rc.left + 85, (rc.bottom - 30) / 2 - 10, rc.right - 95, 20,
								SWP_NOZORDER | SWP_NOOWNERZORDER);
							SetWindowPos(button1, nullptr, rc.right - 145, rc.bottom - 25, 135, 20, SWP_NOZORDER | SWP_NOOWNERZORDER);
							SetWindowPos(button2, nullptr, rc.right - 300, rc.bottom - 25, 145, 20, SWP_NOZORDER | SWP_NOOWNERZORDER);
						}
						return 0;
						case WM_COMMAND:
						{
							switch (LOWORD(wParam))
							{
							case 1337:
							{
								CHAR text1[255] = { 0 }, text2[255] = { 0 };
								GetWindowText(textBox1, text1, 255);
								std::string val = text1;

								try
								{
									postfix = new TPostfix<double, std::string>(val, manager);
								}
								catch (std::string ex)
								{
									MessageBox(hWnd, ex.c_str(), "Error", MB_ICONINFORMATION);
								}
								ShowWindow(hWnd, 0);


								std::pair<bool, HWND> newHChild;
								newHChild = AddWindow("AddWindowClass", "Add", hwnd, [](HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)->LRESULT
									{
										std::vector<std::string> variables = new_polinom.GetAllVariables();
										static HWND edits[50];
										RECT rc{};
										PAINTSTRUCT childPs;
										HDC childHdc;
										int posY = 0;
										int maxY = 30 * variables.size() + 50;
										switch (uMsg)
										{
										case WM_CREATE:
										{
											GetClientRect(hWnd, &rc);
											HMENU hMenu = CreateMenu();
											AppendMenu(hMenu, MF_STRING, 4004, "Ok");
											SetMenu(hWnd, hMenu);

											SetScrollRange(hWnd, SB_VERT, 0, maxY, TRUE);
											SetScrollPos(hWnd, SB_VERT, posY, TRUE);

											for (int i = 0; i < variables.size(); i++)
											{
												edits[i] = CreateWindow("EDIT", "", WS_CHILD | WS_VISIBLE | WS_BORDER, rc.left + 55,
													rc.top + 30 * (i + 1) - posY, rc.right - 65, 20, hWnd, reinterpret_cast<HMENU>(1200 + i),
													nullptr, nullptr);
											}
										}
										return 0;
										case WM_PAINT:
										{
											GetClientRect(hWnd, &rc);
											childHdc = BeginPaint(hWnd, &childPs);
											for (int i = 0; i < variables.size(); i++)
												TextOut(childHdc, rc.left + 5, rc.top + rc.top + 30 * (i + 1) - posY,
													variables[i].c_str(), 20);
											EndPaint(hWnd, &childPs);
										}
										return 0;
										case WM_SIZE:
										{
											GetClientRect(hWnd, &rc);
											for (int i = 0; i < variables.size(); i++)
												SetWindowPos(textBox1, nullptr, rc.left + 55, rc.top + 30 * (i + 1) - posY, rc.right - 65,
													20, SWP_NOZORDER | SWP_NOOWNERZORDER);
										}
										return 0;
										case WM_VSCROLL:
										{
											int nScrollCode = LOWORD(wParam);
											int nPos = HIWORD(wParam);
											switch (nScrollCode)
											{
											case SB_TOP:
												posY = 0;
												break;
											case SB_BOTTOM:
												posY = maxY;
												break;
											case SB_LINEUP:
												posY--;
												break;
											case SB_LINEDOWN:
												posY++;
												break;
											case SB_PAGEUP:
												posY -= 10;
												break;
											case SB_PAGEDOWN:
												posY += 10;
												break;
											case SB_THUMBTRACK:
												posY = nPos;
												break;
											}

											if (posY < 0)
												posY = 0;
											else if (posY > maxY)
												posY = maxY;

											SetScrollPos(hWnd, SB_VERT, posY, TRUE);
											InvalidateRect(hWnd, NULL, TRUE);
										}
										return 0;
										case WM_COMMAND:
										{
											switch (LOWORD(wParam))
											{
											case 4004:
												std::vector<double> values;
												char text1[255];
												for (int i = 0; i < variables.size(); i++)
												{
													GetWindowText(edits[i], text1, 255);
													values.push_back(std::atof(text1));
												}
												std::string res = "Value in this point: " + std::to_string(postfix->Calculate(values));
												MessageBox(hWnd, res.c_str(), "Result", MB_ICONINFORMATION);
												DestroyWindow(hWnd);
											}
											return 0;
										}
										return 0;
										case WM_DESTROY:
										{
											DestroyWindow(hWnd);
										}
										return 0;
										}
										return DefWindowProc(hWnd, uMsg, wParam, lParam);
									});
								HWND newHChildWnd = hChild.second;
							}
							return 0;
							case 1373:
							{
								CHAR text1[255] = { 0 }, text2[255] = { 0 };
								GetWindowText(textBox1, text1, 255);
								std::string val = text1;

								try
								{
									TPostfix<double, std::string> postfix(val, manager);
									new_polinom = postfix.CreateNewPolinom();
								}
								catch (std::string ex)
								{
									MessageBox(hWnd, ex.c_str(), "Error", MB_ICONINFORMATION);
								}

								ShowWindow(hWnd, 0);


								std::pair<bool, HWND> newHChild;
								newHChild = AddWindow("AddWindowClass", "Add", hwnd, [](HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)->LRESULT
									{
										RECT rc{};
										PAINTSTRUCT childPs;
										HDC childHdc;
										switch (uMsg)
										{
										case WM_CREATE:
										{
											GetClientRect(hWnd, &rc);
											textBox1 = CreateWindow("EDIT", "", WS_CHILD | WS_VISIBLE | WS_BORDER, rc.left + 55, rc.top + 20,
												rc.right - 65, 20, hWnd, reinterpret_cast<HMENU>(1212), nullptr, nullptr);
											textBox2 = CreateWindow("EDIT", "", WS_CHILD | WS_VISIBLE | WS_BORDER, rc.left + 55, rc.top + 60,
												rc.right - 65, 20, hWnd, reinterpret_cast<HMENU>(1221), nullptr, nullptr);
											button1 = CreateWindow("BUTTON", "Ok", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, rc.right - 50,
												rc.bottom - 25, 40, 20, hWnd, reinterpret_cast<HMENU>(1337), nullptr, nullptr);
											SetWindowText(textBox2, new_polinom.ToString().c_str());

										}
										return 0;
										case WM_PAINT:
										{
											GetClientRect(hWnd, &rc);
											childHdc = BeginPaint(hWnd, &childPs);
											SelectObject(childHdc, hFont);
											TextOut(childHdc, rc.left + 5, rc.top + 20, "Key:", 5);
											TextOut(childHdc, rc.left + 5, rc.top + 60, "Value:", 7);
											EndPaint(hWnd, &childPs);
										}
										return 0;
										case WM_SIZE:
										{
											GetClientRect(hWnd, &rc);
											SetWindowPos(textBox1, nullptr, rc.left + 55, rc.top + 20, rc.right - 65, 20,
												SWP_NOMOVE | SWP_NOZORDER | SWP_NOOWNERZORDER);
											SetWindowPos(textBox2, nullptr, rc.left + 55, rc.top + 60, rc.right - 65, 20,
												SWP_NOMOVE | SWP_NOZORDER | SWP_NOOWNERZORDER);
											SetWindowPos(button1, nullptr, rc.right - 50, rc.bottom - 25, 40, 20,
												SWP_NOZORDER | SWP_NOOWNERZORDER);
										}
										return 0;
										case WM_COMMAND:
										{
											switch (LOWORD(wParam))
											{
											case 1337:
												CHAR text1[255] = { 0 };
												GetWindowText(textBox1, text1, 255);
												if (checkOfKey(text1))
													manager.addAll(TRecord<std::string, Polinom>{text1, new_polinom});
												else
													MessageBox(hWnd, "Key is wrong", "Error", MB_ICONINFORMATION);

												cMaxY += 20;
												SetScrollRange(hWnd, SB_VERT, 0, cMaxY, TRUE);
												RedrawWindow(hwnd, nullptr, nullptr, true);
												DestroyWindow(hWnd);
											}
											return 0;
										}
										return 0;
										case WM_DESTROY:
										{
											DestroyWindow(hWnd);
										}
										return 0;
										}
										return DefWindowProc(hWnd, uMsg, wParam, lParam);
									});
								HWND newHChildWnd = hChild.second;
								DestroyWindow(hWnd);
								DestroyWindow(newHChildWnd);
							}
							return 0;
							}
						}
						return 0;
						case WM_DESTROY:
						{
							DestroyWindow(hWnd);
						}
						return 0;
						}
						ShowWindow(hwnd, 1);
						return DefWindowProc(hWnd, uMsg, wParam, lParam);
					});
				hChildWnd = hChild.second;
			};
			return 0;
			case 1004:
			{
				if (hChildWnd) DestroyWindow(hChildWnd);
				hChild = AddWindow("AddWindowClass", "Add", hWnd, [](HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)->LRESULT
					{
						RECT rc{};
						PAINTSTRUCT childPs;
						HDC childHdc;
						static HWND hButton[6];
						switch (uMsg)
						{
						case WM_CREATE:
						{
							GetClientRect(hWnd, &rc);
							hButton[0] = CreateWindow("BUTTON", "Unordered Table", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, rc.left + 5,
								rc.top + 25, 140, 20, hWnd, reinterpret_cast<HMENU>(1301), nullptr, nullptr);
							hButton[0] = CreateWindow("BUTTON", "Sorted Table", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, rc.left + 5,
								rc.bottom - 45, 140, 20, hWnd, reinterpret_cast<HMENU>(1302), nullptr, nullptr);
							hButton[0] = CreateWindow("BUTTON", "Rehashing Table", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, rc.right - 145,
								rc.top + 25, 140, 20, hWnd, reinterpret_cast<HMENU>(1303), nullptr, nullptr);
							hButton[0] = CreateWindow("BUTTON", "Chaining Hash Table", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, rc.right - 145,
								rc.bottom - 45, 140, 20, hWnd, reinterpret_cast<HMENU>(1304), nullptr, nullptr);
							hButton[0] = CreateWindow("BUTTON", "Linked List Table", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, rc.right / 2 - 70,
								rc.top + 25, 140, 20, hWnd, reinterpret_cast<HMENU>(1305), nullptr, nullptr);
							hButton[0] = CreateWindow("BUTTON", "RedBlack Tree Table", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, rc.right / 2 - 70,
								rc.bottom - 45, 140, 20, hWnd, reinterpret_cast<HMENU>(1306), nullptr, nullptr);
						}
						return 0;
						case WM_COMMAND:
						{
							switch (LOWORD(wParam))
							{
							case 1301:
							{
								manager.setActiveTable(0);
								DestroyWindow(hWnd);
							}
							return 0;
							case 1302:
							{
								manager.setActiveTable(1);
								DestroyWindow(hWnd);
							}
							return 0;
							case 1303:
							{
								manager.setActiveTable(2);
								DestroyWindow(hWnd);
							}
							return 0;
							case 1304:
							{
								manager.setActiveTable(3);
								DestroyWindow(hWnd);
							}
							return 0;
							case 1305:
							{
								manager.setActiveTable(4);
								DestroyWindow(hWnd);
							}
							return 0;
							case 1306:
							{
								manager.setActiveTable(5);
								DestroyWindow(hWnd);
							}
							return 0;
							}
							return 0;
						}
						return 0;
						case WM_DESTROY:
						{
							DestroyWindow(hWnd);
						}
						return 0;
						}
						return DefWindowProc(hWnd, uMsg, wParam, lParam);
					});
				hChildWnd = hChild.second;
			};
			return 0;
			}
		}
		return 0;

		case WM_DESTROY:
		{
			PostQuitMessage(0);
		}
		return 0;
		}
		return DefWindowProc(hWnd, uMsg, wParam, lParam);
	};
	wc.lpszClassName = "MainWindow";
	wc.style = CS_VREDRAW | CS_HREDRAW;

	if (!RegisterClassEx(&wc))
		return EXIT_FAILURE;

	hwnd = CreateWindow(wc.lpszClassName, "Polynomial Calculator", WS_VISIBLE | WS_OVERLAPPEDWINDOW | WS_VSCROLL, 380, 200, 500, 400,
		nullptr, nullptr, wc.hInstance, nullptr);
	if (hwnd == INVALID_HANDLE_VALUE)
		return EXIT_FAILURE;

	ShowWindow(hwnd, nCmdShow);
	UpdateWindow(hwnd);

	while (GetMessage(&msg, nullptr, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return static_cast<int>(msg.wParam);
};


