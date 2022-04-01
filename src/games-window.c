#include "games-window.h"
#include "games-utils.h"

typedef enum {
    CARD_ACTION_INIT,
    CARD_ACTION_SHOW,
    CARD_ACTION_DISCARD,
} CardActionMode;

struct _GamesWindowPrivate 
{
    GtkBuilder *builder;
    GtkWidget  *hand_image[3];
    GtkWidget  *other_image;
   
    CardActionMode card_mode;
    gint        size;
};

G_DEFINE_TYPE_WITH_PRIVATE (GamesWindow, games_window, GTK_TYPE_WINDOW)

static void set_window_background (GtkWidget *window, gint size)
{
    GtkCssProvider  *provider;
    GtkStyleContext *context;
    gchar           *css = NULL;

    provider = gtk_css_provider_new ();
    context = gtk_widget_get_style_context (window);
    css = g_strdup_printf ("window {background-image: url('file:///usr/share/games-card/table/table.png');background-size:  %dpx}", size-6);
    gtk_css_provider_load_from_data (provider, css, -1, NULL);
    gtk_style_context_add_provider (context,
                                    GTK_STYLE_PROVIDER (provider),
                                    GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);
    g_object_unref (provider);
    g_free (css);
}

static GtkWidget *create_box_widget (GtkOrientation orientation, gint spacing)
{
    GtkWidget *box;

    box = gtk_box_new (orientation, 0);
    gtk_widget_show (box);
    gtk_container_set_border_width (GTK_CONTAINER (box), spacing);

    return box;
}

static GPtrArray *games_window_get_hand_list (GamesWindow *gw)
{
    GPtrArray  *hand_list;

    hand_list = g_ptr_array_new ();
    
    if (gw->priv->card_mode == CARD_ACTION_INIT)
        for (int i = 0; i < 3; i++)
            g_ptr_array_add (hand_list, CLASSIC"/bb.png");
    else if (gw->priv->card_mode == CARD_ACTION_SHOW)
    {
        g_ptr_array_add (hand_list, CLASSIC"/Ac.png");
        g_ptr_array_add (hand_list, CLASSIC"/As.png");
        g_ptr_array_add (hand_list, CLASSIC"/Ad.png");
    }
    else
    {
        g_ptr_array_add (hand_list, CLASSIC"/bb-d.png");
        g_ptr_array_add (hand_list, CLASSIC"/bb-d.png");
        g_ptr_array_add (hand_list, CLASSIC"/bb-d.png");
    }

    return hand_list;
}

static void games_window_set_hand_image (GamesWindow *gw)
{
    g_autoptr(GdkPixbuf) pb1 = NULL;
    GdkPixbuf *pb2;
    char      *image_path;
    GPtrArray *hand_list;
    
    hand_list = games_window_get_hand_list (gw);
    for (int i = 0; i < hand_list->len; i++)
    {
        image_path  = g_ptr_array_index (hand_list, i);
        pb1 = gdk_pixbuf_new_from_file (image_path, NULL);
        g_print ("image_path = %s\r\n",image_path);
        pb2 = gdk_pixbuf_scale_simple (pb1, 100, 145, GDK_INTERP_BILINEAR);
        gtk_image_set_from_pixbuf (GTK_IMAGE (gw->priv->hand_image[i]), pb2);
    }
}

static void
on_show_card (GtkWidget *widget, gpointer data)
{
    GamesWindow *gameswin;

    gameswin = GAMES_WINDOW (data);
    gtk_widget_set_sensitive (widget, FALSE);
    gameswin->priv->card_mode = CARD_ACTION_SHOW;

    games_window_set_hand_image (gameswin);

}

static void
on_discard_hand (GtkWidget *widget, gpointer data)
{
    GamesWindow *gameswin;

    gameswin = GAMES_WINDOW (data);
    gtk_widget_set_sensitive (widget, FALSE);
    gameswin->priv->card_mode = CARD_ACTION_DISCARD;

    games_window_set_hand_image (gameswin);

}

