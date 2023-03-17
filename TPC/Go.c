#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include <fcntl.h>
#include <signal.h>
#include <errno.h>
#include <sys/mman.h>
#include <sys/time.h>
#include <math.h> 


/*######*/
/* MAIN */
/*######*/
int main( int argc, char *argv[]){
    
    double *lpdb_stateR; 
    double *lpdb_stateL;
    double *pos_x;
    double *pos_y;
    double x;
    double y;
    int c;
    double initx;
    double inity;
    int *count;
    double consigne;  //consigne de position du robot
    double err_consigne;
    c = count;
    x = pos_x;
    y = pos_y;

    /*............................*/
    /* recuperation des arguments */
    /*............................*/

    if( sscanf(argv[0],"%lf",&consigne) == 0 )
    {
        fprintf(stderr,"%s.main()  : ERREUR ---> l'argument #1 doit etre reel\n", argv[0]);
        usage(argv[0]);
        return( 0 );
    };
    if( sscanf(argv[1],"%lf",&err_consigne) == 0 )
    {
        fprintf(stderr,"%s.main()  : ERREUR ---> l'argument #1 doit etre reel\n", argv[1]);
        usage(argv[1]);
        return( 0 );
    };
    if( sscanf(argv[1],"%lf",&Tv) == 0 )
    {
        fprintf(stderr,"%s.main()  : ERREUR ---> l'argument #1 doit etre reel\n", argv[0]);
        usage(argv[0]);
        return( 0 );

    if((count = (double *)(mmap(NULL, sizeof(double), PROT_READ | PROT_WRITE, MAP_SHARED, iFdTarget, 0))) == MAP_FAILED )
    {
        fprintf(stderr,"%s.main() :  ERREUR ---> appel a mmap() #1\n", argv[0]);
        fprintf(stderr,"             code = %d (%s)\n", errno, (char *)(strerror(errno)));
        exit( -errno );
    };
    /******************/
    /* Initialisation */
    /******************/
    if(c == 0){
        initx = 0;
        inity = 0
    }
    /* mise a zero de la vitesse */
    if( sqrt((x-initx)*(x-initx) + (y-inity)*(y-inity)) < consigne + err_consigne && sqrt((x-initx)*(x-initx) + (y-inity)*(y-inity)) > consigne - err_consigne){
        lpdb_stateR[0] = 0;
        lpdb_stateR[1] = 0;
        lpdb_stateL[0] = 0;
        lpdb_stateL[1] = 0;
        initx = *pos_x;
        inity = *pos_y;
        c = 1;
    }
    /* reduction de la vitesse */
    else if(sqrt((x-initx)*(x-initx) + (y-inity)*(y-inity)) < consigne + err_consigne*10 && sqrt((x-initx)*(x-initx) + (y-inity)*(y-inity)) > consigne - err_consigne*10){
        lpdb_stateR[0] = lpdb_stateR[0]/5;
        lpdb_stateL[0] = lpdb_stateL[0]/5;
        c = 1;
    }
    /* fonctionnement normal */
    else{
        lpdb_stateL[0] = 1;
        lpdb_stateR[0] = 1;  
        c = 1;
    }
    return (0);
}