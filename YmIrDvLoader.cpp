// SFD
//Name: YmNbDvLoader.cpp
//Author: M. Hue
//Desc:  Load the IND from the resarail file and put it into a Map of
//Sorted List for each reading days
// This process uses the multithreading
// EFD

// Standard C and C++ include files

using namespace std;

#include <iostream>
#include <stdlib.h>
#include <stdio.h>

#include <string.h>
#include "YmDate.h"

// Application Include Files
#include "YmIrGlobal.h"
#include "YmIrTranche.h"
#include "YmIrTrain.h"
#include "YmIrDvLoader.h"
#include "YmIrSysParms.h"
#include "YmMessLog.h"
#include "YmMapDatesIrATraiter.h"


// SMD
//Name: YmNbDvLoader
//Signature:YmNbDvLoader( YmDate infoBatchDate)
// Desc:Constructor for the Loader
// creates a Loader and initiates it with the parameters of the scheduler
// EMD
YmIrDvLoader::YmIrDvLoader( YmDate infoBatchDate)
{
  _lastInfoBatchDate = infoBatchDate ;

}

//SMD
//Name:~YmNbDvLoader
//signature: YmNbDvLoader::~YmNbDvLoader()
//desc:
//EMD
YmIrDvLoader::~YmIrDvLoader()
{
	// On supprime les instances de tranches
	_selectedTrancheMap.clear();
	// On supprime les instances de trains
	_trainList.clear();
}


void YmIrDvLoader::verifDateHeure( YmDate *date_, char *heure_, int u_heure, string *lTime, string lFil)
//verification de la date et de l'heure versus le PNI_IND_TIME
{
// Time as written in PNI_IND_TIME converted in HHMMSS value
int iComp2 = 0;
char lTravH[3];
char lTravM[3];
memcpy(lTravH,lTime->data(),2);
lTravH[2]='\0';
iComp2=atoi(lTravH)*10000;
memcpy(lTravM,&(lTime->data())[2],2);
lTravM[2]='\0';
iComp2+=atoi(lTravM)*100;

// On affiche les informations sur le fichier
char temptime[3];
temptime[2] = '\0';
string ltextDV = "le fichier DV ";
ltextDV += lFil;
ltextDV += " contient les donnees du ";
char szDate[11];
ltextDV += date_->PrintFrench(szDate);
ltextDV+=" a ";
temptime[0] = heure_[0];
temptime[1] = heure_[1];
ltextDV += temptime;
ltextDV +=":";
temptime[0] = heure_[2];
temptime[1] = heure_[3];
ltextDV += temptime;
ltextDV += ":";
temptime[0] = heure_[4];
temptime[1] = heure_[5];
ltextDV += temptime;
YmMessLog rMess(__FILE__,"verifDateHeure",PROCESS_NAME);
//LOCK_MUTEX(&g_MutexDebug);
rMess.envoiMess(__LINE__,ltextDV,YmMessLog::INF);
//UNLOCK_MUTEX(&g_MutexDebug);

if (u_heure<iComp2) // C'est le fichier de la veille
{
        (*date_) -= 1;
}
// Test de la validite de la date du fichier
int idiffdays=0;
idiffdays+=(*date_).DaysFrom70();
idiffdays-=_lastInfoBatchDate.DaysFrom70();
if ( idiffdays != 1  )

        {
        string ltext = "Le fichier ";
        string szDt;
        ltext+= lFil;
        ltext+=" est pour le : ";
        ltext += date_->PrintFrench(szDate);
        ltext += " la date InfoBatch est: ";
        ltext += _lastInfoBatchDate.PrintFrench(szDt);
        ltext += " le traitement ne peut avoir lieu - abort\n";
        cerr << ltext << '\n';
	exit (4);
        }

}

