#include <glib-object.h>

#include "tdouble.h"

void notify_value_set_cb (TDouble *d, gpointer user_data) {
  g_print ("hello, value property has been set\n");
}

void div_by_zero_cb (TDouble *d, gpointer user_data) {
  g_printerr ("\nError: happens in main.c\n\n");
}

void t_double_print (TDouble *d, char *op) {
  double value;
  if (t_double_get_value (d, &value)) {
    g_print ("successful %s: %lf\n", op, value);
  } else {
    g_print ("%s failed\n", op);
  }
}

void math() {
  TDouble *d1, *d2, *d3;

  d1 = t_double_new (25.0);
  d2 = t_double_new (-14.0);

  // 25 - 14 = 11
  d3 = t_double_add (d1, d2);
  t_double_print (d3, "add");

  g_object_unref (d3);

  // 25 + 14 = 39
  d3 = t_double_sub (d1, d2);
  t_double_print (d3, "sub");

  g_object_unref (d3);

  // 25 * (-14) = -350
  d3 = t_double_mul (d1, d2);
  t_double_print (d3, "mul");

  g_object_unref (d3);

  // 25 / (-14) = -1.785714
  d3 = t_double_div (d1, d2);
  t_double_print (d3, "div");

  g_object_unref (d3);

  t_double_set_value (d2, 0.0);
  g_signal_connect (d1, "div-by-zero", G_CALLBACK (div_by_zero_cb), NULL);
  // 25 / 0 = NULL -> emit signal
  d3 = t_double_div (d1, d2);
  t_double_set_value (d2, -14.0);

  // -25
  d3 = t_double_inv (d1);
  t_double_print (d3, "inv");

  g_object_unref (d3);

  // 14
  d3 = t_double_inv (d2);
  t_double_print (d3, "inv2");
}

int main() {
  g_print("main\n");

  TDouble *d;

  d = t_double_new (10.0);
  t_double_print(d, "get_value");

  g_signal_connect (G_OBJECT (d), "notify::value", G_CALLBACK (notify_value_set_cb), NULL);

  t_double_set_value (d, -20.0);
  t_double_print(d, "get_value after set");

  math();
}
