#include "plot3D.h"

#include <qcoreapplication.h>
#include <qdebug.h>
#include <QKeyEvent>
#include <math.h>
#include <QVector>


Plot3D :: Plot3D(QVector<double> X, QVector<double> Z, QVector<double> Y, QWidget* parent)
    : QGLWidget( parent ),
      m_theta( 0.0f ),
      m_phi( 0.0f ),
      m_aspectRatio( 1.0 ),
      m_lineWidthRange(),
      m_lineWidthStep( 0.0f ),
      m_lineWidth( 1.25f ),
	  tip(25.0f),
	  turn(-30.0f),
	  XX(X),
	  YY(Y),
	  ZZ(Z)
{
}
 
void Plot3D :: initializeGL()
{
    // Set the clear color to white
    glClearColor( 1.0f, 1.0f, 1.0f, 1.0f );
 
    // Set the drawing color to black
    glColor3f( 0.0f, 0.0f, 0.0f );
 
    // Query some info about supported point sizes
    glGetFloatv( GL_LINE_WIDTH_RANGE, reinterpret_cast<float*>( &m_lineWidthRange ) );
    glGetFloatv( GL_LINE_WIDTH_GRANULARITY, &m_lineWidthStep );
 
    qDebug() << "Point size range:" << m_lineWidthRange;
    qDebug() << "Point size step:" << m_lineWidthStep;
 
    m_lineWidth = m_lineWidthRange.x();
}
 
void Plot3D :: resizeGL( int w, int h )
{
    // Prevent a divde by zero
    if ( h == 0 )
        h = 1;
 
    // Set the viewport to window dimensions
    glViewport( 0, 0, w, h );
 
    // reset the coordinate system
    glMatrixMode( GL_PROJECTION );
    glLoadIdentity();
 
    // Establish the clipping volume by setting up an orthographic projection
    double range = 100.0;
    m_aspectRatio = double( w ) / double( h );
    if ( w <=h )
        glOrtho( -range, range, -range / m_aspectRatio, range / m_aspectRatio, range, -range );
    else
        glOrtho( -range * m_aspectRatio, range * m_aspectRatio, -range, range, range, -range );
 
    glMatrixMode( GL_MODELVIEW );
    glLoadIdentity();
}
 