//SMD
//Name: verifSignature
//Signature: void YmNbDvLoader::verifSignature(YmDate *date_, char *buffer, string lFil)
//Desc:
//EMD
void YmIrDvLoader::verifSignature(YmDate *date_, char *buffer, string lFil)
{
// Lecture de la signature du fichier
short intueurSignature = strlen(SIGNATURE_DV);
char *signature_ = new char[intueurSignature+1];
strncpy(signature_,&buffer[14],intueurSignature);
signature_[intueurSignature]='\0';

// Test de la signature
if(strcmp(signature_, SIGNATURE_DV))
        {
        cerr <<  "YmIrDvLoader LectureDV : Le fichier " << lFil << " n'est pas un fichier interface DV valable. \n";
        exit (5);
        }

delete signature_;

// Lecture de la date du dernier train dans le fichier
char derniereDateChar_[9];
strncpy(derniereDateChar_,&buffer[14+intueurSignature],8);
derniereDateChar_[8]='\0';
date_=Char2Date(derniereDateChar_);
if (*date_==YmDate(0,0,1))
        {
        cerr <<  "YmInDvLoader lectureDV: Format de la date du dernier train present non valable dans l'en-tete du fichier DV : " << lFil;
        exit(6);
        }

delete date_;
}

//SMD
//Name: LectureDV
//Signature: void YmNbDvLoader::LectureDV(YmMapDatesNbATraiter *MapDatesATraiter)
//Desc:
//EMD
void YmIrDvLoader::LectureDV(YmMapDatesIrATraiter *MapDatesATraiter)
{
const char *lfile=getenv("YMBA_DV_NAME");
const char * lpath=getenv("YMBA_DV_DIR");
string lFil(lpath);
lFil+="/";
lFil+=lfile;
FILE *file_=fopen(lFil.data(),"r");
if (file_==NULL)
        {
        cerr << "YmIrDvLoader LectureDV: Ouverture impossible du fichier " << lFil;
        exit(1);
        }

unsigned short tailleEnregistrement = RECORD_DV_SIZE + RETOUR_LIGNE_DV;

char *buffer=new char[tailleEnregistrement+1];

// Test de l'entete du fichier
fgets(buffer,tailleEnregistrement,file_);

// Lecture de la date de creation du fichier
char dateChar[9];
strncpy(dateChar,buffer,8);
dateChar[8]='\0';
YmDate *date_ = Char2Date(dateChar);
if (*date_==YmDate(0,0,1))
        {
        cerr << "YmIrDvLoader lectureDV: Format de la date de creation non valable dans le fichier DV : " << lFil;
        exit(2);
        }

// Lecture de l'heure de creation du fichier
char heure_[7];
strncpy(heure_,&buffer[8],6);
heure_[6]='\0';
int u_heure=atoi(heure_);

// Lecture du parametre PNI_IND_TIME
YmIrSysParms laparm;
string lTime(laparm.getChar((char *)"PNI_IND_TIME",(char *)""));
if (lTime==string(""))
  {
  cerr << "YmIrDvLoader lectureDV: PNI_IND_TIME system parameter not found - abort\n";
  exit(3);
  }

verifDateHeure( date_, heure_, u_heure, &lTime, lFil);

// date_ a ete instancie par Char2Date(...)
delete date_;

verifSignature(date_, buffer, lFil);

lectureFichierDV(buffer, tailleEnregistrement, dateChar, lFil, file_, MapDatesATraiter);

delete []buffer;
fclose(file_);
}

void YmIrDvLoader::lectureFichierDV(char *buffer, unsigned short tailleEnregistrement,
                                       char *dateChar, string lFil, FILE *file_, YmMapDatesIrATraiter *MapDatesATraiter)
