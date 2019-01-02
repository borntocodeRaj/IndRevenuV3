
//## Module: YmDate
//SFD
// Name:   YmDate.cpp.
// Author: JM. Grugeaux
// Desc:   Realisation d'une classe CDate adapte a nos besoins
//EDF

using namespace std;

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "YmDate.h"

char* DonneHeure()
{
    static char buf[10];
    time_t tt = time (NULL);
    struct tm Tres;
    struct tm * pTime = localtime_r (&tt, &Tres);
    sprintf (buf, "%2.2u:%2.2u:%2.2u", pTime->tm_hour, pTime->tm_min, pTime->tm_sec);
    return buf;
}

YmDate::YmDate()	// Default constructor, initialise avec la date du jour
{
    _nbseconds = time (NULL);
    struct tm Tres;
    struct tm * pTime = localtime_r (&_nbseconds, &Tres);
    memcpy (&_datetime, pTime, sizeof (struct tm));
    _datetime.tm_sec = 0;
    _datetime.tm_min = 0;
    _datetime.tm_hour = 0;
    _nbseconds = mktime (&_datetime);
}

YmDate::YmDate(const YmDate& aYmDate) // Copy constructor
{
    _nbseconds = aYmDate._nbseconds;
    memcpy (&_datetime, &aYmDate._datetime, sizeof (struct tm));
}

YmDate::YmDate(const string& szAAAAMMJJ) // Construit et initialise une date a partir d'une string au format AAAAMMJJ

{
    // ou au format JJ/MM/AAAA. la diferentition se fait sur la intueur de la string
    memset (&_datetime, '\0', sizeof (struct tm));
    string sub;
    int year, month, day;

    year = month = day = 0;
    if (szAAAAMMJJ.size() == 8)
    {
        sub.assign (szAAAAMMJJ, 0, 4);
        year = atoi (sub.c_str());
        sub.assign (szAAAAMMJJ, 4, 2);
        month = atoi (sub.c_str());
        sub.assign (szAAAAMMJJ, 6, 2);
        day = atoi (sub.c_str());
    }
    else if (szAAAAMMJJ.size() == 10)
    {
        sub.assign (szAAAAMMJJ, 6, 4);
        year = atoi (sub.c_str());
        sub.assign (szAAAAMMJJ, 3, 2);
        month = atoi (sub.c_str());
        sub.assign (szAAAAMMJJ, 0, 2);
        day = atoi (sub.c_str());
    }

    if (year) year -= 1900;
    _datetime.tm_year = year;

    if (month) month -= 1;
    _datetime.tm_mon = month;

    if (!day) day = 1;
    _datetime.tm_mday = atoi (sub.c_str());

    // Si le format de szAAAAMMJJ est incorrect on aura le 1 janvier 1900. (year = 0, month = 0, day = 1)

    _nbseconds = mktime (&_datetime);
}

YmDate::YmDate(int annee, int mois, int jour) // Construit et initialise une date a partir anne mois jour
{
    memset (&_datetime, '\0', sizeof (struct tm));
    if (annee > 1900)
        _datetime.tm_year = annee - 1900;
    if ((mois >= 1) && (mois <= 12))
        _datetime.tm_mon = mois - 1;
    if ((jour >= 1) && (jour <= 31))
        _datetime.tm_mday = jour;
    else
        _datetime.tm_mday = 1;

    _nbseconds = mktime (&_datetime);
}

string& YmDate::PrintFrench(string& scible, bool fullyear /*=true*/) const// renvoi scible: JJ/MM/AAAA si fullyear = true,
{						     		     //	au format JJ/MM/AA sinon
    char buf[11];
    AllPrint (buf, 1, fullyear);
    scible = buf;
    return scible;
}

string& YmDate::PrintUS(string& scible, bool fullyear /*=true*/) const     // renvoi scible: MM/DD/YYYY si fullyear = true,
{				                     		     //	au format MM/DD/YY sinon
    char buf[11];
    AllPrint (buf, 2, fullyear);
    scible = buf;
    return scible;
}

string& YmDate::PrintOracle(string& scible, bool fullyear /*=true*/) const // renvoi scible: YYYY/MM/DD si fullyear = true,
{				                     		     //	au format YY/MM/DD sinon
    char buf[11];
    AllPrint (buf, 3, fullyear);
    scible = buf;
    return scible;
}

string& YmDate::PrintResaven(string& scible, bool fullyear /*=true*/) const // renvoi scible: YYYYMMDD si fullyear = true,
{				                     		     //	au format YYMMDD sinon
    char buf[11];
    AllPrint (buf, 4, fullyear);
    scible = buf;
    return scible;
}

char* YmDate::PrintFrench(char* sbuf, bool fullyear /*=true*/) const // idem avec un char*
{
    return AllPrint (sbuf, 1, fullyear);
}

char* YmDate::PrintUS(char* sbuf, bool fullyear /*=true*/) const // idem avec un char*
{
    return AllPrint (sbuf, 2, fullyear);
}

