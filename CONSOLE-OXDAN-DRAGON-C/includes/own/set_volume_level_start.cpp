#include <Windows.h>
#include <iostream>
#include <string>
#include "all_diclarations.h"

using namespace std;

void setWindowsVolumeLevel(float volumeLevel) {
    INPUT input = { 0 };
    input.type = INPUT_KEYBOARD;
    input.ki.wScan = 0;
    input.ki.time = 0;
    input.ki.dwExtraInfo = 0;


        for (int i = 0; i < volumeLevel; i++) {
            input.ki.wVk = VK_VOLUME_UP;
            input.ki.dwFlags = 0;
            SendInput(1, &input, sizeof(INPUT));
            input.ki.dwFlags = KEYEVENTF_KEYUP;
            SendInput(1, &input, sizeof(INPUT));
        }

}

void changeVolumeretvv_78()
{
    INPUT ip = { 0 };
    ip.type = INPUT_KEYBOARD;
    ip.ki.wVk = VK_VOLUME_DOWN;   //or VOLUME_DOWN or MUTE
    SendInput(1, &ip, sizeof(INPUT));
    ip.ki.dwFlags = KEYEVENTF_KEYUP;
    SendInput(1, &ip, sizeof(INPUT));
}

void set_volume_level_start(string ma90n) 
{
    float volumeLevel = stoi(ma90n) / 2; // Set the desired volume level here
    for (int i = 0; i < 50; i++)
    {
        changeVolumeretvv_78();
    }
    setWindowsVolumeLevel(volumeLevel);
    check_start_start();
}
