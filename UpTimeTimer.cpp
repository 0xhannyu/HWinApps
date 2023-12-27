#include <windows.h>
#include <shellapi.h>
#include <string>

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

std::string textToDisplay = "Ş̴͍̱̯̹̭͍̹̼̣̯͖̺̮͗͐̀͠G̸̼̯̜͖̏͑̾͆̏͝F̷͖̘̖̃͒̆ụ̴̺̠͈̰̃͐͑̀̍̚ḏ̸̢̥̯̙̔̌̈̑̚Q̴̛̛̪̥̣̤͈̠̎͋̅́͛͒̂=̶͕͖̙̠̥̗̭̱͈͊͋̐̍͆̑̐͗͗͐͊̒͌=̵͙̭̤͐̑̽̐̌̏̒̽̔͑̈́̈́̋͐̎̏͘";
UINT_PTR timerID = 0;
double i = 0;
const int ID_EXIT = 1001; 

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE, LPSTR, int nCmdShow) {
    WNDCLASSEX wc = {};
    wc.cbSize = sizeof(WNDCLASSEX);
    wc.style = CS_HREDRAW | CS_VREDRAW;
    wc.lpfnWndProc = WndProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = "SGFudQ==";
    RegisterClassEx(&wc);

    HWND hwnd = CreateWindowEx(
        WS_EX_LAYERED | WS_EX_TRANSPARENT,
        "SGFudQ==",
        "SGFudQ==",
        WS_POPUP,
        CW_USEDEFAULT, CW_USEDEFAULT,
        50, 20,
        nullptr, nullptr, hInstance, nullptr
    );

    // Transparency level
    SetLayeredWindowAttributes(hwnd, RGB(0, 0, 0), 255, LWA_ALPHA | LWA_COLORKEY);

    // Permanent position
    SetWindowPos(hwnd, HWND_TOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);

    ShowWindow(hwnd, SW_SHOWNOACTIVATE);

    NOTIFYICONDATA nid;
    nid.cbSize = sizeof(NOTIFYICONDATA);
    nid.hWnd = hwnd;
    nid.uID = 1;
    nid.uFlags = NIF_ICON | NIF_TIP;
    nid.hIcon = LoadIcon(NULL, IDI_APPLICATION);
    lstrcpyn(nid.szTip, "System Up Time", sizeof(nid.szTip));
    Shell_NotifyIcon(NIM_ADD, &nid);

    // Message loop with timer
    timerID = SetTimer(hwnd, 1, 1000, nullptr);

    MSG msg = {};
    while (GetMessage(&msg, nullptr, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    KillTimer(hwnd, timerID);

    return 0;
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {

    switch (msg) {
        case WM_DESTROY:
            PostQuitMessage(0);
            printf("close");
            break;

        case WM_TIMER: {
            i += 0.000001;
            textToDisplay = std::to_string(i);
            InvalidateRect(hwnd, NULL, true);
        } break;

        case WM_PAINT: {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hwnd, &ps);
            HFONT font = CreateFont(13, 0, 0, 0, FW_NORMAL, FALSE, FALSE, FALSE, ANSI_CHARSET,
                                 OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY,
                                 DEFAULT_PITCH | FF_DONTCARE, "Consolas");
            SelectObject(hdc, font);
            SetTextColor(hdc, RGB(0, 255, 0));
            SetBkColor(hdc, RGB(0,0,0));
            //SetBkMode(hdc, TRANSPARENT);
            TextOut(hdc, 0, 0, textToDisplay.c_str(), 8);
            DeleteObject(font);
            EndPaint(hwnd, &ps);
        } break;

        default:
            return DefWindowProc(hwnd, msg, wParam, lParam);
    }
    return 0;
}

//g++ uptimetimer.cpp -o "System Up Time" -lgdi32 -Wl,-subsystem,windows