#include <glib-object.h>

#include "tdouble.h"
#include "tint.h"
#include "tnumber.h"

void notify_value_set_cb (GObject *gobject, GParamSpec *pspec, gpointer user_data) {
  const char *name;
  int i;
  double d;

  name = g_param_spec_get_name (pspec);
  if (T_IS_INT (gobject) && strcmp(name, "value") == 0) {
    g_object_get (T_INT (gobject), "value", &i, NULL);
    g_print ("property '%s' has been set to: %d\n", name, i);
  } else if (T_IS_DOUBLE (gobject) && strcmp(name, "value") == 0) {
    g_object_get (T_DOUBLE (gobject), "value", &d, NULL);
    g_print ("property '%s' has been set to: %lf\n", name, d);
  } else {
    g_print ("don't know how to print property '%s'\n", name);
  }
}

/* void div_by_zero_cb (TDouble *d, gpointer user_data) { */
/*   g_printerr ("\nError: happens in main.c\n\n"); */
/* } */
/*  */
/* void t_double_print (TDouble *d, char *op) { */
/*   double value; */
/*   if (t_double_get_value (d, &value)) { */
/*     g_print ("successful %s: %lf\n", op, value); */
/*   } else { */
/*     g_print ("%s failed\n", op); */
/*   } */
/* } */

int main() {
  TNumber *i, *d, *n;
  char *si, *sd, *sn;

  i = T_NUMBER (t_int_new ());
  d = T_NUMBER (t_double_new ());

  g_signal_connect (G_OBJECT (i), "notify::value", G_CALLBACK (notify_value_set_cb), NULL);
  g_signal_connect (G_OBJECT (d), "notify::value", G_CALLBACK (notify_value_set_cb), NULL);

  g_object_set (T_INT (i), "value", 100, NULL);
  g_object_set (T_DOUBLE (d), "value", 12.345, NULL);

  n = t_number_add (i, d);

  si = t_number_to_s (i);
  sd = t_number_to_s (d);
  sn = t_number_to_s (n);

  g_print ("(int add) %s + %s = %s\n", si, sd, sn);
  
  g_object_unref (n);
  g_free (sn);

  n = t_number_add (d, i);
  sn = t_number_to_s (n);

  g_print ("(double add) %s + %s = %s\n", si, sd, sn);

  g_object_unref (n);
  g_free (sd);
  g_free (sn);

  g_object_set (T_DOUBLE (d), "value", 0.0, NULL);
  sd = t_number_to_s (d);
  if ((n = t_number_div (i, d)) != NULL) {
    sn = t_number_to_s (n);
    g_print ("%s / %s = %s\n", si, sd, sn);
    g_object_unref (n);
    g_free (sn);
  }

  g_object_unref (i);
  g_object_unref (d);
  g_free (si);
  g_free (sd);
}
