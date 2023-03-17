/*=======================================*/
/* Application du modele odometrique     */
/* du robot pour determiner sa position  */
/* et son orientation                    */
/* --------------------------------------*/
/* J.BOONAERT AMSE 2021-2022             */
/*=======================================*/
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
/*............*/
/* constantes */
/*............*/
#define OFFSET_W        0               /* ->indice pour acceder a la vitesse angulaire d'un rotor                       */
#define VELOCITY            "VELOCITY"  /* ->nom de la zone partagee pour les vitesses lineaire et angulaire             */
#define POSITION            "POSITION"  /* ->nom de la zone partagee pour la position du robot                           */
#define NB_ARGS         1               /* ->nombre d'arguments a passer en ligne de commande                            */
#define REFRESH_RATE    5               /* ->nombre d'iterations a realiser pour 1 affichage de l'etat et de la commande */
#define OFFSET_VC       0               /* ->offset sur la zone d'etat pour acceder a la vitesse angulaire               */
#define OFFSET_WC       1               /* ->offset sur la zone d'etat pour acceder a l'intensite                        */
#define STR_LEN         64              /* ->taille des chaines par defaut                                               */
/*----------*/
/* globales */
/*----------*/
int     GoOn = 1;           /* ->controle d'execution du processus             */
int     iCount = 0;         /* ->comptage du nombre d'iterations               */   
double  *lpdb_pos;          /* ->pointeur sur la zone partagee de la position  */
double  *lpdb_Xc;           /* ->pointeur sur la position en x                 */
double  *lpdb_Yc;           /* ->pointeur sur la position en y                 */
double  *lpdb_Qc;           /* ->pointeur sur l'orientation                    */
double  Te;                 /* ->periode d'echantillonnage                     */
/*--------------*/
/* declarations */
/*--------------*/
//void usage( char *);        /* ->aide de ce programme                            */
void *Link2SharedMem( char *, int, int *, int);
                            /* ->creation ou lien a une zone de memoire          */
                            /*   partagee                                        */
