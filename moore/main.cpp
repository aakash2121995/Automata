#include <iostream>
#include <cstdio>
#include <vector>
#include <cstring>

using namespace std;

int main()
{
    char temp[100];
    FILE*fp = fopen("input","r");
    int initialState;
    fscanf(fp,"%d",&initialState);

    //for reading states
    fgetc(fp);
    fgets(temp,99,fp);

    int noOfStates=0,noOfInputs = 0;
    int states[10][10];
    int num,offset;
    char *tempPtr = temp;
    while(sscanf(tempPtr,"%d%n",&num,&offset)!=-1)
    {
        states[noOfStates][noOfInputs] = num;
        tempPtr += offset;
        noOfInputs++;
    }

    noOfStates= 1;
    while(fscanf(fp,"%d",&num)!=-1)
    {
        states[noOfStates][0] = num;
        for(int i=1;i<noOfInputs;i++)
        {
            fscanf(fp,"%d",&num);
            states[noOfStates][i] = num;
        }
        noOfStates++;
    }

    int i,j;
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
        if(currentState==-1||input[i]-'0'>=noOfInputs-1)
            break;
        currentState = states[currentState][input[i]-'0'];
        cout<<states[currentState][noOfInputs-1];

        i++;
    }

    if(input[i]!='\0')
        cout<<"\nerror";
    }


    return 0;
}
