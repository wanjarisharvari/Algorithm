  // Online C compiler to run C program online
#include <stdio.h>
#include<string.h>
 
void merge(int arr[], int p, int q, int r) 
{ 
    int i, j, k; 
    int n1 = q - p + 1; 
    int n2 = r - q;
    int L[n1], R[n2]; 
    int temp[100];
 
    for (i = 0; i < n1; i++)  L[i] = arr[p + i]; 
    for (j = 0; j < n2; j++)  R[j] = arr[q + 1 + j]; 
  
    i = 0; 
    j = 0; 
    k = p; 
    while (i < n1 && j < n2) { 
        if (L[i] <= R[j])   arr[k++] = L[i++]; 
             
         
        else { 
            arr[k++] = R[j++]; 
            
        } 
        
    } 
  
    while (i < n1) { 
        arr[k++] = L[i++]; 
         
    } 
 
    while (j < n2) { 
        arr[k++] = R[j++]; 
          
    } 
}
void mergesort(int arr[], int p, int r){
 
    int q;
    if(p<r){
    q=(p+r)/2;
    mergesort(arr,p,q);
    mergesort(arr,q+1,r);
    merge(arr,p,q,r);
    }
}

int main() {
    int arr[]={1,4,3,6,7,3};
    int l = sizeof(arr)/sizeof(arr[0]);
    mergesort(arr,0,l-1);
    
    for(int i=0 ; i< l ; i++){
        printf("%d ",arr[i]);
    }

    return 0;
}