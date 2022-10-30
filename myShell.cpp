#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <iostream>
#include <stdlib.h>
#include <sys/wait.h> 
#include <bits/stdc++.h> 
#include <fcntl.h> 
#include <string>
#include <regex>
#include <sstream>
#include <iostream>
#include <fstream>
#include <vector>

using namespace std;
// this function implements the "listdir" command.
// by creating a child process and executing ls command.
void my_listdir(){
    pid_t pid;

    pid = fork();
    if(pid < 0) {
        cout << "an error with the fork in listdir" << endl;
    }
    else if(pid == 0){
        execlp("/bin/ls", "ls", NULL);
    }
    else{
        wait(NULL);
    }
}
// this function implements the "mycomputername" command
// by creating a child process which calls the whoami command.
// the parent process waits untill the child process is completed.
void my_mycomputername(){
    pid_t pid;

    pid = fork();
    if(pid < 0){
        cout << "an error with the fork in mycomputername" << endl;
    }
    else if(pid == 0){
        execlp("/bin/whoami", "whoami", NULL);
        exit(0);
    }
    else {
        wait(NULL);
    }
}
// This function implements the "whatsmyip" command
// by creating a child process that calls the hostname -I comamnd.
void whatsmyip(){
    pid_t pid;

    pid = fork();
    if(pid < 0) {
        cout << "an error in whatsmyip" << endl;
    }
    else if(pid == 0){
        execlp("/bin/hostname", "hostname", "-I", NULL);
        exit(0);
    } else {
        wait(NULL);
    }
}
// This function implements the "printfile (filename)" command
// by creating a child process that calls cat command with the filename
// Filename should be given directly without ""
void printfile(string file_name){
    
    string my_line;
    ifstream read_file(file_name);
    while (getline(read_file, my_line))
    {
        cout << my_line;
        cin.ignore();
    }
    
}
// This function implements the "printfile (file1) > (file2)" command
// by creating a child process which uses the cp command. 
// Filenames should be given directly without any "".
void copyfile(string source_file, string new_file) {
    pid_t pid;

    pid = fork();
    if(pid < 0) {
        cout << "an error in copy file" << endl;
    } else if(pid == 0) {
        const char* old = source_file.c_str();
        const char* newfile = new_file.c_str();
        execlp("/bin/cp", "cp", old, newfile, NULL);
        exit(0);
    } else {
        wait(NULL);
    }
}

// processes the input commands
int main(int argc, char const *argv[])
{
    // regex of possible commands
    regex listdir_expr("^\\s*listdir\\s*$");
    regex mycomputername_expr("^\\s*mycomputername\\s*$");
    regex whatsmyip_expr("^\\s*whatsmyip\\s*$");
    regex printfile_expr("^\\s*printfile\\s*\\w+\\.*\\w*\\s*$");
    regex copyfile_expr("^\\s*printfile\\s*\\w+\\.*\\w*\\s*>\\s*\\w+\\.*\\w*\\s*$");
    regex hellotext_expr("^\\s*hellotext\\s*$");
    regex exit_expr("^\\s*exit\\s*$");

    // get the username of the desktop -> we need this thourout the program
    string username = getenv("USER");

    // Keeps the command history for the "dididothat" command
    deque<string> history;
    string line = "";
    cout << "Welcome to myShell " << username << " <3!!!" << endl;
    
    // This while loop traverses the input line until the user enters the "exit" command.
    while (!(regex_match(line, exit_expr)))
    {
        // for every user command username and " >>> " will be printed
        cout << username << " >>> ";
        getline(cin, line);

        // create a list of words in the input file
        // create a string of input line without spaces to use it in history list
        vector<string> line_list;
        stringstream ls(line);
        string part;
        string line_without_space = "";
        while(ls >> part){
            line_list.push_back(part);
            line_without_space += part;
        }

        // if input line matches "listdir" command syntax
        if(regex_match(line, listdir_expr)){
            // check if history full, if full pop the oldest command
            if(history.size() == 15){
                history.pop_front();
            }
            // add the new command to history
            history.push_back("\"" + line_without_space + "\"");
            // call the function for listdir implementation
            my_listdir();
        }

        // if input line matches "mycomputername" command syntax
        else if(regex_match(line, mycomputername_expr)){
            // check if history full, if full pop the oldest command
            if(history.size() == 15){
                history.pop_front();
            }
            // add the new command to history
            history.push_back("\"" + line_without_space + "\"");
            // call the function for mycomputername implementation
            my_mycomputername();
        }
        // if input line matches "whatsmyip" command syntax
        else if(regex_match(line, whatsmyip_expr)) {
            // check if history full, if full pop the oldest command
            if(history.size() == 15){
                history.pop_front();
            }
            // add the new command to history
            history.push_back("\"" + line_without_space + "\"");
            // call the function for whatsmyip implementation
            whatsmyip();
        }
        // if input line matches "printfile (filename)" command syntax
        else if (regex_match(line, printfile_expr)){
            // check if history full, if full pop the oldest command
            if(history.size() == 15){
                history.pop_front();
            }
            // add the new command to history
            history.push_back("\"" + line_without_space + "\"");
            // call the function for printfile implementation
            printfile(line_list[1]);
        }
        // if input line matches "printfile (filename) > (filename2)" command syntax
        else if(regex_match(line, copyfile_expr)) {
            // check if history full, if full pop the oldest command
            if(history.size() == 15){
                history.pop_front();
            }
            // add the new command to history
            history.push_back("\"" + line_without_space + "\"");
            // call the function for copyfile implementation
            copyfile(line_list[1], line_list[3]);
        }
        // if input matches "dididothat" command syntax
        else if(line_list[0] == "dididothat"){
            // get the expression after dididothat command
            string expr = "";
            for(string word: line_list){
                if(word != "dididothat"){
                    expr = expr + word;
                }
                expr = expr + " ";
            }
            // remove the whitespaces form the expression to compare with the history list
            // this way if user input additional whitespaces in dididothat command the program disregards those whitespaces
            stringstream qs(expr);
            string var;
            string result = "";
            while(qs >> var){
                result += var;
            }
            // if expression in history list
            if(find(begin(history), end(history), result) != end(history)) {
                cout << "Yes" << endl;
            } else {
                cout << "No" << endl;
            }
        }
        // if input matches "hellotext" command syntax
        else if(regex_match(line, hellotext_expr)) {
            if(history.size() == 15){
                history.pop_front();
            }
            history.push_back("\"" + line_without_space + "\"");
            // use the system function to call gedit command
            system("gedit");
        }
        // in case of invalid command input prompt a warning message
        else {
            if(line_without_space != "exit"){
                cout << "You have entered an invalid command. Please check spelling or the project description for the valid commands. :)" << endl;
            }
            
        }

    }
    return 0;
}
