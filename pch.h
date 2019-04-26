#pragma once
using namespace std;
#include <string>
struct Raw_Score {
	string First_distance[6][6];
	string Second_distance[6][6];
};
struct Score_Archer {
	Raw_Score Score_raw;
	int Total_score_for_1st_distance = 0;
	int Total_score_for_2nd_distance = 0;
	int Total_score = 0;
	int Total_10_plus_x = 0;
	int Total_10 = 0;
};
struct Archer_info {
	string Target_Number;
	string name;
	string HKAA_Archer_number;
	string HKAA_Affiliated_Organization;
	string Coach_name;
	string Division;
	Score_Archer score;
	string rank = "-1";
	int rankWeight;
};
//All error checking related functions
//Read myerrorcheckingfunction.cpp
void Errorchecking_name(string item, int i, int j);
void Errorchecking_Target_Number(string item, int i, int j);
void Errorchecking_HKAA_Archer_number(string &item, int i, int j);
void Errorchecking_HKAA_Affiliated_Organization(string item, int i, int j);
void Errorchecking_Division(string item, int i, int j);
int errorchecking_score(string item);
bool CheckAllInteger(string check);

//File Input and Count the number of archers
//Read InfoFileInputPlusCount.cpp
int Count_no_of_archer(string filename);
void fileopening_and_call_Count_no_of_archer(int &No_of_archer, Archer_info *&a, bool &fileOpen);
//Score Input and checking


//Score Processing+Edit
//Read ScoreOperations.cpp
void Raw_Score_Interpret(Archer_info *a, int i, int j, int k, bool state);
void Process_Score(int num_archers, Archer_info *a);
void DisplayRawScore(Archer_info a);
bool readscore(Archer_info *a, int No_of_archer);

//Rank Operation
//Read GiveRank.cpp
void GiveRank(Archer_info *a, int no_of_archer);

//Edit score or DQ an archer
//Read EditScoreORDQ.cpp
bool EditRecordScoreOrFile(Archer_info *a, int no_of_archer);

//File Generation
//Read FileGeneration.cpp
bool generatetemplatefile(Archer_info *a, int i);
bool GenerateArcherResult(Archer_info *a, int no_of_archer);

string CLI(Archer_info *a, int No_of_archer, bool dependecylist[]);