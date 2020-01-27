#ifndef IMAGE_H
#define IMAGE_H

#include <array>
#include <QImage>
#include "main_window.h"

namespace IMAGE
{
	struct Image
	{
		Image();
		std::array<QImage, CORE::MainWindow::LongHandInterval> m_hourHandImage;
		std::array<QImage, CORE::MainWindow::ShortHandInterval> m_minHandImage;
		std::array<QImage, CORE::MainWindow::ShortHandInterval> m_secHandImage;
	};

	extern const Image image;
}

#endif
