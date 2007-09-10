#include <stdlib.h>
#include <stdio.h>
#include <windows.h>
#include <winioctl.h>
#include "Usb_Boot_defines.h"
#include "USB_Boot_API.h"
 
int com_argc;
char com_argv[20][50];
unsigned char code_buf[MAX_TRANSFER_SIZE];
const char CURRENT_VERSION[]="0.8";
const char HEX_NUM[17]={'0','1','2','3','4','5','6','7','8','9','a','b','c','d','e','f',' '};
NAND_IN nand_in;
NAND_OUT nand_out;
SDRAM_IN sdram_in;
unsigned char cs[16];

extern int Error_Check(unsigned char *org,unsigned char * obj,unsigned int size);

const char COMMAND[][30]=
{
	"",
	"query",
	"querya",
	"erase",
	"read",
	"prog",
	"nquery",
	"nerase",
	"nread",
	"nreadraw",
	"nreadoob",
    "nprog",
	"help",
	"version",
	"go",
	"fconfig",
	"exit",
	"readnand",
	"",
	"",
	"boot",
	"list",
	"select",
	"unselect",
	"chip",
	"unchip",
	"nmake",
	"load"
};
unsigned int HextoDec(char *s)
{
	int i,L=(int)strlen(s),j;
	unsigned int temp=0;
	//printf("\n LLL:%d",L);
	if (L>8) L=8;
	for (i=0;i<L;i++)
	{
		for (j=0;j<16;j++)
		if (s[i]==HEX_NUM[j]) break;
		if (j==16) return 0;
		temp=temp*16+j;
	}
	return temp;
}

void Exit(int res)
{
	printf("\n Exiting USB Boot software");
	//Handle_Close();
	exit(res);
}


int Handle_nquery(void)
{
	int i;
	if (com_argc<3)
	{
		printf("\n Usage:");
		printf(" nquery (1) (2) ");
		printf("\n 1:device index number \
			   \n 2:flash index number "); 
		return -1;
	}
	for (i=0;i<MAX_DEV_NUM;i++)
		(nand_in.cs_map)[i] = 0;

	nand_in.dev = atoi(com_argv[1]);
	(nand_in.cs_map)[atoi(com_argv[2])] = 1;
	API_Nand_Query(&nand_in);
	return 1;
}

int Handle_nerase(void)				//need transfer two para :blk_num ,start_blk
{
	//int start_blk,blk_num;
	int i;
	if (com_argc<5)
	{
		printf("\n Usage:");
		printf(" nerase (1) (2) (3) (4) ");
		printf("\n 1:start block number   \
				\n 2:block length         \
				\n 3:device index number \
				\n 4:flash chip index number ");

		return -1;
	}
	for (i=0;i<MAX_DEV_NUM;i++)
		(nand_in.cs_map)[i] = 0;

	nand_in.start = atoi(com_argv[1]);
	nand_in.dev = atoi(com_argv[3]);
	nand_in.length = atoi(com_argv[2]);
	if (atoi(com_argv[4])>=MAX_DEV_NUM)
	{
		printf("\n Flash index number overflow!");
		return -1;
	}
	(nand_in.cs_map)[atoi(com_argv[4])] = 1;
	API_Nand_Erase(&nand_in);
	return 1;
}

int Handle_nread(void)
{
	int i;

	if (com_argc<5)
	{
		printf("\n Usage:");
		printf(" nread (1) (2) (3) (4) ");
		printf("\n 1:start page number   \
			    \n 2:length in byte    \
				\n 3:device index number \
				\n 4:flash index number ");
		return -1;
	}
	for (i=0;i<MAX_DEV_NUM;i++)
		(nand_in.cs_map)[i] = 0;
	if (atoi(com_argv[4])>=MAX_DEV_NUM)
	{
		printf("\n Flash index number overflow!");
		return -1;
	}
	(nand_in.cs_map)[atoi(com_argv[4])] = 1;
	nand_in.dev = atoi(com_argv[3]);
	nand_in.start = atoi(com_argv[1]);
	nand_in.length= atoi(com_argv[2]);
	API_Nand_Read(&nand_in,0);
	return 1;
} 

