
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
int parse_command(char command[], char *args[], int &readWrite)
{

    //USED TO CHECK IF THE COMMAND HAS < or > operator
    std::string commandStr(command);

    //three states for wheter we are reading,writing, or none from a file
    //WRITING STATE
    if (commandStr.find(">") != std::string::npos)  {
        readWrite = 1;
    }
    //READING STATE
    else if (commandStr.find("<") != std::string::npos ){
        readWrite = 2;
    }

    else {
       readWrite = 0;
    }

    char *token = strtok(command, " <>"); // Second param are delimiters for parsing tokens
    int i = 0;


    // Loop through each token produced by the function 
    while ( token != NULL ) {
        // Add token produced by strtok to args array, increment # tokens
        args[i] = token;
        i++;
        // According to cppreference: Subsequent calls to strtok require a null pointer in order to continue where the first call left off.
        token = strtok(NULL, " <>");
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

    int file_descriptor;


    while (should_run){

        printf("osh>");
        fflush(stdout);
        // Read the input command and get rid of the new line character generated when
        // the enter gets pressed by the user
        if (fgets(input, MAX_LINE, stdin) != NULL) {
            size_t len = strlen(input);
            if (len > 0 && input[len - 1] == '\n') {
                input[len - 1] = '\0';
            }
        }

        //Makes a copy of the input so we can have an original copy of the line so
        //that when the command is extracted the orginal line remains
        strcpy(command,input);


        //if we do not need to use historical commands then we can parse our the command like normal
        //and extract each argument
        if(strcmp(input, "!!") != 0 ){


            //TODO: update the parse function so that it extracts
            //out each one of the tokens based on space
            // if there exist the < or > we need handle this special
            // case so that it extracts everything before and after the < and >
            num_args = parse_command(command, args,readWrite);

            //if we have an arrow this is a special case for the input
            // what needs to happen is we need to extract out the txt
            //file that exist in the command
            //however we cannot assume that the > or < will always be
            //the second argument of the args list as some
            //linux commands vary in size ex : ls and ls -l
            //what needs to happen is we need extract everything up to > < and after those values

        }
        else if(strcmp(command, "!!") == 0 and num_args == 0){
            cout<<"No commands in history"<<endl;
        }

//        CHILD PROCESS STARTS HERE
        int id = fork();

        if(id == 0){
            if( readWrite == 1 or readWrite == 2){

//                cout<<"File name:"<<args[num_args-1]<<endl;

                fileName = args[num_args-1];

                strcpy(fileName,args[num_args-1]);
                cout<<"File name:"<<fileName<<endl;

                if(readWrite == 1){
                    file_descriptor = open(fileName, O_WRONLY | O_CREAT | O_TRUNC);
                }
                else{
                    cout<<"READ IS BEING ACTIVATED"<<endl;
                    file_descriptor = open(fileName, O_RDONLY);
                }

                args[num_args-1] = NULL;
                num_args = num_args - 1;

//                for (int i = 0; i < num_args; ++i) {
//                    std::cout << "args[" << i << "]: " << args[i] << std::endl;
//                }
                //IF file is not open correctly error is handled here

                if(file_descriptor < 0){
                    perror("open");
                    exit(EXIT_FAILURE);
                }

                //since we already checked abouve for it being either 1 or 2 it just has to check for 1 here
                if(readWrite == 1){
                    if(dup2(file_descriptor,STDOUT_FILENO) < 0 ){
                        perror("dup2");
                        exit(EXIT_FAILURE);
                    }
                }
                else{


                    if(dup2(file_descriptor,STDIN_FILENO) < 0 ){
                        perror("dup2");
                        close(file_descriptor);
                        exit(EXIT_FAILURE);
                    }
//                    num_args+=1;
//                    args[num_args-1] = fileName;
//                    for (int i = 0; i < num_args; ++i) {
//                        std::cout << "args[" << i << "]: " << args[i] << std::endl;
//                    }
//
//                    close(file_descriptor);
                    close(file_descriptor);

                }

            }

            fflush(stdout);

            if (execvp(args[0], args) == -1) {
                perror("execvp");
                exit(EXIT_FAILURE);
            }
            if(readWrite != 2){
                close(file_descriptor);
            }


        }

//        if(id != 0 && args[num_args - 1] != "&"){
            wait(NULL);
//        }



    }

    return 0;
}
