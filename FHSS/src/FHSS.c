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
#include <sys/types.h>
#include <sys/wait.h>
#include "cmd.h"
#include "Stack.h"  // push/pop-directory
#include <dirent.h> // Verzeichnis-Informationen anzeigen
#include <pwd.h>
#include <grp.h>
#include <inttypes.h>

const char * monthNames[12] = {"Jan", "Feb", "Mar", "Apr", "Mai", "Jun", "Jul", "Aug", "Sep", "Okt", "Nov", "Dez"};

// Return-Code des letzten Befehls
int cmdRetVal = 0;

int main(int argc, char *argv[], char ** envp)
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

        cmdRetVal = parseInput(line, envp);
        if (RET_PARSE_CMD_EXIT == cmdRetVal)
        {
            break;
        }
    }

    Sdelete(); // Wenn etwas im Stack abgelegt wurde => Stack bereinigen

    return EXIT_SUCCESS;
}

/*
 * Loescht einen String aus einem anderen String
 * Parameter:
 *  - s: der String in dem gesucht werden soll (dieser wird ersetzt)
 *  - toremove: der String, welcher aus 's' geloescht werden soll
*/
void removeSubstring(char *s,const char *toremove)
{
  while( true == (bool)(s=strstr(s,toremove)) )
  {
	  /*
	   * The C library function
	   * void *memmove(void *str1, const void *str2, size_t n)
	   * copies n characters from str2 to str1,
	   * but for overlapping memory blocks,
	   * memmove() is a safer approach than memcpy().
	  */
	  memmove(s,s+strlen(toremove),1+strlen(s+strlen(toremove)));
  }
}

/*
 * Prueft ob eine Datei existiert
 * Parameter:
 * 	- path: ganzer Pfad, bspw. /bin/nano
 * Rueckgabewert:
 *    true wenn Datei existiert, sonst false
 */
bool FileExist(char * path)
{
    return ( access( path, F_OK ) != -1 );
}

/*
 * Sucht in den Umgebungsvariablen nach der Programmdatei, welche ausgefuehrt werden soll
 * Dies ermoeglicht es, Programme wie bspw. vi oder nano oder komplette Pfadangabe zu finden
 * Parameter:
 *  - values: die Umgebungsvariable
 *  - found: der vollstaendige Pfad (z.b. /bin/nano)
 *  - command: die Programmdatei, die ausgefuehrt werden soll (bspw. nano)
 * Rueckgabewerte:
 *  - true wenn ein Pfad zur Programmdatei gefunden wurde, sonst false
 */
bool findExecutable(char * values, char * found, char * command)
{
    char delimiter[] = ";:";
    char *ptr;

    // initialisieren und ersten Abschnitt erstellen
    ptr = strtok(values, delimiter);

    while(ptr != NULL) {

        char * dest = malloc(sizeof(char) * 255);
        if (NULL == dest)
        {
        	found = NULL;
        	return false;
        }
        char * src = malloc(sizeof(char) * 255);
        if (NULL == src)
		{
			found = NULL;
			return false;
		}
        strcpy(src, ptr);
        strcpy(dest, command);
        strcat(src, "/");
        strcat(src, dest);
        removeSubstring(src, "PATH=");
        //Jede Pfadangabe in den Umgebungsvariablen für PFAD wird ueberprueft
        //Wenn die Datei exitiert, wird found gesetzt und true zurueck gegeben
        if (FileExist(src))
        {
            strcpy(found, src);
            return true;
        }

        // naechsten Abschnitt erstellen
        ptr = strtok(NULL, delimiter);
    }

    return false;
}




/*
 * Ueberprueft, ob ein String mit einem anderen String beginnt
 * Parameter:
 * 	search: Suchstring
 * 	complete: String, in dem gesucht werden soll
 * Rueckgabewert:
 *  true wenn der complete-String mit dem search-String beginnt, sonst false
*/
bool startsWith(const char * search, const char * complete)
{
    int pos = 0;

    while (search[pos] != '\0')
    {
        if (complete[pos] == '\0') //search String ist kuerzer als der complete string
        {
            return false;
        }

        if (search[pos] != complete[pos]) // ein unterschiedliches Zeichen gefunden
        {
            return false;
        }
        pos++;
    }

    return true;
}

