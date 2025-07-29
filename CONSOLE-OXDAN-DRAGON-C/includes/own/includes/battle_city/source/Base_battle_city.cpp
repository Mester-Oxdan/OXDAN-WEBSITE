#include "Base_battle_city.h"
#include "../../../all_diclarations.h"

Base::Base()
    
    : life(true) {

	string filePath = oxdan_dragon_c;
	vector<string> directories;

	// Split the path into directories and add them to the list
	size_t start = 0, end;
	while ((end = filePath.find("\\", start)) != string::npos) {
		string dir = filePath.substr(start, end - start);
		directories.push_back(dir);
		start = end + 1;
	}
	string lastComponent = filePath.substr(start);
	directories.push_back(lastComponent);

	// Keep track of the first and last words with spaces
	string firstSpaceWord;
	string lastSpaceWord;

	// Print the list of directories and detect first/last words with spaces
	//cout << "Original Path: " << filePath << endl;
	//cout << "List: ";
	for (const string& dir : directories) {
		//cout << "\"" << dir << "\" ";

		if (containsSpaces_2(dir)) {
			if (firstSpaceWord.empty()) {
				firstSpaceWord = dir;
			}
			lastSpaceWord = dir;
		}
	}
	//cout << endl;

	// Print the first and last words with spaces
	if (!firstSpaceWord.empty()) {
		//cout << "First word with spaces: " << firstSpaceWord << endl;
		//cout << "Last word with spaces: " << lastSpaceWord << endl;

		if (firstSpaceWord == lastSpaceWord)
		{

			// Replace spaces within the first and last words with double quotes
			size_t startPos = filePath.find(firstSpaceWord);
			size_t endPos = startPos + firstSpaceWord.length();
			string modifiedPath = filePath.substr(0, startPos) + "\"" + firstSpaceWord + filePath.substr(endPos);

			startPos = modifiedPath.find(lastSpaceWord);
			endPos = startPos + lastSpaceWord.length();
			modifiedPath = modifiedPath.substr(0, startPos) + lastSpaceWord + "\"" + modifiedPath.substr(endPos);


			// Print the modified path
			//cout << "Modified Path: " << modifiedPath << endl;
			string cmd_cmd = "start ";
			cmd_cmd += modifiedPath;
			system(cmd_cmd.c_str());
		}
		else
		{
			// Replace spaces within the first and last words with double quotes
			size_t startPos = filePath.find(firstSpaceWord);
			size_t endPos = startPos + firstSpaceWord.length();
			string modifiedPath = filePath.substr(0, startPos) + "\"" + firstSpaceWord + "\"" + filePath.substr(endPos);

			startPos = modifiedPath.find(lastSpaceWord);
			endPos = startPos + lastSpaceWord.length();
			modifiedPath = modifiedPath.substr(0, startPos) + "\"" + lastSpaceWord + "\"" + modifiedPath.substr(endPos);


			// Print the modified path
			//cout << "Modified Path: " << modifiedPath << endl;
			//string cmd_cmd = "start ";
			//cmd_cmd += modifiedPath;
			//system(cmd_cmd.c_str());

			mTexture.loadFromFile(modifiedPath + "/includes/own/includes/battle_city/media/baseSprite.png");
			mSprite.setTexture(mTexture);
			mSprite.setTextureRect(sf::IntRect(0, 0, 48, 48));
			mSprite.setPosition(336, 600);
		}
	}
	else {
		//cout << "No words with spaces found." << endl;
	}
    mTexture.loadFromFile(filePath + "/includes/own/includes/battle_city/media/baseSprite.png");
    mSprite.setTexture(mTexture);
    mSprite.setTextureRect(sf::IntRect(0, 0, 48, 48));
    mSprite.setPosition(336, 600);
}
