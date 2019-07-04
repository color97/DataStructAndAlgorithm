
int CountNode(BinaryNode* t)
{
    if ( t == nullptr)
    {
        return 0;
    }

    return 1 + CountNode(t->left) + CountNode(t->right);    
}

int CountLeave(BinaryNode* t)
{
    if ( t == nullptr)
    {
        return 1;
    }
    
    return CountNode(t->left) + CountNode(t->right);
}

int CountFullNode(BinaryNode* t)
{
    if ( t == nullptr)
    {
        return 1;
    }

    return CountNode(t->left) + CountNode(t->right);
}