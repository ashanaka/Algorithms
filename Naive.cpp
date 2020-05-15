#include<iostream>
#include<String>
#include<fstream>
#include<vector>

using namespace std;

int main(){
	
	//========================================Inserting nubers in to vector==================================================================
	vector <char> text;
	
	string line;
	fstream myfile ("pi.txt");
	
	if (myfile.is_open())
	{
		int counter = 0;
	    while ( getline (myfile,line) )
	    {
			counter++;
			
	    	string sentence = line;
	    	
	    	if(counter > 8){
	    		if(sentence.length() > 50){
		    		
					sentence.erase(sentence.begin()+54, sentence.end());
					
					for(int j=0; j<54; j++){
						if(sentence[j] != ' '){
							text.push_back(sentence[j]);
						}
					}	
				}	
			}
	    }
	    myfile.close();
	}
	else cout << "Unable to open file";

	//========================================================================================================================================

	//==============================================================Making the string according to the b'day==================================
	string bDayStr = "141592j6535";
	
	
	//========================================================================================================================================
	
	int m = bDayStr.length();
	int n = text.size();
	
	int isFound = 0;
	
	for(int i=0; i<n-m; i++){
		int j = 0;
		while(j<m && bDayStr[j] == text[i+j]){
			if(j == m-1){
				cout << "matching found index at " << i  << endl;
				isFound = 1;
			}
			j++;
		}
	}
	
	if(isFound == 0){
		cout << "No matching found\n";
	}
	
	
	return 0;
}
