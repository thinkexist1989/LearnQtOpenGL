#ifndef WIDGET_H
#define WIDGET_H

#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QOpenGLShaderProgram>
#include <QOpenGLVertexArrayObject>
#include <QOpenGLBuffer>
#include <QOpenGLTexture>

#include <model.h>

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QOpenGLWidget, protected QOpenGLFunctions
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

    QOpenGLShaderProgram* psp;
    QOpenGLVertexArrayObject *vao;
    QOpenGLBuffer *vbo;
    QOpenGLBuffer *veo;

    QOpenGLVertexArrayObject *lightVAO; //用来绘制灯光

    QOpenGLTexture *texture1;
    QOpenGLTexture *texture2;
    QOpenGLTexture *texture3;

    std::vector<QVector3D> rotAxis;

    int uniGreen;

    void setPolygonLineMode(bool b);
    int PolygonMode;

    QVector3D cameraPos;
    QVector3D cameraFront;
    QVector3D cameraUp;

    QPointF lastMousePos;
    bool firstMouse;

    float yaw;
    float pitch;

    float fov;

    QVector3D lightPos;
    QOpenGLShaderProgram *pspLight;

    Model* ourModel;

private:
    Ui::Widget *ui;

protected:
    void initializeGL() override;
    void resizeGL(int w, int h) override;
    void paintGL() override;

    void keyPressEvent(QKeyEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void wheelEvent(QWheelEvent *event) override;
};

#endif // WIDGET_H
