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

*/

#ifndef PROCESS_THREAD_H
#define PROCESS_THREAD_H

#include <qobject.h>
#include <qthread.h>
#include <qaudiobuffer.h>
#include <qaudiodecoder.h>
#include <qaudioformat.h>

#include <vector> 

class ProcessThread :
    public QThread
{
    Q_OBJECT

public:
    enum ProcessStatus
    {
        Empty,
        Decoding,
        Finished
    };

    ProcessThread(QObject* parent = nullptr);
    ~ProcessThread();

    // void setProperties(int ChannelCount, int sampleRate, QAudioFormat::ChannelConfig ChannelConfig);
    void decodeFile(QString fileName);
    ProcessStatus getProcessingStatus();
    void abortDecoding();

protected:
    void processDecodedBuffer();

private:
    QAudioDecoder* m_decoder;
    QAudioFormat m_targetFormat;

    ProcessStatus m_ThreadStatus;

    std::vector<std::vector<int>>* m_bufferPeakValues;

signals:
    void newDataAvailable();

};


#endif