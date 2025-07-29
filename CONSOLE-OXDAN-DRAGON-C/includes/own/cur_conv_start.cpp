#include <windows.h>
#include <iostream>
#include <boost/algorithm/string.hpp>
#include "all_diclarations.h"

using namespace std;

void cur_conv_start()
{
	const double YEN_PER_DOLLAR = 146.33; //
	const double EUROS_PER_DOLLAR = 0.92; //
	const double peso_per = 19.30; //
	const double rub_per = 85.74; //
	const double funt_per = 0.79; //
	const double canada_per = 1.37; //
	const double hryvna_per = 40.97; //
	const double uane_per = 7.18; //
	const double rupee_per = 83.93; //
	const double real_per = 5.64; //

	string usd_str;

	cout << endl;
	printf("\033[0;31mEnter 'esc' (for exit) \033[0;37m\n");
	cout << "\033[0;32mEnter U.S. dollar amount: \033[0;37m";
	cin >> usd_str;
	boost::to_lower(usd_str);
	boost::trim(usd_str);
	if (usd_str == "esc")
	{
		check_start_start();
	}
	double usd = std::stod(usd_str);
	cout << endl << "(" << "\033[0;31m" << "2025" << "\033[0;37m" << ")" << ":" << "\n";
	cout << endl << "\033[0;33m" << usd << "\033[0;32m" << "$ " << "\033[0;37m" << "is: " << endl;
	cout << "                             " << endl;
	cout << "  " << " \033[0;33m" << (usd * YEN_PER_DOLLAR) << "\033[0;37m" << "     Yen (Japan) (JPY)" << endl;
	cout << "                                                            " << endl;
	cout << "  " << " \033[0;33m" << (usd * EUROS_PER_DOLLAR) << "\033[0;37m" << "     Euro (Europe) (EUR)" << endl;
	cout << "                                                            " << endl;
	cout << "  " << " \033[0;33m" << (usd * peso_per) << "\033[0;37m" << "     Pesos (Mexico) (MXN)" << endl;
	cout << "                                                            " << endl;
	cout << "  " << " \033[0;33m" << (usd * rub_per) << "\033[0;37m" << "     Ruble (Russia) (RUB)" << endl;
	cout << "                                                            " << endl;
	cout << "  " << " \033[0;33m" << (usd * funt_per) << "\033[0;37m" << "     lb. (England) (GBP)" << endl;
	cout << "                                                            " << endl;
	cout << "  " << " \033[0;33m" << (usd * canada_per) << "\033[0;37m" << "     $Dollars$ (Canada) (CAD)" << endl;
	cout << "                                                            " << endl;
	cout << "  " << " \033[0;33m" << (usd * hryvna_per) << "\033[0;37m" << "     Hryvnia (Ukraine) (UAH)" << endl;
	cout << "                                                            " << endl;
	cout << "  " << " \033[0;33m" << (usd * uane_per) << "\033[0;37m" << "     Yuan (Chaina) (CNY)" << endl;
	cout << "                                                            " << endl;
	cout << "  " << " \033[0;33m" << (usd * rupee_per) << "\033[0;37m" << "     Rupee (India) (INR)" << endl;
	cout << "                                                            " << endl;
	cout << "  " << " \033[0;33m" << (usd * real_per) << "\033[0;37m" << "     Real (Brazil) (BRL)" << endl;
	cout << "\033[0;37m";

	//cout << endl;

	check_start_start();
}