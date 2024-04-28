#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <string.h>

int main() {
    struct sockaddr_in s1_addr;
    int s1;
    char str[100];
    int slen;
    
    s1 = socket(AF_INET, SOCK_STREAM, 0);
    s1_addr.sin_family = AF_INET;
    s1_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    s1_addr.sin_port = htons(9145);
    connect(s1, (struct sockaddr*)&s1_addr, sizeof(s1_addr));
    
    while (1) {
        printf("Enter the string to check: ");
        fgets(str, sizeof(str), stdin);
        slen = strlen(str) - 1; // Calculate string length excluding newline
        write(s1, str, sizeof(str));
        write(s1, &slen, sizeof(slen));
    }
    
    close(s1);
    return 0;
}
