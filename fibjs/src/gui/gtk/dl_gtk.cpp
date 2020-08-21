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

#define GTK2_LIB "libgtk-x11-2.0.so.0"
#define GTK3_LIB "libgtk-3.so.0"
#define WEBKIT_LIB "libwebkitgtk-3.0.so.0"
#define WEBKIT2_LIB "libwebkit2gtk-4.0.so.37"

static void* gtk = NULL;
static void* webkit = NULL;

#define webkit_func dlsym(webkit, __func__, s_func)
#define gtk_func dlsym(gtk, __func__, s_func)

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

bool gtk_init()
{
    if (!webkit)
        webkit = dlopen(WEBKIT2_LIB, RTLD_LAZY | RTLD_GLOBAL);
    if (!webkit)
        webkit = dlopen(WEBKIT_LIB, RTLD_LAZY | RTLD_GLOBAL);
    if (!webkit)
        return false;

    if (!gtk)
        gtk = dlopen(GTK3_LIB, RTLD_LAZY | RTLD_GLOBAL);
    // if (!gtk)
    //     gtk = dlopen(GTK2_LIB, RTLD_LAZY | RTLD_GLOBAL);
    if (!gtk)
        return false;

    return true;
}

void gtk_main()
{
    static void (*s_func)();
    gtk_func();
}

void g_idle_add(int (*func)(void*), void* data)
{
    static void (*s_func)(int (*)(void*), void*);
    gtk_func(func, data);
}

GTypeInstance* g_type_check_instance_cast(GTypeInstance* arg0, GType arg1)
{
    static GTypeInstance* (*s_func)(GTypeInstance*, GType);
    return gtk_func(arg0, arg1);
}

GType gtk_window_get_type()
{
    static GType (*s_func)();
    return gtk_func();
}

GType gtk_container_get_type()
{
    static GType (*s_func)();
    return gtk_func();
}

GtkWidget* gtk_window_new(GtkWindowType t)
{
    static void (*s_func_init)(int*, char***);
    if (!s_func_init)
        dlsym(gtk, "gtk_init", s_func_init)(NULL, NULL);

    static GtkWidget* (*s_func)(GtkWindowType);
    return gtk_func(t);
}

void gtk_widget_show_all(GtkWidget* widget)
{
    static void (*s_func)(GtkWidget*);
    gtk_func(widget);
}

void gtk_widget_destroy(GtkWidget* widget)
{
    static void (*s_func)(GtkWidget*);
    gtk_func(widget);
}

void gtk_window_set_title(GtkWindow* window, const gchar* title)
{
    static void (*s_func)(GtkWindow*, const gchar*);
    gtk_func(window, title);
}

void gtk_widget_set_size_request(GtkWidget* widget, gint width, gint height)
{
    static void (*s_func)(GtkWidget*, gint, gint);
    gtk_func(widget, width, height);
}

void gtk_window_set_default_size(GtkWindow* window, gint width, gint height)
{
    static void (*s_func)(GtkWindow*, gint, gint);
    gtk_func(window, width, height);
}

void gtk_window_resize(GtkWindow* window, gint width, gint height)
{
    static void (*s_func)(GtkWindow*, gint, gint);
    gtk_func(window, width, height);
}

void gtk_window_move(GtkWindow* window, gint x, gint y)
{
    static void (*s_func)(GtkWindow*, gint, gint);
    gtk_func(window, x, y);
}

void gtk_window_set_decorated(GtkWindow* window, gboolean setting)
{
    static void (*s_func)(GtkWindow*, gboolean);
    gtk_func(window, setting);
}

void gtk_window_set_resizable(GtkWindow* window, gboolean resizable)
{
    static void (*s_func)(GtkWindow*, gboolean);
    gtk_func(window, resizable);
}

GtkWidget* gtk_scrolled_window_new(GtkAdjustment* hadjustment, GtkAdjustment* vadjustment)
{
    static GtkWidget* (*s_func)(GtkAdjustment*, GtkAdjustment*);
    return gtk_func(hadjustment, vadjustment);
}

gulong g_signal_connect_data(gpointer object, const gchar* name, GCallback func,
    gpointer func_data, GClosureNotify destroy_data, GConnectFlags connect_flags)
{
    static gulong (*s_func)(gpointer, const gchar*,
        GCallback, gpointer, GClosureNotify, GConnectFlags)
        = 0;
    return gtk_func(
        object, name, func, func_data, destroy_data, connect_flags);
}

GdkScreen* gdk_screen_get_default()
{
    static GdkScreen* (*s_func)();
    return gtk_func();
}

GdkScreen* gtk_widget_get_screen(GtkWidget* widget)
{
    static GdkScreen* (*s_func)(GtkWidget*);
    return gtk_func(widget);
}

guint gdk_screen_get_height(GdkScreen* scr)
{
    static guint (*s_func)(GdkScreen*);
    return gtk_func(scr);
}

guint gdk_screen_get_width(GdkScreen* scr)
{
    static guint (*s_func)(GdkScreen*);
    return gtk_func(scr);
}

void gtk_widget_grab_focus(GtkWidget* widget)
{
    static void (*s_func)(GtkWidget*);
    gtk_func(widget);
}

void gtk_container_add(GtkContainer* container, GtkWidget* widget)
{
    static void (*s_func)(GtkContainer*, GtkWidget*);
    gtk_func(container, widget);
}

GType webkit_web_view_get_type(void)
{
    static GType (*s_func)();
    return webkit_func();
}

GtkWidget* webkit_web_view_new(void)
{
    static GtkWidget* (*s_func)();
    return webkit_func();
}

void webkit_web_view_load_uri(GtkWidget* widget, const char* url)
{
    static void (*s_func)(GtkWidget*, const char*);
    webkit_func(widget, url);
}

const gchar* webkit_web_view_get_title(WebKitWebView* web_view)
{
    static const gchar* (*s_func)(WebKitWebView*);
    return webkit_func(web_view);
}

WebKitWebContext* webkit_web_context_get_default()
{
    static WebKitWebContext* (*s_func)();
    return webkit_func();
}

void webkit_web_context_set_web_extensions_directory(WebKitWebContext* context, const gchar* directory)
{
    static void (*s_func)(WebKitWebContext*, const gchar*);
    webkit_func(context, directory);
}

void webkit_web_context_set_cache_model(WebKitWebContext* context, WebKitCacheModel cache_model)
{
    static void (*s_func)(WebKitWebContext*, WebKitCacheModel);
    webkit_func(context, cache_model);
}

void webkit_web_context_clear_cache(WebKitWebContext* context)
{
    static void (*s_func)(WebKitWebContext*);
    webkit_func(context);
}

}

#endif