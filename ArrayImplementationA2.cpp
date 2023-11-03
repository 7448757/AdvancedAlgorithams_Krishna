#include<stdio.h>
#include<iostream>
using namespace std;
int main(){
    /* Array implementation for sparse matrix*/
 int Sarray[4][5]={{0,0,3,0,4},{0,0,5,7,0},{0,0,0,0,0},{0,2,6,0,0}};
 int valuecount=0;//valuecount is the number of non zero elements in matrix. Using this we can also decide the column size for sparsematrix representation

//Below for loop tells the row and column number of the non zero value to be considered for sparse matrix in an array.
 for(int i=0;i<4;i++){
    for(int j=0;j<5;j++){
        if(Sarray[i][j]!=0){
        cout<<"Row: "<<i<<" Column: "<<j<<" Value: "<<Sarray[i][j]<<"\n";
        valuecount++;
    }
    }
 }   

 cout<<"Total non zero elements: "<<valuecount<<"\n";

 //Lets create a 2D array with three rows which holds row number, column number and value of sparse elements.
 int sparseMat[3][valuecount];
 int k=0;    //Here k  is the column number in sparse matrix.
    for(int l=0;l<4;l++){
        for(int m=0;m<5;m++){
                if(Sarray[l][m]!=0){
                    sparseMat[0][k]=l;
                    sparseMat[1][k]=m;
                    sparseMat[2][k]=Sarray[l][m];
                    k++; // we increment k value since we need to move into a new column to store new non zero element details(i.e row number,column number and value)
                }
        }
    }
//Below is the final representation of sparse matrix usinf 2D array 
    for(int r=0;r<3;r++){
        cout<<"\n";
        for(int c=0;c<valuecount;c++){
            cout<<sparseMat[r][c]<<" ";
            
        }
    }
    return 0;

}