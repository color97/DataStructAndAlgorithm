#define MINIMAL_M   5
#define MINIMAL_L   7
#define MAXIMAL_M   2*MINIMAL_M
#define MAXIMAL_L   2*MINIMAL_L


template <typename T>
class BPlusTree
{
public:
    struct BPlusNode
    {
        bool        isLeaf;
        int         keyNum;
        T*          keyValues;
        BPlusNode** children;

        BPlusNode(bool pIsLeaf = true, int pKeyNum = 0 )
        : isLeaf(pIsLeaf), keyNum(pKeyNum)
        {
            if (isLeaf)
            {
                keyValues = new T[MAXIMAL_L];
                children = nullptr;
            }
            else
            {
                keyValues = new T[MAXIMAL_M - 1];
                children = new BPlusNode*[MAXIMAL_M]
            }  
        }

        bool isFull() const
        {
            if (isLeaf)
            {
                return keyNum >= MAXIMAL_L;
            }
            else
            {
                // 非叶子节点数据项为 M - 1
                return keyNum >= MAXIMAL_M - 1;
            }
        }

        void insertNonFull(const T& x)
        {
            int i = keyNum - 1;
            if (isLeaf)
            {
                while(i >= 1 && k < x->keyValue[i])
                {
                    x->keyValue[i+1] = x->keyValue[i];
                    i--;
                }

                keyValues[i+1] = k;
                keyNum++;
            }
            else
            {
                while(i >= 1 && k < x->keyValue[i])
                {
                    i--;
                }

                if (children[i]->isFull)
                {
                    splitChildNode(i, children[i]);
                }
                children[i]->insertNonFull(x);
            }
        }

        void splitChildNode(int index, BPlusNode* childNode)
        {

        }
    };

public:
    BPlusTree(): root(nullptr) {}

    void insert(const T& x)
    {
        if (root == nullptr)
        {
            root = new BPlusNode();
            root->insertNonFull(x);
        }
        else if ( root->isFull() )
        {
            BPlusNode* s = new BPlusNode(false);

            s->children[0] = root;
            s->splitChildNode(0, root);
            
            const int childIndex = s->keyValues[0] < x ? 0 : 1;
            s->children[i]->insertNonFull(x);

            root = s;
        }
        else
        {
            root->insertNonFull(x);
        }
    }


private:
    BPlusNode* root;
};

// template <typename T>
// void insert(BPlusNode<T>*& t, const T& x)
// {
//     if (t == nullptr)
//     {
//         return;
//     }

//     int childIndex = t->keywords.size();
//     for (size_t i = 0; i < t->keywords.size(); i++)
//     {
//         if (x < t->keywords[i])
//         {
//             childIndex = i;
//             break;
//         }
//     }
    
//     if (!t->children.empty())
//     {
//         insert(t->children[childIndex], x);
//     }
//     else
//     {
//         if (/* condition */)
//         {
//             /* code */
//         }
        
//     }  
// }