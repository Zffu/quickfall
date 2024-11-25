/**
 * Quickfall Logging Utilities.
 */

#define RESET "\x1b[0m"

#define PREFIX "\x1b["

#define CLASSIC_OP PREFIX "0;"
#define BOLD_OP PREFIX "1;"

#define RED "31m"
#define BLACK "30m"
#define GREEN "32m"
#define YELLOW "33m"
#define BLUE "34m"
#define MAGENTA "35m"
#define CYAN "36m"
#define WHITE "37m"
#define GRAY "90m"

#define HBLACK "90m"
#define HRED "91m"
#define HGREEN "92m"
#define HYELLOW "93m"
#define HBLUE "94m"
#define HMAGENTA "95m"
#define HCYAN "96m"
#define HWHITE "97m"
#define HGRAY "98m"

#define BG_BLACK "40m"
#define BG_RED "41m"
#define BG_GREEN "42m"
#define BG_YELLOW "43m"
#define BG_BLUE "44m"
#define BG_MAGENTA "45m"
#define BG_CYAN "46m"
#define BG_WHITE "47m"
#define BG_GRAY "48m"

#define BG_HBLACK "100m"
#define BG_HRED "101m"
#define BG_HGRREEN "102m"
#define BG_HYELLOW "103m"
#define BG_HBLUE "104m"
#define BG_HPURPLE "105m"
#define BG_HCYAN "106m"
#define BG_HWHITE "107m"
#define BH_HGRAY "108m"

#define TEXT_RED CLASSIC_OP RED
#define TEXT_BLACK CLASSIC_OP BLACK
#define TEXT_GREEN CLASSIC_OP GREEN
#define TEXT_YELLOW CLASSIC_OP YELLOW
#define TEXT_BLUE CLASSIC_OP BLUE
#define TEXT_MAGENTA CLASSIC_OP MAGENTA
#define TEXT_CYAN CLASSIC_OP CYAN
#define TEXT_WHITE CLASSIC_OP WHITE
#define TEXT_GRAY CLASSIC_OP GRAY

#define BACKGROUND_RED CLASSIC_OP BG_RED
#define BACKGROUND_BLACK CLASSIC_OP BG_BLACK
#define BACKGROUND_GREEN CLASSIC_OP BG_GREEN
#define BACKGROUND_YELLOW CLASSIC_OP BG_YELLOW
#define BACKGROUND_BLUE CLASSIC_OP BG_BLUE
#define BACKGROUND_MAGENTA CLASSIC_OP BG_MAGENTA
#define BACKGROUND_CYAN CLASSIC_OP BG_CYAN
#define BACKGROUND_WHITE CLASSIC_OP BG_WHITE
#define BACKGROUND_GRAY CLASSIC_OP BG_GRAY
