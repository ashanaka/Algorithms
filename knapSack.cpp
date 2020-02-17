#include<iostream>

using namespace std;





int main(){
	
	int noOfGoods;
	cout << "Number of goods: ";
	cin >> noOfGoods;
	
	int maxWeight;
	cout << "Max weight: ";
	cin >> maxWeight;
	
	int dataArr[2][noOfGoods];
	cout << "Weight  Profit:\n";
	
	for(int i=0; i<noOfGoods; i++){
		
		cin >> dataArr[i][0] >> dataArr[i][1];
	}
	
	for(int i=0; i<noOfGoods; i++){
		
		for(int j=i; j<noOfGoods; j++){
			
			if(dataArr[j][0] > dataArr[j+1][0]){
				
				int temp1 = dataArr[j][0];
				int temp2 = dataArr[j][1];
				
				dataArr[j][0] = dataArr[j+1][0];
				dataArr[j][0] = dataArr[j+1][1];
				
				dataArr[j+1][0] = temp1;
				dataArr[j+1][1] = temp2;
				
			}
		}
	}
	
	int knackMatrix[noOfGoods+2][];
	
	
	
    return 0;
}
