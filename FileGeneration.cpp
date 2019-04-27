#include "pch.h"
#include <cctype>
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>

//Function Description
//This function will generate the template score files
//Input: a: Archer Information
//		 no_of_archer: number of archer for iteration
//Output: Template Score files
bool generatetemplatefile(Archer_info *a, int i) {
	ofstream fout;
	bool success = true;
	string templatefile_name = a[i].Target_Number + ".csv";
	fout.open(templatefile_name.c_str());
	if (fout.fail()) {
		cout << a[i].Target_Number << ".csv cannot be created.";
		//cout << "Template Error in file opening!" << endl;
		cout << "Press Enter to confirm" << endl;
		success = false;
		goto End;
	}
	fout << a[i].Target_Number << "," << a[i].name << ",,,," << endl;
	fout << "First Distance,,,,," << endl;
	fout << ",,,,," << endl;
	fout << ",,,,," << endl;
	fout << ",,,,," << endl;
	fout << ",,,,," << endl;
	fout << ",,,,," << endl;
	fout << ",,,,," << endl;
	fout << "Second distance,,,,," << endl;
	fout << ",,,,," << endl;
	fout << ",,,,," << endl;
	fout << ",,,,," << endl;
	fout << ",,,,," << endl;
	fout << ",,,,," << endl;
	fout << ",,,,," << endl;
End:;
	fout.close();
	return success;
}
//Function Description
//This function will output the ArcherResult.csv
//Input: a: Archer Information
//		 no_of_archer: number of archer for iteration
//Output: ArcherResult.csv
bool GenerateArcherResult(Archer_info *a, int no_of_archer) {
	bool success = true;
	const string outputfilename = "ArcherResult.csv";
	string division = a[0].Division, dummy;
	ofstream fout;
	fout.open(outputfilename);
	if (fout.fail()) {
		cout << "Cannot create file"<<endl;
		success = false;
		cout << "Input something to confirm" << endl;
		cin>>dummy;
		goto CloseFile;
	}
	Process_Score(no_of_archer, a);
	GiveRank(a, no_of_archer);
	fout << division << endl;
	fout << "Target Number,Name,1st Distance Score,2nd Distance Score,Total Score,Number of '10+X',Number of 'X',Ranking" << endl;
	for (int i = 0; i < no_of_archer; i++) {
		//cout <<i<<" "<<a[i].name<<" "<<a[i].Division <<" "<<division<<endl;
		if (a[i].Division != division) {
			division = a[i].Division;
			fout << endl << division << endl;
			fout << "Target Number,Name,1st Distance Score,2nd Distance Score,Total Score,Number of '10+X',Number of 'X',Ranking" << endl;
		}
		fout << a[i].Target_Number << "," << a[i].name << "," << a[i].score.Total_score_for_1st_distance << "," << a[i].score.Total_score_for_2nd_distance << "," << a[i].score.Total_score << "," << a[i].score.Total_10_plus_x << "," << a[i].score.Total_10_plus_x - a[i].score.Total_10 << "," << a[i].rank << endl;
	}
CloseFile:;
	fout.close();
	return success;
}