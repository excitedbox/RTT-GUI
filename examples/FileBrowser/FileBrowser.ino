/***************************************************************************//**
 * @file    FileBrowser.ino
 * @brief   RTT-GUI library "FileBrowser" example
 * @author  onelife <onelife.real[at]gmail.com>
 ******************************************************************************/
#include <rtt.h>
#include <rttgui.h>

#define LOG_LVL LOG_LVL_INFO
#define LOG_TAG "APP_FB "
#include <log.h>

#define PATH_SEPARATOR                  '/'
#define MAX_PATH_LENGTH                 (128)

static const char bmp[] = "bmp";
static const char jpeg[] = "jpeg";
static const char* format = RT_NULL;

static rtgui_app_t *fileBrs;
static rtgui_win_t *mainWin;
static rtgui_win_t *fileWin;
static char path[MAX_PATH_LENGTH];


static rt_bool_t fileBrowser_on_close(void *obj, rtgui_evt_generic_t *evt) {
  (void)obj;
  (void)evt;
  (void)rtgui_win_show(mainWin, RT_FALSE);

  return RT_TRUE;
}

static rt_bool_t fileWin_handler(void *obj, rtgui_evt_generic_t *evt) {
  rtgui_dc_t *dc;
  rtgui_rect_t rect;
  rtgui_image_t *img;
  rt_bool_t done = RT_FALSE;

  do {
    if (DEFAULT_HANDLER(obj))
      done = DEFAULT_HANDLER(obj)(obj, evt);

    if (!IS_EVENT_TYPE(evt, PAINT)) break;
    done = RT_FALSE;
    LOG_I("Loading %s: %s", format, path);

    dc = rtgui_dc_begin_drawing(TO_WIDGET(obj));
    if (!dc) {
      LOG_E("No DC!");
      break;
    }

    rtgui_dc_get_rect(dc, &rect);

    img = rtgui_image_create_from_file(format, path, RT_FALSE);
    if (img) {
        rtgui_image_blit(img, dc, &rect);
        rtgui_image_destroy(img);
    } else {
      LOG_E("Load %s filed!", path);
    }

    rtgui_dc_end_drawing(dc, RT_TRUE);
    done = RT_TRUE;
  } while (0);

  return done;
}

static rt_bool_t fileBrowser_on_file(void *obj, rtgui_evt_generic_t *evt) {
  rt_bool_t done = RT_FALSE;
  (void)evt;

  do {
    rtgui_filelist_t *filelist = (rtgui_filelist_t *)obj;
    rtgui_list_item_t *item = &SUPER_(filelist).items[SUPER_(filelist).current];
    char *ptr;
    rt_uint8_t len, len2;

    format = RT_NULL;
    if ((ptr = rt_strstr(item->name, ".bmp")) || \
      (ptr = rt_strstr(item->name, ".BMP")))
      format = bmp;
    else if ((ptr = rt_strstr(item->name, ".jpg")) || \
      (ptr = rt_strstr(item->name, ".JPG")))
      format = jpeg;

    if (!format) break;

    len = rt_strlen(filelist->cur_dir);
    len2 = ptr - item->name + 4;
    rt_strncpy(path, filelist->cur_dir, len);
    if (path[len - 1] != PATH_SEPARATOR)
      path[len++] = PATH_SEPARATOR;
    rt_strncpy(path + len, item->name, len2);
    path[len + len2] = '\x00';

    rtgui_win_show(fileWin, RT_TRUE);
    done = RT_TRUE;
  } while (0);

  return done;
}

static void fileBrowser_entry(void *param) {
  rtgui_rect_t rect;
  rtgui_filelist_t *filelist;
  (void)param;

  /* create app */
  CREATE_APP_INSTANCE(fileBrs, RT_NULL, "FileBrowser");
  if (!fileBrs) {
    LOG_E("Create app failed!");
    return;
  }

  /* create win */
  mainWin = CREATE_MAIN_WIN(RT_NULL, "FileBrowser",
    RTGUI_WIN_STYLE_MAINWIN);
  if (!mainWin) {
    rtgui_app_uninit(fileBrs);
    LOG_E("Create mainWin failed!");
    return;
  }

  rtgui_get_screen_rect(&rect);

  /* filelist */
  filelist = CREATE_FILELIST_INSTANCE(mainWin, fileBrowser_on_file, &rect, "/");
  if (!filelist) {
      LOG_E("Create filelist failed!");
      return;
  }

  /* fileWin */
  fileWin = CREATE_WIN_INSTANCE(RT_NULL, fileWin_handler, &rect, "PicWin",
    RTGUI_WIN_STYLE_DEFAULT);
  if (!fileWin) {
      LOG_E("Create fileWin failed!");
      return;
  }
  WIN_SETTER(on_close)(fileWin, fileBrowser_on_close);  

  rtgui_win_show(mainWin, RT_FALSE);
  rtgui_app_run(fileBrs);

  DELETE_WIN_INSTANCE(fileWin);
  DELETE_WIN_INSTANCE(mainWin);
  rtgui_app_uninit(fileBrs);
}

// RT-Thread function called by "RT_T.begin()"
void rt_setup(void) {
  rt_thread_t tid = rt_thread_create(
    "FileBrowser", fileBrowser_entry, RT_NULL, 2048, 25, 10);
  if (tid) {
    rt_thread_startup(tid);
  } else {
    LOG_E("Create thread failed!");
  }
}

void setup() {
  RT_T.begin();
  // no code here as RT_T.begin() never return
}

// this function will be called by "Arduino" thread
void loop() {
  // may put some code here that will be run repeatedly
}
