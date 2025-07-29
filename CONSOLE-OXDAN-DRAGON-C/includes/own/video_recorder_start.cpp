#include "opencv2\opencv.hpp"
#include "opencv2\highgui.hpp"
#include <iostream>
#include <vector>
#include <windows.h>
#include <string>
#include <conio.h>
#include <portaudio.h>
#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <malloc.h>
#include "all_diclarations.h"

#pragma warning(disable : 4996).

using namespace std;
using namespace cv;

void SetOpenCVWindowIcon_2(const std::string& windowName, const std::string& iconPath) {
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
}

void webcam_recorder_start()
{
	printf("\n\033[0;31mPress 'Esc' for exit\033[0;37m\n");

	while (true)
	{
		//system("cls");
		// Create video capturing object
		// 0 opens default camera, otherwise filename as argument
		cv::VideoCapture video(0);
		string iconPath_2 = oxdan_dragon_c + "/my_dragon_ico.ico";
		// Check that video is opened
		if (!video.isOpened()) - 1;

		// For saving the frame
		cv::Mat frame;

		// Get video resolution
		int frameWidth = video.get(cv::CAP_PROP_FRAME_WIDTH);
		int frameHeigth = video.get(cv::CAP_PROP_FRAME_HEIGHT);

		// Create video writer object
		cv::VideoWriter output("webcam_recording.avi", cv::VideoWriter::fourcc('M', 'J', 'P', 'G'), 30, cv::Size(frameWidth, frameHeigth));

		// Loop through available frames
		while (video.read(frame)) 
        {

			// Display the frame
			cv::imshow("Webcam Recorder: ", frame);
            SetOpenCVWindowIcon_2("Webcam Recorder: ", iconPath_2);
			// Write video frame to output
			output.write(frame);

			// For breaking the loop
			if (cv::waitKey(27) >= 0)
			{

                // Release video capture and writer
                output.release();
                video.release();

                // Destroy all windows
                cv::destroyAllWindows();

                check_start_start();

			}

		} // end while (video.read(frame))

        // Release video capture and writer
        output.release();
        video.release();

        // Destroy all windows
        cv::destroyAllWindows();

        check_start_start();

	}

    // Destroy all windows
    cv::destroyAllWindows();

    check_start_start();

}