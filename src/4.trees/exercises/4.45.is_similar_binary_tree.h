
template<typename T>
struct BinaryNode
{
    T   data;
    BinaryNode* left;
    BinaryNode* right;
};


template<typename T>
bool isSimilar(const BinaryNode<T>* lhs, const BinaryNode<T>* rhs)
{
    // if (lhs == nullptr && rhs == nullptr)
    // {
    //     return true
    // }
    // else if (lhs != nullptr && rhs != nullptr)
    // {
    //     return isSimilar(lhs->left, rhs->left) && isSimilar(lhs->right, rhs->right);
    // }
    // // 其中之一是 nullptr, 不相似
    // else
    // {
    //     return false;
    // }
    
    // 标准答案
    if( lhs == nullptr || rhs == nullptr )
        return lhs == nullptr && rhs == nullptr;
    return isSimilar( lhs->left, rhs->left ) && isSimilar( lhs->right, rhs->right );
}