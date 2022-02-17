#include "../classi/RBT.h"
#include <iostream>
#include <sstream>

using namespace std;

void input(string &choice,int &value,string &stringValue){
    string line;
    getline(cin,line);
    istringstream iss(line);
    iss>>choice;
    iss>>value;
    iss>>stringValue;
    cin.clear();
}

int main() {
    RBT *root = nullptr;
    string choice;
    int value;
    string stringValue;

    do{
        input(choice,value,stringValue);
        if(choice == "insert"){
            root = root->insert(root,value, stringValue);
        }
        if(choice == "show"){
            root->preOrder(root);
            cout<<endl;
        }
        if(choice == "find"){
            RBT* temp = root->find(root, value);
            if (temp)
                cout<<temp->getStringKey(temp);
            else
                cout<<"NULL";
            cout<<endl;
        }
    } while (choice!="exit");

    return 0;
}