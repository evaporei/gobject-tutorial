#include <ctype.h>

#include "tnumstr.h"
#include "../09-abstract-type/tnumber.h"
#include "../09-abstract-type/tint.h"
#include "../09-abstract-type/tdouble.h"

struct _TNumStr {
  TStr parent;
  int type;
};

G_DEFINE_TYPE (TNumStr, t_num_str, T_TYPE_STR)

static int t_num_str_string_type (const char *string) {
  const char *t;
  int stat, input;
  // state matrix
  int m[4][5] = {
    { 1, 2, 3, 6, 6 },
    { 6, 2, 3, 6, 6 },
    { 6, 2, 3, 4, 6 },
    { 6, 3, 6, 5, 6 }
  };

  if (string == NULL) {
    return t_none;
  }

  stat = 0;
  for (t = string; ; ++t) {
    if (*t == '+' || *t == '-') {
      input = 0;
    } else if (isdigit (*t)) {
      input = 1;
    } else if (*t == '.') {
      input = 2;
    } else if (*t == '\0') {
      input = 3;
    } else {
      input = 4;
    }

    stat = m[stat][input];

    if (stat >= 4 || *t == '\0') {
      break;
    }
  }

  if (stat == 4) {
    return t_int;
  } else if (stat == 5) {
    return t_double;
  } else {
    return t_none;
  }
}

static void t_num_str_real_set_string (TStr *self, const char *s) {
  T_STR_CLASS (t_num_str_parent_class)->set_string (self, s);
  T_NUM_STR (self)->type = t_num_str_string_type (s);
}

static void t_num_str_init (TNumStr *self) {
  self->type = t_none;
}

static void t_num_str_class_init (TNumStrClass *class) {
  TStrClass *t_str_class = T_STR_CLASS (class);

  t_str_class->set_string = t_num_str_real_set_string;
}

int t_num_str_get_string_type (TNumStr *self) {
  g_return_val_if_fail (T_IS_NUM_STR (self), -1);

  return self->type;
}

void t_num_str_set_from_t_number (TNumStr *self, TNumber *n) {
  g_return_if_fail (T_IS_NUM_STR (self));
  g_return_if_fail (T_IS_NUMBER (n));

  char *s;

  s = t_number_to_s (T_NUMBER (n));
  t_str_set_string (T_STR (self), s);

  g_free (s);
}

TNumber *t_num_str_get_t_number (TNumStr *self) {
  g_return_val_if_fail (T_IS_NUM_STR (self), NULL);

  char *s;
  TNumber *n;

  s = t_str_get_string (T_STR (self));

  if (self->type == t_int) {
    n = T_NUMBER (t_int_new_with_value (atoi (s)));
  } else if (self->type == t_double) {
    n = T_NUMBER (t_double_new_with_value (atof (s)));
  } else {
    n = NULL;
  }

  g_free (s);
  return n;
}

TNumStr *t_num_str_new_with_t_number (TNumber *n) {
  g_return_val_if_fail (T_IS_NUMBER (n), NULL);

  TNumStr *numstr;

  numstr = t_num_str_new ();
  t_num_str_set_from_t_number (numstr, n);

  return numstr;
}

TNumStr *t_num_str_new (void) {
  return T_NUM_STR (g_object_new (T_TYPE_NUM_STR, NULL));
}
