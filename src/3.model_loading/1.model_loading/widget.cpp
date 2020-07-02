#include "widget.h"
#include "ui_widget.h"
#include <boost/date_time.hpp>
#include <QTimer>
#include <stb_image.h>
#include <QMatrix4x4>
#include <QTime>
#include <random>
#include <QKeyEvent>
#include <QtMath>


Widget::Widget(QWidget *parent)
    : QOpenGLWidget(parent)
    , PolygonMode(GL_FILL)
    , cameraPos(0.0, 0.0, 3.0)
    , cameraFront(0.0, 0.0, -1.0)
    , cameraUp(0.0, 1.0, 0.0)
    , firstMouse(true)
    , yaw(-90) //当yaw= 0时，在xz平面的分量指向x轴，而初始值应该指向-z，所以旋转-90度
    , pitch(0)
    , fov(45.0)
//    , lightPos(1.2, 1.0, 2.0)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    setFocus();
    this->setFocusPolicy(Qt::StrongFocus);

    std::default_random_engine e;
    std::uniform_real_distribution<float> u(-1.0, 1.0);
    for(int i = 0; i < 10; i++)
    {
        rotAxis.push_back(QVector3D(u(e), u(e), u(e)));
    }

    lastMousePos.setX(width()/2.0);
    lastMousePos.setY(height()/2.0);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::initializeGL()
{
    // Set up the rendering context, load shaders and other resources, etc.:
    //    initializeOpenGLFunctions();
//    QOpenGLExtraFunctions *f = QOpenGLContext::currentContext()->extraFunctions();
//    f->initializeOpenGLFunctions();
    initializeOpenGLFunctions();

    psp = new QOpenGLShaderProgram;
    psp->addShaderFromSourceFile(QOpenGLShader::Vertex, ":/shaders/model_loading.vert");
    psp->addShaderFromSourceFile(QOpenGLShader::Fragment, ":/shaders/model_loading.frag");
    psp->link();
    psp->bind();

    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);


    glEnable(GL_DEPTH_TEST);

    int nrAttributes;
    glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &nrAttributes);
    qDebug() <<"Maximum nr of vertex attributes supported: " << nrAttributes;

    ourModel = new Model("D:/GitHub/LearnQtOpenGL/resources/objects/backpack/backpack.obj");
//    ourModel = new Model("D:/GitHub/LearnOpenGL/resources/objects/nanosuit/nanosuit.obj");
//    ourModel = new Model("C:/Users/think/Desktop/xx.STL");

    QTimer *timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, [=]{update();});
    timer->start(50);
}

void Widget::setPolygonLineMode(bool b)
{
    if(b)
    {
        PolygonMode = GL_LINE;
    }
    else
    {
        PolygonMode = GL_FILL;
    }
}

void Widget::resizeGL(int w, int h)
{
    glViewport(0, 0, w, h);
}

void Widget::paintGL()
{
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    psp->bind();

    QMatrix4x4 view;
    view.lookAt(cameraPos, cameraPos+cameraFront, cameraUp);

    QMatrix4x4 projection;
    projection.perspective(fov, (float)width()/height(), 0.1, 100);


    psp->setUniformValue("view", view);
    psp->setUniformValue("projection", projection);

//    psp->setUniformValue("viewPos", cameraPos);
    QMatrix4x4 model;
    model.translate(0.0f, 0.0f, 0.0f);
//    model.rotate(20.0f, rotAxis[i]);
    model.scale(1.0f, 1.0f, 1.0f);
    psp->setUniformValue("model", model);

    glPolygonMode(GL_FRONT_AND_BACK, static_cast<GLenum>(PolygonMode));

    ourModel->Draw(psp);

}

void Widget::keyPressEvent(QKeyEvent *event)
{
    float cameraSpeed = 0.05;
    switch(event->key())
    {
    case Qt::Key_W:
        qDebug() <<"W pressed!";
        cameraPos += cameraSpeed * cameraFront;
        break;
    case Qt::Key_S:
        cameraPos -= cameraSpeed * cameraFront;
        qDebug() << "S pressed!";
        break;
    case Qt::Key_A:
        cameraPos -= cameraSpeed * QVector3D::crossProduct(cameraFront, cameraUp).normalized();
        break;
    case Qt::Key_D:
        cameraPos += cameraSpeed * QVector3D::crossProduct(cameraFront, cameraUp).normalized();
        break;
    default:
        break;
    }
}

void Widget::mousePressEvent(QMouseEvent *event)
{
    switch (event->button())
    {
    case Qt::LeftButton:
        qDebug() << "Mouse Left Button Pressed!";
        break;
    case Qt::RightButton:
        qDebug() << "Mouse Right Button Pressed!";
        break;
    default:
        break;
    }

    lastMousePos = event->pos();

}

void Widget::mouseReleaseEvent(QMouseEvent *event)
{
    firstMouse = true;
}

void Widget::mouseMoveEvent(QMouseEvent *event)
{
    QPointF mousePose = event->pos();

    if(firstMouse)
    {
        lastMousePos = mousePose;
        firstMouse = false;
    }

    QPointF offset = mousePose - lastMousePos;

    float xoffset = offset.x();
    float yoffset = -offset.y(); //界面坐标y正向向下，而摄像机y轴向上

    lastMousePos = mousePose;

    float sensitivity = 0.1f;
    xoffset *= sensitivity;
    yoffset *= sensitivity;

    //    qDebug() << "xoffset: " << xoffset << "yoffset: " <<yoffset;

    yaw += xoffset;
    pitch += yoffset;

    //    qDebug() << "yaw: " << yaw << "pitch: " <<pitch;

    if(fabs(pitch) > 89.0f)
    {
        pitch = 89.0*pitch/fabs(pitch);
    }

    QVector3D front(cos(qDegreesToRadians(pitch))*cos(qDegreesToRadians(yaw)),
                    sin(qDegreesToRadians(pitch)),
                    cos(qDegreesToRadians(pitch))*sin(qDegreesToRadians((yaw))));
    cameraFront = front.normalized();
}

void Widget::wheelEvent(QWheelEvent *event)
{
    //    qDebug() << event->delta(); //每次delta都是+/- 120，每滚动一格都会进入，+1即可
    int scale = event->delta()/120.0;

    fov += scale;

    if(fov <= 1.0f)
    {
        fov = 1.0f;
    }
    else if(fov >= 50.0f)
    {
        fov = 50.0f;
    }

    qDebug() << "fov: " <<fov;

}
