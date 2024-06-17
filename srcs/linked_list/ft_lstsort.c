/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsort.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plouvel <plouvel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 12:56:03 by plouvel           #+#    #+#             */
/*   Updated: 2024/06/17 13:48:23 by plouvel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <assert.h>

#include "libft.h"

/**
 * @brief Split the list in src into two sublist.
 *
 * @param src
 * @param front
 * @param back
 */
static void
split_sublst(t_list *src, t_list **front, t_list **back) {
    t_list *fast = NULL;
    t_list *slow = NULL;

    slow = src;
    fast = src->next;
    while (fast != NULL) {
        fast = fast->next;
        if (fast != NULL) {
            slow = slow->next;
            fast = fast->next;
        }
    }
    *front     = src;
    *back      = slow->next;
    slow->next = NULL;
}

static t_list *
sorted_merge(t_list *a, t_list *b, int (*pred)(const void *, const void *)) {
    t_list *rslt = NULL;

    if (a == NULL) {
        return (b);
    }
    if (b == NULL) {
        return (a);
    }
    if (pred(a->content, b->content) <= 0) {
        rslt       = a;
        rslt->next = sorted_merge(a->next, b, pred);
    } else {
        rslt       = b;
        rslt->next = sorted_merge(a, b->next, pred);
    }
    return (rslt);
}

/**
 * @brief Perform a merge sort on a given list, with predicate.
 *
 * @param head Head of the list
 * @param pred Predicate
 */
void
ft_lstsort(t_list **head, int (*pred)(const void *, const void *)) {
    assert(head != NULL);
    assert(pred != NULL);

    t_list *head_elem = *head;
    t_list *a         = NULL;
    t_list *b         = NULL;

    if (head_elem == NULL || head_elem->next == NULL) {
        return;
    }
    split_sublst(head_elem, &a, &b);
    ft_lstsort(&a, pred);
    ft_lstsort(&b, pred);
    *head = sorted_merge(a, b, pred);
}