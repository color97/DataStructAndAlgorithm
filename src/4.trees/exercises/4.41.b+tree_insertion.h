#include <vector>

#define M   5
#define L   7

using namespace std;

template <typename T>
struct BPlusNode
{
    vector<T>   keywords;
    vector<BPlusNode*> children;
};

template <typename T>
void insert(BPlusNode<T>*& t, const T& x)
{
    if (t == nullptr)
    {
        return;
    }

    int childIndex = t->keywords.size();
    for (size_t i = 0; i < t->keywords.size(); i++)
    {
        if (x < t->keywords[i])
        {
            childIndex = i;
            break;
        }
    }
    
    if (!t->children.empty())
    {
        insert(t->children[childIndex], x);
    }
    else
    {
        if (/* condition */)
        {
            /* code */
        }
        
    }  
}