
/**
 * Assignment 2: Simple UNIX Shell
 * @file pcbtable.h
 * @author Alvaro E. Merida, Lucas Birkenstock
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
int parse_command(char command[], char *args[], int &readWrite, int &concurrent)
{

    //USED TO CHECK IF THE COMMAND HAS < or > operator
    std::string commandStr(command);

    //three states for wheter we are reading,writing, or none from a file
    //WRITING STATE
    if (commandStr.find('>') != std::string::npos)  {
        readWrite = 1;
    }
    //READING STATE
    else if (commandStr.find('<') != std::string::npos ){
        readWrite = 2;
    }

    else {
       readWrite = 0;
    }

    if (commandStr.find('&') != std::string::npos ){
        concurrent = 1;
    }

    else {
        concurrent = 0;
    }



    char *token = strtok(command, " <>|"); // Second param are delimiters for parsing tokens
    int i = 0;


    // Loop through each token produced by the function 
    while ( token != NULL ) {
        // Add token produced by strtok to args array, increment # tokens
        args[i] = token;
        i++;
        // According to cppreference: Subsequent calls to strtok require a null pointer in order to continue where the first call left off.
        token = strtok(NULL, " <>&|");
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
    char input[MAX_LINE];
    char command[MAX_LINE];       // the command that was entered
    char *args[MAX_LINE / 2 + 1]; // hold parsed out command line arguments
    int should_run = 1;           /* flag to determine when to exit program */
    int num_args = 0 ;

    char *fileName;
    int readWrite = 0;
    int concurrent = 0;
    int file_descriptor;

    // For storing previous command when !! is entered
    char previous[MAX_LINE];



    while (should_run) {

        // Prompt input
        printf("osh>");
        fflush(stdout);

        // Read user input and replace newline char with null terminator (if present). 
        if (fgets(input, MAX_LINE, stdin) != NULL) {
            size_t len = strlen(input);
            if (len > 0 && input[len - 1] == '\n') {
                input[len - 1] = '\0';
            }
        }

        // Make a duplicate of user command input, so we can manipulate it without altering the original command. 
        strcpy(command,input);


        // Break loop and terminate if user input is "exit"
        if(strcmp(input, "exit") == 0 ) {
            break;
        }


        // If input is not "!!": 
        if(strcmp(input, "!!") != 0 ) {

            // Make copy of previously executed command for manipulation
            strcpy(previous,input);

            // Get number of command arguments by parsing the command. Function returns # commands. 
            num_args = parse_command(command, args, readWrite, concurrent);

        } else if (strcmp(command, "!!") == 0 and num_args == 0) {
            // If user command is "!!" and num_args is zero, print error. Num_args will be zero if parse_command is never called, meaning there is no previously entered command.
            cout<<"No command history found."<<endl;
        } else if (strcmp(command, "!!") == 0 ) {
            // If user enters !!, print previous command to console, and update num_args
            cout << previous << endl;
            num_args = parse_command(previous, args, readWrite, concurrent);
        }

//        CHILD PROCESS STARTS HERE
        int id = fork();

        // pid = 0 means code is executed in the child process
        if(id == 0) {
            // If reading or writing: 
            if( readWrite == 1 or readWrite == 2) {
                // Extract filename from argument array
                // fileName = args[num_args-1]; // Redundant? 
                strcpy(fileName,args[num_args-1]);

                // If writing state:
                if(readWrite == 1){
                    // Open file to be written to. Create new file if it doesn't exist. Truncate file to length = 0 if it already exists. 
                    file_descriptor = open(fileName, O_WRONLY | O_CREAT | O_TRUNC);
                }
                else {
                    // If in reading state
                    cout<<"READ IS BEING ACTIVATED"<<endl;
                    // Open file for reading 
                    file_descriptor = open(fileName, O_RDONLY);
                }

                // Filename was num_args-1. Now that it is handled, set that arg to NULL and decrement the number of arguments. 
                args[num_args-1] = NULL;
                num_args = num_args - 1;

                // Print errors if unable to read
                if(file_descriptor < 0) {
                    perror("open");
                    exit(EXIT_FAILURE);
                }

                // If in write state:
                if(readWrite == 1) {
                    // Redirect stdout to file_descriptor
                    if(dup2(file_descriptor,STDOUT_FILENO) < 0 ) {
                        // Print error if unsuccessful. 
                        perror("dup2");
                        exit(EXIT_FAILURE);
                    }
                // If reading state: 
                } else if (readWrite == 2){

                    if(dup2(file_descriptor,STDIN_FILENO) < 0 ) {
                        perror("dup2");
                        close(file_descriptor);
                        exit(EXIT_FAILURE);
                    }
                    close(file_descriptor);
                }

            }

            fflush(stdout);

            if (execvp(args[0], args) == -1) {
                cout<<"Command not found"<<endl;
            }

            if(readWrite != 2){
                close(file_descriptor);
            }


        }
        else if (id > 0) {
            if(concurrent != 1){
                wait(NULL);
            }
        } else{
            std::cout << "Fork failed" << std::endl;
        }


    }

    return 0;
}
