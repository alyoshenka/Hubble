#include "internetSpeed.h"

internetSpeed::internetSpeed(errorDisplay* errDisp) { 
	eDisp = errDisp;
	fnt = GetFontDefault();
	
	down = 199.99; 
	up = 9.99;
	updateTime = updateElapsed = 60 * 10; // 10 min
	setStr();
}

string internetSpeed::getCommand(string cmd){
	char buffer[128];
	string res = "";
	FILE * stream = popen(cmd.c_str(), "r");
	if(!stream){
		eDisp->addErrString("popen failed");
		std::cerr << "popen failed" << std::endl;
		
		return "";
	}
	
	// read to end
	while(!feof(stream)){
		if(NULL != fgets(buffer, 128, stream)) { res += buffer; }
	}
	
	pclose(stream);
	return res;
}

float internetSpeed::getFloatFromSpeed(const string line){
	
	string l = string(line);
	int i = l.find_first_of(' ');
	l = l.substr(i + 1);
	i = l.find_first_of(' ');
	l = l.substr(0, i);
	
	return std::stof(l);
}

string internetSpeed::getUpString(){
	// Upload: {speed} Mbit/s
	
	return getCommand(GET_UP_CMD);
}

string internetSpeed::getDownString(){
	// Download: {speed} Mbit/s
	
	return getCommand(GET_DOWN_CMD);
	
}

void internetSpeed::testUp(){
	up = getFloatFromSpeed(getUpString());
}

void internetSpeed::testDown(){
	down = getFloatFromSpeed(getDownString());
}

float internetSpeed::getUp(){ return up; }

float internetSpeed::getDown(){ return down; }

void internetSpeed::updateViaThread(){
	std::cout << "sending speed test async update" << std::endl;
	eDisp->addErrString("sending speedtest async update");
	
	fut = std::async(std::launch::async, [this]{
		this->testUp();
		this->testDown();
	});
}

void internetSpeed::update(float dt){
	// should this be running on every update?
	if(fut.valid()){
		try{
			std::future_status s = fut.wait_for(0ms);
			if(std::future_status::ready == s){
				fut.get();
				setStr();
				
				std::cout << "recieved new speed data" << std::endl;
				eDisp->addErrString("recieved new speed data");
			}
		}
		catch(const std::future_error& e){
			std::cerr << "future error: " << e.code() << std::endl;
			eDisp->addErrString("future error");
		}
	}	
	
	updateElapsed += dt;
	if(updateElapsed >= updateTime) { 
		updateElapsed = 0;
		updateViaThread(); 
	}
}

void internetSpeed::draw(){	
	//DrawText("DWN:", 405, 405, 20, A_GREEN_2);
	DrawTextRec(fnt, "DWN:", {405, 405, 50, 30}, 20, 1, false, A_GREEN_2);
	DrawText("UP:", 260, 405, 20, A_GREEN_2);
	
	DrawText(dStr.c_str(), 460, 415, 40, A_BLUE_1);
	DrawText(uStr.c_str(), 300, 415, 40, A_BLUE_1);
	
	DrawText("Mbps", 460, 455, 15, A_GREEN_1);
	DrawText("Mbps", 300, 455, 15, A_GREEN_1);
}

void internetSpeed::setStr(){
	std::stringstream uStream, dStream;
	uStream << std::fixed << std::setprecision(2) << up;
	dStream << std::fixed << std::setprecision(2) << down;
	uStr = uStream.str();
	dStr = dStream.str();
}
