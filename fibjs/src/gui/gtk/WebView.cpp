/*
 * WebView.cpp
 *
 *  Created on: Aug 8, 2020
 *      Author: lion
 */

#if !defined(_WIN32) && !defined(__APPLE__)

#include "object.h"
#include "ifs/gui.h"
#include "ifs/fs.h"
#include "dl_gtk.h"
#include "WebView.h"
#include "EventInfo.h"

namespace fibjs {

DECLARE_MODULE(gui);

static gint s_sdk;
exlib::OSThread* pth;

extern exlib::LockedList<Isolate> s_isolates;

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

__attribute__((visibility("default"))) extern "C" void webkit_web_extension_initialize(WebKitWebExtension* extension)
{
    puts("webkit_web_extension_initialize");
    // g_signal_connect(extension, "page-created",
    //     G_CALLBACK(web_page_created_callback),
    //     NULL);
}

static void initialize_web_extensions(WebKitWebContext* context, gpointer user_data)
{
    puts("initialize_web_extensions");
    webkit_web_context_set_web_extensions_directory(context, ".");
}

static void scheme_callback(WebKitURISchemeRequest* request, gpointer data)
{
    const gchar* url = webkit_uri_scheme_request_get_uri(request);
    if (qstrcmp(url, "fs://", 5))
        return;

    exlib::string contents;
    result_t hr = fs_base::cc_readTextFile(url + 5, contents, s_isolates.head());
    if (hr < 0)
        return;

    GInputStream* stream = g_memory_input_stream_new_from_data(contents.c_str(), contents.length(), NULL);
    webkit_uri_scheme_request_finish(request, stream, contents.length(), "");
    g_object_unref(stream);
}

void init_gui()
{
    s_sdk = gtk_init();
}

void run_gui()
{
    exlib::OSThread th;
    pth = &th;

    th.bindCurrent();
    Runtime rtForThread(NULL);

    th.suspend();

    if (s_sdk) {
        if (s_sdk & WEBKIT_V2) {
            WebKitWebContext* ctx = webkit_web_context_get_default();
            webkit_web_context_clear_cache(ctx);
            webkit_web_context_register_uri_scheme(ctx, "fs", scheme_callback, NULL, NULL);
            g_signal_connect(ctx, "initialize-web-extensions", G_CALLBACK(initialize_web_extensions), NULL);
        }
        gtk_main();
    }
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

gboolean WebView::configure(GtkWidget* widget, GdkEventConfigure* event, gpointer user_data)
{
    obj_ptr<WebView> web = (WebView*)user_data;

    if (web->x != event->x || web->y != event->x) {
        web->x = event->x;
        web->y = event->y;

        obj_ptr<EventInfo> ei = new EventInfo(web, "move");
        ei->add("left", web->x);
        ei->add("top", web->y);

        web->_emit("move", ei);
    }

    if (web->nWidth != event->width || web->nHeight != event->height) {
        web->nWidth = event->width;
        web->nHeight = event->height;

        obj_ptr<EventInfo> ei = new EventInfo(web, "resize");
        ei->add("width", web->nWidth);
        ei->add("height", web->nHeight);

        web->_emit("resize", ei);
    }

    return false;
}

void WebView::console_message(WebKitWebPage* web_page, WebKitConsoleMessage* console_message, gpointer user_data)
{
}

void WebView::resource_request_starting(WebKitWebView* web_view, WebKitWebFrame* web_frame, WebKitWebResource* web_resource,
    WebKitNetworkRequest* request, WebKitNetworkResponse* response, gpointer user_data)
{
    puts("resource_request_starting");
}

result_t WebView::open()
{
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

    gtk_window_move(GTK_WINDOW(GTK_WINDOW(m_window)), x, y);
    gtk_window_set_default_size(GTK_WINDOW(m_window), nWidth, nHeight);

    m_webview = webkit_web_view_new();

    GtkWidget* scrolled_window = gtk_scrolled_window_new(NULL, NULL);
    gtk_container_add(GTK_CONTAINER(m_window), GTK_WIDGET(scrolled_window));
    gtk_container_add(GTK_CONTAINER(scrolled_window), GTK_WIDGET(m_webview));

    gtk_widget_grab_focus(m_webview);

    g_signal_connect(GTK_WIDGET(m_window), "destroy", G_CALLBACK(destroy_Window), this);
    g_signal_connect(GTK_WIDGET(m_window), "configure-event", G_CALLBACK(configure), this);

    g_signal_connect(GTK_WIDGET(m_webview), "notify::title", G_CALLBACK(changed_title), this);

    if (s_sdk & WEBKIT_V1)
        g_signal_connect(GTK_WIDGET(m_webview), "resource-request-starting", G_CALLBACK(resource_request_starting), this);

    // g_signal_connect(WEBKIT_WEB_VIEW(m_webview), "close", G_CALLBACK(close_WebView), this);
    // g_signal_connect(WEBKIT_WEB_VIEW(m_webview), "console-message-sent", G_CALLBACK(console_message), this);
    // g_signal_connect(WEBKIT_WEB_VIEW(m_webview), "load-failed", G_CALLBACK(load_failed_WebView), this);
    // webkit_web_context_register_uri_scheme

    gtk_widget_show_all(GTK_WIDGET(m_window));
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

    gtk_widget_destroy(m_window);
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