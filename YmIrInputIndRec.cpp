//## Module : YmIrInputIndRec
//SFD
//  Name    : YmIrInputIndRec.cpp
//  Author  : Jacques FUTERAL 
//  Desc    : create record for the IndRecord File   
//EFD

using namespace std;

//## Includes
#include <stdlib.h> 
#include "YmIrInputIndRec.h"
#include "YmMessLog.h"

//SMD
// Name : YmIrInputIndRec::YmIrInputIndRec(char * buffer)    
// Desc : Constructor for the IND input record 
//        creates a structure record from the input buffer
//        this record contains all the infomartions for the Ind Output Record  
//        initiates the tranche number, the departure date, the number of legs, 
//        the number of base calls of service , the number of buckets 
//        the it copies, the leg header section, the bcs, the leg bucket section
//	  for future use
//EMD
YmIrInputIndRec::YmIrInputIndRec(char *buffer)    
{
  char   	  ltranche_no[4];
  unsigned char   lbyte = 0;
  unsigned short  lnb_legs = 0;
  unsigned short  lnb_bcs = 0;
  unsigned short  lnb_buc = 0;
  unsigned short  lnb_days = 0;
  unsigned short  lordinalTypeEquip = 0;
  char		  l_ID6TH0 = 0;
  char		  l_ID6TH1 = 0;
  char		  l_ID6TH2 = 0;
  int		  llegbuclen = 0;

  _nb_legs = 0; 
  _nb_bcs  = 0; 
  _nb_days = 0;
  _nb_buc  = 0;
char temp[LGHEADERDATE];
  /* Tranche Number */
  ltranche_no[0] = 0 ; 
  
  memcpy(&ltranche_no[1], &buffer[POS_TRANCHE - ID_LEN], 3);
  memcpy(&_trancheNo, ltranche_no, 4);

  /* Number of days since 1/2/1966 */
  temp[0] = buffer[POS_NB_DAYS_LL - ID_LEN + 1];
  temp[1] = buffer[POS_NB_DAYS_LL - ID_LEN];
  memcpy(&lnb_days, &temp[0],LGHEADERDATE);
  if ((lnb_days < 10000) || (lnb_days > 100000))
    {
      _nb_days = 0;
      YmMessLog rMess(__FILE__, "YmIrInputIndRec", PROCESS_NAME);
      string ltext = string("Incorrect number of days \n");
      rMess.envoiMess(__LINE__, ltext, YmMessLog::ERROR);
    }
  else  
    _nb_days = lnb_days;

  /* Type equipement */
  /* Inutile pour l'indrevenu
   *  lordinalTypeEquip = buffer[POS_ID6EQP - ID_LEN];
   *  if ((lordinalTypeEquip < 0) || (lordinalTypeEquip > MAX_ORDINAL_TYPE_EQUIP))
   *    {
   *      _ordinal_TypeEquip = 0;
   *      _codeEquip.clear();
   *      YmMessLog  lmess(__FILE__, "YmIrInputIndRec", PROCESS_NAME);
   *      char szMess[100];
   *      sprintf(szMess, "type equipement ordinal %d inexistant pour tranche %d", lordinalTypeEquip, _trancheNo);
   *      string ltext = string(szMess);
   *      lmess.envoiMess(__LINE__, ltext, YmMessLog::WARN);
   *    }
   *  else
   *    {
   *      _ordinal_TypeEquip = lordinalTypeEquip;
   *      YmTypeEquip *pTypeEquip = g_MapTypeEquip.isInMap(lordinalTypeEquip);
   *      if (pTypeEquip == NULL)
   *	_codeEquip.clear();
   *      else
   *	this->set_codeEquip(pTypeEquip->get_codeEquipement());
   *    } */
  

  /* Type algo */
  char cTypeAlgo = buffer[POS_ID6AVN - ID_LEN];
  _typeAlgo.clear();
  if (cTypeAlgo & ID6AGP)
    _typeAlgo = 'P';
  else if (cTypeAlgo & ID6AGD)
    _typeAlgo = 'D';

  /* Nature Tranche */
  _nature_Tranche = 0;
  if (!buffer[ POS_NATURE_TRANCHE])
    _nature_Tranche = 0;
  else
    {
      if (buffer[POS_NATURE_TRANCHE] & 8)
	_nature_Tranche = 1;
      else if (buffer[POS_NATURE_TRANCHE] & 4)
	_nature_Tranche = 2;
      else if (buffer[POS_NATURE_TRANCHE] & 2)
	_nature_Tranche = 3;
    }

  if (_nature_Tranche == 0)
    {
      if (!buffer[POS_NATURE_BI_TRANCHE])
	_nature_Tranche = 0;
      else
	{
	  if (buffer[POS_NATURE_BI_TRANCHE] & 128)
	    _nature_Tranche = 4;
	  else if (buffer[POS_NATURE_BI_TRANCHE] & 64)
	    _nature_Tranche = 5;
	}
    }

  /* Number of legs */
  char correct[LGHEADERDATE];
  correct[0] = buffer[POS_NB_LEG  - ID_LEN + 1];
  correct[1] = buffer[POS_NB_LEG  - ID_LEN];
  memcpy(&lnb_legs, &correct[0],LGHEADERDATE);
  cout << "Value of lnb_legs" << lnb_legs << endl ;
  
  if ((lnb_legs < 0) || (lnb_legs > MAX_NB_LEG))
    {
      _nb_legs = 0;
      YmMessLog lmess(__FILE__, "YmIrInputIndRec", PROCESS_NAME);
      string ltext = "Incorrect number of legs \n";
      lmess.envoiMess(__LINE__, ltext, YmMessLog::ERROR);
    }
  else
    _nb_legs = lnb_legs;
  cout << "Value of lnb_legs if it passes through else is  " << _nb_legs << endl ;
  /* Determines if the tranche is yield managed or not */
  memcpy(&l_ID6TH1, &buffer[POS_ID6TH1 - ID_LEN], 1);
  /* Not yield managed = NYM */ 
  if ((l_ID6TH1 & ID6NYM) == ID6NYM)  
    _isYieldManaged = false;
  else
    _isYieldManaged = true;

  /* Check if the tranche is YM by Netnesting or by Threshold */ 
  memcpy(&l_ID6TH2, &buffer[POS_ID6TH2 - ID_LEN], 1);

  if ((l_ID6TH2 & ID6NET) == ID6NET)
    {
      _isYMNetNesting = true;
      _isYMThreshold  = false;
    }
  else
    {
      _isYMNetNesting = false;
      _isYMThreshold  = true;
    }

  /* Check if the tranche is used or not */
  _isUsed = true;

  memcpy(&l_ID6TH0, &buffer[POS_ID6TH0 - ID_LEN], 1);

  if ((l_ID6TH0 & ID6CNX) == ID6CNX)
    /* If the tranche is cancelled */
    _isUsed = false;
  else if ((l_ID6TH1 & ID6FXS) == ID6FXS)
    /* If the tranche is NOOped */
    _isUsed = false ;
  else if  ((l_ID6TH0 & ID6PVT) == ID6PVT)
  {
    /* If the tranche is provisional */
    //_isUsed = false ;
	_isUsed = true ;
  }

  /* Number of bcs */
  char shift[LGHEADERDATE];
  shift[0] = buffer[POS_NB_BCS  - ID_LEN + 1];
  shift[1] = buffer[POS_NB_BCS  - ID_LEN];
  
  memcpy(&lnb_bcs, &shift,LGHEADERDATE);
  cout << "Value of lnb_bcs " << lnb_bcs << endl ;
  if ((lnb_bcs < 0) || (lnb_bcs > MAX_BCS ))
    {
      _nb_bcs = 0;
      YmMessLog lmess(__FILE__, "YmIrInputIndRec", PROCESS_NAME);
      string ltext = "Incorrect number of Base Class of Service \n";
      lmess.envoiMess(__LINE__, ltext, YmMessLog::ERROR);
    }
  else
    _nb_bcs = lnb_bcs;

  /* Number of buc */
  memcpy(&lnb_buc, &buffer[POS_NB_BU_TR - ID_LEN], 2);
  cout << "Value of lnb_buc" << lnb_buc << endl ;
  _nb_buc = lnb_buc;
  cout << "Value of nb_buc" << _nb_buc << endl ;
  /* Crosses Midnight */
  lbyte = buffer[POS_CR_MIDNIGHT - ID_LEN];
  _crossesMidnight = lbyte;

  /* Terminate Station */
  memcpy(_terminate, &buffer[gnHeaderLen - ID_LEN + _nb_legs * gnLegHeaderLen], 4);
  cout << "Value of _terminate  " << _terminate << endl ;
  for (int i = 0; i < _nb_legs; i++) 
    {
      /* Read the leg header */      
      for (int j = 0; j < gnLegHeaderLen; j++)
	_legHeader[i][j] = buffer[gnHeaderLen - 2 + gnLegHeaderLen * i + j];
    }

  for (int i = 0; i < get_nb_legs(); i++)
    {
      for (int j = 0; j < get_nb_bcs(); j++)
	{
	  for (int k = 0; k < gnLegBcsLen; k++)
	    _legBCS[i][j][k] = buffer[gnHeaderLen - ID_LEN + gnLegHeaderLen * get_nb_legs() +
				      TER_LEN + j * gnLegBcsLen + gnLegBcsLen * i * _nb_bcs + k];

	  _nb_buc = (int)(char)_legBCS[i][j][2];
	  for (int k1 = 0; k1 < _nb_buc; k1++)
	    {
	      for (int l = 0; l < gnLegBucketLen; l++)
		_legBucket[i][j][k1][l] =
		  buffer[gnHeaderLen - ID_LEN + gnLegHeaderLen * get_nb_legs() + TER_LEN + get_nb_bcs() *
			 gnLegBcsLen * get_nb_legs() + llegbuclen + k1 * gnLegBucketLen + l];
	    }

	  llegbuclen = _nb_buc * gnLegBucketLen + llegbuclen;
	}
    }

  /* Reads the supplement level */
  int i;

  i = gnHeaderLen - ID_LEN + gnLegHeaderLen * _nb_legs + TER_LEN + _nb_bcs * _nb_legs * gnLegBcsLen + llegbuclen + 4;
  memcpy(&_supplementLevel, &buffer[i], 1);
  cout << "Value of _supplementLevel  " << _supplementLevel << endl ;

  //DM 6882 TOP - MHUE
  i = gnHeaderLen - ID_LEN + gnLegHeaderLen * _nb_legs + TER_LEN + _nb_bcs * _nb_legs * gnLegBcsLen + llegbuclen + 12;
  memcpy(&_top, &buffer[i], 1);
   cout << "Value of _top  " << _top << endl ;
}
