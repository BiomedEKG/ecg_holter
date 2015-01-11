#include "PdfGenerator.h"
#include <QtCore/qdatetime.h>

//Constructor
PdfGenerator::PdfGenerator(QString path2file) 
	: pdfPrinter(), docCreator(), plotInserter(), currentPos(leftRightMargin,topBottomMargin), pageCounter(1)
{
	//Printer's settings
	pdfPrinter.setOutputFileName(path2file);
	pdfPrinter.setOutputFormat(QPrinter::PdfFormat);
	pdfPrinter.setPageSize(QPrinter::A4);
	pdfPrinter.setOrientation(QPrinter::Portrait);
	pdfPrinter.setFullPage(true);
	plotInserter.setDiscardFlag(QwtPlotRenderer::DiscardBackground );
	//Qwt plot renderer settings
	plotInserter.setDiscardFlag(QwtPlotRenderer::DiscardLegend);
}
//Private copy constructor (coping disabled)
PdfGenerator::PdfGenerator(const PdfGenerator &p){
}
//Destructor
PdfGenerator::~PdfGenerator(void)
{
	if (docCreator.isActive())
		docCreator.end();
}
// Private method - returns current time formatted as a QString
QString PdfGenerator::getTime(void){
	QDateTime dateTime = QDateTime::currentDateTime();
	QString dateTimeString = dateTime.toString("dd-MM-yyyy hh:mm:ss");
	return dateTimeString;
}
//Protected method - changes position of currentPos point
bool PdfGenerator:: movePosition(int x, int y){
	int newCoordinateX	= currentPos.rx() + x;
	int newCoordinateY = currentPos.ry() + y;

	if (newCoordinateX > pageWidth)
		newCoordinateX = pageWidth - leftRightMargin;

	if (newCoordinateX < leftRightMargin)
		newCoordinateX = leftRightMargin;

	if (newCoordinateY < topBottomMargin) 
		newCoordinateY = topBottomMargin;

	if ((newCoordinateY + topBottomMargin) >= pageHeight) 
		return false;
	else 
		currentPos = QPoint(newCoordinateX,newCoordinateY);
	return true;
}
//Protected method - Checks whether object gonna fit in paper sheet
bool PdfGenerator::isTooBig(int objectHeight){
	return ((objectHeight + currentPos.ry() + topBottomMargin) > pageHeight);

}
//*********************Protected method - creates new page************/
bool PdfGenerator::createNewPage(){
	if (!pdfPrinter.newPage())
		return false;
	currentPos.setX(leftRightMargin);
	currentPos.setY(topBottomMargin);
	writePageNumber(++pageCounter);
	return true;
}
//Private method - writes page number in the rigth corner od the page
bool PdfGenerator:: writePageNumber(int nr){
	//Init if docCreator wasn't activated before
	if (!docCreator.isActive())
		if (!docCreator.begin(&pdfPrinter))
			return false;
	QString str = QString::number(nr);
	docCreator.setFont(QFont("Tahoma",10));
	QFontMetrics fMetrics = docCreator.fontMetrics();
	QSize strSize = fMetrics.size(Qt::TextSingleLine,str);
	QRect bbox = QRect(QPoint(pageWidth-leftRightMargin-strSize.width(),pageHeight-leftRightMargin-strSize.height()),strSize);
	docCreator.drawText(bbox,str);
	return true;
}

