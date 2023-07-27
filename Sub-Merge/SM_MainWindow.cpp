/* --------------------------------------------------------------------------------------
* Author : Gabriel Wulveryck.
* Year : 2023
* for any information, please contact : wulveryck.gabriel@gmail.com
*
* This file is a part of the SubMerge project.
*
* SubMerge is a free software, and is published under the terms of the GNU General Public Licence, version 3.
* You can redistribute it and/or modify it under the terms of the GNU General Public License
* as published by the Free Software Foundation; either version 3 of the License,
* or (at your option) any later version.
* You should have recived a copy of the licence with the project.
*
* SubMerge is distributed as a contribution to the open-source and free software community,
* in the hope it'll be usefull.
* SubMerge is distributed without ANY WARRANTY, without even the implied warranty
* of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
*
* See the GNU General Public License for more details.
*
*-------------------------------------------------------------------------------------- */

/*
    Main Window class implementation.
*/

#include "SM_MainWindow.h"
#include "DebugMacro.h"
#include "Audio_player.h"
#include "TimelineFrame.h"

#include <qobject.h>
#include <QPushButton>

#include <QFileDialog>
#include <QString>
#include <QMessageBox>

#include <QDebug>


SM_MainWindow::SM_MainWindow(QWidget* parent) :
    QMainWindow(parent),
    m_currentFile(nullptr),
    FocusFile(new FocusedFile(this)),
    player(new AudioPlayer(this)),
    Timeline(new TimelineFrame(this))
{
    ui.setupUi(this);

    setWindowFlags(windowFlags() | Qt::CustomizeWindowHint |
        Qt::WindowMinimizeButtonHint |
        Qt::WindowMaximizeButtonHint |
        Qt::WindowCloseButtonHint);

    ui.l_trackName->setText("idle...");
    ui.gridLayout_2->addWidget(Timeline);

        // Connection of the differrents UI elements
    connect(ui.actionOpen,  SIGNAL(triggered()),    
            this,           SLOT(on_OpenFile_triggered())   );

    connect(ui.B_Play, SIGNAL(clicked()), 
            this,      SLOT(on_PlayButton_Clicked()) );

    connect(ui.B_Pause, SIGNAL(clicked()),
            this,       SLOT(on_PauseButton_Clicked()) );

    connect(ui.s_Volume,SIGNAL(sliderMoved(int)),
            this,       SLOT(on_Volume_changed(int)) );

    connect(ui.s_Pitch, &QAbstractSlider::sliderMoved,
            player, &AudioPlayer::updatePitch);

    connect(ui.s_Time, SIGNAL(sliderMoved(int)),
        this, SLOT(on_sliderTime_moved(int)));


        //QAction to play or pause the audio with the Space-Bar shortcut
    connect(ui.actionPlay_Pause, SIGNAL(triggered()),
            this, SLOT(on_actionPlayPause_triggered()));


        // Signals from the audio player
    connect(player, SIGNAL(durationChanged(int)), 
            this,   SLOT(on_DurationChanged(int)) );

    connect(player, SIGNAL(readingPositionChanged(int)),
            this,   SLOT(on_playerProgress(int))  );

    connect(Timeline, &TimelineFrame::userChangedPosition,
            player, &AudioPlayer::moveReadingPosition);

    // Error signals handling
        // Decoder error
    connect(player, SIGNAL(audioDecodingError(QAudioDecoder::Error)),
            this,   SLOT(displayAudioDecodingError(QAudioDecoder::Error)) );
        
        // Output error
    connect(player, SIGNAL(audioOutputError(QAudio::Error)),
            this,   SLOT(displayAudioDeviceError(QAudio::Error)) );
    
}

SM_MainWindow::~SM_MainWindow()
{
    delete m_currentFile;
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
    
    if (m_currentFile != nullptr)
    {
        delete m_currentFile;
    }
    m_currentFile = new QFileInfo(QFileDialog::getOpenFileName(
        this,
        tr("Open file"),
        tr("D:/"),
        tr("All Files (*.*)")) );
  
    FocusFile->setNewFile(m_currentFile->canonicalFilePath());
    
    Timeline->setNewProperties(FocusFile->getAudioProperties()->channels());

        //Set label name on the track name.
    ui.l_trackName->setText(m_currentFile->fileName());
   
        // Set the player's source to selected file
    player->decodeFile(m_currentFile->canonicalFilePath() );
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
        Timeline->on_DurationChanged(duration);
    }
    
}

// Space bar triggered
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

    // Time Slider slot
void SM_MainWindow::on_sliderTime_moved(int timePosition)
{

    double _timeRatio = ((double)timePosition / 100);

    player->updateSpeed(_timeRatio);

}

void SM_MainWindow::on_playerProgress(int position)
{
        // Called when the player progress.
        // Move the slider to have a "TimeLine", or progression bar.

    if (position == -1)
    {
            // Reset the playhead to 0 when an inavlid position is sent.
            // Typically hapend when the audio is over.
        Timeline->setPlayHeadPosition(0);
    }
    else
    {
        Timeline->setPlayHeadPosition(position);
    }

}

void SM_MainWindow::on_newFileSelected()
{
    
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



