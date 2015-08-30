#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <stdarg.h>
#include <fcntl.h>
#include <unistd.h>
#include <err.h>
#include <sys/ioctl.h>
#include <linux/input.h>
#include <linux/uinput.h>

#define KEYMASK 0xfff
#define SHIFT 0x10000

#include "config.h"

static void check_posix(intmax_t rc, const char *fmt, ...)
{
    if (rc < 0) {
        va_list args;
        va_start(args, fmt);
        verr(EXIT_FAILURE, fmt, args);
        va_end(args);
    }
}

static int ev_emit(int fd, int type, int code, int value)
{
    struct input_event ev = {
        .type = type,
        .code = code,
        .value = value
    };

    gettimeofday(&ev.time, 0);
    return write(fd, &ev, sizeof(ev));
}

static int ev_syn(int fd)
{
    return ev_emit(fd, EV_SYN, SYN_REPORT, 0);
}

static int ev_key(int fd, int key, int value)
{
    int ret;

    if (value && (SHIFT & key)) {
        if (ev_key(fd, KEY_LEFTSHIFT, 1) < 0)
            return -1;
    }

    ret = ev_emit(fd, EV_KEY, key & KEYMASK, value);
    if (ev_syn(fd) < 0)
        return -1;

    if (!value && (SHIFT & key)) {
        if (ev_key(fd, KEY_LEFTSHIFT, 0) < 0)
            return -1;
    }

    return ret;
}

static int ev_key_click(int fd, int key)
{
    if (ev_key(fd, key, 1) < 0)
        return -1;
    return ev_key(fd, key, 0);
}

int main(void)
{
    int fd = open("/dev/uinput", O_WRONLY | O_NONBLOCK);
    check_posix(fd, "failed to open uinput");

    check_posix(ioctl(fd, UI_SET_EVBIT, EV_KEY), "failed to set EV_KEY");
    check_posix(ioctl(fd, UI_SET_KEYBIT, KEY_LEFTSHIFT), "failed to set UI_SET_KEYBIT");

    for (const int *key = programmed_input; *key != 0; key++) {
        check_posix(ioctl(fd, UI_SET_KEYBIT, *key & KEYMASK),
                    "failed to set UI_SET_KEYBIT");
    }

    struct uinput_user_dev uidev = {
        .id.bustype = BUS_VIRTUAL,
        .id.vendor = 0x1,
        .id.product = 0x1,
        .id.version = 1
    };

    snprintf(uidev.name, UINPUT_MAX_NAME_SIZE, "Virtual Injector Keyboard");
    check_posix(write(fd, &uidev, sizeof(uidev)),
                "failed to write uinput_user_dev struct");
    check_posix(ioctl(fd, UI_DEV_CREATE),
                "failed to create uinput device");

    for (const int *key = programmed_input; *key != 0; key++) {
        ev_key_click(fd, *key);
        if (*key == KEY_ENTER)
            sleep(1);
    }

    ioctl(fd, UI_DEV_DESTROY);
    close(fd);
}
