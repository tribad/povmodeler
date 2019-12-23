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

#include <QAction>
#include <QStatusBar>
#include <QFileDialog>
#include <QMenuBar>
#include <QTimer>
#include <QSettings>
#if QT_VERSION >= 0x050000
    #include <QStandardPaths>
#endif
#include <QMessageBox>
#include <QShowEvent>

#include "pmshell.h"
#include "pmpart.h"
#include "ipmpartextern.h"
#include "pmsettingsdialog.h"
#include "pmdefaults.h"
#include "pmdockwidget.h"
#include "pmviewbase.h"
#include "pmunknownview.h"
#include "pmviewlayoutmanager.h"

#define KPM_WITH_OBJECT_LIBRARY

PMShell::PMShell( const QUrl &url )
      : PMDockMainWindow( nullptr )
{
   setAttribute( Qt::WA_DeleteOnClose );
   statusBarLabel = new QLabel( this );
   currentUrl = nullptr;
   m_pPart    = nullptr;
   /***call pmpart with mainwidget***/

   m_viewNumber = 0;
   /***eticre view-hide Declare with name have "_" at first char***/
   show_list = false;

   //
   //  Do not know why this is important. But let it stay here. Does not harm.
   //  Removing all toolbars that may be installed by magic.
   QList<QToolBar *> allToolBars = this->findChildren<QToolBar *>();
   foreach(QToolBar *tb, allToolBars) {
       // This does not delete the tool bar.
       this->removeToolBar(tb);
   }
    //
    //  construct most of the menubar content
    mMenuBar         = new PMIMenuBar;
#if QT_VERSION >= 0x050000
    mMenuBar->GetMenu("File/Recent File")->setToolTipsVisible(true);
#endif
    setMenuBar(mMenuBar);
    //
    //  Connect the actions to the slots.
    setupActions();
    //
    //  Create the povmodeler.
    m_pPart = new PMPart(this, this, true, this, mMenuBar);
    //
    //  Transfer the actions from the menu initialization to the toolbars.
    std::vector<QToolBar*> toolbars = m_pPart->toolbars();

    for (auto toolbar : toolbars) {
        toolbar->addActions(m_pPart->getMenu(toolbar->windowTitle())->actions());
        addToolBar(toolbar);
    }
    restoreRecent();
    restoreOptions();
    setSize();
    setupView();

    m_pStatusBar = statusBar();
    m_pStatusBar->addWidget ( statusBarLabel, 1 );
    statusBarLabel->setText(" Status Bar ");

   if( !url.isEmpty() )
   {
      openUrl( url );
      currentUrl = url;
   }

   setWindowTitle( url.toString() );

   QSettings qset;
   restoreState( qset.value("mainwindow/state").toByteArray() );

   connect( m_pPart, SIGNAL( controlPointMessage( const QString& ) ),
                       SLOT( slotControlPointMsg( const QString& ) ) );
}

PMShell::~PMShell()
{
    QSettings qset;

    qset.setValue( "mainwindow/size", this->size() );
    qset.setValue( "mainwindow/fullscreen", this->isFullScreen() );
    qset.setValue( "mainwindow/state", saveState(0) );
}

void PMShell::setSize()
{
    QSettings qset;
    if ( qset.value( "mainwindow/fullscreen" ).toBool() )
       this->showFullScreen();
    else if ( qset.contains( "mainwindow/size" ) )
        this->resize( qset.value( "mainwindow/size" ).toSize() );
    else
        this->resize( 1024, 800 );
}

