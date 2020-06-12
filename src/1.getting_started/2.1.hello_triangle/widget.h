#ifndef WIDGET_H
#define WIDGET_H

#include <QOpenGLWidget>
#include <QOpenGLExtraFunctions>
#include <QOpenGLShaderProgram>
#include <QOpenGLVertexArrayObject>
#include <QOpenGLBuffer>

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QOpenGLWidget
{
    Q_OBJECT

public:
    Widget(QOpenGLWidget *parent = nullptr);
    ~Widget();

    QOpenGLShaderProgram* psp;
    QOpenGLVertexArrayObject *vao;
    QOpenGLBuffer *vbo;

private:
    Ui::Widget *ui;

protected:
    void initializeGL() override;
    void resizeGL(int w, int h) override;
    void paintGL() override;
};
#endif // WIDGET_H
