/*
 * File      : rtgui_server.h
 * This file is part of RT-Thread GUI Engine
 * COPYRIGHT (C) 2006 - 2017, RT-Thread Development Team
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License along
 *  with this program; if not, write to the Free Software Foundation, Inc.,
 *  51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 *
 * Change Logs:
 * Date           Author       Notes
 * 2009-10-04     Bernard      first version
 */
#ifndef __RTGUI_SERVER_H__
#define __RTGUI_SERVER_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "include/rtservice.h"
#include "./list.h"

/* RTGUI server definitions */

/* top window definitions in server */
enum rtgui_topwin_flag
{
    WINTITLE_INIT       =  0x00,
    WINTITLE_ACTIVATE   =  0x01,
    WINTITLE_NOFOCUS    =  0x02,
    /* window is hidden by default */
    WINTITLE_SHOWN      =  0x04,
    /* window is modaled by other window */
    WINTITLE_MODALED    =  0x08,
    /* window is modaling other window */
    WINTITLE_MODALING   = 0x100,
    WINTITLE_ONTOP      = 0x200,
    WINTITLE_ONBTM      = 0x400,
};

struct rtgui_topwin
{
    /* the window flag */
    enum rtgui_topwin_flag flag;
    /* event mask */
    rt_uint32_t mask;

    struct rtgui_win_title *title;

    /* the window id */
    struct rtgui_win *wid;

    /* which app I belong */
    struct rtgui_app *app;

    /* the extent information */
    rtgui_rect_t extent;

    struct rtgui_topwin *parent;

    /* we need to iterate the topwin list with usual order(get target window)
     * or reversely(painting). So it's better to use a double linked list */
    rt_list_t list;
    rt_list_t child_list;

    /* the monitor rect list */
    rtgui_list_t monitor_list;
};

/* top win manager init */
void rtgui_topwin_init(void);
void rtgui_server_init(void);

void rtgui_server_install_show_win_hook(void (*hk)(void));
void rtgui_server_install_act_win_hook(void (*hk)(void));

/* post an event to server */
rt_err_t rtgui_server_post_event(rtgui_evt_generic_t *evt);
rt_err_t rtgui_server_post_event_sync(rtgui_evt_generic_t *evt);

#ifdef __cplusplus
}
#endif

#endif /* __RTGUI_SERVER_H__ */
