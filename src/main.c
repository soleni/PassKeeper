#include "generate.h"
#include "encrypt.h"
#include "store.h"

#include <stdio.h>
#include <string.h>
#include <unistd.h>

const char NEW = 0;
const char PASS = 1;

#define RED   "\x1B[31m"
#define GRN   "\x1B[32m"
#define YEL   "\x1B[33m"
#define BLU   "\x1B[34m"
#define MAG   "\x1B[35m"
#define CYN   "\x1B[36m"
#define WHT   "\x1B[37m"
#define RESET "\x1B[0m"

void PrintHelp(){
       printf("Usage:\n	generate [size] [name]\n	ecrypt\n	exit\n");
}

void Save_Main(int argc, char **argv , char flag , char* GeneratedPass){
	char* FilePath = malloc(256);
	char* PassName = malloc(50);
	char* Pass = "";
	char* EncryptionKey = "";
	
	printf(YEL "Give file path : " RESET);
	scanf("%s" , FilePath);
	printf("\n");

	printf(YEL "Give Password Name : " RESET);
	scanf("%s" , PassName);
	printf("\n");

	char* temp;

	Pass = malloc(strlen(GeneratedPass));
	strcpy(Pass , GeneratedPass);

	while(strlen(Pass) == 0 && flag == 0){
		temp = getpass(YEL "Give password : " RESET);
		Pass = malloc(strlen(temp));
		strcpy(Pass , temp);
	}

	while(strlen(EncryptionKey) == 0){
		temp = getpass(YEL "Give key : " RESET);
		EncryptionKey = malloc(strlen(temp));
		strcpy(EncryptionKey , temp);
	}

	printf(CYN "[DEBUG]: %s , %s , %s , %s\n" RESET , FilePath , PassName , Pass , EncryptionKey);

	if(SAVE(FilePath , PassName , Pass , EncryptionKey) == 0){
		printf(GRN "	Success!\n" RESET);
	}
	else{
		printf(RED "	FILE I/O ERROR!\n" RESET);
	}
}

int main(int argc, char **argv){
        char *LookUp[3] = {"help" , "generate" , "exit"};
        if(argc == 1){
		PrintHelp();
		return 0;
        }
        if(strcmp(argv[1],"generate") == 0){
		int size = 8;
		if(argc > 2) size = atoi(argv[2]);
		char* Pass;
		char* temp = generate(size > 8 ? size : 8);
		Pass = malloc (strlen(temp));
		strcpy(Pass , temp);
                
		printf("password is: %s\n",Pass);

		printf("Do you want to save it?\n[Y]es\\[N]o");
		char answer;
		scanf("%c" , &answer);
		if(answer == 'Y' || answer == 'y'){
			Save_Main(argc , argv , PASS , Pass);
		}
        }
	if(strcmp(argv[1],"save") == 0){
		Save_Main(argc , argv , NEW , "");
	}
	if(strcmp(argv[1],"read") == 0){
		char* FilePath = malloc(256);
		char* EncryptionKey = "";
		
		printf("Give file path\n");
		scanf("%s" , FilePath);

		char* temp;
		while(strlen(EncryptionKey) == 0){
			temp = getpass("give key:\n");
			EncryptionKey = malloc(strlen(temp));
			strcpy(EncryptionKey , temp);
		}

		if(READ(FilePath , EncryptionKey) == 0){
			printf("success!\n");
		}
		else{
			printf("error!\n");
		}
	return 0;
	}
}
