#ifndef WAVEFORM_BUILDER_H
#define WAVEFORM_BUILDER_H

#include <qobject.h>
#include <qthread.h>

class WaveformBuilder :
    public QThread
{
    Q_OBJECT

public:
    WaveformBuilder(QObject* parent = nullptr);
    virtual ~WaveformBuilder();


};


#endif // !WAVEFORM_BUILDER_H