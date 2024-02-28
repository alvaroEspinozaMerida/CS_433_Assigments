//
// Created by Alvaro Merida on 2/26/24.
//

#include "tokenizertest.h"



#include <stdio.h>
#include <string.h>

int parse_command(char command[], char *args[], const char sep[]) {
    char *token = strtok(command, sep);
    int i = 0;
    while (token != NULL) {
        args[i] = token;
        printf("Token: %s\n", token); // Debug print
        i++;
        token = strtok(NULL, sep);
    }
    args[i] = NULL;
    return i;
}

int main() {
    char command[] = "hello my name >is<bob";
    char *args[50];
    int num_tokens = parse_command(command, args, " ><"); // Including space, '>', and '<' as delimiters

    printf("Resulting args:\n");
    for (int i = 0; i < num_tokens; ++i) {
        printf("[%s]\n", args[i]);
    }


    return 0;
}
