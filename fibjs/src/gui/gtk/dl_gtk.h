/*
 * dl_gtk.h
 *
 *  Created on: Aug 8, 2020
 *      Author: lion
 */

#ifndef DL_GTK_H_
#define DL_GTK_H_

#include <stdint.h>

namespace fibjs {

typedef enum {
    GTK_ACCEL_VISIBLE = 1 << 0,
    GTK_ACCEL_LOCKED = 1 << 1,
    GTK_ACCEL_MASK = 0x07
} GtkAccelFlags;

typedef enum {
    GTK_BASELINE_POSITION_TOP,
    GTK_BASELINE_POSITION_CENTER,
    GTK_BASELINE_POSITION_BOTTOM
} GtkBaselinePosition;

typedef enum {
    GTK_ORIENTATION_HORIZONTAL,
    GTK_ORIENTATION_VERTICAL
} GtkOrientation;

typedef enum {
    GTK_PACK_START,
    GTK_PACK_END
} GtkPackType;

typedef enum {
    GTK_WINDOW_TOPLEVEL,
    GTK_WINDOW_POPUP
} GtkWindowType;

typedef enum {
    GTK_WIN_POS_NONE,
    GTK_WIN_POS_CENTER,
    GTK_WIN_POS_MOUSE
} GtkWindowPosition;

typedef enum {
    G_PARAM_READABLE = 1 << 0,
    G_PARAM_WRITABLE = 1 << 1,
    G_PARAM_CONSTRUCT = 1 << 2,
    G_PARAM_CONSTRUCT_ONLY = 1 << 3,
    G_PARAM_LAX_VALIDATION = 1 << 4,
    G_PARAM_STATIC_NAME = 1 << 5,
    G_PARAM_STATIC_NICK = 1 << 6,
    G_PARAM_STATIC_BLURB = 1 << 7,
    /* User defined flags go up to 30 */
    G_PARAM_DEPRECATED = 1 << 31
} GParamFlags;

typedef enum {
    G_SIGNAL_RUN_FIRST = 1 << 0,
    G_SIGNAL_RUN_LAST = 1 << 1,
    G_SIGNAL_RUN_CLEANUP = 1 << 2,
    G_SIGNAL_NO_RECURSE = 1 << 3,
    G_SIGNAL_DETAILED = 1 << 4,
    G_SIGNAL_ACTION = 1 << 5,
    G_SIGNAL_NO_HOOKS = 1 << 6
} GSignalFlags;
#define G_SIGNAL_FLAGS_MASK 0x7f

typedef enum {
    G_CONNECT_AFTER = 1 << 0,
    G_CONNECT_SWAPPED = 1 << 1
} GConnectFlags;

typedef enum {
    G_SIGNAL_MATCH_ID = 1 << 0,
    G_SIGNAL_MATCH_DETAIL = 1 << 1,
    G_SIGNAL_MATCH_CLOSURE = 1 << 2,
    G_SIGNAL_MATCH_FUNC = 1 << 3,
    G_SIGNAL_MATCH_DATA = 1 << 4,
    G_SIGNAL_MATCH_UNBLOCKED = 1 << 5
} GSignalMatchType;

typedef void* gpointer;

typedef char gchar;
typedef short gshort;
typedef long glong;
typedef int gint;
typedef char gboolean;

typedef unsigned char guchar;
typedef unsigned short gushort;
typedef unsigned long gulong;
typedef unsigned int guint;

typedef float gfloat;
typedef double gdouble;

typedef int32_t gint;
typedef uint32_t guint;
typedef int8_t gint8;
typedef uint8_t guint8;
typedef uint16_t guint16;
typedef int16_t gint16;
typedef int32_t gint32;
typedef uint32_t guint32;
typedef int64_t gint64;
typedef uint64_t guint64;

typedef unsigned int gsize;
typedef const void* gconstpointer;
typedef guint32 gunichar;
typedef gulong GType;
typedef guint32 GQuark;

#define _G_TYPE_CIC(ip, gt, ct) ((ct*)g_type_check_instance_cast((GTypeInstance*)ip, gt))
#define G_TYPE_CHECK_INSTANCE_CAST(instance, g_type, c_type) (_G_TYPE_CIC((instance), (g_type), c_type))

struct GObject {
};

struct GTypeInstance {
};

struct GtkAdjustment {
};

struct GdkScreen {
};

struct GtkWidget {
};
#define GTK_WIDGET(obj) (G_TYPE_CHECK_INSTANCE_CAST((obj), gtk_widget_get_type(), GtkWidget))

struct GtkContainer {
};
#define GTK_CONTAINER(obj) (G_TYPE_CHECK_INSTANCE_CAST((obj), gtk_container_get_type(), GtkContainer))

struct GtkWindow {
};
#define GTK_WINDOW(obj) (G_TYPE_CHECK_INSTANCE_CAST((obj), gtk_window_get_type(), GtkWindow))

struct GParamSpec {
};

typedef enum {
    GDK_NOTHING = -1,
    GDK_DELETE = 0,
    GDK_DESTROY = 1,
    GDK_EXPOSE = 2,
    GDK_MOTION_NOTIFY = 3,
    GDK_BUTTON_PRESS = 4,
    GDK_2BUTTON_PRESS = 5,
    GDK_3BUTTON_PRESS = 6,
    GDK_BUTTON_RELEASE = 7,
    GDK_KEY_PRESS = 8,
    GDK_KEY_RELEASE = 9,
    GDK_ENTER_NOTIFY = 10,
    GDK_LEAVE_NOTIFY = 11,
    GDK_FOCUS_CHANGE = 12,
    GDK_CONFIGURE = 13,
    GDK_MAP = 14,
    GDK_UNMAP = 15,
    GDK_PROPERTY_NOTIFY = 16,
    GDK_SELECTION_CLEAR = 17,
    GDK_SELECTION_REQUEST = 18,
    GDK_SELECTION_NOTIFY = 19,
    GDK_PROXIMITY_IN = 20,
    GDK_PROXIMITY_OUT = 21,
    GDK_DRAG_BEGIN = 22,
    GDK_DRAG_REQUEST = 23,
    GDK_DROP_ENTER = 24,
    GDK_DROP_LEAVE = 25,
    GDK_DROP_DATA_AVAIL = 26,
    GDK_CLIENT_EVENT = 27,
    GDK_VISIBILITY_NOTIFY = 28,
    GDK_NO_EXPOSE = 29,
    GDK_OTHER_EVENT = 9999 /* Deprecated, use filters instead */
} GdkEventType;

struct GdkEventConfigure {
    GdkEventType type;
    void* window;
    gint8 send_event;
    gint x, y;
    gint width;
    gint height;
};

typedef void (*GCallback)(gpointer*);
typedef void (*GClosureNotify)(gpointer data, gpointer closure);

#define G_CALLBACK(f) (reinterpret_cast<GCallback>((f)))

#define GTK_V2 1
#define GTK_V3 2
#define WEBKIT_V1 4
#define WEBKIT_V2 8

gint gtk_init();
void gtk_main();
void g_idle_add(int (*func)(void*), void* data);

GTypeInstance* g_type_check_instance_cast(GTypeInstance* arg0, GType arg1);

GType gtk_window_get_type();
GType gtk_container_get_type();
GType gtk_widget_get_type();

GtkWidget* gtk_window_new(GtkWindowType);
void gtk_widget_show_all(GtkWidget* widget);
void gtk_widget_destroy(GtkWidget* widget);

GtkWidget* gtk_scrolled_window_new(GtkAdjustment* hadjustment, GtkAdjustment* vadjustment);

void gtk_window_set_title(GtkWindow* window, const gchar* title);

void gtk_widget_set_size_request(GtkWidget* widget, gint width, gint height);
void gtk_window_set_default_size(GtkWindow* window, gint width, gint height);
void gtk_window_resize(GtkWindow* window, gint width, gint height);
void gtk_window_move(GtkWindow* window, gint x, gint y);
void gtk_window_set_decorated(GtkWindow* window, gboolean setting);
void gtk_window_set_resizable(GtkWindow* window, gboolean resizable);

gulong g_signal_connect_data(gpointer object, const gchar* name, GCallback func,
    gpointer func_data, GClosureNotify destroy_data, GConnectFlags connect_flags);
#define g_signal_connect(instance, detailed_signal, c_handler, data) \
    g_signal_connect_data((instance), (detailed_signal), (c_handler), (data), NULL, (GConnectFlags)0)
#define g_signal_connect_after(instance, detailed_signal, c_handler, data) \
    g_signal_connect_data((instance), (detailed_signal), (c_handler), (data), NULL, G_CONNECT_AFTER)
#define g_signal_connect_swapped(instance, detailed_signal, c_handler, data) \
    g_signal_connect_data((instance), (detailed_signal), (c_handler), (data), NULL, G_CONNECT_SWAPPED)

GdkScreen* gdk_screen_get_default();
GdkScreen* gtk_widget_get_screen(GtkWidget* widget);
guint gdk_screen_get_height(GdkScreen* scr);
guint gdk_screen_get_width(GdkScreen* scr);

void gtk_widget_grab_focus(GtkWidget* widget);

void gtk_container_add(GtkContainer* container, GtkWidget* widget);

typedef enum {
    WEBKIT_LOAD_STARTED,
    WEBKIT_LOAD_REDIRECTED,
    WEBKIT_LOAD_COMMITTED,
    WEBKIT_LOAD_FINISHED
} WebKitLoadEvent;

typedef enum {
    WEBKIT_POLICY_DECISION_TYPE_NAVIGATION_ACTION,
    WEBKIT_POLICY_DECISION_TYPE_NEW_WINDOW_ACTION,
    WEBKIT_POLICY_DECISION_TYPE_RESPONSE,
} WebKitPolicyDecisionType;

typedef enum {
    WEBKIT_NAVRESP_ACCEPT,
    WEBKIT_NAVRESP_IGNORE,
    WEBKIT_NAVRESP_DOWNLOAD
} WebKitNavigationResponse;

typedef enum {
    WEBKIT_CONSOLE_MESSAGE_SOURCE_JAVASCRIPT,
    WEBKIT_CONSOLE_MESSAGE_SOURCE_NETWORK,
    WEBKIT_CONSOLE_MESSAGE_SOURCE_CONSOLE_API,
    WEBKIT_CONSOLE_MESSAGE_SOURCE_SECURITY,
    WEBKIT_CONSOLE_MESSAGE_SOURCE_OTHER
} WebKitConsoleMessageSource;

typedef enum {
    WEBKIT_CONSOLE_MESSAGE_LEVEL_INFO,
    WEBKIT_CONSOLE_MESSAGE_LEVEL_LOG,
    WEBKIT_CONSOLE_MESSAGE_LEVEL_WARNING,
    WEBKIT_CONSOLE_MESSAGE_LEVEL_ERROR,
    WEBKIT_CONSOLE_MESSAGE_LEVEL_DEBUG
} WebKitConsoleMessageLevel;

typedef enum {
    WEBKIT_CACHE_MODEL_DOCUMENT_VIEWER,
    WEBKIT_CACHE_MODEL_WEB_BROWSER,
    WEBKIT_CACHE_MODEL_DOCUMENT_BROWSER
} WebKitCacheModel;

struct WebKitWebView {
};
#define WEBKIT_WEB_VIEW(obj) (G_TYPE_CHECK_INSTANCE_CAST((obj), webkit_web_view_get_type(), WebKitWebView))

struct WebKitWebFrame {
};

struct WebKitWebResource {
};

struct WebKitNetworkRequest {
};

struct WebKitNetworkResponse {
};

struct WebKitWebPage {
};

struct WebKitWebContext {
};

struct WebKitWebExtension {
};

struct WebKitConsoleMessage {
};

struct WebKitURISchemeRequest {
};

struct GInputStream {
};

typedef void (*WebKitURISchemeRequestCallback)(WebKitURISchemeRequest*, gpointer);
typedef void (*GDestroyNotify)(gpointer);

GType webkit_web_view_get_type(void);
GtkWidget* webkit_web_view_new(void);
void webkit_web_view_load_uri(GtkWidget* widget, const char* url);
const gchar* webkit_web_view_get_title(WebKitWebView* web_view);

WebKitWebContext* webkit_web_context_get_default();
void webkit_web_context_set_web_extensions_directory(WebKitWebContext* context, const gchar* directory);
void webkit_web_context_set_cache_model(WebKitWebContext* context, WebKitCacheModel cache_model);
void webkit_web_context_clear_cache(WebKitWebContext* context);

void webkit_web_context_register_uri_scheme(WebKitWebContext* context, const gchar* scheme,
    WebKitURISchemeRequestCallback callback, gpointer user_data, GDestroyNotify user_data_destroy_func);

const gchar* webkit_uri_scheme_request_get_scheme(WebKitURISchemeRequest* request);
const gchar* webkit_uri_scheme_request_get_uri(WebKitURISchemeRequest* request);
const gchar* webkit_uri_scheme_request_get_path(WebKitURISchemeRequest* request);
WebKitWebView* webkit_uri_scheme_request_get_web_view(WebKitURISchemeRequest* request);
void webkit_uri_scheme_request_finish(WebKitURISchemeRequest* request, GInputStream* stream,
    gint64 stream_length, const gchar* content_type);

typedef signed long gssize;

void g_object_unref(gpointer object);
GInputStream* g_memory_input_stream_new_from_data(const void* data, gssize len, GDestroyNotify destroy);

}

#endif // DL_GTK_H_