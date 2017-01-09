#include <iostream>
#include <vector>
#include <cstring>
#include<fstream>
#include<cstdlib>
using namespace std;

int main()
{
    char temp[100],temp2[100];
    ifstream input,inputTemp;
    input.open("input");
    ofstream outputTemp;
    FILE *fp = fopen("temp","w");
    int initialState;
    input>>initialState;
    int finalState;
    input>>finalState;
    //for reading states

//    getline(temp,10,fp)
    //    getline(input,temp);
    char *pch;
    char *pch2;
    input.ignore();
    while(input.getline(temp,100)){
        pch = strtok(temp," ");
        int len = strlen(pch);
        while(pch!=NULL){
//            cout<<pch<<endl;
            strcpy(temp2,pch);
            pch2 = strtok(temp2,",");
            while(pch2!=NULL){
                cout<<pch2;
                pch2 = strtok(NULL,",");
            }
        pch = strtok(temp+len-1," ");
        }
    }

//    input.getline(temp,100);
//    cout<<temp;
//    cout<<initialState;
//    cout<<finalState;
//    cout<<temp;
    exit(0);
//    fgetc(fp);
//    fgets(temp,99,fp);
//    fputs(temp,tempFile);

//    fclose(tempFile);
//    tempFile = fopen("temp","r");
//    int noOfStates,noOfInputs = 0;
//    int states[10][10];
//    int num;
//    while(fscanf(tempFile,"%d",&num)!=-1)
//    {
//        states[noOfStates][noOfInputs] = num;
//        noOfInputs++;
//    }
//    fclose(tempFile);
//    noOfStates= 1;
//    while(fscanf(fp,"%d",&num)!=-1)
//    {
//        states[noOfStates][0] = num;
//        for(int i=1;i<noOfInputs;i++)
//        {
//            fscanf(fp,"%d",&num);
//            states[noOfStates][i] = num;
//        }
//        noOfStates++;
//    }
////    cout<<noOfStates;
////    cout<<noOfInputs;
////    cout<<states[0][0]<<states[0][1]<<states[1][0]<<states[1][1]<<states[2][0]<<states[2][1];
//    int i,j;
//    char input[100];
//    while(1){
//    cout<<"Enter String (quit for quiting): ";
//    cin>>input;
//    if(strcmp(input,"quit")==0)
//        break;
//
//    int currentState = 0;
//    int i = 0;
//    while(currentState!=-1&&input[i]!='\0')
//    {
//        currentState = states[currentState][input[i]-'0'];
//        i++;
//    }
//
//    if(currentState == finalState&&input[i]=='\0')
//        cout<<"Accepted\n";
//    else
//        cout<<"Not accepted\n";
//
//    }
//    for(i = 0;i < noOfStates;i++)
//    {
//        for(j = 0;j< noOfInputs;j++)
//        cout<<states[i][j];
//    }

    return 0;
}
