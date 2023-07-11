#include <glib-object.h>

#include "tdouble.h"

void math() {
  TDouble *d1, *d2, *d3;
  double value3;

  d1 = t_double_new (25.0);
  d2 = t_double_new (-14.0);

  d3 = t_double_add (d1, d2);
  if (t_double_get_value (d3, &value3)) {
    g_print ("successful get_value3: %lf\n", value3);// 25 - 14 = 11
  } else {
    g_print ("get_value3 failed\n");
  }
}

int main() {
  TDouble *d;
  double value;

  d = t_double_new (10.0);
  if (t_double_get_value (d, &value)) {
    g_print ("successful get_value: %lf\n", value);
  } else {
    g_print ("get_value failed\n");
  }

  t_double_set_value (d, -20.0);
  if (t_double_get_value (d, &value)) {
    g_print ("successful get_value after set: %lf\n", value);
  } else {
    g_print ("get_value failed after set\n");
  }

  math();
}