/******************* Adds header on the top of the page*************/
bool PdfGenerator::addHeader(QString title){
	//Init if docCreator wasn't activated before
	if (!docCreator.isActive())
		if (!docCreator.begin(&pdfPrinter))
			return false;
	//Set painter
	docCreator.setPen(QPen(Qt::black, 2.0, Qt::SolidLine));
	docCreator.setBrush(Qt::NoBrush);
	// Write title
	//QString title = "ECG Analysis Results";
	QFont f("Tahoma",24);
	docCreator.setFont(f);
	QFontMetrics fMetrics = docCreator.fontMetrics();
	QSize titleSize = fMetrics.size( Qt::TextSingleLine, title);
	docCreator.drawText(QRect(currentPos, titleSize),title);
	
	//Write date and time
	docCreator.setFont(QFont("Tahoma",10));
	fMetrics = docCreator.fontMetrics();
	QString dateTimeStr = getTime();
	QRect bbox = QRect(QPoint(pageWidth-6*leftRightMargin, currentPos.ry()), fMetrics.size(Qt::TextSingleLine,dateTimeStr));
	docCreator.drawText(bbox,dateTimeStr);
	movePosition(0,titleSize.height());//move "cursor" down
	//Draw lines
	docCreator.setPen(Qt::red);//change color
	docCreator.drawLine(currentPos, QPoint(pageWidth-leftRightMargin, currentPos.ry()));//draw one line
	movePosition(0,5);// move again
	docCreator.drawLine(currentPos, QPoint(pageWidth-leftRightMargin, currentPos.ry()));//draw another line
	docCreator.setPen(Qt::black);//reset color to black
	return (writePageNumber(pageCounter));
		
}
	
