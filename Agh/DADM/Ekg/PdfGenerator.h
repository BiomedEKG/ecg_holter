#ifndef _PDF_GENERATOR
#define	_PDF_GENERATOR
#include <QtPrintSupport\qprinter.h>
#include <QtCore\qrect.h>
#include <QtCore\qpoint.h>
#include <QtGui\qpainter.h>
#include <qwt_plot_renderer.h>
#include <qwt_plot.h>
class PdfGenerator
{
private:
	//Static members
	static const int leftRightMargin = 25;//lewy & prawy margines
	static const int topBottomMargin = 30;//górny & dolny margines
	static const int gap = 25; //odstêp pomiêdzy kolejnymi elementami
	static const int pageWidth = 793; //Rozmiar strony A4 w punktach
	static const int pageHeight = 1123;
	static const int cellHeight = 20; //wysokoœc komórki tabelki
	QPrinter pdfPrinter;
	QPainter docCreator;
	QwtPlotRenderer plotInserter;
	QPoint currentPos;
	int pageCounter;
public:
	enum directionOfCursorMove {toSide, toBottom};
private:
	QString getTime(void);
	PdfGenerator(const PdfGenerator &p);
	bool writePageNumber(int nr);
protected:
	bool createNewPage();
	bool movePosition(int x, int y);
	bool isTooBig(int objectHeight);
public:
	explicit PdfGenerator(QString path2file);
	~PdfGenerator(void);
	bool addHeader(QString title);
	bool addPlot(QwtPlot* ptrPlot, bool strechToPageWidth = false);
	bool addPlots(QwtPlot* ptrPlotLeft, QwtPlot* ptrPlotRight);
	bool addPlot(QwtPlot* ptrPlot, int plotWidth, directionOfCursorMove dir);
	bool addSubtitle(QString title);
	bool addTable(QStringList data, int colsNr, int width, directionOfCursorMove dir);
	
};

#endif //_PDF_GENERATOR