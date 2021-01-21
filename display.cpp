#include "display.h"



display::display(int w, int h) 
{ 
	timeString = "time";
	faceBorder = 10;
	faceSize = 200 - faceBorder * 2;
	facePos.x = w - faceSize - faceBorder;
	facePos.y = h - faceSize - faceBorder;	

	setMood(happy);
}

display::~display() { UnloadTexture(faceTex); }

void display::setMood(mood newMood)
{
	std::cout << "Setting mood: " << stringMood[int(newMood)] << std::endl;
	currentMood = newMood;
	UnloadTexture(faceTex); 
	std::string num = std::to_string((int)currentMood + 1);
	std::string fileName = facesDir + "sansf" + num + ".png";
	Image img = LoadImage(fileName.c_str());
	ImageResize(&img, faceSize, faceSize);
	faceTex = LoadTextureFromImage(img);
	UnloadImage(img);
}

void display::setMood(string newMood){
	// optimize, no MNs
	for(int i = 0; i < 16; i++){
		std::cout << stringMood[i] << "=" << newMood << std::endl;
		if(stringMood[i].compare(newMood) == 0){				
			setMood(i);
			return;
		}
	}
	std::cout << "No mood matches " << newMood << std::endl;
}

void display::setMood(int newMood){
	if(newMood > 15){
		std::cout << "No mood matches " << std::to_string(newMood) << std::endl;
	} else {
		setMood((mood)newMood);
	}
}

void display::update(float frameTime)
{
	std::time_t now = time(0);
	tm* local = localtime(&now);

	int h = local->tm_hour;
	int m = local->tm_min;
	int s = local->tm_sec;

	timeString = "";
	if (h < 10) { timeString += "0"; }
	timeString += std::to_string(h) + ":";
	if (m < 10) { timeString += "0"; }
	timeString += std::to_string(m) + ":";
	if (s < 10) { timeString += "0"; }
	timeString += std::to_string(s);
	
	if(IsKeyPressed(KEY_W)){setMood("wink");}
	if(IsKeyPressed(KEY_H)){setMood(0);} // happy
}

void display::draw()
{
	DrawText("HUBBLE", 10, 10, 70, A_BLUE_3);
	// DrawText(FACE_AT, 320, 320, 160, A_BLUE_4);
	DrawText(timeString.c_str(), 10, 410, 60, A_GREEN_2);

	DrawTexture(faceTex, facePos.x, facePos.y, WHITE);
	
	// drawLayoutDebug();
}

void display::drawLayoutDebug()
{
	// hubble
	DrawRectangleLines(0, 0, 300, 80, WHITE);
	// alert icons
	DrawRectangleLines(300, 0, 300, 80, WHITE);
	// temp data
	DrawRectangleLines(600, 0, 200, 280, WHITE);
	// face
	DrawRectangleLines(600, 280, 200, 200, WHITE);
	// time & speed
	DrawRectangleLines(0, 400, 600, 80, WHITE);
}



