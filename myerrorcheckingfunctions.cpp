#include "pch.h"
#include <cctype>
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>


using namespace std;



//to check archer's name and coach's name
//input: item:name
//       i,j:the position of the mistake
void Errorchecking_name(string item, int i, int j) {

	stringstream ss(item);
	string temp;
	if (item.length() == 0) {//to checl if the input of name is empty
		cout << "Your name is invalid. Check Row: " << i << "Column: " << j << endl;
		goto end;
	}
	while (getline(ss, item, ' ')) {
	  if (not(item[0] >= 'A'&& item[0] <= 'Z')) {//to check if the first letter is capital
			cout << "Your name is invalid. Check Row: " << i << "Column: " << j << endl;
			goto end;
		}

		for (int k = 1;k < item.length();k++) {
		  if (!(isalpha(item[k]) || item[k] == '-')) {//to check if there is any characters that is not alphabet or '-'
				cout << "Your name is invalid. Check Row: " << i << "Column: " << j << endl;
				goto end;
			}
		}
	}
end:;
}
//to check archer's target number
//input: item:archers' target number
//       i,j:the position of the mistake
void Errorchecking_Target_Number(string item, int i, int j) {
	int length = item.length();
	if (length == 0) {// to check if the Target number is empty

		cout << "Your target number is invalid. Check Row: " << i << "Column: " << j << endl;
		goto end;
	}
	if ((item[length - 1] >= 'a'&& item[length - 1] <= 'z') || (item[length - 1] >= 'A'&& item[length - 1] <= 'Z')) {//to check if the last character is alphabet or not
	}
	else {

	  cout << "Your target number is invalid. Check Row: " << i << "Column: " << j << endl;

		goto end;
	}
	for (int k = 0;k < length - 1;k++) {//to check if the character(except the last one) is digit or not
		if (isdigit(item[k])) {}
		else {

			cout << "Your target number is invalid. Check Row: " << i << "Column: " << j << endl;
			goto end;
		}
	}
end:;
}
//to check archer number
//input: item:archer number
//       i,j:the position of the mistake
void Errorchecking_HKAA_Archer_number(string &item, int i, int j) {
	int length = item.length();
	string *temp = new string[length];

	if (length == 0) {//to check if the archer number is empty or not
		cout << "Your archer number is invalid. Check Row: " << i << "Column: " << j << endl;
		goto end;
	}
	*temp = "";
	if ((item[0] == 'T' || item[0] == 't') && (item[length - 1] == 'D' || item[length - 1] == 'd')) {//to turn all temporarily registered archer's archer number to "Temporary Registered"
		for (int i = 0; i < length; i++) {
			*temp += tolower(item[i]);
		}
		if (*temp == "temporary registered") {
			item = "Temporary Registered";
			goto end;
		}
		else {
			cout << "Your archer number is invalid. Check Row: " << i << "Column: " << j << endl;
			goto end;
		}
	}
	else if ((item[0] != 'M') || (item[length - 1] != 'S')) {// to check if the archer number follow the format(start with M and end with S)
		cout << "Your archer number is invalid. Check Row: " << i << "Column: " << j << endl;
		goto end;
	}
	for (int k = 1;k < length - 1;k++) {//to check if the middle 4 charachers are number or not
		if (not(isdigit(item[k]))) {
			cout << "Your archer number is invalid. Check Row: " << i << "Column: " << j << endl;
			goto end;
		}
	}
 end:delete[] temp;;// to free the memory
}

//to check archer's organiztaion
//input: item:archers' organization
//       i,j:the position of the mistake
void Errorchecking_HKAA_Affiliated_Organization(string item, int i, int j) {
	int length = item.length();
	if (length == 0) {//to check if the input is empty
		cout << "Your archer number is invalid. Check Row: " << i << "Column: " << j << endl;
		goto end;
	}

	for (int k = 0;k < item.length();k++) {//to check if all characters in the organization are alphabet
		if (not (isalpha(item[k]))) {
			cout << "Your orgainization is invalid. Check Row: " << i << "Column: " << j << endl;
			goto end;
		}
	}
end:;
}
//to check archer's division
//input: item:archers' division
//       i,j:the position of the mistake
void Errorchecking_Division(string item, int i, int j) {
	const string matchstring = "RBM RBW REM REW RIM RIW RAM RAW";
	string temp = "";//to remove the accadental extra spacing in the division
	for (int k = 0;k < item.length();k++) {
		if (isalpha(item[k])) {
			temp += item[k];
		}

	}


	if (item.length() != 3) {//to check if the length of the division is 3 or not
		cout << "Your division is invalid. Check Row: " << i << "Column: " << j << endl;
		goto end;
	}
	if (matchstring.find(item) == -1) {// to check if the division is the one in matchstring

		cout << "Your division is invalid. Check Row: " << i << "Column: " << j << endl;
		goto end;
	}
end:;
}
//to check score
//input: item:score
//output:1
int errorchecking_score(string item) {

  if (!(isdigit(item.c_str()[0]))){
  
	if (not(item == "M" || item == "X" || item == "x" || item == "m")) {
    
	cout<<"invalid score"<<endl;
	return 0;
	
     }
   }
 

	
	

  else  if (stoi(item)<=0||stoi(item)>10){
    cout<<"invalid score"<<endl;
    return 0;
  }
  
  
  
 
 
 
return 1;
}
//to check  if all char is is integer
//input:check:string to be checked
//output:true if all char in check is digit
//       false if any of them is not digit
bool CheckAllInteger(string check) {//to check if all char in check is digit
	for (int i = 0; i < check.length();i++) {
		if (!isdigit(check[i])) {
			return false;
		}
	}
	return true;
}
