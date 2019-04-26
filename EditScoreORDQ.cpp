#include "pch.h"
#include <cctype>
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>

//Function Description
//To iterate all the elements inside "a" so as to search for the "target"
//Input: a:Archer_info
//		 no_of_archer: required for iterating through all elements
//		 target: the target string that the user wants to search for
//		 index: true:search by Target Number (not implemented) false:search by Name
//		 pos: the position of that found element in the array "a" (initialized as -1)
//Output: return true+the corresponding "pos" if target is found
//		  return false if target is not found
bool LinearSearchByIndexOrName(Archer_info *a, int no_of_archer, string target, bool index, int *pos) {
	bool found = false;
	//index=True -> Search by Archer Number
	if (index) {
		for (int i = 0; i < no_of_archer; i++) {
			if (a[i].Target_Number == target) {
				*pos = i;
				found = true;
				break;
			}
		}
	}
	//index=True -> Search by Name (Not Implemented)
	else {
		for (int i = 0; i < no_of_archer; i++) {
			if (a[i].name == target) {
				*pos = i;
				found = true;
				break;
			}
		}
	}
	return found;


	// return a vector???


}

//Function Description
//This fuction is used to edit the score of a particular archer or DQ a particular archer
//Input: (It is self-explainatary)
//Output: To always return true to CLI function so as to indicate that this function is executed successfully
//        Update the corresponding field of the record chosen (a.rank + a. raw score)
bool EditRecordScoreOrFile(Archer_info *a, int no_of_archer) {
	string target = "";
	string temp = "",dummy;
	bool index = true;
	int pos = -1;
	//After this line, the program enters another command line interface page
	while (target != "Exit" && target != "exit") {
		temp = "";
	InputTarget:;
		cout << "Edit wt target number(Back)?";
		cin >> target;
		if (target == "back" || target == "Back") {
			temp = "";
			return true;
		}
		//After receiving the target, LinearSearchByIndexOrName will be called to search if that target number exists
		if (LinearSearchByIndexOrName(a, no_of_archer, target, index, &pos)) {
			//if it exists, Ask to change score or DQ him/her and then conduct the corresponding operation
			cout  << "Target Number | Name :" << a[pos].Target_Number<<" "<<a[pos].name<<endl<<endl;
			cout << "Edit Score Or DQ? (S / DQ / Back)";
			cin >> temp;
			if (temp == "Back") {
				goto InputTarget;
			}
			else if (temp == "DQ") {
				a[pos].rank = "DQ";
				goto InputExit;
			}
			else if (temp == "S" || temp == "s") {
				int row = -1, col = -1;
				cout << "Target Number | Name " << endl;
				DisplayRawScore(a[pos]);
				temp = "";
				cin.ignore();
			InputRow:;
				if (!(temp == "")) {
					cout << "Wrong Input Try Again"<<endl;
				}
				cout << "Edit which row(0-11)";
				getline(cin, temp);
				if (CheckAllInteger(temp)&& temp.length()<=2) {
					row = stoi(temp);
					if (!(row >= 0 && row <= 11)) {
						cout << "Please input a range between 0-11" << endl;
						goto InputRow;
					}
				}
				else {
					goto InputRow;
				}
				temp = "";
			InputCol:;
				cout << "Edit which column(0-5)";
				getline(cin, temp);
				if (CheckAllInteger(temp)&& temp.length() <= 2) {
					col = stoi(temp);
					if (!(col >= 0 && col <= 5)) {
						cout << "Please input a range between 0-5" << endl;
						goto InputCol;
					}
				}
				else {
					goto InputCol;
				}
				temp = "";
				string c_score = " ";
			InputScoreChange:;
				if (c_score == "") {
					cout << "The input is wrong. Try Again!";
				}
				cout << "What is the value to be replaced? (1-10/M/X)";
				cin >> temp;
				if (temp.length() == 2 && temp == "10") {
					c_score = "10";
				}
				else if (temp.length() == 1) {
					if (temp[0] >= '1' && temp[0] <= '9') {
						c_score = temp[0];
					}
					else if (temp[0] == 'M' || temp[0] == 'm') {
						c_score = temp[0];
					}
					else if (temp[0] == 'X' || temp[0] == 'x') {
						c_score = temp[0];
					}
					else c_score = "";
				}
				if (c_score == "") {
					goto InputScoreChange;
				}
				if (row <= 5) {
					a[pos].score.Score_raw.First_distance[row][col] = c_score;
				}
				if (row >= 6) {
					a[pos].score.Score_raw.Second_distance[row - 6][col] = c_score;
				}
				DisplayRawScore(a[pos]);
			}
		InputExit:;
			cout << "It is edited successfully" << endl;
			cout << "Exit?(Y/N)";
			cin >> temp;
			if (temp == "Y" || temp == "y") {
				target = "Exit";
			}
			else if (temp == "N" || temp == "n") {
			}
			else {
				cout << "Wrong Input. Try Again" << endl;
				goto InputExit;
			}
		}
		else {
			cout << "The request record cannot be searched. Try again" << endl;
			goto InputTarget;
		}
	EndWhile:;
	}
	//To update the score
	cout<<"Process Score"<<endl;
	Process_Score(no_of_archer, a);
	return true;
}
