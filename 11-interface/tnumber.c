#include "tnumber.h"

static guint t_number_signal;

G_DEFINE_ABSTRACT_TYPE (TNumber, t_number, G_TYPE_OBJECT)

static void div_by_zero_default_cb (TNumber *d) {
  g_printerr ("\nError: division by zero.\n\n");
}

static void t_number_class_init (TNumberClass *class) {
  class->add = NULL;
  class->sub = NULL;
  class->mul = NULL;
  class->div = NULL;
  class->inv = NULL;
  class->to_s = NULL;
  class->div_by_zero = div_by_zero_default_cb;
  t_number_signal = g_signal_new (
      "div-by-zero",
      G_TYPE_FROM_CLASS (class),
      G_SIGNAL_RUN_LAST | G_SIGNAL_NO_RECURSE | G_SIGNAL_NO_HOOKS,
      G_STRUCT_OFFSET (TNumberClass, div_by_zero),
      NULL,
      NULL,
      NULL,
      G_TYPE_NONE,
      0
  );
}

static void t_number_init (TNumber *inst) {}

#define t_number_unary_null_check(name) \
  g_return_val_if_fail (T_IS_NUMBER (name), NULL)

#define t_number_binary_null_check \
  t_number_unary_null_check(self); \
  t_number_unary_null_check(other)

#define t_number_unary_op(op) \
  t_number_unary_null_check (self); \
  \
  TNumberClass *class = T_NUMBER_GET_CLASS (self); \
  return class->op ? class->op (self) : NULL

#define t_number_binary_op(op) \
  t_number_binary_null_check; \
  \
  TNumberClass *class = T_NUMBER_GET_CLASS (self); \
  return class->op ? class->op (self, other) : NULL

TNumber *t_number_add (TNumber *self, TNumber *other) {
  t_number_binary_op (add);
}

TNumber *t_number_sub (TNumber *self, TNumber *other) {
  t_number_binary_op (sub);
}

TNumber *t_number_mul (TNumber *self, TNumber *other) {
  t_number_binary_op (mul);
}

TNumber *t_number_div (TNumber *self, TNumber *other) {
  t_number_binary_op (div);
}

TNumber *t_number_inv (TNumber *self) {
  t_number_unary_op (inv);
}

char *t_number_to_s (TNumber *self) {
  t_number_unary_op (to_s);
}
