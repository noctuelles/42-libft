/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_args_parser_generate_docs.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plouvel <plouvel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 11:11:03 by plouvel           #+#    #+#             */
/*   Updated: 2024/01/16 14:16:40 by plouvel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>

#include "ft_args_parser.h"
#include "libft.h"

static int
set_description(char *buffer, const t_args_parser_option_entry *entry) {
    if (entry->short_key) {
        if (entry->long_key) {
            if (entry->long_key_argument_description) {
                sprintf(buffer, "-%s, --%s=%s", entry->short_key, entry->long_key,
                        entry->long_key_argument_description);
            } else {
                sprintf(buffer, "-%s, --%s", entry->short_key, entry->long_key);
            }
        } else {
            sprintf(buffer, "-%s", entry->short_key);
        }
    } else if (entry->long_key) {
        if (entry->long_key_argument_description) {
            sprintf(buffer, "    --%s=%s", entry->long_key, entry->long_key_argument_description);
        } else {
            sprintf(buffer, "    --%s", entry->long_key);
        }
    }

    return (0);
}
static size_t
find_biggest_tab_len(const char desc_tab[MAX_PARSER_ENTRIES][256]) {
    size_t len = 0;

    for (size_t i = 0; i < MAX_PARSER_ENTRIES; i++) {
        if (ft_strlen(desc_tab[i]) > len) {
            len = ft_strlen(desc_tab[i]);
        }
    }

    return (len);
}

void
ft_args_parser_generate_docs(const t_args_parser_config *config, char *buffer) {
    char   desc_tab[MAX_PARSER_ENTRIES][256] = {0};
    size_t biggest_desc_len                  = 0;

    for (size_t i = 0; i < config->nbr_parser_entries; i++) {
        set_description(desc_tab[i], &config->parser_entries[i]);
    }

    biggest_desc_len = find_biggest_tab_len(desc_tab);

    for (size_t i = 0; i < config->nbr_parser_entries; i++) {
        buffer += sprintf(buffer, "%-*s%s\n", (int)biggest_desc_len + DEFAULT_SPACING_DESCRIPTION, desc_tab[i],
                          config->parser_entries[i].description);
    }
}