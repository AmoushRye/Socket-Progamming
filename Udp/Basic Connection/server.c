#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>

#define MAXLINE 10
#define PORT 8000

int main(){
    struct sockaddr_in servaddr, cliaddr;
    int sockfd;
    char buffer[MAXLINE];
    
    if((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0){
        perror("Socket creation failed\n");
        exit(EXIT_FAILURE);
    }
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = INADDR_ANY;
    servaddr.sin_port = htons(PORT);
    if(bind(sockfd, (struct sockaddr*)&servaddr, sizeof(servaddr)) < 0){
        perror("Bind failed\n");
        exit(EXIT_FAILURE);
    }
    while(1) {
        socklen_t len = sizeof(cliaddr);
        int n = recvfrom(sockfd, buffer, sizeof(buffer), 0, (struct sockaddr*)&cliaddr, &len);
        if(n < 0) {
            perror("Receive failed\n");
            continue; // Continue to the next iteration of the loop
        }
        printf("Received: %s\n", buffer);
    }
    
    close(sockfd);
    
    return 0;
}
