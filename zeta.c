/* Zeta Command Interpreter.

   Zeta is a prompt or command interpreter built purely in C.
   It provides a command-line interface to users to access the services offered by
   the kernel of the OS.
   Works with the Windows line of Operating Systems.
   
   Coding by - Arun Michael Dsouza 
   Date : 26/08/2013

   NOTE : Zeta has been built at an 'implementation-scale'. Although the native OS
          is equipped with a standard command-line utility, use of Zeta is completely not
          discouraged.
*/



//Header File Inclusion
#include <stdio.h>
#include <string.h>
#include <process.h>
#include <stdlib.h>
#include <dos.h>
#include <time.h>
#include <windows.h>

#define SIZE 256
#define IPSIZE 10

#define PERR(bSuccess, api){if(!(bSuccess)) printf("%s:Error %d from %s \ on line %d\n", __FILE__, GetLastError(), api, __LINE__);}


void initiate();
void main_exit();
void sys_time_def();
void sys_time_24hr();
void sys_time_12hr();
void sys_date_def();
void sys_day();
void sys_day_det();

int main(int argc, char const *argv[])
{
	initiate();
	return 0;
}

void initiate()
{
	char input[30];

	//Prompt Start
	printf("\n:> ");
    scanf("%s",&input);

    //----------------------------------------------------------------------------------------
	//EXIT COMMAND
    if ((stricmp(input,"exit")==0))//To exit command interpreter
    {
        main_exit();
    }
	//----------------------------------------------------------------------------------------

	//----------------------------------------------------------------------------------------
	//CLEAR SCREEN COMMAND
	else if(stricmp(input,"clr")==0) //To clear screen
	{
	    cls( GetStdHandle( STD_OUTPUT_HANDLE ));
	    initiate();
	}
	//----------------------------------------------------------------------------------------

	//----------------------------------------------------------------------------------------

	//----------------------------------------------------------------------------------------
	//TIME COMMANDS
	else if ((stricmp(input,"time")==0)) //To show time (default format:24hr HH/MM/SS.MS)
    {
    	sys_time_def();
    }

    else if ((stricmp(input,"time-24")==0)) //To show time in 24hrformat:HH/MM
    {
    	sys_time_24hr();    
    }

    else if ((stricmp(input,"time-12")==0)) //To show time in 12hr format:HH:MM AM/PM
    {
        sys_time_12hr();
    }

    else if ((stricmp(input,"time-e")==0)) //To show time and provide 'editing' option
    {
		system("time");
		initiate();
    }
    //----------------------------------------------------------------------------------------

    //----------------------------------------------------------------------------------------
	//DATE COMMANDS
	else if ((stricmp(input,"date")==0)) //To show date (default format:MM/DD/YYYY)
    {
    	sys_date_def();
    }

    else if ((stricmp(input,"date-e")==0)) //To show date and provide 'editing' option
    {
		system("date");
		initiate();
    }
    //----------------------------------------------------------------------------------------

    //----------------------------------------------------------------------------------------
	//DAY COMMANDS
	else if ((stricmp(input,"day")==0)) //To show day/date of month
    {
    	sys_day();
    }

    else if ((stricmp(input,"day-d")==0)) //To show day info in detailed format
    {
    	sys_day_det();
    }
	//----------------------------------------------------------------------------------------

	else
    {
    	printf("\aNo such command found. \n");
    	main(0,0);
    }


}



void main_exit()
{
	exit(0);
}



void sys_time_def()
{
    //Type Declaration Statements
    char input[IPSIZE];
    char buffer[SIZE];
    time_t curtime;
    struct tm *loctime;
    curtime = time (NULL); //Get the current time
	loctime = localtime (&curtime); //Convert it to local time representation

	time_t now = time(NULL);
    struct tm *now_s = localtime(&now);

    printf("%02d:%02d:%02d\n",now_s->tm_hour, now_s->tm_min,now_s->tm_sec);

    initiate();
}



