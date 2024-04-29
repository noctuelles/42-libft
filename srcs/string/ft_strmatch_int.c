/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmatch_int.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plouvel <plouvel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 16:31:58 by plouvel           #+#    #+#             */
/*   Updated: 2024/04/29 16:32:31 by plouvel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>

#include "libft.h"

bool
ft_strmatch_int(const char *str) {
    if (*str == '-') {
        str++;
    }
    while (*str != '\0') {
        if (!ft_isdigit(*str)) {
            return (false);
        }
        str++;
    }

    return (true);
}
