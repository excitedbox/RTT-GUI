/*
 * File      : title.h
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
 * 2009-10-16     Bernard      first version
 * 2019-05-15     onelife      refactor
 */

#ifndef __RTGUI_TITLE__
#define __RTGUI_TITLE__

/* Includes ------------------------------------------------------------------*/
#include "./widget.h"

/* Exported defines ----------------------------------------------------------*/
RTGUI_CLASS_PROTOTYPE(win_title);
/** Gets the type of a title */
#define _WIN_TITLE_METADATA                 CLASS_METADATA(win_title)
/** Casts the object to an rtgui_win_title */
#define TO_WIN_TITLE(obj)                   \
    RTGUI_CAST(obj, _WIN_TITLE_METADATA, rtgui_win_title_t)
/** Checks if the object is an rtgui_win_title */
#define IS_WIN_TITLE(obj)                   \
    IS_INSTANCE((obj), _WIN_TITLE_METADATA)

/* Exported types ------------------------------------------------------------*/
typedef struct rtgui_win_title {
    struct rtgui_widget _super;
} rtgui_win_title_t;

/* Exported constants --------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */
rtgui_win_title_t *rtgui_win_title_create(rtgui_win_t *win, rtgui_evt_hdl_t evt_hdl);
void rtgui_win_title_destroy(rtgui_win_title_t *win_t);

#endif /* __RTGUI_TITLE__ */
