/*
 * gcc glibsample3.c `pkg-config --cflags --libs glib-2.0` -o glibsample3
 */

#include <glib.h>

static gboolean idle_func(gpointer data)
{
	g_print("%s\n", (gchar *)data);

	/*
	 * this is removed from mainloop if the func returns false and the
	 * message gets printed only once
	 */
	return TRUE;
}

int main(int argc, char **argv)
{
	GMainLoop *loop = g_main_loop_new(NULL, TRUE);
	GMainContext *context = g_main_loop_get_context(loop);

	g_idle_add(idle_func, "Hello World!");

	g_main_loop_run(loop);

	g_main_context_unref(context);
	g_main_loop_unref(loop);

	return 0;
}
