/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_args_parser.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plouvel <plouvel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 09:44:37 by plouvel           #+#    #+#             */
/*   Updated: 2024/02/12 10:50:09 by plouvel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_args_parser.h"

#include <stdio.h>

#include "libft.h"

enum e_parser_option_key_type {
    OPTION_KEY_NOT_FOUND  = -1,
    OPTION_KEY_TYPE_SHORT = 1,
    OPTION_KEY_TYPE_LONG  = 2,
};

struct s_parser_option_result {
    char                         *option_key;
    char                         *option_argument;
    enum e_parser_option_key_type option_key_type;
};

static size_t
option_key_len(const char *key) {
    size_t len = 0;

    while (key[len] != '\0' && key[len] != '=') {
        len++;
    }

    return (len);
}

/**
 * For a given arg parser option_key entries, find an entry whose short_key or
 * long_key is equal to parameter key.
 * @param parser_option_entries
 * @param nbr_parser_option_entry
 * @param key
 * @return parser option_key entry associated with key, or NULL if no entry are
 * found.
 */
static t_args_parser_option_entry *
get_parser_option_entry(t_args_parser_option_entry *parser_option_entries, size_t nbr_parser_option_entry,
                        struct s_parser_option_result *parser_option_result) {
    t_args_parser_option_entry *parser_entry = NULL;
    size_t                      key_len      = 0;

    for (size_t i = 0; i < nbr_parser_option_entry; i++) {
        parser_entry = &parser_option_entries[i];

        if (parser_option_result->option_key_type == OPTION_KEY_TYPE_SHORT) {
            key_len = 1;
        } else if (parser_option_result->option_key_type == OPTION_KEY_TYPE_LONG) {
            key_len = option_key_len(parser_option_result->option_key);
        }

        if ((parser_entry->short_key != NULL &&
             ft_strncmp(parser_entry->short_key, parser_option_result->option_key, key_len) == 0) ||
            (parser_entry->long_key != NULL &&
             ft_strncmp(parser_entry->long_key, parser_option_result->option_key, key_len) == 0)) {
            return (parser_entry);
        }
    }

    return (NULL);
}

static char *
get_option_long_key_argument(char *option_key) {
    char *option_long_key_end = NULL;
    char *option_argument     = NULL;

    option_long_key_end = option_key + option_key_len(option_key);

    if (*option_long_key_end == '=') {
        option_argument = option_long_key_end + 1;
    }

    return (option_argument);
}

static char *
get_option_short_key_argument(char *option_key, char **argv, size_t *i) {
    char *option_argument = NULL;

    if (*option_key != '\0' && option_key[1] != '\0') {
        option_argument = &option_key[1];
    } else {
        (*i)++;
        option_argument = argv[*i];
    }

    return (option_argument);
}

static int
get_option_and_argument(char **argv, size_t *i, struct s_parser_option_result *parser_option_result) {
    char *option_key      = argv[*i];
    char *option_argument = NULL;

    if (*option_key == '-') {
        option_key++;
        if (*option_key == '-') {
            option_key++;

            parser_option_result->option_key_type = OPTION_KEY_TYPE_LONG;

            option_argument = get_option_long_key_argument(option_key);
        } else {
            parser_option_result->option_key_type = OPTION_KEY_TYPE_SHORT;

            option_argument = get_option_short_key_argument(option_key, argv, i);
        }
    } else {
        parser_option_result->option_key_type = OPTION_KEY_NOT_FOUND;
    }

    parser_option_result->option_key      = option_key;
    parser_option_result->option_argument = option_argument;

    return (parser_option_result->option_key_type);
}

static int
parse_option(t_args_parser_config *parser_config, size_t *i) {
    struct s_parser_option_result parser_option_result;
    t_args_parser_state           parser_state;
    t_args_parser_option_entry   *parser_option_entry;

    if (get_option_and_argument(parser_config->argv, i, &parser_option_result) == OPTION_KEY_NOT_FOUND) {
        return (parser_config->parse_argument_fn(parser_config->argv[*i], &parser_state, parser_config->input));
    }
    parser_option_entry = get_parser_option_entry(parser_config->parser_entries, parser_config->parser_entries_len,
                                                  &parser_option_result);
    if (parser_option_entry == NULL) {
        ft_error(0, 0, "invalid option -- '%s'", parser_option_result.option_key);
        return (-1);
    }
    if (parser_option_entry->argument != false) {
        if (parser_option_result.option_argument == NULL) {
            ft_error(0, 0, "option requires an argument -- '%s'\n", parser_option_result.option_key);
            return (-1);
        }
    }
    if (parser_option_entry->parse_fn != NULL &&
        parser_option_entry->parse_fn(parser_option_result.option_argument, &parser_state, parser_config->input) ==
            -1) {
        ft_error(0, 0, "%s: option -- '%s': %s\n",
                 parser_option_result.option_key_type == OPTION_KEY_TYPE_LONG ? parser_option_entry->long_key
                                                                              : parser_option_entry->short_key,
                 parser_state.error_message);
        return (-1);
    }
    return (0);
}

int
ft_args_parser(t_args_parser_config *parser_config) {
    for (size_t i = 1; i < parser_config->argc; i++) {
        if (parse_option(parser_config, &i) == -1) {
            return (-1);
        }
    }

    return (0);
}