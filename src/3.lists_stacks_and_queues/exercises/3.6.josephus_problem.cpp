#include <iostream>
#include <list>

using namespace std;

int josephus_problem(int m, int n)
{
    // initialize data
    list<int> players;
    for (size_t i = 0; i < n; i++)
    {
        players.push_back(i + 1);
    }
    
    list<int>::iterator itr = players.begin();
    while (players.size() > 1)
    {
        for (size_t passStep = m % players.size(); passStep > 0; passStep--)
        {  
            itr++;
            if (itr == players.end())
            {
                itr = players.begin();
            }
        }
        
        cout<<"removed "<<*itr<<endl;
        itr = players.erase(itr);
        if(itr == players.end())
        {
            itr = players.begin();
        }
    }
    
    cout<<"winner is: "<< players.front()<<endl<<endl;
    return players.front();
}

int main()
{
    josephus_problem(0, 5);
    josephus_problem(1, 5);
    josephus_problem(1, 100000);
}
