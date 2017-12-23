/*
 * gcc glibsample1.c `pkg-config --cflags --libs glib-2.0` -o glibsample1
 */

#include <glib.h>
#include <glib/gprintf.h>

typedef struct MySource MySource;

struct MySource {
	GSource source;
	gchar text[256];
};

static gboolean prepare(GSource *source, gint *timeout)
{
	*timeout = 1000;

	return TRUE;
}

static gboolean check(GSource *source)
{
	return TRUE;
}

static gboolean dispatch(GSource *source, GSourceFunc callback, gpointer user_data)
{
	MySource *mysource = (MySource *)source;

	g_print("%s\n", mysource->text);

	return TRUE;
}

int main(int argc, char **argv)
{
	GMainLoop *loop = g_main_loop_new(NULL, TRUE);
	GMainContext *context = g_main_loop_get_context(loop);
	GSourceFuncs source_funcs = {prepare, check, dispatch, NULL};
	GSource *source = g_source_new(&source_funcs, sizeof(MySource));

	g_sprintf(((MySource *)source)->text, "Hello World!");
	g_source_attach(source, context);
	g_source_unref(source);

	g_main_loop_run(loop);

	g_main_context_unref(context);
	g_main_loop_unref(loop);

	return 0;
}