static void create_opponent_area (GtkWidget *box)
{
    GtkWidget *table;
    GtkWidget *label;
    GdkPixbuf *pb2;
    GdkPixbuf *pb1;
    GtkWidget *image;

    table = gtk_grid_new ();
    gtk_widget_show (table);
    gtk_box_pack_end (GTK_BOX (box), table, TRUE, FALSE, 6);
    gtk_grid_set_column_homogeneous (GTK_GRID (table), TRUE);

    label = gtk_label_new (NULL);
    gtk_widget_show (label);
    gtk_grid_attach (GTK_GRID (table), label, 0, 0, 13, 2);

    pb1 = gdk_pixbuf_new_from_file(CLASSIC"/bbb-d.png", NULL);
    pb2 = gdk_pixbuf_scale_simple (pb1, 70, 82, GDK_INTERP_BILINEAR);
    image = gtk_image_new_from_pixbuf(pb2);
    gtk_grid_attach (GTK_GRID (table), image, 6, 3, 1, 1);

    image = gtk_image_new_from_pixbuf(pb2);
    gtk_grid_attach (GTK_GRID (table), image, 9, 5, 1, 1);

    image = gtk_image_new_from_pixbuf(pb2);
    gtk_grid_attach (GTK_GRID (table), image, 3, 5, 1, 1);

    image = gtk_image_new_from_pixbuf(pb2);
    gtk_grid_attach (GTK_GRID (table), image, 1, 7, 1, 1);

    image = gtk_image_new_from_pixbuf(pb2);
    gtk_grid_attach (GTK_GRID (table), image, 11, 7, 1, 1);

}

void
system_user_info (GSimpleAction *action,
                  GVariant      *parameter,
                  gpointer       user_data)
{

}

static const GActionEntry actions[] = {
  { "system-user-info",    system_user_info },
};

static GtkWidget *create_jeton_menu_button (GamesWindow *gameswin,
                                            const char    *object_id)
{
    GtkWidget  *menu_button;
    GtkWidget  *popover;
    GSimpleActionGroup *action_group;

    menu_button = gtk_menu_button_new ();
    gtk_button_set_label (GTK_BUTTON (menu_button), "加注");
    gtk_widget_set_opacity (menu_button, 0.75);
    action_group = g_simple_action_group_new ();
    g_action_map_add_action_entries (G_ACTION_MAP (action_group),
                                     actions,
                                     G_N_ELEMENTS (actions),
                                     gameswin);

    gtk_widget_insert_action_group (GTK_WIDGET(gameswin), "win", G_ACTION_GROUP (action_group));
    popover = (GtkWidget *)gtk_builder_get_object (gameswin->priv->builder, object_id);
    gtk_menu_button_set_popover (GTK_MENU_BUTTON (menu_button), popover);

    return menu_button;
}

