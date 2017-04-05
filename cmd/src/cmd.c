/*
 ============================================================================
 Name        : FHSS.c
 Author      : Michael Bieringer
 Version     : 1.0
 Copyright   : Nothing - except free
 Description : FHS Shell, Professional Programmer, Operation Systems
 ============================================================================
 */
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>
#include <errno.h>
#include <unistd.h>
#include "cmd.h"

int main(int argc, char *argv[], char * envp[])
{
    puts("Hello to the custom FHS Command Ghost in the Shell");
    puts("Created by Michael Bieringer 2017");
    puts("Professional Programmer");
    puts("Version 1.0");

    char line[MAX_LENGTH];

    while(true)
    {
        printf("fhss:>");
        if (!fgets(line, MAX_LENGTH, stdin)) break;

        int cmdRetVal = parseInput(line);
        if (RET_PARSE_CMD_EXIT == cmdRetVal)
        {
            break;
        }
    }

    return EXIT_SUCCESS;
}

void showHelp(void)
{
    puts("Verfuegbare Kommandos:");
    printf("\t%s      \tGibt die aktuelle Uhrzeit aus\n", cmdFHSTime);
    printf("\t%s      \tGibt das aktuelle Datum aus\n", cmdFHSDate);
    printf("\t%s      \tBeendet die aktuelle Sitzung\n", cmdExit);
    printf("\t%s      \tGibt diese Hilfe aus\n", cmdHelp);
    printf("\t%s [Dir]\tAendert das aktuelle Verzeichnis\n", cmdChangeDir);
    printf("\t%s      \tGibt das aktuelle Verzeichnis aus\n", cmdCurrDir);
}

int parseInput(char * input)
{
    // Parse and execute command
    char * cmd;
    if ((cmd = strtok(input, DELIMS)))
    {
        if (strcmp(cmd, cmdExit) == 0)
        {
            return RET_PARSE_CMD_EXIT;
        } else if (strcmp(cmd, cmdHelp) == 0)
        {
            showHelp();
            return RET_PARSE_CMD_OK;
        } else if (strcmp(cmd, cmdFHSDate) == 0)
        {
            struct tm * timeinfo = getTimeInfo();
            printf ( "Das aktuelle Datum ist: %02d.%02d.%d\n", timeinfo->tm_mday, timeinfo->tm_mon, (timeinfo->tm_year)+1900 );
            return RET_PARSE_CMD_OK;
        } else if (strcmp(cmd, cmdFHSTime) == 0)
        {
            struct tm * timeinfo = getTimeInfo();
            printf ( "Die aktuelle Uhrzeit ist: %02d:%02d:%02d\n", timeinfo->tm_hour, timeinfo->tm_min, timeinfo->tm_sec );
            return RET_PARSE_CMD_OK;
        } else if (strcmp(cmd, cmdChangeDir) == 0)
        {
            char * arg = strtok(0, DELIMS);
            if (!arg)
            {
                printf("Fehler: das Verzeichnis wurde nicht angegeben\n");
                return RET_PARSE_CMD_ERROR;
            }
            chdir(arg);
            return RET_PARSE_CMD_OK;
        } else if (strcmp(cmd, cmdCurrDir) == 0)
	{
            char cwd[1024];
            getcwd(cwd, sizeof(cwd));
            printf("%s\n", cwd);
            return RET_PARSE_CMD_OK;
	} else
        {
            //system(cmd);
            //return RET_PARSE_CMD_SYS;
            printf("Fehler: Die Eingabe %s ist unbekannt!\n", input);
            return RET_PARSE_CMD_UNKNOWN;
        }
    } else
    {
    	return RET_PARSE_CMD_NOT_SET;
    }
}


