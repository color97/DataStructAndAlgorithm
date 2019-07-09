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
            // 叶子节点存储数据， L 个数据项
            if (isLeaf)
            {
                keyValues = new T[MAXIMAL_L];
                children = nullptr;
            }
            // 非叶子节点，数据项为 M - 1 个，子节点为 M 个
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

        const T& minData() const
        {
            if (isLeaf)
            {
                return keyValues[0];
            }
            else
            {
                return children[0]->minData();
            }    
        }

        void updateKeyValues()
        {
            if (isLeaf)
            {
                for (size_t i = 0; i < keyNum; i++)
                {
                    // i 数据项指代第 i + 1 个子节点中的最小值
                    keyValues[i] = children[i+1]->minData()
                }
            }
        }

        void insertNonFull(const T& x)
        {
            int i = keyNum - 1;
            if (isLeaf)
            {
                while(i >= 1 && x < keyValue[i])
                {
                    keyValue[i+1] = keyValue[i];
                    i--;
                }

                keyValues[i+1] = x;
                keyNum++;
            }
            else
            {
                while(i >= 1 && x < keyValue[i])
                {
                    i--;
                }

                if (children[i]->isFull())
                {
                    splitChildNode(i, children[i]);
                    // 分裂子节点后，数据项有变化
                    if(x > keyValue[i])
                    {
                        i++;
                    }
                }
                children[i]->insertNonFull(x);

                // 更新数据项
                updateKeyValues();
            }
        }

        void splitChildNode(int index, BPlusNode* childNode)
        {
            const int newChildKeyNum = childNode->isLeaf ? MINIMAL_L : MINIMAL_M;
            BPlusNode* newChild = new BPlusNode(childNode->isLeaf, newChildKeyNum);

            // 拷贝最后 newChild->keyNum 个数据项给 newchild
            for (size_t i = 0; i < newChild->keyNum; i++)
            {
                newChild->keyValues[i] = childNode->keyValues[childNode->keyNum - newChild->keyNum + i + 1];
            }
            
            // 拷贝子节点 newChild->keyNum + 1 个
            if (!childNode->isLeaf)
            {
                for (size_t i = 0; i < newChild->keyNum + 1; i++)
                {
                    newChild->children[i] = childNode->children[childNode->keyNum - newChild->keyNum + i + 1];
                }
            }

            childNode->keyNum = childNode->keyNum - newChild->keyNum;
            // 移动出位置给新子节点
            for (size_t i = keyNum; i > index + 1; i)
            {
                children[i + 1] childNode[i];
            }

            children[i + 1] = newChild;
            keyNum++;

            updateKeyValues();
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
            s->insertNonFull(x);
            // const int childIndex = s->keyValues[0] < x ? 0 : 1;
            // s->children[i]->insertNonFull(x);

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