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
    audioOutput->setVolume(80);



    connect(ui.actionOpen,  SIGNAL(triggered()),    this, SLOT(on_OpenFile_triggered()  ));

    connect(ui.B_Play,  SIGNAL(clicked()),      this, SLOT(on_PlayButton_Clicked()) );
    connect(ui.B_Pause, SIGNAL(clicked()),      this, SLOT(on_PauseButton_Clicked()));
    connect(ui.s_Volume,SIGNAL(valueChanged(int)), this, SLOT(on_Volume_changed(int)) );

    connect(player,     SIGNAL(durationChanged(qint64)), this, SLOT(on_DurationChanged(qint64)) );
    connect(player,     SIGNAL(positionChanged(qint64)), this, SLOT(on_playerProgress(qint64)));

    connect(ui.TimeLine, SIGNAL(valueChanged(qint64 value)), this, SLOT(on_SliderPosition_moved(qint64 value
    )));
}

SM_MainWindow::~SM_MainWindow()
{
    delete currentFileInfo;
}




// Private Slots definitions
// Menu implementation.

void SM_MainWindow::on_OpenFile_triggered()
{
        // Open Dialog box, and gather information on the selected file.
        // Store them in the "QFileInfo* currentFileInfo" atribute.
    currentFileInfo->setFile(QFileDialog::getOpenFileName());
    player->stop();

        //Set label name on the track name.
    ui.l_trackName->setText(currentFileInfo->fileName());

        // Set the player's source on this selected file
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



// Volume control
void SM_MainWindow::on_Volume_changed(int volumePos)
{
    audioOutput->setVolume(volumePos);

}




// "Timeline" slider implementation

void SM_MainWindow::on_DurationChanged(qint64 duration)
{
        // Used to make the slider fit the duration of each different tracks
    ui.TimeLine->setMaximum(duration);
}

void SM_MainWindow::on_SliderPosition_moved(qint64 newPosition)
{
        // Called when the user move the slider to select a different time to play.
    player->setPosition(newPosition);

}

void SM_MainWindow::on_playerProgress(qint64 position)
{
        // Called when the player progress.
        // Move the slider to have a "TimeLine", or progression bar.
    ui.TimeLine->setSliderPosition(position);

}