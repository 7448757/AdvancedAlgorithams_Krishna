#include<stdio.h>
#include <climits>
#include <iostream>
using namespace std;

#define V 5 // Since we have 5 vertices

//This method is to find the minimum distance vertex from unvisited nodes
int minimum_Distance(int dist[],bool visitedNode[]){
    int minimum= INT_MAX,minimum_distance_index;
    for(int v=0;v<V;v++){
        if(visitedNode[v]==false && dist[v]<=minimum){
            minimum=dist[v];
            minimum_distance_index=v;
        }
    }
return minimum_distance_index;
}

//Printing the final output i.e vertex and its distance from source
void printSol(int dist[],int n){
cout<<"Vertex"<<"   "<< "distance of vertex\n";
for(int i=0;i<V;i++){
cout<<i<<"   ";
if(dist[i]==INT_MAX){// for better user understanding maximum value is displayed as infinity
cout<<"INFINITY"<<"\n";
}else{
    cout<<dist[i]<<"\n";
}

}
}

//The Algoritham
void DijkstraAlgo(int source_vertex,int agraph[V][V]){
//declare array to hold distance and bool value for visited/unvisited nodes
int dist[V];
bool visitedNode[V];

for(int i=0;i<V;i++){
    //initally update all vertex distance as infinity and boolean of visited node as false
    dist[i]=INT_MAX; 
    visitedNode[i]=false; 
}
//Since we start from source the distance from source to source is zero
dist[source_vertex]=0;

//For all the vertices we perform dijkstras algoritham to find minimum distance from source
for(int count =0;count<V-1;count++){
    int u=minimum_Distance(dist,visitedNode); //get minimum distance node or vertex from set of vertices
    visitedNode[u]=true; //update the selected minimum distance vertex as visited by making visited node of vertex as true

    for(int v=0;v<V;v++){
        /*if distance of selected vertex plus distance of selected and destination is less than distance of destination then update 
        minimum value*/
        if(!visitedNode[v]&&agraph[u][v]&&dist[u]!=INT_MAX
        && dist[u]+agraph[u][v]<dist[v]){
            dist[v]=dist[u]+agraph[u][v];
        }
    }
}
printSol(dist,V);

}

int main(){
    int source_ver;
    //implemented graph using 2D array
    int agraph[V][V]={{0,10,0,0,3},
                           {0,0,2,0,4},
                           {0,0,0,9,0},
                           {0,0,7,0,0},
                           {0,1,8,2,0}};

// user input source vertex to find distance to all other vertices from source
    cout<<"Please enter source vertex to find distance to all other vertices: ";
    cin>>source_ver;
if(source_ver<V){
  DijkstraAlgo(source_ver,agraph);
}else{
    cout<<"Enter valid source vertex(i.e < "<<V<<")";
}
  return 0;

}