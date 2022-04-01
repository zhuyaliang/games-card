#include "games-window.h"
#include "games-utils.h"

int main (int argc, char *argv[])
{
    GtkWidget *window;
 
    bindtextdomain (GETTEXT_PACKAGE, LUNAR_CALENDAR_LOCALEDIR);
    textdomain (GETTEXT_PACKAGE);

    gtk_init (&argc, &argv);
    
    window = games_window_new ();
    
    gtk_widget_show (window);
  
    gtk_main ();
  
    return 0;
}
