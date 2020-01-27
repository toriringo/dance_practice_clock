#include "image.h"

namespace IMAGE
{
	const Image image;
}

IMAGE::Image::Image()
{
	// ダンサーのデータを画像ファイルで初期化する
	for (int i = 0; i < CORE::MainWindow::LongHandInterval; ++i) {
		QString hourHand = ":/images/man_hand" + QString::number(i + 1) + ".png";
		m_hourHandImage[i].load(hourHand);
	}
	for (int i = 0; i < CORE::MainWindow::ShortHandInterval; ++i) {
		QString minHand = ":/images/girl_hand" + QString::number(i + 1) + ".png";
		QString secHand = ":/images/boy_hand" + QString::number(i + 1) + ".png";
		m_minHandImage[i].load(minHand);
		m_secHandImage[i].load(secHand);
	}
}
