#include <QtGui>
#include <QApplication>
#include <QStylePainter>
#include <QStyleOptionFocusRect>
#include "about_window.h"
#include "image.h"
#include "main_window.h"

CORE::MainWindow::MainWindow(QMainWindow *parent) :
	QMainWindow(parent),
	ScaleLength(240.0),
	ScaleStartPosX(40.0),
	DetailScaleHeight(5.0),
	NormalScaleHeight(10.0),
	HourScalePosY(50.0),
	MinScalePosY(100.0),
	SecScalePosY(150.0),
	HandStartPosX(ScaleStartPosX - 3.0),
	m_backGroundColor(0),
	m_detailScaleColor(0)
{
	readAndSetSettings();

	setWindowTitle(tr("Dance Practice Clock"));
	setStyleSheet(m_backGroundColors[m_backGroundColor]);

	IMAGE::initImage();

	createActions();
	createMenu();
#ifndef QT_DEBUG
	menuBar()->hide();
#endif
	createContextMenu();

	QTimer *timer = new QTimer(this);
	connect(timer, SIGNAL(timeout()), this, SLOT(update()));
	timer->start(1000);  // msec
}

void CORE::MainWindow::createActions()
{
	aboutAction = new QAction(tr("About Dance Practice Clock"), this);
	aboutAction->setShortcut(tr("About The Application"));
//	connect(aboutAction, SIGNAL(triggered()), qApp, SLOT(aboutQt()));
	connect(aboutAction, SIGNAL(triggered()), this, SLOT(about()));
}

void CORE::MainWindow::createMenu()
{
	m_menu = menuBar()->addMenu(tr("Help(&H)"));
	m_menu->addAction(aboutAction);
}

// 右クリックで表示されるメニューの設定
void CORE::MainWindow::createContextMenu()
{
	this->addAction(aboutAction);
	this->setContextMenuPolicy(Qt::ActionsContextMenu);
}

void CORE::MainWindow::about()
{
	ABOUT::AboutWindow aboutWindow;
	aboutWindow.setPosition(this->x(), this->y());
	aboutWindow.exec();
}

