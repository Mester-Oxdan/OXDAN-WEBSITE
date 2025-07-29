#include <windows.h>
#include <mmeapi.h>
#include <mmdeviceapi.h> 
#include <endpointvolume.h>
#include <audioclient.h>
#include <windows.h>
#include <cmath>
#include "all_diclarations.h"

bool GetVolumeLevel()
{
    HRESULT hr;
    IMMDeviceEnumerator* pDeviceEnumerator = 0;
    IMMDevice* pDevice = 0;
    IAudioEndpointVolume* pAudioEndpointVolume = 0;

    try {
        hr = CoCreateInstance(__uuidof(MMDeviceEnumerator), NULL, CLSCTX_ALL, __uuidof(IMMDeviceEnumerator), (void**)&pDeviceEnumerator);
        if (FAILED(hr)) throw "CoCreateInstance";
        hr = pDeviceEnumerator->GetDefaultAudioEndpoint(eRender, eMultimedia, &pDevice);
        if (FAILED(hr)) throw "GetDefaultAudioEndpoint";
        hr = pDevice->Activate(__uuidof(IAudioEndpointVolume), CLSCTX_ALL, NULL, (void**)&pAudioEndpointVolume);
        if (FAILED(hr)) throw "pDevice->Active";

        float fVolume; // float

        hr = pAudioEndpointVolume->GetMasterVolumeLevelScalar(&fVolume); // &

        if (fVolume == 0)
        {
            printf("\n\033[0;33mWindows volume muted:\033[0;32m yes\033[0;37m");
        }

        else if (fVolume > 0)
        {
            printf("\n\033[0;33mWindows volume muted:\033[0;31m no\033[0;37m");
        }

        double roundedValue = std::round(fVolume * 100);

        printf("\n\033[0;33mCurrent windows volume: \033[0;37m");
        printf("%lf", roundedValue); // "%lf"

        printf("\n");

        if (FAILED(hr)) throw "SetMasterVolumeLevelScalar";

        pAudioEndpointVolume->Release();
        pDevice->Release();
        pDeviceEnumerator->Release();
        return true;
    }
    catch (...) {
        if (pAudioEndpointVolume) pAudioEndpointVolume->Release();
        if (pDevice) pDevice->Release();
        if (pDeviceEnumerator) pDeviceEnumerator->Release();
        throw;
    }
    return false;
}

void my_volume_level()
{
    CoInitialize(0);
    try
    {
        GetVolumeLevel();

    }
    catch (...) 
    {
        //err handle..
    }
    CoUninitialize();
    check_start_start();
}