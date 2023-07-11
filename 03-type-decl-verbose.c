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

void t_double_class_init (TDoubleClass *class) {}

void t_double_init (TDouble *d) {}

GType t_double_get_type (void) {
  static GType type = 0;
  GTypeInfo info;

  if (type == 0) {
    info.class_size = sizeof (TDoubleClass);

    info.base_init = NULL;
    info.base_finalize = NULL;

    info.class_init = (GClassInitFunc) t_double_class_init;
    info.class_finalize = NULL;
    info.class_data = NULL;

    info.instance_size = sizeof (TDouble);
    info.instance_init = (GInstanceInitFunc) t_double_init;

    info.n_preallocs = 0;
    info.value_table = NULL;

    type = g_type_register_static (G_TYPE_OBJECT, "TDouble", &info, 0);
  }

  return type;
}

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
