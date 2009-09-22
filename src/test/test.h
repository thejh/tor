/* Copyright (c) 2001-2003, Roger Dingledine.
 * Copyright (c) 2004-2006, Roger Dingledine, Nick Mathewson.
 * Copyright (c) 2007-2009, The Tor Project, Inc. */
/* See LICENSE for licensing information */

#ifndef _TOR_TEST_H
#define _TOR_TEST_H

/**
 * \file test.h
 * \brief Macros used by unit tests.
 */

#include "compat.h"
#include "tinytest.h"
#define TT_EXIT_TEST_FUNCTION STMT_BEGIN goto done; STMT_END
#include "tinytest_macros.h"

#ifdef __GNUC__
#define PRETTY_FUNCTION __PRETTY_FUNCTION__
#else
#define PRETTY_FUNCTION ""
#endif

#define test_fail_msg(msg) TT_DIE((msg))

#define test_fail() test_fail_msg("Assertion failed.")

#define test_assert(expr) tt_assert(expr)

#define test_eq(expr1, expr2) tt_int_op((expr1), ==, (expr2))
#define test_eq_ptr(expr1, expr2) tt_ptr_op((expr1), ==, (expr2))
#define test_neq(expr1, expr2) tt_int_op((expr1), !=, (expr2))
#define test_neq_ptr(expr1, expr2) tt_ptr_op((expr1), !=, (expr2))
#define test_streq(expr1, expr2) tt_str_op((expr1), ==, (expr2))
#define test_strneq(expr1, expr2) tt_str_op((expr1), !=, (expr2))
#define test_streq(expr1, expr2) tt_str_op((expr1), ==, (expr2))

#define test_mem_op(expr1, op, expr2, len)                              \
  tt_assert_test_fmt_type(expr1,expr2,#expr1" "#op" "#expr2,            \
                          const char *,                                 \
                          (memcmp(_val1, _val2, len) op 0),             \
                          char *, "%s",                                 \
                          { size_t printlen = (len)*2+1;                \
                            _print = tor_malloc(printlen);              \
                            base16_encode(_print, printlen, _value,     \
                                          (len)); },                    \
                          { tor_free(_print); }                         \
                          );

#define test_memeq(expr1, expr2, len) test_mem_op((expr1), ==, (expr2), len)
#define test_memneq(expr1, expr2, len) test_mem_op((expr1), !=, (expr2), len)

#define test_mem_op_hex(expr1, op, hex)                                 \
  STMT_BEGIN                                                            \
  size_t length = strlen(hex);                                          \
  char *value2 = tor_malloc(length/2);                                  \
  tor_assert((length&1)==0);                                            \
  base16_decode(value2, length/2, hex, length);                         \
  test_mem_op(expr1, op, value2, length/2);                             \
  STMT_END

#define test_memeq_hex(expr1, hex) test_mem_op_hex(expr1, ==, hex)

#endif
