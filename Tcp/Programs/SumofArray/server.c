#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <string.h>
#include <unistd.h>

#define ARRAY_SIZE 5

int main() {
    struct sockaddr_in s1_addr, s2_addr;
    int s1, s2;
    int arr_received[ARRAY_SIZE];
    s1 = socket(AF_INET, SOCK_STREAM, 0);
    s1_addr.sin_family = AF_INET;
    s1_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    s1_addr.sin_port = htons(9145);
    bind(s1, (struct sockaddr*)&s1_addr, sizeof(s1_addr));
    listen(s1, 5);
    int slen = sizeof(s2_addr);
    s2 = accept(s1, (struct sockaddr*)&s2_addr, &slen);
    read(s2, arr_received, sizeof(arr_received));
    int sum = 0;
    for (int i = 0; i < ARRAY_SIZE; ++i) {
        sum += arr_received[i];
    }
    printf("Sum of array elements received from the client: %d\n", sum);
    close(s1);
    close(s2);
    return 0;
}
