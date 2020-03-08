#include <QMenu>
#include "pmimenubar.h"

PMIMenuBar::PMIMenuBar()
{
    QMenu* m;

    m = AddMenu("File");
    //
    //  addAction() calls here are the standard calls to the QMenu object.
    m->addAction(new QAction( "New" ));
    m->addAction(new QAction("Open"));

    m->addMenu(AddMenu("Recent File", "File/Recent File"));

    m->addAction(new QAction("Save"));
    m->addAction(new QAction("Save as"));
    m->addAction(new QAction("Revert"));
    m->addSeparator();
    m->addAction(new QAction("Print"));
    m->addSeparator();
    m->addAction(new QAction("Close"));
    m->addAction(new QAction("Quit"));

    AddMenu("Edit");

    m = AddMenu("View");

    m->addAction("New Object Tree");
    m->addAction("New Properties View");
    m->addAction("New Library Browser");
    m->addSeparator();
    m->addAction("New Top View");
    m->addAction("New Bottom View");
    m->addAction("New Left View");
    m->addAction("New Right View");
    m->addAction("New Front View");
    m->addAction("New Back View");
    m->addAction("New Camera View");
    m->addSeparator();

    AddMenu("Insert");

    m = AddMenu("Settings");

    m->addAction("Show &List")->setCheckable( true );
    m->addAction("Show &Path")->setCheckable( true );
    m->addAction("Show &Status Bar")->setCheckable( true );
    m->addAction("");
    //
    //  This addition is a marker for the toolbar initialization sequence.
    //  As it can be searched for and new toolbar activation action can be added later.
    m->addSection("Toolbars");

    m->addAction("");
    m->addSection("App. Layout");
    m->addAction("Preferences");
    m->addAction("Save Options");
}

PMIMenuBar::~PMIMenuBar() {

}

QMenu* PMIMenuBar::AddMenu(const QString& title) {
    QMenu* retval = new QMenu(title);

    addMenu(retval);
    menu[title] = retval;

    return retval;
}

QMenu* PMIMenuBar::AddMenu(const QString& title, const QString& key, bool addToMenuBar) {
    QMenu* retval = new QMenu(title);

    if (addToMenuBar == true) {
        addMenu(retval);
    }
    menu[key] = retval;

    return retval;
}

QMenu* PMIMenuBar::GetMenu(const QString& title) {
    QMenu* retval = nullptr;
    auto   mi = menu.find(title);

    if (mi != menu.end()) {
        retval = mi->second;
    }
    return retval;
}

QAction* PMIMenuBar::GetAction(const QString& menuKey, const QString& actionTitle) {
    QAction* retval = nullptr;

    auto mi = menu.find(menuKey);

    if (mi != menu.end()) {
        QList<QAction*> qa = mi->second->actions();

        for (auto a : qa) {
            if (a->text() == actionTitle) {
                retval = a;
                break;
            }
        }
    }
    return retval;
}
