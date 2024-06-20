/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_baselen.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plouvel <plouvel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 10:51:44 by plouvel           #+#    #+#             */
/*   Updated: 2024/06/20 10:52:06 by plouvel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

size_t
ft_baselen(const char *base) {
    size_t i;
    size_t j;

    i = 0;
    while (base[i] != '\0') {
        j = 0;
        if (base[i] == '-' || base[i] == '+')
            return (0);
        while (j < i)
            if (base[j++] == base[i])
                return (0);
        i++;
    }
    if (i == 0 || i == 1)
        return (0);
    return (i);
}