#include "PrefDialog.h"
#include<qlabel.h>
#include<qlayout.h>


PrefDialog::PrefDialog(QWidget* parent = nullptr)
	:QDialog(parent)
{
	setWindowTitle("Preferences");
	
	QLabel* labeltest = new QLabel("Set you preferences.", this);
	QVBoxLayout* Vlayout = new QVBoxLayout(this);
	setLayout(Vlayout);
	Vlayout->addWidget(labeltest);
}

PrefDialog::~PrefDialog()
{
}
