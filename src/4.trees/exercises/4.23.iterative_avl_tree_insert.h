#include <stack>

using namespace std;

void iterativeInsert(const Comparable& x)
{
    stack<AvlNode*> traveledNodes;
    AvlNode* t = root;
    
    // 记录所有遍历路径上的节点指针
    traveledNodes.push(t);
    while (t != nullptr)
    {
        if (x < t->element)
        {
            t = t->left;
            traveledNodes.push(t);
        }
        else if ( x > t->element)
        {
            t= t->right;
            traveledNodes.push(t);
        }
        else
        {
            return;
        }
    }

    t = new AvlNode{x, nullptr, nullptr};

    // 出栈，从插入位置到根节点，重新平衡 avl 树
    while (traveledNodes.size() > 0)
    {
        balance(traveledNodes.top());
        traveledNodes.pop();
    } 
}