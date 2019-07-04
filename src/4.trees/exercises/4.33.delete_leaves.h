Node* deleteLeaves( Node* t)
{
    if (t == nullptr)
    {
        return t;
    }
    else if ( t->left == nullptr && t->right == nullptr)
    {
        delete t;
        return nullptr;
    }
    else
    {
        t->left = deleteLeaves(t->left);
        t->right = deleteLeaves(t->right);
        return t; 
    }

}