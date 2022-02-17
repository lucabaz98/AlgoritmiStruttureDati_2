#include <iostream>
#include <string>
#include <sstream>
using namespace std;



int main(){
    string input;
    char* temp;
    bool exit = true;
    
    while(exit)
    {
        getline(cin,input);
        char str[input.length()+1];
        strcpy(str, input.c_str());
        temp = strtok(str, " ");
    
        if(strcmp(temp,"insert") == 0)
        {
            int number;
            string snumber;
            temp = strtok(NULL," ");
            sscanf(temp, "%d", &number);
            temp = strtok(NULL," ");
            snumber = temp;
            cout<<number<<":"<<snumber<<endl;
        }else if (strcmp(temp,"show") == 0)
        {   
            cout<<"show"<<endl;
        }else
        {
            exit = false;
        }
    }
    
    
    
    
    return 0;
}