#ifndef ABOUT_WINDOW_H
#define ABOUT_WINDOW_H

#include <QDialog>
#include <QLabel>
#include <QPlainTextEdit>
#include <QPushButton>
#include <QTabWidget>

namespace ABOUT
{
	// アプリケーションの説明をするタブ
	class DancePracticeClockTab : public QWidget
	{
		Q_OBJECT
	public:
		DancePracticeClockTab(QWidget *parent = nullptr);

	private:
		QLabel *m_appImageLabel;
		QLabel *m_descriptionLabel;
	};

	// 開発者を列挙するタブ
	class DeveloperTab : public QWidget
	{
		Q_OBJECT
	public:
		DeveloperTab(QWidget *parent = nullptr);

	private:
		QPlainTextEdit *m_developerPlainTextEdit;
	};

	// ライセンスを明記するタブ
	class LicenseTab : public QWidget
	{
		Q_OBJECT
	public:
		LicenseTab(QWidget *parent = nullptr);

	private:
		QPlainTextEdit *m_licensePlainTextEdit;
	};

	// 使い方のタブ
	class UsageTab : public QWidget
	{
		Q_OBJECT
	public:
		UsageTab(QWidget *parent = nullptr);

	private:
		QPlainTextEdit *m_usagePlainTextEdit;
	};

	class AboutWindow : public QDialog
	{
		Q_OBJECT
	public:
		AboutWindow(QWidget *parent = nullptr);
		void setPosition(const int x, const int y);

	private:
		enum
		{
			WindowWidth = 600,
			WindowHeight = 360
		};

		QTabWidget *m_tabWidget;
		QPushButton *m_okButton;
	};
}

#endif
