#include "widget.h"
#include "ui_widget.h"
#include <boost/date_time.hpp>
#include <QTimer>

float vertices[] = {
    0.5f, 0.5f, 0.0f,   // 右上角
    0.5f, -0.5f, 0.0f,  // 右下角
    -0.5f, 0.5f, 0.0f,  // 左上角
    -0.5f, -0.5f, 0.0f, // 左下角
};

unsigned int indices[] = {
    0, 1, 2, //第一个三角形
    1, 2, 3  //第二个三角形
};

Widget::Widget(QWidget *parent)
    : QOpenGLWidget(parent)
    , ui(new Ui::Widget)
    , PolygonMode(GL_FILL)
{
    ui->setupUi(this);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::initializeGL()
{
    // Set up the rendering context, load shaders and other resources, etc.:
//    initializeOpenGLFunctions();
    QOpenGLExtraFunctions *f = QOpenGLContext::currentContext()->extraFunctions();
    psp = new QOpenGLShaderProgram;
    psp->addShaderFromSourceFile(QOpenGLShader::Vertex, ":/shaders/triangle.vert");
    psp->addShaderFromSourceFile(QOpenGLShader::Fragment, ":/shaders/triangle.frag");
    psp->link();
    psp->bind();

    uniGreen = psp->uniformLocation("ourColor"); //qt里获取uniform变量指针位置

//    program.addShaderFromSourceFile(QOpenGLShader::Vertex, ":/shaders/triangle_vert.glsl");
//    program.addShaderFromSourceFile(QOpenGLShader::Fragment, ":/shaders/triangle_frag.glsl");
//    program.link();
//    program.bind();

    f->glClearColor(0.2f, 0.3f, 0.3f, 1.0f);

    vao = new QOpenGLVertexArrayObject;
    if(vao->create())
        vao->bind();

    vbo = new QOpenGLBuffer;
    vbo->create();
    vbo->bind();
    vbo->allocate(vertices, 3*sizeof(GL_FLOAT)*4);
    vbo->setUsagePattern(QOpenGLBuffer::StaticDraw);

    veo = new QOpenGLBuffer(QOpenGLBuffer::IndexBuffer);
    //create()相当于glGenBuffers(1,&EBO)
    veo->create();
    //bind()相当于glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO)
    veo->bind();
    //allocate()相当于glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
    veo->allocate(indices, 3*sizeof(GL_UNSIGNED_INT)*2);
    veo->setUsagePattern(QOpenGLBuffer::StaticDraw);

    f->glEnableVertexAttribArray(0);
    f->glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3*sizeof(float), reinterpret_cast<void*>(0));

    vbo->release();
    vao->release();

    int nrAttributes;
    glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &nrAttributes);
    qDebug() <<"Maximum nr of vertex attributes supported: " << nrAttributes;
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
    // Update projection matrix and other size related settings:
//        m_projection.setToIdentity();
//        m_projection.perspective(45.0f, w / float(h), 0.01f, 100.0f);
    QOpenGLExtraFunctions *f = QOpenGLContext::currentContext()->extraFunctions();
    f->glViewport(0, 0, w, h);
}

void Widget::paintGL()
{
    // Draw the scene:
    QOpenGLExtraFunctions *f = QOpenGLContext::currentContext()->extraFunctions();
    f->glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    f->glClear(GL_COLOR_BUFFER_BIT);

//    static boost::posix_time::ptime start_time = boost::posix_time::microsec_clock::local_time();
//    boost::posix_time::time_duration timeValue = boost::posix_time::microsec_clock::local_time() - start_time;
    static float timeValue = 0.0;
    float greenValue = sin(timeValue)/2.0f + 0.5f;
    timeValue += 0.1;

    if(psp->isLinked()){
        psp->setUniformValue(uniGreen, 0.0f, greenValue, 0.0f, 1.0f);
        vao->bind();
//        qDebug() << "DRAW TRIANGLE" ;
//        f->glDrawArrays(GL_TRIANGLES, 0 ,3);
        //需要加载OpenGL库，否则glPolygonMode()编译时会找不到reference
//        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        glPolygonMode(GL_FRONT_AND_BACK, PolygonMode);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    }
}

