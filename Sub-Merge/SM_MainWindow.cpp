#include "SM_MainWindow.h"
#include <QPushButton>
#include <QDebug>
#include <QFileDialog>





SM_MainWindow::SM_MainWindow(QWidget* parent)
    : QMainWindow(parent),
    m_currentFilePath("./"),
    m_currentFileName("blank")
{
    ui.setupUi(this);

    player = new QMediaPlayer(this);
    audioOutput = new QAudioOutput(player);

    player->setAudioOutput(audioOutput);


    connect(ui.actionOpen,  SIGNAL(triggered()),    this, SLOT(on_OpenFile_triggered()  ));

    connect(ui.B_Play,      SIGNAL(clicked()),      this, SLOT(on_PlayButton_Clicked()  ));
    connect(ui.B_Pause,     SIGNAL(clicked()),      this, SLOT(on_PauseButton_Clicked() ));
}

SM_MainWindow::~SM_MainWindow()
{
    
}




//Private Slots definitions
void SM_MainWindow::on_OpenFile_triggered()
{
    QFileInfo* fileInfo = new QFileInfo(QFileDialog::getOpenFileName());
    
    // m_currentFileName = QFileDialog::getOpenFileName();
    m_currentFilePath = fileInfo->absoluteFilePath();
    m_currentFileName = fileInfo->fileName();

    ui.l_trackName->setText(m_currentFileName);

    player->setSource(m_currentFilePath);
    player->play();

    delete fileInfo;
}



void SM_MainWindow::on_PlayButton_Clicked()
{
    player->play();

}

void SM_MainWindow::on_PauseButton_Clicked()
{
    player->pause();

}

void SM_MainWindow::on_Slider_Postion_moved()
{



}
