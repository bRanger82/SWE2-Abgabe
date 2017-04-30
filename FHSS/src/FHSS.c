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
#include <sys/stat.h>
#include "cmd.h"
#include "Stack.h" //push/pop-directory
#include <dirent.h>



int main(int argc, char *argv[], char * envp[])
{
    // Information ueber die Shell bei Programmstart ausgeben
    puts("Hello to the custom FHS Command Ghost in the Shell");
    puts("Created by Michael Bieringer 2017");
    puts("Professional Programmer");
    puts("Version 1.0");

    // Puffer fuer die Eingabe
    char line[MAX_LENGTH];

    // Verarbeitung der Shell, solange die Exit-Anweisung nicht zutrifft (break)
    while(true)
    {
        printf("%sfhss:>", NORMAL_COLOR);
        if (!fgets(line, MAX_LENGTH, stdin)) break;

        int cmdRetVal = parseInput(line);
        if (RET_PARSE_CMD_EXIT == cmdRetVal)
        {
            break;
        }
    }

    Sdelete(); // Wenn etwas im Stack abgelegt wurde => Stack bereinigen

    return EXIT_SUCCESS;
}

// Gibt einen Hilfe-Text auf stdout aus
void showHelp(void)
{
    puts("Verfuegbare Kommandos:");
    printf("\t%s       \tGibt die aktuelle Uhrzeit aus\n", cmdFHSTime);
    printf("\t%s       \tGibt das aktuelle Datum aus\n", cmdFHSDate);
    printf("\t%s       \tBeendet die aktuelle Sitzung\n", cmdExit);
    printf("\t%s       \tGibt diese Hilfe aus\n", cmdHelp);
    printf("\t%s [Dir] \tAendert das aktuelle Verzeichnis\n", cmdChangeDir);
    printf("\t%s       \tGibt das aktuelle Verzeichnis aus\n", cmdCurrDir);
    printf("\t%s [Text]\tGibt den angegeben Text auf stdout aus\n", cmdEcho);
    printf("\t%s [DIR] \tLegt das Verzeichnis in den Speicher\n", cmdPushDir);
    printf("\t         \tWenn kein Parameter angegeben wird, wird das aktuelle Verzeichnis verwendet.\n");
    printf("\t%s       \tRuft das Vezeichnis aus dem Speicher ab und wechselt in diesen.\n", cmdPopDir);
    printf("\t%s [DIR] \tListet das Verzeichnis auf\n", cmdListDir);
    printf("\t         \tWenn kein Parameter angegeben wird, wird das aktuelle Verzeichnis verwendet.\n");
}

int show_dir_content(char * path, bool paramAgiven)
{
	DIR * d = opendir(path); // open the path
	if(NULL == d)
		return RET_PARSE_CMD_ERROR; // if was not able return

	struct dirent * dir; // for the directory entries

	while ((dir = readdir(d)) != NULL) // if we were able to read somehting from the directory
	{
		if(dir-> d_type != DT_DIR) // if the type is not directory just print it with blue
			printf("%s%s\n",BLUE, dir->d_name);
		else
			if(dir -> d_type == DT_DIR && strcmp(dir->d_name,".")!=0 && strcmp(dir->d_name,"..")!=0 ) // if it is a directory
			{
				printf("%s%s\n",GREEN, dir->d_name); // print its name in green
			} else if (strcmp(dir->d_name,".") == 0 && paramAgiven)
			{
				printf("%s%s\n",GREEN, ".");
			} else if (strcmp(dir->d_name,"..") == 0 && paramAgiven)
			{
				printf("%s%s\n",GREEN, "..");
			}
	}
	closedir(d); // finally close the directory
	return RET_PARSE_CMD_OK;
}

int changeDir(char * newDir, bool popDirOnly)
{
	struct stat info;

	if(lstat(newDir, &info) != 0) //Pruefung ob Verzeichnis existiert/kann zugegriffen werden
	{
		if(errno == ENOENT)
		{
			printf("Fehler: das Verzeichnis '%s' existiert nicht!\n", newDir);
		} else if(errno == EACCES)
		{
			printf("Fehler: auf das Verzeichnis '%s' kann nicht zugegriffen werden!\n", newDir);
		} else
		{
			printf("Fehler: auf das Verzeichnis '%s' kann nicht gewechselt werden!\n", newDir);
		}
		return RET_PARSE_CMD_ERROR;
	}


	if(S_ISDIR(info.st_mode))
	{
		if (popDirOnly)
		{
			push(newDir);
			printf("Verzeichnis %s gespeichert\n", newDir);
		} else
		{
			chdir(newDir);
			printf("Verzeichnis geaendert auf: %s\n", newDir);
		}

		return RET_PARSE_CMD_OK;
	} else if(S_ISFIFO(info.st_mode))
	{
		//Es ist eine Datei
		printf("Fehler: kein Verzeichnis!\n");
		return RET_PARSE_CMD_ERROR;
	}

	printf("Fehler beim Wechseln in das Verzeichnis!\n");
	return RET_PARSE_CMD_ERROR;
}

/*
    Verarbeiten der Benutzer-Eingabe
    Parameter:
    	- input: Eingabezeile
    Rueckgabewert:
    	- (int) --> siehe RET_PARSE_CMD_*
*/
int parseInput(char * input)
{
    // Befehlsargument
    char * cmd;

    // Es soll der erste Wert aus der Eingabezeile bis zum Trennzeichen gelesen werden
    // Bsp: zeigeEtwasAn [Wert von DELIMS] Parameter1 [Wert von DELIMS] Parameter2
    //      ^--> cmd                       ^
    //                                      --> naechster Wert strtok	...
    if ((cmd = strtok(input, DELIMS)))
    {
        if (strcmp(cmd, cmdExit) == 0)
        {
            return RET_PARSE_CMD_EXIT;
        } else if (strcmp(cmd, cmdHelp) == 0)
        {
            showHelp();
            return RET_PARSE_CMD_OK;
        } else if (strcmp(cmd, cmdPushDir) == 0)
		{
        	char * arg = strtok(NULL, DELIMS);

			if (NULL == arg)
			{
				char cwd[1024];
				getcwd(cwd, sizeof(cwd));
				return changeDir(cwd, true);
			}

			return changeDir(arg, true);
		} else if (strcmp(cmd, cmdListDir) == 0)
		{
			char * arg = strtok(NULL, DELIMS);

			if (NULL == arg)
			{
				char cwd[1024];
				getcwd(cwd, sizeof(cwd));

				return show_dir_content(cwd, false);
			}

			return show_dir_content(arg, false);
		} else if (strcmp(cmd, cmdPopDir) == 0)
		{

			if (NULL == top())
			{
				printf("Fehler: es wurde kein Verzeichnis in den Speicher abgelegt!\n");
				return RET_PARSE_CMD_ERROR;
			}
			char * savedDir = pop();
			return changeDir(savedDir, false);
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

            char * arg = strtok(NULL, DELIMS);

            if (NULL == arg)
			{
				printf("Fehler: das Verzeichnis wurde nicht angegeben\n");
				return RET_PARSE_CMD_ERROR;
			}

            return changeDir(arg, false);

        } else if (strcmp(cmd, cmdCurrDir) == 0)
		{
			char cwd[1024];
			getcwd(cwd, sizeof(cwd));
			printf("%s\n", cwd);
			return RET_PARSE_CMD_OK;
		} else if (strcmp(cmd, cmdEcho) == 0)
		{
			char * param = strtok(NULL, DELIMS);
			while (NULL != param)
			{
				printf("%s ", param);
				param = strtok(NULL, DELIMS);
			}
			printf("\n");
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


