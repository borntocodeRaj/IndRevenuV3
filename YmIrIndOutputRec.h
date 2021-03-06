//## Module : YmIrIndOutputRec.h
//SFD
//  Name    : YmIrIndOutputRec.h
//  Author  : Lienard william
//  Desc    : Contains YmIrIndOutputRec Class Descriptions
//EFD

#ifndef YmIrIndOutputRec_h
#define YmIrIndOutputRec_h 1

//## Includes
#include <string>
#include "YmIrInputIndRec.h"
#include "YmMapStations.h"
#include "YmDate.h"

class YmIrIndOutputRec
{
 public:
  //## Constructeurs
  YmIrIndOutputRec();
  YmIrIndOutputRec(int trancheNo, YmDate dptDate);
  
  YmIrIndOutputRec(int trancheNo,
		   YmDate    dptDate,
		   int       natureTranche, 
		   int       crossesMidnight,
		   int       supplementLevel,
		   int       trainNo,
		   int       legNo,
		   string    legOrig,
		   string    legDest,
		   int       legDptTime,
		   int       legArvTime,
		   int       legDistanceKm,
		   int       cmptNo,
		   string    cmpt,
		   int       physicalCapacity,
		   int       cmptResHold,
		   int       blockedCapacity,
		   int       tgvJumeauxPct,
		   int 	     bucketNo,
		   int       nestLevel,
		   int       authorizedCapacity,
		   int       bktResHold,
		   YmDate    dptDateTr,
		   YmDate    rrdDate,
		   int       isYieldManaged,
		   string    codeEquip,
		   string    typeAlgo,
		   int	     top,
		   int       oshibori,
		   int       disney,
		   int       familles
		   );

  YmIrIndOutputRec(int trancheNo,
		   YmDate    dptDate,
		   int       natureTranche,
		   int       crossesMidnight,
		   int       supplementLevel,
		   int       trainNo,
		   int       legNo,
		   string    legOrig,
		   string    legDest,
		   YmDate    dptLegDate,
		   int       legDptTime,
		   YmDate    arvLegDate,
		   int       legArvTime,
		   int       legDistanceKm,
		   int       cmptNo,
		   string    cmpt,
		   int       physicalCapacity,
		   int       cmptResHold,
		   int       blockedCapacity,
		   int       tgvJumeauxPct,
		   int 	     bucketNo,
		   int       nestLevel,
		   int       authorizedCapacity,
		   int       bktResHold,
		   YmDate    dptDateTr,
		   YmDate    rrd_date,
		   int       isYieldManaged,
		   string    codeEquip,
		   string    typeAlgo,
		   int      
		   short     authScg,
		   short     resHoldScg,
		   short     *authScx,
		   short     *resHoldScx,
		   char      *etancheiteScx,
		   short     nbScx,
		   int       top,
		   int       oshibori,
		   int       disney,
		   int       familles
		   );
  YmIrIndOutputRec(YmIrInputIndRec, int, int, int, YmMapStations *);
  YmIrIndOutputRec(const YmIrIndOutputRec &right);

  //## Destructeur
  virtual ~YmIrIndOutputRec();

  //## Operateur
  const YmIrIndOutputRec &operator=(const YmIrIndOutputRec &right);
  bool operator==(const YmIrIndOutputRec &right) const;
  bool operator!=(const YmIrIndOutputRec &right) const;
  bool EqualLeg(const YmIrIndOutputRec &right) const;
  bool EqualCmpt(const YmIrIndOutputRec &right) const;

  //## Accesseurs
  const int get_trancheNo() const { return _trancheNo; }
  const YmDate get_dptDate() const { return _dptDate; }
  const YmDate get_dptDateTr() const { return _dptDateTr; }
  const int get_natureTranche() const { return _natureTranche; }
  const int get_crossesMidnight() const { return _crossesMidnight; }
  const int get_isYieldManaged() const { return _isYieldManaged; }
  const int get_supplementLevel() const { return _supplementLevel; }
  const int get_top() const { return _top; }
  const int get_oshibori() const { return _oshibori; }
  const int get_disney() const { return _disney; }
  const int get_familles() const { return _familles; }
  const int get_trainNo() const { return _trainNo; } 
  const int get_legNo() const { return _legNo;}
  const string & get_legOrig() const { return _legOrig; }
  const string & get_legDest() const { return _legDest; }
  const YmDate get_dptLegDate() const { return _dptLegDate; }
  const int get_legDptTime() const { return _legDptTime; }
  const YmDate get_arvLegDate() const { return _arvLegDate; }
  const int get_legArvTime() const { return _legArvTime; }
  const int get_legDistanceKm() const  { return _legDistanceKm; }
  const int get_cmptNo() const  { return _cmptNo; }
  const string & get_cmpt() const  { return _cmpt; }
  const int get_physicalCapacity() const { return _physicalCapacity; }
  const int get_cmptResHold() const { return _cmptResHold; }
  const int get_blockedCapacity() const { return _blockedCapacity; }
  const int get_tgvJumeauxPct() const { return _tgvJumeauxPct; }
  const int get_bucketNo() const { return _bucketNo; }
  const int get_nestLevel() const { return _nestLevel; }
  const int get_authorizedCapacity() const { return _authorizedCapacity; }
  const int get_bktResHoldInd() const { return _bktResHoldInd; }
  const YmDate get_rrdDate() const { return _rrdDate; }
  const short get_authScg() const { return _authScg; }
  const short get_resHoldScg() const { return _resHoldScg; }
  const short *get_authScx(int scx) const { return _authScx; }
  const short *get_resHoldScx(int scx) const { return _resHoldScx; }
  const char  *get_etancheiteScx(int scx) const { return _etancheiteScx; }
  const short *get_authScx() const { return _authScx; }
  const short *get_resHoldScx() const { return _resHoldScx; }
  const char  *get_etancheiteScx() const { return _etancheiteScx; }
  const short get_nbScx() const { return _nbScx; }
  string &get_codeEquip() { return _codeEquip; }
  string &get_typeAlgo() { return _typeAlgo; }

