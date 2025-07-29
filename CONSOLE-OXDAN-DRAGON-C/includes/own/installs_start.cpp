#include <windows.h>
#include <string>
//#include <boost/filesystem.hpp>
//#include <boost/process.hpp>
#include "all_diclarations.h"

using namespace std;
//namespace bp = boost::process;

void installs_start(string name)
{
	
	if (name == "python")
	{
		string cmdhg = "start " + oxdan_dragon_c + "\\includes\\own\\includes\\installs\\python.exe";
		system(cmdhg.c_str());
	}
	else if (name == "nmap")
	{
		string cmdhg_7 = "start " + oxdan_dragon_c + "\\includes\\own\\includes\\installs\\nmap.exe";
		system(cmdhg_7.c_str());
	}
	else if (name == "metasploit")
	{
		string cmdhg_7 = "start " + oxdan_dragon_c + "\\includes\\own\\includes\\installs\\metasploit.exe";
		system(cmdhg_7.c_str());
	}
	else if (name == "virtualbox")
	{
		string cmdhg_7 = "start " + oxdan_dragon_c + "\\includes\\own\\includes\\installs\\virtualbox.exe";
		system(cmdhg_7.c_str());
	}
	else if (name == "wireshark")
	{
		string cmdhg_7 = "start " + oxdan_dragon_c + "\\includes\\own\\includes\\installs\\wireshark.exe";
		system(cmdhg_7.c_str());
	}
	else if (name == "protonvpn")
	{
		string cmdhg_7 = "start " + oxdan_dragon_c + "\\includes\\own\\includes\\installs\\protonvpn.exe";
		system(cmdhg_7.c_str());
	}
	else if (name == "git")
	{
		//boost::filesystem::path cur_path(boost::filesystem::current_path());
		//printf("Hello git \n");
		//printf(cur_path.string().c_str());

		//boost::filesystem::path cmd_path = cur_path / "includes" / "own" / "includes" / "installs" / "Git-2.37.2.2-64-bit.exe";
		//printf("\n cmd: \n");
		//printf(cmd_path.string().c_str());
		//printf("\n");
		//bp::system(cmd_path);

		string cmdhg_10 = "start " + oxdan_dragon_c + "\\includes\\own\\includes\\installs\\git.exe";
		//printf(cmdhg_10.c_str());
		//printf("\n");
		system(cmdhg_10.c_str());
	}
	else if (name == "miniconda")
	{
		string cmdhg_9 = "start " + oxdan_dragon_c + "\\includes\\own\\includes\\installs\\miniconda3.exe";
		system(cmdhg_9.c_str());
	}
	else if (name == "tor")
	{
		string cmdhg_9 = "start " + oxdan_dragon_c + "\\includes\\own\\includes\\installs\\tor.exe";
		system(cmdhg_9.c_str());
	}
	else if (name == "torrent")
	{
		string cmdhg_9 = "start " + oxdan_dragon_c + "\\includes\\own\\includes\\installs\\torrent.exe";
		system(cmdhg_9.c_str());
	}
	else if (name == "vscode")
	{
		string cmdhg_9 = "start " + oxdan_dragon_c + "\\includes\\own\\includes\\installs\\vs_code.exe";
		system(cmdhg_9.c_str());
	}
	else if (name == "vs")
	{
		string cmdhg_9 = "start " + oxdan_dragon_c + "\\includes\\own\\includes\\installs\\vs.exe";
		system(cmdhg_9.c_str());
	}
	else if (name == "steam")
	{
		string cmdhg_9 = "start " + oxdan_dragon_c + "\\includes\\own\\includes\\installs\\steam.exe";
		system(cmdhg_9.c_str());
	}
	else if (name == "ea")
	{
		string cmdhg_9 = "start " + oxdan_dragon_c + "\\includes\\own\\includes\\installs\\ea.exe";
		system(cmdhg_9.c_str());
	}
	else if (name == "7_zip")
	{
		string cmdhg_9 = "start " + oxdan_dragon_c + "\\includes\\own\\includes\\installs\\7_zip.exe";
		system(cmdhg_9.c_str());
	}
}