static void
games_window_fill (GamesWindow *gameswin)
{
    GtkWidget *frame;
    GtkWidget *box;
    GtkWidget *hbox;
    GtkWidget *vbox;
    GtkWidget *chips_hbox;
    GtkWidget *table;
    GtkWidget *label;
    GtkWidget *button;

    set_window_background (GTK_WIDGET (gameswin), gameswin->priv->size);
    games_window_set_hand_image (gameswin);

    frame = gtk_frame_new (NULL);
    gtk_widget_show (frame);
    gtk_frame_set_shadow_type (GTK_FRAME (frame), GTK_SHADOW_OUT);
    gtk_container_add (GTK_CONTAINER (gameswin), frame);

    box = gtk_box_new (GTK_ORIENTATION_VERTICAL, 0);
    gtk_widget_show (box);
    gtk_container_set_border_width (GTK_CONTAINER (box), 0);
    gtk_container_add (GTK_CONTAINER (frame), box);

    hbox = create_box_widget (GTK_ORIENTATION_VERTICAL, 100);
    gtk_box_pack_start (GTK_BOX (box), hbox, TRUE, TRUE, 0);
    create_opponent_area (hbox);

    hbox = create_box_widget (GTK_ORIENTATION_VERTICAL, 100);
    gtk_box_pack_start (GTK_BOX (box), hbox, TRUE, TRUE, 0);

    vbox = create_box_widget (GTK_ORIENTATION_VERTICAL, 18);
    gtk_box_pack_end (GTK_BOX (box), vbox, TRUE, TRUE, 0);

    table = gtk_grid_new ();
    gtk_widget_show (table);
    gtk_box_pack_end (GTK_BOX (vbox), table, TRUE, FALSE, 6);
    gtk_grid_set_column_homogeneous (GTK_GRID (table), TRUE);

    label = gtk_label_new (NULL);
    gtk_widget_show (label);
    gtk_grid_attach (GTK_GRID (table), label, 0, 0, 12, 2);
    gtk_grid_attach (GTK_GRID (table), gameswin->priv->hand_image[0], 6, 3, 1, 1);
    gtk_grid_attach (GTK_GRID (table), gameswin->priv->hand_image[1], 5, 3, 2, 1);
    gtk_grid_attach (GTK_GRID (table), gameswin->priv->hand_image[2], 4, 3, 3, 1);

    chips_hbox = create_box_widget (GTK_ORIENTATION_HORIZONTAL, 18);
    gtk_grid_attach (GTK_GRID (table), chips_hbox, 4, 4, 3, 1);

    button = gtk_button_new_with_label (_("show card"));
    gtk_widget_set_opacity (button, 0.75);
    gtk_box_pack_start (GTK_BOX (chips_hbox), button, TRUE, TRUE, 6);
    g_signal_connect (button,
                     "clicked",
                      G_CALLBACK (on_show_card),
                      gameswin);

    button = gtk_button_new_with_label ("跟注");
    gtk_widget_set_opacity (button, 0.75);
    gtk_box_pack_start (GTK_BOX (chips_hbox), button, TRUE, TRUE, 6);

    button = create_jeton_menu_button (gameswin, "popover-jeton");
    gtk_box_pack_start (GTK_BOX (chips_hbox), button, TRUE, TRUE, 6);

    button = gtk_button_new_with_label ("开牌");
    gtk_widget_set_opacity (button, 0.75);
    gtk_box_pack_start (GTK_BOX (chips_hbox), button, TRUE, TRUE, 6);

    button = gtk_button_new_with_label ("弃牌");
    gtk_widget_set_opacity (button, 0.75);
    gtk_box_pack_start (GTK_BOX (chips_hbox), button, TRUE, TRUE, 6);
    g_signal_connect (button,
                     "clicked",
                      G_CALLBACK (on_discard_hand),
                      gameswin);

    gtk_widget_show_all (box);
}

static GObject *
games_window_constructor (GType                  type,
                            guint                  n_construct_properties,
                            GObjectConstructParam *construct_properties)
{
    GObject        *obj;
    GamesWindow  *gameswin;

    obj = G_OBJECT_CLASS (games_window_parent_class)->constructor (type,
                                      n_construct_properties,
                                      construct_properties);

    gameswin = GAMES_WINDOW (obj);
    games_window_fill (gameswin);

    return obj;
}

static void gameswin_init_hand (GamesWindow *gw)
{
    gw->priv->card_mode = CARD_ACTION_INIT;

    for (int i = 0; i < 3; i++)
    {
        gw->priv->hand_image[i] = gtk_image_new ();
    }
}

static void
games_window_dispose (GObject *object)
{
//    GamesWindow *gw;

//    gw = GAMES_WINDOW (object);

    G_OBJECT_CLASS (games_window_parent_class)->dispose (object);
}

static void
games_window_class_init (GamesWindowClass *klass)
{
    GObjectClass   *gobject_class = G_OBJECT_CLASS (klass);

    gobject_class->constructor = games_window_constructor;
    gobject_class->dispose = games_window_dispose;
}

static void
games_window_init (GamesWindow *gameswin)
{
    GtkWindow  *window;
    GdkDisplay *display;
    GdkMonitor *monitor;
    GdkRectangle rect;

    gameswin->priv = games_window_get_instance_private (gameswin);

    display = gdk_display_get_default ();
    monitor = gdk_display_get_primary_monitor (display);
    gdk_monitor_get_geometry (monitor, &rect);

    window = GTK_WINDOW (gameswin);
    gtk_window_set_resizable (window, FALSE);
    gtk_window_maximize (GTK_WINDOW (window));

    gameswin->priv->size = rect.width;
    gameswin_init_hand (gameswin);
    gameswin->priv->builder = gtk_builder_new_from_resource ("/org/games/card/jeton-menus-function-manager.ui");

}

GtkWidget *
games_window_new (void)
{
    GamesWindow *gameswin;

    gameswin = g_object_new (GAMES_TYPE_WINDOW,
                              "type", GTK_WINDOW_TOPLEVEL,
                              "window-position", GTK_WIN_POS_CENTER,
                               NULL);

    return GTK_WIDGET (gameswin);
}
