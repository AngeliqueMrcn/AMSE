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
/* constantes */
#define STR_LEN       256   /* ->taille  de la zone */
/* declarations */
void usage( char *);        /* ->aide de programme  */
/*&&&&&&&&&&&&&&&&&&&&&&*/
/* aide de ce programme */
/*&&&&&&&&&&&&&&&&&&&&&&*/
void usage( char *szPgmName )
{
    if( szPgmName == NULL )
    {
        exit( -1 );
    };
    printf("%s <nom de la zone>\n", szPgmName );
}
/*######*/
/* MAIN */
/*######*/
int main( int argc, char *argv[] )
{
    int     iArea;      /* ->file descriptor sur la zone partagee */
    char    *szString;  /* ->chaine stockee dans la zone partagee */
    /* verification de s arguments */
    if( argc != 2)
    {
        usage( argv[0]);
        return( 0 );
    };
    /* creation de la zone partagee */
    if(( iArea = shm_open(argv[1], O_RDWR | O_CREAT, 0600)) < 0)
    {
        fprintf(stderr,"%s.main() :  ERREUR ---> appel a shm_open() #1\n", argv[0]);
        fprintf(stderr,"             code = %d (%s)\n", errno, (char *)(strerror(errno)));
        exit( -errno );
    }
    else
    {
        printf("CREATION de la zone %s\n", argv[1]);
    };
    /* ajustement de la taille de la zone partagee */    
    if( ftruncate(iArea, STR_LEN) < 0 )
    {
        fprintf(stderr,"%s.main() :  ERREUR ---> appel a ftruncate() #1\n", argv[0]);
        fprintf(stderr,"             code = %d (%s)\n", errno, (char *)(strerror(errno)));
        exit( -errno );
    };
    /* obtention d'un pointeur sur la zone et transtypage */
    if((szString = (char *)(mmap(NULL, STR_LEN, PROT_READ | PROT_WRITE, MAP_SHARED, iArea, 0))) == MAP_FAILED )
    {
        fprintf(stderr,"%s.main() :  ERREUR ---> appel a mmap() #1\n", argv[0]);
        fprintf(stderr,"             code = %d (%s)\n", errno, (char *)(strerror(errno)));
        exit( -errno );
    };
    /* on saisie une chaine jusqu'a ce qu'on entre STOP */
    do
    {
        fflush( stdin );
        scanf("%s", szString);
    }
    while( strcmp(szString, "STOP") != 0);
    /* OK */
    munmap( szString, STR_LEN );
    close( iArea);
    return( 0 );
}