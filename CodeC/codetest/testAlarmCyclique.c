/* test d'une alarme */
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <signal.h>		/* ->gestion des signaux          */
#include <sys/time.h>   /* ->timer                        */

#define TE          1.0 /* ->periode de l'alarme cyclique */

int hh = 0;             /* ->heures   */
int mm = 0;             /* ->minutes  */
int ss = 0;             /* ->secondes */

void SignalHandler( int );
/* definitions */
void SignalHandler( int signal )
{
	if( signal == SIGALRM )
	{
		ss++;
        if( ss > 59 )
        {
            ss = 0;
            mm++;
            if( mm > 59)
            {
                mm = 0;
                hh++;
                if( hh > 23 )
                {
                    hh = 0;
                };
            };
        };
	};
}
/*=====================*/
/* programme principal */
/*=====================*/
int main( int argc, char *argv[] )
{
	struct sigaction	sa,	/* ->configuration de l'interception du signal */
				sa_old; /* ->sauvegarde de l'ancienne interception  */
    char    cRep;       /* ->caractere a saisir */
	sigset_t 		sa_mask; /* ->liste des  signaux qui seront masques */
	struct itimerval    sTime;              /* ->periode du timer*/
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
    /*........................*/
    /* configuration du timer */
    /*........................*/
    sTime.it_interval.tv_sec = (int)(TE);
    sTime.it_interval.tv_usec = (int)((TE - (int)(TE))*1e6);
    
    sTime.it_value.tv_sec = (int)(TE);
    sTime.it_value.tv_usec = (int)((TE - (int)(TE))*1e6);
    
    if( setitimer( ITIMER_REAL, &sTime, NULL) < 0 )
     {
        fprintf(stderr,"%s.main() :  ERREUR ---> appel a setitimer() \n", argv[0]);
        fprintf(stderr,"             code = %d (%s)\n", errno, (char *)(strerror(errno)));
        exit( -errno );
    };
	/* attente des signaux */
	do
	{
        pause();
        printf("%02d:%02d:%02d\n", hh,mm,ss);
	}
	while( 1 );
	return( 0 );
}


