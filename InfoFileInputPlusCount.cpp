#include "pch.h"
#include <cctype>
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <limits>



//to count no of Archers in the contest
//input:filename:the name of the TargetAssognment file
//output:the number of archers
int Count_no_of_archer(string filename) {
	ifstream file;
	char check;
	bool checkconsecutivenewline=false;//to avoid the case that the target assignment have empty line in the middle of the file but the function still count it as a new archer

	int temp = 0;
	file.open(filename);
	while (file) {
		file.get(check);


		if (check == '\n'){//theoretically,one archer occupy one line

		  if (checkconsecutivenewline==false){



			temp++;
		  }



			checkconsecutivenewline=true;

		}


		else if (isalnum(check)) {//to check if the the line is empty
		  checkconsecutivenewline=false;


		}



	}
	file.close();

	file.open(filename.c_str());
	if (file.fail()) {
		cout << "Count Error in file opening!" << endl;
		exit(1);
	}
	file.close();
	temp--;



	cout << "Number of Archers: " << temp<<endl;
	return temp;
}
//to open the file and store the archer's information in the dynamic array
//input:No_of_archer: no of archers
//      a: the pointer of the dynamic array that are going to store archer's information
//      fileopen:a bool to show whether the file is opened successfully
void fileopening_and_call_Count_no_of_archer(int &No_of_archer, Archer_info *&a, bool &fileOpen) {
		string TargetAssignment_CSV,dummy;
	cout << "Please close the target assignment file(eg.TargetAssignment.csv)" << endl;
	cout << "Input the filename(eg.TargetAssignment.csv)" << endl;
	cin >> TargetAssignment_CSV;

	int j = 0;

	ifstream fin;
	fin.open(TargetAssignment_CSV.c_str());
	if (fin.fail()) {

		cout << "Error in targetassignment.csv opening!" << endl;
		fileOpen = false;
	}
	fin.close();
	if (!fileOpen) {
		goto end;
	}
	else {
		No_of_archer = Count_no_of_archer(TargetAssignment_CSV);

		a = new Archer_info[No_of_archer];

		string archerinfo;
		fin.open(TargetAssignment_CSV.c_str());

		getline(fin, archerinfo);
		while (getline(fin, archerinfo)) {
			stringstream ss;
			ss << archerinfo;//each archer has one archer info stringstream
			string item;
			int i = 0;
			while (getline(ss, item, ','))//each item represent one item of a particular archer(e.g.name,division)
			{
			  switch (i) {//each line contain five kind of infomation of archer
				case 0: a[j].Target_Number = item;

				  Errorchecking_Target_Number(item, i, j);// all errorchecking function is used to check if a particular input of a particular archer is valid or not

					break;
				case 1: a[j].name = item;

					Errorchecking_name(item, i, j);

					break;
				case 2: a[j].HKAA_Archer_number = item;

					Errorchecking_HKAA_Archer_number(item, i, j);

					break;
				case 3: a[j].HKAA_Affiliated_Organization = item;

					Errorchecking_HKAA_Affiliated_Organization(item, i, j);

					break;
				case 4: a[j].Coach_name = item;

				  if (item != "NA") {//there are some archers that do not have a coach
						Errorchecking_name(item, i, j);
					}

					break;
				case 5: a[j].Division = item;
					string temp = "";

					for (int k = 0;k < item.length();k++) {//this for loop is used to remove the extra spacing(if any)in the division

						if (isalpha(item[k])) {
							temp += item[k];
						}

					}
					item = temp;
					a[j].Division = temp;


					Errorchecking_Division(item, i, j);

				}
				i++;
			}


			j++;

		}
		fin.close();
	}
	//count the no of line(no of archers)in the input file and generate the dynamic array
	////////////////////////////////////////////////////////////////////
	cout << "File is opened successfully" << endl;
	cout << "Please input something to confirm!";
	cin>>dummy;
end:;


}
