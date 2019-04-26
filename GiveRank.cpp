#include "pch.h"
#include <cctype>
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>

//(that is obvious)
void SwapInt(int &a, int &b) {
	int temp = a;
	a = b;
	b = temp;
}

//Function Description
//To return the array position range of "division" in "a"
//Input: a: archer info
//		 lower: the lower range of the mentioned position range
//		 upper: the upper range of the mentioned position range
//		 start: the starting position of the next ReturnDivisionRange
//		 no_of_archer: number of archers for iteration
//		 division: the division to be checked
//Output: update lower,upper,start
void ReturnDivisionRange(Archer_info *a, int &lower, int &upper, int &start, int no_of_archer, string division) {
	int i = start;
	lower = start;
	while (start <= no_of_archer) {
		if (!(a[i].Division == division)) {
			break;
		}
		i++;
	}
	start = i;
	i--;
	upper = i;
}

//Function Description
//Return the "change" (see the description)
//Input: a: Archer Info
//		 lower: lower range of the array "a" to be checked
//		 upper: upper range of the array "a" to be checked
//		 no_of_archer: number of archer for iteration
//		 change: Division | position | position | ... | "-1" | Division | position ...
//			Division: Indicate the following "position" is from which division
//			Position: Indicate the position of the element. They are arranged the descending order
//Output: return vector "change"
vector <string> DivisionRank(Archer_info *a, int lower, int upper, int no_of_archer, vector <string> change) {
	int *listnumber = NULL;
	int temp = upper - lower + 1, targetindex = -1, max = -1;
	listnumber = new int[temp];
	stringstream ss;
	bool state = false;
	//intitialize listnumber
	for (int i = 0;i < temp;i++) {
		listnumber[i] = i + lower;
	}
	//Implement selection sort
	
	for (int i = 0; i < temp; i++) {
		targetindex = 0;
		max = a[0].rankWeight;
		state = true;
		for (int j = 0;j < temp - i;j++) {
			if (max < a[listnumber[j]].rankWeight) {
				targetindex = j;
				max = a[listnumber[j]].rankWeight;
				state = true;
			}
		}
		if (state) {
			cout <<"Swap"<<targetindex << " " << temp - i - 1;
			SwapInt(listnumber[targetindex], listnumber[temp - i - 1]);
		}
	}
	//Append listnumber in descending order to the back of the vector "change" 
	for (int i = temp - 1;i >= 0;i--) {
		ss << listnumber[i];
		//cout << "ss.str" << ss.str() << endl;
		change.push_back(ss.str());
		ss.str("");
	}
	change.push_back("-1");
	delete[] listnumber;
	return change;
}

//Function Description
//To give rank to each archer according to the processed score
//Input: (self-explained)
//Output: Update the "a" correspondingly
void GiveRank(Archer_info *a, int no_of_archer) {
	vector <string> rank;
	//Format: Division->Index->Index->Index0->"-1"->Division->...
	int lowerRange = 0, upperRange = 0, start = 0, count = 0, check = -1, eqpos = -1;
	const string matchstring = "RBM RBW REM REW RIM RIW RAM RAW";
	stringstream s(matchstring);
	string checkdivision, temp;
	bool state = false;
	//Suppose there must be 8 division
	//content in rank: Division | position | position | ... | "-1" | Division | position ...
	//Division: Indicate the following "position" is from which division
	//Position: Indicate the position of the element. They are arranged the descending order
	for (int i = 0;i <= 7;i++) {
		s >> checkdivision;
		ReturnDivisionRange(a, lowerRange, upperRange, start, no_of_archer, checkdivision);
		rank.push_back(checkdivision);
		rank = DivisionRank(a, lowerRange, upperRange, no_of_archer, rank);
	}
	//To unpack rank into a.rank
	for (vector <string>::iterator it = rank.begin(); it != rank.end(); it++) {
		temp = *it;
		//Check if the one iterated is division
		if (isalpha(temp[0])) {
			count = 1;
			continue;
		}
		else if (temp == "-1") {
			eqpos = -1;
			continue;
		}
		else {
			if (eqpos == -1) {
				goto Assignrank;
			}
			//check if the checked one and the one being checked have the same rank
			if (a[eqpos].rankWeight == a[stoi(temp)].rankWeight) {
				// check if the one being checked is DQ
				if (a[stoi(temp)].rank == "DQ") {
					cout << a[stoi(temp)].Target_Number<<" DQ"<<endl;
					continue;
				}
				count--;
				a[stoi(temp)].rank = to_string(count);
				count++;
				count++;
			}
			else {
			Assignrank:;
				if (a[stoi(temp)].rank == "DQ") {
					cout << a[stoi(temp)].Target_Number << " DQ" << endl;
					continue;
				}
				a[stoi(temp)].rank = to_string(count);
				eqpos = stoi(temp);
				count++;
			}

		}
	}
}