#ifndef __T_NUM_STR_H__
#define __T_NUM_STR_H__

#include <glib-object.h>

#include "tstr.h"
#include "../09-abstract-type/tnumber.h"

#define T_TYPE_NUM_STR (t_num_str_get_type ())
G_DECLARE_FINAL_TYPE (TNumStr, t_num_str, T, NUM_STR, TStr)

enum {
  t_none,
  t_int,
  t_double
};

int t_num_str_get_string_type (TNumStr *self);

void t_num_str_set_from_t_number (TNumStr *self, TNumber *n);

TNumber *t_num_str_get_t_number (TNumStr *self);

TNumStr *t_num_str_new_with_t_number (TNumber *num);

TNumStr *t_num_str_new (void);

#endif
