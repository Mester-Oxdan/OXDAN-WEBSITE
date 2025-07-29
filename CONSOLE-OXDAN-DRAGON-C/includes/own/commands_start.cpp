#include <windows.h>
#include <iostream>
#include <vector>
#include "all_diclarations.h"

using namespace std;

void commands_start()
{

		printf("\n");
		printf("\033[0;31mCOMMANDS: \n"); // class !MAIN COMMANDS! (yellow: \033[0;33m white: \033[0;37m white blue: \033[0;36m)
		Sleep(1);
		printf("\n");
		Sleep(1);
		printf("\033[0;33mMAINS: \n"); // class MAINS: (+)
		Sleep(1);
		printf("\n");
		Sleep(1);
		printf("\033[0;37msearch - check if entered command exists \033[0;33m(\033[0;37m command \033[0;33m)\033[0;37m \n"); // search (-)
		Sleep(1);
		printf("\033[0;37m--help \033[0;36mor \033[0;37m-help \033[0;36mor \033[0;37mhelp \033[0;36mor \033[0;37m-h - shows all commands \n"); // --help (+)
		Sleep(1);
		printf("--version \033[0;36mor \033[0;37m-version \033[0;36mor \033[0;37mversion \033[0;36mor \033[0;37m-v - shows version \n"); // --version (+)
		Sleep(1);
		printf("pip - using entered pip commands \033[0;33m(\033[0;37m command \033[0;33m)\033[0;37m \n"); // pip (+)
		Sleep(1);
		printf("git - using entered git commands \033[0;33m(\033[0;37m command \033[0;33m)\033[0;37m \n"); // git (+)
		Sleep(1);
		printf("conda - using entered conda commands \033[0;33m(\033[0;37m command \033[0;33m)\033[0;37m \n"); // conda (+)
		Sleep(1);
		printf("cmd - using entered cmd commands \033[0;33m(\033[0;37m command \033[0;33m)\033[0;37m \n"); // cmd (+)
		Sleep(1);
		printf("cls \033[0;36mor \033[0;37mclear - clear your screen \n"); // cls (+)
		Sleep(1);
		printf("go_to \033[0;36mor \033[0;37mcd - go to entered directory \033[0;33m(\033[0;37m path \033[0;33m)\033[0;37m\n"); // go_to (+)
		Sleep(1);
		printf("where - find path to file \033[0;33m(\033[0;37m file name \033[0;33m)\033[0;37m\n"); // where (+)
		Sleep(1);
		printf("dir \033[0;36mor \033[0;37mls - shows all files and folders of current directory \n"); // dir (+)
		Sleep(1);
		printf("mkdir - create new folder with entered name \033[0;33m(\033[0;37m folder name \033[0;33m)\033[0;37m\n"); // mkdir (+)
		Sleep(1);
		printf("create - create new file with entered name.type \033[0;33m(\033[0;37m name.type \033[0;33m)\033[0;37m\n"); // create (+)
		Sleep(1);
		printf("del \033[0;36mor \033[0;37mdelete - delete entered file name or directory \033[0;33m(\033[0;37m file name \033[0;33m)\033[0;37m\n"); // del (+)
		Sleep(1);
		printf("install - install entered option \033[0;33m(\033[0;37m python, nmap, metasploit, git, miniconda, virtualbox, wireshark, protonvpn, tor, torrent, vscode, vs, steam, ea, 7_zip \033[0;33m)\n"); // install (+)
		Sleep(1);
		printf("\033[0;37mupdate - update Dragon console to last version\n"); // update (+)
		Sleep(1);
		printf("\n");
		Sleep(1);
		printf("\033[0;33mHACKER STUFFS: \n"); // class HACKER STUFFS: (+)
		Sleep(1);
		printf("\n");
		Sleep(1);
		printf("\033[0;37mdll_injector - shows dll injector, run as admin \n"); // dll_injector (+)
		Sleep(1);
		printf("file_injector - shows file injector, run as admin \n"); // file_injector (+)
		Sleep(1);
		printf("pas_gen - shows password generator \033[0;33m(\033[0;37m w, u, n, nw \033[0;33m)\033[0;37m\n"); // pas_gen (+)
		Sleep(1);
		printf("my_wifi_pas - shows list passwords of yours wifi \n"); // my_wifi_pas (+)
		Sleep(1);
		printf("cor_desk - shows coordinates Desktop,Console,... \n"); // cor_desk (+)
		Sleep(1);
		printf("ascii_code - shows ascii code of each pressed key \n"); // ascii_code (+)
		Sleep(1);
		printf("ip_search - searching location by entered network ip address \033[0;33m(\033[0;37m ip address \033[0;33m)\033[0;37m (for location on google maps use (https://www.maps.ie/coordinates.html)) \n"); // ip_search (+)
		Sleep(1);
		//printf("phone_search - searching location by entered phone number with country code \033[0;33m(\033[0;37m phone number \033[0;33m)\033[0;37m (for location on google maps use (https://www.maps.ie/coordinates.html)) \n"); // phone_search (+)
		//Sleep(1);
		printf("mimikatz - using entered mimikatz commands \033[0;33m(\033[0;37m command \033[0;33m)\033[0;37m \n"); // mimikatz (+)
		Sleep(1);
		printf("john - using entered john the ripper commands \033[0;33m(\033[0;37m command \033[0;33m)\033[0;37m \n"); // john (+)
		Sleep(1);
		printf("nmap - using entered nmap commands \033[0;33m(\033[0;37m command \033[0;33m)\033[0;37m \n"); // nmap (+)
		Sleep(1);
		printf("sqlmap - using entered sqlmap commands \033[0;33m(\033[0;37m command \033[0;33m)\033[0;37m \n"); // sqlmap (+)
		Sleep(1);
		printf("hydra - using entered hydra commands \033[0;33m(\033[0;37m command \033[0;33m)\033[0;37m \n"); // hydra (+)
		Sleep(1);
		printf("metasploit - using entered metasploit commands \033[0;33m(\033[0;37m command \033[0;33m)\033[0;37m \n"); // metasploit (+)
		Sleep(1);
		printf("aircrack-ng - using entered aircrack-ng commands \033[0;33m(\033[0;37m command \033[0;33m)\033[0;37m \n"); // aircrack-ng (+)
		Sleep(1);
		printf("con_wifi - doing connection to entered wifi network \033[0;33m(\033[0;37m wifi network name \033[0;33m)\033[0;37m \n"); // con_wifi (+)
		Sleep(1);
		printf("wifi_hack - shows tool for brute force wifi network \n"); // wifi_hack (+)
		Sleep(1);
		printf("\033[0;37mget_ip_website - shows ip address of entered website \033[0;33m(\033[0;37m website name \033[0;33m)\033[0;37m\n"); // get_ip_website (+)
		Sleep(1);
		printf("auto_clicker - auto clicking, for exit press 'Esc' \n"); // auto_clicker (+)
		Sleep(1);
		printf("morse_code_cipher - shows morse code cipher \n"); // morse_code (+)
		Sleep(1);
		printf("caesar_cipher - shows caesar cipher \n"); // caesar_cipher (+)
		Sleep(1);
		//printf("ai_chat - shows ai chat \n"); // ai_chat (+)
		//Sleep(1);
		printf("\n");
		Sleep(1);
		printf("\033[0;33mPICTURES: \n"); // class PICTURES: (+)
		Sleep(1);
		printf("\n");
		Sleep(1);
		printf("\033[0;37mukraine - shows Ukraine flag \n"); // ukraine (+)
		Sleep(1);
		printf("author - shows Author of this console \n"); // author (+)
		Sleep(1);
		printf("matrix - shows hacker matrix \n"); // matrix (+)
		Sleep(1);
		printf("\n");
		Sleep(1);
		printf("\033[0;33mACCOUNTS: \n"); // class ACCOUNTS: (+)
		Sleep(1);
		printf("\n");
		Sleep(1);
		printf("\033[0;37mlogin - go to login page \n"); // login (+)
		Sleep(1);
		printf("registration - go to registration page \n"); // registration (+)
		Sleep(1);
		printf("instructions - go to instructions page \n"); // instructions (+)
		Sleep(1);
		printf("del_account - delete entered account \n"); // del_account (+)
		Sleep(1);
		printf("my_accounts - shows all your accounts \n"); // my_accounts (+)
		Sleep(1);
		printf("logout - go to main menu \n"); // logout (+)
		Sleep(1);
		printf("\n");
		Sleep(1);
		printf("\033[0;33mSERIOUS: \n"); // class SERIOUS: (+)
		Sleep(1);
		printf("\n");
		Sleep(1);
		printf("\033[0;37mtim \033[0;36mor \033[0;37mtime - shows real time \n"); // tim (+)
		Sleep(1);
		printf("stopwatch - shows stopwatch \n"); // stopwatch (+)
		Sleep(1);
		printf("timer - shows timer \n"); // timer (+)
		Sleep(1);
		printf("calculator - shows calculator \n"); // calculator (+)
		Sleep(1);
		printf("calendar - shows calendar \n"); // calendar (+)
		Sleep(1);
		printf("webcam_recorder - shows webcam video recorder (without recording voice (you can use dictaphone for recording voice)) \n"); // webcam_recorder (+)
		Sleep(1);
		printf("screen_recorder - shows screen video recorder (without recording voice (you can use dictaphone for recording voice)) \n"); // screen_recorder (+)
		Sleep(1);
		printf("cur_conv - shows currency converter \n"); // cur_conv (+)
		Sleep(1);
		printf("notepad - shows notepad \n"); // notepad (+)
		Sleep(1);
		printf("translator - shows languages translator \n"); // translator (+)
		Sleep(1);
		printf("dictaphone - shows dictaphone \n"); // dictaphone (+)
		Sleep(1);
		//printf("chat - shows chat \n"); // chat (+)
		//Sleep(1);
		printf("files_convertor - converts file to another file \n"); // files_convertor (+)
		Sleep(1);
		printf("3d_price_calc - calculates price for 3d model at Oxdan store \n"); // 3d_price_calc (+)
		Sleep(1);
		printf("\n");
		Sleep(1);
		printf("\033[0;33mGAMES: \n"); // class GAMES: (+)
		Sleep(1);
		printf("\n");
		Sleep(1);
		printf("\033[0;37mpacman - shows pacman \n"); // pacman (+)
		Sleep(1);
		printf("2048 - shows 2048 \n"); // 2048 (+)
		Sleep(1);
		printf("arkanoid - shows arkanoid \n"); // arkanoid (-)
		Sleep(1);
		printf("flappy_bird - shows flappy bird \n"); // flappy_bird (+)
		Sleep(1);
		printf("tetris - shows tetris \n"); // tetris (-)
		Sleep(1);
		printf("hangman - shows hangman \n"); // hangman (+)
		Sleep(1);
		printf("car_racing - shows car racing game \n"); // car_racing (+)
		Sleep(1);
		printf("guess_number - shows game guess my number \n"); // guess_number (+)
		Sleep(1);
		printf("typing_tutor - shows typing tutor \n"); // typing_tutor (+)
		Sleep(1);
		printf("battle_city - shows battle city, tanks game \n"); // battle_city (+)
		Sleep(1);
		printf("doom - shows doom \n"); // doom (+)
		Sleep(1);
		printf("mario - shows mario \n"); // mario (+)
		Sleep(1);
		printf("snake - shows snake game \033[0;33m(\033[0;37m 1, 2, ai \033[0;33m)\033[0;37m \n"); // snake (+)
		Sleep(1);
		printf("ping_pong - shows ping pong \033[0;33m(\033[0;37m 1, 2, ai \033[0;33m)\033[0;37m \n"); // ping_pong (+)
		Sleep(1);
		printf("tic_tac_toe - shows tic-tac-toe \033[0;33m(\033[0;37m 2, ai \033[0;33m)\033[0;37m \n"); // tic_tac_toe (+)
		Sleep(1);
		printf("checkers - shows checkers \033[0;33m(\033[0;37m 2, ai \033[0;33m)\033[0;37m \n"); // checkers (+)
		Sleep(1);
		printf("chess - shows chess \033[0;33m(\033[0;37m 2, ai \033[0;33m)\033[0;37m \n"); // chess (+)
		Sleep(1);
		printf("space_shooter - shows space shooter \n"); // space_shooter (+)
		Sleep(1);
		printf("\n");
		Sleep(1);
		printf("\033[0;33mOWNS: \n"); // class OWNS: (+)
		Sleep(1);
		printf("\n");
		Sleep(1);
		printf("\033[0;37mtitle - set input title \033[0;33m(\033[0;37m title name \033[0;33m)\033[0;37m\n"); // title (+)
		Sleep(1);
		printf("new \033[0;36mor \033[0;37mstart - opens one more Dragon console \n"); // new (+)
		Sleep(1);
		printf("open - opens entered file \033[0;33m(\033[0;37m path \033[0;33m)\033[0;37m \n"); // open (+)
		Sleep(1);
		printf("shutdown - shutdowns your laptop \n"); // shutdown (+)
		Sleep(1);
		printf("restart - restarts your laptop \n"); // restart (+)
		Sleep(1);
		printf("date - shows real time and date \n"); // date (+)
		Sleep(1);
		printf("promo_code - using input promo code \033[0;33m(\033[0;37m promo code name \033[0;33m)\033[0;37m\n"); // promo_code (+)
		Sleep(1);
		printf("i_am_here - shows how much time did you spent here \n"); // i_am_here (+)
		Sleep(1);
		printf("&main - shows and hides start path \033[0;33m(\033[0;37m on, off \033[0;33m)\033[0;37m \n"); // &main (+)
		Sleep(1);
		printf("donate - donate specified amount of money for author \n"); // donate (+)
		Sleep(1);
		printf("donators - shows list of top 15 donators for author (updating every time with new version) \n"); // donators (+)
		Sleep(1);
		printf("helpers - shows list of top 15 helpers for author (updating every time with new version) \n"); // helpers (+)
		Sleep(1);
		//printf("color - set color text \033[0;33m("); // color (+)
		//printf("\033[0;37m color,\033[0;32m g\033[0;37m,\033[0;34m b\033[0;37m,\033[0;31m r\033[0;37m,\033[0;33m y\033[0;37m,\033[0;37m bl\033[0;37m, w,\033[0;35m p\033[0;37m,\033[0;36m wb \033[0;33m)\033[0;37m \n"); // colors (+)
		//Sleep(1);
		printf("color_back - set background color for console \033[0;33m("); // color_back (+)
		printf("\033[0;37m color,\033[0;32m g\033[0;37m,\033[0;34m b\033[0;37m,\033[0;31m r\033[0;37m,\033[0;33m y\033[0;37m,\033[0;37m bl\033[0;37m, w,\033[0;35m p\033[0;37m,\033[0;36m wb \033[0;33m)\033[0;37m \n"); // colors (+)
		Sleep(1);
		printf("i? - shows you are admin or user \n"); // i? (+)
		Sleep(1);
		printf("administrator \033[0;36mor \033[0;37madmin \033[0;36mor \033[0;37msuperuser - opens Dragon console as administrator \n"); // administrator (+)
		Sleep(1);
		printf("chan_backg - sets desktop background with entered full path to photo \033[0;33m(\033[0;37m path \033[0;33m)\033[0;37m\n"); // chan_backg (+)
		Sleep(1);
		//printf("send_ph_message - send message on entered phone number \n"); // send_ph_message (+)
		//Sleep(1);
		//printf("send_em_message - sends message on entered email \n"); // send_em_message (+)
		//Sleep(1);
		printf("history - shows all entered commands \n"); // history (+)
		Sleep(1);
		printf("cls_history - clear all entered commands \n"); // cls_history (+)
		Sleep(1);
		printf("memory - shows memory of your disks \n"); // memory (+)
		Sleep(1);
		printf("rules - shows rules of this console \n"); // rules (+)
		Sleep(1);
		printf("commands - shows commands only \n"); // commands (+)
		Sleep(1);
		printf("tips - shows tips only \n"); // tips (+)
		Sleep(1);
		printf("links - shows links only \n"); // links (+)
		Sleep(1);
		//printf("dragon_helper - will enter commands that you said, while you did't say 'exit' \n"); // dragon_helper (+)
		//Sleep(1);
		printf("my_volume_level - shows windows volume level \n"); // my_volume_level (+)
		Sleep(1);
		printf("set_volume_level - set windows volume level \033[0;33m(\033[0;37m number \033[0;33m)\033[0;37m\n"); // set_volume_level (+)
		Sleep(1);
		printf("set_mute - set windows mute \033[0;33m(\033[0;37m on, off \033[0;33m)\033[0;37m \n"); // set_mute (+)
		Sleep(1);
		printf("ip - shows your ip address \n"); // ip (+)
		Sleep(1);
		printf("size - set console size with entered parameters \033[0;33m(\033[0;37m x, y \033[0;33m)\033[0;37m\n"); // size (+)
		Sleep(1);
		printf("my_location - shows your location \n"); // my_location (+)
		Sleep(1);
		printf("system_info - shows info about pc \n"); // system_info (+)
		Sleep(1);
		printf("energy \033[0;36mor \033[0;37mpower - shows energy of pc \n"); // energy (+)
		Sleep(1);
		printf("\n");
		Sleep(1);
		printf("\033[0;33mPRANKS: \n"); // class PRANKS: (+)
		Sleep(1);
		printf("\n");
		Sleep(1);
		printf("\033[0;37mprank_button - shows prank with run away button \033[0;33m(\033[0;37m yes, no \033[0;33m)\033[0;37m \n"); // prank_button (+)
		Sleep(1);
		printf("melt_screen - shows melting screen, for exit from process press 'Alt + F4' \n"); // melt_screen (+)
		Sleep(1);
		printf("gdi_virus - shows gdi virus, for exit just wait or close program \n"); // gdi_virus (+)
		Sleep(1);
		printf("\n");
		Sleep(1);
		printf("\033[0;33mELSES: \n"); // class ELSES: (+)
		Sleep(1);
		printf("\n");
		Sleep(1);
		printf("\033[0;37mexit \033[0;36mor \033[0;37mesc \033[0;36mor \033[0;37mquit - exit from here \n"); // exit (+)
		Sleep(1);
		check_start_start();
}