
#include <iostream> 
  
using namespace std; 
int main() 
{ 
    int totalinputs,targetvalue,consideredvalue[2];
  { 
   cout<<"Enter total inputs:";
  cin>>totalinputs;
  cout<<"total inputs are :"<<totalinputs<<"\n";
  int numbers[totalinputs];
  for(int i=0;i<=totalinputs-1;i++){
    int num;
    cout<<"Enter number "<<i+1<<": ";
    cin>>num;
    numbers[i]=num;
  }
  cout<<"Numbers entered are: ";
  for(int j=0;j<=totalinputs-1;j++)
  {
    cout<<numbers[j]<<" ";
  }
  cout<<"\nEnter target value: ";
  cin>>targetvalue;
  cout<<" \nTarget value is: "<<targetvalue<<"\n";

  for(int cv=0;cv<=totalinputs-1;cv++)
  {
    for(int cv2=1;cv2<=totalinputs-1;cv2++){
        if(numbers[cv]+numbers[cv2]==targetvalue)
        {
            cout<<"Considered indices are :"<<cv<<" "<<cv2;
    }
    }
  }

   
    return 0; 
}