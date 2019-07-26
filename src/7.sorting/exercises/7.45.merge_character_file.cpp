#include <fstream>
#include <string>
#include <iostream>

using namespace std;

void mergeFileByChar(const string& pOutFileName, const string& pInFileName1, const string& pInFileName2)
{
    ifstream file1(pInFileName1), file2(pInFileName2);
    if ( !file1.is_open() || !file2.is_open())
    {
        cout<<"file opened failed"<<endl;
        return;
    }

    ofstream result(pOutFileName);
    if (!result.is_open())
    {
        return;
    }
    
    while (file1.peek() != EOF && file2.peek() != EOF)
    {
        if (file1.peek() <= file2.peek())
        {
            char c = file1.get();
            result << c;
        }
        else
        {
            char c = file2.get();
            result << c;
        } 
    }
    
    while (file1.peek() != EOF)
    {
        result << file1.rdbuf();
    }
    
    while (file2.peek() != EOF)
    {
        result << file2.rdbuf();
    }
}

int main()
{
    mergeFileByChar(
        "resources\\out.txt"
        , "resources\\character_file1.txt"
        , "resources\\character_file2.txt"
        );

    return 0;
}