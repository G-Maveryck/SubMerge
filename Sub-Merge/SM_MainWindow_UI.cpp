#include "SM_MainWindow_UI.h"

#include <qgridlayout.h>
#include <qlabel.h>

SM_MainWindow_UI::SM_MainWindow_UI(QMainWindow* MainWindow = (QMainWindow*)nullptr)
	:parentWindow(MainWindow)
		// ui elements init
	,MenuBar(new MainMenu(MainWindow))

	,centralWidget(new QWidget(MainWindow))
	,centralLout(new QGridLayout(centralWidget))
	
	,F_upInfo(new QFrame(MainWindow))
	,F_playing(new QFrame(MainWindow))
	,F_up_Lout(new QGridLayout(F_upInfo))
	,F_playing_Lout(new QGridLayout(F_playing))
{	
		// Configuring the main window
	if (MainWindow->objectName().isEmpty() ) {
		MainWindow->setObjectName("SM_MainWindow");
	}
		//General window settings
	MainWindow->setWindowModality(Qt::ApplicationModal);
	MainWindow->setDockNestingEnabled(true);		//MacOS feature only
	MainWindow->resize(1200, 720);		//tmp Size

	MainWindow->setMenuBar(MenuBar);
	MainWindow->setCentralWidget(centralWidget);
	
	//--------------------------------------------------
		//Begin building UI.

	centralWidget->setLayout(centralLout);

	F_upInfo->setLayout(F_up_Lout);
	F_upInfo->setBaseSize(480, 200);

	F_playing->setLayout(F_playing_Lout);
	F_playing->setBaseSize(480, 800);
	
	centralLout->addWidget(F_upInfo);
	centralLout->addWidget(F_playing);
}

SM_MainWindow_UI::~SM_MainWindow_UI()
{

}

