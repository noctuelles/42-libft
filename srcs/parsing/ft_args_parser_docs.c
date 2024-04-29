/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_args_parser_print_docs.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plouvel <plouvel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 11:11:03 by plouvel           #+#    #+#             */
/*   Updated: 2024/02/11 20:06:30 by plouvel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>

#include "ft_args_parser.h"
#include "libft.h"

#define DEFAULT_BASE_SIZE 15

static int
set_description(char *desc, size_t desc_len, const t_args_parser_option_entry *entry) {
    if (entry->short_key) {
        if (entry->long_key) {
            if (entry->long_key_argument_description) {
                snprintf(desc, desc_len, "-%s, --%s=%s", entry->short_key, entry->long_key,
                         entry->long_key_argument_description);
            } else {
                snprintf(desc, desc_len, "-%s, --%s", entry->short_key, entry->long_key);
            }
        } else {
            snprintf(desc, desc_len, "-%s", entry->short_key);
        }
    } else if (entry->long_key) {
        if (entry->long_key_argument_description) {
            snprintf(desc, desc_len, "    --%s=%s", entry->long_key, entry->long_key_argument_description);
        } else {
            snprintf(desc, desc_len, "    --%s", entry->long_key);
        }
    }

    return (0);
}

static size_t
find_biggest_tab_len(char **desc, size_t desc_len) {
    size_t maxlen = 0;

    for (size_t i = 0; i < desc_len; i++) {
        if (ft_strlen(desc[i]) > maxlen) {
            maxlen = ft_strlen(desc[i]);
        }
    }

    return (maxlen);
}

static void
free_desc(char **desc, size_t desc_len) {
    for (size_t i = 0; i < desc_len; i++) {
        free(desc[i]);
    }
    free(desc);
}

void
ft_args_parser_print_docs(const t_args_parser_config *config) {
    char **desc             = NULL;
    size_t biggest_desc_len = 0;

    if ((desc = malloc(sizeof(*desc) * config->entries_nbr)) == NULL) {
        return;
    }
    ft_bzero(desc, config->entries_nbr * sizeof(*desc));
    for (size_t i = 0; i < config->entries_nbr; i++) {
        size_t                            size  = DEFAULT_BASE_SIZE;
        const t_args_parser_option_entry *entry = &config->entries[i];

        if (entry->short_key) {
            size += ft_strlen(entry->short_key);
        }
        if (entry->long_key) {
            size += ft_strlen(entry->long_key);
        }
        if (entry->long_key_argument_description) {
            size += ft_strlen(entry->long_key_argument_description);
        }

        if ((desc[i] = malloc(size)) == NULL) {
            free_desc(desc, i);
            return;
        }

        set_description(desc[i], size, entry);
    }
    biggest_desc_len = find_biggest_tab_len(desc, config->entries_nbr);
    for (size_t i = 0; i < config->entries_nbr; i++) {
        (void)printf("\t%-*s%s\n", (int)biggest_desc_len + DEFAULT_SPACING_DESCRIPTION, desc[i],
                     config->entries[i].description);
    }

    free_desc(desc, config->entries_nbr);
}