// On construit ici une nouvelle map qui va contenir les dates des trains que l'on doit selectionner
// On ne prend pas la date des RRD car elles ne sont pas suffisantes
// Il nous faut pour chaque tranche/date a traiter tous les trains qui la portent or ils ne partent pas
// necessairement le jour du RRD
// On va donc prendre la date des D des RRD plus les dates D-1 et D+1 pour chacun d'eux
// Par la suite on supprimera les tranche/date qui ne sont portees que par des trains ne partant qu'a
// des dates qui ne sont pas des RRDs
{
YmMapDatesIrATraiter _datesEtenduesMap;
MapDatesIrATraiterType::iterator iPosE; //iterateur sur map etendue
MapDatesIrATraiterType::iterator iPosR; //iterateur sur map reading days
MapDatesIrATraiterType::iterator iPos = g_MapDatesIrATraiter.getMapDatesATraiter()->begin();
MapDatesIrATraiterType::iterator iFin =g_MapDatesIrATraiter.getMapDatesATraiter()->end();

YmDatesIrATraiter *dateAT;
YmDate date;

// construction d'une liste de date a traiter en ajoutant la veille et le lendemain.
while (iPos!=iFin)
{
    dateAT = iPos->second;
    _datesEtenduesMap.AddNoBase(dateAT);
    date = dateAT->get_DateATraiter();
    date += 1;
    dateAT = new YmDatesIrATraiter(date,0x00); //0x00 la date est a traiter
    _datesEtenduesMap.AddNoBase(dateAT);
    date = dateAT->get_DateATraiter();
    date -= 2;
    dateAT = new YmDatesIrATraiter(date, 0x00); //0x00 la date est a traiter
    _datesEtenduesMap.AddNoBase(dateAT);
    iPos++;
}


unsigned short cptTranches_ = 0;
unsigned short cptTrains_ = 0;

unsigned short nbTranchesMax = (RECORD_DV_SIZE-(26)) / 25;

// On stocke toutes les tranches dans cette map : une selection sur cette map est faite
// a la fin de la lecture du fichier
mapTranchesType tempTrancheMap;
mapTranchesType::iterator iPosTranche;

// variables utilisees pour le train
char numTrain_[7];
string s_numTrain;
char nbTranches_[3];
short u_nbTranches;
char origTrain_[6];
YmIrTrain *train_;
// variables utilisees pour la tranche
char dateTranche_[9];
char numTranche_[7];
int u_numTranche;
string defTranche_;
YmIrTranche *trancheTmp_;

while(!feof(file_))
        {
        if(fgets(buffer,tailleEnregistrement,file_))
                {
                strncpy(dateChar,&buffer[6],8);
                dateChar[8]='\0';
                // test sur la date du train
		if ((iPosE=_datesEtenduesMap.getMapDatesATraiter()->find(dateChar))!=_datesEtenduesMap.getMapDatesATraiter()->end())
                        {
                        strncpy(numTrain_,buffer,6);
                        numTrain_[6]='\0';
                        s_numTrain = numTrain_;

                        YmDate *dateTr = new YmDate;
                        *dateTr=iPosE->second->get_DateATraiter();
                        train_ = new YmIrTrain(s_numTrain,dateTr);
			_trainList.insert(_trainList.end(),train_);
                        strncpy(nbTranches_,&buffer[24],2);
                        nbTranches_[2]='\0';
                        u_nbTranches = atoi(nbTranches_);

			// Initialisation de l'origine du train
                        strncpy(origTrain_,&buffer[14],5);
                        origTrain_[5]='\0';
			train_->Orig(origTrain_);

                        // Test sur la coherence du nombre de tranches
                        if (u_nbTranches > nbTranchesMax)
                                {
				YmMessLog rMess(__FILE__,"lectureFichierDV",PROCESS_NAME);
				string ltext = string("Le nombre de tranches pour le train/date ") + numTrain_ + "/"
							 + dateChar + " est trop elevee (" + nbTranches_ + ") : l'enregistrement est rejete.";
				//LOCK_MUTEX(&g_MutexDebug);
                                rMess.envoiMess(__LINE__,ltext,YmMessLog::WARN);
				//UNLOCK_MUTEX(&g_MutexDebug);
                                continue;
                                }

                        // Boucle sur les tranches
                        for(short cpt=0;cpt<u_nbTranches;cpt++)
                                {
                                short decalage=(26) + cpt * 25;

                                strncpy(numTranche_,&buffer[decalage],6);
                                strncpy(dateTranche_,&buffer[decalage+6],8);
                                numTranche_[6]='\0';
                                u_numTranche=atoi(numTranche_);
                                dateTranche_[8]='\0';
                                defTranche_=string(dateTranche_) + numTranche_;

                                // Test sur la presence de la tranche
		                if ((iPosTranche=tempTrancheMap.find(defTranche_))==tempTrancheMap.end())
                                        {
                                        trancheTmp_ = new YmIrTranche;
                                        trancheTmp_->Date(YmDate(string(dateTranche_)));
                                        trancheTmp_->Num(u_numTranche);
                                        trancheTmp_->TrainList().push_back(train_);
                                        tempTrancheMap[defTranche_]=trancheTmp_;
		                        if ((iPosR=MapDatesATraiter->getMapDatesATraiter()->find(dateChar))!=MapDatesATraiter->getMapDatesATraiter()->end())
						{
						// la tranche est portee par un train qui part
						// a une date de NB
						trancheTmp_->GoodDate(1);
						}
                                        }
                                else
                                        {
                                        trancheTmp_=iPosTranche->second;
                                        trancheTmp_->TrainList().push_back(train_);
					if (!trancheTmp_->GoodDate())
						{
		                                if ((iPosR=MapDatesATraiter->getMapDatesATraiter()->find(dateChar))!=MapDatesATraiter->getMapDatesATraiter()->end())
							{
							// la tranche est portee par un train qui part
							// a une date de NB
							trancheTmp_->GoodDate(1);
							}
						}
                                        }

                                }

                        }
                }
        else // probleme dans le fichier ou fin du fichier
                {
			unsigned int pos = ftell(file_);
//DM5496 non change
			if (pos%RECORD_DV_SIZE == 0) break; // fin du fichier
//DM5496
			YmMessLog rMess(__FILE__,"lectureFichierDV",PROCESS_NAME);
			string ltext = string("Probleme dans la lecture du fichier de l'interface DV : ") + lFil + ", fichier incomplet";
			//LOCK_MUTEX(&g_MutexDebug);
            rMess.envoiMess(__LINE__,ltext,YmMessLog::ERROR);
	                //UNLOCK_MUTEX(&g_MutexDebug);
                        fclose(file_);
			exit (7);
                }
        }


// On va eliminer ici de la collection de tranches, celles qui ne sont portees que par des trains
// partant a des dates qui ne sont pas des RRDs
mapTranchesType::iterator iPosTrancheFin = tempTrancheMap.end();
mapTranchesType::iterator iPosTrancheC = tempTrancheMap.begin();
while (iPosTrancheC!=iPosTrancheFin)
{
	if (iPosTrancheC->second->GoodDate())
	{
		_selectedTrancheMap[iPosTrancheC->first]=iPosTrancheC->second;
	}
	else
	{
		iPosTrancheC->second->TrainList().clear();
		delete iPosTrancheC->second;
	}
        iPosTrancheC++;
}


// On detruit la map etendue
(_datesEtenduesMap.getMapDatesATraiter())->clear();

}

