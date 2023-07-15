#include <glib-object.h>
#include <string.h>
#include "tstr.h"

static void notify_cb (GObject *gobject, GParamSpec *pspec, gpointer user_data) {
  const char *name;
  char *s;

  name = g_param_spec_get_name (pspec);
  if (strcmp (name, "string") == 0) {
    g_print ("string property is set to %s.\n", (s = t_str_get_string (T_STR (gobject))));
    if (s) g_free (s);
  }
}

int main () {
  const char *one = "one";
  const char *two = "two";
  TStr *str1, *str2, *str3;
  char *s;

  str1 = t_str_new ();
  g_signal_connect (G_OBJECT (str1), "notify::string", G_CALLBACK (notify_cb), NULL);
  g_object_set (G_OBJECT (str1), "string", one, NULL);

  str2 = t_str_new ();
  g_object_set (G_OBJECT (str2), "string", two, NULL);

  str3 = t_str_concat (str1, str2);
  s = t_str_get_string (str3);
  g_print ("\"%s\" and \"%s\" is \"%s\".\n", one, two, s);

  if (s) g_free (s);
  if (str1) g_object_unref (str1);
  if (str2) g_object_unref (str2);
  if (str3) g_object_unref (str3);
}
