// **************************************************************************
//
// Modul-Name        : pmrecentfilelist.cpp
// Author            : Hans-Juergen Lange <hjl@simulated-universe.de>
// Creation-Date     : 27.10.2019
//
//  Copyrights by Hans-Juergen Lange. All rights reserved.
//
// **************************************************************************

#include "pmrecentfilelist.h"
#include "pmsettings.h"

PMRecentFileList::PMRecentFileList()
{

}

void PMRecentFileList::SetMaxFiles(unsigned int aMaxFiles) {
    mMaxFiles = aMaxFiles;
    //
    //  Need to reduce the list from the back.
    while (mFiles.size() > mMaxFiles) {
        //
        //  Remove key from settings and then the file from the list.
        PMSettings::instance().remove(recentfile_key_prefix + QString::number(mFiles.size()));

        mFiles.pop_back();
    }
}

void PMRecentFileList::SetFile(const QString &aPath) {
    //
    //  Check for existance of the file in list.
    std::list<QString>::iterator fi = mFiles.begin();

    while (fi != mFiles.end()) {
        if (*fi == aPath) {
            break;
        }
    }
    //
    //  Got a new path for the filelist.
    if (fi == mFiles.end()) {
        mFiles.push_front(aPath);
        //
        //  To make sure we do not missed something in between.
        //  Even if the mMaxFiles differs more than one from the real size of
        //  the list we remove them all. But let the settings stay at they are.
        //  We need to update the file list anyway.
        while (mFiles.size() > mMaxFiles) {
            mFiles.pop_back();
        }
    } else {
        //
        //  Remove on old position and put it back in front.
        mFiles.erase(fi);
        mFiles.push_front(aPath);
    }
    //
    //  Update the settings Position starts with 1
    unsigned int filepos = 1;

    for (auto f : mFiles) {
        PMSettings::instance().setValue(recentfile_key_prefix + QString::number(filepos++), f);
    }
}
