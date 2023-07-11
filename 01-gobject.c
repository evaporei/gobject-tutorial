#include <glib-object.h>

int main() {
  GObject *instance1, *instance2;
  GObjectClass *class1, *class2;

  instance1 = g_object_new (G_TYPE_OBJECT, NULL);
  instance2 = g_object_new (G_TYPE_OBJECT, NULL);
  g_print ("The address of instance1 is %p\n", instance1);
  g_print ("The address of instance2 is %p\n", instance2);

  class1 = G_OBJECT_GET_CLASS (instance1);
  class2 = G_OBJECT_GET_CLASS (instance2);
  g_print ("The address of class1 is %p\n", class1);
  g_print ("The address of class2 is %p\n", class2);

  g_object_unref (instance1);
  g_object_unref (instance2);
}
