/*
 * Copyright (c) 2004-2013 Sergey Lyubka <valenok@gmail.com>
 * Copyright (c) 2013 Cesanta Software Limited
 * All rights reserved
 *
 * This library is dual-licensed: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation. For the terms of this
 * license, see <http://www.gnu.org/licenses/>.
 *
 * You are free to use this library under the terms of the GNU General
 * Public License, but WITHOUT ANY WARRANTY; without even the implied
 * warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details.
 *
 * Alternatively, you can license this library under a commercial
 * license, as set out in <http://cesanta.com/products.html>.
 */

#ifndef SLRE_HEADER_DEFINED
#define SLRE_HEADER_DEFINED

#ifdef __cplusplus
extern "C" {
#endif

/*
 * This is a regular expression library that implements a subset of Perl RE.
 * Please refer to https://github.com/cesanta/slre for detailed reference.
 */

/* This structure describes a matched fragment, a "capture" */
struct slre_cap {
  const char *ptr;  /* Points to the matched fragment */
  int len;          /* Length of the matched fragment */
};

/*
 * Match string buffer "buf" of length "buf_len" against "regexp", which should
 * conform the syntax outlined below. If regular expression
 * "regexp" contains brackets, slre_match() will capture the respective
 * substring. Array of captures, "caps", must have at least as many elements
 * as number of opening parenthesis in the regexp.
 *
 * Return:
 *   0, if there is no match. error_msg will contain the error message
 *   >0, number of bytes matched in a buffer
 */
int slre_match(const char *regexp, const char *buf, int buf_len,
               struct slre_cap *caps, const char **error_msg);

#ifdef __cplusplus
}
#endif

#endif  /* SLRE_HEADER_DEFINED */