void sys_time_24hr()
{
	//Type Declaration Statements
    char input[IPSIZE];
    char buffer[SIZE];
    time_t curtime;
    struct tm *loctime;
    curtime = time (NULL); //Get the current time
	loctime = localtime (&curtime); //Convert it to local time representation

	time_t now = time(NULL);
    struct tm *now_s = localtime(&now);
    
    printf("%02d:%02d\n",now_s->tm_hour, now_s->tm_min);

    initiate();
}



void sys_time_12hr()
{
	//Type Declaration Statements
    char input[IPSIZE];
    char buffer[SIZE];
    time_t curtime;
    struct tm *loctime;
    curtime = time (NULL); //Get the current time
	loctime = localtime (&curtime); //Convert it to local time representation
    
    strftime(buffer, SIZE, "The time is %I:%M %p\n", loctime);
    
    fputs(buffer, stdout);

    initiate();
}



void sys_date_def()
{
	time_t now = time(NULL);
    struct tm *now_s = localtime(&now);

    printf("%02d/%02d/%02d\n",++now_s ->tm_mon,now_s->tm_mday,1900+now_s->tm_year);

    initiate();
}



void sys_day()
{
	//Type Declaration Statements
    char input[IPSIZE];
    char buffer[SIZE];
    time_t curtime;
    struct tm *loctime;
    curtime = time (NULL); //Get the current time
	loctime = localtime (&curtime); //Convert it to local time representatio
	
	strftime(buffer, SIZE, "Today is %A, %B %d.\n", loctime);
    
    fputs(buffer, stdout);

    initiate();
}



void sys_day_det()
{
	//Type Declaration Statements
    char input[IPSIZE];
    char buffer[SIZE];
    time_t curtime;
    struct tm *loctime;
	curtime = time (NULL); //Get the current time
    loctime = localtime (&curtime); //Convert it to local time representation

	//Print out day and time in a nice format
    strftime(buffer, SIZE, "Today is %A, %B %d.\n", loctime);
    fputs(buffer, stdout);

     //Print out the date and time in the standard format
     fputs(asctime (loctime), stdout);

	strftime(buffer, SIZE, "The time is %I:%M %p.\n", loctime);

    fputs(buffer, stdout);

    initiate();
}



void cls( HANDLE hConsole )
 {
    COORD coordScreen = { 0, 0 };    /* here's where we'll home the
                                        cursor */
    BOOL bSuccess;
    DWORD cCharsWritten;
    CONSOLE_SCREEN_BUFFER_INFO csbi; /* to get buffer info */
    DWORD dwConSize;                 /* number of character cells in
                                        the current buffer */

    /* get the number of character cells in the current buffer */

    bSuccess = GetConsoleScreenBufferInfo( hConsole, &csbi );
    PERR( bSuccess, "GetConsoleScreenBufferInfo" );
    dwConSize = csbi.dwSize.X * csbi.dwSize.Y;

    /* fill the entire screen with blanks */

    bSuccess = FillConsoleOutputCharacter( hConsole, (TCHAR) ' ',
       dwConSize, coordScreen, &cCharsWritten );
    PERR( bSuccess, "FillConsoleOutputCharacter" );

    /* get the current text attribute */

    bSuccess = GetConsoleScreenBufferInfo( hConsole, &csbi );
    PERR( bSuccess, "ConsoleScreenBufferInfo" );

    /* now set the buffer's attributes accordingly */

    bSuccess = FillConsoleOutputAttribute( hConsole, csbi.wAttributes,
       dwConSize, coordScreen, &cCharsWritten );
    PERR( bSuccess, "FillConsoleOutputAttribute" );

    /* put the cursor at (0, 0) */

    bSuccess = SetConsoleCursorPosition( hConsole, coordScreen );
    PERR( bSuccess, "SetConsoleCursorPosition" );
    return;
 }
