/* test d'une alarme */
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>		/* ->gestion des signaux */
#define DUREE        10

int GoOn = 1;           /* ->controle d'execution de la boucle dans main() */
void SignalHandler( int );
/* definitions */
void SignalHandler( int signal )
{
	if( signal == SIGALRM )
	{
		printf("TROP TARD !!\n");
        GoOn = 0;
	};
}
/*=====================*/
/* programme principal */
/*=====================*/
int main( void )
{
	struct sigaction	sa,	/* ->configuration de l'interception du signal */
				sa_old; /* ->sauvegarde de l'ancienne interception  */
    char    cRep;       /* ->caractere a saisir */
	sigset_t 		sa_mask; /* ->liste des  signaux qui seront masques */
	/* initialisation */
	memset( &sa, 0, sizeof( struct sigaction));
	memset( &sa_old, 0, sizeof( struct sigaction));
	/*  mise a jour de  sa */
	sigemptyset( &sa_mask );
	sa.sa_flags = 0;
	sa.sa_mask  = sa_mask;
	sa.sa_handler =  SignalHandler;
	/* installation de la routine d'interception */
	sigaction( SIGALRM, &sa, &sa_old );
	/* attente des signaux */
	do
	{
        alarm( DUREE );/* ->reception du signal SIGALRM dans DUREE seconde */
        printf("vous avez %d secondes pour saisir un caractere...\n", DUREE);
        scanf("%c", &cRep);
		alarm(0);
	}
	while( GoOn );
	return( 0 );
}


