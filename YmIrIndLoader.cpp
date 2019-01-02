//## Module : YmIrIndLoader
//SFD
//  Name    : YmIrIndLoader.cpp
//  Author  : M. Hue
//  Desc    : Load the IND from the resarail file and put it into a Map of
//	      Sorted List for each reading days
//	      This process uses the multithreading
//EFD

using namespace std;

//## Includes
#include <iostream>
#include <stdlib.h>
#include <string>
#include <map>
#include <list>
#include "YmIrInfoBatch.h"
#include "YmIrGlobal.h"
#include "YmDate.h"
#include "YmIrTranche.h"
#include "YmIrDvLoader.h"
#include "YmIrIndLoader.h"
#include "YmIrSysParms.h"
#include "YmMessLog.h"
#include "YmIrInputIndRec.h"
#include "YmIrIndOutputRec.h"
#include "YmIrDataValidator.h"
#include "YmTools.h"
#include "YmMapDatesIrATraiter.h"
#include "YmTranche.h"
#include "YmTraitementTables.h"


//SMD
//  Name : YmIrIndLoader
//  Desc : Constructor for the Loader
//         creates a Loader and initiates it with the parameters of the scheduler
//EMD
YmIrIndLoader::YmIrIndLoader(YmDate infoBatchDate, string sInputFileName)
{
  _lastInfoBatchDate = infoBatchDate;
  _inputFileName = sInputFileName;
}

//SMD
// Name : ~YmIrIndLoader
// Desc : Destructeur par defaut
//EMD
YmIrIndLoader::~YmIrIndLoader()
{
}

