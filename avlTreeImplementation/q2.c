#include<iostream>
#include<vector>
using namespace std;

int main() 
{ 
  
    vector<int> Smaller_right;  
    vector<int> Greater_left;
    int i;
    
    int arr[] = {12, 1, 2, 3, 0, 11, 4};
    int n= sizeof(arr)/sizeof(arr[0]);
     for(i=0; i<n; i++){
       int y=i+1;
       int count=0;
       while(y<n){
         if(arr[i]>arr[y])
         count++;
         y++;
     }
     Smaller_right.push_back(count); 
   }
   
   for(i=0; i<n; i++){
       int y=0;
       int count=0;
       while(y<i){
         if(arr[i]<arr[y])
         count++;
         y++;
     }
     Greater_left.push_back(count); 
   }

  for(int i = 0; i < n; i++) {
    cout << Smaller_right.at(i) << "  ";
  }
     
     cout << endl;
     
  for(int i = 0; i < n; i++) {
    cout << Greater_left.at(i) << "  ";
  }
  
  
    return 0;  
}
