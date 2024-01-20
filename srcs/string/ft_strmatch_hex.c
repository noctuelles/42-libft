/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_match_base.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plouvel <plouvel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/20 14:23:09 by plouvel           #+#    #+#             */
/*   Updated: 2024/01/20 14:26:43 by plouvel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>

#include "libft.h"

bool
ft_strmatch_hex(const char *str) {
    while (*str != '\0') {
        if (!ft_isdigit(*str) || !(ft_tolower(*str) >= 'a' && ft_tolower(*str) <= 'f')) {
            return (false);
        }
    }

    return (true);
}