void PMShell::setupActions()
{
    //
    //  File menu specific connects
    connect( mMenuBar->GetAction("File", "New"),     SIGNAL(triggered()), this, SLOT(slotFileNew()) );
    connect( mMenuBar->GetAction("File", "Open"),    SIGNAL(triggered()), this, SLOT(slotFileOpen()) );
    connect( mMenuBar->GetMenu("File/Recent File"),  SIGNAL(triggered(QAction*)),   this, SLOT(slotOpenRecent(QAction*)) );
    connect( mMenuBar->GetAction("File", "Save"),    SIGNAL(triggered()), this, SLOT(slotFileSave()) );
    connect( mMenuBar->GetAction("File", "Save as"), SIGNAL(triggered()), this, SLOT(slotFileSaveAs()) );
    connect( mMenuBar->GetAction("File", "Revert"),  SIGNAL(triggered()), this, SLOT(slotFileRevert()) );
    connect( mMenuBar->GetAction("File", "Print"),   SIGNAL(triggered()), this, SLOT(slotFilePrint ()));
    connect( mMenuBar->GetAction("File", "Close"),   SIGNAL(triggered()), this, SLOT(slotFileClose()) );
    connect( mMenuBar->GetAction("File", "Quit"),    SIGNAL(triggered()), this, SLOT(shellClose()) );
    //
    //  Settings specific connects.
    connect( mMenuBar->GetAction("Settings", "Show &List"),       SIGNAL( triggered() ), this, SLOT( slotShowList() ) );
    connect( mMenuBar->GetAction("Settings", "Show &Path"),       SIGNAL( triggered() ), this, SLOT( slotShowPath() ) );
    connect( mMenuBar->GetAction("Settings", "Show &Status Bar"), SIGNAL( triggered() ), this, SLOT( saveOptions() ) );
    connect( mMenuBar->GetAction("Settings", "Preferences" ),     SIGNAL( triggered() ), this, SLOT( slotSettings() ) );
    connect( mMenuBar->GetAction("Settings", "Save Options"),     SIGNAL( triggered() ), this, SLOT( saveOptions() ) );
    //
    //  View menu specific signal connects.
    connect( mMenuBar->GetAction("View", "New Object Tree"),      SIGNAL( triggered() ), this, SLOT( slotNewTreeView() ) );
    connect( mMenuBar->GetAction("View", "New Properties View" ), SIGNAL( triggered() ), this, SLOT( slotNewDialogView() ) );
#ifdef KPM_WITH_OBJECT_LIBRARY
    connect( mMenuBar->GetAction("View", "New Library Browser"),  SIGNAL( triggered() ), this, SLOT( slotNewLibraryBrowserView() ) );
#endif
    connect( mMenuBar->GetAction("View", "New Top View" ),        SIGNAL( triggered() ), this, SLOT( slotNewTopView() ) );
    connect( mMenuBar->GetAction("View", "New Bottom View" ),     SIGNAL( triggered() ), this, SLOT( slotNewBottomView() ) );
    connect( mMenuBar->GetAction("View", "New Left View" ),       SIGNAL( triggered() ), this, SLOT( slotNewLeftView() ) );
    connect( mMenuBar->GetAction("View", "New Right View" ),      SIGNAL( triggered() ), this, SLOT( slotNewRightView() ) );
    connect( mMenuBar->GetAction("View", "New Front View" ),      SIGNAL( triggered() ), this, SLOT( slotNewRightView() ) );
    connect( mMenuBar->GetAction("View", "New Back View" ),       SIGNAL( triggered() ), this, SLOT( slotNewBackView() ) );
    connect( mMenuBar->GetAction("View", "New Camera View"),      SIGNAL( triggered() ), this, SLOT( slotNewCameraView() ) );

#if 0
   layout_viewMenu_submenu = viewMenu->addMenu( tr( "View Layouts" ) );

   connect( layout_viewMenu_submenu, SIGNAL( aboutToShow() ), SLOT( slotViewsMenuAboutToShow() ) );
   PMViewLayoutManager::theManager()->fillPopupMenu( layout_viewMenu_submenu );
   connect( layout_viewMenu_submenu, SIGNAL( triggered( QAction* ) ), SLOT( slotSelectedLayout( QAction* ) ) );


   m_pSaveViewLayoutAction = viewMenu->addAction( "save_view_layout" );
   m_pSaveViewLayoutAction->setText( tr( "Save View Layout..." ) );
   connect( m_pSaveViewLayoutAction, SIGNAL( triggered() ), this, SLOT( slotSaveViewLayout() ) );
#endif

}

void PMShell::setupView()
{
   PMViewLayoutManager::theManager()->displayDefaultLayout( this );
}


