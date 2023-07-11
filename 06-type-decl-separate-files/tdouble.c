#include "tdouble.h"

struct _TDouble {
  GObject parent;
  double value;
};

G_DEFINE_TYPE (TDouble, t_double, G_TYPE_OBJECT);

void t_double_class_init (TDoubleClass *class) { g_print ("t_double_class_init\n"); }

void t_double_init (TDouble *d) { g_print ("t_double_init\n"); }

gboolean t_double_get_value (TDouble *d, double *value) {
  g_return_val_if_fail (T_IS_DOUBLE (d), FALSE);

  *value = d->value;
  return TRUE;
}

void t_double_set_value (TDouble *d, double value) {
  g_return_if_fail (T_IS_DOUBLE (d));

  d->value = value;
}

TDouble *t_double_new (double value) {
  TDouble *d;

  d = g_object_new (T_TYPE_DOUBLE, NULL);
  d-> value = value;

  return d;
}

#define t_double_binary_op(op) \
  g_return_val_if_fail (T_IS_DOUBLE (self), NULL); \
  g_return_val_if_fail (T_IS_DOUBLE (other), NULL); \
  \
  double other_value; \
  g_return_val_if_fail (t_double_get_value (other, &other_value), NULL); \
  \
  return t_double_new (self->value op other_value);

TDouble *t_double_add (TDouble *self, TDouble *other) {
  t_double_binary_op(+)
}

TDouble *t_double_sub (TDouble *self, TDouble *other) {
  t_double_binary_op(-)
}

TDouble *t_double_mul (TDouble *self, TDouble *other) {
  t_double_binary_op(*)
}

TDouble *t_double_div (TDouble *self, TDouble *other) {
  t_double_binary_op(/)
}

TDouble *t_double_inv (TDouble *self) {
  g_return_val_if_fail (T_IS_DOUBLE (self), NULL);

  return t_double_new (-self->value);
}
