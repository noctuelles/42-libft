/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_args_parser.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plouvel <plouvel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 09:50:28 by plouvel           #+#    #+#             */
/*   Updated: 2024/06/29 17:16:57 by plouvel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_ARGS_PARSER_H
#define FT_ARGS_PARSER_H

#include <stdbool.h>
#include <stddef.h>

#define DEFAULT_SPACING_DESCRIPTION 10

typedef struct s_args_parser_state {
    char *error_message;
    bool  print_arg;
} t_args_parser_state;

typedef int (*t_args_parser_parse_fn)(const char *, t_args_parser_state *, void *);

typedef struct s_args_parser_option_entry {
    const char            *short_key;
    const char            *long_key;
    const char            *description;
    const char            *long_key_argument_description;
    bool                   has_argument;
    t_args_parser_parse_fn parse_fn;
} t_args_parser_option_entry;

typedef struct s_args_parser_config {
    char                            **argv;
    size_t                            argc;
    const t_args_parser_option_entry *entries;
    size_t                            entries_nbr;
    t_args_parser_parse_fn            default_argument_parse_fn;
    void                             *input;
} t_args_parser_config;

int  ft_args_parser(const t_args_parser_config *parser_config);
void ft_args_parser_print_docs(const t_args_parser_config *config);

#endif  // FT_ARGS_PARSER_H