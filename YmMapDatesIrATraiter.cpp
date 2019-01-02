
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
           char  filnam[24];
};
static const struct sqlcxp sqlfpn =
{
    23,
    "YmMapDatesIrATraiter.pc"
};


static unsigned int sqlctx = 688915387;


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
   unsigned char  *sqhstv[1];
   unsigned long  sqhstl[1];
            int   sqhsts[1];
            short *sqindv[1];
            int   sqinds[1];
   unsigned long  sqharm[1];
   unsigned long  *sqharc[1];
   unsigned short  sqadto[1];
   unsigned short  sqtdso[1];
} sqlstm = {12,1};

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
};


//## Module : YmMapDatesIrATraiter
//SFD
//  Name    : YmMapDatesIrATraiter.pc
//  Author  : flabyt
//  Desc    : Traitement de la liste des JXIrATraiter
//EFD

using namespace std;

//## Includes
#include <map>
#include <list>
#include <iterator>
/* Pour stacksize */
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
/* Pour process id */
#include <unistd.h>
/* Pour les erreurs des threads */
#include <errno.h>
#include <pthread.h>
#include <thread.h>
#include <sqlca.h>
#include "YmDate.h"
#include "YmIrGlobal.h"
#include "YmMapDatesIrATraiter.h"
#include "YmDatesIrATraiter.h"
#include "YmMessLog.h"
#include "YmIrInfoBatch.h"

//## Define
/* pour le stack */
/*  Ne pas mettre la taille du stack trop grande pour pourvoir faire des new et des liste */
#define N 0
#define HEGEXTRA 1000000

//## Thread
pthread_attr_t attr;


/* Pour la connection */
/* EXEC SQL BEGIN DECLARE SECTION; */ 

char connectstringThread[55];
sql_context ctx[20];
/* EXEC SQL END DECLARE SECTION; */ 


//## Globale
extern sql_context ctxMain;
extern int g_maxJXATraiter;


//SMD
// Name : Constructeur
// Desc : Constructeur par defaut
//EMD
YmMapDatesIrATraiter::YmMapDatesIrATraiter()
{
}

//SMD
// Name : ClearMap
// Desc : Vide la map
//EMD
void YmMapDatesIrATraiter::ClearMap()
{
  MapDatesIrATraiterType::iterator iPos = _MapDatesIrATraiter.begin();
  MapDatesIrATraiterType::iterator iFin = _MapDatesIrATraiter.end();

  YmDatesIrATraiter* pDatesIrATraiter;
  while (iPos != iFin)
    {
      pDatesIrATraiter = iPos->second;
      delete pDatesIrATraiter;
      iPos++;
    }

  _MapDatesIrATraiter.clear();
}

//SMD
// Name : Destructeur
// Desc : Destructeur
//EMD
YmMapDatesIrATraiter::~YmMapDatesIrATraiter()
{
  ClearMap();
}


//SMD
// Name : Init
// Desc : initialisation de la map, 0 = OK, -1 = pas trouve
//EMD
int YmMapDatesIrATraiter::init()
{
  int iRet = 0;
  int JXRef = 0; 
  int iStatusTraitementJX = 0;
  
  string sKey1;

  YmDate infoBatchCompleteDate = g_InfoBatch.get_assocCompleteDate();
  YmDate wDate;
  wDate = infoBatchCompleteDate;
  /* EXEC SQL CONTEXT USE :ctxMain; */ 


  /* EXEC SQL BEGIN DECLARE SECTION; */ 

  int iJxRef;
  char cDptDate[9];
  int iFlagCollecteJXATraiter;
  int iStatusJXATraiter;
  /* EXEC SQL END DECLARE SECTION; */ 


  cout << "g_maxJXATraiter : " << g_maxJXATraiter << endl; 
  for (int i = -1; i <= g_maxJXATraiter; i++)
    {
      wDate.PrintResaven (cDptDate, true);
      wDate.PrintResaven (sKey1);

      JXRef = i;
      iJxRef = JXRef;

      YmDatesIrATraiter *pDatesIrATraiter = new YmDatesIrATraiter(wDate, 0x00);
      _MapDatesIrATraiter[sKey1] = pDatesIrATraiter;

      wDate += 1;
    }

  return 0;
}

//SMD
// Name : IsInMap
// Desc : 
//EMD
YmDatesIrATraiter *YmMapDatesIrATraiter::isInMap(YmDate DateATraiter)
{
  MapDatesIrATraiterType::iterator iPos;
  YmDatesIrATraiter* pYmDatesIrATraiter;
  char szKey[20];

  pYmDatesIrATraiter = NULL;
  DateATraiter.PrintResaven(szKey, true);

  nbKey = 0;

  iPos = _MapDatesIrATraiter.find((string)szKey);

  if (iPos == _MapDatesIrATraiter.end())
    return NULL;
  else
    {
      pYmDatesIrATraiter = iPos->second;
      return pYmDatesIrATraiter;
    }
}

//SMD
// Name : AddNoBase
// Desc : Ajout dans la map
//EMD
void YmMapDatesIrATraiter::AddNoBase(YmDatesIrATraiter *pDatesIrATraiter)
{
  char cDate[9];
  string sKey;
  YmDate dDate = pDatesIrATraiter->get_DateATraiter();
  dDate.PrintResaven(cDate,true);
  sKey = cDate;

  _MapDatesIrATraiter[sKey] = pDatesIrATraiter;
}
