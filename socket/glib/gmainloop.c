/*
 * pkg-config --cflags glib-2.0
 * pkg-config --libs glib-2.0
 *
 * cc hello.c `pkg-config --cflags --libs glib-2.0` -o hello
 */

#include <glib.h>
#include <stdio.h>
#include <strings.h>

GMainLoop *loop;

gboolean callback(GIOChannel *channel)
{
	gchar *str;
	gsize len;

	g_io_channel_read_line(channel, &str, &len, NULL, NULL);

	while (len > 0 && (str[len-1] == '\r' || str[len-1] == '\n'))
		str[--len] = '\0';

	for( ; len ; len--)
		g_print("%c", str[len-1]);
	g_print("\n");

	if (strcasecmp(str, "q") == 0)
		g_main_loop_quit(loop);

	g_free(str);
}

void add_source(GMainContext *context)
{
	GIOChannel *channel;
	GSource *source;

	channel = g_io_channel_unix_new(1);
	source = g_io_create_watch(channel, G_IO_IN);
	g_io_channel_unref(channel);

	g_source_set_callback(source, (GSourceFunc)callback, channel, NULL);

	g_source_attach(source, context);
	g_source_unref(source);
}

int main(int argc, char **argv)
{
	GMainContext *context;

	if (g_thread_supported() == 0)
		g_thread_init(NULL);

	context = g_main_context_new();

	add_source(context);

	loop = g_main_loop_new(context, FALSE);

	g_print("input string\n");
	g_main_loop_run(loop);
	g_main_loop_unref(loop);

	g_main_context_unref(context);

	return 0;
}
