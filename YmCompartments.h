//## Module : YmCompartments
//SFD
//  Name    : YmCompartments.h
//  Author  : flabyt
//  Desc    : Description de la classe qui mappe la table des Compartments 
//EFD

#ifndef YmCompartments_h
#define YmCompartments_h 1

//## Includes
#include <string>

class YmCompartments
{
 public:
  //## Constructeurs
  YmCompartments(string cmpt);

  //## Destructeur
  ~YmCompartments() {;}

  //## Accesseurs
  string& get_cmpt() { return _cmpt; }
  
 private:
  //## Donnees
  string _cmpt;
};

#endif

