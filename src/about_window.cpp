#include "about_window.h"
#include "image.h"
#include <QVBoxLayout>

ABOUT::AboutWindow::AboutWindow(QWidget *parent) :
	QDialog(parent)
{
	m_tabWidget = new QTabWidget;
	m_tabWidget->addTab(new DancePracticeClockTab(), tr("Dance Practice Clock"));
	m_tabWidget->addTab(new UsageTab(), tr("Usage"));
	m_tabWidget->addTab(new LicenseTab(), tr("License"));
	m_tabWidget->addTab(new DeveloperTab(), tr("Developer"));

	m_okButton = new QPushButton(tr("ok"), this);
//	m_okButton->setAutoDefault(true);
	connect(m_okButton, &QPushButton::clicked, this, &QDialog::accept);

	// レイアウト
	QVBoxLayout *mainLayout = new QVBoxLayout;
	mainLayout->addWidget(m_tabWidget);
	QHBoxLayout *buttonLayout = new QHBoxLayout;
	buttonLayout->addWidget(m_okButton, 0, Qt::AlignRight);
	mainLayout->addLayout(buttonLayout);
	setLayout(mainLayout);

	setFixedSize(WindowWidth, WindowHeight);

	setWindowTitle(tr("About Dance Practice Clock"));
}

void ABOUT::AboutWindow::setPosition(const int x, const int y)
{
	setGeometry(x, y, this->width(), this->height());
}

ABOUT::DancePracticeClockTab::DancePracticeClockTab(QWidget *parent) :
	QWidget(parent)
{
	m_appImageLabel = new QLabel();
//	m_appImageLabel->setFixedWidth(200);
//	m_appImageLabel->setFixedHeight(40);
	m_appImageLabel->setAlignment(Qt::AlignHCenter | Qt::AlignTop);
	m_appImageLabel->setMargin(10);

	QPixmap *appImagePimap =
		new QPixmap(QPixmap::fromImage(IMAGE::image.m_hourHandImage[0]));
	m_appImageLabel->setPixmap(*appImagePimap);

	QString description(
		"Dance Practice Clock\n\n"
		"Clock expressed by dance. \n\n"
		"Version 20200124-21\n\n"

		"Copyright 2020 TORIUMI Mitsugu and contributors. License GPLv3: GNU GPL version 3.\n"
		"This is free software; see the source for copying conditions. There is NO warranty;\n"			"not even for MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.\n\n"

		"Dance Practice Clock is Open Source Software released under the GNU General Public License.\n"
	);
	m_descriptionLabel = new QLabel(description);
	m_descriptionLabel->setAlignment(Qt::AlignHCenter | Qt::AlignTop);

	// レイアウト
	QVBoxLayout *mainLayout = new QVBoxLayout;
	mainLayout->setAlignment(Qt::AlignCenter | Qt::AlignTop);
	mainLayout->addWidget(m_appImageLabel);
	mainLayout->addWidget(m_descriptionLabel);
	setLayout(mainLayout);
}

ABOUT::DeveloperTab::DeveloperTab(QWidget *parent) :
	QWidget(parent)
{
	QString auther("TORIUMI Mitsugu  <toriringo@gmail.com>");

	m_developerPlainTextEdit = new QPlainTextEdit(auther);
//	m_developerPlainTextEdit->setAlignment(Qt::AlignHCenter | Qt::AlignTop);
	m_developerPlainTextEdit->setReadOnly(true);

	QVBoxLayout *mainLayout = new QVBoxLayout;
	mainLayout->addWidget(m_developerPlainTextEdit);
	setLayout(mainLayout);
}

ABOUT::LicenseTab::LicenseTab(QWidget *parent) :
	QWidget(parent)
{
	QString licenseArticle(
		"Dance Practice Clock is distributed under the GNU GPL version 3. There are no restrictions on its use. There are significant restrictions on its distribution.\n\n"

		"Parts of Dance Practice Clock can be built and distributed as libraries. These parts are still covered by the GPL, and NOT by the Lesser General Public License or any other license.\n\n"

		"If you create a combined work using all or part of Dance Practice Clock, then your combined work must be released under a license compatible with the GPL.\n\n"

		"...and don't get us started on trademarks.\n\n"

		"The full text of the GNU GPL may be viewed in\n"
		"https://www.gnu.org/licenses/gpl-3.0.html"
	);

	m_licensePlainTextEdit = new QPlainTextEdit(licenseArticle);
	m_licensePlainTextEdit->setReadOnly(true);
	m_licensePlainTextEdit->setLineWrapMode(QPlainTextEdit::WidgetWidth);

	QVBoxLayout *mainLayout = new QVBoxLayout;
	mainLayout->addWidget(m_licensePlainTextEdit);
	setLayout(mainLayout);
}

ABOUT::UsageTab::UsageTab(QWidget *parent) :
	QWidget(parent)
{
	QString usageText(
		"Changing Background Color:  Left Arrow and Right Arrow keys\n"
		"Changing Clock Hands Color:  Up Arrow and Down Arrow keys\n"
	);

	m_usagePlainTextEdit = new QPlainTextEdit(usageText);
	m_usagePlainTextEdit->setReadOnly(true);

	QVBoxLayout *mainLayout = new QVBoxLayout;
	mainLayout->addWidget(m_usagePlainTextEdit);
	setLayout(mainLayout);
}
