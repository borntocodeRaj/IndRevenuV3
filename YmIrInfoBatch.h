//## Module : YmIrInfoBatch
//SFD
//  Name    : YmIrInfoBatch.h
//  Author  : plf
//  Desc    : Lecture et mise a jour ym_info_batch  pour key_info = KEY_INFO
//EFD


#ifndef YmIrInfoBatch_h
#define YmIrInfoBatch_h 1


#include <string>
#include "YmDate.h"

class YmIrInfoBatch
{
 public:
  //## Constructeurs
  YmIrInfoBatch();

  //## Destructeur
  ~YmIrInfoBatch();

  //## Accesseurs
  YmDate get_assocCompleteDate() {return _assocCompleteDate; }
  YmDate get_assocCurrentDate() {return _assocCurrentDate; }
  string &get_assocStatusBatch() {return _assocStatusBatch; }

  //## Mutateurs
  void set_assocCompleteDate(YmDate assocCompleteDate_) { _assocCompleteDate=assocCompleteDate_; }
  void set_assocCurrentDate(YmDate assocCurrentDate_) { _assocCurrentDate=assocCurrentDate_; }
  void set_assocStatusBatch(string &assocStatusBatch_) {_assocStatusBatch=assocStatusBatch_; }

  //## Autres
  /* recuperation des occurrences de YM_INFO_BATCH concernant l'IndRevenuv3 */
  int  init();
  bool incrementerAssocCompleteDate ();
  bool majAssocCurrentDate(YmDate currentDate);
  bool majAssocStatusBatch(string statusBatch);

 private:
  //## Donnees
  YmDate _assocCompleteDate;
  YmDate _assocCurrentDate;
  string _assocStatusBatch;
};

#endif
