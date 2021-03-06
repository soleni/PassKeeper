#include "generate.h"
#include "store.h"
#include "colors.h"

#include <stdio.h>
#include <string.h>
#include <unistd.h>

void PrintHelp(){
       printf(YEL "Usage:\n	generate [size] [name]\n	ecrypt\n	exit\n" RESET);
}

void Save_Main(char* GeneratedPass){
	char* FilePath = malloc(256);
	char* PassName = malloc(256);
	char* Pass = "";
	char* EncryptionKey = "";
	
	printf(YEL "Give file path : " RESET);
	scanf("%s", FilePath);
	printf("\n");

	printf(YEL "Give Password Name : " RESET);
	scanf("%s", PassName);
	printf("\n");

	char* temp;

	Pass = malloc(strlen(GeneratedPass));
	strcpy(Pass, GeneratedPass);

	while(strlen(Pass) == 0){
		temp = getpass(YEL "Give password : " RESET);
		Pass = malloc(strlen(temp));
		strcpy(Pass, temp);
	}

	while(strlen(EncryptionKey) == 0){
		temp = getpass(YEL "Give key : " RESET);
		EncryptionKey = malloc(strlen(temp));
		strcpy(EncryptionKey, temp);
	}

	if(SAVE(FilePath, PassName, Pass, EncryptionKey) != 0){
		printf(RED "FILE I/O ERROR!\n" RESET);
	}
}

void Read_Main(){
	char* FilePath = malloc(256);
	char* EncryptionKey = "";

	printf(YEL "Give file path : " RESET);
	scanf("%s", FilePath);
	printf("\n");
	
	char* temp;
	while(strlen(EncryptionKey) == 0){
		temp = getpass(YEL "Give key : " RESET);
		EncryptionKey = malloc(strlen(temp));
		strcpy(EncryptionKey, temp);
	}
	
	char** Output = READ(FilePath, EncryptionKey); 
	if(Output != NULL){
		printf(GRN "Success!\n" RESET);
		
		int i = 0;
		while(Output[i] != NULL){
			printf("%s\n", Output[i]);
			i++;
		}
	}
	else{
		printf(GRN "Error!\n" RESET);
	}
}

void Generate_Main(int argc, char **argv){
	int size = 8;

	if(argc > 2) size = atoi(argv[2]);

	char* Pass;
	char* temp = generate(size > 8 ? size : 8);
	Pass = malloc (strlen(temp));
	strcpy(Pass, temp);
               
	printf(GRN "Password is: %s\n" RESET, Pass);

	printf(YEL "Do you want to save it?\n[Y]es\\[N]o\n" RESET);

	char answer;
	scanf("%c", &answer);

	if(answer == 'Y' || answer == 'y'){
		Save_Main(Pass);
	}
}

int main(int argc, char **argv){
        if(argc == 1){
		PrintHelp();
		return 0;
        }
        if(strcmp(argv[1],"generate") == 0){
		Generate_Main(argc, argv);
        }
	if(strcmp(argv[1],"save") == 0){
		Save_Main("");
	}
	if(strcmp(argv[1],"read") == 0){
		Read_Main();
	}
}
