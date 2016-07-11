#pragma once
#include <Windows.h>
#include <string>

class KeySender {
public:
    KeySender();
    ~KeySender();

    void writeString(std::string text) {writeCharArray(text.c_str());}
    void writeCharArray(const char text[]);
    void writeKey(char c);

    void setDelay(int milliSeconds) {mDelay = milliSeconds;}

private:
    HKL mKBLayout = GetKeyboardLayout(0);
    INPUT mInput;

    int mDelay;
};
