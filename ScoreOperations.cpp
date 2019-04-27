#include "pch.h"
#include <cctype>
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <iomanip>

//Function Description
//Analyze the score "i" the element in Archer_info array "a" in the raw score structure array in [j][k] position
//	To update the corresponding value in the Archer_info array "a"
//Input: a: the Archer information array
//		 i: to analyze i th element in array "a"
//		 j: refer to the jth row in the 2D array for raw score
//		 k: refer to the kth col in the 2D array for raw score
//		 state: True: it is in the first distance of shooting | False: in the second distance of shooting
//Output: update the corresponding value in the Archer_info array "a"
void Raw_Score_Interpret(Archer_info *a, int i, int j, int k, bool state) {
	string temp;
	if (state) {
		temp = a[i].score.Score_raw.First_distance[j][k];
	}
	else {
		temp = a[i].score.Score_raw.Second_distance[j][k];
	}
	if ((temp == "X" || temp == "x")) {
		a[i].score.Total_10_plus_x++;
		if (state) {
			a[i].score.Total_score_for_1st_distance += 10;
		}
		else {
			a[i].score.Total_score_for_2nd_distance += 10;
		}
	}
	else if (temp == "10") {
		a[i].score.Total_10++;
		a[i].score.Total_10_plus_x++;
		if (state) {
			a[i].score.Total_score_for_1st_distance += 10;
		}
		else {
			a[i].score.Total_score_for_2nd_distance += 10;
		}
	}
	else if (temp == "M" || temp == "m") {
		//nothing is needed to be done
	}
	else {
		int temp;
		if (state) {
			temp = a[i].score.Score_raw.First_distance[j][k][0] - '0';
			a[i].score.Total_score_for_1st_distance += temp;
		}
		else {
			temp = a[i].score.Score_raw.Second_distance[j][k][0] - '0';
			a[i].score.Total_score_for_2nd_distance += temp;
		}
	}
}

//Function Description
//To extract and analyze the raw score.
//Then, store them back to the corresponding element in the Archer Info struct
//Input: num_archers:number of archers for iteration
//		 a: the array that store all Archer information
//Output: update the archer info
void Process_Score(int num_archers, Archer_info *a) {
	bool state = false;
	int first_distance = 0;
	for (int i = 0;i < num_archers;i++) {
		a[i].score.Total_score = 0;
		a[i].score.Total_score_for_1st_distance = 0;
		a[i].score.Total_score_for_2nd_distance = 0;
		a[i].score.Total_10 = 0;
		a[i].score.Total_10_plus_x = 0;
		a[i].rankWeight = 0;
	}
	for (int i = 0; i < num_archers;i++) {
		for (int j = 0; j < 6;j++) {
			for (int k = 0; k < 6; k++) {
				Raw_Score_Interpret(a, i, j, k, true);
			}
		}
		for (int j = 0; j < 6;j++) {
			for (int k = 0; k < 6; k++) {
				Raw_Score_Interpret(a, i, j, k, false);
			}
		}
		a[i].score.Total_score = a[i].score.Total_score_for_1st_distance + a[i].score.Total_score_for_2nd_distance;
		//Priority of weighting:
		//Total Score -> Number of 10+X -> Number of X
		//This is used to prepare for the multi layer sorting for ranking
		a[i].rankWeight = a[i].score.Total_score * 10000 + a[i].score.Total_10_plus_x * 100 + (a[i].score.Total_10_plus_x - a[i].score.Total_10);
		cout << "Target Number" << a[i].Target_Number << " " << a[i].rankWeight << endl;
	}
}
//Function Description
//To display the inputted score of an archer
//Input: a: the archer information that are going to be displayed
//Output: print the raw score out
void DisplayRawScore(Archer_info a) {
	cout << a.Target_Number << " " << a.name << endl;
	cout << "###########################################" << endl;
	cout << "First Distance" << endl;
	for (int i = 0; i < 6;i++) {
		cout << "Row " << setw(2) << i << ": |";
		for (int j = 0; j < 6;j++) {
			cout <<setw(2)<< a.score.Score_raw.First_distance[i][j] << " ";
		}
		cout << endl;
	}
	cout << "###########################################" << endl;
	cout << "Second Distance" << endl;
	for (int i = 0; i < 6;i++) {
		cout << "Row " <<setw(2) << i + 6 << ": |";
		for (int j = 0; j < 6;j++) {
			cout <<setw(2)<< a.score.Score_raw.Second_distance[i][j] << " ";
		}
		cout << endl;
	}
	cout << "###########################################" << endl;
	cout << endl << endl;
}

//Function Description
//to read the score file of each archers
//input:a:the pointer of the dynamic array that store archers' info
//      No_of_archer: the number of arhcers
//output:it return true if it successfully read the score file
bool readscore(Archer_info *a, int No_of_archer) {
	bool success = true;
	string dummy = "";
	for (int i = 0;i < No_of_archer;i++) {
		//generatetemplatefile(a,i);
		int no_of_score_distance1 = 0;
		int no_of_score_distance2 = 0;
		int line_no_in_the_file = 1;
		ifstream fin;

		string temp = (a[i].Target_Number + ".csv").c_str();
		//cout << "Inputting Score files" << endl;
		fin.open(temp);

		if (fin.fail()) {
			cout << a[i].Target_Number << endl;
			cout << "Read Error in file opening!" << temp << endl;
			success = false;
			fin.close();
			goto End;
		}
		string archer_score;
		int b = 0;
		getline(fin, archer_score);
		getline(fin, archer_score);
		string item = "";
		for (int b = 0;b <= 5;b++) {

			getline(fin, archer_score);
			stringstream ss(archer_score);
			int k = 0;
			while (getline(ss, item, ',')) {
				string temp = "";

				for (int k = 0;k < item.length();k++) {
					if (isalnum(item[k])) {
						temp += item[k];
					}
				}

				if (errorchecking_score(temp) == 0) {
					cout << a[i].Target_Number << ".csv" << " row " << b << " column " << k << endl << endl;;
				};
				a[i].score.Score_raw.First_distance[b][k] = temp;
				k = k + 1;

				no_of_score_distance1++;
			}

		}
		if (no_of_score_distance1 != 36) {
			cout << a[i].Target_Number << " " << a[i].name << " miss some scores in the first distance" << endl;
			success = false;
		}

		getline(fin, archer_score);
		item = "";
		for (int b = 0;b <= 5;b++) {
			getline(fin, archer_score);
			stringstream ss(archer_score);
			int k = 0;
			while (getline(ss, item, ',')) {
				string temp = "";

				for (int k = 0;k < item.length();k++) {
					if (isalnum(item[k])) {
						temp += item[k];
					}
				}
				if (errorchecking_score(temp) == 0) {
					cout << a[i].Target_Number << ".csv" << " row " << b+5 << " column " << k << endl << endl;;
				};
				a[i].score.Score_raw.Second_distance[b][k] = temp;
				k = k + 1;
				no_of_score_distance2++;
			}
		}
		if (no_of_score_distance2 != 36) {
			cout << a[i].Target_Number << " " << a[i].name << " miss some scores in the second distance" << endl;
			success = false;
		}
		fin.close();
	}
End:;
	if (!success) {
		cout << "Please correct the abovementioned errors and then reexecute function2 again"<<endl;
		cout << "Please enter something to confirm.";
		cin >> dummy;
	}
	return success;
}
