
#include "PrefDialog.h"

#include <qlabel.h>
#include <qlayout.h>
#include <qpushbutton.h>


PrefDialog::PrefDialog(QWidget* parent = nullptr)
	: QDialog(parent)
	, mainLayout(new QGridLayout(this))
	, b_Reset(new QPushButton(this))
	, b_Accept(new QPushButton(this))
	, b_Exit(new QPushButton(this))
{
	setWindowTitle("Preferences");
	
	b_Reset->setText("Reset to default");

	QSpacerItem* spacer1(new QSpacerItem(100, 30));

	b_Accept->setText("Accept");
	if (b_Accept->isDefault() != true) {
		b_Accept->setDefault(true);
	}

	b_Exit->setText("Cancel");
	

	mainLayout->addWidget(b_Reset, 0, 0);
	mainLayout->addItem(spacer1, 0, 1);
	mainLayout->addWidget(b_Accept, 0, 2);
	mainLayout->addWidget(b_Exit, 0, 3);

	setLayout(mainLayout);


	connect(b_Accept, &QPushButton::clicked, this, &QDialog::accept);
	connect(b_Exit, &QPushButton::clicked, this, &QDialog::reject);

}

PrefDialog::~PrefDialog()
{
}
