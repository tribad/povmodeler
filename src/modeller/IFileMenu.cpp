// *************************************************************************************************************
//
//  Modul-Name     : IFileMenu.cpp
//
//  Copyrights by Hans-Juergen Lange <hjl@simulated-universe.de>. All rights reserved.
//
// *************************************************************************************************************
//
//  All needed headers in header file. This is needed for the moc tool.
#include "IFileMenu.h"
// Optional
#include <QSettings>
#include "CSettings.h"
void IFileMenu::New(void) {
// User-Defined-Code:AAAAAAFwzgoeWgDheho=
// End-Of-UDC:AAAAAAFwzgoeWgDheho=
}

void IFileMenu::Load(void) {
// User-Defined-Code:AAAAAAFwzfZCkP/1yjU=
    //
    //  Get the last visited from the settings.
    //  If not set already we take the users home directory.
    QString last_visited = CSettings::instance().value(LAST_DIRECTORY_VISITED, QDir::homePath()).toString();

    QString to_open = QFileDialog::getOpenFileName(nullptr, "Open File", last_visited, "POV modeler (*.kpm)");
    //
    //  If the user selected a file we do open it.
    //  This also updates the recent file list.
    if (!to_open.isEmpty()) {
        emit Load(to_open);
        //
        //  Convenient way to get the directory where the file resides.
        QFileInfo now_visited(to_open);

        CSettings::instance().setValue(LAST_DIRECTORY_VISITED, now_visited.absolutePath());
    }
// End-Of-UDC:AAAAAAFwzfZCkP/1yjU=
}

void IFileMenu::LoadRecent(void) {
// User-Defined-Code:AAAAAAFwzgvPYQD/gTo=
// End-Of-UDC:AAAAAAFwzgvPYQD/gTo=
}

void IFileMenu::Save(void) {
// User-Defined-Code:AAAAAAFwzgn0eQDaF5s=
// End-Of-UDC:AAAAAAFwzgn0eQDaF5s=
}

void IFileMenu::Close(void) {
// User-Defined-Code:AAAAAAFwzgsyqgD3d2Y=
// End-Of-UDC:AAAAAAFwzgsyqgD3d2Y=
}