  //## Mutateurs
  void set_authorizedCapacity(const int value) { _authorizedCapacity = value; }
  void set_cmptNo(const int value) { _cmptNo = value; }
  void set_tgvJumeauxPct(const int value) { _tgvJumeauxPct = value; }
  void set_rrdDate(const YmDate value) { _rrdDate = value; }
  void set_dptDate(const YmDate value) { _dptDate = value; }
  void set_dptDateTr(const YmDate value) { _dptDateTr = value; }
  void set_codeEquip( string &value) { _codeEquip = value; }
  void set_typeAlgo(string &value) { _typeAlgo = value; }

 private:
  //## Mutateurs
  void set_trancheNo(const int value) { _trancheNo = value; }
  void set_natureTranche(const int value) { _natureTranche = value; }
  void set_crossesMidnight(const int value) { _crossesMidnight = value; }
  void set_isYieldManaged(const int value) { _isYieldManaged = value; }
  void set_supplementLevel(const int value) { _supplementLevel = value; }
  void set_top(const int value) { _top = value; }
  void set_disney(const int value) { _disney = value; }
  void set_oshibori(const int value) { _oshibori = value; }
  void set_familles(const int value) { _familles = value; }
  void set_trainNo(const int value) { _trainNo = value; }
  void set_legNo(const int value) { _legNo = value; }
  void set_legOrig(const string &value) { _legOrig = value; }
  void set_legDest(const string &value) { _legDest = value; }
  void set_legDptTime(const int value) { _legDptTime = value; }
  void set_legArvTime(const int value) { _legArvTime = value; }
  void set_legDistanceKm(const int value) { _legDistanceKm = value; }
  void set_cmpt(const string &value) { _cmpt = value; }
  void set_physicalCapacity(const int value) { _physicalCapacity = value; }
  void set_cmptResHold(const int value) { _cmptResHold = value; }
  void set_blockedCapacity(const int value) { _blockedCapacity = value; }
  void set_bucketNo(const int value) { _bucketNo = value; }
  void set_nestLevel(const int value) { _nestLevel = value; }
  void set_bktResHoldInd(const int value) { _bktResHoldInd = value; }
  void set_authScg(const short value) { _authScg = value; }
  void set_resHoldScg(const short value) { _resHoldScg = value; }
  void set_authScx(const short authScx, const int scx) { _authScx[scx] = authScx; }
  void set_resHoldScx(const short resHoldScx, const int scx) { _resHoldScx[scx] = resHoldScx; }
  void set_etancheiteScx(const short etancheiteScx, const int scx) { _etancheiteScx[scx] = etancheiteScx; }
  void set_nbScx(const short value) { _nbScx = value; }

  //## Donnees
  /* Numero de tranche */
  int 	 _trancheNo;
  /* Date de depart de la tranche */
  YmDate _dptDate;
  /* Date de depart reel de la tranche */
  YmDate _dptDateTr;
  /* Nature de la tranche */
  int    _natureTranche;
  /* Flag indiquant si la tranche passe minuit */
  int	 _crossesMidnight;
  /* Flag indiquant si la tranche est yield managed */
  int	 _isYieldManaged;
  /* Tgv supplement level de la tranche */
  int	 _supplementLevel;
  /* Top */
  int    _top;
  /* Oshibori */
  int	 _oshibori;
  /* Disney */
  int	 _disney;
  /* Familles */
  int	 _familles;
  /* Numero du train */
  int 	 _trainNo;
  /* Nombre de leg de la tranche */
  int	 _legNo;
  /* Niveau leg */
  /* Code de la station d'origine */
  string _legOrig;
  /* Code de la station de destination */
  string _legDest;
  /* Date de depart du leg */
  YmDate _dptLegDate;
  /* Heure de depart du leg */
  int 	 _legDptTime;
  /* Date d'arrivee du leg */
  YmDate _arvLegDate;
  /* Heure d'arrivee du leg */
  int	 _legArvTime;
  /* Distance, en kilometre, du leg */ 
  int	 _legDistanceKm;
  /* Nombre de compartiment pour le leg */
  int	 _cmptNo;
  /* Niveau Compartiment */
  /* Code du compartiment */
  string _cmpt;
  /* Capacite phisique du compartiment */
  int 	 _physicalCapacity;
  /* Reservation (ID6BS) */
  int 	 _cmptResHold;
  /* Capacity blocked (cannot be sold) */
  int	 _blockedCapacity;
  /* Preferred inventory percentage (ID6PFC) */
  int	 _tgvJumeauxPct;
  /* Nombre de buckets */
  int	 _bucketNo;
  /* Niveau */
  /* Nesting level */
  int	 _nestLevel;
  /* Autorisation de la bucket (ID6AUT) */
  int	 _authorizedCapacity;
  /* Available seats in the bucket (ID6SAV) */
  int	 _bktResHoldInd;
  /* Code equipement */
  string _codeEquip;
  /* Type algorithme */
  string _typeAlgo;
  YmDate _rrdDate;
  /* Autorisation CC-1 */
  short  _authScg;
  /* Reservation CC-1 */
  short  _resHoldScg;
  /* Autorisation SCXs */
  short  _authScx[SCX_MAX];
  /* Reservation SCXs */
  short  _resHoldScx[SCX_MAX];
  /* Etancheite SCXs */
  char 	 _etancheiteScx[SCX_MAX];
  /* Nombre de SCX */
  short  _nbScx;
};


#endif
