// **************************************************************************
//
// Modul-Name        : CSystemTime.cpp
// Author            : Hans-Juergen Lange <hjl@simulated-universe.de>
// Creation-Date     : 13.01.2011
// Modification-Date : 05.05.2011 10:13:05
//
//  Copyrights by Hans-Juergen Lange. All rights reserved.
//
// **************************************************************************
// **************************************************************************
//                   E x t r a   I n c l u d e   L i s t
// **************************************************************************
#include <sys/time.h>
#include <time.h>
#include <string>
#include <stddef.h>
#include <stdint.h>
#include <sstream>
// **************************************************************************
//                   F i r s t   I n c l u d e   L i s t
// **************************************************************************
#include "CSystemTime.h"
// **************************************************************************
//                   L a s t   I n c l u d e   L i s t
// **************************************************************************
// **************************************************************************
//                   N a m e s p a c e   L i s t
// **************************************************************************
const char* CSystemTime::WeekDay[] = {"Sun", "Mon",  "Tue", "Wed", "Thu", "Fri", "Sat"};
const char* CSystemTime::Month[] = {"Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sept", "Oct", "Nov", "Dec"};
// **************************************************************************
//
//  Method-Name       : CSystemTime()
//  Author            : Hans-Juergen Lange <hjl@simulated-universe.de>
//  Creation-Date     : 21.02.2011
//  Modification-Date : 12.04.2011 14:49:56
//
//  Copyrights by Hans-Juergen Lange. All rights reserved.
//
// **************************************************************************
CSystemTime::CSystemTime() {
    struct tm t;
    struct timeval tv;
    
    gettimeofday(&tv, 0);
    Time=tv.tv_sec;
    localtime_r(&Time, &t);
    
    tm_year=t.tm_year+1900;
    tm_mon=t.tm_mon+1;
    tm_wday=t.tm_wday;
    tm_mday=t.tm_mday;
    tm_hour=t.tm_hour;
    tm_min=t.tm_min;
    tm_sec=t.tm_sec;
    tm_msec=tv.tv_usec/1000;
}
// **************************************************************************
//
//  Method-Name       : GetYear()
//  Author            : Hans-Juergen Lange <hjl@simulated-universe.de>
//  Creation-Date     : 23.02.2011
//  Modification-Date : 23.02.2011 12:14:10
//
//  Copyrights by Hans-Juergen Lange. All rights reserved.
//
// **************************************************************************
int CSystemTime::GetYear() {
    return (tm_year);
}
// **************************************************************************
//
//  Method-Name       : GetMonth()
//  Author            : Hans-Juergen Lange <hjl@simulated-universe.de>
//  Creation-Date     : 23.02.2011
//  Modification-Date : 23.02.2011 12:14:22
//
//  Copyrights by Hans-Juergen Lange. All rights reserved.
//
// **************************************************************************
int CSystemTime::GetMonth() {
    return(tm_mon);
}
// **************************************************************************
//
//  Method-Name       : GetDayOfMonth()
//  Author            : Hans-Juergen Lange <hjl@simulated-universe.de>
//  Creation-Date     : 23.02.2011
//  Modification-Date : 23.02.2011 12:14:51
//
//  Copyrights by Hans-Juergen Lange. All rights reserved.
//
// **************************************************************************
int CSystemTime::GetDayOfMonth() {
    return (tm_mday);
}
// **************************************************************************
//
//  Method-Name       : GetWeekDay()
//  Author            : Hans-Juergen Lange <hjl@simulated-universe.de>
//  Creation-Date     : 23.02.2011
//  Modification-Date : 23.02.2011 12:14:55
//
//  Copyrights by Hans-Juergen Lange. All rights reserved.
//
// **************************************************************************
int CSystemTime::GetWeekDay() {
    return (tm_wday);
}
// **************************************************************************
//
//  Method-Name       : GetHour()
//  Author            : Hans-Juergen Lange <hjl@simulated-universe.de>
//  Creation-Date     : 23.02.2011
//  Modification-Date : 23.02.2011 12:14:58
//
//  Copyrights by Hans-Juergen Lange. All rights reserved.
//
// **************************************************************************
int CSystemTime::GetHour() {
    return (tm_hour);
}
// **************************************************************************
//
//  Method-Name       : GetMinute()
//  Author            : Hans-Juergen Lange <hjl@simulated-universe.de>
//  Creation-Date     : 23.02.2011
//  Modification-Date : 23.02.2011 12:15:02
//
//  Copyrights by Hans-Juergen Lange. All rights reserved.
//
// **************************************************************************
int CSystemTime::GetMinute() {
    return (tm_min);
}
// **************************************************************************
//
//  Method-Name       : GetSecond()
//  Author            : Hans-Juergen Lange <hjl@simulated-universe.de>
//  Creation-Date     : 23.02.2011
//  Modification-Date : 23.02.2011 12:15:06
//
//  Copyrights by Hans-Juergen Lange. All rights reserved.
//
// **************************************************************************
int CSystemTime::GetSecond() {
    return (tm_sec);
}
// **************************************************************************
//
//  Method-Name       : GetMilliSecond()
//  Author            : Hans-Juergen Lange <hjl@simulated-universe.de>
//  Creation-Date     : 23.02.2011
//  Modification-Date : 23.02.2011 12:15:17
//
//  Copyrights by Hans-Juergen Lange. All rights reserved.
//
// **************************************************************************
int CSystemTime::GetMilliSecond() {
    return (tm_msec);
}
// **************************************************************************
//
//  Method-Name       : Format()
//  Author            : Hans-Juergen Lange <hjl@simulated-universe.de>
//  Creation-Date     : 24.02.2011
//  Modification-Date : 25.02.2011 14:31:54
//
//  Copyrights by Hans-Juergen Lange. All rights reserved.
//
// **************************************************************************
std::string CSystemTime::Format(const char* aFormat) {
    char buffer[1024];
    struct tm tmm;
    
    localtime_r(&Time, &tmm);
    strftime(buffer, sizeof(buffer)-1, aFormat, &tmm);
    
    return (std::string(buffer));
}
// **************************************************************************
//
//  Method-Name       : Get1123Date()
//  Author            : Hans-Juergen Lange <hjl@simulated-universe.de>
//  Creation-Date     : 25.02.2011
//  Modification-Date : 25.02.2011 14:33:36
//
//  Copyrights by Hans-Juergen Lange. All rights reserved.
//
// **************************************************************************
std::string CSystemTime::Get1123Date() {
    std::ostringstream oss;
    
    oss << WeekDay[tm_wday] << ", " ;
    oss.width(2);
    oss.fill('0');
    oss << tm_mday << " ";
    oss << Month[tm_mon] << " " ;
    oss.width(4);
    oss << tm_year << " ";
    oss.width(2);
    oss << tm_hour << ":";
    oss.width(2);
    oss << tm_min << ":";
    oss.width(2);
    oss << tm_sec << " GMT";
    
    return (oss.str());
    
    
}
// **************************************************************************
//
//  Method-Name       : Set()
//  Author            : 
//  Creation-Date     : 30.03.2011
//  Modification-Date : 12.04.2011 14:49:55
//
//  Copyrights by Hans-Juergen Lange. All rights reserved.
//
// **************************************************************************
void CSystemTime::Set(time_t aTime) {
    struct tm t;
    struct timeval tv;
    
    gettimeofday(&tv, 0);
    Time=tv.tv_sec;
    localtime_r(&Time, &t);
    
    tm_year=t.tm_year+1900;
    tm_mon=t.tm_mon+1;
    tm_wday=t.tm_wday;
    tm_mday=t.tm_mday;
    tm_hour=t.tm_hour;
    tm_min=t.tm_min;
    tm_sec=t.tm_sec;
    tm_msec=tv.tv_usec/1000;
    
}
// **************************************************************************
//
//  Method-Name       : operator==()
//  Author            : 
//  Creation-Date     : 06.04.2011
//  Modification-Date : 06.04.2011 10:48:48
//
//  Copyrights by Hans-Juergen Lange. All rights reserved.
//
// **************************************************************************
bool CSystemTime::operator==(CSystemTime& b) {
    if ((tm_msec==b.GetMilliSecond()) && (tm_sec==b.GetSecond()) &&
        (tm_min==b.GetMinute()) && (tm_hour==b.GetHour()) && (tm_mday==b.GetDayOfMonth()) &&
        (tm_mon==b.GetMonth()) && (tm_year==b.GetYear())) {
        return(true);
    } else {
        return (false);
    }
}
// **************************************************************************
//
//  Method-Name       : operator!=()
//  Author            : 
//  Creation-Date     : 06.04.2011
//  Modification-Date : 06.04.2011 10:48:56
//
//  Copyrights by Hans-Juergen Lange. All rights reserved.
//
// **************************************************************************
bool CSystemTime::operator!=(CSystemTime& b) {
    if ((tm_msec==b.GetMilliSecond()) && (tm_sec==b.GetSecond()) &&
        (tm_min==b.GetMinute()) && (tm_hour==b.GetHour()) && (tm_mday==b.GetDayOfMonth()) &&
        (tm_mon==b.GetMonth()) && (tm_year==b.GetYear())) {
        return(false);
    } else {
        return (true);
    }
    
}
// **************************************************************************
//
//  Method-Name       : operator>()
//  Author            : Hans-Juergen Lange <hjl@simulated-universe.de>
//  Creation-Date     : 05.05.2011
//  Modification-Date : 05.05.2011 10:14:47
//
//  Copyrights by Hans-Juergen Lange. All rights reserved.
//
// **************************************************************************
bool CSystemTime::operator>(CSystemTime& B) {
    if (tm_year>B.GetYear()) return (true);
    if ((tm_year==B.GetYear()) && (tm_mon>B.GetMonth())) return (true);
    if ((tm_mon==B.GetMonth()) && (tm_mday>B.GetDayOfMonth())) return (true);
    if ((tm_mday==B.GetDayOfMonth()) && (tm_hour>B.GetHour())) return (true);
    if ((tm_hour==B.GetHour()) && (tm_min>B.GetMinute())) return (true);
    if ((tm_min==B.GetMinute()) && (tm_sec>B.GetSecond())) return (true);
    if ((tm_sec==B.GetSecond()) && (tm_msec>B.GetMilliSecond())) return (true);
    return (false);
}
// **************************************************************************
//
//  Method-Name       : operator<()
//  Author            : Hans-Juergen Lange <hjl@simulated-universe.de>
//  Creation-Date     : 05.05.2011
//  Modification-Date : 05.05.2011 10:15:12
//
//  Copyrights by Hans-Juergen Lange. All rights reserved.
//
// **************************************************************************
bool CSystemTime::operator<(CSystemTime& B) {
    if (tm_year<B.GetYear()) return (true);
    if ((tm_year==B.GetYear()) && (tm_mon<B.GetMonth())) return (true);
    if ((tm_mon==B.GetMonth()) && (tm_mday<B.GetDayOfMonth())) return (true);
    if ((tm_mday==B.GetDayOfMonth()) && (tm_hour<B.GetHour())) return (true);
    if ((tm_hour==B.GetHour()) && (tm_min<B.GetMinute())) return (true);
    if ((tm_min==B.GetMinute()) && (tm_sec<B.GetSecond())) return (true);
    if ((tm_sec==B.GetSecond()) && (tm_msec<B.GetMilliSecond())) return (true);
    return (false);
    
}