/*
 * Fuehrt ein Programm mittels execv aus (zuvor wird mittels fork() ein Kindprozess erzeugt)
 * Parameter:
 *  - command: die Datei, welche ausgefuehrt werden soll
 *  - params: die Parameter zu der Programm-Datei Ausfuehrung
 * Rueckgabewerte:
 * 	Nach Beendigung des Programms die Rueckgabecode des Programms, welches ausgefuehrt wurde
 * 	Falls es beim Erstellen des Prozesses ein Problem gegeben hat wird -1 zurueck gegeben
 */
int execute(char * command, char * params)
{
	if (!(FileExist(command)))
	{
		printf("FEHLER: Die angegebene Datei existiert nicht!\n");
		return (int)-1;
	}

    pid_t pid;
    pid = fork();
    int status;
    if(pid == -1)
    {
        printf("FEHLER: beim Starten des Programms ist ein Fehler aufgetreten!\n");
    }
    if(pid == 0)
    {
    	/*
    	int pos = 0;
    	int posLastSlash = (int)-1;
    	for(pos=strlen(params)-1;pos>0;pos--)
    	{
    		if (params[pos] == '/')
    		{
    			posLastSlash = pos+1;
    			break;
    		}
    	}
    	char * tmpParam = (char *)malloc(sizeof(char) * (strlen(params) - posLastSlash) + 1);

    	if (posLastSlash > -1)
    	{
    		int newPos = 0;
    		for(pos=posLastSlash; pos<strlen(params); pos++)
    		{
    			tmpParam[newPos++] = params[pos];
    		}
    		tmpParam[newPos] = '\0';
    	}
		*/

    	char * argumente[2] = { params, NULL };


    	waitpid(pid, &status, 0);
    	execv (command, argumente);
    }
    else if (pid > 0)
    {
    	wait(&status);
		if (WIFEXITED(status))
		{
			return WEXITSTATUS(status);
		}
    }
    return (int)-1;
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

/*
 * Gibt eine Kurzform des Verzeichnisinhaltes eines Verzeichnisses auf stdout aus
 * Parameter:
 *  - d: das Verzeichnis, dessen Inhalt aufgelistet werden soll
 *  - hidePointDirs: wenn true werden keine Dateinamen/Verzeichnisse mit fuehrenden Punkt angefuehrt
 */
void printDirectoryShort(DIR * d, bool hidePointDirs)
{
	struct dirent * dir; // fuer die Dateien im Verzeichnis
	while ((dir = readdir(d)) != NULL) // Solange die Dateien aus dem Verzeichnis gelesen werden kann
		{

			if(dir-> d_type != DT_DIR) // Wenn kein Verzeichnis Ausgabe auf stdout in blau
			{
				printf("%s%s\t",BLUE, dir->d_name);
			}
			else
			{
				char fName[256];
				strcpy(fName, dir->d_name);
				if(dir -> d_type == DT_DIR && strcmp(dir->d_name,".")!=0 && strcmp(dir->d_name,"..")!=0 ) // Ausgabe auf stdout in gruen wenn Verzeichnis
				{
					printf("%s%s\t",GREEN, dir->d_name); // Wenn Parameter 'a' angegeben wurde dann '.' und '..' mit auf stdout ausgeben
				} else if ((fName[0] == '.') && !hidePointDirs)
				{
					printf("%s%s\t",GREEN, ".");
				}
			}
		}
		printf("\n");
}

/*
 * Gibt den Dateirechte einer Datei auf stdout aus
 * bswp:
 *       drwxr--r--
 *       -rwxr--r--
 * Parameter:
 * 	- st_mode: st_mode aus der Funktion stat fuer eine Datei
 */
void printfFileRights(__mode_t st_mode)
{
	printf("%s",NORMAL_COLOR);
	if (S_ISLNK(st_mode))
	{
		printf("l");
	} else if (S_ISDIR(st_mode))
	{
		printf("d");
	} else
	{
		printf("-");
	}
	printf( (st_mode & S_IRUSR) ? "r" : "-");
	printf( (st_mode & S_IWUSR) ? "w" : "-");
	printf( (st_mode & S_IXUSR) ? "x" : "-");
	printf( (st_mode & S_IRGRP) ? "r" : "-");
	printf( (st_mode & S_IWGRP) ? "w" : "-");
	printf( (st_mode & S_IXGRP) ? "x" : "-");
	printf( (st_mode & S_IROTH) ? "r" : "-");
	printf( (st_mode & S_IWOTH) ? "w" : "-");
	printf( (st_mode & S_IXOTH) ? "x" : "-");
}

/*
 * Gibt den Gruppennamen der Datei auf stdout aus
 * Parameter:
 * 	- gid: group-id der Datei
 */
void printGroupUser(__gid_t gid)
{
	struct group *grp;
	grp = getgrgid(gid);
	printf("%s", NORMAL_COLOR);
	if (NULL == grp->gr_name)
	{
		printf("<null>");
	} else
	{
		printf("%s", grp->gr_name);
	}
}

/*
 * Gibt die Benuternamen der Datei auf stdout aus
 * Parameter:
 * 	- uid: user-id der Datei
 */
void printUserUser(__uid_t uid)
{
	struct passwd *pwd;

	pwd = getpwuid(uid);
	printf("%s", NORMAL_COLOR);
	if (NULL == pwd->pw_name)
	{
		printf("<null>");
	} else
	{
		printf("%s", pwd->pw_name);
	}
}

/*
 * Gibt die Anzahl der Links einer Datei formatiert auf stdout aus
 * Parameter:
 * 	- nlink_t: Anzahl der Links der Datei
 */
void printLinkInfo(__nlink_t nlink_t)
{
	printf("%s", NORMAL_COLOR);
	printf("%02" PRId64"", nlink_t);
}

/*
 * Gibt das Datum der Datei formatiert auf stdout aus
 * Wenn der Zeitpunkt der Erstellung nicht im selben Jahr wie die aktuelle Systemzeit ist
 * wird  'Monat Tag Jahr' ausgegeben
 * sonst 'Monat Tag Uhrzeit'
 * Parameter:
 * 	- mtime: Datum der Datei
 */
void printFileDate(const time_t mtime)
{
	printf("%s", NORMAL_COLOR);

	struct tm * tm_info;
	struct tm * timeinfo = getTimeInfo();

	tm_info = localtime(&mtime);

	printf("%s", monthNames[tm_info->tm_mon-1]);
	printf(" %02d", tm_info->tm_mday);
	//Wenn aktuelles Jahr nicht gleich das Jahr der Datei -> Jahr anstelle der Uhrzeit ausgeben
	if ((timeinfo->tm_year) == (tm_info->tm_year))
	{
		printf(" %02d:%02d", tm_info->tm_hour, tm_info->tm_min);
	} else
	{
		printf("  %04d", tm_info->tm_year+1900);
	}

}

/*
 * Gibt die Groesse der Datei formatiert auf stdout aus
 * Parameter:
 * 	- size: Dateigroesse
 */
void printFileSize(__off_t size)
{
	char str[30];
	sprintf(str, "%"PRId64"", size);
	if (size < 10000000)
	{
		printf("%9s", str);
	} else
	{
		printf("%15s", str);
	}
}

/*
 * Gibt den Dateinamen auf stdout aus
 * Abhaengig von dem Typ (Verzeichnis, Datei, Link, ...)
 * werden diese in unterschiedlichen Farben auf stdout ausgegeben
 * Parameter:
 * 	- st: die Struktur von dem Verzeichnis welche mittels stat eingelesen wurde
 * 	- d_name: Dateiname
 */
void printFileName(struct stat st, const char * d_name)
{
	// Handelt es sich um eine ausfuehrbare Datei?
	bool isExecuteAble = (st.st_mode & S_IXUSR) || (st.st_mode & S_IXGRP) || (st.st_mode & S_IXOTH);

	if (S_ISDIR(st.st_mode))
	{
		printf("%s%s  ", BLUE, d_name);
	} else if (S_ISLNK(st.st_mode))
	{
		printf("%s%s  ", MANGAN, d_name);
	} else if (isExecuteAble)
	{
		printf("%s%s  ", GREEN, d_name);
	} else
	{
		printf("%s%s  ", NORMAL_COLOR, d_name);
	}
}

/*
 * Gibt die Dateiinformationen fuer das angegebene Verzeichnis auf stdout aus
 * Parameter:
 * 	- Path: welches Verzeichnis verwendet werden soll
 * 	- Params: welche Informationen auf stdout ausgegeben werden sollen
 * Rueckgabeparameter:
 *  - RET_PARSE_CMD_OK wenn erfolgreich, sonst RET_PARSE_CMD_ERROR
 */
int show_dir_content(char * path, int params)
{
	DIR * d = opendir(path); // Pfad oeffnen
	if(NULL == d)
	{
		printf("Fehler: Pfad konnte nicht geoeffnet werden!\n");
		return RET_PARSE_CMD_ERROR; // Wenn der Pfad nicht geoeffnet werden kann
	}

	struct dirent * dir; // fuer die Dateien im Verzeichnis

	while ((dir = readdir(d)) != NULL) // Solange die Dateien aus dem Verzeichnis gelesen werden kann
	{
		// ignorieren, wenn Parameter nicht gesetzt ist
		if(dir->d_name[0] == '.' && ((params & MASK_LS_a) != MASK_LS_a))
		{
			continue;
		}

		struct stat st;

		// Fehlerbehandlung
		if (stat(dir->d_name, &st) == -1)
		{
			printf("Fehler beim Lesen von %s\n",dir->d_name);
			continue;
		}

		if ((params & MASK_LS_l) == MASK_LS_l)
		{
			printfFileRights(st.st_mode);
			printf(" ");
			printLinkInfo(st.st_nlink);
			printf(" ");
			printGroupUser(st.st_gid);
			printf(" ");
			printUserUser(st.st_uid);
			printf(" ");
			printFileSize(st.st_size);
			printf(" ");
			printFileDate(st.st_mtime);
			printf(" ");
			printFileName(st, dir->d_name);
			printf("\n");
		} else
		{
			printFileName(st, dir->d_name);
		}

	}
	if ((params & MASK_LS_l) != MASK_LS_l)
	{
		printf("\n");
	}
	closedir(d); // Den Verzeichnis-Kanal schliessen
	return RET_PARSE_CMD_OK;
}

/*
 * Das aktuelle Verzeichnis aendern
 * Parameter:
 *  - newDir: Pfad auf das neue Verzeichnis
 *  - popDirOnly: das neue Verzeichnis wird nur in den Zwischenspeicher abgelegt
 * Rueckgabewerte:
 *  - RET_PARSE_CMD_OK wenn erfolgreich, sonst RET_PARSE_CMD_ERROR
*/
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
int parseInput(char * input, char ** envp)
{
    // Befehlsargument
    char * cmd;


    // Es soll der erste Wert aus der Eingabezeile bis zum Trennzeichen gelesen werden
    // Bsp: zeigeEtwasAn [Wert von DELIMS] Parameter1 [Wert von DELIMS] Parameter2
    //      ^--> cmd                       ^
    //                                      --> naechster Wert strtok	...
    if ((cmd = strtok(input, DELIMS)))
    {
        if (strcmp(cmd, cmdExit) == 0) // Shell beenden
        {
            return RET_PARSE_CMD_EXIT;
        } else if (strcmp(cmd, cmdHelp) == 0)  // Hilfe auf stdout ausgeben
        {
            showHelp();
            return RET_PARSE_CMD_OK;
        } else if (strcmp(cmd, cmdPushDir) == 0) // Pfad in den Speicher schreiben
		{
        	char * arg = strtok(NULL, DELIMS);

			if (NULL == arg)
			{
				char cwd[1024];
				getcwd(cwd, sizeof(cwd));
				return changeDir(cwd, true);
			}

			return changeDir(arg, true);
		} else if (strcmp(cmd, cmdListDir) == 0) // List-Dir ausfuehren
		{
			char * arg = strtok(NULL, DELIMS);
			char cwd[1024];
			getcwd(cwd, 1024);
			int maskLS = 0;

			if (NULL == arg)
			{
				return show_dir_content(cwd, maskLS);
			}

			if ('-' == arg[0])
			{
				//Parameter fuer das Anzeigen des Verzeichnisses
				int pos = 1;
				while(arg[pos] != '\0')
				{
					if ('l' == arg[pos])
						maskLS = maskLS | MASK_LS_l; // setze die Bitmaske fuer den 'l' Parameter
					else if ('a' == arg[pos])
						maskLS = maskLS | MASK_LS_a;  // setze die Bitmaske fuer den 'a' Parameter
					pos++;
				}
			}

			return show_dir_content(cwd, maskLS);
		} else if (strcmp(cmd, cmdPopDir) == 0) // Pfad aus dem Speicher auslesen
		{

			if (NULL == top())
			{
				printf("Fehler: es wurde kein Verzeichnis in den Speicher abgelegt!\n");
				return RET_PARSE_CMD_ERROR;
			}
			char * savedDir = pop();
			return changeDir(savedDir, false);
		} else if (strcmp(cmd, cmdFHSDate) == 0) // Datum auf stdout ausgeben
        {
            struct tm * timeinfo = getTimeInfo();
            printf ( "Das aktuelle Datum ist: %02d.%02d.%d\n", timeinfo->tm_mday, timeinfo->tm_mon, (timeinfo->tm_year)+1900 );
            return RET_PARSE_CMD_OK;
        }  else if (strcmp(cmd, cmdFHSTime) == 0) // Uhrzeit auf stdout ausgeben
        {
            struct tm * timeinfo = getTimeInfo();
            printf ( "Die aktuelle Uhrzeit ist: %02d:%02d:%02d\n", timeinfo->tm_hour, timeinfo->tm_min, timeinfo->tm_sec );
            return RET_PARSE_CMD_OK;
        } else if (strcmp(cmd, cmdChangeDir) == 0) // aktuelles Verzeichnis aendern
        {

            char * arg = strtok(NULL, DELIMS);

            if (NULL == arg)
			{
				printf("Fehler: das Verzeichnis wurde nicht angegeben\n");
				return RET_PARSE_CMD_ERROR;
			}

            return changeDir(arg, false);

        } else if (strcmp(cmd, cmdCurrDir) == 0) // Das aktuelle Verzeichnis auf stdout ausgeben
		{
			char cwd[1024];
			getcwd(cwd, sizeof(cwd));
			printf("%s\n", cwd);
			return RET_PARSE_CMD_OK;
		} else if (strcmp(cmd, cmdEcho) == 0) // echo kommando ausfuehren, Parameter auf stdout ausgeben
		{
			char * param = strtok(NULL, DELIMS);
			if (strcmp(param, "$?") == 0)
			{
				printf("%d\n", cmdRetVal);
				return cmdRetVal; //Return-Code behalten
			}
			while (NULL != param)
			{
				printf("%s ", param);
				param = strtok(NULL, DELIMS);
			}
			printf("\n");
			return RET_PARSE_CMD_OK;
		} else
        {
			if (cmd[0] == '.' || cmd[0] == '/')
			{
				return execute(cmd, cmd);
			}

			char** env;
			char path[255];
			for (env = envp; *env != 0; env++)
			{
				char thisEnv[4096];
				strcpy(thisEnv, *env);

				if (startsWith("PATH=", thisEnv))
				{

					if (findExecutable(thisEnv, path, cmd))
					{
						return execute (path, cmd);
					}
					else
					{
						printf("Fehler: Befehl '%s' nicht gefunden!\n", cmd);
					}
				}
			}
            //system(cmd);
            //return RET_PARSE_CMD_SYS;
            //printf("Fehler: Die Eingabe %s ist unbekannt!\n", input);
            return RET_PARSE_CMD_UNKNOWN;
        }
    } else
    {
    	return RET_PARSE_CMD_NOT_SET;
    }
}


