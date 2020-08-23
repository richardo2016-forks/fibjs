/*
 * dl_gtk.cpp
 *
 *  Created on: Aug 8, 2020
 *      Author: lion
 */

#if !defined(_WIN32) && !defined(__APPLE__)

#include "dl_gtk.h"
#define __USE_GNU /* need RTLD_NEXT */
#include <dlfcn.h>
#include <stdlib.h>
#include <stdio.h>

namespace fibjs {

#define GLIB2 "libglib-2.0.so.0"
#define GIO_LIB "libgio-2.0.so.0"
#define GOBJECT_LIB "libgobject-2.0.so.0"
#define GTK2_LIB "libgtk-x11-2.0.so.0"
#define GTK3_LIB "libgtk-3.so.0"
#define WEBKIT_LIB "libwebkitgtk-3.0.so.0"
#define WEBKIT2_LIB "libwebkit2gtk-4.0.so.37"

static void* g = NULL;
static void* gio = NULL;
static void* gobject = NULL;
static void* gtk = NULL;
static void* webkit = NULL;

#define webkit_func dlsym(webkit, __func__, s_func)
#define gtk_func dlsym(gtk, __func__, s_func)
#define g_func dlsym(g, __func__, s_func)
#define gio_func dlsym(gio, __func__, s_func)
#define gobject_func dlsym(gobject, __func__, s_func)

template <typename T>
T dlsym(void* handle, const char* name, T& func)
{
    if (!gtk_init()) {
        fputs(dlerror(), stderr);
        exit(1);
    }

    if (!func) {
        func = (T)::dlsym(handle, name);
        if (!func) {
            fputs(dlerror(), stderr);
            exit(1);
        }
    }
    return func;
}

template <typename T>
T typeof(T func)
{
    return (T)0;
}

gint gtk_init()
{
    static gint ver;

    if (!g) {
        g = dlopen(GLIB2, RTLD_LAZY);
        if (!g)
            return 0;
    }

    if (!gio) {
        gio = dlopen(GIO_LIB, RTLD_LAZY);
        if (!gio)
            return 0;
    }

    if (!gobject) {
        gobject = dlopen(GOBJECT_LIB, RTLD_LAZY);
        if (!gobject)
            return 0;
    }

    if (!gtk) {
        gtk = dlopen(GTK3_LIB, RTLD_LAZY);
        if (gtk)
            ver |= GTK_V3;
        else {
            gtk = dlopen(GTK2_LIB, RTLD_LAZY);
            if (gtk)
                ver |= GTK_V2;
            else
                return 0;
        }
    }

    if (!webkit) {
        webkit = dlopen(WEBKIT2_LIB, RTLD_LAZY);
        if (webkit)
            ver |= WEBKIT_V2;
        else {
            webkit = dlopen(WEBKIT_LIB, RTLD_LAZY);
            if (webkit)
                ver |= WEBKIT_V1;
            else
                return 0;
        }
    }

    return ver;
}

void gtk_main()
{
    static auto s_func = typeof(gtk_main);
    gtk_func();
}

void g_idle_add(int (*func)(void*), void* data)
{
    static auto s_func = typeof(g_idle_add);
    gtk_func(func, data);
}

GTypeInstance* g_type_check_instance_cast(GTypeInstance* arg0, GType arg1)
{
    static auto s_func = typeof(g_type_check_instance_cast);
    return gtk_func(arg0, arg1);
}

GType gtk_window_get_type()
{
    static auto s_func = typeof(gtk_window_get_type);
    return gtk_func();
}

GType gtk_container_get_type()
{
    static auto s_func = typeof(gtk_container_get_type);
    return gtk_func();
}

GType gtk_widget_get_type()
{
    static auto s_func = typeof(gtk_widget_get_type);
    return gtk_func();
}

GtkWidget* gtk_window_new(GtkWindowType t)
{
    static void (*s_func_init)(int*, char***);
    if (!s_func_init)
        dlsym(gtk, "gtk_init", s_func_init)(NULL, NULL);

    static auto s_func = typeof(gtk_window_new);
    return gtk_func(t);
}

void gtk_widget_show_all(GtkWidget* widget)
{
    static auto s_func = typeof(gtk_widget_show_all);
    gtk_func(widget);
}

void gtk_widget_destroy(GtkWidget* widget)
{
    static auto s_func = typeof(gtk_widget_destroy);
    gtk_func(widget);
}

void gtk_window_set_title(GtkWindow* window, const gchar* title)
{
    static auto s_func = typeof(gtk_window_set_title);
    gtk_func(window, title);
}

void gtk_widget_set_size_request(GtkWidget* widget, gint width, gint height)
{
    static auto s_func = typeof(gtk_widget_set_size_request);
    gtk_func(widget, width, height);
}

void gtk_window_set_default_size(GtkWindow* window, gint width, gint height)
{
    static auto s_func = typeof(gtk_window_set_default_size);
    gtk_func(window, width, height);
}

void gtk_window_resize(GtkWindow* window, gint width, gint height)
{
    static auto s_func = typeof(gtk_window_resize);
    gtk_func(window, width, height);
}

void gtk_window_move(GtkWindow* window, gint x, gint y)
{
    static auto s_func = typeof(gtk_window_move);
    gtk_func(window, x, y);
}

void gtk_window_set_decorated(GtkWindow* window, gboolean setting)
{
    static auto s_func = typeof(gtk_window_set_decorated);
    gtk_func(window, setting);
}

void gtk_window_set_resizable(GtkWindow* window, gboolean resizable)
{
    static auto s_func = typeof(gtk_window_set_resizable);
    gtk_func(window, resizable);
}

GtkWidget* gtk_scrolled_window_new(GtkAdjustment* hadjustment, GtkAdjustment* vadjustment)
{
    static auto s_func = typeof(gtk_scrolled_window_new);
    return gtk_func(hadjustment, vadjustment);
}

gulong g_signal_connect_data(gpointer object, const gchar* name, GCallback func,
    gpointer func_data, GClosureNotify destroy_data, GConnectFlags connect_flags)
{
    static auto s_func = typeof(g_signal_connect_data);
    return gtk_func(object, name, func, func_data, destroy_data, connect_flags);
}

GdkScreen* gdk_screen_get_default()
{
    static auto s_func = typeof(gdk_screen_get_default);
    return gtk_func();
}

GdkScreen* gtk_widget_get_screen(GtkWidget* widget)
{
    static auto s_func = typeof(gtk_widget_get_screen);
    return gtk_func(widget);
}

guint gdk_screen_get_height(GdkScreen* scr)
{
    static auto s_func = typeof(gdk_screen_get_height);
    return gtk_func(scr);
}

guint gdk_screen_get_width(GdkScreen* scr)
{
    static auto s_func = typeof(gdk_screen_get_width);
    return gtk_func(scr);
}

void gtk_widget_grab_focus(GtkWidget* widget)
{
    static auto s_func = typeof(gtk_widget_grab_focus);
    gtk_func(widget);
}

void gtk_container_add(GtkContainer* container, GtkWidget* widget)
{
    static auto s_func = typeof(gtk_container_add);
    gtk_func(container, widget);
}

GType webkit_web_view_get_type(void)
{
    static auto s_func = typeof(webkit_web_view_get_type);
    return webkit_func();
}

GtkWidget* webkit_web_view_new(void)
{
    static auto s_func = typeof(webkit_web_view_new);
    return webkit_func();
}

void webkit_web_view_load_uri(GtkWidget* widget, const char* url)
{
    static auto s_func = typeof(webkit_web_view_load_uri);
    webkit_func(widget, url);
}

const gchar* webkit_web_view_get_title(WebKitWebView* web_view)
{
    static auto s_func = typeof(webkit_web_view_get_title);
    return webkit_func(web_view);
}

WebKitWebContext* webkit_web_context_get_default()
{
    static auto s_func = typeof(webkit_web_context_get_default);
    return webkit_func();
}

void webkit_web_context_set_web_extensions_directory(WebKitWebContext* context, const gchar* directory)
{
    static auto s_func = typeof(webkit_web_context_set_web_extensions_directory);
    webkit_func(context, directory);
}

void webkit_web_context_set_cache_model(WebKitWebContext* context, WebKitCacheModel cache_model)
{
    static auto s_func = typeof(webkit_web_context_set_cache_model);
    webkit_func(context, cache_model);
}

void webkit_web_context_clear_cache(WebKitWebContext* context)
{
    static auto s_func = typeof(webkit_web_context_clear_cache);
    webkit_func(context);
}

void webkit_web_context_register_uri_scheme(WebKitWebContext* context, const gchar* scheme,
    WebKitURISchemeRequestCallback callback, gpointer user_data, GDestroyNotify user_data_destroy_func)
{
    static auto s_func = typeof(webkit_web_context_register_uri_scheme);
    webkit_func(context, scheme, callback, user_data, user_data_destroy_func);
}

const gchar* webkit_uri_scheme_request_get_scheme(WebKitURISchemeRequest* request)
{
    static auto s_func = typeof(webkit_uri_scheme_request_get_scheme);
    return webkit_func(request);
}

const gchar* webkit_uri_scheme_request_get_uri(WebKitURISchemeRequest* request)
{
    static auto s_func = typeof(webkit_uri_scheme_request_get_uri);
    return webkit_func(request);
}

const gchar* webkit_uri_scheme_request_get_path(WebKitURISchemeRequest* request)
{
    static auto s_func = typeof(webkit_uri_scheme_request_get_path);
    return webkit_func(request);
}

WebKitWebView* webkit_uri_scheme_request_get_web_view(WebKitURISchemeRequest* request)
{
    static auto s_func = typeof(webkit_uri_scheme_request_get_web_view);
    return webkit_func(request);
}

void webkit_uri_scheme_request_finish(WebKitURISchemeRequest* request, GInputStream* stream,
    gint64 stream_length, const gchar* content_type)
{
    static auto s_func = typeof(webkit_uri_scheme_request_finish);
    return webkit_func(request, stream, stream_length, content_type);
}

void g_object_unref(gpointer object)
{
    static auto s_func = typeof(g_object_unref);
    gobject_func(object);
}

GInputStream* g_memory_input_stream_new_from_data(const void* data, gssize len, GDestroyNotify destroy)
{
    static auto s_func = typeof(g_memory_input_stream_new_from_data);
    return gio_func(data, len, destroy);
}

}

#endif