/***************Inserts plot do the document************************/
bool PdfGenerator::addPlot(QwtPlot* ptrPlot,bool strechToPageWidth){
	//If QPainter is not active
	if (!docCreator.isActive())
		if (!docCreator.begin(&pdfPrinter))
			return false;
	//Get size of the plot
	QSize sizePlot = ptrPlot->size();
	//Check whether plot would fit in the current page
	if (isTooBig(sizePlot.height()))
		if (!createNewPage())
			return false;
	//Compute coordinates of bottom right point
	QPoint bottomRight;
	bottomRight.setY(currentPos.ry() + sizePlot.height());
	if (strechToPageWidth)
		bottomRight.setX(pageWidth-2*leftRightMargin);
	else 
		bottomRight.setX(currentPos.rx() + sizePlot.width());
	//Create rectangle for new plot
	QRectF bbox = QRectF(currentPos, bottomRight); 
	ptrPlot->replot();//bez tego nie zadzia³a, bd pusty wykres
	//Insert plot
	plotInserter.render(ptrPlot, &docCreator, bbox);
	//Increase current position
	if (!movePosition(0, sizePlot.height() + gap))
		if (!createNewPage())
			return false;
	//if success, return true
	return true;
}
/***************Insert plot to the document - overloaded************/
bool PdfGenerator::addPlot(QwtPlot* ptrPlot,int plotWidth, directionOfCursorMove dir){
	//If QPainter is not active
	if (!docCreator.isActive())
		if (!docCreator.begin(&pdfPrinter))
			return false;
	//Get size of the plot
	QSize sizePlot = ptrPlot->size();
	//Check whether plot would fit in the current page
	if (isTooBig(sizePlot.height()))
		if (!createNewPage())
			return false;
	//Compute coordinates of bottom right point
	double scale = (double)plotWidth/(double)sizePlot.width();

	QPoint bottomRight;
	bottomRight.setY(currentPos.ry() + (int)((double)sizePlot.height()*scale));
	bottomRight.setX(currentPos.rx() + plotWidth);

	//Create rectangle for new plot
	QRectF bbox = QRectF(currentPos, bottomRight); 
	ptrPlot->replot();//bez tego nie zadzia³a, bd pusty wykres
	//Insert plot
	plotInserter.render(ptrPlot, &docCreator, bbox);
	switch (dir){
		case toSide:
			movePosition((pageWidth-gap)/2-leftRightMargin, 0);
			break;
		case toBottom:
			if (!movePosition(leftRightMargin-currentPos.rx(), (int)((double)sizePlot.height()*scale) + gap))
				if(!createNewPage())
					return false;
			break;
	}
	//if success, return true
	return true;
}
/*********************Inserts two plots*****************************/
bool PdfGenerator::addPlots(QwtPlot* ptrPlotLeft, QwtPlot* ptrPlotRight){
	//If QPainter is not active
	if (!docCreator.isActive())
		if (!docCreator.begin(&pdfPrinter))
			return false;
	//Get the size of left and rigth plot
	QSize sizeLeft = ptrPlotLeft->size();
	QSize sizeRight = ptrPlotRight->size();
	//Set plot height & width
	int plotHeight;
	int plotWidth = (int)((pageWidth - 2*leftRightMargin - gap)/2);
	//If both plots don't have the same height, choose the greater one
	if (sizeLeft.height() > sizeRight.height())
		plotHeight = sizeLeft.height();
	else 
		plotHeight = sizeRight.height();
	//Check whether plot would fit in the current page, if not create another page
	if (isTooBig(plotHeight))
		if (!createNewPage())
			return false;

	// Compute coordinates of bottom right corner - leftPlot
	QPoint bottomRight = QPoint(currentPos.rx() + plotWidth,currentPos.ry() + plotHeight);
	// Add left plot
	ptrPlotLeft -> replot();
	plotInserter.render(ptrPlotLeft, &docCreator, QRectF(currentPos, bottomRight));//insert plot
	//Move position of a cursor
	movePosition(plotWidth+gap,0);
	//Change position of bottom-right corner, y remains the same
	bottomRight += QPoint(plotWidth+gap,0);
	//Add right plot
	ptrPlotRight -> replot();
	plotInserter.render(ptrPlotRight, &docCreator, QRectF(currentPos, bottomRight));//insert plot
	//Move position of a cursor
	//IF you can't move cursor return false
	if (!movePosition(-(gap+plotWidth),plotHeight+gap))
		if (!createNewPage())
			return false;
	//Success, return true
	return true;
}
/*********************Adds title of the section******************************/
bool PdfGenerator::addSubtitle(QString title){
	//If QPainter is not active
	if (!docCreator.isActive())
		if (!docCreator.begin(&pdfPrinter))
			return false;
	docCreator.setFont(QFont("Tahoma", 18));
	QFontMetrics fMetrics = docCreator.fontMetrics();
	QSize titleSize = fMetrics.size( Qt::TextSingleLine, title);
	if (isTooBig(titleSize.height()))//check whether title would fit
		if (!createNewPage())
			return false;
	docCreator.drawText(QRect(currentPos, titleSize),title);
	if (!movePosition(0,titleSize.height()+gap))// move position, if false, crete new page
		if (!createNewPage())
			return false;
	return true;
}
/*******************Adds table to the document**************************/
bool PdfGenerator::addTable(QStringList data, int colsNr, int width, directionOfCursorMove dir){
	
	int dataSize = data.size(); 
	int rowsNr = (int) ((float)dataSize/float(colsNr) + 0.5);//compute how many rows

	//Check whether plot would fit in the current page, if not create another one
	if (isTooBig(cellHeight*rowsNr + gap)) 
		if(!createNewPage())
			return false;
	QRect r (currentPos, QSize(width/colsNr, cellHeight));//rectable for table's cell
	QRect required = QRect();
	int x_pos = currentPos.x();//where to start drawing table
	int y_pos = currentPos.y();
	
	if (!docCreator.isActive())
		if(!docCreator.begin(&pdfPrinter))
			return false;
	//Set font, first row of table in bold
	QFont f("Tahoma",12);
	f.setBold(true);
	docCreator.setFont(f);
	//Write data to table
	for (int i=0; i<dataSize; i++){

		docCreator.drawRect(r);//draw rectangle
		if (i == colsNr){//if we go through thirst row, switch of bold
			f.setBold(false);
			docCreator.setFont(f);
		}
		if ((i % colsNr) == 0)// if first column set text to left
			docCreator.drawText(r,Qt::AlignLeft | Qt::TextWordWrap, data.at(i), &required);
		else
			docCreator.drawText(r,Qt::AlignCenter | Qt::TextWordWrap, data.at(i), &required);

		if ((i % colsNr) == colsNr -1){
			//Skip to next row
			x_pos = currentPos.rx();
			y_pos += cellHeight;
			r.moveTopLeft(QPoint(x_pos, y_pos));
		}
		else{
			//Skip to next column, move to the right
			x_pos+= width/colsNr;
			r.moveTopLeft(QPoint(x_pos,y_pos));
		}
	}
	switch (dir){
	case toSide:
		movePosition((pageWidth-2*leftRightMargin-gap)/2, 0); break;
	case toBottom:
		if (!movePosition(- currentPos.rx() + leftRightMargin,cellHeight*rowsNr+gap))
			if (!createNewPage())
				return false;
		break;
	}
	return true;
}

