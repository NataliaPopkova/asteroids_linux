
//
//  DO NOT MODIFY THIS FILE
//

#include "Engine.h"
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/keysym.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <errno.h>
#include <time.h>
#include <unistd.h>

uint32_t buffer[SCREEN_HEIGHT][SCREEN_WIDTH] = { 0 };

static bool keys[VK__COUNT] = { 0 };

static Display * display = NULL;
static Window window;
static Visual * visual = NULL;
static GC gc = 0;
static Pixmap pixmap = 0;
static XEvent event;
static int screen = 0;
static bool quit = false;
static Atom wmDeleteMessage = 0;
static XClassHint * classhint = NULL;
static XWMHints * wmhints = NULL;
static XSizeHints * sizehints = NULL;
static char title[] = "game";

static void term_sig_handler(int)
{
  quit = true;
}

bool is_key_pressed(int button_vk_code)
{
  if (unsigned(button_vk_code) >= VK__COUNT)
    return false;
  return keys[button_vk_code];
}

static void on_key_event(XKeyEvent & event, bool pressed)
{
  const int buf_size = 256;
  char buf[buf_size];
  KeySym ks;
  XLookupString(&event, buf, buf_size, &ks, NULL);

  switch (ks)
  {
    case XK_Left:
      keys[VK_LEFT] = pressed;
      break;
    case XK_Right:
      keys[VK_RIGHT] = pressed;
      break;
    case XK_Down:
      keys[VK_DOWN] = pressed;
      break;
    case XK_Up:
      keys[VK_UP] = pressed;
      break;
    case XK_Escape:
      keys[VK_ESCAPE] = pressed;
      break;
    case XK_space:
      keys[VK_SPACE] = pressed;
      break;
    case XK_Return:
      keys[VK_RETURN] = pressed;
      break;
  }
}

void schedule_quit_game()
{
  quit = true;
}

uint64_t get_nsec()
{
  timespec ts = { 0, 0 };
  clock_gettime(CLOCK_MONOTONIC, &ts);
  return uint64_t(ts.tv_sec) * 1000000000 + uint64_t(ts.tv_nsec);
}

int main(int, const char **)
{
  if ((display = XOpenDisplay(getenv("DISPLAY"))) == NULL)
  {
    fprintf(stderr, "Cannot connect X server: %s\n", strerror(errno));
    exit(1);
  }

  screen = XDefaultScreen(display);
  visual = DefaultVisual(display, screen);
  gc = DefaultGC(display, screen);
  window = XCreateWindow(display, DefaultRootWindow(display),
    10, 10, SCREEN_WIDTH, SCREEN_HEIGHT, 1, 24, InputOutput, CopyFromParent, 0, 0);

  classhint = XAllocClassHint();
  classhint->res_name = title;
  classhint->res_class = title;

  wmhints = XAllocWMHints();
  wmhints->input = true;
  wmhints->flags = InputHint;

  sizehints = XAllocSizeHints();
  sizehints->flags = PMaxSize | PMinSize;
  sizehints->min_width = sizehints->max_width = SCREEN_WIDTH;
  sizehints->min_height = sizehints->max_height = SCREEN_HEIGHT;
  XSetWMProperties(display, window, NULL, NULL, NULL, 0, sizehints, wmhints, classhint);

  pixmap = XCreatePixmap(display, window, SCREEN_WIDTH, SCREEN_HEIGHT, 24);

  XSelectInput(display, window, ExposureMask | KeyPressMask | KeyReleaseMask);
  XMapWindow(display, window);
  wmDeleteMessage = XInternAtom(display, "WM_DELETE_WINDOW", false);
  XSetWMProtocols(display, window, &wmDeleteMessage, 1);

  XFlush(display);

  initialize();

  uint64_t prevTime = get_nsec();

  XImage * image = XCreateImage(display, visual, 24, ZPixmap, 0, (char*)buffer, SCREEN_WIDTH, SCREEN_HEIGHT, 32, 0);

  signal(SIGINT, term_sig_handler);
  signal(SIGTERM, term_sig_handler);

  for (;;)
  {
    usleep(10000);

    while (XPending(display))
    {
      XNextEvent(display, &event);

      if (event.type == KeyPress)
        on_key_event(event.xkey, true);

      if (event.type == KeyRelease)
        on_key_event(event.xkey, false);

      if (event.type == ClientMessage && event.xclient.data.l[0] == (int)wmDeleteMessage)
        quit = true;
    }

    uint64_t curTime = get_nsec();
    if (curTime == prevTime)
      continue;

    float dt = float(double(curTime - prevTime) * 1e-9);
    act(dt);
    prevTime = curTime;

    if (quit)
      break;

    draw();
    XPutImage(display, pixmap, gc, image, 0, 0, 0, 0, image->width, image->height);
    XCopyArea(display, pixmap, window, gc, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, 0, 0);
    XFlush(display);
  }

  finalize();

  XFree(classhint);
  XFree(wmhints);
  XFree(sizehints);
  XFreePixmap(display, pixmap);
  XCloseDisplay(display);

  return 0;
}
