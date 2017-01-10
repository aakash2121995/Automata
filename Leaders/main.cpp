#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>
#include <map>
#include <tr1/unordered_set>
using namespace std::tr1;
using namespace std;

bool dfs(int target,int removed,int cfg[30][30],int source,int lSize,vector<bool>& visited)
{
    //cout<<source<<'\n';
    visited[source] = true;
    for(int i=1;i<=lSize;i++)
    {
        if(source==target)
            return true;
        else if(i!=removed&&cfg[source][i]&&!visited[i])
        {
            bool ans = dfs(target,removed,cfg,i,lSize,visited);
            if(ans)
                return true;
        }
    }
}

int main()
{
    map<int,int> stateToBlock;
    ifstream read("input.c");
    string line;
    unordered_set <int>leaders;
    int lineNo = 0;
    leaders.insert(1);
    vector<int>leads;
    while(getline(read,line))
    {
        lineNo++;
        //cout<<line<<'\n';
        string firstStatement;
        stringstream code(line);
        code>>firstStatement;

        if(firstStatement.compare("goto")==0)
        {
            int leader;
            code>>leader;
            leaders.insert(leader);
            leaders.insert(lineNo+1);
        }
        else if(firstStatement.compare("if")==0)
        {
            int leader;
            string temp;
            code>>temp;
            code>>temp;
            code>>leader;
            leaders.insert(leader);
            leaders.insert(lineNo+1);
        }
    }
    cout<<"Leaders are:";
    for (unordered_set<int>:: iterator it = leaders.begin(); it != leaders.end(); ++it )
        leads.push_back(*it);

    sort(leads.begin(),leads.end());
    int lSize = leads.size();
    for(int i=0;i<lSize;i++)
    {
        cout<<leads[i]<<' ';
    }
    cout<<"\n\nBlocks\n";
    int i;
    for( i=0;i<lSize-1;i++)
    {
        cout<<"Block "<<i+1<<" : "<<leads[i]<<"->"<<leads[i+1]-1<<'\n';
        stateToBlock[leads[i]] = i+1;
    }
    stateToBlock[leads[i]] = i+1;
    cout<<"Block "<<i+1<<": "<<leads[i]<<"->"<<lineNo<<'\n';
    read.clear();
    read.seekg(0,read.beg);
    lineNo = 0;
    int block=1;

    cout<<"\nCFG: \n";
    int cfg[30][30] = {{0}};
    while(getline(read,line))
    {
        lineNo++;
        //cout<<line;
        if(lineNo==leads[block]-1)
        {
            string firstStatement;
            stringstream code(line);
            code>>firstStatement;
            cout<<block<<" : ";
            if(firstStatement.compare("goto")==0)
            {
                int leader;
                code>>leader;
                cfg[block][stateToBlock[leader]] = 1;
                cout<<stateToBlock[leader]<<'\n';
            }
            else if(firstStatement.compare("if")==0)
            {
                int leader;
                string temp;
                code>>temp;
                code>>temp;
                code>>leader;
                cfg[block][stateToBlock[leader]] = 1;
                cfg[block][block+1] = 1;
                cout<<stateToBlock[leader]<<' ' <<block + 1<<'\n';
            }
            else{
                cout<<block+1<<'\n';
                cfg[block][block+1] = 1;
            }
            block++;
        }
    }
    cout<<block<<" : "<<'\n';

    cout<<"\nNatural loops are:-\n";

    for(int i=1;i<=lSize;i++)
    {
        for(int j=1;j<=lSize;j++)
        {
            if(i>j&&cfg[i][j])
            {
                cout<<i<<"->"<<j<<" : "<<i<<','<<j;
                for(int node = 1;node<=lSize;node++)
                {
                    if(node==i||node==j)
                        continue;
                    vector<bool>visited(lSize+1);
                    if(dfs(i,j,cfg,node,lSize,visited))
                        cout<<','<<node;
                }
                cout<<'\n';
            }
        }
    }
    cout<<"\nDominators are:-\n";
    cout<<"1 Dominates :- ";
    for(int i=1;i<=lSize;i++)
        cout<<i<<' ';

    for(int i=2;i<=lSize;i++)
    {
        cout<<'\n'<<i<<" Dominates :- "<<i<<' ';
        for(int j=1;j<=lSize;j++)
        {
            if(j==i)
                continue;
            vector<bool>visited(lSize+1);
            if(!dfs(j,i,cfg,1,lSize,visited))
                cout<<j<<' ';
        }
    }
    return 0;

}
