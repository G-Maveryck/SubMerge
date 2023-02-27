#ifndef SUBMERGE_H
#define SUBMERGE_H



#include <QtWidgets/QMainWindow>
#include "ui_SubMerge.h"

#include <QtMultimedia/QMediaPlayer>
#include <QtMultimedia/QAudioOutput>
#include <QFileInfo>


class SM_MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    SM_MainWindow(QWidget *parent = nullptr);    // Constructeur
    ~SM_MainWindow();                            // Destructeur


private slots:
        // Mediaplayer control
    void on_PlayButton_Clicked();
    void on_PauseButton_Clicked();
    void on_Volume_changed(int volumePos);
    void on_DurationChanged(qint64 duration);
   

        // Menu controls
    void on_OpenFile_triggered();

        // Timeline controls
    void on_SliderPosition_moved(qint64 newPosition);
    void on_playerProgress(qint64 position);


private:
    Ui::SubMergeClass ui;

    QFileInfo* currentFileInfo;

    QMediaPlayer* player;
    QAudioOutput* audioOutput;

 

};



#endif // !SUBMERGE_H