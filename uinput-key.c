#include "uinput-key.h"

#include <linux/input.h>
#include <linux/uinput.h>

static const int printable_map[] = {
    [0x20] = KEY_SPACE,
    [0x21] = KEY_1 | SHIFT,
    [0x22] = KEY_APOSTROPHE | SHIFT,
    [0x23] = KEY_3 | SHIFT,
    [0x24] = KEY_4 | SHIFT,
    [0x25] = KEY_5 | SHIFT,
    [0x26] = KEY_7 | SHIFT,
    [0x27] = KEY_APOSTROPHE,
    [0x28] = KEY_9 | SHIFT,
    [0x29] = KEY_0 | SHIFT,
    [0x2a] = KEY_8 | SHIFT,
    [0x2b] = KEY_EQUAL | SHIFT,
    [0x2c] = KEY_COMMA,
    [0x2d] = KEY_MINUS,
    [0x2e] = KEY_DOT,
    [0x2f] = KEY_SLASH,
    [0x30] = KEY_0,
    [0x31] = KEY_1,
    [0x32] = KEY_2,
    [0x33] = KEY_3,
    [0x34] = KEY_4,
    [0x35] = KEY_5,
    [0x36] = KEY_6,
    [0x37] = KEY_7,
    [0x38] = KEY_8,
    [0x39] = KEY_9,
    [0x3a] = KEY_SEMICOLON | SHIFT,
    [0x3b] = KEY_SEMICOLON,
    [0x3c] = KEY_COMMA | SHIFT,
    [0x3d] = KEY_EQUAL,
    [0x3e] = KEY_DOT | SHIFT,
    [0x3f] = KEY_SLASH | SHIFT,
    [0x40] = KEY_2 | SHIFT,
    [0x41] = KEY_A | SHIFT,
    [0x42] = KEY_B | SHIFT,
    [0x43] = KEY_C | SHIFT,
    [0x44] = KEY_D | SHIFT,
    [0x45] = KEY_E | SHIFT,
    [0x46] = KEY_F | SHIFT,
    [0x47] = KEY_G | SHIFT,
    [0x48] = KEY_H | SHIFT,
    [0x49] = KEY_I | SHIFT,
    [0x4a] = KEY_J | SHIFT,
    [0x4b] = KEY_K | SHIFT,
    [0x4c] = KEY_L | SHIFT,
    [0x4d] = KEY_M | SHIFT,
    [0x4e] = KEY_N | SHIFT,
    [0x4f] = KEY_O | SHIFT,
    [0x50] = KEY_P | SHIFT,
    [0x51] = KEY_Q | SHIFT,
    [0x52] = KEY_R | SHIFT,
    [0x53] = KEY_S | SHIFT,
    [0x54] = KEY_T | SHIFT,
    [0x55] = KEY_U | SHIFT,
    [0x56] = KEY_V | SHIFT,
    [0x57] = KEY_W | SHIFT,
    [0x58] = KEY_X | SHIFT,
    [0x59] = KEY_Y | SHIFT,
    [0x5a] = KEY_Z | SHIFT,
    [0x5b] = KEY_LEFTBRACE,
    [0x5c] = KEY_BACKSLASH,
    [0x5d] = KEY_RIGHTBRACE,
    [0x5e] = KEY_6 | SHIFT,
    [0x5f] = KEY_MINUS | SHIFT,
    [0x60] = KEY_GRAVE,
    [0x61] = KEY_A,
    [0x62] = KEY_B,
    [0x63] = KEY_C,
    [0x64] = KEY_D,
    [0x65] = KEY_E,
    [0x66] = KEY_F,
    [0x67] = KEY_G,
    [0x68] = KEY_H,
    [0x69] = KEY_I,
    [0x6a] = KEY_J,
    [0x6b] = KEY_K,
    [0x6c] = KEY_L,
    [0x6d] = KEY_M,
    [0x6e] = KEY_N,
    [0x6f] = KEY_O,
    [0x70] = KEY_P,
    [0x71] = KEY_Q,
    [0x72] = KEY_R,
    [0x73] = KEY_S,
    [0x74] = KEY_T,
    [0x75] = KEY_U,
    [0x76] = KEY_V,
    [0x77] = KEY_W,
    [0x78] = KEY_X,
    [0x79] = KEY_Y,
    [0x7a] = KEY_Z,
    [0x7b] = KEY_LEFTBRACE | SHIFT,
    [0x7c] = KEY_BACKSLASH | SHIFT,
    [0x7d] = KEY_RIGHTBRACE | SHIFT,
    [0x7e] = KEY_GRAVE | SHIFT,
};

int printable_to_key(int c)
{
    if (c == '\t')
        return KEY_TAB;
    else if (c == '\n')
        return KEY_ENTER;
    else if (c >= ' ' && c <= '~')
        return printable_map[c];

    return 0;
}

