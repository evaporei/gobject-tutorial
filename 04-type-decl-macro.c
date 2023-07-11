#include <glib-object.h>

#define T_TYPE_DOUBLE (t_double_get_type ())

typedef struct _TDoubleClass TDoubleClass;
struct _TDoubleClass {
  // The first member of the structure must be the parent’s class structure.
  GObjectClass parent_class;
};

typedef struct _TDouble TDouble;
struct _TDouble {
  GObject parent;
  double value;
};

G_DEFINE_TYPE (TDouble, t_double, G_TYPE_OBJECT)

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
}
