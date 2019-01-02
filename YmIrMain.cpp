
/* Result Sets Interface */
#ifndef SQL_CRSR
#  define SQL_CRSR
  struct sql_cursor
  {
    unsigned int curocn;
    void *ptr1;
    void *ptr2;
    unsigned int magic;
  };
  typedef struct sql_cursor sql_cursor;
  typedef struct sql_cursor SQL_CURSOR;
#endif /* SQL_CRSR */

/* Thread Safety */
typedef void * sql_context;
typedef void * SQL_CONTEXT;

/* Object support */
struct sqltvn
{
  unsigned char *tvnvsn; 
  unsigned short tvnvsnl; 
  unsigned char *tvnnm;
  unsigned short tvnnml; 
  unsigned char *tvnsnm;
  unsigned short tvnsnml;
};
typedef struct sqltvn sqltvn;

struct sqladts
{
  unsigned int adtvsn; 
  unsigned short adtmode; 
  unsigned short adtnum;  
  sqltvn adttvn[1];       
};
typedef struct sqladts sqladts;

static struct sqladts sqladt = {
  1,1,0,
};

/* Binding to PL/SQL Records */
struct sqltdss
{
  unsigned int tdsvsn; 
  unsigned short tdsnum; 
  unsigned char *tdsval[1]; 
};
typedef struct sqltdss sqltdss;
static struct sqltdss sqltds =
{
  1,
  0,
};

/* File name & Package Name */
struct sqlcxp
{
  unsigned short fillen;
           char  filnam[12];
};
static const struct sqlcxp sqlfpn =
{
    11,
    "YmIrMain.pc"
};


static unsigned int sqlctx = 168955;


static struct sqlexd {
   unsigned long  sqlvsn;
   unsigned int   arrsiz;
   unsigned int   iters;
   unsigned int   offset;
   unsigned short selerr;
   unsigned short sqlety;
   unsigned int   occurs;
      const short *cud;
   unsigned char  *sqlest;
      const char  *stmt;
   sqladts *sqladtp;
   sqltdss *sqltdsp;
   unsigned char  **sqphsv;
   unsigned long  *sqphsl;
            int   *sqphss;
            short **sqpind;
            int   *sqpins;
   unsigned long  *sqparm;
   unsigned long  **sqparc;
   unsigned short  *sqpadto;
   unsigned short  *sqptdso;
   unsigned int   sqlcmax;
   unsigned int   sqlcmin;
   unsigned int   sqlcincr;
   unsigned int   sqlctimeout;
   unsigned int   sqlcnowait;
            int   sqfoff;
   unsigned int   sqcmod;
   unsigned int   sqfmod;
   unsigned char  *sqhstv[4];
   unsigned long  sqhstl[4];
            int   sqhsts[4];
            short *sqindv[4];
            int   sqinds[4];
   unsigned long  sqharm[4];
   unsigned long  *sqharc[4];
   unsigned short  sqadto[4];
   unsigned short  sqtdso[4];
} sqlstm = {12,4};

// Prototypes
extern "C" {
  void sqlcxt (void **, unsigned int *,
               struct sqlexd *, const struct sqlcxp *);
  void sqlcx2t(void **, unsigned int *,
               struct sqlexd *, const struct sqlcxp *);
  void sqlbuft(void **, char *);
  void sqlgs2t(void **, char *);
  void sqlorat(void **, unsigned int *, void *);
}

// Forms Interface
static const int IAPSUCC = 0;
static const int IAPFAIL = 1403;
static const int IAPFTL  = 535;
extern "C" { void sqliem(unsigned char *, signed int *); }

typedef struct { unsigned short len; unsigned char arr[1]; } VARCHAR;
typedef struct { unsigned short len; unsigned char arr[1]; } varchar;

/* cud (compilation unit data) array */
static const short sqlcud0[] =
{12,4130,871,0,0,
5,0,0,0,0,0,60,292,0,0,0,0,0,1,0,
20,0,0,0,0,0,58,298,0,0,1,1,0,1,0,3,109,0,0,
39,0,0,0,0,0,27,300,0,0,4,4,0,1,0,1,97,0,0,1,97,0,0,1,10,0,0,1,10,0,0,
70,0,0,2,48,0,1,301,0,0,0,0,0,1,0,
85,0,0,3,67,0,4,307,0,0,1,0,0,1,0,2,97,0,0,
104,0,0,4,0,0,30,315,0,0,0,0,0,1,0,
119,0,0,5,0,0,30,333,0,0,0,0,0,1,0,
134,0,0,6,0,0,30,342,0,0,0,0,0,1,0,
149,0,0,7,0,0,30,352,0,0,0,0,0,1,0,
164,0,0,8,0,0,30,369,0,0,0,0,0,1,0,
179,0,0,9,0,0,30,386,0,0,0,0,0,1,0,
194,0,0,10,0,0,30,412,0,0,0,0,0,1,0,
209,0,0,0,0,0,59,413,0,0,1,1,0,1,0,3,109,0,0,
};


