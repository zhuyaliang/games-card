/*************************************************************************
  File Name: games-window.h
  
  Copyright (C) 2022  zhuyaliang https://github.com/zhuyaliang/
  This program is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.
                                      
  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.
                                               
  You should have received a copy of the GNU General Public License
  along with this program.  If not, see <https://www.gnu.org/licenses/>.
                                               
  Created Time: 2022年04月01日 星期五 11时17分17秒
 ************************************************************************/

#ifndef __GAMES_WINDOW__
#define __GAMES_WINDOW__

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif
#include <locale.h>
#include <glib/gi18n.h>

#include <gtk/gtk.h>

#define GAMES_TYPE_WINDOW         (games_window_get_type ())
#define GAMES_WINDOW(o)           (G_TYPE_CHECK_INSTANCE_CAST ((o), GAMES_TYPE_WINDOW, GamesWindow))
#define GAMES_WINDOW_CLASS(k)     (G_TYPE_CHECK_CLASS_CAST((k), GAMES_TYPE_WINDOW, GamesWindowClass))
#define GAMES_IS_WINDOW(o)        (G_TYPE_CHECK_INSTANCE_TYPE ((o), GAMES_TYPE_WINDOW))
#define GAMES_WINDOW_GET_CLASS(o) (G_TYPE_INSTANCE_GET_CLASS ((o), GAMES_TYPE_WINDOW, GamesWindowClass))

typedef struct _GamesWindow        GamesWindow;
typedef struct _GamesWindowClass   GamesWindowClass;
typedef struct _GamesWindowPrivate GamesWindowPrivate;

struct _GamesWindow {
    GtkWindow           parent_instance;
    GamesWindowPrivate *priv;
};

struct _GamesWindowClass {
    GtkWindowClass parent_class;
};

GType            games_window_get_type         (void) G_GNUC_CONST;

GtkWidget       *games_window_new              (void);


#endif