//SMD
// Name : ReadHeader
// Desc : Open the resarail input file and read the Header file and test
//EMD
bool YmIrIndLoader::ReadHeader(FILE **f_if)
{
  char buffer[IND_LEN];
  char *lprefixeName;
  char *lchemin;

  /* Test if the file is Valid */
  *f_if = fopen(_inputFileName.data(), "r");
  if (*f_if == NULL)
    {
      cerr << "YmIrIndLoader : YmIrIndLoader.cpp : 101 : ReadHeader : impossible d'ouvrir le fichier IND  "
	   << _inputFileName << "\n";
      exit(12);

      return false;
    }

  /* Read the header of the file */
  if (fread((void *)buffer, HEADER_FILE_SIZE, 1, *f_if) == 0)
    {
      cerr << "YmIrIndLoader : YmIrIndLoader.cpp : 101 : ReadHeader : impossible de lire le header du fichier "
	   << _inputFileName << "\n";
      exit(13);

      return false;
    }

  /* Conversion of the part of the header where the text "PNI COLLECTOR..." is to be found */
  g_tools.convertEBC2ASC(&buffer[POSHEADERTEXT], LGHEADERTEXT);

  /* If the text is not found here then the file is not a resarail file */
  if(strncmp(&buffer[POSHEADERTEXT], "PNI COLLECTOR HEADER", LGHEADERTEXT))
    {
      /* Pas le bon fichier */
      cerr << "YmIrIndLoader : YmIrIndLoader.cpp : 101 : ReadHeader : header incorrect pour le fichier "
	   << _inputFileName << "\n";
      exit(13);

      return false;
    }

  /* Test if the date of the file is the collection date + 1 */
  short lIrDays;
char temp[LGHEADERDATE];
 /*conversion of Big Endian to Little Endian*/
 

  /* conversion of the date of the file as written in the header(nb of days) */

  g_tools.convertEBC2ASC(&buffer[POSHEADERTIME], LGHEADERTIME);
        temp[0] = buffer[POSHEADERDATE + 1];
	temp[1] = buffer[POSHEADERDATE];
  memcpy(&lIrDays, &temp[0], LGHEADERDATE);
  if((lIrDays < 10000) || (lIrDays > 100000))
    {
      cerr << "YmIrIndLoader : YmIrIndLoader.cpp : 101 : ReadHeader : date des donnees incorrecte dans le fichier "
	   << _inputFileName << "\n";
      exit(13);

      return false;
    }

  /* conversion from number of days to date */
  g_tools.transdate(_pniIndDate, lIrDays);

  /* If the time is less than the values contained in the parameters table, the date in the file becomes date -1 day */
  char lTravH[3];
  char lTravM[3];
  int  iComp1, iComp2;

  /* Lecture du parametre PNI_IND_TIME */
  YmIrSysParms laparm;
  string lTime(laparm.getChar((char *)"PNI_IND_TIME", (char *)""));
  if(lTime == string(""))
    {
      cerr << "YmIrIndLoader YmIrIndLoader.cpp : 169 : ReadHeader: PNI_IND_TIME system parameter not found - abort\n";
      exit(14);

      return false;
    }

  /* Time as written in the file converted in HHMM value */
     
  
  memcpy(&lTravH, &buffer[POSHEADERTIME], LGHEADERDATE);
  cout << "value of lTravH before memcpy  " << lTravH << endl ;
  lTravH[2] = '\0';
  iComp1 = atoi(lTravH) * 100;
  memcpy(&lTravM, &buffer[POSHEADERTIME + 2],LGHEADERDATE);
  cout << "value of lTravM before memcpy  " << lTravM << endl;
  iComp1 += atoi(lTravM);

  /* INFO  de la date/time du fichier */
  YmMessLog lmess2(__FILE__, "ReadHeader", PROCESS_NAME);
  string ltext2("le fichier PNI/IND ");
  ltext2 += _inputFileName;
  ltext2 += " contient les donnees du ";
  string szDt;
  ltext2 += _pniIndDate.PrintFrench(szDt);
  ltext2 += " a ";
  ltext2 += lTravH;
  ltext2 += "H";
  lTravM[2] = '\0';
  ltext2 += lTravM;
  cout << "value of ltext2" << ltext2 ;
  lmess2.envoiMess(__LINE__, ltext2, YmMessLog::INF);

  /* Time as written in PNI_IND_TIME converted in HHMM value */
  memcpy(&lTravH, lTime.data(), 2);
  cout << "value of lTravH after memcpy  " << lTravH << endl ;
  lTravH[2] = '\0';
  iComp2 = atoi(lTravH)*100;
  memcpy(lTravM, &(lTime.data())[2], 2);
  lTravM[2] = '\0';
  iComp2 += atoi(lTravM);

  YmDate lDate = YmDate(_pniIndDate);
  cout << "value of lDate after YmDate" << lDate << endl ;
  /* values comparison */
  if (iComp2 > iComp1)
    /* In reality the date is yesterday */
    lDate -= 1;

  /* Now, the date of the file is correct. elle doit etre collection date + 1 if not, the file must not be processed */
  int idiffdays = 0;
  idiffdays += lDate.DaysFrom70();
  idiffdays -= _lastInfoBatchDate.DaysFrom70();
  string slast;
  string slDate;
  lDate.PrintResaven(slDate, true);
  _lastInfoBatchDate.PrintResaven(slast, true);

  if (idiffdays != 1)
    {
      YmMessLog lmess(__FILE__, "ReadHeader", PROCESS_NAME);
      string ltext("le fichier ");
      ltext += _inputFileName;
      ltext += " est pour le: ";
      string szDt;
      ltext += lDate.PrintFrench(szDt);
      ltext += " la date du dernier Batch termine est: ";
      ltext += _lastInfoBatchDate.PrintFrench(szDt);
      ltext += " le traitement ne peut avoir lieu - abort\n";
      lmess.envoiMess(__LINE__, ltext, YmMessLog::ERROR);

      return false;
    }

  return true;
}

//SMD
// Name : YmIrIndLoaderClearTemp
// Desc : Vidage de la liste temporaire
//EMD
void YmIrIndLoader::YmIrIndLoaderClearTemp(list<YmIrIndOutputRec *> *_outSlisttemp)
{
  list<YmIrIndOutputRec *>::iterator litr = _outSlisttemp->begin();
  list<YmIrIndOutputRec *>::iterator litrFin = _outSlisttemp->end();
  while (litr != litrFin)
    {
      delete *litr;
      litr++;
    }
  _outSlisttemp->clear();
}

