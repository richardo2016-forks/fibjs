/*
 * WebView.cpp
 *
 *  Created on: Aug 8, 2020
 *      Author: lion
 */

#if !defined(_WIN32) && !defined(__APPLE__)

#include "object.h"
#include "ifs/gui.h"
#include "dl_gtk.h"
#include "WebView.h"

namespace fibjs {

DECLARE_MODULE(gui);

static bool s_inited;
exlib::OSThread* pth;

static int idle_proc(void* data)
{
    AsyncEvent* p = (AsyncEvent*)data;
    p->invoke();
    return 0;
}

void putGuiPool(AsyncEvent* ac)
{
    pth->resume();
    g_idle_add(idle_proc, ac);
}

void init_gui()
{
    s_inited = gtk_init();
}

void run_gui()
{
    exlib::OSThread th;
    pth = &th;

    th.bindCurrent();
    Runtime rtForThread(NULL);

    th.suspend();

    if (s_inited)
        gtk_main();
}

result_t gui_base::setVersion(int32_t ver)
{
    return 0;
}

static result_t async_open(obj_ptr<WebView> w)
{
    w->open();
    return 0;
}

result_t gui_base::open(exlib::string url, v8::Local<v8::Object> opt, obj_ptr<WebView_base>& retVal)
{
    obj_ptr<NObject> o = new NObject();
    o->add(opt);

    obj_ptr<WebView> w = new WebView(url, o);
    w->wrap();

    asyncCall(async_open, w, CALL_E_GUICALL);
    retVal = w;

    return 0;
}

WebView::WebView(exlib::string url, NObject* opt)
{
    holder()->Ref();

    m_url = url;
    m_opt = opt;

    m_window = NULL;
}

WebView::~WebView()
{
}

void WebView::destroy_Window(GtkWidget* widget, gpointer data)
{
    obj_ptr<WebView> pView = (WebView*)data;
    pView->holder()->Unref();
    pView->Unref();
}

void WebView::changed_title(GObject* obj, GParamSpec* pspec, gpointer data)
{
    obj_ptr<WebView> web = (WebView*)data;
    const gchar* title = webkit_web_view_get_title(WEBKIT_WEB_VIEW(web->m_webview));
    if (title)
        gtk_window_set_title(GTK_WINDOW(web->m_window), title);
}

gboolean WebView::close_WebView(GtkWidget* web_view, GtkWidget* window)
{
    puts("close_WebView");
    gtk_widget_destroy(window);
    return true;
}

gboolean WebView::load_failed_WebView(GtkWidget* web_view, WebKitLoadEvent load_event,
    gchar* failing_uri, gpointer error, gpointer user_data)
{
    puts(failing_uri);
}

#define CW_USEDEFAULT -1

result_t WebView::open()
{
    int x = CW_USEDEFAULT;
    int y = CW_USEDEFAULT;
    int nWidth = CW_USEDEFAULT;
    int nHeight = CW_USEDEFAULT;

    m_window = gtk_window_new(GTK_WINDOW_TOPLEVEL);

    if (m_opt) {
        Variant v;

        if (m_opt->get("left", v) == 0)
            x = v.intVal();
        if (m_opt->get("top", v) == 0)
            y = v.intVal();
        if (m_opt->get("width", v) == 0)
            nWidth = v.intVal();
        if (m_opt->get("height", v) == 0)
            nHeight = v.intVal();

        if (m_opt->get("border", v) == 0 && !v.boolVal()) {
            gtk_window_set_decorated(GTK_WINDOW(m_window), false);
            gtk_window_set_resizable(GTK_WINDOW(m_window), false);
        } else {
            if (m_opt->get("caption", v) == 0 && !v.boolVal())
                gtk_window_set_decorated(GTK_WINDOW(m_window), false);

            if (m_opt->get("resizable", v) == 0 && !v.boolVal())
                gtk_window_set_resizable(GTK_WINDOW(m_window), false);
        }
    }

    GdkScreen* scr = gtk_widget_get_screen(m_window);
    int32_t screen_width = gdk_screen_get_width(scr);
    int32_t screen_height = gdk_screen_get_height(scr);

    if (nWidth == CW_USEDEFAULT)
        nWidth = screen_width * 3 / 4;

    if (nHeight == CW_USEDEFAULT)
        nHeight = screen_height * 3 / 4;

    if (x == CW_USEDEFAULT)
        x = (screen_width - nWidth) / 2;

    if (y == CW_USEDEFAULT)
        y = (screen_height - nHeight) / 2;

    gtk_window_move(GTK_WINDOW(m_window), x, y);
    gtk_widget_set_size_request(m_window, nWidth, nHeight);

    GtkWidget* scrolled_window = gtk_scrolled_window_new(NULL, NULL);
    gtk_container_add(GTK_CONTAINER(m_window), scrolled_window);

    m_webview = webkit_web_view_new();
    gtk_container_add(GTK_CONTAINER(scrolled_window), m_webview);
    gtk_widget_grab_focus(m_webview);

    g_signal_connect(m_window, "destroy", G_CALLBACK(destroy_Window), this);
    // g_signal_connect(WEBKIT_WEB_VIEW(m_webview), "close", G_CALLBACK(close_WebView), this);
    g_signal_connect(WEBKIT_WEB_VIEW(m_webview), "notify::title", G_CALLBACK(changed_title), this);
    // g_signal_connect(WEBKIT_WEB_VIEW(m_webview), "load-failed", G_CALLBACK(load_failed_WebView), this);

    gtk_widget_show_all(m_window);
    webkit_web_view_load_uri(m_webview, m_url.c_str());

    Ref();

    return 0;
}

result_t WebView::setHtml(exlib::string html, AsyncEvent* ac)
{
    if (ac->isSync())
        return CHECK_ERROR(CALL_E_GUICALL);

    return 0;
}

result_t WebView::print(int32_t mode, AsyncEvent* ac)
{
    if (ac->isSync())
        return CHECK_ERROR(CALL_E_GUICALL);

    return 0;
}

result_t WebView::close(AsyncEvent* ac)
{
    if (ac->isSync())
        return CHECK_ERROR(CALL_E_GUICALL);

    return 0;
}

result_t WebView::postMessage(exlib::string msg, AsyncEvent* ac)
{
    if (ac->isSync())
        return CHECK_ERROR(CALL_E_GUICALL);

    return 0;
}

result_t WebView::get_visible(bool& retVal)
{
    return 0;
}

result_t WebView::set_visible(bool newVal)
{
    return 0;
}
}

#endif