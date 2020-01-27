#ifndef MAIN_WINDOW_H
#define MAIN_WINDOW_H

#include <QAction>
#include <QMainWindow>
#include <QMenu>
#include <QMenuBar>
#include <QSettings>
#include <QWidget>

namespace CORE
{
	const QString OrgName = "toriminho";             // 組織名
	const QString AppName = "dance_practice_clock";  // アプリケーション名

	class MainWindow : public QMainWindow
	{
		Q_OBJECT

	public:
		MainWindow(QMainWindow *parent = 0);
		enum
		{
			HandWidth = 20,        // 針の画像の幅
			HandHeight = 20,       // 針の画像の高さ
			LongHandInterval = 3,  // 針の画像（時）の周期
			ShortHandInterval = 5  // 針の画像（分秒）の周期
		};

	protected:
		virtual void paintEvent(QPaintEvent *event) override;
		virtual void keyPressEvent(QKeyEvent *event) override;
		virtual void closeEvent(QCloseEvent *event) override;

	private slots:
		void about();

	private:
		enum
		{
			WindowWidth = 320,
			WindowHeight = 200
		};

		//メニュー
		QMenu *m_menu;
		void createMenu();

		// コンテキストメニュー
		void createContextMenu();

		// アクション
		void createActions();
		QAction *aboutAction;

		const double ScaleLength;        // 目盛りの全長
		const double ScaleStartPosX;     // 目盛りの開始位置X
		const double DetailScaleHeight;  // 短い目盛りの高さ
		const double NormalScaleHeight;  // 長い目盛りの高さ
		const double HourScalePosY;      // 時間目盛りの位置Y
		const double MinScalePosY;       // 分目盛りの位置Y
		const double SecScalePosY;       // 秒目盛りの位置Y

		const double HandStartPosX;      // 針の画像の開始位置X

		void writeSettings();
		void readAndSetSettings();

		// 背景の色セット
		const std::array<QString, 4> m_backGroundColors =
		{
			"background-color: rgb(220, 220, 220)",
			"background-color: rgb(60, 60, 60)",
			"background-color: rgb(0, 128, 128)",
			"background-color: rgb(240, 128, 128)"
		};
		unsigned int m_backGroundColor;  // 現在の背景の色

		// 目盛りの色セット
		const std::array<QColor, 2> m_detailScaleColors =
		{
			QColor(10, 10, 10),
			QColor(245, 245, 245)
		};
		unsigned int m_detailScaleColor;  // 現在の目盛りの色
	};
}

#endif
