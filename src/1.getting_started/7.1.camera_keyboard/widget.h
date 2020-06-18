#ifndef WIDGET_H
#define WIDGET_H

#include <QOpenGLWidget>
#include <QOpenGLExtraFunctions>
#include <QOpenGLShaderProgram>
#include <QOpenGLVertexArrayObject>
#include <QOpenGLBuffer>
#include <QOpenGLTexture>

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QOpenGLWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

    QOpenGLShaderProgram* psp;
    QOpenGLVertexArrayObject *vao;
    QOpenGLBuffer *vbo;
    QOpenGLBuffer *veo;

    QOpenGLTexture *texture1;
    QOpenGLTexture *texture2;

    std::vector<QVector3D> rotAxis;

    int uniGreen;

    void setPolygonLineMode(bool b);
    int PolygonMode;

    QVector3D cameraPos;
    QVector3D cameraFront;
    QVector3D cameraUp;

private:
    Ui::Widget *ui;

protected:
    void initializeGL() override;
    void resizeGL(int w, int h) override;
    void paintGL() override;

    void keyPressEvent(QKeyEvent *event) override;
};

#endif // WIDGET_H