void CORE::MainWindow::paintEvent(QPaintEvent *)
{
	QPainter painter(this);

	painter.setRenderHint(QPainter::Antialiasing);
	painter.setPen(QPen(m_detailScaleColors[m_detailScaleColor], 1,
						Qt::SolidLine));

	// 文字盤の数字（書式設定）
	int hourNumber = 0;
	int minNumber = 0;
	int secNumber = 0;
	QFont scaleFont("courier", 9, QFont::Bold);
	painter.setFont(scaleFont);

	for (double xpos = 0; xpos <= ScaleLength; xpos += 30) {
		// 長い目盛り（時）
		painter.drawLine(QPointF(ScaleStartPosX + xpos,
						HourScalePosY),
						QPointF(ScaleStartPosX + xpos,
						HourScalePosY - NormalScaleHeight));

		// 文字盤の数字（1桁か2桁）によりx位置を変える
		int xposAdj;
		if (xpos < 100) {
			xposAdj = 3;
		}
		else {
			xposAdj = 6;
		}
		// 文字盤の数字（時）
		painter.drawText(ScaleStartPosX + xpos - xposAdj,
						HourScalePosY + 12,
						QString::number(hourNumber));
		hourNumber += 3;
	}

	for (double xpos = 0.0; xpos <= ScaleLength; xpos += 10.0) {
		// 短い目盛り（時）
		if ((static_cast<int>(xpos) % 3) != 0) {
			painter.drawLine(QPointF(ScaleStartPosX + xpos,
							HourScalePosY),
							QPointF(ScaleStartPosX + xpos,
							HourScalePosY - DetailScaleHeight));
		}
	}

	for (double xpos = 0.0; xpos <= ScaleLength; xpos += 40.0) {
		// 長い目盛り（分）
		painter.drawLine(QPointF(ScaleStartPosX + xpos,
						MinScalePosY),
						QPointF(ScaleStartPosX + xpos,
						MinScalePosY - NormalScaleHeight));
		// 長い目盛り（秒）
		painter.drawLine(QPointF(ScaleStartPosX + xpos,
						SecScalePosY),
						QPointF(ScaleStartPosX + xpos,
						SecScalePosY - NormalScaleHeight));

		// 文字盤の数字（1桁か2桁）によりx位置を変える
		int xposAdj;
		if (xpos > 36) {
			xposAdj = 6;
		}
		else {
			xposAdj = 3;
		}
		// 文字盤の数字（分）
		painter.drawText(ScaleStartPosX + xpos - xposAdj,
						MinScalePosY + 12,
						QString::number(minNumber));
		minNumber += 10;
		// 文字盤の数字（秒）
		painter.drawText(ScaleStartPosX + xpos - xposAdj,
						SecScalePosY + 12,
						QString::number(secNumber));
		secNumber += 10;

	}

	for (double xpos = 0; xpos <= ScaleLength; xpos += 4) {
		if ((static_cast<int>(xpos) % 40) != 0) {
			// 短い目盛り（分）
			painter.drawLine(QPointF(ScaleStartPosX + xpos,
							MinScalePosY),
							QPointF(ScaleStartPosX + xpos,
							MinScalePosY - DetailScaleHeight));
			// 短い目盛り（秒）
			painter.drawLine(QPointF(ScaleStartPosX + xpos,
							SecScalePosY),
							QPointF(ScaleStartPosX + xpos,
							SecScalePosY - DetailScaleHeight));
		}
	}

	// 現在時刻
	QTime time = QTime::currentTime();

	// 時針
	if (static_cast<int>(time.hour()) % LongHandInterval == 0) {
		painter.drawImage(QRect((HandStartPosX - 7) + time.hour() * 10,
							HourScalePosY - 30, HandWidth, HandHeight),
							IMAGE::image->m_hourHandImage[0]);
	}
	else if (static_cast<int>(time.hour() - 1.0) % LongHandInterval == 0) {
		painter.drawImage(QRect((HandStartPosX - 7) + time.hour() * 10,
							HourScalePosY - 25, HandWidth, HandHeight),
							IMAGE::image->m_hourHandImage[1]);
	}
	else if (static_cast<int>(time.hour() - 2.0) % LongHandInterval == 0) {
		painter.drawImage(QRect((HandStartPosX - 7) + time.hour() * 10,
							HourScalePosY - 25, HandWidth, HandHeight),
							IMAGE::image->m_hourHandImage[2]);
	}

	// 分針
	if (static_cast<int>(time.minute()) % ShortHandInterval == 0) {
		painter.drawImage(QRect(HandStartPosX + time.minute() * 4,
							MinScalePosY - 25, HandWidth, HandHeight),
							IMAGE::image->m_minHandImage[0]);
	}
	else if (static_cast<int>(time.minute() - 1.0) % ShortHandInterval == 0) {
		painter.drawImage(QRect(HandStartPosX + time.minute() * 4,
							MinScalePosY - 25, HandWidth, HandHeight),
							IMAGE::image->m_minHandImage[1]);
	}
	else if (static_cast<int>(time.minute() - 2.0) % ShortHandInterval == 0) {
		painter.drawImage(QRect(HandStartPosX + time.minute() * 4,
							MinScalePosY - 27, HandWidth, HandHeight),
							IMAGE::image->m_minHandImage[2]);
	}
	else if (static_cast<int>(time.minute() - 3.0) % ShortHandInterval == 0) {
		painter.drawImage(QRect(HandStartPosX + time.minute() * 4,
							MinScalePosY - 30, HandWidth, HandHeight),
							IMAGE::image->m_minHandImage[3]);
	}
	else if (static_cast<int>(time.minute() - 4.0) % ShortHandInterval == 0) {
		painter.drawImage(QRect(HandStartPosX + time.minute() * 4,
							MinScalePosY - 30, HandWidth, HandHeight),
							IMAGE::image->m_minHandImage[4]);
	}

	// 秒針
	if (static_cast<int>(time.second()) % ShortHandInterval == 0) {
		painter.drawImage(QRect(HandStartPosX + time.second() * 4,
							SecScalePosY - 24, HandWidth, HandHeight),
							IMAGE::image->m_secHandImage[0]);
	}
	else if (static_cast<int>(time.second() - 1.0) % ShortHandInterval == 0) {
		painter.drawImage(QRect(HandStartPosX + time.second() * 4,
							SecScalePosY - 25, HandWidth, HandHeight),
							IMAGE::image->m_secHandImage[1]);
	}
	else if (static_cast<int>(time.second() - 2.0) % ShortHandInterval == 0) {
		painter.drawImage(QRect(HandStartPosX + time.second() * 4,
							SecScalePosY - 27, HandWidth, HandHeight),
							IMAGE::image->m_secHandImage[2]);
	}
	else if (static_cast<int>(time.second() - 3.0) % ShortHandInterval == 0) {
		painter.drawImage(QRect(HandStartPosX + time.second() * 4,
							SecScalePosY - 30, HandWidth, HandHeight),
							IMAGE::image->m_secHandImage[3]);
	}
	else if (static_cast<int>(time.second() - 4.0) % ShortHandInterval == 0) {
		painter.drawImage(QRect(HandStartPosX + time.second() * 4,
							SecScalePosY - 30, HandWidth, HandHeight),
							IMAGE::image->m_secHandImage[4]);
	}
}

