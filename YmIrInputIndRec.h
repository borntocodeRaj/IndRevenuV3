//## Module : YmIrInputIndRec
//SFD
//  Name    : YmIrInputIndRec.h
//  Author  : Jacques FUTERAL 
//  Desc    : Class definition for the IND input record
//EFD

#ifndef YMIRINPUTINDREC 
#define YMIRINPUTINDREC 

//## Define
#define ID_LEN 			2	
#define INPUTINDREC_LEN 	4095
#define TRANCHE_HEADER_LEN	256
#define HEADER_LEN		848 
#define TER_LEN			4
#define LEG_HEADER_LEN		45
#define LEG_BCS_LEN		110
#define LEG_BUCKET_LEN		22
#define MAX_NB_LEG	 	80	
#define MAX_BCS		 	8	
#define MAX_BUCKETS		15	
#define MAX_BUCKETS_BCS		15	
#define MAX_ORDINAL_TYPE_EQUIP  999
#define LGHEADERDATE            2
/* Absolute position for the fields
 * ID6TCC resarail company code of the owner of this A-06-IND
 * ID6UID host company partition ordinal
 * ID6TNB tranche number in binary format
 * ID6DTE index date for this tranche this is the pars equivalent of the date on which the inventory
 * this is the same as the date of departure of the last leg
 * ID6EQP tranche equipment ordinal number
 * ID6STC service type code
 * ID6NDF net number of times this tranche crosses midnight between the origin and the departure of the last leg
 * ID6NLG number of legs of this tranche
 * ID6NBC number of base class of service for this tranche
 * ID6TNC total number of buckets for this tranche
 * ID6MXL maximum number of legs per tranche
 * ID6MXB maximum of base classes of services
 * ID6MXN maximum of nested buckets per base classes of services */

#define POS_TRANCHE  		55
#define POS_NB_DAYS_LL 		60
/* Train Realys (68 - ID_LEN) */
#define POS_NATURE_TRANCHE      65
/* Train Bitranche */
#define POS_NATURE_BI_TRANCHE	73
#define POS_CR_MIDNIGHT 	82
#define POS_NB_LEG	 	88
#define POS_NB_BCS		90
#define POS_NB_BU_TR		92
#define POS_DEST_STN		92
#define POS_FORWARD_CHAIN	8
#define POS_ID6TH0		214
#define POS_ID6TH1		215
#define POS_ID6TH2		216
#define POS_ID6EQP              80
#define POS_ID6AVN              85
#define ID6NET			'\x80'
#define ID6NYM			'\x04'
#define ID6PVT			'\x80'
#define ID6FXS			'\x80'
#define ID6CNX			'\x10'
#define ID6LOX			'\x80'
#define ID6LH1		        3
/* Types d'algorithme */
#define ID6AGP                  '\x20'
#define ID6AGD                  '\x10'
#define FORWARD_CHAIN		"\x00\x00\x00\x00"
#define POS_NB_BUC		2

//## Includes
#include <stdlib.h> 
#include <iostream>
#include <stdio.h>
#include <cstring>
#include <string>
#include "YmDate.h"
#include "YmIrGlobal.h"
#include "YmTools.h"

class  YmIrInputIndRec
{
 public:
  //## Constructeurs
  YmIrInputIndRec(char *);

  //## Accesseurs
  short		get_trancheNo() { return _trancheNo; }
  short		get_nb_days() { return _nb_days; }
  short		get_ordinal_TypeEquip() { return _ordinal_TypeEquip; }
  string	&get_codeEquip() { return  _codeEquip; }
  string	&get_typeAlgo() { return _typeAlgo; }
  unsigned char get_top() { return _top; }
  YmDate	get_dptDate()
    {
      YmDate d1;
      g_tools.transdate(d1, _nb_days) ; 
      return d1;
    }
  short		get_nb_legs() { return _nb_legs; }
  short		get_nb_bcs() { return _nb_bcs; }
  short		get_nb_bucs() { return _nb_buc; }
  unsigned char get_supplementLevel() { return _supplementLevel; }
  short		get_crossesMidnight() { return _crossesMidnight; }
  short		get_nb_bucs(int i, int j) { return (int)(_legBCS[i][j][POS_NB_BUC]); }
  bool		get_isLegCancel(int i)
    { 
      if ((_legHeader[i][ID6LH1] & ID6LOX) == ID6LOX) 
	return true ;
      else 
	return false ;
    }
  short		get_isYieldManaged() { return _isYieldManaged; }
  short		get_isUsed() { return _isUsed; }
  bool		get_isYMThreshold() { return _isYMThreshold; }
  bool		get_isYMNetNesting() { return _isYMNetNesting; }
  int		get_physicalCapacity(int i, int j)
    {
      short lshort;
      memcpy(&lshort, &_legBCS[i][j][4], 2);
      return lshort; 
    }
  char		get_BcsName(int i, int j) { return _legBCS[i][j][0]; }

  /* Returns the Nature of tranche for Realys train
   * the return value can be ID_NOT_REALYS. It isn't a realys train
   *                         ID_PRINC_REALYS.It is a realys train and a main tranche
   *                         ID_INTER_REALYS. It is a realys train and an Internationale tranche
   *                         ID_DEUTCH_REALYS. It is a realys train and a Deutch bahn tranche */
  short int	get_natureTranche() { return _nature_Tranche; }

  //## Mutateurs
  void set_codeEquip(string &value) { _codeEquip = value; }
  void set_typeAlgo(string & value) { _typeAlgo = value; }

  //## Donnees
  /* UNUSED */
  static int	_gsOpnIndCnt;
  /* UNUSED */
  static int	_glIndCnt;
  /* Destination de la tranches */
  char		_terminate[TER_LEN];
  /* Header de la description de la tranche */
  char		_header[HEADER_LEN];
  /* Header de la description du leg */
  char		_legHeader[MAX_NB_LEG][LEG_HEADER_LEN];
  /* Description des compartiments pour chaque leg */
  char		_legBCS[MAX_NB_LEG][MAX_BCS][LEG_BCS_LEN];
  /* Description des buckets pour chaques leg/compartiment */
  char		_legBucket[MAX_NB_LEG][MAX_BUCKETS][MAX_BUCKETS_BCS][LEG_BUCKET_LEN];

 private:
  //## Donnees
  /* Flag indiquant si la tranche est yield managed */
  bool		_isYieldManaged;
  /* Flag indiquant si la tranche est vraiment utilisee */
  bool		_isUsed;
  /* Flag indiquant si la methode threshold yield manage est utilise */
  bool		_isYMThreshold;
  /* Flag indiquant si la methode net nesting yield manage est utilise */
  bool		_isYMNetNesting;
  /* Numero de tranche */
  int		_trancheNo;
  /* Nature de la tranche */
  short		_nature_Tranche;
  /* Ordinal type equipement */
  short	        _ordinal_TypeEquip;
  /* Code equipement */
  string	_codeEquip;
  /* Type algorithme */
  string	_typeAlgo;
  /* Nombre de jours depuis 1996 jusqua la date de depart de la tranche */
  int		_nb_days;
  /* Date de depart de la tranche */
  YmDate	_dptDate;
  /* Nombre de legs */
  short		_nb_legs;
  /* Nombre de compartiment dans le leg */
  short		_nb_bcs;
  /* Nombre de buckets par compartiment */
  short		_nb_buc;
  /* Supplement level */
  unsigned char _supplementLevel;
  /* Top */
  unsigned char _top;
  /* Flag indiquant si la tranche passe minuit */
  int		_crossesMidnight;
};

#endif
