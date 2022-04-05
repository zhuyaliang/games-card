#include "games-player.h"
#include "games-utils.h"

typedef enum {
    CARD_ACTION_INIT,
    CARD_ACTION_SHOW,
    CARD_ACTION_DISCARD,
} CardActionMode;

struct _GamesPlayerPrivate 
{
    GtkWidget  *label_info;
    GtkWidget  *label_action;
    GtkWidget  *image_face;
    GtkWidget  *label_message;
    GtkWidget  *image;

    CardActionMode card_mode;
};

G_DEFINE_TYPE_WITH_PRIVATE (GamesPlayer, games_player, GTK_TYPE_BOX)

static void
games_player_fill (GamesPlayer *gp)
{
    g_autoptr(GdkPixbuf) pb1 = NULL;
    GdkPixbuf *pb2;

    gtk_orientable_set_orientation (GTK_ORIENTABLE (gp), GTK_ORIENTATION_VERTICAL);

    gp->priv->label_action = gtk_label_new (_("Show card"));
    gtk_box_pack_start (GTK_BOX (gp), gp->priv->label_action, TRUE, TRUE, 6);

    gp->priv->image_face = gtk_image_new ();
    gtk_box_pack_start (GTK_BOX (gp), gp->priv->image_face, TRUE, TRUE, 6);
    pb1 = gdk_pixbuf_new_from_file ("/tmp/cat.jpg", NULL);
    pb2 = gdk_pixbuf_scale_simple (pb1, 70, 80, GDK_INTERP_BILINEAR);
    gtk_image_set_from_pixbuf (GTK_IMAGE (gp->priv->image_face), pb2);

    gp->priv->label_info = gtk_label_new (_("Player A\r\njeton: 5000"));
    gtk_box_pack_start (GTK_BOX (gp), gp->priv->label_info, TRUE, TRUE, 6);

    gp->priv->image = gtk_image_new ();
    gtk_box_pack_start (GTK_BOX (gp), gp->priv->image, TRUE, TRUE, 6);
    pb1 = gdk_pixbuf_new_from_file ("/usr/share/games-card/table/dealer_button.png", NULL);
    pb2 = gdk_pixbuf_scale_simple (pb1, 40, 40, GDK_INTERP_BILINEAR);
    gtk_image_set_from_pixbuf (GTK_IMAGE (gp->priv->image), pb2);

    gp->priv->label_message = gtk_label_new (_("yijing jia zhu"));
}

static GObject *
games_player_constructor (GType                  type,
                          guint                  n_construct_properties,
                          GObjectConstructParam *construct_properties)
{
    GObject      *obj;
    GamesPlayer  *gp;

    obj = G_OBJECT_CLASS (games_player_parent_class)->constructor (type,
                                      n_construct_properties,
                                      construct_properties);

    gp = GAMES_PLAYER (obj);
    games_player_fill (gp);

    return obj;
}

static void
games_player_dispose (GObject *object)
{
//    GamesPlayer *gw;

//    gw = GAMES_PLAYER (object);

    G_OBJECT_CLASS (games_player_parent_class)->dispose (object);
}

static void
games_player_class_init (GamesPlayerClass *klass)
{
    GObjectClass *gobject_class = G_OBJECT_CLASS (klass);

    gobject_class->constructor = games_player_constructor;
    gobject_class->dispose = games_player_dispose;
}

static void
games_player_init (GamesPlayer *gp)
{
    gp->priv = games_player_get_instance_private (gp);
}

GtkWidget *
games_player_new (void)
{
    GamesPlayer *gp;

    gp = g_object_new (GAMES_TYPE_PLAYER, NULL);

    return GTK_WIDGET (gp);
}