int Handle_nreadraw(void)
{
	int i;

	if (com_argc<5)
	{
		printf("\n Usage:");
		printf(" nreadraw (1) (2) (3) (4) ");
		printf("\n 1:start page number   \
			    \n 2:length in byte    \
				\n 3:device index number \
				\n 4:flash index number ");
		return -1;
	}
	for (i=0;i<MAX_DEV_NUM;i++)
		(nand_in.cs_map)[i] = 0;
	if (atoi(com_argv[4])>=MAX_DEV_NUM)
	{
		printf("\n Flash index number overflow!");
		return -1;
	}
	(nand_in.cs_map)[atoi(com_argv[4])] = 1;
	nand_in.dev = atoi(com_argv[3]);
	nand_in.start = atoi(com_argv[1]);
	nand_in.length= atoi(com_argv[2]);
	API_Nand_Readraw(&nand_in,0);
	return 1;
}

int Handle_nreadoob(void)
{
	int i;

	if (com_argc<5)
	{
		printf("\n Usage:");
		printf(" nreadoob (1) (2) (3) (4) ");
		printf("\n 1:start page number   \
			    \n 2:length in byte    \
				\n 3:device index number \
				\n 4:flash index number ");
		return -1;
	}
	for (i=0;i<MAX_DEV_NUM;i++)
		(nand_in.cs_map)[i] = 0;
	if (atoi(com_argv[4])>=MAX_DEV_NUM)
	{
		printf("\n Flash index number overflow!");
		return -1;
	}
	(nand_in.cs_map)[atoi(com_argv[4])] = 1;
	nand_in.dev = atoi(com_argv[3]);
	nand_in.start = atoi(com_argv[1]);
	nand_in.length= atoi(com_argv[2]);
	API_Nand_Readoob(&nand_in,0);
	return 1;
}

int Handle_nprog(void)
{
	unsigned int i;
	if (com_argc<6)
	{
		printf("\n Usage:");
		printf(" nprog (1) (2) (3) (4) (5) ");
		printf("\n 1:start page number   \
			    \n 2:image file name    \
				\n 3:device index number \
				\n 4:flash index number  \
				\n 5:image type  -n:no oob,-o:with oob no ecc,-e:with oob and ecc");

		return 0;
	}
	for (i=0;i<MAX_DEV_NUM;i++)
		(nand_in.cs_map)[i] = 0;
	if (atoi(com_argv[4])>=MAX_DEV_NUM)
	{
		printf("\n Flash index number overflow!");
		return -1;
	}
	(nand_in.cs_map)[atoi(com_argv[4])] = 1;
	nand_in.start = atoi(com_argv[1]);
	nand_in.dev = atoi(com_argv[3]);
	if (!strcmp(com_argv[5],"-e")) nand_in.option = OOB_ECC;
	else if (!strcmp(com_argv[5],"-o")) nand_in.option = OOB_NO_ECC;
	else nand_in.option = NO_OOB;
		//printf("\n NO_oob");

	API_Nand_Program_File(&nand_in,&nand_out,com_argv[2]);
	printf("\n Flash check result:");
	for (i=0;i<16;i++)
		printf(" %d",(nand_out.status)[i]);
	return 1;
}

int Handle_help(void)
{
	printf("\n Command support in current version:");
	printf("\n help          print this help;");
	printf("\n boot          boot device and make it in stage2;");
	printf("\n list          show current device number can connect;");
	printf("\n fconfig       set USB Boot config file;");
	printf("\n nquery        query NAND flash info;");
	printf("\n nread         read NAND flash data with checking bad block and ECC;");
	printf("\n nreadraw      read NAND flash data without checking bad block and ECC;");
	printf("\n nreadoob      read NAND flash oob without checking bad block and ECC;");
	printf("\n nerase        erase NAND flash;");
	printf("\n nprog         program NAND flash with data and ECC;");
	printf("\n go            execute program in SDRAM;");
	printf("\n version       show current USB Boot software version;");
	printf("\n exit          quit from telnet session;");
	printf("\n readnand      read data from nand flash and store to SDRAM;");
	printf("\n load          load file data to SDRAM;");
	printf("\n nmake         read all data from nand flash and store to file(experimental);");
	return 1;
}

