/* --------------------------------------------------------------------------------------
* Author : Gabriel Wulveryck.
* Year : 2024
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
	This class is the implementation of the "data" that will be stored in the model.
	It is understandable as "a row" of the TableResult.

*/


#ifndef SEARCH_RESULT_ITEM_H
#define SEARCH_RESULT_ITEM_H


#include <qstring.h>
#include <qvariant.h>


class SearchResultItem
{
public:
	SearchResultItem();
	SearchResultItem(int _samplerate
		, int _bitrate
		, int _channels
		, QString _name
		, int _duration
		, QString _path
		, QString _description
		);
	~SearchResultItem();

	QVariant getData(int index);	// Used to acces each properties with an "index". Corresponding to the "column"


protected:
	QString format() const;		// Helper function to combine sample rate and bitrate into a single string


private:
	// Properties section
	/*0*/ int m_SampleRate;		// Samples per second (48kHz, 96kHz, etc...)
	/*0*/ int m_BitRate;			// Bits per samples
	/*1*/ int m_ChannelCount;		// Number of audio channels
	/*2*/ QString m_Name;			// Name of the file
	/*3*/ int m_Duration;			// Duration of the audio in milisec
	/*4*/ QString m_Path;			// File path
	/*5*/ QString m_Description;	// Description of the audio, embbed in the file (aka "Tags")

};


#endif // !SEARCH_RESULT_ITEML_H