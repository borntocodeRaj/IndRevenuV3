//## Module: YmDate
//SFD
// Name:   YmDate.h
// Author: JM. Grugeaux
// Desc:   Realisation d'une classe CDate adapte a nos besoins
//EDF

#ifndef YmDate_h
#define YmDate_h 1

#include <ctime>
#include <string>
#include <iostream>

extern char* DonneHeure(); // renvoi l'heure sous forme HH:MI:SS

class YmDate
{
  public:
  YmDate();	// Default constructor, initialise avec la date du jour
  YmDate(const YmDate& aYmDate); // Copie constructor;
  YmDate(const string& szAAAAMMJJ); // Construit et initialise une date a partir d'une string au format AAAAMMJJ
                              // ou au format JJ/MM/AAAA. la diferentition se fait sur la intueur de la string
  YmDate(int annee, int mois, int jour); // Construit et initialise une date a partir anne mois jour
  ~YmDate() {;}

  string& PrintFrench(string& scible, bool fullyear = true) const; // renvoi scible, format JJ/MM/AAAA si fullyear = true,
					     		     //  au format JJ/MM/AA sinon
  string& PrintUS(string& scible, bool fullyear = true) const;     // renvoi scible, format MM/DD/YYYY si fullyear = true,
				             		     //	au format MM/DD/YY sinon
  string& PrintOracle(string& scible, bool fullyear = true) const; // renvoi scible, format YYYY/MM/DD si fullyear = true,
				             		     //	au format YY/MM/DD sinon
  string& PrintResaven (string& cible, bool fullyear = true) const; //renvoi scible, format YYYYMMDD si fullyear = true,
                                                             // au format YYMMDD sinon
  char* PrintFrench(char* sbuf, bool fullyear = true) const;	     // idem mais avec un char*
  char* PrintUS(char* sbuf, bool fullyear = true) const;	     // idem mais avec un char*
  char* PrintOracle(char* sbuf, bool fullyear = true) const;	     // idem mais avec un char*
  char* PrintResaven(char* sbuf, bool fullyear = true) const;	     // idem mais avec un char*

  int WeekDay(bool bMondayFirst = true) const; // renvoi le jour de semaine entre 1 et 7
					 // Lundi = 1 si bMondayFirst vrai, Dimanche = 1 sinon
  int YearDay() const;	// renvoi le nombre de jour depuis le debut de l'annee
  int DaysFrom70() const;    // renvoi le nombre de jour depuis le 01/01/1970
  int year() const;		// renvoi l'annee
  int month() const;		// renvoi le mois
  int day() const;		// renvoi le jour du mois
  YmDate& operator=(const YmDate& aYmDate);
  bool operator==(const YmDate& aYmDate) const;
  bool operator!=(const YmDate& aYmDate) const;
  bool operator>=(const YmDate& aYmDate) const;
  bool operator<=(const YmDate& aYmDate) const;
  bool operator>(const YmDate& aYmDate) const;
  bool operator<(const YmDate& aYmDate) const;
  YmDate& operator+=(int nbjour);
  YmDate& operator-=(int nbjour);
  YmDate& operator++();
  YmDate& operator--();

  private:
  char* AllPrint (char* sbuf, int typrint, bool fullyear) const;
  time_t _nbseconds;
  struct tm _datetime;
};


/**
 * Comparateur de date-heure (pour palier à l'absence de ce type
 * dans collecte). Evite les manipulations fastidieuses de YmDate et int.
 *
 * Les "heures" sont des entiers représentant le nombre de minutes depuis minuit,
 * comme partout dans collecte.
 *
 * Retour classique pour un comparateur:
 *   - retour  > 0 ssi (day1, time1)  > (day2, time2)
 *   - retour == 0 ssi (day1, time1) == (day2, time2)
 *   - retour  < 0 ssi (day1, time1)  < (day2, time2)
 */
int compareDatetimes(const YmDate& day1, int time1, const YmDate& day2, int time2);


namespace std
{
    ostream& operator<<(ostream& os, const YmDate& date);
}

#endif
