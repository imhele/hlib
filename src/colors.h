#ifndef __HLIB_COLORS
#define __HLIB_COLORS
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>

#define ColorDefault "0"
#define ColorBlack "30"
#define ColorRed "31"
#define ColorGreen "32"
#define ColorBrown "33"
#define ColorBlue "34"
#define ColorPurple "35"
#define ColorCyan "36"
#define ColorWhite "37"

#define BGColorDefault "0"
#define BGColorBlack "40"
#define BGColorRed "41"
#define BGColorGreen "42"
#define BGColorBrown "43"
#define BGColorBlue "44"
#define BGColorPurple "45"
#define BGColorCyan "46"
#define BGColorWhite "47"

/** alias **/
#ifndef __HLIB_COLOR_NO_ALIAS
#define CDf ColorDefault
#define CBl ColorBlack
#define CRe ColorRed
#define CGr ColorGreen
#define CBr ColorBrown
#define CBe ColorBlue
#define CPu ColorPurple
#define CCy ColorCyan
#define CWh ColorWhite

#define BCDe BGColorDefault
#define BCBl BGColorBlack
#define BCRe BGColorRed
#define BCGr BGColorGreen
#define BCBr BGColorBrown
#define BCBe BGColorBlue
#define BCPu BGColorPurple
#define BCCy BGColorCyan
#define BCWh BGColorWhite
#endif /* __HLIB_COLOR_ALIAS */

#define coloredStr(str, bg, text) "\033[" text ";" bg "m" str "\033[0m"

typedef enum ConsoleType
{
  ConsoleError,
  ConsoleWarn,
  ConsoleInfo,
  ConsoleLog,
  ConsolePass,
  ConsoleTest,
  ConsoleStart,
} ConsoleType;

void console(ConsoleType type, ...)
{
  switch (type)
  {
  case ConsoleError:
    printf(coloredStr(" ERROR ", BGColorRed, ColorBlack) "  ");
    break;
  case ConsoleWarn:
    printf(coloredStr(" WARN ", BGColorBrown, ColorBlack) "   ");
    break;
  case ConsoleInfo:
    printf(coloredStr(" INFO ", BGColorCyan, ColorBlack) "   ");
    break;
  case ConsoleLog:
    printf(coloredStr("  LOG  ", BGColorWhite, ColorBlack) "  ");
    break;
  case ConsolePass:
    printf(coloredStr(" PASS ", BGColorGreen, ColorBlack) "   ");
    break;
  case ConsoleTest:
    printf(coloredStr(" Test ", BGColorBlue, ColorBlack) "   ");
    break;
  case ConsoleStart:
    printf(coloredStr(" START ", BGColorGreen, ColorBlack) "  ");
    break;
  default:
    break;
  }
  char *extra;
  va_list sArgv;
  va_start(sArgv, type);
  while ((extra = va_arg(sArgv, char *)))
    printf("%s", extra);
  printf("\n");
  va_end(sArgv);
}

#endif /* __HLIB_COLORS */
