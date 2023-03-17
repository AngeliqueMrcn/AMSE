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
    double consigne_rotation;
    double *lpdb_stateR; 
    double *lpdb_stateL;
    double err_rotation;
    double *pos_rot;
    double rot;
    rot = pos_rot;

    /*............................*/
    /* recuperation des arguments */
    /*............................*/
    if( sscanf(argv[0],"%lf",&consigne_rotation) == 0 )
    {
        fprintf(stderr,"%s.main()  : ERREUR ---> l'argument #1 doit etre reel\n", argv[0]);
        usage(argv[0]);
        return( 0 );
    };
    if( sscanf(argv[1],"%lf",&err_rotation) == 0 )
    {
        fprintf(stderr,"%s.main()  : ERREUR ---> l'argument #2 doit etre reel\n", argv[1]);
        usage(argv[1]);
        return( 0 );
    };
    if( sscanf(argv[1],"%lf",&Tv) == 0 )
    {
        fprintf(stderr,"%s.main()  : ERREUR ---> l'argument #1 doit etre reel\n", argv[0]);
        usage(argv[0]);
        return( 0 );

    /*****************************/
    /* mise a zero de la vitesse */
    /*****************************/
    if( rot < consigne_rotation + err_rotation && rot > consigne_rotation - err_rotation){
        lpdb_stateR[0] = 0;
        lpdb_stateR[1] = 0;
        lpdb_stateL[0] = 0;
        lpdb_stateL[1] = 0;
    }
    /* reduction de la vitesse */
    else if(rot < consigne_rotation + err_rotation*100 && rot > consigne_rotation - err_rotation*100){
        lpdb_stateR[0] = lpdb_stateR[1]/5;
        lpdb_stateL[0] = - lpdb_stateL[1]/5;
    }
    /* fonctionnement normal */
    else{
        lpdb_stateL[0] = - 1;
        lpdb_stateR[0] = 1;
    }
    return (0);
}