void Plot3D :: paintGL ()
{
    // Clear the buffer with the current clearing color
    glClear( GL_COLOR_BUFFER_BIT );
  
    // Save matrix state and do the custom rotation
	glPushMatrix ();
	glTranslatef (-10, -10, -5);
	glRotatef (tip , 1,0,0);
	glRotatef (turn, 0,1,0);
	
	// uwaga: oœ Y to oœ Z! s¹ zamienione! uwazaæ przy wyœwietlaniu wektorów
	glLineWidth (m_lineWidth );
	glColor3f( 0.0f, 0.0f, 0.0f ); //set axis&grid color black
	// create 3 axis (0:100)
	glBegin (GL_LINE_STRIP);
	glVertex3fv (ORG);
	glVertex3fv (XP ); //x axis
	glVertex3f(102.0f,0.0f,3.0f); 
	glVertex3fv (XP ); 
	glVertex3f(102.0f,3.0f,-1.5f);
	glVertex3fv (XP ); 
	glVertex3f(102.0f,-3.0f,-1.5f);
	glVertex3fv (XP ); 
	glVertex3fv (ORG);
	glVertex3fv (YP ); //y axis
	glVertex3f(0.0f,102.0f,3.0f); 
	glVertex3fv (YP ); 
	glVertex3f(3.0f,102.0f,-1.5f);
	glVertex3fv (YP ); 
	glVertex3f(-3.0f,102.0f,-1.5f);
	glVertex3fv (YP ); 
	glVertex3fv (ORG);
	glVertex3fv (ZP );//z axis
	glVertex3f(0.0f,3.0f,102.0f); 
	glVertex3fv (ZP ); 
	glVertex3f(3.0f,-1.5f,102.0f);
	glVertex3fv (ZP ); 
	glVertex3f(-3.0f,-1.5f,102.0f);
	glVertex3fv (ZP ); 
	glEnd();

	//set points on axis (ticks)
	glPointSize (m_lineWidth+1.5);

	glBegin(GL_POINTS);
	for(int r = 0; r <= 100; r=r+10){
		glVertex3i(r,0,0);
		glVertex3i(0,r,0);
		glVertex3i(0,0,r);}
	glEnd();

	// grid
	glLineWidth (m_lineWidth-0.5);

	glBegin (GL_LINES);
	for(int r = 0; r <= 100; r=r+20){
		glVertex3i(r,0,0); //xz
		glVertex3i(r,100,0);


		glVertex3i(0,r,0);
		glVertex3i(100,r,0);

		glVertex3i(0,0,r); //yz
		glVertex3i(0,100,r);
		
		glVertex3i(0,r,0);
		glVertex3i(0,r,100);
	
		glVertex3i(0,0,r); //xy
		glVertex3i(100,0,r);
		
		glVertex3i(r,0,0);
		glVertex3i(r,0,100);}
	glEnd();
	
	glRasterPos3i(110,0,0);
	glutBitmapCharacter(GLUT_BITMAP_9_BY_15, 'X');
	glRasterPos3i(0,110,0);
	glutBitmapCharacter(GLUT_BITMAP_9_BY_15, 'Z');
	glRasterPos3i(0,0,110);
	glutBitmapCharacter(GLUT_BITMAP_9_BY_15, 'Y');
	
	//podpisy p³aszczyzn
	char str1[9]={"VERTICAL"};
	char str2[9]={"SAGGITAL"};
	char str3[11]={"HORIZONTAL"};
	glColor3f( 0.0f, 0.0f, 1.0f );
	glRasterPos3i(60,80,0);
	for(int i =0; i<strlen(str1);i++)
		glutBitmapCharacter(GLUT_BITMAP_9_BY_15, str1[i]);
	glRasterPos3i(20,0,90);
	for(int i =0; i<strlen(str3);i++)
		glutBitmapCharacter(GLUT_BITMAP_9_BY_15, str3[i]);
	glRasterPos3i(0,90,90);
	for(int i =0; i<strlen(str2);i++)
		glutBitmapCharacter(GLUT_BITMAP_9_BY_15, str2[i]);

	//czerwony wykres
	glLineWidth( m_lineWidth+1 );
	glColor3f( 1.0f, 0.0f, 0.0f );

    glBegin( GL_LINE_STRIP );
  	for (int i=0; i <XX.size(); i++ )
    {
        glVertex3d( ZZ[i]+10, YY[i]+30, XX[i]+25);
    }
	glEnd();

	//rzuty na p³aszczyzny
	glColor3f( 0.0f, 0.0f, 0.0f );
	glBegin( GL_LINE_STRIP );
	for (int i=0; i <XX.size(); i++ )
    {
		glVertex3f( 0, YY[i]+30, XX[i] +25);
	}
	glEnd();

	glBegin( GL_LINE_STRIP );
    for (int i=0; i <XX.size(); i++ )
    {
	    glVertex3f( ZZ[i]+10, 0, XX[i]+25);
	}
	 glEnd();

	glBegin( GL_LINE_STRIP );
	for (int i=0; i <XX.size(); i++ )
    {
		glVertex3f( ZZ[i]+10, YY[i]+30, 0);
	}
    glEnd();

	glPopMatrix ();
	
}

void Plot3D :: keyPressEvent( QKeyEvent* e )
{
    switch ( e->key() )
    {
        case Qt::Key_Escape:
            QCoreApplication::instance()->quit();
            break;
 
        case Qt::Key_Left:
            turn -= 5;
            updateGL();
            break;
 
        case Qt::Key_Right:
			turn += 5;
            updateGL();
            break;
 
        case Qt::Key_Up:
            tip -= 5;
            updateGL();
            break;
 
        case Qt::Key_Down:
            tip += 5;
            updateGL();
            break;
 
        case Qt::Key_Plus:
            m_lineWidth = qMin( m_lineWidth + m_lineWidthStep, float( m_lineWidthRange.y() ) );
            qDebug() << "m_lineWidth =" << m_lineWidth;
            updateGL();
            break;
 
        case Qt::Key_Minus:
            m_lineWidth = qMax( m_lineWidth - m_lineWidthStep, float( m_lineWidthRange.x() ) );
            qDebug() << "m_lineWidth =" << m_lineWidth;
            updateGL();
            break;
 
        default:
            QGLWidget::keyPressEvent( e );
    }
}