//## Module : YmIrMain
//SFD
//  Name    : YmIrMain.cpp
//  Authors : M. Hue / flabyt / Lienard william
//  Desc    : Main de l'application Regles commerciales hors reading days
//	      Ir (IndRevenuV3)
//EFD

using namespace std;

//## Includes
#include <iostream>
#include <list>
#include <map>
#include <iterator>
#include <signal.h>
#include "CoreLimit.h"
#undef SQLCA_STORAGE_CLASS
#include <sqlca.h>
/* Pour le sleep */
#include "unistd.h"
#include "YmIrGlobal.h"
#include "YmDate.h"
#include "YmMessLog.h"
#include "YmIrInfoBatch.h"
#include "YmMapStations.h"
#include "YmMapCompartments.h"
#include "YmDatesIrATraiter.h"
#include "YmMapDatesIrATraiter.h"
#include "YmTools.h"
#include "YmLeg.h"
#include "YmTranche.h"
#include "YmIrSysParms.h"
#include "YmIrDvLoader.h"
#include "YmIrIndLoader.h"
#include "YmTraitementTables.h"


//## Global
int		     DEBUG;
YmMessLog	     rMess(__FILE__, "Traitement du batch IndRevenu", PROCESS_NAME);    
YmIrInfoBatch	     g_InfoBatch;
YmMapStations	     g_MapStations;
YmMapCompartments    g_MapCompartments;
YmTraitementTables   g_traitementTables;
YmMapDatesIrATraiter g_MapDatesIrATraiter;
int		     g_IrThreadDatesATraiterActifs = 0;
int		     g_maxJXATraiter = 200;
YmTools		     g_tools; 
/* utilise par les process pour evaluation */
int		     _maxCriticality;
/* utilise par les process pour evaluation */
int		     _critThreshold;

int		     g_maxResHoldIdv;

char		     g_UserName[20];
char		     g_Password[32];
char		     g_Sid[20];

/* Non utilise pour l'indrevenu */
int		     g_IrMaxProcess = 1;

/* Global variable for access to the length PNI */
int		     gnPniLength = PNI_LEN ;
/* Global variable for access to the length Tranche header len */
int		     gnTrancheHeaderLen = TRANCHE_HEADER_LEN;
/* Global variable for access to the length  header len */
int		     gnHeaderLen = HEADER_LEN;
/* Global variable for access to the length  leg header len */
int		     gnLegHeaderLen = LEG_HEADER_LEN;
/* Global variable for access to the length  leg bcs len */
int		     gnLegBcsLen = LEG_BCS_LEN;
/* Global variable for access to the length  leg bucket len */
int		     gnLegBucketLen = LEG_BUCKET_LEN;

int		     g_bTrd = 0;
int                  g_ModuloDay=0;
/* Utilise par le nouveau format du fichier FSCORAIL */
//int		     g_VersionDv = 0;


/* EXEC SQL BEGIN DECLARE SECTION; */ 

sql_context ctxMain; 
/* EXEC SQL END DECLARE SECTION; */ 



//SMD
// Name : 
// Desc : fonctions utilisees pour le core Limit
//EMD
/* Signal handling code */
extern "C"
{
  void SigUsr2Handler(int sig_);
  void SigUsr1Handler(int sig_);
  void AllSigHandler(int sig_);
}

void SigUsr2Handler(int sig_)
{
  cerr << "Process " << getpid() << " received SIGUSR2 signal." << endl;
}

void SigUsr1Handler(int sig_)
{
  cerr << "Process " << getpid() << " received SIGUSR1 signal." << endl;

  YmMessLog lMess(__FILE__, "Main", PROCESS_NAME); 
  string ltext = "Process received SIGUSR1 signal and exited.";
  lMess.envoiMess(__LINE__, ltext, YmMessLog::ERROR);

  exit(6);
}

void AllSigHandler(int sig_)
{
  char lbuf[10];

  cerr << "Process " << getpid() << " received signal " << sig_ << endl;

  /* Log message in the DB */
  string ltext = "Process received signal ";
  sprintf(lbuf, "%2d", sig_);
  ltext += lbuf;

  YmMessLog lMess(__FILE__, "Main", PROCESS_NAME); 
  lMess.envoiMess(__LINE__, ltext, YmMessLog::ERROR);

  exit(5);
}

