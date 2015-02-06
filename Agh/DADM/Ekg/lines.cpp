#include "lines.h"
 
#include <QCoreApplication>
#include <QDebug>
#include <QKeyEvent>
 
#include <math.h>
 
Lines::Lines( QWidget* parent )
    : QGLWidget( parent ),
      m_theta( 0.0f ),
      m_phi( 0.0f ),
      m_aspectRatio( 1.0 ),
      m_lineWidthRange(),
      m_lineWidthStep( 0.0f ),
      m_lineWidth( 1.0f )
{
}
 
void Lines::initializeGL()
{
    // Set the clear color to black
    glClearColor( 0.0f, 0.0f, 0.0f, 1.0f );
 
    // Set the drawing color to green
    glColor3f( 0.0f, 1.0f, 0.0f );
 
    // Query some info about supported point sizes
    glGetFloatv( GL_LINE_WIDTH_RANGE, reinterpret_cast<float*>( &m_lineWidthRange ) );
    glGetFloatv( GL_LINE_WIDTH_GRANULARITY, &m_lineWidthStep );
 
    qDebug() << "Point size range:" << m_lineWidthRange;
    qDebug() << "Point size step:" << m_lineWidthStep;
 
    m_lineWidth = m_lineWidthRange.x();
}
 
void Lines::resizeGL( int w, int h )
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
 
void Lines::paintGL()
{
    // Clear the buffer with the current clearing color
    glClear( GL_COLOR_BUFFER_BIT );
 
    // Set drawing colour to red
    glColor3f( 1.0f, 0.0f, 0.0f );
 
    // Save matrix state and do the custom rotation
    glPushMatrix();
    glRotatef( m_theta, 1.0f, 0.0f, 0.0f );
    glRotatef( m_phi,   0.0f, 1.0f, 0.0f );
 
    // Draw some Lines in a helix
    glLineWidth( m_lineWidth );
    glBegin( GL_LINE_STRIP );
    float z = -50.0f;
    float angle = 0.0f;
    for ( angle = 0.0f; angle <= twoPi * 3.0f; angle += 0.1f, z += 0.5f )
    {
        float x = 50.0 * sin( angle );
        float y = 50.0 * cos( angle );
        glVertex3f( x, y, z );
    }
    glEnd();
 
    // Restore the matrix state
    glPopMatrix();
}
 
void Lines::keyPressEvent( QKeyEvent* e )
{
    switch ( e->key() )
    {
        case Qt::Key_Escape:
            QCoreApplication::instance()->quit();
            break;
 
        case Qt::Key_Left:
            m_phi += 1.0f;
            updateGL();
            break;
 
        case Qt::Key_Right:
            m_phi -= 1.0f;
            updateGL();
            break;
 
        case Qt::Key_Up:
            m_theta += 1.0f;
            updateGL();
            break;
 
        case Qt::Key_Down:
            m_theta -= 1.0f;
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