//SMD
//Name:Char2Date
//signature:YmDate *Char2Date(char *)
//desc:transforme un char* au format YYYYMMDD en un YmDate
//EMD
YmDate *YmIrDvLoader::Char2Date(const char *charDate_)
{
string szDate(charDate_);

YmDate *date_=new YmDate(szDate);

return date_;
}


// On determine ici pour quelle date la tranche doit etre selectionnee
// En effet une tranche date peut etre portee par des trains partant a des dates
// differentes
short YmIrDvLoader::DetermineTrancheRrd(YmIrTranche* pTranche_)
{

        // Pour savoir si une tranche doit etre affectee a un train/date, on regarde
        // si la tranche est partie en meme temps ou apres le train
        // Pour cela on regarde si l'origine du train est dans la desserte de la tranche :
        // - si c'est aussi l'origine de la tranche on garde ce train/date
        // - si c'est une autre gare de la desserte on rejete ce train/date
        // - si l'origine du train n'est pas desservie par la tranche, le train/date est
        //   parti avant la tranche et on le garde
        // ON SUPPOSE ICI QU'UN TRAIN NE PASSE QU'UNE SEULE FOIS PAR UNE GARE DONNEE
        // Le train/date selectionne pour la tranche nous donne la date de RRD a laquelle
        // la tranche doit etre affectee

	short res;

	list<YmIrTrain *>::iterator itTrain=(pTranche_->TrainList()).begin();
	list<YmIrTrain *>::iterator itTrainFin=(pTranche_->TrainList()).end();
	list<YmIrTrain *> selectedTrains;

	while (itTrain!=itTrainFin)
	{
		string trainOrig = (*itTrain)->Orig();
		// si le retour est > 0, on rejette le train/date : la methode retourne
		// -1 si la gare n'est pas desservie et 0 si c'est le depart
		short legSeq;
		if ((legSeq=pTranche_->FindStation(trainOrig))<=0)
		{
			if (legSeq==0)
			{
				// La tranche et le train ont la meme origine
				selectedTrains.clear();
				selectedTrains.push_back(*itTrain);
				break;
			}
			else
			{
				// le train est parti avant la tranche
				selectedTrains.push_back(*itTrain);
			}
		}
        itTrain++;
	}

	if (selectedTrains.size() == 1)
	{
		// On a trouve un train/date
	        itTrain=(pTranche_->TrainList()).begin();
		pTranche_->RrdDate((*itTrain)->Date());
		res = 1; //true;
	}
	else if (selectedTrains.size() == 0)
	{
		// Aucun train/date n'a ete trouve : la tranche doit etre
		// traitee pour une date qui ne correspond a aucun RRD
	  res = 0; //false;
	}
	else
	{
	        res = 1; //true;
		YmDate *pDate = NULL;
		string ltext = "La tranche ";
		char num[100];
		sprintf(num,"%d",pTranche_->Num());
		ltext += num;
                string szDt;
                (pTranche_->Date()).PrintFrench(szDt);
		ltext += " du ";
                ltext+=szDt;
                ltext+=" est assignee a plusieurs trains :\n";
		StartMapType::iterator iPos=(pTranche_->StartMap()).begin();
		StartMapType::iterator iFin=(pTranche_->StartMap()).end();
		while (iPos!=iFin)
		{
			sprintf(num,"%s:%d/",(iPos->first).data(),iPos->second);
			ltext += num;
                        iPos++;
		}
		list<YmIrTrain *>::iterator itSel=selectedTrains.begin();
		list<YmIrTrain *>::iterator itSelFin=selectedTrains.end();
		while (itSel!=itSelFin)
		{
			ltext += "\n - le ";
			ltext += (*itSel)->Num();
                        ltext += " du  ";
                        string szDt;
                        ((*itSel)->Date()).PrintFrench(szDt);
			ltext += szDt;
			ltext += "  : ORIG = ";
			ltext += (*itSel)->Orig();
			if (!pDate)
			{
				pDate = new YmDate((*itSel)->Date());
			}
			else if (*pDate != (*itSel)->Date())
			{
				res = 0;
			}
                itSel++;
		}
		if (res)
		{
			ltext += "\nLa tranche est acceptee";
			pTranche_->RrdDate((*(selectedTrains.begin()))->Date());
		}
		else
		{
			ltext += "\nLa tranche est rejetee";
		}
		YmMessLog rMess(__FILE__,"DetermineTrancheRrd",PROCESS_NAME);
		//LOCK_MUTEX(&g_MutexDebug);
        rMess.envoiMess(__LINE__,ltext,YmMessLog::WARN);
	        //UNLOCK_MUTEX(&g_MutexDebug);
		if (pDate)
			delete pDate;
	}

	selectedTrains.clear();

	// On supprime la desserte de la tranche car on n'en a plus besoin
	pTranche_->CleanStations();
	// On nettoie la liste de trains
	pTranche_->TrainList().clear();

	return res;
}

