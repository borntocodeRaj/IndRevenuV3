//## Module : YmDatesIrATraiter
//SFD
//  Name    : YmDatesIrATraiter.h
//  Author  : plf
//  Desc    : Description de la classe qui mappe la table des DatesIrATraiter 
//EFD

#ifndef YmDatesIrATraiter_h
#define YmDatesIrATraiter_h 1

//## Includes
#include <string>
#include "YmDate.h"

class YmDatesIrATraiter
{
 public:
  //## Constructeurs
  YmDatesIrATraiter(YmDate DateATraiter, unsigned char Busy);
  YmDatesIrATraiter(int ATraiter, unsigned char Busy);

  //## Destructeur
  ~YmDatesIrATraiter() {;}

  //## Accesseurs
  YmDate	get_DateATraiter() { return _DateATraiter; }
  unsigned char get_Busy() { return _Busy; }

  //## Mutateurs
  void set_Busy(unsigned char Busy) { _Busy = Busy; };

 private:
  //## Donnees
  YmDate	_DateATraiter;
  /* 0x00 = date A Traiter,
   * 0x01 = date en cours de traitement par un process
   * 0x02 = date deja traitee par un process*/
  unsigned char _Busy;
};

#endif

