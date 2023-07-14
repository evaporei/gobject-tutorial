#include "tint.h"
#include "tdouble.h"

#define PROP_INT 1
static GParamSpec *int_property = NULL;

struct _TInt {
  TNumber parent;
  int value;
};

G_DEFINE_TYPE (TInt, t_int, T_TYPE_NUMBER)

static void t_int_set_property (GObject *object, guint property_id, const GValue *value, GParamSpec *pspec) {
  TInt *self = T_INT (object);

  if (property_id == PROP_INT) {
    self->value = g_value_get_int (value);
  } else {
    G_OBJECT_WARN_INVALID_PROPERTY_ID (object, property_id, pspec);
  }
}

static void t_int_get_property (GObject *object, guint property_id, GValue *value, GParamSpec *pspec) {
  TInt *self = T_INT (object);

  if (property_id == PROP_INT) {
    g_value_set_int (value, self->value);
  } else {
    G_OBJECT_WARN_INVALID_PROPERTY_ID (object, property_id, pspec);
  }
}

static void t_int_init (TInt *i) {}

#define t_int_unary_type_check(name) \
  g_return_val_if_fail (T_IS_NUMBER (name), NULL)

#define t_int_binary_op(op) \
  int i; \
  double d; \
  if (T_IS_INT (other)) { \
    g_object_get (T_INT (other), "value", &i, NULL); \
    return T_NUMBER (t_int_new_with_value (T_INT (self)->value op i)); \
  } else { \
    g_object_get (T_DOUBLE (other), "value", &d, NULL); \
    return T_NUMBER (t_int_new_with_value (T_INT (self)->value op (int) d)); \
  }

static TNumber *t_int_add (TNumber *self, TNumber *other) {
  t_int_unary_type_check (self);

  t_int_binary_op (+)
}

static TNumber *t_int_sub (TNumber *self, TNumber *other) {
  t_int_unary_type_check (self);

  t_int_binary_op (-)
}

static TNumber *t_int_mul (TNumber *self, TNumber *other) {
  t_int_unary_type_check (self);

  t_int_binary_op (*)
}

static TNumber *t_int_div (TNumber *self, TNumber *other) {
  t_int_unary_type_check (self);

  int i;
  double d;
  if (T_IS_INT (other)) {
    g_object_get (T_INT (other), "value", &i, NULL);
    if (i == 0) {
      g_signal_emit_by_name (self, "div-by-zero");
      return NULL;
    }
    return T_NUMBER (t_int_new_with_value (T_INT (self)->value / i));
  } else { \
    g_object_get (T_DOUBLE (other), "value", &d, NULL);
    if (d == 0.0) {
      g_signal_emit_by_name (self, "div-by-zero");
      return NULL;
    }
    return T_NUMBER (t_int_new_with_value (T_INT (self)->value / (int) d));
  }
}

static TNumber *t_int_inv (TNumber *self) {
  t_int_unary_type_check (self);

  return T_NUMBER (t_int_new_with_value (- T_INT (self)->value));
}

static char *t_int_to_s (TNumber *self) {
  t_int_unary_type_check (self);

  int i;
  g_object_get (T_INT (self), "value", &i, NULL);
  return g_strdup_printf ("%d", i);
}

static void t_int_class_init (TIntClass *class) {
  TNumberClass *tnumber_class = T_NUMBER_CLASS (class);
  GObjectClass *gobject_class = G_OBJECT_CLASS (class);

  tnumber_class->add = t_int_add;
  tnumber_class->sub = t_int_sub;
  tnumber_class->mul = t_int_mul;
  tnumber_class->div = t_int_div;
  tnumber_class->inv = t_int_inv;
  tnumber_class->to_s = t_int_to_s;

  gobject_class->set_property = t_int_set_property;
  gobject_class->get_property = t_int_get_property;
  int_property = g_param_spec_int ("value", "val", "Integer value", G_MININT, G_MAXINT, 0, G_PARAM_READWRITE);
  g_object_class_install_property (gobject_class, PROP_INT, int_property);
}

TInt *t_int_new_with_value (int value) {
  TInt *i;
  i = g_object_new (T_TYPE_INT, "value", value, NULL);
  return i;
}

TInt *t_int_new (void) {
  TInt *i;
  i = g_object_new (T_TYPE_INT, NULL);
  return i;
}
