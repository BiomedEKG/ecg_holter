#ifndef PLOT3D_H
#define PLOT3D_H
 
#include <QGLWidget>
#include <QVector2D>
#include <GL/glu.h>
#include <glut.h>


const float pi = 3.141592653f;
const float twoPi = 2.0f * pi;
const float piBy2 = 0.5f * pi;
const float degToRad = pi / 180.0f;
const float radToDeg = 180.0f / pi;
const int w = 400;
const int h = 600;

const float ORG[3] = {0,0,0};

const float XP[3] = {105,0,0}, XN[3] = {-105,0,0},
			YP[3] = {0,105,0}, YN[3] = {0,-105,0},
			ZP[3] = {0,0,105}, ZN[3] = {0,0,-105};
 
class Plot3D : public QGLWidget
{
    Q_OBJECT
 
public:
    Plot3D( QVector<double> X, QVector<double> Y, QVector<double> Z, QWidget* parent = 0 );

protected:
    virtual void initializeGL();
    virtual void resizeGL( int w, int h );
    virtual void paintGL();
    virtual void keyPressEvent( QKeyEvent* e );
	
private:
    float m_theta;  /**< Rotation about x-axis */
    float m_phi;    /**< Rotation about y-axis */
    float m_aspectRatio;
    QVector2D m_lineWidthRange;
    float m_lineWidthStep;
    float m_lineWidth;
	float tip;
	float turn;
	QVector<double> XX;
	QVector<double> YY;
	QVector<double> ZZ;


};
 
#endif // PLOT3D_H