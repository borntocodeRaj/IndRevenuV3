//## Module : YmIrIndLoader
//SFD
//  Name    : YmIrIndLoader.h
//  Author  : Lienard william
//  Desc    : description of classes used in IND processing for the processing
//	      itself providing data from IND processing to PNI processing
//EFD

#ifndef _YMIRINDLOADER_H
#define _YMIRINDLOADER_H

//## Includes
#include <stdlib.h>
#include <map>
#include <list>
#include <iostream>
#include "YmDate.h"
#include "YmIrInputIndRec.h"
#include "YmIrIndOutputRec.h"

//## Defines
#define USEDPARTOFLASTRECORD	 50
#define POSOFLASTRECORDNAME	 22
#define LGOFLASTRECORDNAME	 18
#define CONTENTOFLASTRECORD	 "COLLECTOR COMPLETE"

/* Dans le cas d'un enregistrement not prime,l'entete du not prime doit etre enlevee
 * pour pouvoir coller l'enregsitrement au prime */
#define NPRM_HDR_LEN		 30
/* Dans buffers suite */
#define POS_TRNO		 16
/* valeur de N en EBCDIC */
#define N_EBCDIC (unsigned char) 0xD5
/* Position du code qualite commerciale */
#define POS_ID6STC		 81
#define PNI_LEN			 4095
#define IND_LEN			 4095
#define IND_LEN_MAX		 4095
#define IC_LEN			 4095
#define PNI_IDENTIFER		 "PD"
#define IND_IDENTIFER		 "ID"
#define IC_IDENTIFER		 "IC"
#define ID_LEN			 2
#define PNI_REC_LEN		 64
/* 3 caracteres a enlever si pas le dernier overflow ni primaire */
#define FIN_OVERFLOW_LEN	 3
#define HEADER_FILE_SIZE	 1055

//description du header
#define POSHEADERTEXT		 20
#define LGHEADERTEXT		 20
#define POSHEADERDATE		 52
#define LGHEADERDATE		 2
#define POSHEADERTIME		 48
#define LGHEADERTIME		 4


//## Structure
/* Structure pour stocker le buffer */
typedef struct buffer_
{
  char *ar;
  /* Compteur */
  int  cnt;
  int  lPrimaryBuffer;
  int  nbBcsRestant;
  int  nbBuckRestant;
} t_buffer;

typedef multimap<int,t_buffer *,std::less<int> > ChainMapType;

class YmIrIndLoader
{
 public:
  //## Constructeurs
  YmIrIndLoader(YmDate infoBatchDate, string sInputFileName);

  //## Destructeur
  ~YmIrIndLoader();

  //## Accesseurs
  const YmDate get_pniIndDate() const { return _pniIndDate; }

  //## Autres
  short  Validate();
  /* On determine ici pour quelle date la tranche doit etre selectionnee
   * En effet une tranche date peut etre portee par des trains partant a
   * des dates differentes */
  bool  LectureInd(YmIrDvLoader *_dvLoader);
  void CleanChainMap();

 private:
  //## Donnees
  /* Derniere date de collecte des donnees */ 
  YmDate       _lastInfoBatchDate;
  /* Nom du fichier IND */
  string       _inputFileName;
  /* Date PNI/IND */
  YmDate       _pniIndDate;
  /* Structure pour stocker un enregistrement */
  ChainMapType _chainMap ;

  //## Autres
  bool ReadHeader(FILE ** pf_if);
  bool Get_buffer_chained(char *, int, int) ;
  bool isTrancheRejected(YmIrInputIndRec) ;
  void YmIrIndLoaderClearTemp(list<YmIrIndOutputRec *> *_outSlisttemp);
};

#endif
