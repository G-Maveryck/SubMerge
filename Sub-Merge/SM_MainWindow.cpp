/*

*/


#include "SM_MainWindow.h"
#include "DebugMacro.h"

#include <QPushButton>

#include <QFileDialog>
#include <QString>
#include <QMessageBox>

#include <QDebug>




SM_MainWindow::SM_MainWindow(QWidget* parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);

    currentFileInfo = new QFileInfo();
    player = new AudioPlayer(this);


    ui.l_trackName->setText("idle...");

    Timeline = new TimelineFrame(this);
    ui.gridLayout_2->addWidget(Timeline);



        // Connection of the differrents elements
    connect(ui.actionOpen,  SIGNAL(triggered()),    
            this,           SLOT(on_OpenFile_triggered())   );

    connect(ui.B_Play, SIGNAL(clicked()), 
            this,      SLOT(on_PlayButton_Clicked()) );

    connect(ui.B_Pause, SIGNAL(clicked()),
            this,       SLOT(on_PauseButton_Clicked()) );

    connect(ui.s_Volume,SIGNAL(sliderMoved(int)),
            this,       SLOT(on_Volume_changed(int)) );

        //QAction to play or pause the audio with the Space-Bar shortcut
    connect(ui.actionPlay_Pause, SIGNAL(triggered()),
            this, SLOT(on_actionPlayPause_triggered()));


    /* //////////////////////////   */

    connect(player, SIGNAL(durationChanged(int)), 
            this,   SLOT(on_DurationChanged(int)) );

    connect(player, SIGNAL(readingPositionChanged(int)),
            this,   SLOT(on_playerProgress(int))  );

    connect(ui.s_Pitch, SIGNAL(sliderMoved(int)),
            this,   SLOT(on_sliderPitch_moved(int)) );

    connect(ui.s_Time, SIGNAL(sliderMoved(int)),
            this,      SLOT(on_sliderTime_moved(int)) );



    // Error signals handling
        //Decoder error
    connect(player, SIGNAL(audioDecodingError(QAudioDecoder::Error)),
            this,   SLOT(displayAudioDecodingError(QAudioDecoder::Error)) );
        
        //Output error
    connect(player, SIGNAL(audioOutputError(QAudio::Error)),
            this,   SLOT(displayAudioDeviceError(QAudio::Error)) );
    

 
}

SM_MainWindow::~SM_MainWindow()
{

}




// Private Slots definitions
// Menu implementation.

void SM_MainWindow::on_OpenFile_triggered()
{
        // Open Dialog box, and gather information on the selected file.
        // Store them in the "QFileInfo* currentFileInfo" atribute.
    if (player->getStatus() != AudioPlayer::Stopped && player->getStatus() != AudioPlayer::Loading)
    {
        player->stopPlaying();
    }
    else if (player->getStatus() == AudioPlayer::Loading)
    {
        player->cancelDecoding();
    } 
    
    currentFileInfo->setFile(QFileDialog::getOpenFileName(
                                            this, 
                                            tr("Open file"),
                                            "C:/user/",
                                            tr("All Files (*.*)")) );
   
 
        //Set label name on the track name.
    ui.l_trackName->setText(currentFileInfo->fileName());

        // Set the player's source to selected file
    player->decodeFile(currentFileInfo->canonicalFilePath() );

    player->startPlaying();

   
}


void SM_MainWindow::on_PlayButton_Clicked()
{
    if (player->getStatus() != AudioPlayer::Playing)
    {
        switch (player->getStatus())
        {
            case AudioPlayer::Stopped :
            {
                player->startPlaying();
                break;
            }

            case AudioPlayer::Paused :
            {
                player->resumePlaying();
                break;
            }

            default:
                break;
        }

        /*
        if (player->getStatus() == AudioPlayer::Stopped)
        {
            player->startPlaying();
        }
        else
        {
            player->resumePlaying();
        }
        */
    }

    

}

void SM_MainWindow::on_PauseButton_Clicked()
{
    player->pausePlaying();

}



// Volume control
void SM_MainWindow::on_Volume_changed(int volumePos)
{
    // Send the new slider position to the audio player, casted as a percentage,
    // in a Qreal value.

    player->updateVolume( (static_cast<qreal>(volumePos) /100.0f) );

}




// Progression slider implementation
void SM_MainWindow::on_DurationChanged(int duration)
{
        // Used to make the slider fit the duration of each different tracks
        // Minimum is always 0, maximum is set to the total file's duration in millisec.
        // The slider's position then match the playing time in millisec.

    if (duration != -1)
    {
        ui.TimeLine->setMaximum(duration);

        Timeline->on_DurationChange(duration);
    }
    
}

/*
* 
* Old method to move the playing position, with the QMediaPlayer.
* It makes the program crash with the new player...
* 
* 
void SM_MainWindow::on_SliderPosition_moved(int newPosition)
{
        // Called when the user move the slider to select a different time to play.
    player->moveReadingPosition(5000);

}

*/

void SM_MainWindow::on_playerProgress(int position)
{
        // Called when the player progress.
        // Move the slider to have a "TimeLine", or progression bar.

        // If an invalid position if emited, slider go back to 0. 
        // else it follow the reading position.

    if (position == -1)
    {
            // Move the temporary "placeholder" slider
        ui.TimeLine->setMaximum(1);
        ui.TimeLine->setSliderPosition(0);

        Timeline->setPlayHeadPosition(0);

    }
    else
    {
            // Same placeholder slider
        ui.TimeLine->setSliderPosition(position);

        Timeline->setPlayHeadPosition(position);
    }

}



// Prompt an error popup for an audio decoding error
void SM_MainWindow::displayAudioDecodingError(QAudioDecoder::Error error)
{
    QString error_message;

    switch (error) {
    case QAudioDecoder::ResourceError:
        error_message = "File not found";
        break;
    case QAudioDecoder::FormatError:
        error_message = "Format not supported";
        break;
    case QAudioDecoder::AccessDeniedError:
        error_message = "Access denied";
        break;
    case QAudioDecoder::NotSupportedError:
        error_message = "Audio decoding not supported on this platform";
        break;
    default:
        error_message = "Unknown error";
    }

    QMessageBox::critical(this, "Audio decoding error", "Error while decoding audio file:\n" + error_message, QMessageBox::Ok);

}

// Prompt an error popup for an audio device error
void SM_MainWindow::displayAudioDeviceError(QAudio::Error error)
{
    QString error_message;

    switch (error) {
    case QAudio::OpenError:
        error_message = "Unable to open audio device";
        break;
    case QAudio::IOError:
        error_message = "Unable to send data to audio device";
        break;
    case QAudio::FatalError:
        error_message = "Audio device not usable";
        break;
    default:
        error_message = "Unknown error";
    }

    QMessageBox::critical(this, "Audio device error", "Error while accessing audio device:\n" + error_message, QMessageBox::Ok);

}


void SM_MainWindow::on_actionPlayPause_triggered()
{
    switch (player->getStatus())
    {
        case AudioPlayer::Paused :
        {
            player->resumePlaying();
            break;
        }
        case AudioPlayer::Playing :
        {
            player->pausePlaying();
            break;
        }

        default:
            break;
    }

}


        // Pitch and Time controls implementation

    // Pitch slider slot
void SM_MainWindow::on_sliderPitch_moved(int pitchPosition)
{
    player->updatePitch(pitchPosition);

}

    // Time Slider slot
void SM_MainWindow::on_sliderTime_moved(int timePosition)
{

    double _timeRatio = ((double)timePosition / 100);

    player->updateSpeed(_timeRatio);

}

