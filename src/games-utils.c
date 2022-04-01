#include "games-utils.h"

GtkWidget *set_button_icon (const gchar *icon_path)
{
    GtkWidget *button;
    GtkWidget *image;
    GdkPixbuf *pb1 = NULL;

    pb1 = gdk_pixbuf_new_from_file (icon_path, NULL);

    button = gtk_button_new ();
    image  = gtk_image_new_from_pixbuf (pb1);
    gtk_button_set_image (GTK_BUTTON (button), image);

    return button;
}

