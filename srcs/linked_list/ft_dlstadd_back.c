/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dlstadd_back.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plouvel <plouvel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/25 00:46:30 by plouvel           #+#    #+#             */
/*   Updated: 2022/02/25 00:55:52 by plouvel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_dlstadd_back(t_dlist **dlst, t_dlist *new)
{
	t_dlist	*elem;
	t_dlist	*prev_elem;

	if (!dlst)
		return ;
	if (!*dlst)
		*dlst = new;
	else
	{
		elem = *dlst;
		while (elem)
		{
			prev_elem = elem;
			elem = elem->next;
		}
		prev_elem->next = new;
		new->prev = prev_elem;
	}
}

