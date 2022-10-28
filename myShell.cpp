#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <iostream> //Used to perform input and output operations
#include <string> //Perform string manipulation operations
#include <stdlib.h> //exit()
#include <sys/wait.h> //wait()
#include <bits/stdc++.h> //// using stringstream
#include <fcntl.h> //file control options
#include <string>
#include <regex>
#include <sstream>
#include <vector>

using namespace std;
// listdir fonksiyonu
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
// mycomputername function
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
// whatsmyip function
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
// printfile function
void printfile(string file_name){
    
    pid_t pid;

    pid = fork();
    if(pid < 0) {
        cout << "an error with printfile" << endl;
    } else if(pid == 0) {
        const char * file = file_name.c_str();
        execlp("/bin/cat", "cat", file, NULL);
        exit(0);
    } else {
        wait(NULL);
        cout << endl;
    }
}
// printfile2 function
void copyfile(string source_file, string new_file) {
    pid_t pid;

    pid = fork();
    if(pid < 0) {
        cout << "an error in copy file" << endl;
    } else if(pid == 0) {
        const char* old = source_file.c_str();
        const char* newfile = new_file.c_str();
        cout << old << endl;
        execlp("/bin/cat", "cat", old, ">", newfile, NULL);
        exit(0);
    } else {
        wait(NULL);
    }
}

// hellotext


int main(int argc, char const *argv[])
{
    /* code */

    // regex of possible commands
    regex listdir_expr("^\\s*listdir\\s*$");
    regex mycomputername_expr("^\\s*mycomputername\\s*$");
    regex whatsmyip_expr("^\\s*whatsmyip\\s*$");
    regex printfile_expr("^\\s*printfile\\s*\\w+\\.*\\w*\\s*$");
    regex copyfile_expr("^\\s*printfile\\s*\\w+\\.*\\s*>\\s*\\w+\\.*\\s*$");
    regex dididothat_expr("^\\s*dididothat\\s*\"\\w+\"\\s*$");
    regex hellotext_expr("^\\s*hellotext\\s*$");

    // get the username of the desktop -> we need this thourout the program
    string username = getenv("USER");

    deque<string> history;
    string line = "";

    // get the input
    // traverse line by line while exit commandi gelene kadar
    while (line != "exit")
    {
        cout << username << " >>> ";
        getline(cin, line);

        if(regex_match(line, listdir_expr)){
            if(history.size() == 15){
                history.pop_front();
            }
            history.push_back("\"" + line + "\"");

            my_listdir();
        }

        else if(regex_match(line, mycomputername_expr)){
            if(history.size() == 15){
                history.pop_front();
            }
            history.push_back("\"" + line + "\"");
            my_mycomputername();
        }

        else if(regex_match(line, whatsmyip_expr)) {
            if(history.size() == 15){
                history.pop_front();
            }
            history.push_back("\"" + line + "\"");
            whatsmyip();
        }

        else if (regex_match(line, printfile_expr)){
            vector <string> param;
            stringstream ss(line);
            string word;
            while(ss >> word){
                param.push_back(word);
            }
            if(history.size() == 15){
                history.pop_front();
            }
            history.push_back("\"" + line + "\"");
            printfile(param[1]);
        }

        else if(regex_match(line, copyfile_expr)) {
            vector <string> param;

            stringstream ss(line);
            string word;
            while(ss >> word) {
                param.push_back(word);
            }
            if(history.size() == 15){
                history.pop_front();
            }
            history.push_back("\"" + line + "\"");
            copyfile(param[1], param[3]);
        }

        else if(regex_match(line, dididothat_expr)){
            vector<string> param;
            if(history.size() == 15){
                history.pop_front();
            }
            history.push_back("\"" + line + "\"");
            stringstream ss(line);
            string word;
            while(ss >> word) {
                param.push_back(word);
            }

            if(find(begin(history), end(history), param[1]) != end(history)) {
                cout << "Yes" << endl;
            } else {
                cout << "No" << endl;
            }
        }

        else if(regex_match(line, hellotext_expr)) {
            if(history.size() == 15){
                history.pop_front();
            }
            history.push_back("\"" + line + "\"");
        }
    }
    
    
    

    // initialize an array to store the last 15 commands -> her loopta bakicaz bos yer var mi diye, yoksa en eskisini cikarip 
    // yeni commandi eklicez

    // if blockuyla yukaridaki fonksiyonlara at


    return 0;
}
