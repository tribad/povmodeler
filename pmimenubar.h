#ifndef PMIMENUBAR_H
#define PMIMENUBAR_H

#include <QMenuBar>
#include <QMenu>
#include <QAction>

class PMIMenuBar : public QMenuBar
{
    Q_OBJECT
public:
    PMIMenuBar();
    virtual ~PMIMenuBar();
    QAction* GetAction(const QString& menuKey, const QString& actionTitle);
    QMenu* GetMenu(const QString& title);
    QMenu* AddMenu(const QString& title);
    QMenu* AddMenu(const QString& title, const QString& key, bool addToMenuBar=false);
public:
    std::map<QString, QMenu*> menu;
};

#endif // PMIMENUBAR_H
