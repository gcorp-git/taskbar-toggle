#pragma once

#include <windows.h>
#include <algorithm>
#include <string>
#include "status.cpp"

namespace Taskbar {
    class Shortcut {
    public:
        Shortcut(std::string shortcut) {
            this->_isCorrect = this->_parse(shortcut);
        }
        ~Shortcut() {
            //
        }
        bool isCorrect() {
            return this->_isCorrect;
        }
        bool isActive() {
            if (!this->_isCorrect) return false;

            bool is_alt = GetAsyncKeyState(VK_MENU) & 0x8000;
            bool is_ctrl = GetAsyncKeyState(VK_CONTROL) & 0x8000;
            bool is_meta = (GetAsyncKeyState(VK_LWIN) & 0x8000) || (GetAsyncKeyState(VK_RWIN) & 0x8000);
            bool is_shift = GetAsyncKeyState(VK_SHIFT) & 0x8000;

            if (this->_alt != is_alt) return false;
            if (this->_ctrl != is_ctrl) return false;
            if (this->_meta != is_meta) return false;
            if (this->_shift != is_shift) return false;

            bool is_code = GetAsyncKeyState(this->_code) & 0x8000;

            return is_code;
        }
    private:
        bool _isCorrect = false;
        bool _alt = false;
        bool _ctrl = false;
        bool _meta = false;
        bool _shift = false;
        int _code = 0;
        bool _parse(std::string shortcut) {
            std::string s = shortcut.c_str();
            std::string delimiter = "+";
            size_t pos = 0;

            std::transform(s.begin(), s.end(), s.begin(), ::toupper);

            while ((pos = s.find(delimiter)) != std::string::npos) {
                if (!this->_processToken(s.substr(0, pos))) return false;

                s.erase(0, pos + delimiter.length());
            }

            if (!this->_processToken(s)) return false;

            return this->_code != 0;
        }
        bool _processToken(std::string token) {
            if (token == "ALT") { this->_alt = true; return true; }
            if (token == "CTRL") { this->_ctrl = true; return true; }
            if (token == "META" || token == "SUPER" || token == "WIN") { this->_meta = true; return true; }
            if (token == "SHIFT") { this->_shift = true; return true; }

            if (this->_code != 0) return false;

            if (token == "LEFT") { this->_code = VK_LEFT; return true; }
            if (token == "UP") { this->_code = VK_UP; return true; }
            if (token == "RIGHT") { this->_code = VK_RIGHT; return true; }
            if (token == "DOWN") { this->_code = VK_DOWN; return true; }
            
            if (token == "INSERT") { this->_code = VK_INSERT; return true; }
            if (token == "HOME") { this->_code = VK_HOME; return true; }
            if (token == "END") { this->_code = VK_END; return true; }
            if (token == "PAGEUP") { this->_code = VK_PRIOR; return true; }
            if (token == "PAGEDOWN") { this->_code = VK_NEXT; return true; }
            if (token == "BACKSPACE") { this->_code = VK_BACK; return true; }
            if (token == "DELETE") { this->_code = VK_DELETE; return true; }
            if (token == "TAB") { this->_code = VK_TAB; return true; }
            if (token == "ENTER") { this->_code = VK_RETURN; return true; }
            if (token == "PAUSE") { this->_code = VK_PAUSE; return true; }
            if (token == "ESC" || token == "ESCAPE") { this->_code = VK_ESCAPE; return true; }
            if (token == "SPACE") { this->_code = VK_SPACE; return true; }

            if (token == "KEYPAD0" || token == "NUMPAD0") { this->_code = VK_NUMPAD0; return true; }
            if (token == "KEYPAD1" || token == "NUMPAD1") { this->_code = VK_NUMPAD1; return true; }
            if (token == "KEYPAD2" || token == "NUMPAD2") { this->_code = VK_NUMPAD2; return true; }
            if (token == "KEYPAD3" || token == "NUMPAD3") { this->_code = VK_NUMPAD3; return true; }
            if (token == "KEYPAD4" || token == "NUMPAD4") { this->_code = VK_NUMPAD4; return true; }
            if (token == "KEYPAD5" || token == "NUMPAD5") { this->_code = VK_NUMPAD5; return true; }
            if (token == "KEYPAD6" || token == "NUMPAD6") { this->_code = VK_NUMPAD6; return true; }
            if (token == "KEYPAD7" || token == "NUMPAD7") { this->_code = VK_NUMPAD7; return true; }
            if (token == "KEYPAD8" || token == "NUMPAD8") { this->_code = VK_NUMPAD8; return true; }
            if (token == "KEYPAD9" || token == "NUMPAD9") { this->_code = VK_NUMPAD9; return true; }

            if (token == "KEYPAD_DECIMAL" || token == "NUMPAD_DECIMAL" || token == "KEYPAD_PERIOD" || token == "NUMPAD_PERIOD") { this->_code = VK_DECIMAL; return true; }
            if (token == "KEYPAD_SEPARATOR" || token == "NUMPAD_SEPARATOR" || token == "KEYPAD_COMMA" || token == "NUMPAD_COMMA") { this->_code = VK_SEPARATOR; return true; }
            if (token == "KEYPAD_DIVIDE" || token == "NUMPAD_DIVIDE") { this->_code = VK_DIVIDE; return true; }
            if (token == "KEYPAD_MULTIPLY" || token == "NUMPAD_MULTIPLY") { this->_code = VK_MULTIPLY; return true; }
            if (token == "KEYPAD_SUBTRACT" || token == "NUMPAD_SUBTRACT" || token == "KEYPAD_MINUS" || token == "NUMPAD_MINUS") { this->_code = VK_SUBTRACT; return true; }
            if (token == "KEYPAD_ADD" || token == "NUMPAD_ADD" || token == "KEYPAD_PLUS" || token == "NUMPAD_PLUS") { this->_code = VK_ADD; return true; }
            if (token == "VK_CLEAR") { this->_code = VK_CLEAR; return true; }

            if (token == "F1") { this->_code = VK_F1; return true; }
            if (token == "F2") { this->_code = VK_F2; return true; }
            if (token == "F3") { this->_code = VK_F3; return true; }
            if (token == "F4") { this->_code = VK_F4; return true; }
            if (token == "F5") { this->_code = VK_F5; return true; }
            if (token == "F6") { this->_code = VK_F6; return true; }
            if (token == "F7") { this->_code = VK_F7; return true; }
            if (token == "F8") { this->_code = VK_F8; return true; }
            if (token == "F9") { this->_code = VK_F9; return true; }
            if (token == "F10") { this->_code = VK_F10; return true; }
            if (token == "F11") { this->_code = VK_F11; return true; }
            if (token == "F12") { this->_code = VK_F12; return true; }
            if (token == "F13") { this->_code = VK_F13; return true; }
            if (token == "F14") { this->_code = VK_F14; return true; }
            if (token == "F15") { this->_code = VK_F15; return true; }
            if (token == "F16") { this->_code = VK_F16; return true; }
            if (token == "F17") { this->_code = VK_F17; return true; }
            if (token == "F18") { this->_code = VK_F18; return true; }
            if (token == "F19") { this->_code = VK_F19; return true; }
            if (token == "F20") { this->_code = VK_F20; return true; }
            if (token == "F21") { this->_code = VK_F21; return true; }
            if (token == "F22") { this->_code = VK_F22; return true; }
            if (token == "F23") { this->_code = VK_F23; return true; }
            if (token == "F24") { this->_code = VK_F24; return true; }

            if (token == "0") { this->_code = '0'; return true; }
            if (token == "1") { this->_code = '1'; return true; }
            if (token == "2") { this->_code = '2'; return true; }
            if (token == "3") { this->_code = '3'; return true; }
            if (token == "4") { this->_code = '4'; return true; }
            if (token == "5") { this->_code = '5'; return true; }
            if (token == "6") { this->_code = '6'; return true; }
            if (token == "7") { this->_code = '7'; return true; }
            if (token == "8") { this->_code = '8'; return true; }
            if (token == "9") { this->_code = '9'; return true; }

            if (token == "A") { this->_code = 'A'; return true; }
            if (token == "B") { this->_code = 'B'; return true; }
            if (token == "C") { this->_code = 'C'; return true; }
            if (token == "D") { this->_code = 'D'; return true; }
            if (token == "E") { this->_code = 'E'; return true; }
            if (token == "F") { this->_code = 'F'; return true; }
            if (token == "G") { this->_code = 'G'; return true; }
            if (token == "H") { this->_code = 'H'; return true; }
            if (token == "I") { this->_code = 'I'; return true; }
            if (token == "J") { this->_code = 'J'; return true; }
            if (token == "K") { this->_code = 'K'; return true; }
            if (token == "L") { this->_code = 'L'; return true; }
            if (token == "M") { this->_code = 'M'; return true; }
            if (token == "N") { this->_code = 'N'; return true; }
            if (token == "O") { this->_code = 'O'; return true; }
            if (token == "P") { this->_code = 'P'; return true; }
            if (token == "Q") { this->_code = 'Q'; return true; }
            if (token == "R") { this->_code = 'R'; return true; }
            if (token == "S") { this->_code = 'S'; return true; }
            if (token == "T") { this->_code = 'T'; return true; }
            if (token == "U") { this->_code = 'U'; return true; }
            if (token == "V") { this->_code = 'V'; return true; }
            if (token == "W") { this->_code = 'W'; return true; }
            if (token == "X") { this->_code = 'X'; return true; }
            if (token == "Y") { this->_code = 'Y'; return true; }
            if (token == "Z") { this->_code = 'Z'; return true; }

            // todo: miscellaneous characters have special codes

            // if (token == ",") { this->_code = ','; return true; }
            // if (token == ".") { this->_code = '.'; return true; }
            // if (token == "\\") { this->_code = '\\'; return true; }
            // if (token == "/") { this->_code = '/'; return true; }
            // if (token == ";") { this->_code = ';'; return true; }
            // if (token == "'") { this->_code = '\''; return true; }
            // if (token == "`") { this->_code = '`'; return true; }
            // if (token == "+") { this->_code = '+'; return true; }
            // if (token == "-") { this->_code = '-'; return true; }
            // if (token == "=") { this->_code = '='; return true; }
            // if (token == "[") { this->_code = '['; return true; }
            // if (token == "]") { this->_code = ']'; return true; }

            return false;
        }
    };
}
