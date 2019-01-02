//## Module: YmIrDataValidator
//SFD
//  Name   : YmTranche.cpp
//  Author : M. Hue
//  Desc   : Contains class implementation for YmIrDataValidator class.
//	     This class is used to validate IND data.
//	     It keeps a count of invalid records and the reasons for their
//	     being invalid.
//EFD

using namespace std;

//## Includes
#include <string>
#include "YmIrGlobal.h"
#include "YmMapStations.h"
#include "YmMapCompartments.h"
#include "YmMessLog.h"
#include "YmDate.h"
#include "YmIrDataValidator.h"
#include "YmMapDatesIrATraiter.h"

//## Initialize the static instance
YmIrDataValidator *YmIrDataValidator::_instance = 0;

//SMD
// Name : Instance
// Desc : Instantiation of the validation class for IND
//EMD
YmIrDataValidator *YmIrDataValidator::Instance()
{
  if (_instance == 0)
    _instance = new YmIrDataValidator();

  return _instance;
}

//SMD
// Name : Validate
// Desc : Checks for all the fields and returns the first
//EMD
bool YmIrDataValidator::Validate(YmIrIndOutputRec &ind_) const
{
  if (ValidateIndStnOrig(ind_) == false)
    return false;

  if (ValidateIndStnDest(ind_) == false)
    return false;

  if (ValidateLdtime(ind_) == false)
    return false;

  if (ValidateLatime(ind_) == false)
    return false;

  return true;
}

//SMD
// Name : ValidateIndStnOrig
// Desc : Validates the origin station code against the DB values
//EMD
bool YmIrDataValidator::ValidateIndStnOrig(YmIrIndOutputRec &ind_) const
{
  string lstn(ind_.get_legOrig());
  if (g_MapStations.isInMap(lstn))
    return true;
  else
    {
      YmMessLog lmess(__FILE__, "ValidateIndStnOrig", PROCESS_NAME);
      string ltext("mauvaise station origine de troncon ");
      ltext += lstn;
      ltext += " pour la tranche";
      char szTranche[7];
      sprintf(szTranche, "%06d", ind_.get_trancheNo());
      ltext += szTranche;
      ltext += " du ";
      char szDate[11];
      YmDate dtD = ind_.get_dptDate();
      ltext += dtD.PrintFrench(szDate);
      lmess.envoiMess(__LINE__, ltext, YmMessLog::WARN);

      return false;
    }
}

//SMD
// Name : ValidateIndStnDest
// Desc : Validates the destination station code against the DB values
//EMD
bool YmIrDataValidator::ValidateIndStnDest(YmIrIndOutputRec &ind_) const
{
  string lstn(ind_.get_legDest());
  if (g_MapStations.isInMap(lstn))
    return true;
  else
    {
      YmMessLog lmess(__FILE__, "ValidateIndStnDest", PROCESS_NAME);
      string ltext("mauvaise station destination de troncon ");
      ltext += lstn;
      ltext += " pour la tranche";
      char szTranche[7];
      sprintf(szTranche, "%06d", ind_.get_trancheNo());
      ltext += szTranche;
      ltext += " du ";
      char szDate[11];
      YmDate dtD = ind_.get_dptDate();
      ltext += dtD.PrintFrench(szDate);
      lmess.envoiMess(__LINE__, ltext, YmMessLog::WARN);

      return false;
    }
}

//SMD
// Name : ValidateLdtime
// Desc : Validates the leg depart time
//EMD
bool YmIrDataValidator::ValidateLdtime(YmIrIndOutputRec &ind_) const
{
  YmDate dateT(ind_.get_dptDate());
  YmDate dateTLeg(ind_.get_dptLegDate());
  dateT += 1;

  if ((dateTLeg > dateT) || ((dateTLeg == dateT) && ind_.get_legDptTime() > 1200))
    {
      YmMessLog lmess(__FILE__, "ValidateLdtime", PROCESS_NAME);
      string ltext("mauvaise heure de depart");
      ltext += " pour la tranche";
      char szTranche[7];
      sprintf(szTranche, "%06d", ind_.get_trancheNo());
      ltext += szTranche;
      ltext += " du ";
      char szDate[11];
      YmDate dtD = ind_.get_dptDate();
      ltext += dtD.PrintFrench(szDate);
      lmess.envoiMess(__LINE__, ltext, YmMessLog::WARN);

      return false;
    }

  return true;
}

//SMD
// Name : ValidateLatime
// Desc : Validates the leg arrival time
//EMD
bool YmIrDataValidator::ValidateLatime(YmIrIndOutputRec &ind_) const
{
  YmDate dateLegA(ind_.get_arvLegDate());
  YmDate dateLegD(ind_.get_dptLegDate());

  if (dateLegD > dateLegA)
    {
      YmMessLog lmess(__FILE__, "ValidateLdtime", PROCESS_NAME);
      string ltext("mauvaise heure d'arrivee");
      ltext += " pour la tranche";
      char szTranche[7];
      sprintf(szTranche, "%06d", ind_.get_trancheNo());
      ltext += szTranche;
      ltext += " du ";
      char szDate[11];
      YmDate dtD = ind_.get_dptDate();
      ltext += dtD.PrintFrench(szDate);
      lmess.envoiMess(__LINE__, ltext, YmMessLog::WARN);

      return false;
    }

  if ((dateLegD < dateLegA) && (ind_.get_legArvTime() > ind_.get_legDptTime()))
    {
      YmMessLog lmess(__FILE__, "ValidateLdtime", PROCESS_NAME);
      string ltext("mauvaise heure d'arrivee");
      ltext += " pour la tranche";
      char szTranche[7];
      sprintf(szTranche, "%06d", ind_.get_trancheNo());
      ltext += szTranche;
      ltext += " du ";
      char szDate[11];
      YmDate dtD = ind_.get_dptDate();
      ltext += dtD.PrintFrench(szDate);
      lmess.envoiMess(__LINE__, ltext, YmMessLog::WARN);

      return false;
    }

  if ((dateLegD == dateLegA) && (ind_.get_legArvTime()<= ind_.get_legDptTime()))
    {
      YmMessLog lmess(__FILE__, "ValidateLdtime", PROCESS_NAME);
      string ltext("mauvaise heure d'arrivee");
      ltext += " pour la tranche";
      char szTranche[7];
      sprintf(szTranche, "%06d", ind_.get_trancheNo());
      ltext += szTranche;
      ltext += " du ";
      char szDate[11];
      YmDate dtD = ind_.get_dptDate();
      ltext += dtD.PrintFrench(szDate);
      lmess.envoiMess(__LINE__, ltext, YmMessLog::WARN);

      return false;
    }

  return true;
}

//SMD
// Name : ValidateCmpt
// Desc : Validates the compartment code value.
//EMD
bool YmIrDataValidator::ValidateCmpt(char cmptV) const
{
  int i;
  char szCmpt[2];
  szCmpt[1] = '\0';
  szCmpt[0] = cmptV;

  if (g_MapCompartments.isInMap(string(szCmpt)))
    return true;

  return false ;
}

