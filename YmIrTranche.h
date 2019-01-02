//## Module : YmIrTranche
//SFD
//  Name    : YmIrTranche.h
//  Author  : Jean-Philippe Martel 
//  Desc    : Classe qui contient les informations au niveau Tranche
//EFD

#ifndef IRTRANCHE_H
#define IRTRANCHE_H 1

//## Includes
#include <string.h>
#include <list>
#include <map>
#include "YmDate.h"
#include "YmIrTrain.h"

typedef map<string,unsigned short,less<string> > StartMapType;

class YmIrTranche
{
 public:
  //## Constructeurs
  YmIrTranche() {;}
  YmIrTranche(int num_, YmDate date_) :
    _num(num_),
    _date(date_),
    _goodDate(0)
    { ; }

  //## Destructeur
  ~YmIrTranche() { ; }

  //## Accesseurs
 inline int Num() { return _num; } 
 inline YmDate Date() { return _date; }
 inline YmDate& RrdDate() { return _rrdDate; }
 inline short GoodDate() { return _goodDate; }
 inline list<YmIrTrain *> &TrainList() { return _trainList; }
 inline map<string,unsigned short,std::less<string> >& StartMap() { return _startMap; }

  //## Mutateurs
 inline void Num(int value){ _num = value; }
 inline void Date(const YmDate &value) { _date = value; }
 inline void RrdDate(const YmDate &value) { _rrdDate = value; }
 inline void GoodDate(short value) { _goodDate = value; }

  //## Autres
 inline void CleanStations() { _startMap.clear(); }
 inline void AddStart(string code_, unsigned short legSeq_) { _startMap.insert(StartMapType::value_type(code_, legSeq_)); }
  /* la methode retourne  
   * -1 si la gare n'est pas desservie
   * le legSeq-1, si elle est desservie (eg 0 pour le premier leg) */
 inline short FindStation(string code_) 
    {
      map<string,unsigned short,std::less<string> >::iterator iPos;
      iPos = _startMap.find(code_);
      return (iPos == _startMap.end() ? -1 : iPos->second);
    }

  //## Operateurs
  unsigned int operator()(const YmIrTranche &tranche) const { return (unsigned int) tranche._num; }
  bool operator()(const YmIrTranche &t1,const YmIrTranche &t2) const
    {
      return (t1._num == t2._num) && ((YmDate)t1._date == (YmDate)t2._date);
    }

 private:
  //## Donnees
  /* Numero de tranche */
  int		    _num;
  /* Date de depart de la tranche */
  YmDate	    _date;
  /* Liste des trains */
  list<YmIrTrain *> _trainList;
  /* Date du RRD pour laquelle la tranche est selectionnee (une tranche/date ne peut etre que sur un RRD) */ 
  YmDate	    _rrdDate;
  /* Map qui contient toutes les gares desquelles la tranche repart durant son trajet */
  StartMapType	    _startMap;
  /* TRUE si la tranche est portee par un train qui part a la date d'un RRD */
  short		    _goodDate;
};

#endif
