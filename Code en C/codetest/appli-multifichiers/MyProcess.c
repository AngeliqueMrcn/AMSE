/* fonction de creation d'un processus sous Linux */
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <errno.h>
/* declarations */
pid_t	CreateProcess( char *, char **, char **);
/* definitions */
/*&&&&&&&&&&&&&&&&&&&&&&&*/
/* creation de processus */
/*&&&&&&&&&&&&&&&&&&&&&&&*/
pid_t CreateProcess( char *szPgmName,		/* ->chemin d'acces complet au programme */
					 char **tszArgv,		/* ->arguments passes au processus       */
					 char **tszEnvp     )	/* ->variables d'environnement           */
{
	pid_t	IDSon;
	/* verification des arguments */
	if( ( szPgmName == NULL)||(tszArgv == NULL)||(tszEnvp == NULL) )
	{
		fprintf(stderr,"CreateProcess() : ERREUR --->pointeur(s) NULL passe(s) en argument\n");
		return( (pid_t)(-1) );
	};
	if( (IDSon = fork()) == 0)
	{
		execve( szPgmName, tszArgv, tszEnvp);
	};
	/* alternative cote pere */
	if( (int)(IDSon) < 0 )
	{
		fprintf(stderr,"CreateProcess() : ERREUR ---> appel a fork()\n");
		fprintf(stderr,"code d'erreur = %d (%s)\n", errno, strerror(errno));
		return( IDSon) ;
	};
	/*  OK */
	return( IDSon );
}
