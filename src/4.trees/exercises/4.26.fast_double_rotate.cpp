
void fastDoubleWithLeftChild( AvlNode*& k3)
{
    AvlNode* k1 = k3->left;
    AvlNode* k2 = k1->right;

    k1->right = k2->left;
    k2->left = k1;
    k3->left = k2->right;
    k2->right = k3;

    k1->height = max( height( k1->left), height(k1->right)) + 1;
    k3->height = max( height( k3->left), height(k3->right)) + 1;
    k2->height = max( height( k2->left), height(k2->right)) + 1;

    k3 = k2;
}