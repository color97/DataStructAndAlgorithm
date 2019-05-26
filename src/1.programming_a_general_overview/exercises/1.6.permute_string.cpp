#include <iostream>
#include <string>

using namespace std;

void permute(const string& str, int low, int high)
{
    if(low == high)
    {
        cout<<str<<endl;
    }

    string copy_str = str;

    for (size_t i = low; i <= high; i++)
    {
        swap(copy_str[i], copy_str[low]);
        permute(copy_str, low + 1, high);
        swap(copy_str[i], copy_str[low]);
    }
}

void permute(const string& str)
{
    permute(str, 0, str.size() - 1);
}

int main()
{
    string str = "abc";
    permute(str);
}