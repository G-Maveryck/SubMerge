#ifndef PREF_DIALOG_H
#define PREF_DIALOG_H


#include <qdialog.h>
#include <qgridlayout.h>
#include <qpushbutton.h>


class PrefDialog : public QDialog
{
	Q_OBJECT

public:
	PrefDialog(QWidget* parent);
	~PrefDialog();

private:
	QGridLayout* mainLayout;

	QPushButton* b_Accept;
	QPushButton* b_Exit;

};


#endif // !PREF_DIALOG_H