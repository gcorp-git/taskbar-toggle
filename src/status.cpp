#pragma once

#include <string>

namespace Taskbar {
    struct Status {
        bool error = false;
        std::string message = "";
        Status(bool error=false, std::string message="") {
            this->error = error;
            this->message = message;
        }
        void setOk(std::string message="") {
            this->error = false;
            this->message = message;
        }
        void setError(std::string message="") {
            this->error = true;
            this->message = message;
        }
        void show() {
            std::string msg = "TaskbarToggle: " + this->message;

            if (!this->error) {
                MessageBoxA(NULL, msg.c_str(), "Alert", MB_ICONINFORMATION | MB_OK);
            } else {
                MessageBoxA(NULL, msg.c_str(), "Error", MB_ICONEXCLAMATION | MB_OK);
            }
        }
    };
}
