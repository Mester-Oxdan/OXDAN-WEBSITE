#pragma once

#include <string>
#include <vector>
#include <ctime>
#include <queue>

using namespace std;

// functions:

void start_start(bool willstart);
string getCurrentTime();
void check_start_start();
void first_start();
void hideCursor();
void SetWindow(int xc, int yc);
void gotoxy(int x, int y);
void instructions();
bool containsSpaces_2(const string& str);
extern std::queue<std::string> commandQueue;
extern bool autoRunQueuedCommands;
extern std::queue<std::string> auto_commands;
extern bool auto_command_mode;

#ifdef OXIDAN_MAIN
string oxdan_dragon_c;
#else 
extern string oxdan_dragon_c;
#endif


// for Games:

void pacman_start();
void arkanoid_start();
void tetris_start();
void start_2048_start();
void guess_number_start();
void math_game_start();
void typing_tutor_start();
void hangman_start();
void flappybird_start();
void car_racing_start();
void mario_start();
void battle_city_start();
void space_shooter_start();

void tic_tac_toe_2_start();
void tic_tac_toe_ai_start();

void checkers_2_start();
void checkers_ai_start();

void chess_2_start();
void chess_ai_start();

void ping_pong_1_start();
void ping_pong_2_start();
void ping_pong_ai_start();

void snake_1_start();
void snake_2_start();
void snake_ai_start();

// for Own:

void color_start(string name);
void color_back_start(string name);
void main_start_start(string man, bool willstart);
void system_info_start();
void ip_start();
void memory_start();
void energy_start();
void send_ph_message_start();
void open_start(string path45);
void my_volume_level();
void my_location_start();
void ip_search_start();
void instructions_rules();
void commands_start();
void tips_start();
void links_start();
void helpers_start();
void donators_start();
void set_volume_level_start(string ma90n);

// for Pranks:

void prank_button_no();
void prank_button_yes();
void prank_melt_screen_start();
void gdi_virus_start();

// for Pictures:

void author_start();
void ukraine_start();
void matrix_start();

// for Hacker_Stuffs:

void inject_prog_start();
//void inject_prog_2_start();
void cor_desk_start();
void ascii_code_start();
void my_wifi_pas_start();
void auto_clicker_start();
void con_wifi_start();
void wifi_hack_start();
void pas_gen_w_start();
void pas_gen_u_start();
void pas_gen_n_start();
void pas_gen_nw_start();
void morse_code_start();
void initialize_morse_to_english();
void cuaser_cipher_start();

// for Main_commands:

void installs_start(string name);

// for Serious:

void timer_start();
void time_start();
void chat_start();
void d_price_calc_start();
void notepad_start();
void stopwatch_start();
void cur_conv_start();
void calendar_start();
void calculator_start();
int dictaphone_start();
void screen_recorder_start();
void webcam_recorder_start();
void screen_recorder_start();

// for Accounts:

void login();
void registration();
void del_account_start();
void my_accounts_start();

// Commands:

void Commands();

// Main_commands:

void Main_Commands();

// Games:

void Games();

// Pictures:

void Pictures();

// Elses:

void Elses();

// Accounts:

void Accounts();

// Serious:

void Serious();

// Hackerstuff:

void Hacker_Stuffs();

// Own:

void Own(bool willstart, clock_t timer, vector<string> &history);

// Pranks:

void Pranks();

extern vector<string> history;
extern string x;
extern string writex;
extern vector<string> tokens;
//extern string tokens;
extern wchar_t buf1[256];
std::wstring utf8_to_wstring(const std::string& str);