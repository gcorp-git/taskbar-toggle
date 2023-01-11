#pragma once

#include <windows.h>

bool isDuplicateProcess() {
    CreateMutexA(0, FALSE, "Local\\$myprogram$");

    return GetLastError() == ERROR_ALREADY_EXISTS;
}
