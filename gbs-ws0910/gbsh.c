#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <dirent.h>
char marker[1024];
#define command_size 50
char command[command_size];
char cwd[1024];//home directory

void cd(char *command)
{
	char *cd=getenv("PWD");
	if(!command)
	{
	strcpy(cd,cwd);//go back to home directory
	return;
	}
	DIR *dp=NULL;
	struct dirent *sd=NULL;	
	char pointer[100];
	strcpy(pointer,cd);
	dp = opendir((const char*)cd);//going into desired folder

	while((sd=readdir(dp))!=NULL)
	{

	if(!strcmp(sd->d_name,command))
	{
		strcat(pointer,"/");
		//DIR *dir=
		strcat(pointer,(char*)sd->d_name);
		strcpy(cd,pointer);
		return;
	}	
	}
closedir(dp);
//strcpy(cd,cwd);//not going back to current directory
}

void lsd(char *command)
{
	char *cd=getenv("PWD");
	strcat(cd,"/");
	char *pointer=NULL;
	DIR *dp=NULL;
	struct dirent *sd=NULL;	
	pointer = getenv("PWD");
	dp = opendir((const char*)pointer);//going into desired folder
	while((sd=readdir(dp))!=NULL)
	{
	if(!strcmp(sd->d_name,command))
	{
		//DIR *dir=
		strcat(cd,sd->d_name);
		ls(cd);
	}	
	}
closedir(dp);
strcpy(cd,cwd);//going back to current directory
}

void ls(char *pointer)
{
	if(!pointer)
	{
	
	pointer = getenv("PWD");
	printf("%s\n\n",pointer);
	}
	struct dirent *sd=NULL;	
	DIR *dp=NULL;
	dp = opendir((const char*)pointer);
	while((sd=readdir(dp))!=NULL)
	{
	printf("%s\n",sd->d_name);
	}
closedir(dp);
return 0;
}

void checkCommand(char *command)
{
	
	if(!strcmp(command,"pwd"))
	{
		printf("%s",cwd);
	}
	else if(!strcmp(command,"clear"))
	{
		printf("\033[H\033[J");
	}
	else if(!strcmp(command,"ls"))
	{
		ls(NULL);
	}	
	else if(!strncmp(command,"ls ",3)&&command[4]!='\0')
	{
		lsd(command+3);
	}
	else if(!strcmp(command,"cd"))
	{
		cd(NULL);
	}
	else if(!strncmp(command,"cd ",3)&&command[4]!='\0')
	{
		cd(command+3);
	}	
}

void promptloop()
{int len;
getcwd(cwd,1024);
	while(1)
	{
	fprintf(stdout, "\n");
	fprintf(stdout, marker);
	fgets(command,command_size,stdin);
	len=strlen(command);
	if(command[len-1]=='\n') command[len-1]='\0';
	if(!strcmp(command,"exit"))
	{
		break;
	}
	else
	{
		checkCommand(command);
	}
	}
}
const char* getstring(){
	
	char *user;
	char host[20];
	char cwd[100];
	
	user=getlogin();
	gethostname(host,20);
	getcwd(cwd,1024);
	strcpy(marker,user);
	strcat(marker,"@");
	strcat(marker,host);
	strcat(marker," ");
	strcat(marker,cwd);
	strcat(marker," ");

}
int main(int argc, char *argv[]) {
	getstring();
	promptloop();
	// shell code here
	
	// ...
	
	// ...
	return 0; // exit normally	
}
