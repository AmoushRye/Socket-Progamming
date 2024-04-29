#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <string.h>

#define PORT 8000
#define MAXLINE 10

int main(){
    struct sockaddr_in servaddr;
    int sockfd;
    char str[MAXLINE];
    
    if((sockfd = socket(AF_INET,SOCK_DGRAM,0))<0){
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }    
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = INADDR_ANY;
    servaddr.sin_port = htons(PORT);
    while(1) {
        printf("Enter the string to send (or type 'exit' to quit): ");
        fgets(str,MAXLINE,stdin);
        if(strcmp(str, "exit") == 0) {
            break; // Exit the loop if the user enters "exit"
        }
        sendto(sockfd, str, sizeof(str), 0, (const struct sockaddr*)&servaddr, sizeof(servaddr));
        printf("Message sent.\n");
    }
    close(sockfd);
    return 0;
}
