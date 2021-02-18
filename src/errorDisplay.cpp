#include "errorDisplay.h"

errorDisplay::errorDisplay(){
	errStrCnt = errStrIdx = 0;
	errStrArr = new string[dispNum];
}

errorDisplay::~errorDisplay() { delete[] errStrArr; }

bool errorDisplay::addErrString(string errString){	
	errStrArr[errStrIdx] = errString;
	errStrIdx++;
	if(errStrIdx >= dispNum) { errStrIdx -= dispNum; }
	if(errStrCnt < dispNum) { errStrCnt++; }
	return true;
}

void errorDisplay::draw()
{
	// 30, 90, 540, 290
	DrawRectangle(30, 90, 540, 290, BLACK);
	
	for(int i = 0; i < errStrCnt; i++){
		int idx = errStrIdx - i - 1;
		if(idx < 0) { idx += dispNum; }		
        DrawText(errStrArr[idx].c_str(), 40, 100 + i * 20, 15, GREEN);
	}
}
