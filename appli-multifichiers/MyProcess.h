/* declaration fonction de creation d'un processus sous Linux */
/* (exemple de compilation conditionnelle)                    */
#if !defined(MYPROCESS_)        /* ->SI la constante MYPROCESS_ n'est PAS definie ... */
#define MYPROCESS_              /* ... alors on la definit et on compile tout le code */
#include <unistd.h>             /* jusqu'au #endif                                    */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <errno.h>
/* declarations */
extern pid_t	CreateProcess( char *, char **, char **);
#endif