PMDockWidget* PMShell::createView( const QString& t, PMViewOptions* o,
                                   bool initPosition )
{
   PMDockWidget* dock = nullptr;
   PMViewBase* contents = nullptr;

   PMViewTypeFactory* factory = PMViewFactory::theFactory()->viewFactory( t );

   m_viewNumber++;
   QString name = QString( "View (%1)" ).arg( m_viewNumber );

   if( factory )
   {
      QString desc;
      // Create the appropriate dock widget
      if( o )
         desc = factory->description( o );
      else
         desc = factory->description();

      dock = createDockWidget( QIcon::fromTheme( factory->iconName() ).pixmap( 16, 16), nullptr,
                               desc, desc );

      contents = factory->newInstance( dock, m_pPart );

      if( o ) contents->restoreViewConfig( o );
   }
   else
   {
      // unknown view type
      dock = createDockWidget( QIcon::fromTheme( "Unknown" ).pixmap( 16, 16), nullptr,
                               "Unknown", "Unknown" );
      contents = new PMUnknownView( t, dock );
   }

   dock->setWidget( contents );
   connect( dock, SIGNAL( headerCloseButtonClicked() ),
                  SLOT( slotDockWidgetClosed() ) );

   if( initPosition )
   {
      if( t == "librarybrowserview" )
          dock->resize( 800 , 600 );
      else
          dock->resize( 300 , 400 );

      dock->manualDock( nullptr, PMDockWidget::DockDesktop, 50,
                        mapToGlobal( QPoint( 50, 50 ) ) );
   }
   return dock;
}

void PMShell::slotNewGraphicalView( PMGLView::PMViewType t )
{
   PMGLViewOptions* o = new PMGLViewOptions( t );
   createView( "glview", o );
   delete o;
}

void PMShell::slotNewTopView()
{
   slotNewGraphicalView( PMGLView::PMViewNegY );
}

void PMShell::slotNewBottomView()
{
   slotNewGraphicalView( PMGLView::PMViewPosY );
}

void PMShell::slotNewLeftView()
{
   slotNewGraphicalView( PMGLView::PMViewPosX );
}

void PMShell::slotNewRightView()
{
   slotNewGraphicalView( PMGLView::PMViewNegX );
}

void PMShell::slotNewFrontView()
{
   slotNewGraphicalView( PMGLView::PMViewPosZ );
}

void PMShell::slotNewBackView()
{
   slotNewGraphicalView( PMGLView::PMViewNegZ );
}

void PMShell::slotNewCameraView()
{
   slotNewGraphicalView( PMGLView::PMViewCamera );
}

void PMShell::slotNewDialogView()
{
   createView( "dialogview" );
}

void PMShell::slotNewTreeView()
{
   createView( "treeview" );
}

void PMShell::slotNewLibraryBrowserView()
{
   createView( "librarybrowserview" );
}

void PMShell::slotDockWidgetClosed()
{
   QObject* o = sender();
   if( o && o->inherits( "PMDockWidget" ) )
   {
      if( !m_objectsToDelete.contains( o ) )
      {
         m_objectsToDelete.append( o );
         QTimer::singleShot( 0, this, SLOT( slotDeleteClosedObjects() ) );
      }
   }
}

void PMShell::slotDeleteClosedObjects()
{
	foreach(QObject* o, m_objectsToDelete) delete o;
   m_objectsToDelete.clear();
}

void PMShell::openUrl( const QUrl &url )
{
    add_recentFiles( url );

   if( !m_pPart->ismodified && m_pPart->url().isEmpty() )
   {
      m_pPart->openFileQt( url );
      setWindowTitle( m_pPart->url().toString() );
   }
   else
   {
      PMShell *shell = new PMShell();
      shell->show();
      shell->openUrl( url );
   }
}

void PMShell::slotFileNew()
{
   if( !m_pPart->ismodified && m_pPart->url().isEmpty() )
   {
      m_pPart->newDocument();
      setWindowTitle();
   }
   else
   {
      PMShell *shell = new PMShell();
      shell->show();
   }
}

void PMShell::slotFileOpen()
{
#if QT_VERSION >= 0x050000
   QUrl url = QFileDialog::getOpenFileUrl( this, "File", QUrl(), QString( "*.kpm|" ) +
     "Povray Modeler Files ( *.kpm )" +
     "\n*|" + "All Files" );
#else
   QUrl url = QFileDialog::getOpenFileName( this, "File", QString(), QString( "*.kpm|" ) +
     "Povray Modeler Files ( *.kpm )" +
     "\n*|" + "All Files" );
#endif


   if( !url.isEmpty() )
      openUrl( url );
}

