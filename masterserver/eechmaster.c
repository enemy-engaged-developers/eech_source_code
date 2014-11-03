// ------------------
// Enemy Engaged: Comanche vs Hokum
// MASTER GAME SERVER
// (c) 2003 Playspoon
// ------------------

#include <sys/time.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/wait.h>
#include <netdb.h>
#include <sys/wait.h>
#include <arpa/inet.h>

unsigned addr_len, numbytes = 0;
typedef struct
{
    char Address[100];
    char Name[256];
    int MaxClients;
    int CurClients;
    char Version[256];
    int Age;
    int TotalAge;
    int isUsed;
} ServerData;

char tempstring[500];
int PacketSize = 5000;
struct sockaddr_in from;
struct sockaddr_in gameserver;
char ReceiveBuffer[2048];
char SendBuffer[2048];
unsigned ServerSocket;
int port = 1375;
ServerData Servers[15000];
int maxservers=0;
int MaxServerAge = 240; //Servers are removed after 240 seconds of inactivity

#define FALSE 0
#define TRUE 1
#define LOG 1

const char header1[3000] = {"<HTML><HEAD><TITLE>Enemy Engaged Server List</TITLE><ALKALINE skip> \
<META content=\"A list of all active EECH multiplayer servers\" \
name=description> \
<LINK href=\"eechmaster.css\" rel=stylesheet type=text/css></ALKALINE> \
<META content=\"skiptext skipmeta\" name=alkaline> \
<BODY bgColor=#000000 leftMargin=4 text=#000000 topMargin=4 marginheight=4 marginwidth=4> \
<CENTER><br><img src=\"masterserver.jpg\"><br><br> \
      <TABLE class=t5 border=1 borderColorDark=#464646 cellPadding=0 cellSpacing=0 width=700> \
        <TBODY> \
        <TR bgColor=#9090f0> \
          <TD align=middle borderColor=#c0c0c0><FONT face=Arial size=5><B> Server List \
	  </B></FONT></TD></TR></TBODY></TABLE> \
	  <BR><BR> \
            <TABLE class=t5 border=1 borderColorDark=#464646 cellPadding=0 cellSpacing=0> \
              <TBODY> \
              <TR bgColor=#c0c0c0> \
                <TD width=100 align=left borderColor=#c0c0c0><FONT face=Tahoma size=1><B> \
		&nbsp; Total Servers: \
		</B></FONT></TD> \
                <TD width=70 align=left borderColor=#c0c0c0><FONT face=Tahoma size=1><B> \
		&nbsp; \
		"};
//		 7
const char header2[3000] = {"</B></FONT></TD> \
	      </TR> \
		</TBODY></TABLE> \
            <TABLE border=0 cellPadding=0 cellSpacing=0 height=1> \
              <TBODY> \
              <TR> \
                <TD></TD></TR></TBODY></TABLE> \
            <TABLE class=t5 border=1 borderColorDark=#464646 cellPadding=0 cellSpacing=0> \
              <TBODY> \
              <TR bgColor=#c0c0c0> \
                <TD width=100 align=left borderColor=#c0c0c0><FONT face=Tahoma size=1><B> \
		&nbsp; Total Players: \
		</B></FONT></TD> \
                <TD width=70 align=left borderColor=#c0c0c0><FONT face=Tahoma size=1><B> \
		&nbsp;  \
		"};