//SMD
// Name : YmIrIndLoader::LectureInd(bool bTrd, YmIrDvLoader *_dvLoader)
// Desc : Validation of Ind Record
//        Creates an instance of the DataValidator
//        Opens the Input File which contains Ind records
//        verifies that the header is correct
//        reads the records in a loop
//        PNI and IC records are skipped
//        creates from each record in the input file one record by calling the
//        YmIrInputIndRec constructor and then several YmIrIndOutputRec
//        validates the the records by calling the DataValidator
//        bTrd = true si on veut traiter les CORAIL, = false si on traite les TGV
//        si bTrd = false alors _dvLoader = NULL
//EMD
bool YmIrIndLoader::LectureInd(YmIrDvLoader *_dvLoader)
{
  /* ID, PD, IC */
  char			   id_buf[ID_LEN + 1];
  char			   buffer[IND_LEN * 10];
  int			   lpos_in_file = 1095;
  int			   lnumber_pni = 0;
  int			   lnumber_ind = 0;
  int			   lnumber_indOK = 0;
  int			   lnb_buc;
  YmTranche		   *pYmTranche;
  YmLeg			   *pYmLeg;

  /* Tranche trouvee pour les CORAIL */
  YmIrTranche		   *pTranche;
  int			   _inventoryNestMethod;
  YmIrIndOutputRec	   *lIndOutputRecP;
  YmIrDataValidator	   *lpDataValidator;

  /* Type d'enregistrements */
  /* PD */
  string		   lid_pd(PNI_IDENTIFER);
  /* ID */
  string		   lid_id(IND_IDENTIFER);
  /* IC */
  string		   lid_ic(IC_IDENTIFER);

  /* Slist temporaire pour stocker les enregistrements avant la mise definitive dans la structure chainee */
  list<YmIrIndOutputRec *> _outSlisttemp;

  /* Address of the previous record when the records are chained */
  int   lprevAddress = 0;
  /* Address of the next record when the records are chained */
  int   lnextAddress = 0;
  id_buf[2] = 0;

  /* Fichier PNI/IND */
  FILE *f_if;

  /* Fetch the nesting method(NetNesting or Threshold) */
  YmIrSysParms laparm;
  if (!laparm.getInt((char *)"INVENTORY_NESTING_METHOD", (char *)"", _inventoryNestMethod))
    /* On met 1 par defaut si on trouve pas la valeur */
    _inventoryNestMethod = 1;

  /* Opens a file and reads the header file */
  if (ReadHeader(&f_if) == false)
    return false;

  /* Create one instance of the DataValidator */
  lpDataValidator = lpDataValidator->Instance();
  bool lisTrancheRejected;

  while (fread((void *)id_buf, 2, 1, f_if) != 0) /*lecture des 2 premiers caracteres - determination du type d'enreg */
    {
      g_tools.convertEBC2ASC(id_buf, 2);
      memset(buffer, 1200, IND_LEN_MAX * 10);

      /* if the record is a pni, the record is skipped */
      if (id_buf == lid_pd)
	{
	  if (fread((void *)buffer, gnPniLength - ID_LEN, 1, f_if)== 0)
	    {
	      cerr << "YmIrIndLoader : YmIrIndLoader.cpp : 284 : lectureInd : erreur fichier : " << PROCESS_NAME << " \n";

	      return false;
	    }

	  lpos_in_file += gnPniLength;
	}
      else if (id_buf == lid_ic)
	{
	  if (fread((void *)buffer, IC_LEN-ID_LEN, 1, f_if)== 0)
	    {
	      cerr << "YmIrIndLoader : YmIrIndLoader.cpp : 296 : lectureInd : erreur fichier : " << PROCESS_NAME << " \n";

	      return false;
	    }

	  lpos_in_file += IC_LEN;
	}
      else if (id_buf == lid_id)
	{
	  if (fread((void *)buffer, IND_LEN-ID_LEN, 1, f_if)== 0)
	    {
	      cerr << "YmIrIndLoader : YmIrIndLoader.cpp : 305 : lectureInd : erreur fichier : " << PROCESS_NAME << " \n";

	      return false;
	    }

	  lpos_in_file  += IND_LEN;
	  lnumber_ind++;

	  /* PGM = previous address */
	  memcpy(&lprevAddress, &buffer[2], 4);
	  /* FCH = next adress */
	  memcpy(&lnextAddress, &buffer[6], 4);

	  if ((lnextAddress != 0L)||(lprevAddress != 0L))
	    {
	      if (Get_buffer_chained(buffer, lnextAddress, lprevAddress) == 1)
		{
		  lnumber_indOK++;

		  continue;
		}
	    }

	  YmIrInputIndRec lInputIndRec(buffer);
	  /* Calculates the departure date of the first leg */
	  YmDate ldate_rd(lInputIndRec.get_dptDate());
	  ldate_rd -= lInputIndRec.get_crossesMidnight();

	  pYmTranche = new YmTranche(lInputIndRec.get_trancheNo(), ldate_rd);

	  YmDate lastDataDate = _lastInfoBatchDate;
	  --lastDataDate;

	  if (ldate_rd < lastDataDate)
	    /* Jour incomplet */
	    continue;
		//IC SRO - DT 23805 - JRO
		/*
	  if (lInputIndRec.get_isYieldManaged() == false)
	    {
	      /* Rejet, mise en place dans REV_TRANCHES_NON_YIELD 
	      g_traitementTables.InsererVRtny(pYmTranche);

	      continue;
	    }
	*/

	  /* Dans le cas de l'indrevenu on prend TGV et CORAIL */
	  char ID6STC = 0;
	  memcpy(&ID6STC , &buffer[POS_ID6STC - ID_LEN], 1);

	  if ((unsigned char)ID6STC == N_EBCDIC)
	    {
	      if (g_bTrd != 1)
		/* On n'est pas en Corail, on rejete */
		continue;

	      /* On verifie si tranche est retenue par rapport aux donnees DV */
	      YmIrTranche tranche(pYmTranche->get_trancheNo(), ldate_rd);

	      string lDt;
	      ldate_rd.PrintResaven(lDt);
	      char szTranche[7];
	      sprintf(szTranche, "%06d", pYmTranche->get_trancheNo());
	      string defTranche_ = lDt + szTranche;

	      mapTranchesType::iterator iPosTranche;
	      mapTranchesType *selTranches_ = _dvLoader->get_selectedTrancheMap();
	      iPosTranche = selTranches_->find(defTranche_);

	      if (iPosTranche == selTranches_->end())
		/* Rejet on ne garde pas */
		continue;
	      else
		pTranche = iPosTranche->second;
	    }

	  if (lInputIndRec.get_isUsed() == false)
	    /* Tranche not used */
	    continue;

	  if (((lInputIndRec.get_isYMThreshold() == true) && (_inventoryNestMethod == 1))
	      ||((lInputIndRec.get_isYMThreshold() == false) && (_inventoryNestMethod == 0)))
	    {
	      YmMessLog lmess(__FILE__, "LectureInd", PROCESS_NAME);
	      string ltext("mauvaise nesting methode pour la tranche ");
	      char szTranche[7];
	      sprintf(szTranche, "%06d", pYmTranche->get_trancheNo());
	      ltext += szTranche;
	      ltext += " du ";
	      string szDt;
	      ltext += ldate_rd.PrintFrench(szDt);
	      lmess.envoiMess(__LINE__, ltext, YmMessLog::WARN);

	      continue;
	    }

	  /* Validation des differentes valeurs constitutives de la description de tranches */
	  bool lTrancheOk = true;
	  lIndOutputRecP = NULL;
	  YmDate rDateTrain;
	  int lFirstTime;
	  YmLeg *pLeg;

	  for (int i = 0; i < lInputIndRec.get_nb_legs() && lTrancheOk == true; i++)
	    {
	      lIndOutputRecP = new YmIrIndOutputRec(lInputIndRec, i, 0, 0, &g_MapStations);
	      if (i == 0)
		{
		  if ((unsigned char) ID6STC == N_EBCDIC)
		    {
		      /* Cas CORAIL */
		      if (g_bTrd != 1)
			/* On n'est pas en Corail, on rejete */
			continue;

		     // lTrancheOk = _dvLoader->DetermineTrancheTrain(pTranche, lIndOutputRecP->get_trainNo(), rDateTrain);
		      if (lTrancheOk == false)
			continue;

		      pYmTranche->set_dateTrain(rDateTrain);
		      pYmTranche->set_tgv(0);
		    }
		  else
		    {
		      /* Cas TGV */
		      pYmTranche->set_dateTrain(ldate_rd);
		      pYmTranche->set_tgv(1);
		    }

		  lFirstTime = lIndOutputRecP->get_legDptTime();
		}

	      pLeg = new YmLeg(pYmTranche, lIndOutputRecP->get_legOrig(), lIndOutputRecP->get_legDest(),
			       lIndOutputRecP->get_dptDate(), lIndOutputRecP->get_legDptTime(),
			       lIndOutputRecP->get_legArvTime(), lIndOutputRecP->get_trainNo()); //jro IC SRO - DT 23805 - Ajout train no

	      /* si l'heure de depart du leg est infirieure a celle de la tranche alors le leg est apres minuit
	       * il faut donc faire + 1 sur la date */
	      if (pLeg->get_dptTime() < lFirstTime)
		pLeg->add_dptDate();

	      pLeg->set_sequence(i);
	      /*  mise en place dans la liste des legs a gerer */
	      g_traitementTables.InsererVTtl(pLeg);
	    }
	}
      else
	/* Two possibilities: it's the last record and then, it's ok.
	 * it's not the last one and that means a fatal error! */
	{
	  char lszBLast[USEDPARTOFLASTRECORD + 1];

	  if (fread((void *)buffer, USEDPARTOFLASTRECORD, 1, f_if) != 0)
	    {
	      g_tools.convertEBC2ASC(&buffer[POSOFLASTRECORDNAME], LGOFLASTRECORDNAME);
	      memcpy(lszBLast, &buffer[POSOFLASTRECORDNAME], LGOFLASTRECORDNAME);
	      if(!strcmp(lszBLast, CONTENTOFLASTRECORD))
		/* ok it's the last record */
		return true;
	    }

	  YmMessLog lmess(__FILE__, "LectureInd", PROCESS_NAME);
	  string ltext("record de fin non trouve ou record non reconnu - process arrete ");
	  lmess.envoiMess(__LINE__, ltext, YmMessLog::ERROR);

	  return false;
	}
    }

  /* damned! the last record has not been found in the file! */
  YmMessLog lmess(__FILE__, "LectureInd", PROCESS_NAME);
  string ltext("record de fin non trouve ou record non reconnu - process arrete ");
  lmess.envoiMess(__LINE__, ltext, YmMessLog::ERROR);

  return false;
}