void CORE::MainWindow::keyPressEvent(QKeyEvent *event)
{
	switch (event->key()) {
	case Qt::Key_Escape:
		writeSettings();
		QApplication::quit();
		break;

	case Qt::Key_Up:
		// 目盛りの色を変更する
		if (m_detailScaleColor < m_detailScaleColors.size() - 1) {
			++m_detailScaleColor;
			update();
		}
		else {
			m_detailScaleColor = 0;
			update();
		}
		break;

	case Qt::Key_Down:
		// 目盛りの色を変更する
		if (m_detailScaleColor > 0) {
			--m_detailScaleColor;
			update();
		}
		else {
			m_detailScaleColor = m_detailScaleColors.size() - 1;
			update();
		}
		break;

	case Qt::Key_Right:
		// 背景の色を変更する
		if (m_backGroundColor < m_backGroundColors.size() - 1) {
			++m_backGroundColor;
			setStyleSheet(m_backGroundColors[m_backGroundColor]);
		}
		else {
			m_backGroundColor = 0;
			setStyleSheet(m_backGroundColors[m_backGroundColor]);
		}
		break;

	case Qt::Key_Left:
		// 背景の色を変更する
		if (m_backGroundColor > 0) {
			--m_backGroundColor;
			setStyleSheet(m_backGroundColors[m_backGroundColor]);
		}
		else {
			m_backGroundColor = m_backGroundColors.size() - 1;
			setStyleSheet(m_backGroundColors[m_backGroundColor]);
		}
		break;

	default:
		QWidget::keyPressEvent(event);
		break;
	}
}

void CORE::MainWindow::closeEvent(QCloseEvent *)
{
	writeSettings();
}

// データをファイルに保存する
void CORE::MainWindow::writeSettings()
{
	QSettings settings(CORE::OrgName, CORE::AppName);
	settings.setValue("geometry", geometry());
	settings.setValue("backGroundColor", m_backGroundColor);
	settings.setValue("detailScaleColor", m_detailScaleColor);
}

// ファイルを読み込んでアプリケーションに設定する
void CORE::MainWindow::readAndSetSettings()
{
	// ロード
	QSettings settings(CORE::OrgName, CORE::AppName);

	QRect rect =
		settings.value("geometry",
		QRect(0, 0, WindowWidth, WindowHeight)).toRect();

	m_backGroundColor = settings.value("backGroundColor", 0).toUInt();
	m_detailScaleColor = settings.value("detailScaleColor", 0).toUInt();

	if (m_backGroundColor >= m_backGroundColors.size()) {
		m_backGroundColor = 0;
	}
	if (m_detailScaleColor >= m_detailScaleColors.size()) {
		m_detailScaleColor = 0;
	}

	// ロードしたデータを利用してアプリケーションを設定する
	// ロードした幅と高さを既定値で上書きする
	rect.setWidth(WindowWidth);
	rect.setHeight(WindowHeight);

	move(rect.topLeft());
	setFixedSize(rect.size());
}
