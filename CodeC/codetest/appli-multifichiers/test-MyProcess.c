/* test de la combinaison de fork() avec execv() */
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <errno.h>

#include "MyProcess.h"  /* ->cette fois ci, la fonction est definie dans un autre fichier */
/* parametres par defaut pour le lancement du fils */
#define PGM_NAME 	"/home/debian/AMSE/bin/test-execve"
#define DEFAULT_FREQ	3.0
#define DEFAULT_AMP	2.0
#define STR_LEN		256
/* lancement d'un fils avec fork() */
int main(int argc, char *argv[], char *envp[])
{
	double a,f;		/* ->frequence et amplitude     */
	int 	i;		/* ->compteur de boucle         */
	int 	iNbEnvp;	/* ->nombre d'entrees dans envp */
	int 	IDSon;		/* ->PID du fils..              */
	char **tszArgv;
	char **tszEnvp;
	/* initialisation */
	a = (double)(DEFAULT_AMP);
	f = (double)(DEFAULT_FREQ);
	/* allocations */
	tszArgv = (char **)calloc(4, sizeof(char **));
	for(i=0; i < 3; i++ )
	{
		tszArgv[i] = (char *)calloc(STR_LEN, sizeof( char ));
	};
	/* on compte le nombre de definitions dans envp : */
	iNbEnvp = 0;
	while( envp[iNbEnvp] != NULL )
	{
		iNbEnvp++;
	};
	tszEnvp = (char **)calloc(iNbEnvp+1, sizeof( char *));
	for(i=0; i < iNbEnvp; i++ )
	{
		tszEnvp[i] = (char *)calloc(STR_LEN, sizeof(char));
		sprintf(tszEnvp[i],"%s", envp[i]);
	};
	sprintf(tszArgv[0],"%s", PGM_NAME );
	sprintf(tszArgv[1],"%lf", a);
	sprintf(tszArgv[2],"%lf", f);

	tszEnvp[i] = NULL;
	/* creation du fils avec CreateProcess()  */
	IDSon = CreateProcess( PGM_NAME, tszArgv, tszEnvp);
	if( (int)(IDSon) >= 0)
	{
		printf("processus fils lance avec succes...\n");
	}
	else
	{
		printf("echec de l'appel a CreateProcess()...\n");
	};
	return( 0 );
}

	
	
	
