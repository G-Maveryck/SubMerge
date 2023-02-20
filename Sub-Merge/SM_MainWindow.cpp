#include "SM_MainWindow.h"
#include <QPushButton>
#include <QDebug>
#include <QFileDialog>





SM_MainWindow::SM_MainWindow(QWidget* parent)
    : QMainWindow(parent)
    
{
    ui.setupUi(this);
    ui.l_trackName->setText("idle...");

    currentFileInfo = new QFileInfo;


    player = new QMediaPlayer(this);
    audioOutput = new QAudioOutput(player);

    player->setAudioOutput(audioOutput);

    connect(ui.actionOpen,  SIGNAL(triggered()),    this, SLOT(on_OpenFile_triggered()  ));

    connect(ui.B_Play,      SIGNAL(clicked()),      this, SLOT(on_PlayButton_Clicked()  ));
    connect(ui.B_Pause,     SIGNAL(clicked()),      this, SLOT(on_PauseButton_Clicked() ));


}

SM_MainWindow::~SM_MainWindow()
{
    delete currentFileInfo;
}




//Private Slots definitions
void SM_MainWindow::on_OpenFile_triggered()
{
    player->stop();

    currentFileInfo->setFile(QFileDialog::getOpenFileName());

    ui.l_trackName->setText(currentFileInfo->fileName());

    player->setSource(currentFileInfo->absoluteFilePath());
    player->play();

}



void SM_MainWindow::on_PlayButton_Clicked()
{
    player->play();

}

void SM_MainWindow::on_PauseButton_Clicked()
{
    player->pause();

}

void SM_MainWindow::on_SliderPostion_moved()
{



}
