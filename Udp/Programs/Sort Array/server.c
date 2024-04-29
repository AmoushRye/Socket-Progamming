#include <stdio.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdlib.h>
#define PORT 8000
#define MAXLINE 1024
void insertionsort(int *arr,int SIZE) {
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
    int sockfd;
    int buffer[4];
    struct sockaddr_in servaddr,cliaddr;
    if((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0){
        perror("Socket Creation Failed\n");
        exit(EXIT_FAILURE);
    }
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = INADDR_ANY;
    servaddr.sin_port = htons(PORT);
    if(bind(sockfd,(struct sockaddr*)&servaddr,sizeof(servaddr))<0){
        perror("bind failed");
        exit(EXIT_FAILURE);
    }
    socklen_t len;
    len = sizeof(cliaddr);
    recvfrom(sockfd,buffer,sizeof(buffer),0,(struct sockaddr*)&cliaddr,&len);
    printf("Received unsorted array is\n");
    for(int i =0;i<4;i++){
        printf("%d\t",buffer[i]);
    }
    printf("\n");
    insertionsort(buffer,4);
    printf("Sorted array:\n");
    for(int i =0;i<4;i++) printf("%d\t",buffer[i]);
    sendto(sockfd,buffer,sizeof(buffer),0,(const struct sockaddr*)&cliaddr,len);
    return 0;
}