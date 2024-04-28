#include <stdio.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>
#include <string.h>

int main() {
    struct sockaddr_in s1_addr;
    int s1;
    char str[100], str2[50];
    s1 = socket(AF_INET, SOCK_STREAM, 0);
    s1_addr.sin_family = AF_INET;
    s1_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    s1_addr.sin_port = htons(9145);
    connect(s1, (struct sockaddr*)&s1_addr, sizeof(s1_addr));
    while (1) {
        printf("Client: ");
        fgets(str, 100, stdin);
        write(s1, str, sizeof(str));
        read(s1, str, sizeof(str));
        printf("Server: %s", str);
    }
    close(s1);
    return 0;
}
