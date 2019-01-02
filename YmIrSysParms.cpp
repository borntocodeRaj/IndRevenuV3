
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
           char  filnam[16];
};
static const struct sqlcxp sqlfpn =
{
    15,
    "YmIrSysParms.pc"
};


static unsigned int sqlctx = 2727043;


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
   unsigned char  *sqhstv[3];
   unsigned long  sqhstl[3];
            int   sqhsts[3];
            short *sqindv[3];
            int   sqinds[3];
   unsigned long  sqharm[3];
   unsigned long  *sqharc[3];
   unsigned short  sqadto[3];
   unsigned short  sqtdso[3];
} sqlstm = {12,3};

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
5,0,0,1,109,0,4,61,0,0,3,2,0,1,0,2,9,0,0,1,9,0,0,1,9,0,0,
32,0,0,2,110,0,4,98,0,0,3,2,0,1,0,2,4,0,0,1,9,0,0,1,9,0,0,
59,0,0,3,110,0,4,131,0,0,3,2,0,1,0,2,3,0,0,1,9,0,0,1,9,0,0,
};


//## Module : YmIrSysParms
//SFD
//  Name    : YmIrSysParms.pc
//  Author  : Bernard Sabattié
//  Desc    : Traitement de la lecture des paramètres système.
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
#include "YmIrSysParms.h"
#include <iostream>

//## Global
extern sql_context ctxMain;

//SMD
// Name : Constructeur
// Desc : Constructeur par defaut
//EMD
YmIrSysParms::YmIrSysParms()
{
}

//SMD
// Name : Destructeur
// Desc : Destructeur
//EMD
YmIrSysParms::~YmIrSysParms()
{
}

//SMD
// Name : getChar
// Desc :
//EMD
string  YmIrSysParms::getChar(char *c_sysParmName,char *c_sysParmPlus) 
{
  string scharValue; 

  /* EXEC SQL BEGIN DECLARE SECTION; */ 

  /* varchar charValue[81]; */ 
struct { unsigned short len; unsigned char arr[81]; } charValue;

  /* varchar sysParmName[31]; */ 
struct { unsigned short len; unsigned char arr[31]; } sysParmName;

  /* varchar sysParmPlus[31]; */ 
struct { unsigned short len; unsigned char arr[31]; } sysParmPlus;

  /* EXEC SQL END DECLARE SECTION; */ 

  
  strcpy((char *)sysParmName.arr, c_sysParmName);
  sysParmName.len = strlen((const char *)sysParmName.arr);
  strcpy((char *)sysParmPlus.arr, c_sysParmPlus);
  sysParmPlus.len = strlen((const char *)sysParmPlus.arr);

  /* EXEC SQL WHENEVER SQLERROR GOTO sql_error; */ 

  /* EXEC SQL CONTEXT USE :ctxMain; */ 

  /* EXEC SQL SELECT char_value
    INTO :charValue
    FROM ym_sys_parms
    WHERE sys_parm_name = :sysParmName
    AND sys_parm_plus = nvl(:sysParmPlus, ' '); */ 

{
  struct sqlexd sqlstm;
  sqlstm.sqlvsn = 12;
  sqlstm.arrsiz = 3;
  sqlstm.sqladtp = &sqladt;
  sqlstm.sqltdsp = &sqltds;
  sqlstm.stmt = "select char_value INTO :b0 FROM ym_sys_parms WHERE sys_par\
m_name = :b1 AND sys_parm_plus = nvl ( :b2 , ' ' ) ";
  sqlstm.iters = (unsigned int  )1;
  sqlstm.offset = (unsigned int  )5;
  sqlstm.selerr = (unsigned short)1;
  sqlstm.cud = sqlcud0;
  sqlstm.sqlest = (unsigned char  *)&sqlca;
  sqlstm.sqlety = (unsigned short)4352;
  sqlstm.occurs = (unsigned int  )0;
  sqlstm.sqhstv[0] = (unsigned char  *)&charValue;
  sqlstm.sqhstl[0] = (unsigned long )83;
  sqlstm.sqhsts[0] = (         int  )0;
  sqlstm.sqindv[0] = (         short *)0;
  sqlstm.sqinds[0] = (         int  )0;
  sqlstm.sqharm[0] = (unsigned long )0;
  sqlstm.sqadto[0] = (unsigned short )0;
  sqlstm.sqtdso[0] = (unsigned short )0;
  sqlstm.sqhstv[1] = (unsigned char  *)&sysParmName;
  sqlstm.sqhstl[1] = (unsigned long )33;
  sqlstm.sqhsts[1] = (         int  )0;
  sqlstm.sqindv[1] = (         short *)0;
  sqlstm.sqinds[1] = (         int  )0;
  sqlstm.sqharm[1] = (unsigned long )0;
  sqlstm.sqadto[1] = (unsigned short )0;
  sqlstm.sqtdso[1] = (unsigned short )0;
  sqlstm.sqhstv[2] = (unsigned char  *)&sysParmPlus;
  sqlstm.sqhstl[2] = (unsigned long )33;
  sqlstm.sqhsts[2] = (         int  )0;
  sqlstm.sqindv[2] = (         short *)0;
  sqlstm.sqinds[2] = (         int  )0;
  sqlstm.sqharm[2] = (unsigned long )0;
  sqlstm.sqadto[2] = (unsigned short )0;
  sqlstm.sqtdso[2] = (unsigned short )0;
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
  if (sqlca.sqlcode < 0) goto sql_error;
}


   
  charValue.arr[charValue.len] = '\0';
  scharValue = (char *)charValue.arr;
  return (scharValue);

 sql_error:
  cerr << "INFO - Le parametre " << c_sysParmName << " n est pas renseigne \n";
  charValue.arr[0] = '\0';
  scharValue = (char *)charValue.arr;
  return (scharValue);
}

