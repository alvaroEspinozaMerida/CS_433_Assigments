
/**
 * Assignment 2: Simple UNIX Shell
 * @file pcbtable.h
 * @author ??? (TODO: your name)
 * @brief This is the main function of a simple UNIX Shell. You may add additional functions in this file for your implementation
 * @version 0.1
 */
// You must complete the all parts marked as "TODO". Delete "TODO" after you are done.
// Remember to add sufficient and clear comments to your code

#include <stdio.h>
#include <unistd.h>
#include <iostream>
#include <fcntl.h>
#include <cstring>
#include <unistd.h>
#include <sys/wait.h>

using namespace std;

#define MAX_LINE 80 // The maximum length command

/**
 * @brief parse out the command and arguments from the input command separated by spaces
 *
 * @param command
 * @param args
 * @return int
 */
int parse_command(char command[], char *args[])
{   
    // Get pointer to the first token parsed by strtok

    char *token = strtok(command, " "); // Second param are delimiters for parsing tokens
    int i = 0;

    // Loop through each token produced by the function 
    while (token != NULL) {
        // Add token produced by strtok to args array, increment # tokens
        args[i] = token;
        i++;

        // According to cppreference: Subsequent calls to strtok require a null pointer in order to continue where the first call left off. 
        token = strtok(NULL, " ");
    }

    args[i] = NULL;

    // Return total num of tokens
    return i;
}

// TODO: Add additional functions if you need

/**
 * @brief The main function of a simple UNIX Shell. You may add additional functions in this file for your implementation
 * @param argc The number of arguments
 * @param argv The array of arguments
 * @return The exit status of the program
 */
int main(int argc, char *argv[])
{
    char command[MAX_LINE];       // the command that was entered
    char *args[MAX_LINE / 2 + 1]; // hold parsed out command line arguments
    int should_run = 1;           /* flag to determine when to exit program */
    int num_args = 0 ;


    while (should_run)
    {
        printf("osh>");
        fflush(stdout);
        // Read the input command and get rid of the new line character generated when
        // the enter gets pressed by the user
        if (fgets(command, MAX_LINE, stdin) != NULL) {
            size_t len = strlen(command);
            if (len > 0 && command[len - 1] == '\n') {
                command[len - 1] = '\0';
            }
        }

        if(strcmp(command, "!!") != 0 ){
            num_args = parse_command(command, args);
        }
        else if(strcmp(command, "!!") == 0 and num_args == 0){
            cout<<"No commands in history"<<endl;
        }

//        CHILD PROCESS STARTS HERE
        int id = fork();

        if(id == 0){

//            TODO: ADD a funtion that is able to extract out the < or > operators to that the comamand can pass in the right arguments

            if (execvp(args[0], args) == -1) {
                perror("execvp");
                exit(EXIT_FAILURE);
            }

            if(strcmp(args[1], ">") == 0){


                int file_descriptor = open(args[2],O_WRONLY | O_TRUNC | O_CREAT);

                if(file_descriptor < 0){
                    perror("open");
                    exit(EXIT_FAILURE);
                }

                if(dup2(file_descriptor,STDOUT_FILENO) < 0 ){
                    perror("dup2");
                    exit(EXIT_FAILURE);
                }

            }

        }

        if(id != 0 && args[num_args - 1] != "&"){
            wait(NULL);
        }

    }
    return 0;
}
