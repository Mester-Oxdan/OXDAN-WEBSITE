#include <iostream>
#include <windows.h>
#include <math.h>
#include <conio.h>
#include <boost/algorithm/string.hpp>
#include "all_diclarations.h"

#pragma warning(disable : 4996).

using namespace std;

bool isNumber44(string s)
{
	for (int i = 0; i < s.length(); i++)
		if (isdigit(s[i]) == false)
			return false;

	return true;
}

void d_price_calc_start() {
	string time;
	string plastic;
	string magnits;
	string magnits_size;
	string ring;
	int time_2;
	int plastic_2;
	int magnits_2;
	int magnits_size_2;
	int ring_2;
	float magnits_coast;
	float magnits_coast_2;

	printf("\n\033[0;31mEnter 'esc' (for exit) \033[0;37m\n");
	printf("\033[0;33mEnter time amount ($0.0007/minute): \033[0;37m");
	cin >> time;
	boost::to_lower(time);
	boost::trim(time);
	if (time == "esc")
	{
		check_start_start();
	}

	else if (!(isNumber44(time)))
	{
		printf("\033[0;31m");
		printf("\n");
		printf("(!ERROR!)");
		printf("\033[0;37m");
		printf(" = ");
		printf("\033[0;32m");
		printf("(!Only integers!)\n");
		printf("\033[0;37m");
		getch();

		d_price_calc_start();
	}
	else {
		time_2 = atoi(time.c_str());
	}

	printf("\n\033[0;31mEnter 'esc' (for exit) \033[0;37m\n");
	printf("\033[0;33mEnter plastic amount (grams): \033[0;37m");
	cin >> plastic;
	boost::to_lower(plastic);
	boost::trim(plastic);
	if (plastic == "esc")
	{
		check_start_start();
	}

	else if (!(isNumber44(plastic)))
	{
		printf("\033[0;31m");
		printf("\n");
		printf("(!ERROR!)");
		printf("\033[0;37m");
		printf(" = ");
		printf("\033[0;32m");
		printf("(!Only integers!)\n");
		printf("\033[0;37m");
		getch();

		d_price_calc_start();
	}
	else {
		plastic_2 = atoi(plastic.c_str());
	}

	printf("\n\033[0;31mEnter 'esc' (for exit) \033[0;37m\n");
	printf("\033[0;33mEnter magnits amount (pcs): \033[0;37m");
	cin >> magnits;
	boost::to_lower(magnits);
	boost::trim(magnits);
	if (magnits == "esc")
	{
		check_start_start();
	}

	else if (!(isNumber44(magnits)))
	{
		printf("\033[0;31m");
		printf("\n");
		printf("(!ERROR!)");
		printf("\033[0;37m");
		printf(" = ");
		printf("\033[0;32m");
		printf("(!Only integers!)\n");
		printf("\033[0;37m");
		getch();

		d_price_calc_start();
	}
	else {
		magnits_2 = atoi(magnits.c_str());
	}

	if (magnits_2 != 0) {
		printf("\n\033[0;31mEnter 'esc' (for exit) \033[0;37m\n");
		printf("\033[0;33mEnter magnits size 1, 2, 3, 4 (1 - 10x2mm, 2 - 8x2mm, 3 - 6x2mm, 4 - 5x2mm): \033[0;37m");
		cin >> magnits_size;
		boost::to_lower(magnits_size);
		boost::trim(magnits_size);
		if (magnits_size == "esc")
		{
			check_start_start();
		}

		else if (!(isNumber44(magnits_size)))
		{
			printf("\033[0;31m");
			printf("\n");
			printf("(!ERROR!)");
			printf("\033[0;37m");
			printf(" = ");
			printf("\033[0;32m");
			printf("(!Only integers!)\n");
			printf("\033[0;37m");
			getch();

			d_price_calc_start();
		}
		else {
			magnits_size_2 = atoi(magnits_size.c_str());

			if (magnits_size_2 == 1) {
				magnits_coast = 0.13 * magnits_2;
			}
			else if (magnits_size_2 == 2) {
				magnits_coast = 0.08 * magnits_2;
			}
			else if (magnits_size_2 == 3) {
				magnits_coast = 0.06 * magnits_2;
			}
			else if (magnits_size_2 == 4) {
				magnits_coast = 0.07 * magnits_2;
			}
		}

	}
	printf("\n\033[0;31mEnter 'esc' (for exit) \033[0;37m\n");
	printf("\033[0;33mEnter rings amount ($0.01/pcs): \033[0;37m");
	cin >> ring;
	boost::to_lower(ring);
	boost::trim(ring);
	if (ring == "esc")
	{
		check_start_start();
	}

	else if (!(isNumber44(ring)))
	{
		printf("\033[0;31m");
		printf("\n");
		printf("(!ERROR!)");
		printf("\033[0;37m");
		printf(" = ");
		printf("\033[0;32m");
		printf("(!Only integers!)\n");
		printf("\033[0;37m");
		getch();

		d_price_calc_start();
	}
	else {
		ring_2 = atoi(ring.c_str());
	}
	if (magnits_2 != 0) {
		magnits_coast_2 = magnits_coast;
	}
	else {
		magnits_coast_2 = 0;
	}
	float pla_result = (((time_2 * 0.0007) + (plastic_2 * 0.018) + magnits_coast_2 + (ring_2 * 0.1)) * 2.5 + 0.5);
	float petg_result = (((time_2 * 0.0007) + (plastic_2 * 0.015) + magnits_coast_2 + (ring_2 * 0.1)) * 2.5 + 0.5);

	double pla_result_raunded = std::round(pla_result * 1000.0) / 1000.0;
	double petg_result_raunded = std::round(petg_result * 1000.0) / 1000.0;

	string choice;

	cout << "\n\033[0;33mPLA Model: \033[0;32m$\033[0;37m" << pla_result_raunded << "\n";
	cout << "\033[0;33mPETG Model: \033[0;32m$\033[0;37m" << petg_result_raunded << "\n\n";

	printf("\033[0;33mDo you want to calculate again? \033[0;33m(\033[0;32my\033[0;37m/\033[0;31mn\033[0;33m)\033[0;37m\n");
	cin >> choice;
	boost::to_lower(choice);
	boost::trim(choice);
	if (choice == "y" || choice == "yes")
	{
		d_price_calc_start();
	}
	else
	{
		check_start_start();
	}
}