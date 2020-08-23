/*
 * WebView.h
 *
 *  Created on: Aug 8, 2020
 *      Author: lion
 */
#if !defined(_WIN32) && !defined(__APPLE__)

#include "ifs/WebView.h"
#include "dl_gtk.h"

#ifndef WEBVIEW_GTK_H_
#define WEBVIEW_GTK_H_

namespace fibjs {

#define CW_USEDEFAULT -1

class WebView : public WebView_base {
    FIBER_FREE();

public:
    WebView(exlib::string url, NObject* opt);
    ~WebView();

    result_t open();

    EVENT_SUPPORT();

public:
    // WebView_base
    virtual result_t setHtml(exlib::string html, AsyncEvent* ac);
    virtual result_t print(int32_t mode, AsyncEvent* ac);
    virtual result_t close(AsyncEvent* ac);
    virtual result_t postMessage(exlib::string msg, AsyncEvent* ac);
    virtual result_t get_visible(bool& retVal);
    virtual result_t set_visible(bool newVal);

public:
    EVENT_FUNC(load);
    EVENT_FUNC(move);
    EVENT_FUNC(resize);
    EVENT_FUNC(closed);
    EVENT_FUNC(message);

public:
    static void destroy_Window(GtkWidget* widget, gpointer data);
    static void changed_title(GObject* obj, GParamSpec* pspec, gpointer data);
    static gboolean close_WebView(GtkWidget* web_view, GtkWidget* window);
    static gboolean load_failed_WebView(GtkWidget* web_view, WebKitLoadEvent load_event,
        gchar* failing_uri, gpointer error, gpointer user_data);
    static gboolean configure(GtkWidget* widget, GdkEventConfigure* event, gpointer user_data);
    static void console_message(WebKitWebPage* web_page, WebKitConsoleMessage* console_message, gpointer user_data);
    static void resource_request_starting(WebKitWebView* web_view, WebKitWebFrame* web_frame, WebKitWebResource* web_resource,
        WebKitNetworkRequest* request, WebKitNetworkResponse* response, gpointer user_data);

protected:
    int x = CW_USEDEFAULT;
    int y = CW_USEDEFAULT;
    int nWidth = CW_USEDEFAULT;
    int nHeight = CW_USEDEFAULT;

    exlib::string m_url;
    obj_ptr<NObject> m_opt;

    GtkWidget* m_window;
    GtkWidget* m_webview;
};

} /* namespace fibjs */
#endif /* WEBVIEW_GTK_H_ */
#endif /* !defined(_WIN32) && !defined(__APPLE__) */