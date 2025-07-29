#include "Bullet_battle_city.h"
#include "Map_battle_city.h"
#include "../../../all_diclarations.h"

Bullet::Bullet(const float &x, const float &y)
    : present(false), mX(x), mY(y), mDir(0), mDx(0.f), mDy(0.f), timeBeforeShot(0.f) {

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

			mTexture.loadFromFile(modifiedPath + "/includes/own/includes/battle_city/media/bulletSprite.png");
    mSprite.setTexture(mTexture);
    mSprite.setTextureRect(sf::IntRect(0, 0, 9, 12));
    mSprite.setPosition(x, y);
		}
	}
	else {
		//cout << "No words with spaces found." << endl;
	}
    mTexture.loadFromFile(filePath + "/includes/own/includes/battle_city/media/bulletSprite.png");
    mSprite.setTexture(mTexture);
    mSprite.setTextureRect(sf::IntRect(0, 0, 9, 12));
    mSprite.setPosition(x, y);
}

void Bullet::move(const sf::Int64 &time) {
    switch (mDir) {
        case 0:
            mDx = 0.3f;
            mDy = 0;
			mSprite.setRotation(90.f);
            break;

        case 1:
            mDx = -0.3f;
            mDy = 0;
			mSprite.setRotation(-90.f);
            break;

        case 2:
            mDx = 0;
            mDy = 0.3f;
			mSprite.setRotation(180.f);
            break;

        case 3:
            mDx = 0;
            mDy = -0.3f;
			mSprite.setRotation(0.f);
            break;
    }

    mX += mDx * time;
    mY += mDy * time;
	mSprite.setPosition(mX, mY);
}

void Bullet::update(Map &map, const sf::Int64 &time, float &x, const float &y, const int &dir) {
    if (present) {
        move(time);
        map_interaction(map);
    }
    else {
		mDir = dir;
        switch (mDir) {
        case 0:
            mX = x + 35.f;
            mY = y + 15.f;
            break;

        case 1:
            mX = x + 7.f;
            mY = y + 23.f;
            break;

        case 2:
            mX = x + 23.f;
            mY = y + 32.f;
            break;

        case 3:
            mX = x + 15.f;
            mY = y + 5.f;
            break;
        }
		mSprite.setPosition(mX, mY);
    }
}

void Bullet::map_interaction(Map &map) {
    for (int i = mY / 24; i < (mY + 12) / 24; ++i)
        for (int j = mX / 24; j < (mX + 9) / 24; ++j) {
            char tile = map.get_tile(i, j);

            if (tile == '0' || tile == '2' || tile == '@')
                present = false;

            if (tile == '3' || tile == '%')
                present = true;

            if (tile == '1' || tile == '#') {
                map.break_wall(i, j);
                present = false;
            }
        }
}
