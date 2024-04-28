#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#define SIZE 5
int main(){
    struct sockaddr_in s1_addr;
    int s1;
    int arr[SIZE];
    printf("Enter array elements:");
    for(int i =0;i<SIZE;i++){
        scanf("%d",&arr[i]);
    }
    s1 = socket(AF_INET,SOCK_STREAM,0);
    s1_addr.sin_family = AF_INET;
    s1_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    s1_addr.sin_port = htons(9145);
    connect(s1,(struct sockaddr*)&s1_addr,sizeof(s1_addr));
    write(s1,arr,sizeof(arr));
    close(s1);
    return 0;
}