#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#define SIZE 5
void insertionSort(int *arr) {
    for (int i = 1; i < SIZE; i++) {
        int key = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }
}
int main(){
    struct sockaddr_in s1_addr,s2_addr;
    int s1,s2;
    int arr[SIZE];
    s1 = socket(AF_INET,SOCK_STREAM,0);
    s1_addr.sin_family = AF_INET;
    s1_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    s1_addr.sin_port = htons(9145);
    bind(s1,(struct sockaddr*)&s1_addr,sizeof(s1_addr));
    listen(s1,5);
    int slen = sizeof(s2_addr);
    s2 = accept(s1,(struct sockaddr*)&s2_addr,&slen);
    read(s2,arr,sizeof(arr));
    printf("The array received is:");
    for(int i =0;i<SIZE;i++){
        printf("%d ",arr[i]);
    }
    insertionSort(arr);
    printf("The sorted array is");
    for(int i =0;i<SIZE;i++){
        printf("%d ",arr[i]);
    }
    close(s1);
    close(s2);
    return 0;
}