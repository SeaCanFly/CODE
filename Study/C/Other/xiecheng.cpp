#include <stdio.h>
typedef struct
{
    int i;
    int num;
    int state;
} task;
int cb(task *t)
{
    switch (t->state)
	{
    case 0:
        for (;;)
		{
            t->num = 1;
            for (t->i = 0; t->i < 20; t->i++) 
			{
                t->state = __LINE__ + 2;
                return t->num;
    			case __LINE__:
                t->num += 1;
            }
        }
    }
}
int main()
{
    task t;
    int i;

    t.state = 0;

    for (i = 0; i < 100; i++) 
	{
        printf("%d ", cb(&t));
    }
    return 0;
}