//		0
const char header3[3000] = {"</B></FONT></TD> \
	      </TR> \
		</TBODY></TABLE> \
            <TABLE border=0 cellPadding=0 cellSpacing=0 height=1> \
              <TBODY> \
              <TR> \
                <TD></TD></TR></TBODY></TABLE> \
	   <BR><BR> \
            <TABLE class=t5 border=1 borderColorDark=#464646 cellPadding=0 cellSpacing=0 width=700> \
              <TBODY> \
              <TR bgColor=#9090d0> \
                <TD width=120 align=left borderColor=#c0c0c0><FONT face=Tahoma size=1><B> \
		&nbsp; Hosting Player Name \
		</B></FONT></TD> \
                <TD width=80 align=middle borderColor=#c0c0c0><FONT face=Tahoma size=1><B> \
		Current Players \
		</B></FONT></TD> \
                <TD width=80 align=middle borderColor=#c0c0c0><FONT face=Tahoma size=1><B> \
		MaxPlayers \
		</B></FONT></TD> \
                <TD width=110 align=middle borderColor=#c0c0c0><FONT face=Tahoma size=1><B> \
		IP Address \
		</B></FONT></TD> \
                <TD width=100 align=middle borderColor=#c0c0c0><FONT face=Tahoma size=1><B> \
		Version \
		</B></FONT></TD> \
                <TD width=70 align=middle borderColor=#c0c0c0><FONT face=Tahoma size=1><B> \
		Uptime \
		</B></FONT></TD> \
		</TR> \
              <TR bgColor=#000000> \
                <TD width=120 align=left borderColor=#c0c0c0><FONT face=Tahoma size=1><B> \
		- \
		</B></FONT></TD> \
                <TD width=80 align=middle borderColor=#c0c0c0><FONT face=Tahoma size=1><B> \
		- \
		</B></FONT></TD> \
                <TD width=80 align=middle borderColor=#c0c0c0><FONT face=Tahoma size=1><B> \
		- \
		</B></FONT></TD> \
                <TD width=110 align=middle borderColor=#c0c0c0><FONT face=Tahoma size=1><B> \
		- \
		</B></FONT></TD> \
                <TD width=100 align=middle borderColor=#c0c0c0><FONT face=Tahoma size=1><B> \
		- \
		</B></FONT></TD> \
                <TD width=70 align=middle borderColor=#c0c0c0><FONT face=Tahoma size=1><B> \
		- \
		</B></FONT></TD> \
		</TR> \
		"};

const char trailer[1024] = {"</TBODY></TABLE> \
            <TABLE border=0 cellPadding=0 cellSpacing=0 height=1> \
              <TBODY> \
              <TR> \
                <TD></TD></TR></TBODY></TABLE> \
</CENTER> \
		"};

const char step1a[1024] = {"<TR bgColor=#e0e0e0> \
                <TD align=left borderColor=#c0c0c0><FONT face=Tahoma size=1><B>&nbsp; \
		"};
const char step1b[1024] = {"<TR bgColor=#b0b0b0> \
                <TD align=left borderColor=#c0c0c0><FONT face=Tahoma size=1><B>&nbsp; \
		"};
//		Development Server at draid.dhs.org
const char step2[1024] = 
{"</B></FONT></TD> \
                <TD align=middle borderColor=#c0c0c0><FONT face=Tahoma size=1><B> \
		"};
//		0 curclients
const char step3[1024] = {"</B></FONT></TD> \
                <TD align=middle borderColor=#c0c0c0><FONT face=Tahoma size=1><B> \
		"};
//		8 maxclients
const char step4[1024] = {"</B></FONT></TD> \
                <TD align=middle borderColor=#c0c0c0><FONT face=Tahoma size=1><B> \
		"};
//		192.168.0.200
const char step5[1024] = {"</B></FONT></TD> \
                <TD align=middle borderColor=#c0c0c0><FONT face=Tahoma size=1><B> \
		"};
//		v1.0
const char step6[1024] = {"</B></FONT></TD> \
                <TD align=middle borderColor=#c0c0c0><FONT face=Tahoma size=1><B> \
		"};
//		4h20m
const char step7[1024] = {"</B></FONT></TD> \
		</TR> \
		"};









