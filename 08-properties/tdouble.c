#include "tdouble.h"

static guint t_double_signal;

struct _TDouble {
  GObject parent;
  double value;
};

G_DEFINE_TYPE (TDouble, t_double, G_TYPE_OBJECT);

void div_by_zero_default_cb (TDouble *d, gpointer user_data) {
  g_printerr ("\nError: division by zero.\n\n");
}

#define PROP_DOUBLE 1
static GParamSpec *double_property = NULL;

void t_double_set_property (GObject *object, guint property_id, const GValue *value, GParamSpec *pspec) {
  TDouble *self = T_DOUBLE (object);

  if (property_id == PROP_DOUBLE) {
    self->value = g_value_get_double (value);
  } else {
    G_OBJECT_WARN_INVALID_PROPERTY_ID (object, property_id, pspec);
  }
}

void t_double_get_property (GObject *object, guint property_id, GValue *value, GParamSpec *pspec) {
  TDouble *self = T_DOUBLE (object);

  if (property_id == PROP_DOUBLE) {
    g_value_set_double (value, self->value);
  } else {
    G_OBJECT_WARN_INVALID_PROPERTY_ID (object, property_id, pspec);
  }
}

void t_double_class_init (TDoubleClass *class) {
  g_print ("t_double_class_init\n");

  t_double_signal = g_signal_new_class_handler (
      "div-by-zero",
      G_TYPE_FROM_CLASS (class),
      G_SIGNAL_RUN_LAST | G_SIGNAL_NO_RECURSE | G_SIGNAL_NO_HOOKS,
      G_CALLBACK (div_by_zero_default_cb),
      NULL,
      NULL,
      NULL,
      G_TYPE_NONE,
      0
  );

  GObjectClass *gobject_class = G_OBJECT_CLASS (class);
  gobject_class->set_property = t_double_set_property;
  gobject_class->get_property = t_double_get_property;

  double_property = g_param_spec_double (
      "value",
      "val",
      "Double value",
      -G_MAXDOUBLE,
      G_MAXDOUBLE,
      0.0,
      G_PARAM_READWRITE
  );
  g_object_class_install_property (gobject_class, PROP_DOUBLE, double_property);
}

void t_double_init (TDouble *d) { g_print ("t_double_init\n"); }

gboolean t_double_get_value (TDouble *d, double *value) {
  g_return_val_if_fail (T_IS_DOUBLE (d), FALSE);

  *value = d->value;
  return TRUE;
}

void t_double_set_value (TDouble *d, double value) {
  g_return_if_fail (T_IS_DOUBLE (d));

  // // if not set via g_object_set, no notification signal is sent
  // d->value = value;
  g_object_set (d, "value", value, NULL);
}

TDouble *t_double_new (double value) {
  TDouble *d;

  d = g_object_new (T_TYPE_DOUBLE, NULL);
  d-> value = value;

  return d;
}

#define t_double_unary_null_check(name) \
  g_return_val_if_fail (T_IS_DOUBLE (name), NULL)

#define t_double_binary_null_check \
  t_double_unary_null_check(self); \
  t_double_unary_null_check(other)

#define t_double_binary_op(op) \
  t_double_binary_null_check; \
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
  t_double_binary_null_check;

  double other_value;
  g_return_val_if_fail (t_double_get_value (other, &other_value), NULL);

  if (other_value == 0.0) {
    g_signal_emit (self, t_double_signal, 0);
    return NULL;
  }

  return t_double_new (self->value / other_value);
}

TDouble *t_double_inv (TDouble *self) {
  t_double_unary_null_check (self);

  return t_double_new (-self->value);
}
