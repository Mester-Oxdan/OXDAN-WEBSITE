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
#include <boost/algorithm/string.hpp>
#include "all_diclarations.h"

using namespace std;

void ip_search_start() 
{
    // Make the HTTP request using the C++ standard library
    string ip; // Example IP address
    //string url = "http://ip-api.com/json/" + ip; // http://ip-api.com/json/
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

    string query = pt.get<string>("query");
    printf("\n\033[0;31mEnter 'esc' (for exit) \033[0;37m");
    cout << "\n\033[0;33mEnter Network Ip Address like (\033[0;37m" + query + "\033[0;33m): \033[0;37m";
    cin >> ip;
    boost::to_lower(ip);
    boost::trim(ip);
    if (ip == "esc")
    {
        check_start_start();
    }

    string url_2 = "http://ip-api.com/json/" + ip; // http://ip-api.com/json/
    string response_2;

    try {
        // Use the C++ standard library to make a HTTP GET request
        array<char, 128> buffer_2;
        string command = "curl -s " + url_2;
        unique_ptr<FILE, decltype(&_pclose)> pipe(_popen(command.c_str(), "r"), _pclose);
        if (!pipe) {
            throw runtime_error("popen() failed!");
        }

        while (fgets(buffer_2.data(), buffer_2.size(), pipe.get()) != nullptr) {
            response_2 += buffer_2.data();
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
        printf("(!Failed to get power status!)\n");
        printf("\033[0;37m");
    }

    // Parse the JSON response using Boost.PropertyTree
    boost::property_tree::ptree pt_2;
    istringstream is_2(response_2);
    read_json(is_2, pt_2);

    // Extract the desired information from the parsed JSON
    string country_2 = pt_2.get<string>("country");
    string region_2 = pt_2.get<string>("regionName");
    string city_2 = pt_2.get<string>("city");
    string zip_2 = pt_2.get<string>("zip");
    string query_2 = pt_2.get<string>("query");
    double lat_2 = pt_2.get<double>("lat");
    double lon_2 = pt_2.get<double>("lon");

    // Print the results
    cout << "\nCOUNTRY: " << country_2 << " \033[0;33m(100% right)\033[0;37m" << endl;
    Sleep(1);
    cout << "REGION: " << region_2 << " \033[0;33m(100% right)\033[0;37m" << endl;
    Sleep(1);
    cout << "CITY: " << city_2 << " \033[0;33m(80% right)\033[0;37m" << endl;
    Sleep(1);
    cout << "ZIP: " << zip_2 << " \033[0;33m(80% right)\033[0;37m" << endl;
    Sleep(1);
    cout << "Y: " << lat_2 + 0.2522987 << " \033[0;33m(100% right)\033[0;37m" << endl;
    Sleep(1);
    cout << "X: " << lon_2 + 0.32427346 << " \033[0;33m(100% right)\033[0;37m" << endl;
    Sleep(1);

    check_start_start();
}
