#include "widget.h"
#include "ui_widget.h"
#include <boost/date_time.hpp>
#include <QTimer>
#include <stb_image.h>
#include <QMatrix4x4>
#include <QTime>

static float vertices[] = {
    // 右上角            //颜色            //纹理坐标
    0.5f,  0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f,
    // 右下角
    0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,
    // 左上角
    -0.5f,  0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f,
    // 左下角
    -0.5f, -0.5f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 0.0f
};

static unsigned int indices[] = {
    0, 1, 2, //第一个三角形
    1, 2, 3  //第二个三角形
};

Widget::Widget(QWidget *parent)
    : QOpenGLWidget(parent)
    , PolygonMode(GL_FILL)
    , ui(new Ui::Widget)
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
    vbo->allocate(vertices, sizeof(vertices));
    vbo->setUsagePattern(QOpenGLBuffer::StaticDraw);

    veo = new QOpenGLBuffer(QOpenGLBuffer::IndexBuffer);
    //create()相当于glGenBuffers(1,&EBO)
    veo->create();
    //bind()相当于glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO)
    veo->bind();
    //allocate()相当于glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
    veo->allocate(indices, sizeof(indices));
    veo->setUsagePattern(QOpenGLBuffer::StaticDraw);

    f->glEnableVertexAttribArray(0);
    f->glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8*sizeof(float), reinterpret_cast<void*>(0));

    f->glEnableVertexAttribArray(1);
    f->glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8*sizeof(float), reinterpret_cast<void*>(3*sizeof(float)));

    f->glEnableVertexAttribArray(2);
    f->glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8*sizeof(float), reinterpret_cast<void*>(6*sizeof(float)));



    //准备纹理
    texture1 = new QOpenGLTexture(QImage(":/res/textures/container.jpg").mirrored()); //由于图像坐标与纹理坐标y轴相反，需要mirrored()
    //设置纹理环绕方式
    texture1->setWrapMode(QOpenGLTexture::DirectionS, QOpenGLTexture::Repeat);
    texture1->setWrapMode(QOpenGLTexture::DirectionT, QOpenGLTexture::Repeat);
    //设置纹理过滤
    texture1->setMinificationFilter(QOpenGLTexture::LinearMipMapLinear);
    texture1->setMagnificationFilter(QOpenGLTexture::Linear);

    texture2 = new QOpenGLTexture(QImage(":/res/textures/awesomeface.png").mirrored());

    texture2->setWrapMode(QOpenGLTexture::DirectionS, QOpenGLTexture::Repeat);
    texture2->setWrapMode(QOpenGLTexture::DirectionT, QOpenGLTexture::Repeat);
    //设置纹理过滤
    texture2->setMinificationFilter(QOpenGLTexture::LinearMipMapLinear);
    texture2->setMagnificationFilter(QOpenGLTexture::Linear);


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

    if(psp->isLinked()){
//        psp->setUniformValue(uniGreen, 0.0f, greenValue, 0.0f, 1.0f);
//        int tex1 = psp->uniformLocation("texture1");
//        int tex2 = psp->uniformLocation("texture2");
//        psp->setUniformValue(tex1, 0);
//        psp->setUniformValue(tex2, 1);
        psp->setUniformValue("texture1", 0); //分配纹理单元位置，默认为0， 最少16个
        psp->setUniformValue("texture2",2);  //

        QMatrix4x4 trans;
        trans.translate(QVector3D(0.5,-0.5, 0));
        trans.rotate((float)QTime::currentTime().msecsSinceStartOfDay()/100.0, QVector3D(0.0, 0.0, 1.0));
//        trans.scale(QVector3D(0.5,0.5,0.5));

        psp->setUniformValue("transform", trans);


        vao->bind();
        //        qDebug() << "DRAW TRIANGLE" ;
        //        f->glDrawArrays(GL_TRIANGLES, 0 ,3);
        //需要加载OpenGL库，否则glPolygonMode()编译时会找不到reference
        //        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        texture1->bind(0); //必须在绘制之前绑定纹理，绑定位置值为0的纹理
        texture2->bind(2); //绑定位置值为2的纹理
        glPolygonMode(GL_FRONT_AND_BACK, static_cast<GLenum>(PolygonMode));
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, reinterpret_cast<void*>(0));

        QMatrix4x4 trans2;
        trans2.scale(sin(QTime::currentTime().msecsSinceStartOfDay()/100.0));
        psp->setUniformValue("transform", trans2);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, reinterpret_cast<void*>(0));
    }
}

