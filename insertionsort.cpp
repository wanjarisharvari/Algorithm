# include <iostream>
using namespace std;
int main(){
    int arr[]={3,5,7,3,1,9,6,4,2};
    int l = sizeof(arr)/sizeof(arr[0]);
    for(int i=1 ; i<l ; i++){
        int j= i-1;
        int key = arr[i];
        while(key<arr[j] && j>=0){
            arr[j+1]=arr[j];
            j--;
        }
        arr[j+1]=key;
    }
    //cout<<l<<endl;
    for(int i=0 ; i<l ; i++){
        cout<<arr[i]<<" ";
    }
    return 0;
}