//## Module : YmIrGlobal
//SFD
// Name	    : YmIrGlobal.h
// Author   : 
// Desc     : Contient l'ensemble des variables et define globaux
//EDF

#ifndef YMIRGLOBAL_H
#define YMIRGLOBAL_H


//## Includes
#include <vector>
#include <map>
#include "YmMessLog.h"
/* Threads includes */
#ifdef POSIX_THREAD
#include <pthread.h>
#else
#include <thread.h>
#endif


//## Define
#define ZERO_EPSILON (double) .00001
/* Threads defines */
#ifdef  POSIX_THREAD
#define LOCK_MUTEX(s) pthread_mutex_lock(s)
#define UNLOCK_MUTEX(s) pthread_mutex_unlock(s)
#define THR_SELF() pthread_self()
#else
#define LOCK_MUTEX(s) mutex_lock(s)
#define UNLOCK_MUTEX(s) mutex_unlock(s)
#define THR_SELF() thr_self()
#endif
/* Nombre maximum de buckets par compartiment */
#define BUCK_MAX 20
#define CMPT_MAX 5
#define SCX_MAX 7
#define YMBA_INVALID_LONG -999999
/* 24 Heures * 3600 secondes */
#define NEXT_DAY_IN_SECONDS 86400
/* 19961014 = 01/01/2000 */
#define INIT_YMDATE "19961014"
#define CRITICALITY_MIN_CRITICAL 1
#define CRITICALITY_MAX_CRITICAL 10
#define CRITICALITY_MIN_COMMERCIAL 50
#define CRITICALITY_MAX_COMMERCIAL 70
#define CRITICALITY_MACRO 99
#define CRITICALITY_RAD 98
#define NB_MAX_PROCESS 20
/* Nom du process */
#define PROCESS_NAME "indrevenuv3"
/* Clef d acces a la table YM_INFO_BATCH pour recuperer la date de reference du PNIIND */
#define KEY_INFO_COMPLETE_DATE "COMPLETE_DATE_PNIIND"
/* Clef d acces a la table YM_INFO_BATCH pour stocker la date du PNIIND en cours */
#define KEY_INFO_CURRENT_DATE "CURRENT_DATE_PNIIND"
#define KEY_INFO_STATUS_BATCH "STATUS_BATCHV3"

//## Mutex
#ifdef POSIX_THREAD
extern pthread_mutex_t g_MutexDebug;
extern pthread_mutex_t g_MutexTd;
extern pthread_mutex_t g_MutexTdl;
extern pthread_mutex_t g_MutexTdj;
extern pthread_mutex_t g_MutexTdlj;
extern pthread_mutex_t g_MutexTdlpj;
extern pthread_mutex_t g_MutexTdlpjng;
extern pthread_mutex_t g_MutexTdlpcjng;
extern pthread_mutex_t g_MutexTdpj;
extern pthread_mutex_t g_MutexTdpcjng;
extern pthread_mutex_t g_MutexTdpjng;
extern pthread_mutex_t g_MutexTdoj;
extern pthread_mutex_t g_MutexTdopj;
extern pthread_mutex_t g_MutexTdopjng;
extern pthread_mutex_t g_MutexRevReal;
extern pthread_mutex_t g_MutexTdopcjng;
extern pthread_mutex_t g_MutexMessLog;
extern pthread_mutex_t g_MutexVnau;
extern pthread_mutex_t g_MutexDateTraitee;
extern pthread_mutex_t g_MutexPniLoaderTranche;
extern pthread_mutex_t g_MutexPniLoaderLeg;
extern pthread_mutex_t g_MutexPniLoaderTDOPJE;
extern pthread_mutex_t g_MutexPniLoaderTDLPJE;
extern pthread_mutex_t g_MutexTdopje;
extern pthread_mutex_t g_MutexTdpje;
extern pthread_mutex_t g_MutexTdlpje;
#else
extern mutex_t g_MutexDebug;
extern mutex_t g_MutexVnlHist;
extern mutex_t g_MutexTd;
extern mutex_t g_MutexTdl;
extern mutex_t g_MutexTdj;
extern mutex_t g_MutexTdlj;
extern mutex_t g_MutexTdlpj;
extern mutex_t g_MutexTdlpjng;
extern mutex_t g_MutexTdlpcjng;
extern mutex_t g_MutexTdpj;
extern mutex_t g_MutexTdpcjng;
extern mutex_t g_MutexTdpjng;
extern mutex_t g_MutexTdoj;
extern mutex_t g_MutexTdopj;
extern mutex_t g_MutexTdopjng;
extern mutex_t g_MutexTdopcjng;
extern mutex_t g_MutexRevReal;
extern mutex_t g_MutexMessLog;
extern mutex_t g_MutexVnau;
extern mutex_t g_MutexDateTraitee;
extern mutex_t g_MutexPniLoaderTranche;
extern mutex_t g_MutexPniLoaderLeg;
extern mutex_t g_MutexPniLoaderTDOPJE;
extern mutex_t g_MutexPniLoaderTDLPJE;
extern mutex_t g_MutexTdopje;
extern mutex_t g_MutexTdpje;
extern mutex_t g_MutexTdlpje;
#endif


//## Class
class YmDate;
class YmMessLog;
class YmIrInfoBatch;
class YmMapStations;
class YmMapCompartments;
class YmMapDatesIrATraiter;
class YmTools;
class YmIrIndOutputRec;
class YmTranche;
class YmTraitementTables;


//## Global
extern void sql_error(const char *, int, char * , int);
/* Affiche erreur et numero tcn et decremente nbTot */
extern void sql_warn (const char *szMessErr, int trancheNo , int &nbTot);
extern int			DEBUG;
extern char			g_UserName[20];
extern char			g_Password[32];
extern char			g_Sid[20];
extern int			gnPniLength;
extern int			gnHeaderLen;
extern int			gnLegHeaderLen;
extern int			gnLegBcsLen;
extern int			gnLegBucketLen;
/* Map representant la table ym_info_batch */
extern YmIrInfoBatch		g_InfoBatch;
extern YmMapStations            g_MapStations;
extern YmMapCompartments 	g_MapCompartments;
extern YmMapDatesIrATraiter 	g_MapDatesIrATraiter;
extern YmTools 		       	g_tools;
extern YmTraitementTables	g_traitementTables;
/* Version du fichier FSCORAIL */
//extern int			g_VersionDv;
extern int			g_bTrd;
extern int                      g_ModuloDay;

typedef map<string, int, less<string> > mapAuthType;

#endif
