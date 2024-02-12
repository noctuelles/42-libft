/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_args_parser.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plouvel <plouvel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 09:50:28 by plouvel           #+#    #+#             */
/*   Updated: 2024/02/12 10:44:22 by plouvel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_ARGS_PARSER_H
#define FT_ARGS_PARSER_H

#include <stdbool.h>
#include <stddef.h>

#define DEFAULT_SPACING_DESCRIPTION 10

typedef struct s_args_parser_state {
    char *error_message;
} t_args_parser_state;

typedef int (*t_args_parser_parse_fn)(char *, t_args_parser_state *, void *);

/**
 * The t_args_parser_option_entry_t structure is used to describe an option.
 *
 * A short_key is an option_key whose key if just string containing a single letter, ex. : 'c'. used like this : '-c'.
 * A long_key is an option_key whose key is a full string : ex. : 'count'. used like this : '--count'.
 * The argument indicate if the option takes an argument or not. In our example, the option 'count' takes an argument,
 * The parse_fn is invoke when the option has an argument, and is responsible for parsing of the latter.
 */
typedef struct s_args_parser_option_entry {
    const char            *short_key;
    const char            *long_key;
    const char            *description;
    const char            *long_key_argument_description;
    bool                   argument;
    t_args_parser_parse_fn parse_fn;
} t_args_parser_option_entry;

/**
 * The t_args_parser_config structure is used to configure the arg_parser function.
 *
 * The parse_argument_fn is invoked when the arg_parser function encounters an argument that is not an option.
 * The input void pointer is for an user defined structure
 */
typedef struct s_args_parser_config {
    char                      **argv;
    size_t                      argc;
    t_args_parser_option_entry *parser_entries;
    size_t                      parser_entries_len;
    t_args_parser_parse_fn      parse_argument_fn;
    void                       *input;
} t_args_parser_config;

int  ft_args_parser(t_args_parser_config *parser_config);
void ft_args_parser_print_docs(const t_args_parser_config *config);

#endif  // FT_PING_ARGS_PARSER_H