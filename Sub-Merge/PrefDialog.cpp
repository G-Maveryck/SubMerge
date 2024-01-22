#include "PrefDialog.h"
#include<qlabel.h>
#include<qlayout.h>


PrefDialog::PrefDialog(QWidget* parent = nullptr)
	: QDialog(parent)
	, mainLayout(new QGridLayout(this))
	, b_Accept(new QPushButton(this))
	, b_Exit(new QPushButton(this))
{
	setWindowTitle("Preferences");
	
	b_Accept->setText("Accept");
	if (! b_Accept->isDefault()) {
		b_Accept->setDefault(true);
	}

	b_Exit->setText("Cancel");
	
	mainLayout->addWidget(b_Accept);
	mainLayout->addWidget(b_Exit);

	setLayout(mainLayout);


	connect(b_Accept, &QPushButton::clicked, this, &QDialog::accept);
	connect(b_Exit, &QPushButton::clicked, this, &QDialog::reject);

}

PrefDialog::~PrefDialog()
{
}
