#include QMK_KEYBOARD_H

#include "version.h"

// convert number to string
static const char *itoc(uint8_t number, uint8_t width) {
  static char str[5];
  uint8_t i = 0;

  do {
    str[i++] = (number % 10) + '0';
    number /= 10;
  } while (number != 0);

  while (i < width) {
    str[i++] = ' ';
  }

  int len = i;
  for (int j = 0; j < len / 2; j++) {
    char temp = str[j];
    str[j] = str[len - j - 1];
    str[len - j - 1] = temp;
  }
  str[len] = '\0';
  return str;
}

// CPI, DIV title
static const char PROGMEM img_title[] = {
    0x3e, 0x63, 0x41, 0x41, 0x22, 0x00, 0x7c, 0x14, 0x08, 0x00, 0x74,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x7f,
    0x49, 0x41, 0x22, 0x1c, 0x00, 0x74, 0x00, 0x38, 0x40, 0x38};

// CPI, scroll information
static void print_cpi_status(void) {
  oled_write_raw_P(img_title, sizeof(img_title));
  oled_set_cursor(0, 2);

  oled_write(itoc(keyball_get_cpi(), 0), false);
  oled_write_P(PSTR(" "), false);

  oled_set_cursor(4, 2);
  oled_write_char('0' + keyball_get_scroll_div(), false);
}

// Lock key status
static void print_lock_key_status(void) {
  oled_set_cursor(0, 6);

  const led_t led_state = host_keyboard_led_state();
  oled_write_P(led_state.caps_lock ? PSTR("C ") : PSTR("- "), false);
  oled_write_P(led_state.num_lock ? PSTR("N ") : PSTR("- "), false);
  oled_write_P(led_state.scroll_lock ? PSTR("S") : PSTR("-"), false);
}

// Default page
static void render_default(void) {
  print_cpi_status();
  print_lock_key_status();
}

// Version page
static void render_version(void) {
  oled_write_P(PSTR("Ver.\n\n"), false);
  oled_write_ln_P(PSTR(QMK_BUILDDATE), false);
  oled_write_P(PSTR("\n"), false);
  oled_write_ln_P(PSTR(QMK_KEYMAP), false);
  oled_write_P(PSTR("\n"), false);
  oled_write_ln_P(PSTR(QMK_VERSION), false);
}

// Custom OLED rendering function
void keyball_oled_render_custom(void) { render_default(); }