int Handle_version(void)
{
	printf("\n USB Boot Software current version: %s",CURRENT_VERSION);	
	return 1;
}

int Handle_go(void)
{
	unsigned int addr,obj;
	if (com_argc<3)
	{
		printf("\n Usage:");
		printf(" go (1) (2) ");
		printf("\n 1:start SDRAM address \
			    \n 2:device index number");
		return 0;
	}
	if (com_argv[1][0]=='0'&&com_argv[1][1]=='x') addr=HextoDec(&com_argv[1][2]);
	else addr=atol(com_argv[1]);
	obj = atoi(com_argv[2]);
	API_Go(obj,addr);
	return 1;
}

int Handle_fconfig(void)
{
	if (com_argc<3) 
	{
		printf("\n Usage:");
		printf(" fconfig (1) (2) ");
		printf("\n 1:configration file name \
			    \n 2:deivce index number ");
		return -1;
	}
	API_Fconfig(atoi(com_argv[2]),com_argv[1]);
	return 1;
}

int Handle_readnand(void)
{
	unsigned int ram_addr,i;
	if (com_argc<6)
	{
		printf("\n Usage:");
		printf("\n readnand (1) (2) (3) (4) (5) ");
		printf("\n 1:start SDRAM address \
			    \n 2:start page number   \
				\n 3:page length         \
				\n 4:device index number \
				\n 5:flash index number ");

		return -1;
	}
	if (com_argv[1][0]=='0'&&com_argv[1][1]=='x') ram_addr=HextoDec(&com_argv[1][2]);
	else ram_addr=atol(com_argv[1]);
	for (i=0;i<MAX_DEV_NUM;i++)
		(nand_in.cs_map)[i] = 0;
	if (atoi(com_argv[5])>=MAX_DEV_NUM)
	{
		printf("\n Flash index number overflow!");
		return -1;
	}
	(nand_in.cs_map)[atoi(com_argv[5])] = 1;
	nand_in.start = atoi(com_argv[2]);
	nand_in.length = atoi(com_argv[3]);
	nand_in.dev = atoi(com_argv[4]);

	API_Read_Nand_To_Ram(&nand_in,ram_addr);
	return 1;
}

int Handle_Make(void)
{
	if (com_argc<5)
	{
		printf("\n Usage:");
		printf(" nmake (1) (2) (3) (4) ");
		printf("\n 1:start page number   \
				\n 2:page length         \
				\n 3:device index number \
				\n 4:object file name ");

		return -1;
	}
	if (atoi(com_argv[3])>=MAX_DEV_NUM)
	{
		printf("\n Flash index number overflow!");
		return -1;
	}
	nand_in.start = atoi(com_argv[1]);
	nand_in.length = atoi(com_argv[2]);
	nand_in.dev = atoi(com_argv[3]);

	API_Nand_Make(&nand_in,com_argv[4]);
	return 1;
}

int Handle_boot(void)
{
	if (com_argc<2) 
	{
		printf("\n Usage:");
		printf(" boot (1) ");
		printf("\n 1:device index number ");

		return -1;
	}
	API_Boot(atoi(com_argv[1]));
	return 1;
}

int Handle_load()
{
	if (com_argc<4)
	{
		printf("\n Usage:");
		printf(" load (1) (2) (3) ");
		printf("\n 1:SDRAM start address   \
				\n 2:image file name       \
				\n 3:device index number  ");

		return -1;
	}
	if (com_argv[1][0]=='0'&&com_argv[1][1]=='x') 
		sdram_in.start=HextoDec(&com_argv[1][2]);
	else sdram_in.start=atol(com_argv[1]);
	sdram_in.dev = atoi(com_argv[3]);
	sdram_in.buf = code_buf;
	API_Sdram_Load_File(&sdram_in,com_argv[2]);
	return 1;
}

int command_input(char *buf)
{
	//int key;
	//printf("\n USBBoot > ");
	gets(buf);
	if (strlen(buf)>MAX_COMMAND_LENGTH) 
	{
		printf("\n Command is too long! About!");
		buf="";			//set buffer to NULL
		return 0;
	}
	//printf("\n key= %s",buf);
	return 1;
}

