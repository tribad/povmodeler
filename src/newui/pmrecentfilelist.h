// **************************************************************************
//
// Modul-Name        : pmrecentfilelist.h
// Author            : Hans-Juergen Lange <hjl@simulated-universe.de>
// Creation-Date     : 27.10.2019
//
//  Copyrights by Hans-Juergen Lange. All rights reserved.
//
// **************************************************************************

#ifndef PMRECENTFILELIST_H
#define PMRECENTFILELIST_H
#include <QString>
#include <list>

class PMRecentFileList
{
public:
    PMRecentFileList();
    void                SetMaxFiles(unsigned int aMaxFiles);
    unsigned int        GetMaxFiles() {return mMaxFiles;}
    void                SetFile(const QString& aPath);
    std::list<QString>& GetFiles() {return mFiles;}
    void                Remove(const QString& aPath);
    void                Load();
private:
    void                UpdateSettings();
private:
    unsigned int       mMaxFiles;
    std::list<QString> mFiles;
};

#endif // PMRECENTFILELIST_H