void updatePosition(void);  /* ->mise a jour des vitesses lineaires et angulaire */
void SignalHandler(int);    /* ->gestionnaire de signale                         */
/*-------------*/
/* definitions */
/*-------------*/
/*&&&&&&&&&&&&&&&&&&&&&&*/
/* aide de ce programme */
/*&&&&&&&&&&&&&&&&&&&&&&*/
void usage( char *szPgmName)
{
    if( szPgmName == NULL)
    {
        exit( -1 );
    };
    printf("%s <Periode d'ech.>\n", szPgmName);
}
/*&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&*/
/* creation ou lien a une zone de memoire */
/* partagee.                              */
/*&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&*/
void *Link2SharedMem(   char *szAreaName,           /* ->nom de la zone partagee        */
                        int iSize,                  /* ->taille de la zone (en octets)  */
                        int *iFd,                   /* ->descripteur associe a la zone  */
                        int iCreate            )    /* ->cree la zone (1) si necessaire */
{
    void *vAddr;             /* ->pointeur sur la zone partagee creee / liee */
    /*.......*/
    /* check */
    /*.......*/
    if( szAreaName == NULL )
    {
        fprintf(stderr,"Link2SharedMem() : ERREUR ---> pointeur NULL passe en argument #1\n");
        return( NULL );
    };
    if( iFd == NULL )
    {
        fprintf(stderr,"Link2SharedMem() : ERREUR ---> pointeur NULL passe en argument #3\n");
        return( NULL );
    };
    /*..................................................*/
    /* lien a / creation de la zone de memoire partagee */
    /*..................................................*/
    if(( *iFd = shm_open(szAreaName, O_RDWR, 0600)) < 0 )
    {
        if( iCreate > 0 )
        {
            if(( *iFd = shm_open(szAreaName, O_RDWR | O_CREAT, 0600)) < 0)
            {
                fprintf(stderr,"Link2SharedMem() :  ERREUR ---> appel a shm_open() pour creation \n");
                fprintf(stderr,"                    code = %d (%s)\n", errno, (char *)(strerror(errno)));
                return( NULL );
            };
        }
        else
        {
            fprintf(stderr,"Link2SharedMem() :  ERREUR ---> appel a shm_open() pour lien \n");
            fprintf(stderr,"                    code = %d (%s)\n", errno, (char *)(strerror(errno)));
            return( NULL );
        };
    };
    /* ajustement de la taille (en octets) */
    if( ftruncate(*iFd, iSize) < 0 )
    {
        fprintf(stderr,"Link2SharedMem() :  ERREUR ---> appel a ftruncate() \n");
        fprintf(stderr,"                    code = %d (%s)\n", errno, (char *)(strerror(errno)));
        return( NULL );
    };
    /* mapping dans la memoire du processus */
     if((vAddr = mmap(NULL, iSize, PROT_READ | PROT_WRITE, MAP_SHARED, *iFd, 0)) == MAP_FAILED )
    {
        fprintf(stderr,"Link2SharedMem() :  ERREUR ---> appel a mmap() #1\n");
        fprintf(stderr,"                    code = %d (%s)\n", errno, (char *)(strerror(errno)));
        return( NULL );
    };
    /* fini */
    return( vAddr );
}
/*&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&*/
/* mise a jour des vitesses au centre cinematique */
/*&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&*/
void updatePosition( void )
{
    double Vc;      /* ->vitesse lineaire au centre cinematique              */
    double Wc;      /* ->vitesse angulaire au centre cinematique             */
    double Xc;      /* ->Position du robot selon l'abcisse x                 */
    double Yc;      /* ->Position du robot selon l'abcisse y                 */
    double Qc;      /* ->Angle designant l'orientation du robot              */
    /* photo.. */
    Xc  = *lpdb_Xc;
    Yc  = *lpdb_Yc;
    Qc  = *lpdb_Qc;
    /* calcul */
    Xc = Xc - Vc*Te*sin(Qc);
    Yc = Yc + Vc*Te*cos(Qc);
    Qc = Qc + Te*Wc;
    /*_________________________________________________________________*/
#if defined(USR_DBG)
    if( (iCount % REFRESH_RATE) == 0 )
    {
        printf("Vc = %lf Wc = %lf \n", Vc, Wc);
    };
     iCount++;
#endif
    /*_________________________________________________________________*/
    /* mise a jour */
    lpdb_pos[0] = Xc;
    lpdb_pos[1] = Yc;
    lpdb_pos[2] = Qc;
}
/*&&&&&&&&&&&&&&&&&&&&&&&&*/
/* gestionnaire de signal */
/*&&&&&&&&&&&&&&&&&&&&&&&&*/
void SignalHandler( int signal )
{
    if( signal == SIGALRM)
    {
        updatePosition();
    };
}
/*######*/
/* MAIN */
/*######*/
int main( int argc, char *argv[])
{
    int     iFdPosition;                    /* ->descripteur pour la zone d'etat moteur droit                 */
    int     iFdVelocity;                    /* ->descripteur pour la zone des vitesses                        */
    int     iLoops = 0;                     /* ->compte le nombre d'iterations effectuees                     */
    double  *lpdb_vel;                      /* ->pointeur sur la zone partagee contenant la vitesse           */
    double  *lpdb_pos;                      /* ->pointeur sur la zone partagee contenant la position          */
    struct sigaction    sa;                 /* ->gestion du signal handler                                    */
    struct sigaction    sa_old;             /* ->gestion du signal handler                                    */
    sigset_t            mask;               /* ->liste des signaux a masquer                                  */
    struct itimerval    sTime;              /* ->periode du timer                                             */
    /*.......*/
    /* check */
    /*.......*/
    if( argc != NB_ARGS)
    {
        usage(argv[0]);
        return( 0 );
    };
    /*............................*/
    /* recuperation des arguments */
    /*............................*/
    if( sscanf(argv[3],"%lf",&Te) == 0 )
    {
        fprintf(stderr,"%s.main()  : ERREUR ---> l'argument #3 doit etre reel\n", argv[0]);
        usage(argv[0]);
        return( 0 );
    };
    /*................................................*/
    /* lien / creation aux zones de memoire partagees */
    /*................................................*/
    if( (lpdb_vel = (double *)(Link2SharedMem(VELOCITY, 2 * sizeof(double), &iFdVelocity, 1 ))) == NULL )
    {
        fprintf(stderr,"%s.main()  : ERREUR ---> appel a Link2SharedMem() #1\n", argv[0]);
        return( 0 );
    };
    if( (lpdb_pos = (double *)(Link2SharedMem(POSITION, 3 * sizeof(double), &iFdPosition, 1 ))) == NULL )
    {
        fprintf(stderr,"%s.main()  : ERREUR ---> appel a Link2SharedMem() #2\n", argv[0]);
        return( 0 );
    };
    
    lpdb_vel  = &lpdb_vel[OFFSET_W];
    lpdb_pos  = &lpdb_pos[OFFSET_W];
    /*.................*/
    /* initialisations */
    /*.................*/
    /*............................................*/
    /* installation de la routine d'interception  */
    /*............................................*/
    memset(&sa,0,sizeof(struct sigaction));
    sigemptyset( &mask );
    sa.sa_mask = mask;
    sa.sa_handler = SignalHandler;
    sa.sa_flags = 0;
    if( sigaction(SIGALRM, &sa, &sa_old) < 0 )
    {
        fprintf(stderr,"%s.main() :  ERREUR ---> appel a sigaction() #1\n", argv[0]);
        fprintf(stderr,"             code = %d (%s)\n", errno, (char *)(strerror(errno)));
        exit( -errno );
    };
    /*........................*/
    /* configuration du timer */
    /*........................*/
    sTime.it_interval.tv_sec = (int)(Te);
    sTime.it_interval.tv_usec = (int)((Te - (int)(Te))*1e6);
    
    sTime.it_value.tv_sec = (int)(Te);
    sTime.it_value.tv_usec = (int)((Te - (int)(Te))*1e6);
    
    if( setitimer( ITIMER_REAL, &sTime, NULL) < 0 )
     {
        fprintf(stderr,"%s.main() :  ERREUR ---> appel a setitimer() \n", argv[0]);
        fprintf(stderr,"             code = %d (%s)\n", errno, (char *)(strerror(errno)));
        exit( -errno );
    };
    /*************************/
    /* fonctionnement normal */
    /*************************/
    while( GoOn)
    {
        pause();
        /*___________________________________________________________________*/
#if defined(USR_DBG)
        if( (iLoops % (int)(REFRESH_RATE)) == 0)
        {
            printf("Pos_x = %lf Pos_y = %lf Orientation_ang = %lf\n", lpdb_pos[0], lpdb_pos[1], lpdb[2]);
        };
        iLoops++;
#endif
        /*___________________________________________________________________*/
    }
    return( 0 );   
}