//SMD
// Name : getFloat
// Desc :
//EMD
bool YmIrSysParms::getFloat(char *c_sysParmName, char *c_sysParmPlus,float &floatValue)
{
  /* EXEC SQL BEGIN DECLARE SECTION; */ 

  float   l_floatValue;
  /* varchar sysParmName[31]; */ 
struct { unsigned short len; unsigned char arr[31]; } sysParmName;

  /* varchar sysParmPlus[31]; */ 
struct { unsigned short len; unsigned char arr[31]; } sysParmPlus;

  /* EXEC SQL END DECLARE SECTION; */ 

    
  strcpy((char *)sysParmName.arr, c_sysParmName);
  sysParmName.len = strlen((const char *)sysParmName.arr);

  strcpy((char *)sysParmPlus.arr, c_sysParmPlus);
  sysParmPlus.len = strlen((const char *)sysParmPlus.arr);

  /* EXEC SQL WHENEVER SQLERROR GOTO sql_error; */ 

  /* EXEC SQL CONTEXT USE :ctxMain; */ 

  /* EXEC SQL SELECT float_value
    INTO :l_floatValue
    FROM ym_sys_parms
    WHERE sys_parm_name = :sysParmName
    AND sys_parm_plus = nvl(:sysParmPlus, ' '); */ 

{
  struct sqlexd sqlstm;
  sqlstm.sqlvsn = 12;
  sqlstm.arrsiz = 3;
  sqlstm.sqladtp = &sqladt;
  sqlstm.sqltdsp = &sqltds;
  sqlstm.stmt = "select float_value INTO :b0 FROM ym_sys_parms WHERE sys_pa\
rm_name = :b1 AND sys_parm_plus = nvl ( :b2 , ' ' ) ";
  sqlstm.iters = (unsigned int  )1;
  sqlstm.offset = (unsigned int  )32;
  sqlstm.selerr = (unsigned short)1;
  sqlstm.cud = sqlcud0;
  sqlstm.sqlest = (unsigned char  *)&sqlca;
  sqlstm.sqlety = (unsigned short)4352;
  sqlstm.occurs = (unsigned int  )0;
  sqlstm.sqhstv[0] = (unsigned char  *)&l_floatValue;
  sqlstm.sqhstl[0] = (unsigned long )sizeof(float);
  sqlstm.sqhsts[0] = (         int  )0;
  sqlstm.sqindv[0] = (         short *)0;
  sqlstm.sqinds[0] = (         int  )0;
  sqlstm.sqharm[0] = (unsigned long )0;
  sqlstm.sqadto[0] = (unsigned short )0;
  sqlstm.sqtdso[0] = (unsigned short )0;
  sqlstm.sqhstv[1] = (unsigned char  *)&sysParmName;
  sqlstm.sqhstl[1] = (unsigned long )33;
  sqlstm.sqhsts[1] = (         int  )0;
  sqlstm.sqindv[1] = (         short *)0;
  sqlstm.sqinds[1] = (         int  )0;
  sqlstm.sqharm[1] = (unsigned long )0;
  sqlstm.sqadto[1] = (unsigned short )0;
  sqlstm.sqtdso[1] = (unsigned short )0;
  sqlstm.sqhstv[2] = (unsigned char  *)&sysParmPlus;
  sqlstm.sqhstl[2] = (unsigned long )33;
  sqlstm.sqhsts[2] = (         int  )0;
  sqlstm.sqindv[2] = (         short *)0;
  sqlstm.sqinds[2] = (         int  )0;
  sqlstm.sqharm[2] = (unsigned long )0;
  sqlstm.sqadto[2] = (unsigned short )0;
  sqlstm.sqtdso[2] = (unsigned short )0;
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
  if (sqlca.sqlcode < 0) goto sql_error;
}



  floatValue = l_floatValue;
  return (true);

 sql_error:
  cerr << "INFO - Le parametre " << c_sysParmName << " n est pas renseigne \n";
  return (false);
}

