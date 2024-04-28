#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>

int main() {
    struct sockaddr_in s1_addr;
    int s1;
    char s[200];

    s1 = socket(AF_INET, SOCK_STREAM, 0);
    s1_addr.sin_family = AF_INET;
    s1_addr.sin_addr.s_addr = htonl(INADDR_LOOPBACK); // Loopback address for local testing
    s1_addr.sin_port = htons(9145); // Port

    connect(s1, (struct sockaddr*)&s1_addr, sizeof(s1_addr));

    while (1) {
        printf("\nEnter the message: ");
        fgets(s,20,stdin);
        write(s1, s, sizeof(s));
    }

    close(s1);
    return 0;
}
