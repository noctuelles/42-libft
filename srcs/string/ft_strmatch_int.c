/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmatch_int.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plouvel <plouvel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/20 14:27:27 by plouvel           #+#    #+#             */
/*   Updated: 2024/01/27 15:12:53 by plouvel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>

#include "libft.h"

bool
ft_strmatch_int(const char *str) {
    while (*str != '\0') {
        if (!ft_isdigit(*str)) {
            return (false);
        }
        str++;
    }

    return (true);
}