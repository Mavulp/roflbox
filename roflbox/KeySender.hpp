#pragma once
#include <Windows.h>
#include <string>

class KeySender {
public:
    KeySender();
    ~KeySender() {};

    void writeCharArray(const char text[]);
    void writeChar(char c);

    void setDelay(int milliSeconds) {mDelay = milliSeconds;}

private:
    HKL mKBLayout = GetKeyboardLayout(0);
    INPUT mInput;

    int mDelay;
};
