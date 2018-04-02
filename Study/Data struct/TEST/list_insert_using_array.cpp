#include <stdio.h>

typedef struct {
    int num;
} T;

typedef struct {
    T   data[100];
    int length;    
} list;


int length(const list* lst)
{
    if (!lst) return -1;
    return lst->length;
}

void insert(list* lst, const T* item, int pos)
{
    if (!lst || !item || pos < 0 || pos > lst->length) return;

    for (int i=lst->length; i> pos; i--)
        lst->data[i] = lst->data[i-1];
    lst->data[pos] = *item;
    lst->length++;
}

void display(const list* lst)
{
    if (!lst) return;

    printf("length = %d, ( ", lst->length);
    for (int i=0; i<lst->length; i++)
        printf("%d ", lst->data[i].num);
    printf(")\n");
}

int main()
{
    list lst;
    lst.length = 0;
    
    T item;
    
    display(&lst);
    item.num = 2; insert(&lst, &item, 0); display(&lst);
    item.num = 1; insert(&lst, &item, 1); display(&lst);
    item.num = 3; insert(&lst, &item, 2); display(&lst);
    item.num = 7; insert(&lst, &item, 0); display(&lst);

    return 0;
}