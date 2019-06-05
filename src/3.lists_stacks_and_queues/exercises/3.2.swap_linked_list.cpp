// single linked list
void swapTwoNodes(Node* beforeP)
{
    Node* p = beforeP->next, afterP = p->next;
    p->next = afterP->next;
    afterP->next = p;
    beforeP->next = afterP;
}
// doubly linked list
void swapTwoNdes(Node* beforeP)
{
    Node* p = beforeP->next, afterP = p->next;
    p->next = afterP->next;
    afterP->next->prev = p;
    afterP->next = p;
    p->prev = afterP;
    afterP->prev = beforeP;
    beforeP->next = afterP;
}