void HandleSigs()
{
  for (int li = 1; li < NSIG; li++)
    signal(li, AllSigHandler);	

  /* Use special signal handler for SIGUSR1
   * as this will be used to stop any such process */

  signal(SIGUSR1, SigUsr1Handler);
  signal(SIGUSR2, SigUsr2Handler);

  /* Ignore as window size may change during run time */
  signal(SIGWINCH, SIG_IGN);
  signal(SIGTSTP, SIG_IGN);
  signal(SIGCONT, SIG_IGN);
}

//SMD
// Name : CheckEnvironment
// Desc : Verification de l'envrironnement
//EMD
int CheckEnvironment()
{
  if (!(getenv("YMBA_RESA_DATA_DIR")))
    {
      cerr << "Environment variable YMBA_RESA_DATA_DIR not set.\n";

      return 3;
    }

  if (!(getenv("YMBA_RESA_IND_FILE_NAME")))
    {
      cerr << "Environment variable YMBA_RESA_IND_FILE_NAME not set.\n";

      return 3;
    }

  DEBUG = true;
  char *szDEBUG = NULL;
  szDEBUG = getenv("YM_NB_DEBUG");

  /* NULL quand pas de variable d'environnement */
  if (szDEBUG == NULL || (strcmp(szDEBUG , "false") == 0) || (strcmp(szDEBUG , "FALSE") == 0))
    DEBUG = false;

  if ( g_bTrd == 1)
    {
      /* On est en environnement CORAIL, donc vérification pour la partie FSCORAIL */
      if (!getenv("YMBA_DV_NAME"))
	{
	  cerr << "Environment variable YMBA_DV_NAME not set.\n";

	  return 3;
	}

      if (!getenv("YMBA_DV_DIR"))
	{
	  cerr << "Environment variable YMBA_DV_DIR not set.\n";

	  return 3;
	}

    /*  if (getenv("YNG_FSCORAIL_V2"))
	{
	  g_VersionDv = atoi(getenv("YNG_FSCORAIL_V2"));

	  if (g_VersionDv >= 1)
	    g_VersionDv = 1;
	  else
	    g_VersionDv = 0;

	  cout << "Environment variable YNG_FSCORAIL_V2 = " << g_VersionDv << ".\n";
	}
      else
	{
	  cout << "Environment variable YNG_FSCORAIL_V2 = default value.\n";
	}*/
    }

  return 0;
}


//SMD
// Name : GetSysParms : Lecture de tous les parametres globaux de l'application
// Desc : Get the System Parameters used in Criticality processing.
//        parameter uses by  YmIrThreadJXATraiter process.
//EMD
void GetSysParms()
{
  YmIrSysParms ParmsOfApplication;
  if (ParmsOfApplication.getInt((char*)"CRITICAL_THRESHOLD", (char *)"", _critThreshold) == false)
    /* Valeur par defaut */
    _critThreshold = 0;

  if (ParmsOfApplication.getInt((char *)"MAX_CRITICALITY", (char *)"", _maxCriticality) == false)
    /* Valeur par defaut */
    _maxCriticality = 10;

  if (ParmsOfApplication.getInt((char *)"GROUP_THRESHOLD", (char *)"", g_maxResHoldIdv) == false)
    /* Valeur par defaut */
    g_maxResHoldIdv = 10;
}

