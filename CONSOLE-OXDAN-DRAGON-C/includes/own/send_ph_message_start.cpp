#include <iostream>
#include <curl/curl.h>
#include "all_diclarations.h"

using namespace std;

// Callback function for cURL to write response data
size_t WriteCallback(void* contents, size_t size, size_t nmemb, std::string* response) {
    size_t totalSize = size * nmemb;
    response->append((char*)contents, totalSize);
    return totalSize;
}

void send_ph_message_start() 
{
    std::string accountSID;
    // Twilio account credentials
    cout << "\033[0;31m\nWrite 'esc' (for exit) \033[0;37m";
    cout << "\033[0;33m\nEnter twilio AccountSID: \033[0;37m";
    cin >> accountSID; // "AC020e3c7fc79776b0481c66d2a396e738";
    if (accountSID == "esc")
    {
        check_start_start();
    }
    std::string authToken; // "ac5e22992f69471269fece46237b6b12";
    cout << "\033[0;33mEnter twilio AuthToken: \033[0;37m";
    cin >> authToken;
    if (authToken == "esc")
    {
        check_start_start();
    }
    std::string fromNumber; // "+18667066119";
    cout << "\033[0;33mEnter twilio phone number: \033[0;37m";
    cin >> fromNumber;
    if (fromNumber == "esc")
    {
        check_start_start();
    }
    std::string toNumber; // "+14129089359";
    cout << "\033[0;33mEnter to someone phone number: \033[0;37m";
    cin >> toNumber;
    if (toNumber == "esc")
    {
        check_start_start();
    }
    std::string message; // "Hello, World!";
    cout << "\033[0;33mEnter message: \033[0;37m";
    cin >> message;
    if (message == "esc")
    {
        check_start_start();
    }

    // Twilio API endpoint
    const std::string apiUrl = "https://api.twilio.com/2010-04-01/Accounts/" + accountSID + "/Messages.json";

    // Initialize cURL
    CURL* curl = curl_easy_init();
    if (curl) {
        // Set the cURL options
        std::string authString = accountSID + ":" + authToken;
        std::string postData = "From=" + fromNumber + "&To=" + toNumber + "&Body=" + message;

        curl_easy_setopt(curl, CURLOPT_URL, apiUrl.c_str());
        curl_easy_setopt(curl, CURLOPT_POST, 1L);
        curl_easy_setopt(curl, CURLOPT_USERPWD, authString.c_str());
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, postData.c_str());

        // Response data buffer
        std::string responseData;

        // Set the callback function to handle the response data
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &responseData);

        // Perform the cURL request
        CURLcode res = curl_easy_perform(curl);

        // Check for errors and print the response
        if (res != CURLE_OK) {
            printf("\033[0;31m");
            printf("\n");
            printf("(!ERROR!)");
            printf("\033[0;37m");
            printf(" = ");
            printf("\033[0;32m");
            printf("(!Enter valid information!)\n");
            printf("\033[0;37m");
            check_start_start();
        }
        else {
            std::cout << "\n\033[0;32mSMS successfully!\033[0;37m" << std::endl;
            check_start_start();
        }

        // Cleanup cURL
        curl_easy_cleanup(curl);
    }
    else {
        printf("\033[0;31m");
        printf("\n");
        printf("(!ERROR!)");
        printf("\033[0;37m");
        printf(" = ");
        printf("\033[0;32m");
        printf("(!Enter valid information!)\n");
        printf("\033[0;37m");
        check_start_start();
    }

}
