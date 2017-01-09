#include <iostream>
#include<cstring>
#include<vector>
#include<algorithm>
#include<fstream>
#include<sstream>
using namespace std;

bool CheckFinalState(vector<int> finalStates,int state)
{
    vector<int>::iterator it;
    it = find (finalStates.begin(), finalStates.end(), state);
    if (it != finalStates.end())
        return true;
    else
        return false;
}

int main()
{
    ifstream read("input");
    int no;
    int initialState;
    read>>initialState;
    cout<<"Input DFA\n"<<initialState<<'\n';
    vector<int> finalStates;
    string line;
    getline(read,line);
    getline(read,line);
    cout<<line;
    stringstream Final(line);
    while(Final>>no)
    {
        finalStates.push_back(no);
    }

    int noOfStates=0,noOfInputs;
    int states[50][10];

    while(getline(read,line))
    {
        cout<<'\n'<<line;
        stringstream StateLine(line);
        noOfInputs = 0;
        while(StateLine>>states[noOfStates][noOfInputs])
        {
            noOfInputs++;
        }
        noOfStates++;
    }

    char input[100];
    while(1){
        cout<<"\nEnter String (quit for quiting): ";
        cin>>input;

        if(strcmp(input,"quit")==0)
            break;

        int currentState = initialState;
        int i = 0;
        while(currentState!=-1&&input[i]!='\0')
        {
            currentState = states[currentState][input[i]-'0'];
            i++;
        }

        if(input[i]=='\0'&&CheckFinalState(finalStates,currentState))
            cout<<"Accepted\n";
        else
            cout<<"Not accepted\n";
    }
    return 0;
}
