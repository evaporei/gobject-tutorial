#include <glib-object.h>

#define T_TYPE_DOUBLE (t_double_get_type ())
G_DECLARE_FINAL_TYPE (TDouble, t_double, T, DOUBLE, GObject)

struct _TDouble {
  GObject parent;
  double value;
};

G_DEFINE_TYPE (TDouble, t_double, G_TYPE_OBJECT);

void t_double_class_init (TDoubleClass *class) {}

void t_double_init (TDouble *d) {}

int main() {
  GType dtype;
  TDouble *d;

  dtype = t_double_get_type (); // or dtype = T_TYPE_DOUBLE
  if (dtype) {
    g_print ("successfull registration of type %lx\n", dtype);
  } else {
    g_print ("registration failed\n");
  }

  d = g_object_new (T_TYPE_DOUBLE, NULL);
  if (d) {
    g_print ("successfull instantiation, address: %p\n", d);
  } else {
    g_print ("instantiation failed\n");
  }

  if (T_IS_DOUBLE (d)) {
    g_print ("d is TDouble instance\n");
  } else {
    g_print ("d is NOT TDouble instance\n");
  }

  if (G_IS_OBJECT (d)) {
    g_print ("d is GObject instance\n");
  } else {
    g_print ("d is NOT GObject instance\n");
  }
}
