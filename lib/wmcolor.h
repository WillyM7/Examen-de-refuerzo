//===Color font ===/
#define COLOR_BLACK   "\x1B[30m"
#define COLOR_RED     "\x1b[31m"
#define COLOR_GREEN   "\x1b[32m"
#define COLOR_YELLOW  "\x1b[33m"
#define COLOR_BLUE    "\x1b[34m"
#define COLOR_MAGENTA "\x1b[35m"
#define COLOR_CYAN    "\x1b[36m"
#define COLOR_WHITE   "\x1B[37m"
#define COLOR_ORANGE  "\x1B[38;2;255;128;0m"
#define COLOR_ROSE    "\x1B[38;2;255;151;203m"
#define COLOR_LBLUE   "\x1B[38;2;53;149;240m"
#define COLOR_LGREEN  "\x1B[38;2;17;245;120m"
#define COLOR_GRAY    "\x1B[38;2;176;174;174m"
#define COLOR_RESET   "\x1b[0m"

//===Color background ===/
#define BG_BLACK   "\x1B[40m"
#define BG_RED     "\x1B[41m"
#define BG_GREEN   "\x1B[42m"
#define BG_YELLOW  "\x1B[43m"
#define BG_BLUE    "\x1B[44m"
#define BG_MAGENTA "\x1B[45m"
#define BG_CYAN    "\x1B[46m"
#define BG_WHITE   "\x1B[47m"
#define BG_ORANGE  "\x1B[48;2;255;128;0m"
#define BG_LBLUE   "\x1B[48;2;53;149;240m"
#define BG_LGREEN  "\x1B[48;2;17;245;120m"
#define BG_GRAY    "\x1B[48;2;176;174;174m"
#define BG_ROSE    "\x1B[48;2;255;151;203m"

//Colores de texto
#define textColorBlack 30
#define textColorRed 31
#define textColorGreen 32
#define textColorYellow 33
#define textColorBlue 34
#define textColorMagenta 35
#define textColorCyan 36
#define textColorWhite 37
//colores de fondo
#define fnBgBlack 40
#define fnBgRed 41
#define fnBgGreen 42
#define fnBgYellow 43
#define fnBgBlue 44
#define fnBgMagenta 45
#define fnBgCyan 46
#define fnBgWhite 47


void setColor(int color, int BG_color){
        //El primer valor es del color de texto y el segundo del color del fondo
        printf("%c[%d;%d;%dm", 0x1B, 1,color,BG_color);
}
void setTextColor(int color){
        printf("%c[%d;%dm", 0x1B, 1,color);
}