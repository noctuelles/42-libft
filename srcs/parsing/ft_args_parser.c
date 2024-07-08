/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_args_parser.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plouvel <plouvel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 09:44:37 by plouvel           #+#    #+#             */
/*   Updated: 2024/07/08 14:56:19 by plouvel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_args_parser.h"

#include "libft.h"

enum e_parse_ret_val {
    ERROR                   = -1,
    OK                      = 0,
    USED_NEXT_ARGUMENT      = 1,
    USED_REMAINING_ARGUMENT = 2,
};

typedef enum e_parse_ret_val (*t_parse_key_fn)(const t_args_parser_option_entry *, size_t, const char *, const char *,
                                               void *input);

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
        if (entry->short_key && entry->short_key[0] == key) {
            return (entry);
        }
        i++;
    }

    return (NULL);
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
        if (entry->long_key && ft_strncmp(entry->long_key, key, key_size) == 0) {
            return (entry);
        }
        i++;
    }

    return (NULL);
}

static enum e_parse_ret_val
parse_short_key(const t_args_parser_option_entry *entries, const size_t entries_nbr, const char *argument,
                const char *next_argument, void *input) {
    const t_args_parser_option_entry *entry          = NULL;
    const char                       *argument_value = NULL;
    t_args_parser_state               parser_state   = {0};
    enum e_parse_ret_val              ret_val        = OK;

    while (*argument != '\0' && ret_val != USED_REMAINING_ARGUMENT) {
        entry = find_parser_option_entry_by_short_key(entries, entries_nbr, *argument);
        if (entry == NULL) {
            ft_error(0, 0, "unkown option -- %c", *argument);
            return (ERROR);
        }
        if (entry->has_argument) {
            if (*(argument + 1) != '\0') {
                argument_value = argument + 1;
                ret_val        = USED_REMAINING_ARGUMENT;
            } else {
                if (next_argument == NULL) {
                    ft_error(0, 0, "missing argument for option -- '%s'", entry->short_key);
                    return (ERROR);
                }
                argument_value = next_argument;
                ret_val        = USED_NEXT_ARGUMENT;
            }
        }
        if (entry->parse_fn(argument_value, &parser_state, input) == -1) {
            if (parser_state.print_arg) {
                ft_error(0, 0, "option error -- '%s': %s - '%s'.", entry->short_key, parser_state.error_message,
                         argument_value);
            } else {
                ft_error(0, 0, "option error -- '%s': %s.", entry->short_key, parser_state.error_message);
            }
            return (ERROR);
        }
        argument++;
    }
    return (ret_val);
}

static enum e_parse_ret_val
parse_long_key(const t_args_parser_option_entry *entries, const size_t entries_nbr, const char *argument,
               const char *next_argument, void *input) {
    const t_args_parser_option_entry *entry          = NULL;
    const char                       *argument_value = NULL;
    t_args_parser_state               parser_state   = {0};

    (void)next_argument;
    entry = find_parser_option_entry_by_long_key(entries, entries_nbr, argument);
    if (entry == NULL) {
        ft_error(0, 0, "unkown option -- %s", argument);
        return (ERROR);
    }
    if (entry->has_argument) {
        argument_value = argument + option_key_len(argument);
        if (*argument_value == '=') {
            argument_value++;
        }
        if (*argument_value == '\0') {
            ft_error(0, 0, "missing argument for option -- '%s'", entry->long_key);
            return (ERROR);
        }
    }
    if (entry->parse_fn(argument_value, &parser_state, input) == -1) {
        if (parser_state.print_arg) {
            ft_error(0, 0, "option error -- '%s': %s - '%s'.", entry->long_key, parser_state.error_message,
                     argument_value);
        } else {
            ft_error(0, 0, "option error -- '%s': %s.", entry->long_key, parser_state.error_message);
        }
        return (ERROR);
    }
    return (OK);
}

static enum e_parse_ret_val
parse_opts(const t_args_parser_option_entry *entries, const size_t nbr_entries, const char *argument,
           const char *next_argument, void *input) {
    t_parse_key_fn parse_key_fn = NULL;

    if (argument[1] == '-') {
        parse_key_fn = parse_long_key;
        argument += 2;
    } else {
        parse_key_fn = parse_short_key;
        argument += 1;
    }
    return (parse_key_fn(entries, nbr_entries, argument, next_argument, input));
}

static int
parse_arg(const char *argument, t_args_parser_parse_fn parse_argument_fn, void *input) {
    t_args_parser_state parser_state = {0};

    if (parse_argument_fn(argument, &parser_state, input) == -1) {
        ft_error(0, 0, "argument -- '%s' : %s.", argument, parser_state.error_message);
        return (-1);
    }

    return (0);
}

int
ft_args_parser(const t_args_parser_config *parser_config) {
    char               **argv          = parser_config->argv + 1;
    const char          *argument      = NULL;
    const char          *next_argument = NULL;
    bool                 ignore_opts   = false;
    enum e_parse_ret_val ret_val       = OK;

    while (*argv != NULL) {
        argument      = *argv;
        next_argument = *(argv + 1);
        if (!ignore_opts && argument[0] == '-' && argument[1] != '\0') {
            ret_val = parse_opts(parser_config->entries, parser_config->entries_nbr, argument, next_argument,
                                 parser_config->input);
            if (ret_val == ERROR) {
                return (ret_val);
            }
            if (ret_val == USED_NEXT_ARGUMENT) {
                argv++;
            }
        } else {
            if (parse_arg(argument, parser_config->default_argument_parse_fn, parser_config->input) == -1) {
                return (-1);
            }
            if (parser_config->stop_opts_parsing_on_first_non_opt && !ignore_opts) {
                ignore_opts = true;
            }
        }
        argv++;
    }
    return (0);
}
