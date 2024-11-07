// ALPHA RUI.h V1.0

#ifndef RUI_H
#define RUI_H

#include <windows.h>
#include <vector>
#include <string>
#include <commctrl.h>

class RUIButton {
public:
    RUIButton(const std::string& text, int x, int y, int width, int height);
    ~RUIButton();

    HWND GetHandle() const;
    void SetText(const std::string& text);
    void SetBackgroundColor(COLORREF color);
    void SetTextColor(COLORREF color);
    void SetClickHandler(void (*handler)(RUIButton&));
    void SetIcon(HICON icon);
    void SetTooltip(const std::string& tooltipText);
    void SetFont(HFONT font);

private:
    HWND hButton;
    COLORREF bgColor;
    COLORREF textColor;
    HICON hIcon;
    HWND hTooltip;
    HFONT hFont;
    void (*clickHandler)(RUIButton&);
    void InitTooltip(const std::string& tooltipText);
};

class RUILabel {
public:
    RUILabel(const std::string& text, int x, int y);
    ~RUILabel();

    HWND GetHandle() const;
    void SetText(const std::string& text);
    void SetFont(HFONT font);

private:
    HWND hLabel;
    HFONT hFont;
};

class RUITextBox {
public:
    RUITextBox(int x, int y, int width, int height);
    ~RUITextBox();

    HWND GetHandle() const;
    std::string GetText() const;
    void SetText(const std::string& text);
    void SetFont(HFONT font);

private:
    HWND hTextBox;
    HFONT hFont;
};

class RUI {
public:
    RUI(HINSTANCE hInstance, int nCmdShow);
    ~RUI();

    void CreateMainWindow(const std::string& windowName, int width, int height);
    RUIButton& CreateButton(const std::string& text, int x, int y, int width, int height);
    RUILabel& CreateLabel(const std::string& text, int x, int y);
    RUITextBox& CreateTextBox(int x, int y, int width, int height);
    void ShowMainWindow();
    void RunMessageLoop();

private:
    HINSTANCE hInstance;
    HWND hMainWnd;
    std::vector<RUIButton> buttons;
    std::vector<RUILabel> labels;
    std::vector<RUITextBox> textboxes;
    HFONT hFont;

    static LRESULT CALLBACK MainWndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
    void RegisterWindowClass();
    void HandleButtonClick(WPARAM wParam);
    HFONT LoadFontFromPath(const std::string& fontPath);
};

#endif
