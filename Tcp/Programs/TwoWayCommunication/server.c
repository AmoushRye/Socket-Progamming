#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <string.h>
#include <unistd.h>
int main(){
    struct sockaddr_in s1_addr,s2_addr;
    char str[100],str2[50];
    int s1,s2;
    s1 = socket(AF_INET,SOCK_STREAM,0);
    s1_addr.sin_family = AF_INET;
    s1_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    s1_addr.sin_port = htons(9145);
    bind(s1,(struct sockaddr*)&s1_addr,sizeof(s1_addr));
    listen(s1,5);
    int slen = sizeof(s2_addr);
    s2 = accept(s1,(struct sockaddr*)&s2_addr,&slen);
    while (1) {
        int bytes_read = read(s2, str, sizeof(str));
        if (bytes_read <= 0) {
            printf("Connection closed by the client\n");
            break;
        }
        printf("Client: %s", str);
        printf("Server: ");
        fgets(str, 100, stdin);
        write(s2, str, sizeof(str));
    }
    close(s1);
    close(s2);
    return 0;
}