void PMShell::add_recentFiles( QUrl url )
{
    if( !url.isEmpty() && !recent_urls.contains( url ))
    {
       int i = recentFileAction.length();
       if( i >= 9 )
       {
           recentFileAction.removeFirst();
           recent_urls.removeFirst();
       }

       recent_urls.append( url );
       QSettings qset;
       qset.setValue( "recent/recenturls", recent_urls );
       restoreRecent();
    }
}

void PMShell::restoreRecent()
{
    recentFileAction.clear();
    QSettings qset;
    recent_urls = qset.value("recent/recenturls").toList();
    if ( recent_urls.length()>0 )
        for ( int i = 0; i < recent_urls.size(); ++i )
        {
           QAction* a = new QAction(this);
           a->setText( QFileInfo( recent_urls.at(i).toUrl().path() ).fileName() );
           a->setData( recent_urls.at(i).toUrl() );
           a->setToolTip( recent_urls.at(i).toString() );
           recentFileAction.insert( 0, a );
        }
    mMenuBar->GetMenu("File/Recent File")->clear();
    mMenuBar->GetMenu("File/Recent File")->addActions( recentFileAction );
}

void PMShell::slotOpenRecent( QAction* action )
{
   m_pPart->openFileQt( action->data().toUrl() );
}

void PMShell::slotFileSave()
{
    m_pPart->slotAboutToSave();

   if( m_pPart->ismodified )
   {
      if( !currentUrl.isEmpty() && m_pPart->isReadWrite() ){
         m_pPart->saveFileQt( currentUrl );
      } else {
         saveAs();
      }
      setWindowTitle( m_pPart->url().toString() );
   }
   else
      emit statusMsg( tr( "No changes need to be saved" ) );
}

void PMShell::slotFileSaveAs()
{
    m_pPart->slotAboutToSave();
    saveAs();
}

void PMShell::saveAs()
{
   QFileDialog dlg( this );
   dlg.setNameFilter( "kpov file (*.kpm)" );
   dlg.setAcceptMode( QFileDialog::AcceptSave );

   if( dlg.exec() )
   {
#if QT_VERSION >= 0x050000
       currentUrl = dlg.selectedUrls().at( 0 );
#else
       currentUrl = dlg.selectedFiles().at(0);
#endif
       if( QFileInfo( currentUrl.path() ).completeSuffix().isEmpty() )
          currentUrl.setPath( currentUrl.path() + ".kpm" );

      if( m_pPart->saveFileQt( currentUrl ) )
          setWindowTitle( currentUrl.toString() );
       else
          QMessageBox::warning( this, "Error", tr( "Could not save the file." ) );
   }
}

void PMShell::slotFileRevert()
{
   QUrl url = m_pPart->url();

   if( !url.isEmpty() )
      m_pPart->openFileQt( url );
//   else
//    slotFileNew();
}

void PMShell::slotFilePrint()
{
   //TODO
   //   m_pPart->slotPrint();
}

void PMShell::slotFileNewWindow()
{
   PMShell* shell = new PMShell;
   shell->show();
}

void PMShell::slotFileClose()
{
   if( m_pPart->closeUrl() )
   {
      m_pPart->closeDocument();
      m_pPart->newDocument();
      setWindowTitle();
   }
}

void PMShell::slotShowStatusbar( bool b )
{
   if( !b )
      statusBar()->hide();
   else
      statusBar()->show();
}
/***eticre view-hide Declare with name have "_" at first char***/
/***eticre refresh show lib view hidden not_in_tree***/
void PMShell::slotShowList()
{
    QAction* listAction = mMenuBar->GetAction("Settings", "Show &List");

    if ((listAction != nullptr) && (listAction->isChecked() )) {
        listAction->setText( tr( "Hide &List" ) );
    } else {
        listAction->setText( tr( "Show &List" ) );
    }
    m_pPart->refreshView();
}

void PMShell::slotShowPath()
{
    QAction* pathAction = mMenuBar->GetAction("Settings", "Show &Path");

    if ((pathAction != nullptr) && (pathAction->isChecked() )) {
        pathAction->setText( tr( "Hide &Path" ) );
    } else {
        pathAction = mMenuBar->GetAction("Settings", "Hide &Path");
        pathAction->setText( tr( "Show &Path" ) );
    }

    setWindowTitle( m_pPart->url().toString() );
}

