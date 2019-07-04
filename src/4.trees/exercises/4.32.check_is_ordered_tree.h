
bool isOrderdSearchTree(BinaryNode* t)
{
    int min, max;
    return isOrderdSearchTree(min, max, t);
}

bool isOrderdSearchTree( int& min, int& max, BinaryNode* t )
{
    if (t == nullptr)
    {
        return true;
    }

    int leftMin = 0, leftMax = 0, rightMin = 0, rightMax = 0;
    if (isOrderdSearchTree(leftMin, leftMax, t->left) && isOrderdSearchTree(rightMin, rightMax, t->right))
    {
        min = t->left != nullptr ? leftMin : t->element;
        max = t->right != nullptr ? rightMax : t->element;

        return t->left != nullptr ? leftMax < t->element : 
                (t->right != nullptr ? rightMin > t->element : true);
    }
    

    return  false;
}