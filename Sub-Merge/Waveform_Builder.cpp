#include "Waveform_Builder.h"


WaveformBuilder::WaveformBuilder(QObject* parent) :
		QThread(parent)
{


}

WaveformBuilder::~WaveformBuilder()
{
	exit();
}