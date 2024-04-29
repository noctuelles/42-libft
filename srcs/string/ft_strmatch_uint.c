/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmatch_uint.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plouvel <plouvel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 16:31:24 by plouvel           #+#    #+#             */
/*   Updated: 2024/04/29 16:34:51 by plouvel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>

#include "libft.h"

bool
ft_strmatch_uint(const char *str) {
    while (*str != '\0') {
        if (!ft_isdigit(*str)) {
            return (false);
        }
        str++;
    }

    return (true);
}