void WriteServerList(void)
{
    int i;
    int alternating  = 1;
    int totalservers = 0;
    int totalplayers = 0;
    FILE *f;

	if (f=fopen("//var//www//index.html", "w"))
	{
		for(i=0; i<=(maxservers+5); i++)
			if (Servers[i].isUsed != -1)
			{
				totalservers++;
				totalplayers+=Servers[i].CurClients;
			}

		fprintf(f, "%s", header1);
		fprintf(f, "%i", totalservers);
		fprintf(f, "%s", header2);
		fprintf(f, "%i", totalplayers);
		fprintf(f, "%s", header3);

		for(i=0; i<=(maxservers+5); i++)
			if (Servers[i].isUsed != -1)
			{
				alternating = (-1)*alternating;
				if (alternating<0)
				fprintf(f, "%s", step1a);
				else
				fprintf(f, "%s", step1b);
				fprintf(f, "%s", Servers[i].Name);
				fprintf(f, "%s", step2);
				fprintf(f, "%i", Servers[i].CurClients);
				fprintf(f, "%s", step3);
				fprintf(f, "%i", Servers[i].MaxClients);
				fprintf(f, "%s", step4);
				fprintf(f, "%s", Servers[i].Address);
				fprintf(f, "%s", step5);
				fprintf(f, "%s", Servers[i].Version);
				fprintf(f, "%s", step6);
				fprintf(f, "%ih %im", abs(Servers[i].TotalAge / 3600), abs((Servers[i].TotalAge%3600) / 60));
				fprintf(f, "%s", step7);
			}

		fprintf(f, "%s", trailer);
		fclose(f);
	}
}



void WriteLog(const char s1[])
{
    FILE *f;
	time_t rawtime;
	struct tm *info;

	time( &rawtime );
	info = localtime( &rawtime );
    
	if (f=fopen("//var//log//eechlog", "a"))
    {
        fprintf(f, "%s    %s", asctime(info), s1);
        fclose(f);
    }

	#if LOG
		printf("%s", s1);
	#endif
}


void ServerAging(void)
{
	int i;

    for(i = 0; i <= maxservers + 5; i++)
		if (Servers[i].isUsed != -1)
		{
			Servers[i].TotalAge++;
			Servers[i].Age++;
		}

    for(i = 0;i <= maxservers + 5; i++)
		if (Servers[i].isUsed != -1)
			if (Servers[i].Age > MaxServerAge)
			{
				sprintf(tempstring, "REMOVE: %s [%s] after %ih %im\n", Servers[i].Address, Servers[i].Name, abs(Servers[i].TotalAge / 3600), abs((Servers[i].TotalAge%3600) / 60));
				WriteLog(tempstring);
				Servers[i].isUsed=-1;
				WriteServerList();
//				if (i==maxservers)
//				    maxservers--;
			}
}

void ProcessServerHeartbeat(void)
{
    char header[80];
    char TempName[400];
    char TempAddress[256];
    int TempMaxClients;
    int TempCurClients;
    char TempVersion[256];
    int i;
    int found = FALSE;

    if (strlen(ReceiveBuffer) < 10)
		return;

    sscanf(ReceiveBuffer, "%s %s %s %i %i %s", header,
	TempAddress, TempName, &TempMaxClients, &TempCurClients, TempVersion);

    sprintf(TempAddress, "%s", inet_ntoa(from.sin_addr));

    // convert underscores in server names to spaces
    for (i=0; i<strlen(TempName); i++)
		if (TempName[i]=='_')
			TempName[i]=' ';

    // already in list? If yes, then just update data
    for(i=0; i<=(maxservers+5); i++)
		if ((Servers[i].isUsed!=-1) && (strcmp(Servers[i].Address,TempAddress)==0))
		{
			#if LOG
				printf("UPDATE: Server %i\n", i);
			#endif

			if (Servers[i].CurClients != TempCurClients)
			{
				sprintf(tempstring, "Player count changed: %s [%s] %i Clients\n", Servers[i].Address, Servers[i].Name, Servers[i].CurClients);
				WriteLog(tempstring);
			}

			sprintf(Servers[i].Name, "%s", TempName);
			Servers[i].MaxClients = TempMaxClients;
			Servers[i].CurClients = TempCurClients;
			Servers[i].Age = 0;
			found = TRUE;
			WriteServerList();
			return;
		}
    
    //If not already in list, look for an emtpy slot to place server in...
    if (!found)
    {
        for(i=0; i<=(maxservers+5); i++)
			if (Servers[i].isUsed==-1)
			{
				sprintf(Servers[i].Name, "%s", TempName);
				sprintf(Servers[i].Address, "%s", TempAddress);
				Servers[i].MaxClients = TempMaxClients;
				Servers[i].CurClients = TempCurClients;
				sprintf(Servers[i].Version, "%s", TempVersion);
				Servers[i].Age = 0;
				Servers[i].TotalAge = 0;
				Servers[i].isUsed = 1;
				sprintf(tempstring, "ADD: %s [%s] Version %s\n", Servers[i].Address, Servers[i].Name, Servers[i].Version);
				WriteLog(tempstring);
				found = 1;
				if (i >= maxservers)
					maxservers=i;
				WriteServerList();
				return;
			}
    }
}

