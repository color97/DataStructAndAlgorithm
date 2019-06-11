void splice( iterator position, List<T>& lst)
{
    Node* p = position.current;
    p->prev->next = lst.head->next;
    lst.head->next->prev = p->prev;
    lst.tail->prev->next = p;
    p->prev = lst.tail->prev;
    theSize += lst.size();


    lst.theSize = 0;
    lst.head->next = lst.tail;
    lst.tail->prev = lst->head;
}