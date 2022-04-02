/*************************************************************************
  File Name: games-player.h
  
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
                                               
  Created Time: 2022年04月02日 星期五 11时42分17秒
 ************************************************************************/

#ifndef __GAMES_PLAYER__
#define __GAMES_PLAYER__

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif
#include <locale.h>
#include <glib/gi18n.h>

#include <gtk/gtk.h>

#define GAMES_TYPE_PLAYER         (games_player_get_type ())
#define GAMES_PLAYER(o)           (G_TYPE_CHECK_INSTANCE_CAST ((o), GAMES_TYPE_PLAYER, GamesPlayer))
#define GAMES_PLAYER_CLASS(k)     (G_TYPE_CHECK_CLASS_CAST((k), GAMES_TYPE_PLAYER, GamesPlayerClass))
#define GAMES_IS_PLAYER(o)        (G_TYPE_CHECK_INSTANCE_TYPE ((o), GAMES_TYPE_PLAYER))
#define GAMES_PLAYER_GET_CLASS(o) (G_TYPE_INSTANCE_GET_CLASS ((o), GAMES_TYPE_PLAYER, GamesPlayerClass))

typedef struct _GamesPlayer        GamesPlayer;
typedef struct _GamesPlayerClass   GamesPlayerClass;
typedef struct _GamesPlayerPrivate GamesPlayerPrivate;

struct _GamesPlayer {
    GtkBox           parent_instance;
    GamesPlayerPrivate *priv;
};

struct _GamesPlayerClass {
    GtkBoxClass parent_class;
};

GType            games_player_get_type         (void) G_GNUC_CONST;

GtkWidget       *games_player_new              (void);


#endif
