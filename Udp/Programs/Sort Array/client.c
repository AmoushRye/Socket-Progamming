#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>

#define PORT 8000
#define MAXLINE 1024

int main(){
    int sockfd;
    char buffer[MAXLINE];
    struct sockaddr_in servaddr;
    if((sockfd = socket(AF_INET,SOCK_DGRAM,0))<0){
        perror("Socket Creation failed.");
        exit(EXIT_FAILURE);
    }
    // memset(&servaddr,0,sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = INADDR_ANY;
    servaddr.sin_port = htons(PORT);
    int n;
    socklen_t len;
    printf("Enter the size of the array:");
    scanf("%d",&n);
    int arr[n];
    printf("Enter the elements of array:\n");
    for(int i =0;i<n;i++){
        scanf("%d",&arr[i]);
    }
    sendto(sockfd,arr,sizeof(arr),0,(const struct sockaddr*)&servaddr,sizeof(servaddr));
    recvfrom(sockfd,arr,sizeof(arr),0,(struct sockaddr*)&servaddr,&len);
    printf("Sorted array:\n");
    for(int i =0;i<n;i++){
        printf("%d\t",arr[i]);
    }
    printf("\n");
    close(sockfd);
    return 0;
}