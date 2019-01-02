
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
           char  filnam[21];
};
static const struct sqlcxp sqlfpn =
{
    20,
    "YmMapCompartments.pc"
};


static unsigned int sqlctx = 86193907;


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

 static const char *sq0001 = 
"SELECT cmpt FROM ym_compartments ORDER BY cmpt            ";

typedef struct { unsigned short len; unsigned char arr[1]; } VARCHAR;
typedef struct { unsigned short len; unsigned char arr[1]; } varchar;

/* cud (compilation unit data) array */
static const short sqlcud0[] =
{12,4130,871,0,0,
5,0,0,1,58,0,9,73,0,2049,0,0,0,1,0,
20,0,0,1,0,0,13,82,0,0,1,0,0,1,0,2,9,0,0,
39,0,0,1,0,0,15,93,0,0,0,0,0,1,0,
};


//## Module : YmMapCompartments
//SFD
//  Name    : YmMapCompartments.pc
//  Author  : flabyt
//  Desc    : Traitement de la liste des Compartments
//EFD

using namespace std;

//## Includes
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <thread.h>
#include <iterator>
#include <sqlca.h>
#include "YmIrGlobal.h"
#include "YmMapCompartments.h"

//## Global
extern sql_context ctxMain;

//SMD
// Name : Constructeur
// Desc : Constructeur par defaut
//EMD
YmMapCompartments::YmMapCompartments()
{
  nbFindMapCompartments = 0;
}

//SMD
// Name : Destructeur
// Desc : Destructeur
//EMD
YmMapCompartments::~YmMapCompartments()
{
  MapCompartmentsType::iterator iPos = _MapCompartments.begin();
  MapCompartmentsType::iterator iFin = _MapCompartments.end();

  YmCompartments *pCompartments;
  while (iPos != iFin)
    {
      pCompartments = iPos->second;
      delete pCompartments;
      iPos++;
    }

  _MapCompartments.clear();
}

//SMD
// Name : Init
// Desc : initialisation de la map a partir de la base, 0 = OK, -1 = pas trouve
//EMD
int YmMapCompartments::init()
{
  int iRet = 0;
  int iNb = 0;

  /* EXEC SQL BEGIN DECLARE SECTION; */ 

  /* varchar cmpt[2]; */ 
struct { unsigned short len; unsigned char arr[2]; } cmpt;

  /* EXEC SQL END DECLARE SECTION; */ 

    
  /* EXEC SQL WHENEVER SQLERROR DO sql_error((char *)"liste des compartments illisible", 1, sqlca.sqlerrm.sqlerrmc,
					  sqlca.sqlerrm.sqlerrml); */ 

  /* EXEC SQL CONTEXT USE :ctxMain; */ 

  /* EXEC SQL DECLARE cMapCompartments CURSOR FOR
    SELECT cmpt
    FROM ym_compartments
    ORDER BY cmpt; */ 

  /* EXEC SQL OPEN cMapCompartments ; */ 

{
  struct sqlexd sqlstm;
  sqlstm.sqlvsn = 12;
  sqlstm.arrsiz = 0;
  sqlstm.sqladtp = &sqladt;
  sqlstm.sqltdsp = &sqltds;
  sqlstm.stmt = sq0001;
  sqlstm.iters = (unsigned int  )1;
  sqlstm.offset = (unsigned int  )5;
  sqlstm.selerr = (unsigned short)1;
  sqlstm.cud = sqlcud0;
  sqlstm.sqlest = (unsigned char  *)&sqlca;
  sqlstm.sqlety = (unsigned short)4352;
  sqlstm.occurs = (unsigned int  )0;
  sqlstm.sqcmod = (unsigned int )0;
  sqlcxt(&ctxMain, &sqlctx, &sqlstm, &sqlfpn);
  if (sqlca.sqlcode < 0) sql_error("liste des compartments illisible",1,((sqlca.sqlerrm).sqlerrmc),((sqlca.sqlerrm).sqlerrml));
}



  /* EXEC SQL WHENEVER NOT FOUND DO break; */ 

  string skey1;
  string scmpt;
  string seditDt;

  while(1)
    {
      /* EXEC SQL FETCH cMapCompartments INTO :cmpt; */ 

{
      struct sqlexd sqlstm;
      sqlstm.sqlvsn = 12;
      sqlstm.arrsiz = 1;
      sqlstm.sqladtp = &sqladt;
      sqlstm.sqltdsp = &sqltds;
      sqlstm.iters = (unsigned int  )1;
      sqlstm.offset = (unsigned int  )20;
      sqlstm.selerr = (unsigned short)1;
      sqlstm.cud = sqlcud0;
      sqlstm.sqlest = (unsigned char  *)&sqlca;
      sqlstm.sqlety = (unsigned short)4352;
      sqlstm.occurs = (unsigned int  )0;
      sqlstm.sqfoff = (         int )0;
      sqlstm.sqfmod = (unsigned int )2;
      sqlstm.sqhstv[0] = (unsigned char  *)&cmpt;
      sqlstm.sqhstl[0] = (unsigned long )4;
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
      if (sqlca.sqlcode == 1403) break;
      if (sqlca.sqlcode < 0) sql_error("liste des compartments illisible",1,((sqlca.sqlerrm).sqlerrmc),((sqlca.sqlerrm).sqlerrml));
}


      iNb++;

      cmpt.arr[cmpt.len] = '\0';
      scmpt = (char *)cmpt.arr;
      skey1 = scmpt;
      
      YmCompartments *pCompartments = new YmCompartments(scmpt);

      _MapCompartments[skey1] = pCompartments;
    }
  /* EXEC SQL CLOSE cMapCompartments ; */ 

{
  struct sqlexd sqlstm;
  sqlstm.sqlvsn = 12;
  sqlstm.arrsiz = 1;
  sqlstm.sqladtp = &sqladt;
  sqlstm.sqltdsp = &sqltds;
  sqlstm.iters = (unsigned int  )1;
  sqlstm.offset = (unsigned int  )39;
  sqlstm.cud = sqlcud0;
  sqlstm.sqlest = (unsigned char  *)&sqlca;
  sqlstm.sqlety = (unsigned short)4352;
  sqlstm.occurs = (unsigned int  )0;
  sqlcxt(&ctxMain, &sqlctx, &sqlstm, &sqlfpn);
  if (sqlca.sqlcode < 0) sql_error("liste des compartments illisible",1,((sqlca.sqlerrm).sqlerrmc),((sqlca.sqlerrm).sqlerrml));
}



  if (iNb == 0) 
    iRet = -1;
  else
    iRet = 0;

  return iRet;
}

//SMD
// Name : IsInMap
// Desc : Retourne pointeur si OK, NULL sinon
//EMD
YmCompartments *YmMapCompartments::isInMap(string cmpt)
{
  MapCompartmentsType::iterator iPos;
  YmCompartments *pYmCompartments;

  iPos = _MapCompartments.find(cmpt);
  if (iPos == _MapCompartments.end()) 
    return NULL;
  else
    {
      pYmCompartments = iPos->second;
      nbFindMapCompartments++;
      return pYmCompartments;
    }
}



