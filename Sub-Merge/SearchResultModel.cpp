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


#include "SearchResultModel.h"
#include "DebugMacro.h"

#include <qabstractitemmodel.h>
#include <qvariant.h>
#include <qstring.h>


SearchResultModel::SearchResultModel(QObject* parent = (QObject*)nullptr)
	: QAbstractTableModel(parent)
	, m_results(0)
{
	m_results.push_back(
		new SearchResultItem(48, 16, 2, "First File", 1542, "D:/", "Nice audio, very textured")
	);
}

SearchResultModel::~SearchResultModel()
{
	resetResults();
}



QVariant SearchResultModel::headerData(int section, Qt::Orientation orientation, int role) const
{
	if (role == Qt::DisplayRole && orientation == Qt::Horizontal) {
		switch (section) {
		case 0:
			return QString("Format");
		case 1:
			return QString("Channels");
		case 2:
			return QString("Name");
		case 3:
			return QString("Duration");
		case 4:
			return QString("Path");
		case 5:
			return QString("Description");
		}
	} // end if

	return QVariant();
}




bool SearchResultModel::insertRow(int row, int count, const QModelIndex& parent)
{
	return false;
}

bool SearchResultModel::insertColumns(int column, int count, const QModelIndex& parent)
{
	return false;
}


int SearchResultModel::rowCount(const QModelIndex& parent) const
{
	return m_results.size();
}

int SearchResultModel::columnCount(const QModelIndex& parent) const
{
	return 6;
}


QVariant SearchResultModel::data(const QModelIndex& index, int role) const
{
	// method to read data from the cells.
	// store the current index
	const int ROW(index.row());
	const int COL(index.column());
	
	if (role == Qt::DisplayRole) {
		return m_results.at(ROW)->getData(COL);
	}

	return QVariant();
}

bool SearchResultModel::setData(const QModelIndex& index, const QVariant& value, int role)
{

	return false;
}

inline void SearchResultModel::resetResults()
{
	QLOG("results before clear() : " << m_results.size());

	for (int i = 0; i < m_results.size(); i++)
	{
		delete m_results.at(i);
	}
	m_results.clear();

	QLOG("results after clear() : " << m_results.size());
}


