bool isbalance()
{
    return balance(t->left) && balance(t->right) && balance(t);
}

bool isbalance(AvlNode*& t)
{
    if(nullptr == t)
    {
        return true;
    }
    else if (height(t->left) - height(t->right) > 1)
    {
        return false;
    }
    else if (height(t->right) - height(t->left) > 1)
    {
        return false;
    }
    
    if(t->height != max(height(t->left), height(t->right)) + 1 )
    {
        return false;
    }
}