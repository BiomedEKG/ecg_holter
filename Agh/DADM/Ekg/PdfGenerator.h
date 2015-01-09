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
	static const int leftRightMargin = 25;//lewy & prawy margines
	static const int topBottomMargin = 30;//górny & dolny margines
	static const int gap = 25; //odstêp pomiêdzy kolejnymi elementami
	static const int pageWidth = 793; //Rozmiar strony A4 w punktach
	static const int pageHeight = 1123;
private:
	QPrinter pdfPrinter;
	QPainter docCreator;
	QwtPlotRenderer plotInserter;
	QPoint currentPos;
	int pageCounter;
	QString getTime(void);
	PdfGenerator(const PdfGenerator &p);
	bool movePosition(int x, int y);
	bool writePageNumber(int nr);
	bool createNewPage();
public:
	explicit PdfGenerator(QString path2file);
	~PdfGenerator(void);
	bool addHeader(void);
	bool addPlot(QwtPlot* ptrPlot, bool strechToPageWidth = false);
	bool addPlot(QwtPlot* ptrPlotLeft, QwtPlot* ptrPlotRight);
	bool addSubtitle(QString title);
};

#endif //_PDF_GENERATOR