#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <iostream>
#include <string>
#include <stdlib.h>
#include <sys/wait.h>
#include <bits/stdc.h>
#include <fcntl.h>
#include <regex>
#include <sstream>

using namespace std;

// listdir fonksiyonu
void my_listdir(){
    pid_t pid;

    pid = fork();
    if(pid < 0) {
        cout << "error in listdir" << endl;
    } else if (pid == 0) {
        execlp("/bin/ls", "ls", NULL);
    } else {
        wait(NULL);
    }
}

// mycomputername fonksiyonu
void my_mycomputername() {
    pid_t pid;

    pid = fork();
    if(pid < 0) {
        cout << "an error in mycomputername" << endl;
    } else if(pid == 0) {
        execlp("/bin/whoami", "whoami", NULL);
        exit(0);
    } else {
        wait(NULL);
    }
}

// whatsmyip fonksiyonu
void whatsmyip() {
    pid_t pid;

    pid = fork();
    if(pid < 0) {
        cout << "an error in whatsmyip" << endl;
    } else if(pid == 0) {
        execlp("/bin/hostname", "hostname", "-I", NULL);
        exit(0);
    } else {
        wait(NULL);
    }
}

// printfile function
void printfile(string file_name) {
    pid_t pid;

    pid = fork();
    if (pid < 0) {
        cout << "an error in printfile" << endl;
    } else if(pid == 0) {
        execlp("/bin/cat", "cat", file_name, NULL);
        exit(0);
    } else {
        wait(NULL);
    }
}



int main(int argc, char const *argv[])
{
    string username = getenv("USER");

    const char * history[15] = {"", "", "", "", "", "","", "", "","", "", "","", "", ""};
    
    string line = "";

    while(line != "exit") {
        cout << username << " >>> ";
        getline(cin, line);

        if(line == "listdir") {
            my_listdir();
        } 
        
        else if(line == "mycomputername") {
            my_mycomputername();
        }

        else if(line == "whatsmyip") {
            whatsmyip();
        }

    }
    return 0;
}