char* YmDate::PrintOracle(char* sbuf, bool fullyear /*=true*/) const // idem avec un char*
{
    return AllPrint (sbuf, 3, fullyear);
}

char* YmDate::PrintResaven(char* sbuf, bool fullyear /*=true*/) const // idem avec un char*
{
    return AllPrint (sbuf, 4, fullyear);
}

int YmDate::WeekDay(bool bMondayFirst /*=true*/) const
{
    int jj;
    jj = _datetime.tm_wday;
    if (bMondayFirst)
    {
        if (jj == 0)
            return 7;
        return jj;
    }
    else
        return jj+1;
}

int YmDate::YearDay() const
{
    return _datetime.tm_yday;
}

int YmDate::year() const          // renvoi l'annee
{
    return (_datetime.tm_year + 1900);
}

int YmDate::month() const         // renvoi le mois
{
    return (_datetime.tm_mon + 1);
}

int YmDate::day() const           // renvoi le jour du mois
{
    return (_datetime.tm_mday);
}


char* YmDate::AllPrint (char* sbuf, int typrint, bool fullyear) const
{
    char bufAnnee[5];
    char bufMois[3];
    char bufJour[3];
    if (fullyear)
        sprintf (bufAnnee, "%4.4u", _datetime.tm_year + 1900);
    else
        sprintf (bufAnnee, "%2.2u", _datetime.tm_year + 1900);
    sprintf (bufMois, "%2.2u", _datetime.tm_mon + 1);
    sprintf (bufJour, "%2.2u", _datetime.tm_mday);

    if (typrint == 1) // French Mode
        sprintf (sbuf, "%s/%s/%s", bufJour, bufMois, bufAnnee);
    else if (typrint == 2) // US Mode
        sprintf (sbuf, "%s/%s/%s", bufMois, bufJour, bufAnnee);
    else if (typrint == 3)
        sprintf (sbuf, "%s/%s/%s", bufAnnee, bufMois, bufJour);
    else
        sprintf (sbuf, "%s%s%s", bufAnnee, bufMois, bufJour);

    return sbuf;
}

int YmDate::DaysFrom70() const
{
    int jjj = _nbseconds / 86400;
    return jjj;
}

YmDate& YmDate::operator=(const YmDate& aYmDate)
{
    _nbseconds = aYmDate._nbseconds;
    memcpy (&_datetime, &aYmDate._datetime, sizeof (struct tm));
    return *this;
}

bool YmDate::operator==(const YmDate& aYmDate) const
{
    return ((_nbseconds / 86400) == (aYmDate._nbseconds / 86400));
}

bool YmDate::operator!=(const YmDate& aYmDate) const
{
    return ((_nbseconds / 86400) != (aYmDate._nbseconds / 86400));
}

bool YmDate::operator>=(const YmDate& aYmDate) const
{
    return ((_nbseconds / 86400) >= (aYmDate._nbseconds / 86400));
}

bool YmDate::operator<=(const YmDate& aYmDate) const
{
    return ((_nbseconds / 86400) <= (aYmDate._nbseconds / 86400));
}

bool YmDate::operator>(const YmDate& aYmDate) const
{
    return ((_nbseconds / 86400) > (aYmDate._nbseconds / 86400));
}

bool YmDate::operator<(const YmDate& aYmDate) const
{
    return ((_nbseconds / 86400) < (aYmDate._nbseconds / 86400));
}

YmDate& YmDate::operator+=(int nbjour)
{
    _nbseconds += (nbjour * 86400);
    struct tm Tres;
    struct tm * pTime = localtime_r (&_nbseconds, &Tres);
    memcpy (&_datetime, pTime, sizeof (struct tm));
    return *this;
}

YmDate& YmDate::operator-=(int nbjour)
{
    _nbseconds -= (nbjour * 86400);
    struct tm Tres;
    struct tm * pTime = localtime_r (&_nbseconds, &Tres);
    memcpy (&_datetime, pTime, sizeof (struct tm));
    return *this;
}

YmDate& YmDate::operator++()
{
    _nbseconds += 86400;
    struct tm Tres;
    struct tm * pTime = localtime_r (&_nbseconds, &Tres);
    memcpy (&_datetime, pTime, sizeof (struct tm));
    return *this;
}

YmDate& YmDate::operator--()
{
    _nbseconds -= 86400;
    struct tm Tres;
    struct tm * pTime = localtime_r (&_nbseconds, &Tres);
    memcpy (&_datetime, pTime, sizeof (struct tm));
    return *this;
}


int compareDatetimes(const YmDate& day1, int time1, const YmDate& day2, int time2)
{
    // Comparaison lexicographique date puis heure
    if(day1 > day2)
        return +1;
    if(day1 < day2)
        return -1;

    if(time1 > time2)
        return +1;
    if(time1 < time2)
        return -1;

    return 0;
}


namespace std
{
    ostream& operator<<(ostream& os, const YmDate& date)
    {
        char buf[11];
        date.PrintFrench(buf, true);
        buf[10] = '\0';
        return os << buf;
    }
}
