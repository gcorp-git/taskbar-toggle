#pragma once

#include "settings.cpp"
#include "shortcut.cpp"
#include "taskbar.cpp"

namespace Taskbar {
    class App {
    public:
        App() {
            this->_settings = this->_createSettings(".\\settings.ini");
            if (this->hasError()) return;

            this->_shortcutExit = this->_createShortcut("exit");
            if (this->hasError()) return;

            this->_shortcutToggle = this->_createShortcut("toggle");
            if (this->hasError()) return;

            this->_taskbar = new Taskbar();
        }
        ~App() {
            delete this->_settings;
            delete this->_shortcutExit;
            delete this->_shortcutToggle;
            delete this->_taskbar;
        }
        bool hasError() {
            return this->_status.error;
        }
        const Status getStatus() {
            return this->_status;
        }
        bool isStarted() {
            return this->_isStarted;
        }
        void start() {
            if (this->isStarted()) return;
            if (this->hasError()) return;

            this->_isStarted = true;

            MSG msg;

            while (this->isStarted()) {
                if (PeekMessage(&msg, NULL, 0, 0, PM_NOREMOVE)) {
                    if (GetMessage(&msg, NULL, 0, 0) < 0) {
                        return this->stop(Status(true, "System error"));
                    }

                    TranslateMessage(&msg);
                    DispatchMessage(&msg);
                }

                if (!this->isStarted()) break;
                
                this->_onFrame();
            }
        }
        void stop(const Status status={}) {
            if (!this->isStarted()) return;

            this->_isStarted = false;
            this->_status = status;
        }
    private:
        bool _isStarted = false;
        Status _status = {};
        Settings* _settings = nullptr;
        Shortcut* _shortcutExit = nullptr;
        Shortcut* _shortcutToggle = nullptr;
        Taskbar* _taskbar = nullptr;
        Settings* _createSettings(std::string path) {
            auto settings = new Settings(path);

            if (settings->hasError()) {
                this->_status = settings->getStatus();
            }

            return settings;
        }
        Shortcut* _createShortcut(std::string name) {
            auto shortcut_ = this->_settings->get("shortcuts", name);
            auto shortcut = new Shortcut(shortcut_);

            if (!shortcut->isCorrect()) {
                this->_status = Status(true, "Incorrect shortcut: " + name + " ('" + shortcut_ + "')");
            }

            return shortcut;
        }
        void _onFrame() {
            if (this->_shortcutExit->isActive()) return this->stop();

            if (this->_shortcutToggle->isActive()) {
                this->_taskbar->toggle();
                Sleep(300);
                return;
            }

            this->_taskbar->refresh();

            Sleep(16);
        }
    };
}
