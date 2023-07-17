#include <glib-object.h>

#include "tcomparable.h"
#include "tnumber.h"
#include "tdouble.h"
#include "tint.h"
#include "tstr.h"

static void notify_cb (GObject *gobject, GParamSpec *pspec, gpointer user_data) {
  const char *name;
  int i;
  double d;
  char *s;

  name = g_param_spec_get_name (pspec);
  if (T_IS_INT (gobject) && strcmp (name, "value") == 0) {
    g_object_get (T_INT (gobject), "value", &i, NULL);
    g_print ("property '%s' is set to %d\n", name, i);
  } else if (T_IS_DOUBLE (gobject) && strcmp (name, "value") == 0) {
    g_object_get (T_DOUBLE (gobject), "value", &d, NULL);
    g_print ("property '%s' is set to %lf\n", name, d);
  } else if (T_IS_STR (gobject) && strcmp (name, "string") == 0) {
    s = t_str_get_string (T_STR (gobject));
    g_print ("property '%s' is set to %s\n", name, s);
  }
}

static void t_print (TComparable *c1, const char *cmp, TComparable *c2) {
  char *s1, *s2;
  TStr *ts1, *ts2, *ts3;

  ts1 = t_str_new_with_string ("\"");
  if (T_IS_NUMBER (c1)) {
    s1 = t_number_to_s (T_NUMBER (c1));
  } else if (T_IS_STR (c1)) {
    ts2 = t_str_concat (ts1, T_STR (c1));
    ts3 = t_str_concat (ts2, ts1);
    s1 = t_str_get_string (ts3);
    g_object_unref (ts2);
    g_object_unref (ts3);
  } else {
    g_print ("c1 isn't TInt, TDouble nor TStr\n");
    return;
  }

  if (T_IS_NUMBER (c2)) {
    s2 = t_number_to_s (T_NUMBER (c2));
  } else if (T_IS_STR (c2)) {
    ts2 = t_str_concat (ts1, T_STR (c2));
    ts3 = t_str_concat (ts2, ts1);
    s2 = t_str_get_string (ts3);
    g_object_unref (ts2);
    g_object_unref (ts3);
  } else {
    g_print ("c2 isn't TInt, TDouble nor TStr\n");
    return;
  }

  g_print ("%s %s %s\n", s1, cmp, s2);
  g_object_unref (ts1);
  g_free (s1);
  g_free (s2);
}

static void compare (TComparable *c1, TComparable *c2) {
  if (t_comparable_eq (c1, c2)) {
    t_print (c1, "is equal to", c2);
  } else if (t_comparable_gt (c1, c2)) {
    t_print (c1, "is greater than", c2);
  } else if (t_comparable_lt (c1, c2)) {
    t_print (c1, "is less than", c2);
  } else {
    t_print (c1, "can't compare to", c2);
  }
}

int main() {
  const char *one = "one";
  const char *two = "two";
  const char *three = "three";
  TInt *i;
  TDouble *d;
  TStr *s1, *s2, *s3;
  gpointer obj;

  i = t_int_new_with_value (124);
  d = t_double_new_with_value (123.45);
  s1 = t_str_new_with_string (one);
  s2 = t_str_new_with_string (two);
  s3 = t_str_new_with_string (three);
  obj = g_object_new (G_TYPE_OBJECT, NULL);

  g_signal_connect (G_OBJECT (i), "notify::value", G_CALLBACK (notify_cb), NULL);
  g_signal_connect (G_OBJECT (d), "notify::value", G_CALLBACK (notify_cb), NULL);
  g_signal_connect (G_OBJECT (s1), "notify::string", G_CALLBACK (notify_cb), NULL);
  g_signal_connect (G_OBJECT (s2), "notify::string", G_CALLBACK (notify_cb), NULL);
  g_signal_connect (G_OBJECT (s3), "notify::string", G_CALLBACK (notify_cb), NULL);

  compare (T_COMPARABLE (i), T_COMPARABLE (d));
  compare (T_COMPARABLE (s1), T_COMPARABLE (s2));
  compare (T_COMPARABLE (s2), T_COMPARABLE (s3));

  t_comparable_eq (T_COMPARABLE (d), obj);

  g_object_unref (i);
  g_object_unref (d);
  g_object_unref (s1);
  g_object_unref (s2);
  g_object_unref (s3);
  g_object_unref (obj);
}
