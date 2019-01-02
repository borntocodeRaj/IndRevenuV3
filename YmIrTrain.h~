//## Module : YmIrTrain
//SFD
//  Name    : YmIrTrain.h
//  Author  : Jean-Philippe Martel 
//  Desc    : Classe qui contient les informations au niveau Train
//EFD

#ifndef YMIRTRAIN_H
#define YMIRTRAIN_H

//## Includes
#include 	<string.h>
#include 	"YmDate.h"

class YmIrTrain
{
 public:
  //## Constructeurs
  YmIrTrain():_pDate(NULL) { ; }	
  YmIrTrain(string &num_, YmDate *date_):
    _num(num_),
    _pDate(date_)
    { ; }

  /* Constructeur par copie */
  YmIrTrain(YmIrTrain &train):
    _num(train._num),
    _pDate(new YmDate(*train._pDate))
    { ; }

  //## Destructeur
  ~YmIrTrain() { if (_pDate) delete _pDate; } 

  //## Accesseurs
  string Num() { return _num; }
  YmDate Date() { return *_pDate; }
  string Orig() { return _orig; }
 
  //## Mutateurs
  void Num(string value){ _num = value; }
  void Orig(string value) { _orig = value; }

  //## Operateur
  inline bool operator == (YmIrTrain &train){ return _num == train._num && *_pDate == *train._pDate; }

 private:
  //## Donnees
  /* Numero de train */
  string _num;
  /* Date de depart du train */
  YmDate *_pDate;
  /* Origine du train */
  string _orig;
};

#endif
