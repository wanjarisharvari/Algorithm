# include <iostream>
using namespace std;
void swap(int a, int b){
    int temp;
    temp = a;
    a=b;
    b=temp;
}
int partition(int arr[], int p, int r){
    int pivot=arr[0];
    int start=p;
    int end=r;
    while(start<end){
        while(arr[start]<pivot) start++;
        while(arr[end]>pivot) end--;
        int temp;
        temp = arr[start];
        arr[start]=arr[end];
        arr[end]=temp;
    }
    //swap(pivot,arr[end]);
    int temp;
    temp = pivot;
    pivot=arr[end];
    arr[end]=temp;
    return end;

}
void quicksort(int arr[], int p , int r){
    if(p<r){
        int q= partition(arr,p,r);
        quicksort(arr,p,q-1);
        quicksort(arr,q+1,r);
    }
}
int main(){
    int arr[]={7,5,4,8,2,6,9,7,5,10};
    quicksort(arr,0,9);
    for(int i=0 ; i<10 ; i++){
        cout<<arr[i]<<" ";
    }
    
    return 0;
}