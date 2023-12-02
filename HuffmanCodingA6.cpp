#include<stdio.h>
#include<queue>
#include<iostream>
#include<vector>
#include<algorithm>
#include<unordered_map>

using namespace std;


struct Node{ //Node structure to store character, frequency and its left and right connecting node pointer values for huffmans tree
    char dataValue;
    int frequencyOfData;
    Node *right;
    Node *left;

    Node(char c,int f): dataValue(c),frequencyOfData(f),left(nullptr),right(nullptr){}
    
};

struct CompareDataNodes {
    bool operator()(Node* a, Node* b){//Function to compare nodes in priority queue. This return true or false

        return a->frequencyOfData>b->frequencyOfData;

    }
};


void PrintingHuffmanCodes(Node *root, string code, unordered_map<char, string >&HuffmanCodes){ //Printing Huffman codes for respective characters
    if( root == nullptr){ //if root node is null then return as there's no tree
        return;
    }

    if(root->dataValue!='#'){ //if there's a data value other then # in root node then store the code in HuffmanCodes string
        HuffmanCodes[root->dataValue]=code;
    }

    PrintingHuffmanCodes(root->left,code+"0",HuffmanCodes);// print left connecting nodes as 0 in the tree
    PrintingHuffmanCodes(root->right,code+"1",HuffmanCodes);//print right connecting nodes as 1 in the tree
}

void makeHuffmanTree(string character,int frequencyOfdataValue[],int n){ //Here we are building a Huffman tree using Minimum heap,priority queue
    priority_queue<Node*,vector<Node*>,CompareDataNodes> minimumHeap; // priority queue named minimumHeap which store Node pointers using vector as containers. it uses comparesNodes logic to order elements in the queue

for(int i=0;i<n;i++){ //creating a tree by pushing data into the queue with value and its frequency performing minimumHeap
    Node* newNode= new Node(character[i],frequencyOfdataValue[i]);
    minimumHeap.push(newNode);
}

while(minimumHeap.size()>1){ //while the queue is not empty load values to left nodes and right nodes
Node *left=minimumHeap.top();
minimumHeap.pop();
Node *right=minimumHeap.top();
minimumHeap.pop();

Node* insideNode= new Node('#',left->frequencyOfData+right->frequencyOfData);

insideNode->left=left;
insideNode->right=right;

minimumHeap.push(insideNode);

}

Node* root=minimumHeap.top(); //assigning the root node pointer as minimimumHeap's queue top value 

unordered_map<char,string> huffmanCodeTree; //defining an unordered map named huffmancodeTree

string code="";
PrintingHuffmanCodes(root,code,huffmanCodeTree); // printing huffman's codes for the values
cout<<"The Huffman codes for the given values and frequencies are: "<<endl;

for(auto& val:huffmanCodeTree){
    cout<<" "<<val.first<<" : "<<val.second<<endl;
}
}

int main(){ //Main funciton we define the input data here for the huffman code tree
    string s="abcdef";
    int freq[]={5,9,12,13,16,45};
    int n=sizeof(freq)/sizeof(freq[0]); // here n is the number of elements in the array freq where sizeof[freq] returns bytes occupied by a single element
    makeHuffmanTree(s,freq,n);
    return 0;

}