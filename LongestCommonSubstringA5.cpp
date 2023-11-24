#include<iostream>
#include<string>
#include<vector>
using namespace std;

//creating a method with two parameter string and two return type which returns 2D vector matrix and longest common substring
std::pair<std::vector<std::vector<int>>,std::string> LCS( const std::string& string1, const std::string& string2){
int length=string1.length();

int maximumlen=0; //To store length of LCS
int last_position=0;//To store end position of the LCS

std::vector<std::vector<int>> vectable(length+1,std::vector<int>(length+1,0)); //This is Vector table to find LCS

for( int i=1;i<=length;i++){
    for( int j=1;j<=length;j++){

        if(string1[i-1]==string2[j-1]){
            vectable[i][j]=vectable[i-1][j-1]+1;

            if(vectable[i][j]>maximumlen){
                maximumlen=vectable[i][j];
                last_position=i-1;
            }

        }else{
            vectable[i][j]=0;
        }

    }
}

//Here we retrive the longest common substring and store into a string
//we use string substr method which takes two parameters starting index and length to retrive a substring
std::string LCSubstring= string1.substr(last_position-maximumlen+1,maximumlen);

return{vectable,LCSubstring};

}

int main() {

string str1,str2;
cout<<"Enter First string: ";
cin>>str1;
cout<<"Enter second string to retrive LCS: ";
cin>>str2;
    std::string string1 = str1;//"ABAB";
    std::string string2 = str2;//"BABA";

    auto result = LCS(string1, string2); //Store the return results of LCS into the result dymanic storage

    // Print the dp table
    for (const auto& row : result.first) { //result.first here holds the matrix table
        for (int value : row) {
            std::cout << value << " ";
        }
        std::cout << std::endl;
    }

    string Lc=result.second; // result.second here holds the Longest common substring

    // Print one of the longest common substrings (in case of a tie)
    cout << "Longest Common Substring: " << Lc << endl;
    cout<<"Length of Longest common Substring: "<< Lc.size()<<endl;

    return 0;
}