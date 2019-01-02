//## Module : YmMapCompartments
//SFD
//  Name    : YmMapCompartments.h
//  Author  : flabyt
//  Desc    : Description de la map des Compartments 
//EFD

#ifndef YmMapCompartments_h
#define YmMapCompartments_h 1

//## Includes
#include <map>
#include <string>
#include <list>
#include "YmCompartments.h"

//## Typedef
typedef map<string, YmCompartments*, less<string> > MapCompartmentsType;

class YmMapCompartments
{
 public:
  //## Constructeur
  YmMapCompartments();

  //## Destructeur
  ~YmMapCompartments();

  //## Accesseurs
  int getNbFindMapCompartments() { return nbFindMapCompartments; }

  //## Autres
  int getSize() { return _MapCompartments.size(); }
  int init();
  YmCompartments *isInMap(string Cmpt);

 private:
  //## Donnees
  MapCompartmentsType _MapCompartments;
  /* Debug, compteur de fois ou on a trouve une compensation */
  int nbFindMapCompartments;
};

#endif
