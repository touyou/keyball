#include QMK_KEYBOARD_H

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

// CPI, scroll information
static void print_cpi_status(void) {
  oled_write(itoc(keyball_get_cpi(), 0), false);
  oled_write_P(PSTR(" "), false);

  oled_set_cursor(4, 2);
  oled_write_char('0' + keyball_get_scroll_div(), false);
}

// Default page
static void render_default(void) { print_cpi_status(); }

// Custom OLED rendering function
void keyball_oled_render_custom(void) { render_default(); }
