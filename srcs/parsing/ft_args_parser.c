/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_args_parser.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plouvel <plouvel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 09:44:37 by plouvel           #+#    #+#             */
/*   Updated: 2024/04/18 23:52:04 by plouvel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_args_parser.h"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include "libft.h"

typedef struct s_parsed_arg {
    const t_args_parser_option_entry *entry;
    const char                       *argument_value;
    bool                              opt_arg_on_next_argv;
} t_parsed_arg;

static void
free_parsed_args(void *content) {
    free(content);
}

static size_t
option_key_len(const char *key) {
    size_t len = 0;

    while (key[len] != '\0' && key[len] != '=') {
        len++;
    }

    return (len);
}

static const t_args_parser_option_entry *
find_parser_option_entry_by_short_key(const t_args_parser_option_entry *entries, const size_t nbr_entries,
                                      const char key) {
    size_t                            i     = 0;
    const t_args_parser_option_entry *entry = NULL;

    while (i < nbr_entries) {
        entry = &entries[i];
        if (entry->short_key[0] == key) {
            break;
        }
        i++;
    }

    return (entry);
}

static const t_args_parser_option_entry *
find_parser_option_entry_by_long_key(const t_args_parser_option_entry *entries, const size_t nbr_entries,
                                     const char *key) {
    size_t                            i        = 0;
    size_t                            key_size = 0;
    const t_args_parser_option_entry *entry    = NULL;

    key_size = option_key_len(key);
    while (i < nbr_entries) {
        entry = &entries[i];
        if (ft_strncmp(entry->long_key, key, key_size) == 0) {
            break;
        }
        i++;
    }

    return (entry);
}

static void
handle_short_key(t_parsed_arg *parsed_arg, const char *argument) {}

static void
handle_long_key(t_parsed_arg *parsed_arg, const char *argument) {}

static t_list *
handle_key(t_list **parsed_args, const t_args_parser_option_entry *entry, const char *argument) {
    assert(entry->long_key != NULL && entry->short_key == NULL);
    assert(entry->long_key == NULL && entry->short_key != NULL);

    t_list       *elem       = NULL;
    t_parsed_arg *parsed_arg = NULL;

    parsed_arg = malloc(sizeof(*parsed_arg));
    if (parsed_arg == NULL) {
        return (NULL);
    }
    elem = ft_lstnew(parsed_arg);
    if (elem == NULL) {
        free(parsed_arg);
        return (NULL);
    }
    parsed_arg->entry = entry;
    if (entry->long_key) {
        handle_long_key(parsed_arg, argument);
    } else if (entry->short_key) {
        handle_short_key(parsed_arg, argument);
    }
    ft_lstadd_back(parsed_args, elem);
    return (elem);
}

t_list *
parse_argument(const t_args_parser_option_entry *entries, const size_t nbr_entries, const char *argument) {
    const t_args_parser_option_entry *entry       = NULL;
    t_list                           *parsed_args = NULL;
    t_parsed_arg                     *parsed_arg  = NULL;

    if (*argument == '-') {
        argument++;
        if (*argument == '-') {
            argument++;
            entry = find_parser_option_entry_by_long_key(entries, nbr_entries, argument);
            if (entry == NULL) {
                goto err;
            }
            parsed_arg                       = malloc(sizeof(*parsed_arg));
            parsed_arg->opt_arg_on_next_argv = false;
            parsed_arg->argument_value       = argument + option_key_len(argument);

            ft_lstadd_back(&parsed_args, ft_lstnew(parsed_arg));
        } else {
            while (*argument != '\0') {
                entry = find_parser_option_entry_by_short_key(entries, nbr_entries, *argument);
                if (entry == NULL) {
                    goto err;
                }
                parsed_arg        = malloc(sizeof(*parsed_arg));
                parsed_arg->entry = entry;
                if (parsed_arg->entry->argument) {
                    if (*(argument + 1) == '\0') {
                        parsed_arg->opt_arg_on_next_argv = true;
                        parsed_arg->argument_value       = NULL;
                    } else {
                        parsed_arg->opt_arg_on_next_argv = false;
                        parsed_arg->argument_value       = argument + 1;
                    }
                }
                ft_lstadd_back(&parsed_args, ft_lstnew(parsed_arg));
                argument++;
            }
        }
    }

    return (parsed_args);
err:
    ft_lstclear(&parsed_args, free_parsed_args);
    return (NULL);
}

int
ft_args_parser(t_args_parser_config *parser_config) {
    t_list       *parsed_args     = NULL;
    t_parsed_arg *last_parsed_arg = NULL;

    for (size_t i = 1; i < parser_config->argc; i++) {
        if (last_parsed_arg) {
            if (last_parsed_arg->opt_arg_on_next_argv) {
                last_parsed_arg->argument_value = parser_config->argv[i];
            }
        }

        if ((parsed_args = parse_argument(parser_config->parser_entries, parser_config->parser_entries_len,
                                          parser_config->argv[i])) == NULL) {
            ft_error(0, 0, "unknown option");
            return (-1);
        }

        for (t_list *elem = parsed_args; elem != NULL; elem = elem->next) {
            t_parsed_arg *parsed_arg = elem->content;

            if (parsed_arg->entry->argument) {
                if (parsed_arg->argument_value == '\0') {
                    if (parsed_arg->opt_arg_on_next_argv == true) {
                        last_parsed_arg = parsed_arg;
                    } else {
                        ft_error(0, 0, "argument missing for option '%s'\n",
                                 parsed_arg->entry->short_key != NULL ? parsed_arg->entry->short_key
                                                                      : parsed_arg->entry->long_key);
                        ft_lstclear(&parsed_args, free_parsed_args);
                        return (-1);
                    }
                }
            }
        }
    }

    return (0);
}
