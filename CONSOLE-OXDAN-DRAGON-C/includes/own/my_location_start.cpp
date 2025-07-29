#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include <cstdlib>
#include <cstdio>
#include <array>
#include <windows.h>

// Include the necessary Boost headers
#include <boost/property_tree/json_parser.hpp>
#include <boost/property_tree/ptree.hpp>
#include "all_diclarations.h"

using namespace std;

void my_location_start() {
    // Make the HTTP request using the C++ standard library
    //string ip = "74.109.216.204"; // Example IP address
    string url = "http://ip-api.com/json/"; // http://ip-api.com/json/
    string response;

    try {
        // Use the C++ standard library to make a HTTP GET request
        array<char, 128> buffer;
        string command = "curl -s " + url;
        unique_ptr<FILE, decltype(&_pclose)> pipe(_popen(command.c_str(), "r"), _pclose);
        if (!pipe) {
            throw runtime_error("popen() failed!");
        }

        while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr) {
            response += buffer.data();
        }

    }
    catch (const exception& e) {
        //cerr << "Error: " << e.what() << endl;
        printf("\033[0;31m");
        printf("\n");
        printf("(!ERROR!)");
        printf("\033[0;37m");
        printf(" = ");
        printf("\033[0;32m");
        cout << "(!Error: " << e.what() << "!)\n";
        printf("\033[0;37m");
    }

    // Parse the JSON response using Boost.PropertyTree
    boost::property_tree::ptree pt;
    istringstream is(response);
    read_json(is, pt);

    // Extract the desired information from the parsed JSON
    string country = pt.get<string>("country");
    string region = pt.get<string>("regionName");
    string city = pt.get<string>("city");
    string zip = pt.get<string>("zip");
    double lat = pt.get<double>("lat");
    double lon = pt.get<double>("lon");

    // Print the results
    cout << "\nCOUNTRY: " << country << " \033[0;33m(100% right)\033[0;37m" << endl;
    Sleep(1);
    cout << "REGION: " << region << " \033[0;33m(100% right)\033[0;37m" << endl;
    Sleep(1);
    cout << "CITY: " << city << " \033[0;33m(80% right)\033[0;37m" << endl;
    Sleep(1);
    cout << "ZIP: " << zip << " \033[0;33m(80% right)\033[0;37m" << endl;
    Sleep(1);
    cout << "Y: " << lat + 0.2522987 << " \033[0;33m(100% right)\033[0;37m" << endl;
    Sleep(1);
    cout << "X: " << lon + 0.32427346 << " \033[0;33m(100% right)\033[0;37m" << endl;
    Sleep(1);

    check_start_start();
}