//SMD
// Name : getInt
// Desc :
//EMD
bool YmIrSysParms::getInt(char *c_sysParmName, char *c_sysParmPlus ,int &intValue)
{
  /* EXEC SQL BEGIN DECLARE SECTION; */ 

  int     l_intValue;
  /* varchar sysParmName[31]; */ 
struct { unsigned short len; unsigned char arr[31]; } sysParmName;

  /* varchar sysParmPlus[31]; */ 
struct { unsigned short len; unsigned char arr[31]; } sysParmPlus;

  /* EXEC SQL END DECLARE SECTION; */ 

    
  strcpy((char *)sysParmName.arr, c_sysParmName);
  sysParmName.len = strlen((const char *)sysParmName.arr);
  strcpy((char *)sysParmPlus.arr, c_sysParmPlus);
  sysParmPlus.len = strlen((const char *)sysParmPlus.arr);

  /* EXEC SQL WHENEVER SQLERROR GOTO sql_error; */ 

  /* EXEC SQL CONTEXT USE :ctxMain; */ 

  /* EXEC SQL SELECT float_value
    INTO :l_intValue
    FROM ym_sys_parms
    WHERE sys_parm_name = :sysParmName
    AND sys_parm_plus = nvl(:sysParmPlus, ' '); */ 

{
  struct sqlexd sqlstm;
  sqlstm.sqlvsn = 12;
  sqlstm.arrsiz = 3;
  sqlstm.sqladtp = &sqladt;
  sqlstm.sqltdsp = &sqltds;
  sqlstm.stmt = "select float_value INTO :b0 FROM ym_sys_parms WHERE sys_pa\
rm_name = :b1 AND sys_parm_plus = nvl ( :b2 , ' ' ) ";
  sqlstm.iters = (unsigned int  )1;
  sqlstm.offset = (unsigned int  )59;
  sqlstm.selerr = (unsigned short)1;
  sqlstm.cud = sqlcud0;
  sqlstm.sqlest = (unsigned char  *)&sqlca;
  sqlstm.sqlety = (unsigned short)4352;
  sqlstm.occurs = (unsigned int  )0;
  sqlstm.sqhstv[0] = (unsigned char  *)&l_intValue;
  sqlstm.sqhstl[0] = (unsigned long )sizeof(int);
  sqlstm.sqhsts[0] = (         int  )0;
  sqlstm.sqindv[0] = (         short *)0;
  sqlstm.sqinds[0] = (         int  )0;
  sqlstm.sqharm[0] = (unsigned long )0;
  sqlstm.sqadto[0] = (unsigned short )0;
  sqlstm.sqtdso[0] = (unsigned short )0;
  sqlstm.sqhstv[1] = (unsigned char  *)&sysParmName;
  sqlstm.sqhstl[1] = (unsigned long )33;
  sqlstm.sqhsts[1] = (         int  )0;
  sqlstm.sqindv[1] = (         short *)0;
  sqlstm.sqinds[1] = (         int  )0;
  sqlstm.sqharm[1] = (unsigned long )0;
  sqlstm.sqadto[1] = (unsigned short )0;
  sqlstm.sqtdso[1] = (unsigned short )0;
  sqlstm.sqhstv[2] = (unsigned char  *)&sysParmPlus;
  sqlstm.sqhstl[2] = (unsigned long )33;
  sqlstm.sqhsts[2] = (         int  )0;
  sqlstm.sqindv[2] = (         short *)0;
  sqlstm.sqinds[2] = (         int  )0;
  sqlstm.sqharm[2] = (unsigned long )0;
  sqlstm.sqadto[2] = (unsigned short )0;
  sqlstm.sqtdso[2] = (unsigned short )0;
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
  if (sqlca.sqlcode < 0) goto sql_error;
}



  intValue = l_intValue;
  return (true);

 sql_error:
  cerr << "INFO - Le parametre " << c_sysParmName << " n est pas renseigne \n";
  return (false);
}