int command_interpret(char * com_buf)//,int * com_argc,char *com_argv[])
{
	char *buf=com_buf;
	int i=0,k,j=0,L;
	
	L=(int)strlen(buf);
	buf[L]=' ';
	for (k=0;k<=L;k++)
	{
		//if (*buf=='\r'||*buf=='\n') return 0;
		if (*buf==' '|| *buf=='\n')
		{
			while(*(++buf)==' ');
			com_argv[i][j]='\0';
			i++;
			if (i>9) 
			{
				printf("\n Para is too much! About!");
				return 0;
			}
			j=0;
			continue;
		}
		else
		{
			com_argv[i][j]=*buf;
			j++;
			if (j>100)
			{
				printf("\n Para is too long! About!");
				return 0;
			}
		}
		buf++;
	}
	//if (com_buf[k-1]==' ')com_argc=i; else com_argc=i+1;
	com_argc=i;
	//for (k=0;k<com_argc;k++) printf("\n com_argv[%d]:%s",k,com_argv[k]);

	for (i=1;i<=COMMAND_NUM;i++) 
		if (!strcmp(COMMAND[i],com_argv[0])) return i;
	return COMMAND_NUM+1;
}

int command_handle(char *buf)
{
	int com=1;
	unsigned char t;

	com=command_interpret(buf);
	if (!com) return 1;
		switch (com)
		{
		case 1:		//query
			//printf("\n Here do query!");
			//Handle_query();
			break;
		case 2:		//querya
			//printf("\n Here do querya!");
			//Handle_querya();
			break;
		case 3:		//erase
			//printf("\n Here do erase!");
			//Handle_erase();
			break;
		case 4:		//read
			//printf("\n Here do read!");
			//Handle_read();
			break;
		case 5:		//prog
			//printf("\n Here do prog!");
			//Handle_prog();
			break;
		case 6:		//nquery
			//printf("\n Here do nquery!");
			Handle_nquery();
			break;
		case 7:		//nerase
			//printf("\n Here do nerase!");
			Handle_nerase();
			break;
		case 8:		//nread
			//printf("\n Here do nread!");
			Handle_nread();
			break;
		case 9:		//nreadraw
			//printf("\n Here do nreadraw!");
			Handle_nreadraw();
			break;
		case 10:	//nreadoob
			//printf("\n Here do nreadoob!");
			Handle_nreadoob();
			break;
		case 11:	//nprog
			//printf("\n Here do nprog!");
			Handle_nprog();
			break;
		case 12:	//help
			//printf("\n Here do help!");
			Handle_help();
			break;
		case 13:	//version
			//printf("\n Here do version!");
			Handle_version();
			break;
		case 14:	//go
			//printf("\n Here do go!");
			Handle_go();
			break;
		case 15:	//fconfig
			//printf("\n Here do fconfig!");
			Handle_fconfig();
			break;
		case 16:		//exit
			Exit(1);
			break;
		case 17:
			Handle_readnand();
			break;
		case 18:		//connect
			break;
		case 19:		//disconnect
			break;
		case 20:		//boot
			Handle_boot();
			break;
		case 21 :
			printf("\n Device number can connect :%d",API_Get_Dev_Num());
			break;
		case 22:
			break;
		case 23:
			break;
		case 24:
			break;
		case 25:
			break;
		case 26:
			Handle_Make();
			break;
		case 27:
			Handle_load();
			break;

		default:
				printf("\n Command not support!");
		}
	return 1;
}

////////////////////////////////////////////////////////////////////////
// Main entry point
//
//
//HANDLE	hDevice = INVALID_HANDLE_VALUE;
int __cdecl main(int argc, char *argv[])
{
	char com_buf[100];//,com_argv[100][10];

	printf("\n Welcome!");
	printf("\n USB Boot Host Software!");
	Handle_version();
	API_Init(); 
	printf("\n Handling user command.");
	nand_in.buf = code_buf;
	nand_in.Check = Error_Check;
	nand_in.dev = 0;
	nand_in.cs_map = cs;
	nand_in.max_chip =16;
	//Stage 2
	while (1)
	{
		printf("\n USBBoot :> ");
		if (!command_input(com_buf)) continue;
		command_handle(com_buf);
	}
	return 0;
}
