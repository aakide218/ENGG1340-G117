#include "pch.h"
#include <time.h> 
#include <cctype>
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>

 

using namespace std;

//(that is obvious)
//since c++ does not have a particular good function to clear'
//we have to implement it like this
void ClearScreen() {
	for (int i = 0;i <= 99;i++) {
		cout << endl;
	}
}

//it is developed for debugging
void wait(int seconds)
{
	clock_t endwait;
	endwait = clock() + seconds * CLOCKS_PER_SEC;
	while (clock() < endwait) {}
}

//Function Description
//This is the main command line interface (CLI) for the program
//This interface alows user to choose the belowmentioned function
//Input: a: Archer infomation array
//		 No_of_archer: the number of archer
//		 dependencylist: it is used to indicate if a particular function(only usefu to functions 3 and 4) is allowed to be executed
//				false: allow to be executed
//				true: not allow to be executed
//Output: (Depends on what functions are executed)
//		 return string (dummy)
string CLI(Archer_info *a, int No_of_archer, bool dependencylist[]) {
	string command="-1", TargetAssignment_CSV,dummy;
	bool returntomenu = false, success=true;
MainMenu:;
	ClearScreen();
	returntomenu = false;
	if (success && !(command=="-1")) {
		if (command=="0" || command=="1" || command == "2" || command == "3" || command == "4") {
			cout << "Function " << command << " is executed sucessfully" << endl;
		}
	}
	cout << "##################################" << endl;
	cout << "HKUSU Archery Club Scoring System" << endl;
	cout << "0: Update the target assignment file" << endl;
	cout << "1: Generate template score file" << endl;
	cout << "2: Input the score files"<<endl;
	cout << "3: Edit Score" << endl;
	if (dependencylist[2]) {
		cout << "(Execute function 2 first)"<<endl;
	}
	else {
	//empty (used for debugging)
	}
	cout << "4: Generate the archer result" << endl;
	if (dependencylist[3]) {
		cout << "(Execute function 2 first)" << endl;
	}
	else {
	//empty (used for debugging)
	}
	cout << "##################################" << endl;
	cout << "Input your command (Exit)";
	cin >> command;
	if (command == "0") {
		fileopening_and_call_Count_no_of_archer( No_of_archer, a, success);
		if (!success) {
			cout << "Cannot open " << TargetAssignment_CSV << endl;
			cout << "Please enter something  to confirm ";
			cin>>dummy;
		}
		returntomenu = true;
	}
	else if (command == "1") {
		success = true;
		cout << "####Warning####"<<endl;
		cout << "This function will overwrite all the existing score file" << endl;
	WarningTemplate:;
		cout << "Execute this function?(Y/N)";
		cin >> dummy;
		if (dummy == "N" || dummy == "n") {
			success = false;
		}
		else if (dummy == "Y" || dummy == "y") {
			for (int i = 0;i < No_of_archer;i++) {
				if (!generatetemplatefile(a, i)) {
					success = false;
					cout << "Please reexecute this function" << endl;
					break;
				}
			}
		}
		else {
			cout << "Wrong Input" << endl;
			cout << "Please try again" << endl;
			goto WarningTemplate;
		}
		returntomenu = true;
	}
	else if (command == "2") {
		success=readscore(a, No_of_archer);
		if (success) {
			dependencylist[2] = false;
			dependencylist[3] = false;
		}
		returntomenu = true;
	}
	else if (command == "3") {
		if (!dependencylist[2]) {
			success=EditRecordScoreOrFile(a,No_of_archer);
			returntomenu=true;
		}
		else {
			cout << "Execute function 2 first"<<endl;
			cout << "Please input something to confirm ";
			cin >> dummy;
			success = false;
			returntomenu = true;
		}
	}
	else if (command == "4") {
		if (!dependencylist[3]) {
			success=GenerateArcherResult(a, No_of_archer);
			returntomenu = true;
		}
		else {
			cout << "Execute function 2 first" << endl;
			cout << "Please input something to confirm ";
			cin >> dummy;
			success = false;
			returntomenu = true;
		}
	}
	else if (command == "Exit" || command == "exit") {
		returntomenu = false;
	} 
	else {
		cout <<"Wrong Command input"<<endl;
		cout << "Try again" << endl;
		returntomenu = true;
	}
	if (returntomenu) {
		goto MainMenu;
	}
	return command;
}