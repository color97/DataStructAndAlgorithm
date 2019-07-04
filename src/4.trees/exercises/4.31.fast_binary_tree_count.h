
int CountNode(BinaryNode* t)
{
    if ( t == nullptr)
    {
        return 0;
    }

    // 需要累计父节点和子节点
    return 1 + CountNode(t->left) + CountNode(t->right);    
}

int CountLeave(BinaryNode* t)
{
    if ( t == nullptr)
    {
        return 0;
    }
    else if ( t->left == nullptr && t->right == nullptr)
    {
        return 1;
    }
    
    // 父节点不可能为叶子节点，不累计
    return CountLeave(t->left) + CountLeave(t->right);
}

// or CountLeave() - 1
int CountFullNode(BinaryNode* t)
{
    if ( t == nullptr)
    {
        return 0;
    }

    // 累计父节点及其子节点
    const int fullNodeCount = (t->left != nullptr && t->right != nullptr) ? 1 : 0;  
    return fullNodeCount + CountFullNode(t->left) + CountFullNode(t->right);
}