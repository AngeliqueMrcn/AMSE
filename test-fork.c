/* test de la combinaison de fork() avec execv() */
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <errno.h>
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
	/* creation du fils avec fork() ! */
	if( (IDSon = fork()) == 0 )
	{
		execve(PGM_NAME, tszArgv, tszEnvp );
	}
	else
	{	
		if( IDSon < 0 )
		{
			fprintf(stderr,"%s.main() : ERREUR --> appel a fork().\n", argv[0] );
			fprintf(stderr,"code d'erreur = %d (%s)\n", errno, (char *)(strerror(errno)));
			return( -errno );
		};
	};
	printf("processus fils lance avec succes...\n");
	return( 0 );
}

	
	
	
