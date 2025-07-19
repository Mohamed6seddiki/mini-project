#include <windows.h>
#include <stdlib.h>
#include <stdio.h>

#define ID_START 101
#define ID_EXIT 102
#define ID_CONVERT 103
#define ID_INPUT_NUMBER 106
#define ID_OUTPUT 107
#define ID_INPUT_SYSTEM 108
#define ID_TARGET_BASE 109

LRESULT CALLBACK MainWindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
LRESULT CALLBACK ConversionScreenProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

HINSTANCE g_hInstance;
HWND hMainWindow, hConversionWindow;

// debu
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
    g_hInstance = hInstance;

    WNDCLASS wc = {0};
    wc.lpfnWndProc = MainWindowProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = "BaseConverterMain";

    RegisterClass(&wc);

    hMainWindow = CreateWindowEx(
        0, "BaseConverterMain", "Base Converter - Main Menu",
        WS_OVERLAPPEDWINDOW | WS_VISIBLE,
        CW_USEDEFAULT, CW_USEDEFAULT, 700, 600,
        NULL, NULL, hInstance, NULL);

    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return 0;
}


LRESULT CALLBACK MainWindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    switch (uMsg) {
    case WM_CREATE:
        // Start buton
        CreateWindow("BUTTON", "Start",
                     WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
                     300, 200, 100, 40,
                     hwnd, (HMENU)ID_START, g_hInstance, NULL);

        // Exit buton
        CreateWindow("BUTTON", "Exit",
                     WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
                     300, 260, 100, 40,
                     hwnd, (HMENU)ID_EXIT, g_hInstance, NULL);
        break;

    case WM_COMMAND:
        switch (LOWORD(wParam)) {
        case ID_START:
            //  Conversion Screen ta3k
            {
                WNDCLASS wc = {0};
                wc.lpfnWndProc = ConversionScreenProc;
                wc.hInstance = g_hInstance;
                wc.lpszClassName = "BaseConverterConversion";

                RegisterClass(&wc);

                hConversionWindow = CreateWindowEx(
                    0, "BaseConverterConversion", "Base Converter - Conversion",
                    WS_OVERLAPPEDWINDOW | WS_VISIBLE,
                    CW_USEDEFAULT, CW_USEDEFAULT, 700, 600,
                    hwnd, NULL, g_hInstance, NULL);

                ShowWindow(hwnd, SW_HIDE);
            }
            break;

        case ID_EXIT:
            // Exit 
            PostQuitMessage(0);
            break;
        }
        break;

    case WM_DESTROY:
        PostQuitMessage(0);
        break;

    default:
        return DefWindowProc(hwnd, uMsg, wParam, lParam);
    }

    return 0;
}

// Conversion scren
LRESULT CALLBACK ConversionScreenProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    static HWND hInputNumber, hFromBase, hToBase, hOutput;

    switch (uMsg) {
    case WM_CREATE:
        // Number input
        CreateWindow("STATIC", "Enter Number:",
                     WS_CHILD | WS_VISIBLE,
                     50, 50, 100, 25,
                     hwnd, NULL, g_hInstance, NULL);

        hInputNumber = CreateWindow("EDIT", "",
                                    WS_CHILD | WS_VISIBLE | WS_BORDER,
                                    150, 50, 200, 25,
                                    hwnd, (HMENU)ID_INPUT_NUMBER, g_hInstance, NULL);

        // From Base 
        CreateWindow("STATIC", "From Base:",
                     WS_CHILD | WS_VISIBLE,
                     50, 100, 100, 25,
                     hwnd, NULL, g_hInstance, NULL);

        hFromBase = CreateWindow("COMBOBOX", "",
                                 WS_CHILD | WS_VISIBLE | CBS_DROPDOWNLIST,
                                 150, 100, 100, 100,
                                 hwnd, (HMENU)ID_INPUT_SYSTEM, g_hInstance, NULL);

        // base op
        SendMessage(hFromBase, CB_ADDSTRING, 0, (LPARAM)"2");
        SendMessage(hFromBase, CB_ADDSTRING, 0, (LPARAM)"8");
        SendMessage(hFromBase, CB_ADDSTRING, 0, (LPARAM)"10");
        SendMessage(hFromBase, CB_ADDSTRING, 0, (LPARAM)"16");
        SendMessage(hFromBase, CB_SETCURSEL, 2, 0); // Default to Base 10

        // To Base
        CreateWindow("STATIC", "To Base:",
                     WS_CHILD | WS_VISIBLE,
                     50, 150, 100, 25,
                     hwnd, NULL, g_hInstance, NULL);

        hToBase = CreateWindow("COMBOBOX", "",
                               WS_CHILD | WS_VISIBLE | CBS_DROPDOWNLIST,
                               150, 150, 100, 100,
                               hwnd, (HMENU)ID_TARGET_BASE, g_hInstance, NULL);

        // Add base options
        SendMessage(hToBase, CB_ADDSTRING, 0, (LPARAM)"2");
        SendMessage(hToBase, CB_ADDSTRING, 0, (LPARAM)"8");
        SendMessage(hToBase, CB_ADDSTRING, 0, (LPARAM)"10");
        SendMessage(hToBase, CB_ADDSTRING, 0, (LPARAM)"16");
        SendMessage(hToBase, CB_SETCURSEL, 0, 0); // Default to Base 2

        // Convert
        CreateWindow("BUTTON", "Convert",
                     WS_CHILD | WS_VISIBLE,
                     150, 200, 100, 30,
                     hwnd, (HMENU)ID_CONVERT, g_hInstance, NULL);

        // Result
        CreateWindow("STATIC", "Result:",
                     WS_CHILD | WS_VISIBLE,
                     50, 250, 100, 25,
                     hwnd, NULL, g_hInstance, NULL);

        hOutput = CreateWindow("EDIT", "",
                               WS_CHILD | WS_VISIBLE | WS_BORDER | ES_READONLY,
                               150, 250, 200, 25,
                               hwnd, (HMENU)ID_OUTPUT, g_hInstance, NULL);
        break;

    case WM_COMMAND:
        if (LOWORD(wParam) == ID_CONVERT) {
            char inputNumber[64], result[64] = "";
            int base, target, number;
            char* endptr;

            // number input
            GetWindowText(hInputNumber, inputNumber, sizeof(inputNumber));

            // Get the selected bases from the dropdowns
            base = SendMessage(hFromBase, CB_GETCURSEL, 0, 0);
            target = SendMessage(hToBase, CB_GETCURSEL, 0, 0);
            int bases[] = {2, 8, 10, 16};
            base = bases[base];
            target = bases[target];

            // from base  x to decimal
            number = strtol(inputNumber, &endptr, base);

            // Checker
            if (*endptr != '\0') {
                MessageBox(hwnd, "The number is invalid for the specified base!", "Error", MB_ICONERROR);
                break;
            }

            // decimal to the target base
            _itoa_s(number, result, sizeof(result), target);

            // result
            SetWindowText(hOutput, result);
        }
        break;

    case WM_DESTROY:
        ShowWindow(hMainWindow, SW_SHOW); // Return 
        DestroyWindow(hwnd);
        break;

    default:
        return DefWindowProc(hwnd, uMsg, wParam, lParam);
    }

    return 0;
}
