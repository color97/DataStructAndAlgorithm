template <typename Comparable>
struct AvlNode
{
    Comparable  element;
    AvlNode*    left;
    AvlNode*    right;
    int         height;

    AvlNode(const Comparable& x, AvlNode* lt, AvlNode* rt, int h = 0)
    : element(x), left(lt), right(rt), height(h)
    {}
    AvlNode(Comparable&& x, AvlNode* lt, AvlNode* rt, int h = 0)
    : element(std::move(x)), left(lt), right(rt), height(h)
    {}
};

template <typename Comparable>
bool isBalance(AvlNode<Comparable>* t)
{
    if(nullptr == t)
    {
        return true;
    }
    
    if (isBalance(t->left) && isBalance(t->right))
    {
        return t->height == max(height(t->left), height(t->right)) + 1;
    }
    
    return false;
}