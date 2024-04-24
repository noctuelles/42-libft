//
// Created by plouvel on 24/04/24.
//

#include "libft.h"

void ft_dlstsort(t_dlist **lst, int (*cmp)(void *, void *))
{
    t_dlist *tmp;
    t_dlist *tmp2;
    void *swap;

    tmp = *lst;
    while (tmp)
    {
        tmp2 = tmp->next;
        while (tmp2)
        {
            if (cmp(tmp->content, tmp2->content) > 0)
            {
                swap = tmp->content;
                tmp->content = tmp2->content;
                tmp2->content = swap;
            }
            tmp2 = tmp2->next;
        }
        tmp = tmp->next;
    }
}