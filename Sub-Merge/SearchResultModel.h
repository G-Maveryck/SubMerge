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
*	This class implement a model data to store and organise the search results.
*	Results will then be displayed by the "QTableView TableResults", in the view part.
*
*	Results are stored in a list, each item of the list correspond to a row.
*	Each columns are stored in in the Item, and accessed through item.getData(Column)
*/

#ifndef SEARCH_RESULTS_MODEL_H
#define SEARCH_RESULTS_MODEL_H


#include <qabstractitemmodel.h>
#include <qvariant.h>
#include <qstring.h>
#include <qlist.h>

#include <list>

#include "SearchResultItem.h"


class SearchResultModel : public QAbstractTableModel
{
	Q_OBJECT

public:
	SearchResultModel(QObject* parent);
	~SearchResultModel();

	QVariant headerData(int section, Qt::Orientation orientation, int role) const;

	int rowCount(const QModelIndex& parent = QModelIndex()) const override;
	int columnCount(const QModelIndex& parent = QModelIndex()) const override;
	
	QVariant data(const QModelIndex& index, int role) const override;
	void addResult(SearchResultItem* _result);

	// virtual bool insertRow(int row, int count, const QModelIndex& parent = QModelIndex());
	// virtual bool insertColumns(int column, int count, const QModelIndex& parent = QModelIndex());
	
	// bool setData(const QModelIndex& index, const QVariant& value, int role = Qt::EditRole) override;


protected:
	inline void resetResults();


private:
	QList<SearchResultItem*> m_resultsItems;	// Store all the ResultsItems in a list. Each Item correspond to a Row of the table.

};


#endif // !SEARCH_RESULTS_MODEL_H