//SMD
// Name : isTrancheRejected()
// Desc : Test if for a same bcs through the legs of a tranche, the physical capacity remains the same.
//        If not, the tranche is rejected
//EMD
bool YmIrIndLoader::isTrancheRejected(YmIrInputIndRec lInputIndRec)
{
  int lIrLegs, lIrBcs;

  struct
  {
    char BcsName;
    int Capacity;
  } lCapacity[MAX_BCS];

  char lName;
  int  lCapa;
  bool lNotFound;

  lIrLegs = lInputIndRec.get_nb_legs();
  lIrBcs = lInputIndRec.get_nb_bcs();

  /* 1st leg data research. After that same data must be found for every leg */
  int Ir0 = 0;

  for (int j = 0; j < lIrBcs; j++)
    {
      lCapacity[j].BcsName = lInputIndRec.get_BcsName(0, j);
      lCapacity[j].Capacity = lInputIndRec.get_physicalCapacity(0, j);
      /* if physical capacity is 0, it must be rejected */
      if (lCapacity[j].Capacity == 0)
	Ir0++;
    }
  if (Ir0 == lIrBcs)
    return true;

  /* legs scanning */
  for (int i = 1; i < lIrLegs; i++)
    {
      for (int j = 0; j < lIrBcs; j++)
	{
	  lName = lInputIndRec.get_BcsName(i, j);
	  lCapa = lInputIndRec.get_physicalCapacity(i, j);
	  lNotFound = true;
	  for (int k = 0; k < lIrBcs; k++)
	    {
	      /* The same Bcs(same name)must have always the same capacity */
	      if(lName == lCapacity[k].BcsName)
		{
		  lNotFound = false;
		  if(lCapa != lCapacity[k].Capacity)
		    return true;
		  else
		    k = lIrBcs;
		}
	    }

	  if (lNotFound)
	    return true;
	}
    }

  return false;
}

