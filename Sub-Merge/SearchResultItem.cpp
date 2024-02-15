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

*/

#include "SearchResultItem.h"



SearchResultItem::SearchResultItem()
	: m_SampleRate(-1)
	, m_BitRate(-1)
	, m_ChannelCount(-1)
	, m_Name("")
	, m_Duration(-1)
	, m_Path("")
	, m_Description("")
	, validItem(false)
{

}

SearchResultItem::SearchResultItem(int _samplerate, int _bitrate, int _channels, QString _name, int _duration, QString _path, QString _description)
	: m_SampleRate(_samplerate)
	, m_BitRate(_bitrate)
	, m_ChannelCount(_channels)
	, m_Name(_name)
	, m_Duration(_duration)
	, m_Path(_path)
	, m_Description(_description)
	, validItem(true)
{

}

SearchResultItem::~SearchResultItem()
{
}

bool SearchResultItem::isValid() const
{
	return validItem;
}

QVariant SearchResultItem::atColumn(int columnIndex)
{
		// return the corresponding value to the index in parameter.
		// convenience to acces succesivly all data through a single index and function.

	switch (columnIndex)
	{
	case 0:
		return format();

	case 1:
		return m_ChannelCount;

	case 2:
		return m_Name;

	case 3:
		return m_Duration;

	case 4:
		return m_Path;

	case 5:
		return m_Description;

	default:
		return QVariant();
	}

}



QString SearchResultItem::format() const
	/*
	* Return a QString built with samplerate and bitrate.
	* QString is build with "Arg1 | Arg2" ("%1 | %2"),
	* where Samplerate is passed as Arg1, and bitrate is passed as Arg2
	*/
{
	return QString("%1 | %2")
		.arg(m_SampleRate)
		.arg(m_BitRate);
}
