#include <vector>

using namespace std;

class DisjSets
{
public:
    explicit DisjSets(int numElements) : s{numElements, -1}
    { }

    // path comprass
    int find(int x)
    {
        if (s[x] < 0)
        {
            return s[x];
        }
        else
        {
            return s[x] = find(s[x]);
        }
    }

    // union by rank
    void unionSets(int root1, int root2)
    {
        if (s[root2] < s[root1])
        {
            s[root1] = root2;
        }
        else
        {
            if (s[root1] == s[root2])
            {
                --s[root1];
            }
            s[root2] = s[root1];
        }
    }

private:
    vector<int> s;
};