void SendServerList(void)
{
    int i, o, counter = 0;
    char TempName[800];
    char header[80];

	#if LOG
		printf("LIST REQUEST\n");
	#endif

    for(i=0; i<=(maxservers+5); i++)
    {
		if (Servers[i].isUsed != -1)
		{
			sprintf(TempName, "%s", Servers[i].Name);

			for (o = 0; o < strlen(TempName); o++)
				if (TempName[o]==' ')
					TempName[o]='_' ;

			sprintf(SendBuffer, "%s %s %s %i %i %s", "W",
			Servers[i].Address,
			TempName,
			Servers[i].MaxClients,
			Servers[i].CurClients,
			Servers[i].Version);
			sendto(ServerSocket, SendBuffer ,strlen(SendBuffer),0,(struct sockaddr *)&from, sizeof(struct sockaddr));
			counter++;
		}
    }

    sprintf(SendBuffer, "%s %s", "X", "Done!");
    sendto(ServerSocket, SendBuffer ,strlen(SendBuffer),0,(struct sockaddr *)&from, sizeof(struct sockaddr));
	#if LOG
		printf("%i servers are send\n", counter);
	#endif
}

int main(void)
{
	int QuitServer = 0;
	int i;
	struct timeval tv;
	fd_set readfds;

	ReceiveBuffer[0] = '\0';

	for (i=0; i<14999; i++)
	  Servers[i].isUsed = -1;

	WriteServerList();

	if ((ServerSocket = socket(AF_INET, SOCK_DGRAM, 0)) == -1)
	{
		perror("socket");
		exit(1);
	}

    gameserver.sin_family = AF_INET;
    gameserver.sin_port = htons(port);
    gameserver.sin_addr.s_addr = INADDR_ANY;
    bzero(&(gameserver.sin_zero), 8);

    if (bind(ServerSocket, (struct sockaddr *)&gameserver, sizeof(struct sockaddr)) == -1)
	{
		perror("bind");
		exit(1);
	}

    addr_len = sizeof(struct sockaddr);

	do
	{
		tv.tv_sec = 1;
		tv.tv_usec = 0;
		FD_ZERO(&readfds);
		FD_SET(ServerSocket, &readfds);
		select(ServerSocket+1, &readfds, NULL, NULL, &tv);

		if (FD_ISSET(ServerSocket, &readfds))
		{
			numbytes = recvfrom(ServerSocket,ReceiveBuffer,PacketSize,0,(struct sockaddr *)&from, &addr_len);
			ReceiveBuffer[numbytes] = '\0';

			#if LOG
				printf("\nReceived packet: \"%s\", %i bytes\n",ReceiveBuffer, numbytes);
			#endif

			if (ReceiveBuffer[0] != '\0')
			{
				if (ReceiveBuffer[0]==90)
					ProcessServerHeartbeat();
				else if (ReceiveBuffer[0]==89)
					SendServerList();
				else
				{
					sprintf(SendBuffer, "Unknown Command!");
					sendto(ServerSocket, SendBuffer ,strlen(SendBuffer),0,(struct sockaddr *)&from, sizeof(struct sockaddr));
				}
			}
		}
		else
			ServerAging();


	}
	while (QuitServer==0);

	close(ServerSocket);
	return 0;
}
