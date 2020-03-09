#include <iostream>
#include <iomanip>
#include <CThread.h>
#include <msg.h>
#include <CEvent.h>
#include <logthread.h>

CLogThread CLogThread::Instance;

CLogThread::CLogThread()
{
    //
    //  Always startup with all moduls logging allowed
    Modul    = UINT64_MAX;
    Medium   = MEDIATYPE_CONSOLE;
    bRunning = false;
}

CLogThread::~CLogThread() {

}

bool CLogThread::InitInstance() {
    bool retval = false;

    if (CThread::InitInstance()) {
        retval = bRunning = true;
    }
    return retval;
}

long CLogThread::Run() {
    tMsg* msg = 0;

    for (;bRunning;) {
        q.Wait();

        msg = q.Get();
        if (msg != nullptr) {
            switch (msg->id) {
            case 0x7f2bf08135d803af:
                Process((CMsgEnableModul*)(msg));
                break;
            case 0x4872c94302313910:
                Process((CMsgDisableModul*)(msg));
                break;
            case 0x0f3d8672ebe0ab8e:
                Process((CMsgWriteLog*)(msg));
                break;
            default:
                //
                //  Free the unprocessed message
                delete msg;
                break;
            }
        }
    }
    return 0;
}

void CLogThread::RegisterModul(uint64_t aModul, std::string aName) {
    std::map<uint64_t, std::string>::iterator mi = ModulMap.find(aModul);

    if (mi == ModulMap.end()) {
        ModulMap.insert(std::pair<uint64_t, std::string>(aModul, aName));
    } else {

    }
}

void CLogThread::Process(CMsgWriteLog *aMsg) {
    if (Medium & MEDIATYPE_CONSOLE) {
        ConsoleOutput(aMsg);
    }
    if (Medium & MEDIATYPE_NCURSES) {
        NcursesOutput(aMsg);
    }
    if (Medium & MEDIATYPE_SYSLOG) {
        SyslogOutput(aMsg);
    }
    delete aMsg;
}

void CLogThread::ConsoleOutput(CMsgWriteLog *aMsg) {
    std::cerr << aMsg->stamp.Format("%d.%m.%Y %H:%M:%S") << "." << std::setw(3) << std::setfill('0') << aMsg->stamp.GetMilliSecond() << " ";

    std::map<uint64_t, std::string>::iterator mi = ModulMap.find(aMsg->modul);

    if (mi != ModulMap.end()) {
        std::cerr << mi->second << " :: ";
    }
    std::cerr << aMsg->msg << std::endl;
}
void CLogThread::NcursesOutput(CMsgWriteLog *aMsg) {
}
void CLogThread::SyslogOutput(CMsgWriteLog *aMsg) {

}

void CLogThread::Process(CMsgEnableModul *aMsg) {
    Modul |= aMsg->modul;

    delete aMsg;
}
void CLogThread::Process(CMsgDisableModul *aMsg) {
    Modul &= ~(aMsg->modul);

    delete aMsg;
}