void PMShell::slotSettings()
{
   PMSettingsDialog dlg( m_pPart );
   dlg.exec();
}

void PMShell::updateGUI()
{
   //createGUI( nullptr );
   //createShellGUI( false );
   //createGUI( m_pPart );
}

void PMShell::saveOptions()
{
    QSettings qset;
    QAction*  statusBarAction = mMenuBar->GetAction("Settings", "Show &Status Bar");

    if (statusBarAction != nullptr) {
        qset.setValue( "Appearance/ShowStatusbar", statusBarAction->isChecked() );
        slotShowStatusbar( statusBarAction->isChecked() );
    } else {

    }

    if ( m_pPart ) {
        m_pPart->saveConfig();
    }
}

void PMShell::restoreOptions()
{
    QSettings qset;
    bool      show = true;

    QAction*  statusBarAction = mMenuBar->GetAction("Settings", "Show &Status Bar");

    if (statusBarAction != nullptr) {
        show = qset.value( "Appearance/ShowStatusbar", true ).value<bool>();
        statusBarAction->blockSignals( true );
        statusBarAction->setChecked( show );
        statusBarAction->blockSignals( false );
    } else {

    }
    statusBar()->setVisible(show);
}

void PMShell::setWindowTitle( const QString& caption )
{
    QString tmp = tr ("unknown");

    if(! caption.isEmpty() )
    {
       QAction* pathAction = mMenuBar->GetAction("Settings", "Hide &Path");

       if ((pathAction != nullptr) && (pathAction->isChecked() )) {
            tmp = caption.right( caption.length() - caption.lastIndexOf( '/' ) - 1 );
        } else {
            tmp = caption;
        }
    }

    QMainWindow::setWindowTitle( tmp );
}

void PMShell::statusMsg( const QString& text )
{
   m_pStatusBar->showMessage( text, 5000 );
}

void PMShell::closeEvent( QCloseEvent *event )
{
    shellClose();
}

void PMShell::shellClose()
{
   queryClose();
   m_pPart->deleteContents();
   this->close();

}

bool PMShell::queryClose()
{
   //return m_pPart->closeUrl();
   if( m_pPart->ismodified )
   {
       int i = QMessageBox::question( this, "Save", tr("The document has been modified.\n"
                                                        "Do you want to save your changes?"),
                                       QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel);
       if( i == QMessageBox::Save )
       {
           saveAs();
           return true;
       }
       if( i == QMessageBox::Discard )
       {
           this->close();
           m_pPart->setModified( false );
           return true;
        }

       return false;
   }

   return true;
}

void PMShell::showEvent( QShowEvent* ){
   activateDock();
}

void PMShell::slotModified(bool m)
{
   setWindowTitle( m_pPart->url().toString() );
}

void PMShell::modified(bool m)
{
    if (m_pPart != 0) {
        setWindowTitle( m_pPart->url().toString() );
    }
}

void PMShell::slotControlPointMsg( const QString& msg )
{
   if( msg.isEmpty() )
     statusBarLabel->setText( msg );
   else
     statusBarLabel->setText( QString( " " ) + msg + QString( " " ));
}

bool PMShell::overwriteURL( const QUrl& u )
{
   if( u.isLocalFile() )
   {
      QFileInfo info;
      QString name( u.path() );
      info.setFile( name );

      if( info.exists() )
      {
         QMessageBox m;
         m.setText( "Overwrite file" );
         m.setInformativeText( "A file with this name already exists.\nDo you want to overwrite it?" );
         m.setStandardButtons( QMessageBox::Save | QMessageBox::Cancel );
         if ( m.exec() == QMessageBox::Save )
             return( true );
      }
   }
   return ( false );
}

void PMShell::slotSelectedLayout( QAction* action )
{
   PMViewLayoutManager::theManager()->displayLayout( action->data().toInt(), this );
}

void PMShell::slotSaveViewLayout()
{
   PMSaveViewLayoutDialog dlg( this );
   dlg.show();
}

void PMShell::slotViewsMenuAboutToShow()
{
   QMenu* m = getLayouts();
   PMViewLayoutManager::theManager()->fillPopupMenu( m );
}
