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

#include "ProcessThread.h"
#include <qurl.h>
#include <qaudiobuffer.h>
#include "DebugMacro.h"

ProcessThread::ProcessThread(QObject* parent) :
		QThread(parent)
		, m_decoder(new QAudioDecoder(this))
		, m_ThreadStatus(ProcessStatus::Empty)
		//m_targetFormat()
{
	/*
	m_targetFormat.setChannelCount(2);
	m_targetFormat.setChannelConfig(QAudioFormat::ChannelConfigStereo);
	m_targetFormat.setSampleRate(44000);
	m_targetFormat.setSampleFormat(QAudioFormat::SampleFormat::Int32);

	m_decoder->setAudioFormat(m_targetFormat);
	*/
}

ProcessThread::~ProcessThread()
{
}



void ProcessThread::decodeFile(QString fileName)
{
	if (m_ThreadStatus != ProcessStatus::Decoding)
	{
		m_decoder->setSource(QUrl::fromLocalFile(fileName) );

		m_ThreadStatus = Decoding;
		connect(m_decoder, &QAudioDecoder::bufferReady,
				this, &ProcessThread::processDecodedBuffer );

		m_decoder->start();
	}
}

ProcessThread::ProcessStatus ProcessThread::getProcessingStatus()
{
	return m_ThreadStatus;
}

void ProcessThread::abortDecoding()
{
	if (m_ThreadStatus != Decoding)
	{
		return;
	}
	m_decoder->stop();
	disconnect(	m_decoder, &QAudioDecoder::bufferReady, 
				this, &ProcessThread::processDecodedBuffer);

	m_ThreadStatus = Empty;
}

void ProcessThread::processDecodedBuffer()
{
	FOR_DEBUG(
		static int callNmb(0);
		QLOG("Buffer Received #" << callNmb);
		callNmb++;
	)

	QAudioBuffer currentBuffer = m_decoder->read();
	
}

/*
std::vector<QAudioBuffer> ProcessThread::deInterleavedBuffer(const QAudioBuffer& interleavedBuffer)
{
	int channelsNmb = interleavedBuffer.format().channelCount();
	int channelsOffset = interleavedBuffer.format().bytesPerSample();
	int frameCount = interleavedBuffer.frameCount();

	std::vector<QByteArray> tmp_Channels(channelsNmb);

	for (int i = 0; i < channelsNmb; i++)
	{
		for (int j = 0; j < frameCount; j+=channelsOffset)
		{
			
		}


	}


	std::vector<QAudioBuffer> splittedBuffers(channelsNmb, QAudioBuffer(QByteArray()));
	// return std::vector<QAudioBuffer>();
}
*/