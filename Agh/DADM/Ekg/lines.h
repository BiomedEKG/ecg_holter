#ifndef LINES_H
#define LINES_H
 
#include <QGLWidget>
#include <QVector2D>
 
const float pi = 3.141592653f;
const float twoPi = 2.0f * pi;
const float piBy2 = 0.5f * pi;
const float degToRad = pi / 180.0f;
const float radToDeg = 180.0f / pi;
 
class Lines : public QGLWidget
{
    Q_OBJECT
 
public:
    Lines( QWidget* parent = 0 );
 
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
};
 
#endif // LINES_H