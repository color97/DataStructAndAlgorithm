struct Node
{
    int element;
    Node* left;
    Node* right;

    Node(const int& x, Node* lt, Node* rt)
    : element(x), left(lt), right(rt)
    {}
};

Node* minimalAVLTree(int& min, int& max, int height)
{
    if (height = 0)
    {
        min = max = RandInt();
        return new Node{ min, nullptr, nullptr};
    }
    else if (height == -1)
    {
        return nullptr;
    }
    
    
    int leftMin, leftMax, rightMin, rightMax;
    Node* left = minimalAVLTree(leftMin, leftMax, height - 1 );
    Node* right = minimalAVLTree(leftMin, leftMax, height - 2 );

    int element = right != nullptr ? RandInt(leftMax, rightMin) : leftMax + 1;
    return new Node{element, left, right};
}