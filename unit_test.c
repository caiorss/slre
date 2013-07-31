/*
 * Copyright (c) 2004-2013 Sergey Lyubka <valenok@gmail.com>
 * Copyright (c) 2013 Cesanta Limited
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


/*
 * To unit-test SLRE, do
 * cc -W -Wall -O2 -ansi -pedantic -pipe unit_test.c -o /tmp/t && /tmp/t
 */

#include "slre.c"

static int static_total_tests = 0;
static int static_failed_tests = 0;

#define FAIL(str, line) do {                      \
  printf("Fail on line %d: [%s]\n", line, str);   \
  static_failed_tests++;                          \
} while (0)

#define ASSERT(expr) do {               \
  static_total_tests++;                 \
  if (!(expr)) FAIL(#expr, __LINE__);   \
} while (0)

int main(void) {
  const char *msg = "";

#if 0
#endif
  ASSERT(slre_match("fo", "foo", 3, NULL, &msg) == 2);
  ASSERT(slre_match(".+", "foo", 3, NULL, &msg) == 3);

  ASSERT(slre_match(".+k", "fooklmn", 7, NULL, &msg) == 4);
  ASSERT(slre_match(".+k.", "fooklmn", 7, NULL, &msg) == 5);
  ASSERT(slre_match("p+", "fooklmn", 7, NULL, &msg) == 0);
  ASSERT(slre_match("ok", "fooklmn", 7, NULL, &msg) == 4);
  ASSERT(slre_match("lmno", "fooklmn", 7, NULL, &msg) == 0);
  ASSERT(slre_match("mn.", "fooklmn", 7, NULL, &msg) == 0);
  ASSERT(slre_match("o", "fooklmn", 7, NULL, &msg) == 2);
  ASSERT(slre_match("^o", "fooklmn", 7, NULL, &msg) == 0);
  ASSERT(slre_match("^", "fooklmn", 7, NULL, &msg) == 0);
  ASSERT(slre_match("n$", "fooklmn", 7, NULL, &msg) == 7);
  ASSERT(slre_match("n$k", "fooklmn", 7, NULL, &msg) == 0);
  ASSERT(slre_match("l$", "fooklmn", 7, NULL, &msg) == 0);
  ASSERT(slre_match(".$", "fooklmn", 7, NULL, &msg) == 7);
  ASSERT(slre_match("a?", "fooklmn", 7, NULL, &msg) == 0);

  ASSERT(slre_match("\\_", "fooklmn", 7, NULL, &msg) == 0);
  ASSERT(strcmp(msg, static_error_invalid_metacharacter) == 0);
  ASSERT(slre_match("+", "fooklmn", 7, NULL, &msg) == 0);
  ASSERT(strcmp(msg, static_error_unexpected_quantifier) == 0);
  ASSERT(slre_match("()+", "fooklmn", 7, NULL, &msg) == 0);
  ASSERT(strcmp(msg, static_error_no_match) == 0);

  /* Balancing brackets */
  ASSERT(slre_match("(x))", "fooklmn", 7, NULL, &msg) == 0);
  ASSERT(strcmp(msg, static_error_unbalanced_brackets) == 0);
  ASSERT(slre_match("(", "fooklmn", 7, NULL, &msg) == 0);
  ASSERT(strcmp(msg, static_error_unbalanced_brackets) == 0);

  ASSERT(slre_match("klz?mn", "fooklmn", 7, NULL, &msg) == 7);
  ASSERT(slre_match("fa?b", "fooklmn", 7, NULL, &msg) == 0);

  /* Brackets & capturing */
  ASSERT(slre_match("^(te)", "tenacity subdues all", 20, NULL, &msg) == 2);
  ASSERT(slre_match("(bc)", "abcdef", 6, NULL, &msg) == 3);
  ASSERT(slre_match(".(d.)", "abcdef", 6, NULL, &msg) == 5);
  ASSERT(slre_match(".(d.)\\)?", "abcdef", 6, NULL, &msg) == 5);

  /* Greedy vs non-greedy */
  ASSERT(slre_match(".+c", "abcabc", 6, NULL, &msg) == 6);
  ASSERT(slre_match(".+?c", "abcabc", 6, NULL, &msg) == 3);
  ASSERT(slre_match(".*?c", "abcabc", 6, NULL, &msg) == 3);
  ASSERT(slre_match(".*c", "abcabc", 6, NULL, &msg) == 6);
  ASSERT(slre_match("bc.d?k?b+", "abcabc", 6, NULL, &msg) == 5);

  printf("Unit test %s (total test: %d, failed tests: %d)\n",
         static_failed_tests > 0 ? "FAILED" : "PASSED",
         static_total_tests, static_failed_tests);

  return EXIT_SUCCESS;
}
