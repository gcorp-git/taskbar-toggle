#pragma once

#include <windows.h>

namespace Taskbar {
    class Taskbar {
    public:
        Taskbar() {
            this->_hwnd = FindWindow(TEXT("Shell_traywnd"), NULL);
            this->_hwnd2 = FindWindow(TEXT("Shell_SecondaryTrayWnd"), NULL);
            this->_isVisible = _isReallyVisible();
        }
        ~Taskbar() {
            //
        }
        bool isVisible() {
            return this->_isVisible;
        }
        void show() {
            if (this->isVisible()) return;

            this->_show();

            this->_isVisible = true;
        }
        void hide() {
            if (!this->isVisible()) return;

            this->_hide();

            this->_isVisible = false;
        }
        void toggle() {
            if (this->isVisible()) {
                this->hide();
            } else {
                this->show();
            }
        }
        void refresh() {
            if (this->isVisible()) {
                if (!this->_isReallyVisible()) this->_show();
            } else {
                if (this->_isReallyVisible()) this->_hide();
            }
        }
    private:
        HWND _hwnd = NULL;
        HWND _hwnd2 = NULL;
        bool _isVisible = false;
        bool _isReallyVisible() {
            return IsWindowVisible(this->_hwnd);
        }
        void _show() {
            ShowWindow(this->_hwnd, 1);
            ShowWindow(this->_hwnd2, 1);
        }
        void _hide() {
            ShowWindow(this->_hwnd, 0);
            ShowWindow(this->_hwnd2, 0);
        }
    };
}
