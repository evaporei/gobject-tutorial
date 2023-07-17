#ifndef __T_COMPARABLE_H__
#define __T_COMPARABLE_H__

#include <glib-object.h>

#define T_TYPE_COMPARABLE (t_comparable_get_type ())
G_DECLARE_INTERFACE (TComparable, t_comparable, T, COMPARABLE, GObject)

struct _TComparableInterface {
  GTypeInterface parent;

  // signal
  void (*arg_error) (TComparable *self);

  // virtual function
  int (*cmp) (TComparable *self, TComparable *other);
};

int t_comparable_cmp (TComparable *self, TComparable *other);

gboolean t_comparable_eq (TComparable *self, TComparable *other);

gboolean t_comparable_gt (TComparable *self, TComparable *other);

gboolean t_comparable_lt (TComparable *self, TComparable *other);

gboolean t_comparable_ge (TComparable *self, TComparable *other);

gboolean t_comparable_le (TComparable *self, TComparable *other);

#endif
