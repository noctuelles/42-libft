/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plouvel <plouvel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 08:24:55 by plouvel           #+#    #+#             */
/*   Updated: 2024/01/30 08:30:37 by plouvel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <errno.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

extern char *program_invocation_short_name;

/**
 * @brief same as the stdlib error function.
 *
 * @note uses printf family functions, and exit.
 *
 * @param status if status is different than 0, exit with the status code.
 * @param errnum if errnum is different than 0, print the associated error message (see errno).
 * @param format additional message to print.
 * @param ... variable argument for the format message.
 */
void
ft_error(int status, int errnum, const char *format, ...) {
    va_list ap;

    va_start(ap, format);
    fflush(stdout);
    (void)fprintf(stderr, "%s: ", program_invocation_short_name);
    (void)vfprintf(stderr, format, ap);
    va_end(ap);
    if (errnum != 0)
        (void)fprintf(stderr, ": %s", strerror(errnum));
    (void)fprintf(stderr, "\n");
    if (status != 0) {
        exit(status);
    }
}