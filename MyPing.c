/* programme affichant "PING" a la reception du signal   */
/* SIGUSR1                                               */
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>		/* ->gestion des signaux */
void SignalHandler( int );
/* definitions */
void SignalHandler( int signal )
{
	if( signal == SIGUSR1 )
	{
		printf("PING\n");
	};
}
/*=====================*/
/* programme principal */
/*=====================*/
int main( void )
{
	struct sigaction	sa,	/* ->configuration de l'interception du signal */
				sa_old; /* ->sauvegarde de l'ancienne interception  */

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
	sigaction( SIGUSR1, &sa, &sa_old );
	/* attente des signaux */
	do
	{
		pause();
	}
	while( 1 );
	return( 0 );
}