//SMD
// Name : Main
// Desc : Programme principal
//EMD
int main(int argc, char **argv)
{
  int iRet;

  /* EXEC SQL BEGIN DECLARE SECTION; */ 

  char szUserName[20];
  char szPassword[32];
  char DatePrecFichier[11];
  int  HeurePrecFichier;
  char DynamicTruncate[64];
  char postedTime[16];
  int iJxRef;
  /* EXEC SQL END DECLARE SECTION; */ 


  if ( argc < 8 )
    {
      cerr << PROCESS_NAME << " VERSION 2.0.1 Oracle11" << endl;
      cerr << "Usage: " << PROCESS_NAME << " USER_O PASSWORD_O SID_O USER_R PASSWORD_R SID_R trd" << endl;
      cerr << "         - trd = 1 si CORAIL, trd = 0 sinon" << endl;

      return 1;
    }

  const char *szSid = 0;
  if (!(szSid = getenv("TWO_TASK")))
    {
      cerr << "FATAL: TWO_TASK not set \n";

      return(2);
    }

  if (strcmp(szSid, argv[3]))
    {
      cerr << "FATAL: La base " << argv[3] << " n est pas la base par defaut (" << szSid << ")\n";

      exit(10);
    }

  strcpy (szUserName, argv[1]);
  strcpy (szPassword, argv[2]);
  strcpy (g_UserName, argv[4]);
  strcpy (g_Password, argv[5]);
  strcpy (g_Sid, argv[6]);

  g_bTrd = atoi(argv[7]);
  if (g_bTrd == 1)
    cerr << "Traitement CORAIL selectionne \n";
  else
    cerr << "Traitement THALYS selectionne \n";

  /* Initialize a proces in which to spawn threads */
  /* EXEC SQL ENABLE THREADS; */ 

{
  struct sqlexd sqlstm;
  sqlstm.sqlvsn = 12;
  sqlstm.arrsiz = 0;
  sqlstm.sqladtp = &sqladt;
  sqlstm.sqltdsp = &sqltds;
  sqlstm.stmt = "";
  sqlstm.iters = (unsigned int  )1;
  sqlstm.offset = (unsigned int  )5;
  sqlstm.cud = sqlcud0;
  sqlstm.sqlest = (unsigned char  *)&sqlca;
  sqlstm.sqlety = (unsigned short)4352;
  sqlstm.occurs = (unsigned int  )0;
  sqlcxt((void **)0, &sqlctx, &sqlstm, &sqlfpn);
}



  /* Connexion a la base par default */
  /* EXEC SQL WHENEVER SQLERROR DO sql_error("ouverture base de donnees impossible", 1, sqlca.sqlerrm.sqlerrmc,
					  sqlca.sqlerrm.sqlerrml); */ 


  /* EXEC SQL CONTEXT ALLOCATE :ctxMain; */ 

{
  struct sqlexd sqlstm;
  sqlstm.sqlvsn = 12;
  sqlstm.arrsiz = 1;
  sqlstm.sqladtp = &sqladt;
  sqlstm.sqltdsp = &sqltds;
  sqlstm.stmt = "";
  sqlstm.iters = (unsigned int  )1;
  sqlstm.offset = (unsigned int  )20;
  sqlstm.cud = sqlcud0;
  sqlstm.sqlest = (unsigned char  *)&sqlca;
  sqlstm.sqlety = (unsigned short)4352;
  sqlstm.occurs = (unsigned int  )0;
  sqlstm.sqhstv[0] = (unsigned char  *)&ctxMain;
  sqlstm.sqhstl[0] = (unsigned long )sizeof(void *);
  sqlstm.sqhsts[0] = (         int  )0;
  sqlstm.sqindv[0] = (         short *)0;
  sqlstm.sqinds[0] = (         int  )0;
  sqlstm.sqharm[0] = (unsigned long )0;
  sqlstm.sqadto[0] = (unsigned short )0;
  sqlstm.sqtdso[0] = (unsigned short )0;
  sqlstm.sqphsv = sqlstm.sqhstv;
  sqlstm.sqphsl = sqlstm.sqhstl;
  sqlstm.sqphss = sqlstm.sqhsts;
  sqlstm.sqpind = sqlstm.sqindv;
  sqlstm.sqpins = sqlstm.sqinds;
  sqlstm.sqparm = sqlstm.sqharm;
  sqlstm.sqparc = sqlstm.sqharc;
  sqlstm.sqpadto = sqlstm.sqadto;
  sqlstm.sqptdso = sqlstm.sqtdso;
  sqlcxt((void **)0, &sqlctx, &sqlstm, &sqlfpn);
  if (sqlca.sqlcode < 0) sql_error("ouverture base de donnees impossible",1,((sqlca.sqlerrm).sqlerrmc),((sqlca.sqlerrm).sqlerrml));
}


  /* EXEC SQL CONTEXT USE :ctxMain; */ 

  /* EXEC SQL CONNECT :szUserName IDENTIFIED BY :szPassword; */ 

{
  struct sqlexd sqlstm;
  sqlstm.sqlvsn = 12;
  sqlstm.arrsiz = 4;
  sqlstm.sqladtp = &sqladt;
  sqlstm.sqltdsp = &sqltds;
  sqlstm.iters = (unsigned int  )10;
  sqlstm.offset = (unsigned int  )39;
  sqlstm.cud = sqlcud0;
  sqlstm.sqlest = (unsigned char  *)&sqlca;
  sqlstm.sqlety = (unsigned short)4352;
  sqlstm.occurs = (unsigned int  )0;
  sqlstm.sqhstv[0] = (unsigned char  *)szUserName;
  sqlstm.sqhstl[0] = (unsigned long )20;
  sqlstm.sqhsts[0] = (         int  )20;
  sqlstm.sqindv[0] = (         short *)0;
  sqlstm.sqinds[0] = (         int  )0;
  sqlstm.sqharm[0] = (unsigned long )0;
  sqlstm.sqadto[0] = (unsigned short )0;
  sqlstm.sqtdso[0] = (unsigned short )0;
  sqlstm.sqhstv[1] = (unsigned char  *)szPassword;
  sqlstm.sqhstl[1] = (unsigned long )32;
  sqlstm.sqhsts[1] = (         int  )32;
  sqlstm.sqindv[1] = (         short *)0;
  sqlstm.sqinds[1] = (         int  )0;
  sqlstm.sqharm[1] = (unsigned long )0;
  sqlstm.sqadto[1] = (unsigned short )0;
  sqlstm.sqtdso[1] = (unsigned short )0;
  sqlstm.sqphsv = sqlstm.sqhstv;
  sqlstm.sqphsl = sqlstm.sqhstl;
  sqlstm.sqphss = sqlstm.sqhsts;
  sqlstm.sqpind = sqlstm.sqindv;
  sqlstm.sqpins = sqlstm.sqinds;
  sqlstm.sqparm = sqlstm.sqharm;
  sqlstm.sqparc = sqlstm.sqharc;
  sqlstm.sqpadto = sqlstm.sqadto;
  sqlstm.sqptdso = sqlstm.sqtdso;
  sqlstm.sqlcmax = (unsigned int )100;
  sqlstm.sqlcmin = (unsigned int )2;
  sqlstm.sqlcincr = (unsigned int )1;
  sqlstm.sqlctimeout = (unsigned int )0;
  sqlstm.sqlcnowait = (unsigned int )0;
  sqlcxt(&ctxMain, &sqlctx, &sqlstm, &sqlfpn);
  if (sqlca.sqlcode < 0) sql_error("ouverture base de donnees impossible",1,((sqlca.sqlerrm).sqlerrmc),((sqlca.sqlerrm).sqlerrml));
}


  /* EXEC SQL ALTER SESSION SET NLS_DATE_FORMAT = 'DD/MM/YYYY'; */ 

{
  struct sqlexd sqlstm;
  sqlstm.sqlvsn = 12;
  sqlstm.arrsiz = 4;
  sqlstm.sqladtp = &sqladt;
  sqlstm.sqltdsp = &sqltds;
  sqlstm.stmt = "alter SESSION SET NLS_DATE_FORMAT = 'DD/MM/YYYY'";
  sqlstm.iters = (unsigned int  )1;
  sqlstm.offset = (unsigned int  )70;
  sqlstm.cud = sqlcud0;
  sqlstm.sqlest = (unsigned char  *)&sqlca;
  sqlstm.sqlety = (unsigned short)4352;
  sqlstm.occurs = (unsigned int  )0;
  sqlcxt(&ctxMain, &sqlctx, &sqlstm, &sqlfpn);
  if (sqlca.sqlcode < 0) sql_error("ouverture base de donnees impossible",1,((sqlca.sqlerrm).sqlerrmc),((sqlca.sqlerrm).sqlerrml));
}



  YmMessLog lMess(__FILE__, "Main", PROCESS_NAME); 
  string ltext = "Debut du batch indrevenu";
  lMess.envoiMess(__LINE__, ltext, YmMessLog::JOBSTART);

  /* EXEC SQL SELECT TO_CHAR(SYSDATE, 'DD/MM/YY HH24:MI') into :postedTime FROM DUAL; */ 

{
  struct sqlexd sqlstm;
  sqlstm.sqlvsn = 12;
  sqlstm.arrsiz = 4;
  sqlstm.sqladtp = &sqladt;
  sqlstm.sqltdsp = &sqltds;
  sqlstm.stmt = "select TO_CHAR ( SYSDATE , 'DD/MM/YY HH24:MI' ) into :b0 F\
ROM DUAL ";
  sqlstm.iters = (unsigned int  )1;
  sqlstm.offset = (unsigned int  )85;
  sqlstm.selerr = (unsigned short)1;
  sqlstm.cud = sqlcud0;
  sqlstm.sqlest = (unsigned char  *)&sqlca;
  sqlstm.sqlety = (unsigned short)4352;
  sqlstm.occurs = (unsigned int  )0;
  sqlstm.sqhstv[0] = (unsigned char  *)postedTime;
  sqlstm.sqhstl[0] = (unsigned long )16;
  sqlstm.sqhsts[0] = (         int  )0;
  sqlstm.sqindv[0] = (         short *)0;
  sqlstm.sqinds[0] = (         int  )0;
  sqlstm.sqharm[0] = (unsigned long )0;
  sqlstm.sqadto[0] = (unsigned short )0;
  sqlstm.sqtdso[0] = (unsigned short )0;
  sqlstm.sqphsv = sqlstm.sqhstv;
  sqlstm.sqphsl = sqlstm.sqhstl;
  sqlstm.sqphss = sqlstm.sqhsts;
  sqlstm.sqpind = sqlstm.sqindv;
  sqlstm.sqpins = sqlstm.sqinds;
  sqlstm.sqparm = sqlstm.sqharm;
  sqlstm.sqparc = sqlstm.sqharc;
  sqlstm.sqpadto = sqlstm.sqadto;
  sqlstm.sqptdso = sqlstm.sqtdso;
  sqlcxt(&ctxMain, &sqlctx, &sqlstm, &sqlfpn);
  if (sqlca.sqlcode < 0) sql_error("ouverture base de donnees impossible",1,((sqlca.sqlerrm).sqlerrmc),((sqlca.sqlerrm).sqlerrml));
}



  cout << DonneHeure() << " Debut du batch indrevenu" << endl;
  cout<< postedTime << " BATCH " << PROCESS_NAME << " VERSION 2.0.1 Oracle 11" << endl;

  if (g_InfoBatch.init() != 0)
    {
      cerr << "FATAL - table des Infos Batch : informations manquantes " << endl;   
      /* EXEC SQL COMMIT WORK RELEASE; */ 

{
      struct sqlexd sqlstm;
      sqlstm.sqlvsn = 12;
      sqlstm.arrsiz = 4;
      sqlstm.sqladtp = &sqladt;
      sqlstm.sqltdsp = &sqltds;
      sqlstm.iters = (unsigned int  )1;
      sqlstm.offset = (unsigned int  )104;
      sqlstm.cud = sqlcud0;
      sqlstm.sqlest = (unsigned char  *)&sqlca;
      sqlstm.sqlety = (unsigned short)4352;
      sqlstm.occurs = (unsigned int  )0;
      sqlcxt(&ctxMain, &sqlctx, &sqlstm, &sqlfpn);
      if (sqlca.sqlcode < 0) sql_error("ouverture base de donnees impossible",1,((sqlca.sqlerrm).sqlerrmc),((sqlca.sqlerrm).sqlerrml));
}



      exit(10);
    }

  /* Get the infoBatchDate */
  YmDate linfoBatchDateComplete = g_InfoBatch.get_assocCompleteDate();
  YmDate linfoBatchDateCurrent = g_InfoBatch.get_assocCurrentDate();

  /* Set variables based on environment */
  const  char *lpbatchOutputDir = 0;
  const  char *lpbatchOutputFilePre = 0;
  static char lenv[64];

  /* Check all environment variable */
  if (CheckEnvironment() != 0)
    {
      cerr << "CheckEnvironment non Ok - fin application ! " << endl; 
      /* EXEC SQL COMMIT WORK RELEASE; */ 

{
      struct sqlexd sqlstm;
      sqlstm.sqlvsn = 12;
      sqlstm.arrsiz = 4;
      sqlstm.sqladtp = &sqladt;
      sqlstm.sqltdsp = &sqltds;
      sqlstm.iters = (unsigned int  )1;
      sqlstm.offset = (unsigned int  )119;
      sqlstm.cud = sqlcud0;
      sqlstm.sqlest = (unsigned char  *)&sqlca;
      sqlstm.sqlety = (unsigned short)4352;
      sqlstm.occurs = (unsigned int  )0;
      sqlcxt(&ctxMain, &sqlctx, &sqlstm, &sqlfpn);
      if (sqlca.sqlcode < 0) sql_error("ouverture base de donnees impossible",1,((sqlca.sqlerrm).sqlerrmc),((sqlca.sqlerrm).sqlerrml));
}



      exit(3);
    }

  iRet = g_MapStations.init();
  if (iRet < 0)
    {
      cerr << "FATAL - liste des Stations vide" << endl;
      /* EXEC SQL COMMIT WORK RELEASE; */ 

{
      struct sqlexd sqlstm;
      sqlstm.sqlvsn = 12;
      sqlstm.arrsiz = 4;
      sqlstm.sqladtp = &sqladt;
      sqlstm.sqltdsp = &sqltds;
      sqlstm.iters = (unsigned int  )1;
      sqlstm.offset = (unsigned int  )134;
      sqlstm.cud = sqlcud0;
      sqlstm.sqlest = (unsigned char  *)&sqlca;
      sqlstm.sqlety = (unsigned short)4352;
      sqlstm.occurs = (unsigned int  )0;
      sqlcxt(&ctxMain, &sqlctx, &sqlstm, &sqlfpn);
      if (sqlca.sqlcode < 0) sql_error("ouverture base de donnees impossible",1,((sqlca.sqlerrm).sqlerrmc),((sqlca.sqlerrm).sqlerrml));
}



      exit(10);
    }
  cout << "Chargement Stations termine" << endl;

  iRet = g_MapCompartments.init();
  if (iRet < 0) 
    { 
      cerr << "FATAL - liste des Compartments vide" << endl;
      /* EXEC SQL COMMIT WORK RELEASE; */ 

{
      struct sqlexd sqlstm;
      sqlstm.sqlvsn = 12;
      sqlstm.arrsiz = 4;
      sqlstm.sqladtp = &sqladt;
      sqlstm.sqltdsp = &sqltds;
      sqlstm.iters = (unsigned int  )1;
      sqlstm.offset = (unsigned int  )149;
      sqlstm.cud = sqlcud0;
      sqlstm.sqlest = (unsigned char  *)&sqlca;
      sqlstm.sqlety = (unsigned short)4352;
      sqlstm.occurs = (unsigned int  )0;
      sqlcxt(&ctxMain, &sqlctx, &sqlstm, &sqlfpn);
      if (sqlca.sqlcode < 0) sql_error("ouverture base de donnees impossible",1,((sqlca.sqlerrm).sqlerrmc),((sqlca.sqlerrm).sqlerrml));
}



      exit(10);
    }
  cout << "Chargement Compartments termine" << endl;

  /* lecture de tous les parametres generaux utilises par l application */
  GetSysParms();

  /* simple constitution d'une liste de JX representant la periode de la date de INFOBATCH-1
   * jusqu'a INFOBATCH + g_maxJXATraiter */
  g_MapDatesIrATraiter.init();

  iRet = g_tools.GetPays();
  if (iRet < 0)
    {
      cerr << "FATAL - liste des pays illisible" << endl;
      /* EXEC SQL COMMIT WORK RELEASE; */ 

{
      struct sqlexd sqlstm;
      sqlstm.sqlvsn = 12;
      sqlstm.arrsiz = 4;
      sqlstm.sqladtp = &sqladt;
      sqlstm.sqltdsp = &sqltds;
      sqlstm.iters = (unsigned int  )1;
      sqlstm.offset = (unsigned int  )164;
      sqlstm.cud = sqlcud0;
      sqlstm.sqlest = (unsigned char  *)&sqlca;
      sqlstm.sqlety = (unsigned short)4352;
      sqlstm.occurs = (unsigned int  )0;
      sqlcxt(&ctxMain, &sqlctx, &sqlstm, &sqlfpn);
      if (sqlca.sqlcode < 0) sql_error("ouverture base de donnees impossible",1,((sqlca.sqlerrm).sqlerrmc),((sqlca.sqlerrm).sqlerrml));
}



      exit(10);
    }

	//Suppression lecture FS Corail
    YmIrDvLoader dvLoader(linfoBatchDateComplete);
	/*if (g_bTrd != 0)
    dvLoader.LectureDV(&g_MapDatesIrATraiter);*/

  char sInputFileName[100];
  sprintf(sInputFileName, "%s/%s", getenv("YMBA_RESA_DATA_DIR"), getenv("YMBA_RESA_IND_FILE_NAME"));
  cout << DonneHeure() << " Debut Lecture fichier Ind " << endl;

  YmIrIndLoader indLoader(linfoBatchDateComplete, sInputFileName);
  if (!indLoader.LectureInd(&dvLoader)) 
    {
      /* EXEC SQL COMMIT WORK RELEASE; */ 

{
      struct sqlexd sqlstm;
      sqlstm.sqlvsn = 12;
      sqlstm.arrsiz = 4;
      sqlstm.sqladtp = &sqladt;
      sqlstm.sqltdsp = &sqltds;
      sqlstm.iters = (unsigned int  )1;
      sqlstm.offset = (unsigned int  )179;
      sqlstm.cud = sqlcud0;
      sqlstm.sqlest = (unsigned char  *)&sqlca;
      sqlstm.sqlety = (unsigned short)4352;
      sqlstm.occurs = (unsigned int  )0;
      sqlcxt(&ctxMain, &sqlctx, &sqlstm, &sqlfpn);
      if (sqlca.sqlcode < 0) sql_error("ouverture base de donnees impossible",1,((sqlca.sqlerrm).sqlerrmc),((sqlca.sqlerrm).sqlerrml));
}



      exit(100);
    }

  indLoader.CleanChainMap();
  cout << DonneHeure() << " Fin Lecture fichier Ind" << endl;

  cout << DonneHeure() << " Debut de l'insertion dans la table TPREV_TRANCHES_LEGS" << endl;
  g_traitementTables.TraitementTtl();
  cout << DonneHeure() << " Fin de l'insertion dans la table TPREV_TRANCHES_LEGS" << endl;

  cout << DonneHeure() << " Debut de l'insertion dans la table REV_TRANCHES_NON_YIELD" << endl;
  g_traitementTables.TraitementRtny();
  cout << DonneHeure() << " Fin de l'insertion dans la table REV_TRANCHES_NON_YIELD" << endl;

  cout << DonneHeure() << " Fin traitement du batch " << PROCESS_NAME << endl;

  string ltext1 = "Fin du batch ";
  lMess.envoiMess(__LINE__, ltext1, YmMessLog::JOBEND);

  /* Fermeture de la connection avec la base 1 */
  /* EXEC SQL WHENEVER SQLERROR DO sql_error("LiberationMain-fermeture database impossible pour le Main ",
					  0, sqlca.sqlerrm.sqlerrmc, sqlca.sqlerrm.sqlerrml); */ 


  /* EXEC SQL CONTEXT USE :ctxMain; */ 

  /* EXEC SQL COMMIT WORK RELEASE; */ 

{
  struct sqlexd sqlstm;
  sqlstm.sqlvsn = 12;
  sqlstm.arrsiz = 4;
  sqlstm.sqladtp = &sqladt;
  sqlstm.sqltdsp = &sqltds;
  sqlstm.iters = (unsigned int  )1;
  sqlstm.offset = (unsigned int  )194;
  sqlstm.cud = sqlcud0;
  sqlstm.sqlest = (unsigned char  *)&sqlca;
  sqlstm.sqlety = (unsigned short)4352;
  sqlstm.occurs = (unsigned int  )0;
  sqlcxt(&ctxMain, &sqlctx, &sqlstm, &sqlfpn);
  if (sqlca.sqlcode < 0) sql_error("LiberationMain-fermeture database impossible pour le Main ",0,((sqlca.sqlerrm).sqlerrmc),((sqlca.sqlerrm).sqlerrml));
}


  /* EXEC SQL CONTEXT FREE :ctxMain; */ 

{
  struct sqlexd sqlstm;
  sqlstm.sqlvsn = 12;
  sqlstm.arrsiz = 4;
  sqlstm.sqladtp = &sqladt;
  sqlstm.sqltdsp = &sqltds;
  sqlstm.stmt = "";
  sqlstm.iters = (unsigned int  )1;
  sqlstm.offset = (unsigned int  )209;
  sqlstm.cud = sqlcud0;
  sqlstm.sqlest = (unsigned char  *)&sqlca;
  sqlstm.sqlety = (unsigned short)4352;
  sqlstm.occurs = (unsigned int  )0;
  sqlstm.sqhstv[0] = (unsigned char  *)&ctxMain;
  sqlstm.sqhstl[0] = (unsigned long )sizeof(void *);
  sqlstm.sqhsts[0] = (         int  )0;
  sqlstm.sqindv[0] = (         short *)0;
  sqlstm.sqinds[0] = (         int  )0;
  sqlstm.sqharm[0] = (unsigned long )0;
  sqlstm.sqadto[0] = (unsigned short )0;
  sqlstm.sqtdso[0] = (unsigned short )0;
  sqlstm.sqphsv = sqlstm.sqhstv;
  sqlstm.sqphsl = sqlstm.sqhstl;
  sqlstm.sqphss = sqlstm.sqhsts;
  sqlstm.sqpind = sqlstm.sqindv;
  sqlstm.sqpins = sqlstm.sqinds;
  sqlstm.sqparm = sqlstm.sqharm;
  sqlstm.sqparc = sqlstm.sqharc;
  sqlstm.sqpadto = sqlstm.sqadto;
  sqlstm.sqptdso = sqlstm.sqtdso;
  sqlcxt((void **)0, &sqlctx, &sqlstm, &sqlfpn);
  if (sqlca.sqlcode < 0) sql_error("LiberationMain-fermeture database impossible pour le Main ",0,((sqlca.sqlerrm).sqlerrmc),((sqlca.sqlerrm).sqlerrml));
}



  return 0;
}
