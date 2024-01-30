/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmatch_hex.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plouvel <plouvel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/20 14:23:09 by plouvel           #+#    #+#             */
/*   Updated: 2024/01/27 15:15:12 by plouvel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>

#include "libft.h"

bool
ft_strmatch_hex(const char *str) {
    while (*str != '\0') {
        if (ft_strchr("0123456789abcdef", *str) == NULL) {
            return (false);
        }
        str++;
    }

    return (true);
}