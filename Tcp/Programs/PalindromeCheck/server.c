#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <string.h>
#include <unistd.h>

int PalindromeChecker(char str[], int length) {
    int left = 0;
    int right = length - 1;
    while (left < right) {
        if (str[left] != str[right])
            return -1;
        left++;
        right--;
    }
    return 1;
}

int main() {
    struct sockaddr_in s1_addr, s2_addr;
    int s1, s2;
    char str[100];
    int stringlength;

    s1 = socket(AF_INET, SOCK_STREAM, 0);
    s1_addr.sin_family = AF_INET;
    s1_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    s1_addr.sin_port = htons(9145);
    bind(s1, (struct sockaddr*)&s1_addr, sizeof(s1_addr));
    listen(s1, 5);
    int slen = sizeof(s2_addr);
    s2 = accept(s1, (struct sockaddr*)&s2_addr, &slen);

    while (1) {
        if(read(s2, str, sizeof(str))<=0){
            printf("client connection closed");
            break;
        }
        read(s2, &stringlength, sizeof(stringlength));
        
        if (PalindromeChecker(str, stringlength) == -1) {
            printf("%.*s is not a palindrome\n", stringlength, str);
        } else {
            printf("%.*s is a palindrome\n", stringlength, str);
        }
    }
    
    return 0;
}
