#include<iostream>

using namespace std;

//Sort the data array into ascending order


int main(){

	int noOfGoods = 0;
	cout << "Number of goods: ";
	cin >> noOfGoods;
	
	int dataArr[2][noOfGoods];
	cout << "Weight  Profit:\n";
	
	for(int i=0; i<noOfGoods; i++){
		
		cin >> dataArr[0][noOfGoods] >> dataArr[1][noOfGoods];
	}
	
    return 0;
}
