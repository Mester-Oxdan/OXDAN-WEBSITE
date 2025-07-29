#include <windows.h>
#include <conio.h>
#include <iostream>
#include <SFML/Audio.hpp>
#include "all_diclarations.h"

#pragma warning(disable : 4996).
#pragma comment(lib, "winmm.lib") // Link with the Windows Multimedia library

void author_start()
{
	system("cls");
	system("mode 183, 23"); // set size of console (+)
	SetWindow(141, 29); // set buffer size of console (+)

	printf("                                                                                                                                                                                       ");
	Sleep(30);
	printf("\033[0;33m        @@@BY!^:::^!YB@@@         :!!!~           ^!!!^       @J!!!!!!!!!77J5G&@                  @&###&@                Y@@@@@@P           G@@@@Y          @GYYYYYYYY555PB@           ");
	Sleep(30);
	printf("      @@@G~           ~G@@@        J&@@G^        Y&@@P^       @~              :7B@               @5.....Y@               Y@@    @B^         G@@@@Y          @7             ^5@         ");
	Sleep(30);
	printf("     @@@5    :JPGPJ:    5@@@        ^P@@&J     !#@@#!         @!    5GGGPPJ!     Y@             @B.      G@              Y@@@  @@@#~        G@@@@Y          @P      :7^      P@        ");
	Sleep(30);
	printf("    @@@&    ^&     &^    &@@@         7#@@B~ :P@@@Y           @!   .#       B^    P@           @&^   :   :&@             Y@@@@&@@@@@7       G@@@@Y           @:     7@&.     ?@        ");
	Sleep(30);
	printf("    @@@&    ^&     &^    &@@@          :5@@@P#@@B~            @!   .#        G    ~@          @@7   :B:   !@@            Y@@@@G!&@@@@J      G@@@@Y           @:     7@@:     ?@        ");
	Sleep(30);
	printf("     @@@5    :JPGPJ:    5@@@             !&@@@@J              @!   .#        &    ^@         @@5    P@5    Y@@           Y@@@@G ~#@@@@Y     G@@@@Y           @:     ^Y!      5@        ");
	Sleep(30);
	printf("      @@@G~           ~G@@@             ^P@@@@@P^             @!   .#        B    ~@        @@B.   ?@@@?    G@@          Y@@@@G  :B@@@@P    G@@@@Y           @:             ?@         ");
	Sleep(30);
	printf("\033[0;31m        @@@BY!^:::^!YB@@@              ?&@@G!G@@&?            @!   .#       #~    P@       @@&^    !777!    :&@@         Y@@@@G    P@@@@B:  G@@@@Y           @:     ^?77?J5B@          ");
	Sleep(30);
	printf("                                     ~G@@&?   ?&@@G~          @!    5GGGGG57.   .5@       @@@7               !@@@        Y@@@@G     Y@@@@#~ G@@@@Y          @P.     ^&@                ");
	Sleep(30);
	printf("                                    Y@@@P:     ^P@@@Y         @~              :7B@       @@@5    ?PPPPPPP?    Y@@@       Y@@@@G      J@@@@&!G@@@@Y          @7       5@                ");
	Sleep(30);
	printf("                                  !B@@#7         7#@@#!       @J!!!!!!!!!!7?YG&@        @@@B    !@       @~    G@@@      Y@@@@G       7@@@@@&@@@@Y          @GYYYYYYY#@   @@@@         ");
	Sleep(30);
	printf("                                  !!!!:           :!!!!                                @@@@BYYY5&@       @#5YYYB@@@@     Y@@@@G        ~#@@@    @Y                       @@  @@        ");
	Sleep(30);
	printf("                                                                                                                         Y@@@@G         ^B@@@  @@Y                        @@@@         ");
	Sleep(30);
	printf("                                                                                                                         Y@@@@G           P@@@@@@Y                                     ");
	Sleep(30);
	printf("\033[0;37m                                                                                                                                                                                       ");
	Sleep(30);
	printf("                                                                                       <^BY OXDAN PRADUCTION!^>                                                                        ");
	Sleep(30);
	printf("\n");

	string filepath = (oxdan_dragon_c + "\\includes\\own\\undertale.wav");
	sf::SoundBuffer buffer;
	buffer.loadFromFile(filepath);  // Change to your audio file path

	// Create a sound instance and set the buffer
	sf::Sound sound;
	sound.setBuffer(buffer);

	// Play the sound
	sound.play();
	getch();
	system("mode 148, 29"); // set size of console (+)
	SetWindow(141, 29); // set buffer size of console (+)
	check_start_start();
}