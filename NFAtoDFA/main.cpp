#include<iostream>
#include<vector>
#include<algorithm>
#include<cstring>
#include<sstream>
#include<fstream>
#include<map>

using namespace std;

struct State
{
    vector<vector<int> > transitions;
};

vector<int> strToVector(string states)
{
    vector<int>coll;
    int len = states.length();

    for(int i=0;i<len;i++)
    {
        if(states[i]==',')
            continue;
        else if(states[i]=='-')
        {
            coll.push_back(-1);
            i++;
        }
        else
        coll.push_back(states[i]-'0');

    }
    return coll;
}

bool CheckFinalState(vector<int> finalStates,vector<int> states)
{
  for(int i=0;i<states.size();i++){
  vector<int>::iterator it;
  it = find (finalStates.begin(), finalStates.end(), states[i]);
  if (it != finalStates.end())
    return true;
}
    return false;
}
bool CheckFinalState(vector<int> finalStates,int state)
{
  vector<int>::iterator it;
  it = find (finalStates.begin(), finalStates.end(), state);
  if (it != finalStates.end())
    return true;
  return false;
}

int main()
{
    State TABLE[30];
    ifstream read("input");
    int initialState;
    read>>initialState;
    cout<<"Input NFA\n"<<initialState<<'\n';
    vector<int> finalStates;
    string line;
    int no;
    getline(read,line);
    getline(read,line);
    cout<<line;
    stringstream Final(line);
    while(Final>>no)
    {
        finalStates.push_back(no);
    }
    cout<<'\n';
    int i=0;
    while(getline(read,line))
    {
        string temp;
        cout<<line<<'\n';
        stringstream inputStates(line);
        while(inputStates>>temp)
        {
            vector<int>statesVec = strToVector(temp);
            TABLE[i].transitions.push_back(statesVec);
        }
        i++;
    }
    int noOfStates = i;
    int noOfInputs = TABLE[0].transitions.size();
    i=0;
    map<vector<int>,int> stateMap;
    vector<int>statesVec;
    while(i!=noOfStates)
    {
        for(int j=0;j<noOfInputs;j++)
        {
            if(TABLE[i].transitions[j].size()>1)
            {
                int state = stateMap[TABLE[i].transitions[j]];
                bool flag = false;
                if(state==0){
                    sort(TABLE[i].transitions[j].begin(),TABLE[i].transitions[j].end());
                    state = noOfStates;
                    stateMap[TABLE[i].transitions[j]] = state;
                    if(CheckFinalState(finalStates,TABLE[i].transitions[j]))
                        finalStates.push_back(state);
                    flag = true;
                    for(int k=0;k<noOfInputs;k++)
                    {
                        vector<int> temp ;
                        for(int l=0;l<TABLE[i].transitions[j].size();l++)
                        {
                            int index = TABLE[i].transitions[j][l];
                            if(TABLE[index].transitions[k][0] != -1)
                            {
                                vector<int> vc = TABLE[index].transitions[k];

                                for(int ind = 0;ind<vc.size();ind++)
                                    if(!CheckFinalState(temp,vc[ind]))
                                        temp.push_back(vc[ind]);
                            }
                        }

                        if(temp.size()==0)
                            temp.push_back(-1);

                        TABLE[noOfStates].transitions.push_back(temp);
                    }
                }
                vector<int> statesVec(1,state);
                TABLE[i].transitions[j] = statesVec;
                if(flag)
                    noOfStates++;
            }
        }
        i++;
    }

    cout<<"Output DFA\n"<<initialState<<'\n';

    for(int i=0;i<finalStates.size();i++)
        cout<<finalStates[i]<<' ';

    cout<<'\n';

    for(int i=0;i<noOfStates;i++)
    {
        for(int j=0;j<noOfInputs;j++)
        {
            cout<<TABLE[i].transitions[j][0]<<' ';
        }
        cout<<'\n';
    }

    return 0;
}
