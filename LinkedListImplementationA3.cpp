#include <stdio.h>
#include <iostream>

using namespace std;

class Node{ //This is a node class to represent linked list
    public:
    int row;
    int col;
    int value;
    Node *nextaddr; //Stores next node address.Constructer same as class name
};

void createNewNode(Node **p,int rowval,int colval,int dat){ //This is a function to create a new node
    Node *temporary=*p; //Temporary node address is created to store node *p new node address
    Node *r; //node r is reference node to next address

//If the there's no node exists then the temporary will be null then we need to create a new node
if(temporary==NULL){

    temporary= new Node(); //creating a first new node in list
    temporary->row=rowval;
    temporary->col=colval;
    temporary->value=dat;
    temporary->nextaddr=NULL;
    *p=temporary; //assigning temporary values to first header address
}
else
{
    while(temporary->nextaddr!=NULL)
    temporary=temporary->nextaddr;//using temporary to store the next address value before moving to next node
     r=new Node();
     r->row=rowval;
     r->col=colval;
     r->value=dat;
     r->nextaddr=NULL;
     temporary->nextaddr=r;

}
}

void printlinkedlist(Node* start){
    Node *pointer=start; //Starting node address to start print through linked list
while(pointer!=NULL){

    cout<<"    Row value: "<<pointer->row<<"\n";
    cout<<" Column value: "<<pointer->col<<"\n";
    cout<<"    value: "<<pointer->value<<"\n";
    pointer=pointer->nextaddr;
}
}

int main()
{ 
     // predefined 4x5 sparse matrix
    int sparseMatrix[4][5] = { { 0 , 0 , 3 , 0 , 4 }, { 0 , 0 , 5 , 7 , 0 },{ 0 , 0 , 0 , 0 , 0 },{ 0 , 2 , 6 , 0 , 0 } };
     
    // Creating head/first node of list as NULL
    Node *head = NULL;
    for(int i = 0; i < 4; i++)
    {        for(int j = 0; j < 5; j++)
     {
     if (sparseMatrix[i][j] != 0)//For sparse matrix we only consider non zero elements
      createNewNode(&head, i, j,sparseMatrix[i][j]);
        }
    }
    printlinkedlist(head);//Printing the linked list using this method
 
    return 0;
}
