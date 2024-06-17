/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstartw.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plouvel <plouvel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 13:45:24 by plouvel           #+#    #+#             */
/*   Updated: 2024/06/14 13:47:25 by plouvel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>

/**
 * @brief Check if a string starts with a given prefix.
 *
 * @param str The string to check.
 * @param prefix The prefix to check.
 * @return true The string starts with the prefix.
 * @return false The string does not start with the prefix.
 */
bool
ft_strprefix(const char *str, const char *prefix) {
    while (*prefix != '\0') {
        if (*str != *prefix) {
            return (false);
        }
        str++;
        prefix++;
    }
    return (true);
}