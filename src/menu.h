/*
	This program is free software; you can redistribute it and/or modify
	it under the terms of the GNU General Public License as published by
	the Free Software Foundation; You may only use version 2 of the License,
	you have no option to use any other version.
 
	This program is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU General Public License for more details.
 
	You should have received a copy of the GNU General Public License
	along with this program; if not, write to the Free Software
	Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 
	Metacity - (c) 2001 Havoc Pennington
	xfwm4    - (c) 2002-2003 Olivier Fourdan
 
 */

#ifndef INC_MENU_H
#define INC_MENU_H

#ifdef HAVE_CONFIG_H
#  include "config.h"
#endif

#include <gtk/gtk.h>
#include <gdk/gdk.h>
#include <X11/Xlib.h>

typedef enum
{
    MENU_OP_SEPARATOR    = 0,
    MENU_OP_MAXIMIZE     = 1 << 0,
    MENU_OP_UNMAXIMIZE   = 1 << 1,
    MENU_OP_MINIMIZE     = 1 << 2,
    MENU_OP_MINIMIZE_ALL = 1 << 3,
    MENU_OP_UNMINIMIZE   = 1 << 4,
    MENU_OP_SHADE        = 1 << 5,
    MENU_OP_UNSHADE      = 1 << 6,
    MENU_OP_STICK        = 1 << 7,
    MENU_OP_UNSTICK      = 1 << 8,
    MENU_OP_DELETE       = 1 << 9,
    MENU_OP_DESTROY      = 1 << 10,
    MENU_OP_WORKSPACES   = 1 << 11,
    MENU_OP_QUIT         = 1 << 12,
    MENU_OP_RESTART      = 1 << 13,
    MENU_OP_ABOVE        = 1 << 14,
    MENU_OP_NORMAL       = 1 << 15,
    MENU_OP_CONTEXT_HELP = 1 << 16,
    MENU_OP_OTHER        = 1 << 17
}
MenuOp;

typedef struct _Menu Menu;
typedef struct _MenuItem MenuItem;
typedef struct _MenuData MenuData;

typedef void (*MenuFunc) (Menu * menu, MenuOp op, Window client_xwindow,
			  gpointer menu_data, gpointer item_data);

struct _MenuItem
{
    MenuOp op;
    const char *image_name;
    const char *label;
};

struct _MenuData
{
    Menu *menu;
    MenuOp op;
    Window client_xwindow;
    gpointer data;
};

struct _Menu
{
    GtkWidget *menu;
    MenuFunc func;
    gpointer data;
    MenuOp ops;
    MenuOp insensitive;
};

Menu *menu_default (MenuOp ops, MenuOp insensitive, MenuFunc func,
		    gint ws, gint nws, gchar *wsn, gint wsnl, gpointer data);
Menu *menu_connect (Menu * menu);
GtkWidget *menu_item_connect (GtkWidget * item, MenuData * item_data);
gboolean menu_is_opened (void);
gboolean menu_check_and_close (void);
gboolean menu_popup (Menu * menu, int root_x, int root_y, int button,
		     guint32 timestamp);
void menu_free (Menu * menu);

#endif /* INC_MENU_H */
