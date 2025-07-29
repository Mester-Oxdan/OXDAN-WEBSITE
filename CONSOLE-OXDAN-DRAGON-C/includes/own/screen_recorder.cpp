#include <opencv2/opencv.hpp>
#include <windows.h>
#include "all_diclarations.h"

void SetOpenCVWindowIcon(const std::string& windowName, const std::string& iconPath) {
    // Create the OpenCV window
    cv::namedWindow(windowName, cv::WINDOW_AUTOSIZE);

    // Wait for the window to appear
    cv::waitKey(1);

    // Find the window handle by the OpenCV window name
    HWND hwnd = FindWindowA(NULL, windowName.c_str());

    if (hwnd == NULL) {
        //std::cerr << "Could not find OpenCV window!" << std::endl;
        printf("\033[0;31m");
        printf("\n");
        printf("(!ERROR!)");
        printf("\033[0;37m");
        printf(" = ");
        printf("\033[0;32m");
        printf("(!Could not find OpenCV window!)\n");
        printf("\033[0;37m");
        return;
    }

    // Load the custom icon
    HICON hIcon = (HICON)LoadImageA(NULL, iconPath.c_str(), IMAGE_ICON, 0, 0, LR_LOADFROMFILE | LR_DEFAULTSIZE | LR_SHARED);
    if (hIcon == NULL) {
        //std::cerr << "Could not load icon!" << std::endl;
        printf("\033[0;31m");
        printf("\n");
        printf("(!ERROR!)");
        printf("\033[0;37m");
        printf(" = ");
        printf("\033[0;32m");
        printf("(!Could not load icon!)\n");
        printf("\033[0;37m");
        return;
    }

    // Set the icon for the window
    SendMessage(hwnd, WM_SETICON, ICON_BIG, (LPARAM)hIcon);
    SendMessage(hwnd, WM_SETICON, ICON_SMALL, (LPARAM)hIcon);

    // Optionally, you can keep the icon loaded in memory by storing the HICON handle
    // If you want to automatically unload it when the program exits, you can delete it:
    // DestroyIcon(hIcon);
}

void screen_recorder_start()
{
    cv::VideoWriter writer;
    cv::Mat frame;
    string iconPath_1 = oxdan_dragon_c + "/my_dragon_ico.ico";
    HWND hwndScreen = GetDesktopWindow();
    HDC hdcScreen = GetDC(hwndScreen);
    HDC hdcMem = CreateCompatibleDC(hdcScreen);
    HBITMAP hbmScreen = CreateCompatibleBitmap(hdcScreen, GetSystemMetrics(SM_CXSCREEN), GetSystemMetrics(SM_CYSCREEN));
    SelectObject(hdcMem, hbmScreen);

    int codec = cv::VideoWriter::fourcc('M', 'J', 'P', 'G'); // XVID codec
    double fps = 25.0;
    std::string outputFilename = "screen_recording.avi"; // Change to your desired path if needed

    cv::namedWindow("Screen Recorder: ", cv::WINDOW_NORMAL);
    SetOpenCVWindowIcon("Screen Recorder: ", iconPath_1);
    cv::resizeWindow("Screen Recorder: ", 640, 480);

    bool recording = true;
    bool paused = false;

    while (recording)
    {
        if (!paused)
        {
            // Capture the screen
            BitBlt(hdcMem, 0, 0, GetSystemMetrics(SM_CXSCREEN), GetSystemMetrics(SM_CYSCREEN), hdcScreen, 0, 0, SRCCOPY);
            frame = cv::Mat(GetSystemMetrics(SM_CYSCREEN), GetSystemMetrics(SM_CXSCREEN), CV_8UC4);
            GetBitmapBits(hbmScreen, GetSystemMetrics(SM_CXSCREEN) * GetSystemMetrics(SM_CYSCREEN) * 4, frame.data);
            cv::cvtColor(frame, frame, cv::COLOR_BGRA2BGR);

            if (!writer.isOpened())
            {
                if (!writer.open(outputFilename, cv::VideoWriter::fourcc('M', 'J', 'P', 'G'), fps, frame.size(), true))
                {
                    //std::cerr << "Error: Could not open video file for writing." << std::endl;
                    printf("\033[0;31m");
                    printf("\n");
                    printf("(!ERROR!)");
                    printf("\033[0;37m");
                    printf(" = ");
                    printf("\033[0;32m");
                    printf("(!Could not open video file for writing!)\n");
                    printf("\033[0;37m");
                    break;
                }
            }

            writer.write(frame);
            cv::imshow("Screen Recorder", frame);
        }

        int key = cv::waitKey(1);

        switch (key)
        {
        case 27: // Esc key to stop recording
            recording = false;
            break;
        case 32: // Space key to pause/resume recording
            paused = !paused;
            break;
        }
    }

    // Release resources
    writer.release();
    cv::destroyAllWindows();
    ReleaseDC(hwndScreen, hdcScreen);
    DeleteDC(hdcMem);
    DeleteObject(hbmScreen);

    // Call the next function (assuming you have this implemented)
    check_start_start();

}
