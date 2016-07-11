#include "KeySender.hpp"

int main() {
    KeySender ks;

    Sleep(1000*10);
    ks.setDelay(2);
    while(true) {
        ks.writeKey('t');
        Sleep(160);
        ks.writeString("WWW.ROFLBOX.WEBSITE");
        Sleep(160);
        ks.writeString(" - BEST FREE RL HACK!");
        ks.writeKey('\n');
        Sleep(160);
        ks.writeKey('t');
        Sleep(160);
        ks.writeString("GET GOOD, GET ROFLBOX!");
        ks.writeKey('\n');

        Sleep(1000 * 30);
    }

    return 0;
}
