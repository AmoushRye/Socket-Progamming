#include <stdio.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <stdlib.h>
#include <unistd.h>
#include <netinet/in.h>
#include <string.h>

int main() {
    struct sockaddr_in s1_addr, s2_addr;
    int s1, s2, slen;
    char str[200];

    s1 = socket(AF_INET, SOCK_STREAM, 0);
    s1_addr.sin_family = AF_INET;
    s1_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    s1_addr.sin_port = htons(9145); // Port

    bind(s1, (struct sockaddr*)&s1_addr, sizeof(s1_addr));
    listen(s1, 5);
    slen = sizeof(s2_addr);
    s2 = accept(s1, (struct sockaddr*)&s2_addr, &slen);

    while (1) {
        int bytes_read = read(s2, str, sizeof(str));
        if(bytes_read<=0){
            printf("Client has closed the connection\n");
            break;
        }
        printf("The message received is: %s\n", str);
    }

    close(s1);
    close(s2);
    return 0;
}
