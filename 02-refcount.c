#include <glib-object.h>

void show_ref_count(GObject *instance) {
  if (G_IS_OBJECT (instance)) {
    g_print ("ref count: %d\n", instance->ref_count);
  } else {
    g_print ("not an instance\n");
  }
}

int main() {
  GObject *instance;
  show_ref_count(instance); // not an instance

  instance = g_object_new (G_TYPE_OBJECT, NULL);
  show_ref_count (instance); // 1

  g_object_ref (instance);
  show_ref_count (instance); // 2

  g_object_unref (instance);
  show_ref_count (instance); // 1

  g_object_unref (instance);
  // fish: Job 2, './02-refcount' terminated by signal SIGSEGV (Address boundary error)
  // I tried using gdb and it doesn't even get into show_ref_count or G_IS_OBJECT, it just explodes before that
  // if you use a zero referenced instance.
  /* show_ref_count (instance); */
}
