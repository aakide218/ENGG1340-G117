#include "pch.h"
#include <cctype>
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
//the main function of the whole program
int main()
{
	string dummy;
	int No_of_archer = 0;
	Archer_info *a = nullptr;
	bool fileOpening, dependencylist[4];
	int command;

InfoFileInput:;
	fileOpening = true;

	fileopening_and_call_Count_no_of_archer(No_of_archer, a, fileOpening);
	if (!fileOpening) {
		goto InfoFileInput;
	}

	//need to change the dependency list
	dependencylist[0] = true;
	dependencylist[1] = true;
	dependencylist[2] = true;
	dependencylist[3] = true;
	CLI(a, No_of_archer, dependencylist);




	/*readscore(a, No_of_archer);


	Process_Score(No_of_archer, a);
	//EditRecordScoreOrFile(a, No_of_archer);
	GiveRank(a, No_of_archer);
	GenerateArcherResult(a, No_of_archer);*/

	delete [] a;

}
