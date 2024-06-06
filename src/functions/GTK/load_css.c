
static void load_css(void) {
    GtkCssProvider *provider;
    GdkDisplay *display;
    GdkScreen *screen;

    provider = gtk_css_provider_new();
    display = gdk_display_get_default();
    screen = gdk_display_get_default_screen(display);

    gtk_style_context_add_provider_for_screen(screen, GTK_STYLE_PROVIDER(provider), GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);

    const gchar *cssFilePath = "../resources/style.css";
    GError *error = 0;
    gtk_css_provider_load_from_path(provider, cssFilePath, &error);
    if (error) {
        g_warning("Error loading CSS file: %s", error->message);
        g_clear_error(&error);
    } else {
        Logger(2, "CSS Loaded Successfully");
    }

    g_object_unref(provider);
}