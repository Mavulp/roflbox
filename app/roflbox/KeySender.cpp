#include "KeySender.hpp"

KeySender::KeySender()
{
    mInput.type = INPUT_KEYBOARD;
}

KeySender::~KeySender()
{
}

void KeySender::writeCharArray(const char text[])
{

    for(int i = 0; text[i] != '\0'; i++)
        writeKey(text[i]);
}

void KeySender::writeKey(char c)
{
    mInput.ki.dwFlags = 0;

    SHORT vk = VkKeyScanEx(c, mKBLayout);
    if(vk & 0x100) // Shift-Key
    {
        mInput.ki.wVk = VK_SHIFT;
        SendInput(1, &mInput, sizeof(INPUT));
    }
    if(vk & 0x200) // Ctrl-Key
    {
        mInput.ki.wVk = VK_CONTROL;
        SendInput(1, &mInput, sizeof(INPUT));
    }
    if(vk & 0x400) // Alt-Key
    {
        mInput.ki.wVk = VK_MENU;
        SendInput(1, &mInput, sizeof(INPUT));
    }

    mInput.ki.wVk = vk & 0xFF;
    SendInput(1, &mInput, sizeof(INPUT));

    Sleep(1);

    // Depress Key
    mInput.ki.dwFlags = KEYEVENTF_KEYUP;
    SendInput(1, &mInput, sizeof(INPUT));

    // Depress Modifiers
    mInput.ki.wVk = VK_SHIFT;
    SendInput(1, &mInput, sizeof(INPUT));
    mInput.ki.wVk = VK_CONTROL;
    SendInput(1, &mInput, sizeof(INPUT));
    mInput.ki.wVk = VK_MENU;
    SendInput(1, &mInput, sizeof(INPUT));

    Sleep(mDelay);
}
