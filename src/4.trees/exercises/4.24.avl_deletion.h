void remove(const Comparable& x, AvlNode*& t)
{
    if (t == nullptr)
    {
        return;
    }
    else if (x < t->element)
    {
        remove(x, t->left);
    }
    else if ( x > t->element)
    {
        remove(x, t->right);
    }    
    else if (t->left != nullptr && t->right != nullptr)
    {
        t->element = findMin(t->right)->element;
        remove(t->element, t->right);
    }
    else
    {
        AvlNode* old = t;
        t = t->left != nullptr ? t->left : t->right;
        delete old;
    }
    balance(t);
}