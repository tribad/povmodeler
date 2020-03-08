//-*-C++-*-
/*
**************************************************************************
                                 description
                             --------------------
    copyright            : (C) 2000-2006 by Andreas Zehender
    email                : zehender@kde.org
**************************************************************************

**************************************************************************
*                                                                        *
*  This program is free software; you can redistribute it and/or modify  *
*  it under the terms of the GNU General Public License as published by  *
*  the Free Software Foundation; either version 2 of the License, or     *
*  (at your option) any later version.                                   *
*                                                                        *
**************************************************************************/


#ifndef PMSHELL_H
#define PMSHELL_H

#include "pmdockwidget.h"

//#include "pmpart.h"
#include "pmglview.h"
#include "version.h"

#include <QMenu>
#include "libpovmodeler_export.h"
#include <QToolBar>
#include "pmimenubar.h"
#include "ipmshell.h"
#include "ipmpartextern.h"
class QStatusBar;
class PMViewOptions;
class PMPart;

/**
 * Main view for PovModeler
 */
class LPOVMODELER_EXPORT PMShell : public PMDockMainWindow, public IPMShell
{
   Q_OBJECT

public:
   /**
    * Standard constructor
    */
   PMShell( const QUrl& = QUrl() );
   /**
    * Destructor
    */
   virtual ~PMShell();

   QMenu* getLayouts(){ return layout_viewMenu_submenu; }

   virtual QMenu* get_editMenu()   { return mMenuBar->GetMenu("Edit"); }
   virtual QMenu* get_viewMenu()   { return mMenuBar->GetMenu("View"); }
   virtual QMenu* get_fileMenu()   { return mMenuBar->GetMenu("File"); }
   virtual QMenu* get_insertMenu() { return mMenuBar->GetMenu("Insert"); }

   virtual PMIMenuBar* GetMainWindowMenuBar()  {return mMenuBar;}

   /**
    * Creates the actions
    */
   void setupActions();
   /**
    * Creates the docking views
    */
   void setupView();
   /**
    * Updates the gui (menus and toolbars)
    */
   void updateGUI();

   /**
    * Checks if a file with that name exists and asks if
    * it should be overwritten.
    *
    * Returns true if the files is not a local file, the file does'n exist
    * or the file should be overwritten.
    */
   static bool overwriteURL( const QUrl &u );
   /***eticre view-hide Declare with name have "_" at first char***/
   /**
     eticre show hidden obj not_in_tree
   */
   bool show_list;
   //using KMainWindow::setWindowTitle;

public slots:
   void openUrl( const QUrl& );
   void slotOpenRecent( QAction* action );

   void slotFileNew();
   void slotFileOpen();
   void slotFileSave();
   void slotFileSaveAs();
   void slotFileRevert();
   void slotFilePrint();
   void slotFileNewWindow();
   void slotFileClose();

   void slotShowStatusbar( bool b );
   void slotShowPath();
   /***eticre show lib***/
   void slotShowList();
   void slotSettings();
   void slotNewGraphicalView( PMGLView::PMViewType );
   void slotNewTopView();
   void slotNewBottomView();
   void slotNewLeftView();
   void slotNewRightView();
   void slotNewFrontView();
   void slotNewBackView();
   void slotNewCameraView();
   void slotNewTreeView();
   void slotNewDialogView();
   void slotNewLibraryBrowserView();

   void saveOptions();
   void restoreOptions();

   void setWindowTitle( const QString& caption = QString() );
   void statusMsg( const QString& text = QString() );

   virtual void slotControlPointMsg( const QString& msg = QString() );

   void slotModified(bool m);
   void slotDockWidgetClosed();
   void slotDeleteClosedObjects();
   void slotSelectedLayout( QAction* action );
   void slotSaveViewLayout();
   void slotViewsMenuAboutToShow();
protected:
    virtual bool queryClose();
	virtual void showEvent( QShowEvent* );
    void saveAs();
    void setSize();

public:
   /**
    * Creates a dock widget of view type t with custom config c.
    *
    * If initPosition is true, the widget is docked to the desktop.
    */
   PMDockWidget* createView( const QString& t, PMViewOptions* c = nullptr,
                             bool initPosition = true );
    virtual void modified(bool m);
private:
   void closeEvent( QCloseEvent *event );
   void shellClose();

   void restoreRecent();
   QList<QAction*>recentFileAction;
   QList<QVariant>recent_urls;
   void add_recentFiles( QUrl url );

   //KRecentFilesAction* m_pRecent;

   QAction*        m_pStatusbarAction;
   QStatusBar*     m_pStatusBar;
   QLabel*         statusBarLabel;
   PMPart*         m_pPart;
   QUrl            m_openRecentURL;
   QUrl            currentUrl;

   QList<QObject*> m_objectsToDelete;
   int             m_viewNumber;

   QMenu*          settingsMenu;
   QMenu*          layout_viewMenu_submenu;
   //
   //  The new thingies.
   PMIMenuBar*     mMenuBar;
   IPMPartExtern*  mPart;
};

#endif
