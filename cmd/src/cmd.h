const char * cmdExit = "exit";
const char * cmdCurrDir = "pwd";
const char * cmdFHSDate = "fhsdate";
const char * cmdFHSTime = "fhstime";
const char * cmdHelp = "help";
const char * cmdChangeDir = "cd";

#define RET_PARSE_CMD_SYS -12
#define RET_PARSE_CMD_NOT_SET -5
#define RET_PARSE_CMD_ERROR -2
#define RET_PARSE_CMD_UNKNOWN -1
#define RET_PARSE_CMD_OK 0
#define RET_PARSE_CMD_EXIT 1

#define MAX_LENGTH 1024
#define DELIMS " \t\r\n"

struct tm * getTimeInfo(void)
{
    time_t rawtime;
    time ( &rawtime );
    return localtime ( &rawtime );
}

void showHelp(void);
int parseInput(char * input);