//SMD
// Name : Get_buffer_chained()
// Desc : Test if the buffer is chained to another record
//EMD
bool YmIrIndLoader::Get_buffer_chained(char *buffer, int lnextAddress, int lprevAddress)
{
  t_buffer *lpt_buffer = NULL;
  t_buffer *lpt_buffer1 = NULL;
  unsigned short lIrBcs;
  unsigned short lIrLegs;
  unsigned short lIrBucs;
  unsigned short lReste;

  /* Pointeur sur l'addresse de l'enregistrement suivant ou precedent */
  int lp_adr;

  if ((lnextAddress != 0L) || (lprevAddress != 0L))
    {
      /* Un enregistrement existait deja avant, si on ne le trouve pas il n'est peut etre pas encore apparu */
      if (lprevAddress != 0L)
	{
	  lp_adr = lprevAddress;

	  ChainMapType::iterator iPos = _chainMap.find(lp_adr);

	  if ((iPos == _chainMap.end()) && (lnextAddress == 0L))
	    {
	      YmMessLog lmess(__FILE__, "Get_buffer_chained", PROCESS_NAME);
	      string ltext("le chain record IND n'a pas ete trouve ");
	      lmess.envoiMess(__LINE__, ltext, YmMessLog::ERROR);

	      return 1;
	    }
	  else if ((iPos == _chainMap.end()) && (lnextAddress  != 0L))
	    {
	      /* prime record */
	      YmMessLog lmess(__FILE__, "Get_buffer_chained", PROCESS_NAME);
	      string ltext("prime record non trouve - tranche incomplete ? ");
	      char szTrav[10];
	      memcpy(szTrav, &lpt_buffer->ar[POS_TRNO], 6);
	      szTrav[6] = 0x00;
	      g_tools.convertEBC2ASC(szTrav, 6);
	      ltext += szTrav;
	      ltext += "\n";
	      lmess.envoiMess(__LINE__, ltext, YmMessLog::WARN);

	      lpt_buffer1 = new t_buffer;
	      lpt_buffer1->ar = (char*)malloc(IND_LEN_MAX);
	      lpt_buffer1->cnt = 1;
              char correct[LGHEADERTEXT];
              correct[0] = buffer[POS_NB_LEG-ID_LEN + 1];
              correct[1] = buffer[POS_NB_LEG-ID_LEN];

	      memcpy(&lIrLegs, &buffer[POS_NB_LEG-ID_LEN], 2);
	      memcpy(&lIrBcs, &buffer[POS_NB_BCS-ID_LEN], 2);
	      memcpy(&lIrBucs, &buffer[POS_NB_BU_TR-ID_LEN], 2);

	      if (gnHeaderLen + gnLegHeaderLen * lIrLegs + TER_LEN + lIrLegs * lIrBcs * gnLegBcsLen > IND_LEN)
		{
		  lReste = (IND_LEN - gnHeaderLen - gnLegHeaderLen * lIrLegs - TER_LEN) % gnLegBcsLen;
		  lpt_buffer1->nbBcsRestant = (lIrLegs * lIrBcs) - ((IND_LEN - gnHeaderLen - gnLegHeaderLen *
								     lIrLegs - TER_LEN) / gnLegBcsLen);
		  lpt_buffer1->nbBuckRestant = lIrBucs * lIrLegs;
		  if (!lReste)
		    {
		      lReste = gnLegBcsLen;
		      lpt_buffer1->nbBcsRestant++;
		    }
		}
	      else
		{
		  lReste = (IND_LEN - gnHeaderLen - gnLegHeaderLen * lIrLegs - TER_LEN -
			    lIrBcs * lIrLegs * gnLegBcsLen) % gnLegBucketLen;

		  lpt_buffer1->nbBcsRestant = 0;
		  lpt_buffer1->nbBuckRestant = (lIrLegs * lIrBucs) - ((IND_LEN - gnHeaderLen - gnLegHeaderLen * lIrLegs - 
								       TER_LEN - lIrBcs * lIrLegs * gnLegBcsLen) /
								      gnLegBucketLen);

		  if (!lReste)
		    {
		      lReste = gnLegBucketLen;
		      lpt_buffer1->nbBuckRestant++;
		    }
		}

	      lpt_buffer1->lPrimaryBuffer = IND_LEN - ID_LEN - lReste;
	      memcpy(lpt_buffer1->ar, buffer, lpt_buffer1->lPrimaryBuffer);
	      lp_adr = lnextAddress;
	      _chainMap.insert(ChainMapType::value_type(lp_adr, lpt_buffer1));

	      return 1;
	    }

	  /* Last overflow record */
	  else if ((iPos != _chainMap.end()) && (lnextAddress == 0L))
	    {
	      lpt_buffer = iPos->second;
	      (lpt_buffer->cnt)++;
	      lpt_buffer->ar = (char*)realloc(lpt_buffer->ar, lpt_buffer->lPrimaryBuffer+IND_LEN-ID_LEN-NPRM_HDR_LEN);
	      memcpy(&lpt_buffer->ar[lpt_buffer->lPrimaryBuffer], 
		     &buffer[NPRM_HDR_LEN], IND_LEN - ID_LEN - NPRM_HDR_LEN);
	      memcpy(buffer, lpt_buffer->ar, lpt_buffer->lPrimaryBuffer+IND_LEN-ID_LEN-NPRM_HDR_LEN);
	      free(lpt_buffer->ar);

	      delete lpt_buffer;
	      _chainMap.erase(iPos);

	      return 0;
	    }
	  /* Overflowrecord but not the last */
	  else if ((iPos != _chainMap.end()) && (lnextAddress != 0L))
	    {
	      lpt_buffer = iPos->second;
	      lpt_buffer->cnt++;

	      if (NPRM_HDR_LEN + TER_LEN + lpt_buffer->nbBcsRestant * gnLegBcsLen > IND_LEN - ID_LEN)
		{
		  lReste = (IND_LEN - ID_LEN - NPRM_HDR_LEN - TER_LEN) % gnLegBcsLen;
		  lpt_buffer->nbBcsRestant -= ((IND_LEN - ID_LEN - NPRM_HDR_LEN - TER_LEN) / gnLegBcsLen);
		  if (!lReste)
		    {
		      lReste = gnLegBcsLen;
		      lpt_buffer->nbBcsRestant++;
		    }
		}
	      else
		{
		  lReste = (IND_LEN - ID_LEN - NPRM_HDR_LEN - TER_LEN - lpt_buffer->nbBcsRestant *
			    gnLegBcsLen) % gnLegBucketLen;

		  lpt_buffer->nbBcsRestant = 0;
		  lpt_buffer->nbBuckRestant -= ((IND_LEN - ID_LEN - NPRM_HDR_LEN - TER_LEN - lpt_buffer->nbBcsRestant *
						 gnLegBcsLen) / gnLegBucketLen);

		  if (!lReste)
		    {
		      lReste = gnLegBucketLen;
		      lpt_buffer->nbBuckRestant++;
		    }
		  if (lpt_buffer->nbBuckRestant < 0)
		    lpt_buffer->nbBuckRestant = 0;
		}

	      lpt_buffer->ar = (char*)realloc(lpt_buffer->ar, lpt_buffer->lPrimaryBuffer + IND_LEN - ID_LEN -
					      TER_LEN - NPRM_HDR_LEN - lReste);

	      memcpy(&lpt_buffer->ar[lpt_buffer->lPrimaryBuffer], &buffer[NPRM_HDR_LEN], IND_LEN - ID_LEN -
		     TER_LEN - NPRM_HDR_LEN - lReste);

	      lpt_buffer->lPrimaryBuffer += IND_LEN - ID_LEN - TER_LEN - NPRM_HDR_LEN - lReste;
	      lpt_buffer1 = new t_buffer;
	      lpt_buffer1->ar = (char*)malloc(lpt_buffer->lPrimaryBuffer);
	      lpt_buffer1->cnt = lpt_buffer->cnt;
	      memcpy(lpt_buffer1->ar, lpt_buffer->ar, lpt_buffer->lPrimaryBuffer);
	      lpt_buffer1->lPrimaryBuffer = lpt_buffer->lPrimaryBuffer;
	      lpt_buffer1->nbBcsRestant = lpt_buffer->nbBcsRestant;
	      lpt_buffer1->nbBuckRestant = lpt_buffer->nbBuckRestant;

	      lp_adr = lprevAddress;
	      _chainMap.erase(_chainMap.find(lp_adr));

	      free(lpt_buffer->ar);
	      delete lpt_buffer;

	      lp_adr = lnextAddress;
	      _chainMap.insert(ChainMapType::value_type(lp_adr, lpt_buffer1));
	      return 1;
	    }
	}
      else
	{
	  /* prime record */
	  lpt_buffer = new t_buffer;
	  lpt_buffer->cnt = 1;
	  lpt_buffer->ar = (char*)malloc(IND_LEN);
	  memcpy(&lIrLegs, &buffer[POS_NB_LEG - ID_LEN], 2);
	  memcpy(&lIrBcs, &buffer[POS_NB_BCS - ID_LEN], 2);
	  memcpy(&lIrBucs, &buffer[POS_NB_BU_TR - ID_LEN], 2);
	  if (gnHeaderLen + gnLegHeaderLen * lIrLegs + TER_LEN + lIrLegs * lIrBcs * gnLegBcsLen > IND_LEN)
	    {
	      lReste = (IND_LEN - gnHeaderLen - gnLegHeaderLen * lIrLegs - TER_LEN) % gnLegBcsLen;
	      lpt_buffer->nbBcsRestant = (lIrLegs * lIrBcs) - ((IND_LEN - gnHeaderLen - gnLegHeaderLen *
								lIrLegs - TER_LEN) / gnLegBcsLen);

	      lpt_buffer->nbBuckRestant = lIrBucs*lIrLegs;

	      if (!lReste)
		{
		  lReste = gnLegBcsLen;
		  lpt_buffer->nbBcsRestant++;
		}
	    }
	  else
	    {
	      lReste = (IND_LEN - gnHeaderLen - gnLegHeaderLen * lIrLegs - TER_LEN - lIrBcs *
			lIrLegs * gnLegBcsLen) % gnLegBucketLen;

	      lpt_buffer->nbBcsRestant = 0;
	      lpt_buffer->nbBuckRestant = (lIrLegs * lIrBucs) - ((IND_LEN - gnHeaderLen - gnLegHeaderLen *
								  lIrLegs - TER_LEN - lIrBcs * lIrLegs *
								  gnLegBcsLen) / gnLegBucketLen);

	      if (!lReste)
		{
		  lReste = gnLegBucketLen;
		  lpt_buffer->nbBuckRestant++;
		}
	    }

	  lpt_buffer->lPrimaryBuffer = IND_LEN - ID_LEN - lReste;
	  memcpy(lpt_buffer->ar, buffer, lpt_buffer->lPrimaryBuffer);
	  lp_adr = lnextAddress;
	  _chainMap.insert(ChainMapType::value_type(lp_adr, lpt_buffer));

	  return 1;
	}
    }
}

//SMD
// Name : CleanChainMap
// Desc : En fait juste le clear de _chainMap est utile
//EMD
void YmIrIndLoader::CleanChainMap()
{
  ChainMapType::iterator iPos = _chainMap.begin();
  ChainMapType::iterator iFin = _chainMap.end();
  int kk = 0;

  t_buffer *pbuffer;
  while (iPos != iFin)
    {
      pbuffer = iPos->second;
      free(pbuffer->ar);
      delete pbuffer;
      iPos++;
      kk++;
    }

  _chainMap.clear();
}
