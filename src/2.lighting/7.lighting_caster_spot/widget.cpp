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

//static float vertices[] = {
//    // 右上角            //颜色            //纹理坐标
//    0.5f,  0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f,
//    // 右下角
//    0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,
//    // 左上角
//    -0.5f,  0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f,
//    // 左下角
//    -0.5f, -0.5f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 0.0f
//};

static float vertices[] = {
    // positions          // normals           // texture coords
    -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 0.0f,
     0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 0.0f,
     0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 1.0f,
     0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 1.0f,
    -0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 0.0f,

    -0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 0.0f,
     0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 1.0f,
     0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 1.0f,
    -0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 1.0f,
    -0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 0.0f,

    -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
    -0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 1.0f,
    -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
    -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
    -0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 0.0f,
    -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 0.0f,

     0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
     0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 1.0f,
     0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
     0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
     0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f,

    -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 1.0f,
     0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 1.0f,
     0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 0.0f,
     0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 0.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 0.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 1.0f,

    -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 1.0f,
     0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 1.0f,
     0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 0.0f,
    -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 0.0f,
    -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 1.0f
};

static QVector3D cubePositions[] = {
    QVector3D( 0.0f,  0.0f,  0.0f),
    QVector3D( 2.0f,  5.0f, -15.0f),
    QVector3D(-1.5f, -2.2f, -2.5f),
    QVector3D(-3.8f, -2.0f, -12.3f),
    QVector3D( 2.4f, -0.4f, -3.5f),
    QVector3D(-1.7f,  3.0f, -7.5f),
    QVector3D( 1.3f, -2.0f, -2.5f),
    QVector3D( 1.5f,  2.0f, -2.5f),
    QVector3D( 1.5f,  0.2f, -1.5f),
    QVector3D(-1.3f,  1.0f, -1.5f)
};

static unsigned int indices[] = {
    0, 1, 2, //第一个三角形
    1, 2, 3  //第二个三角形
};

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
    , lightPos(1.2, 1.0, 2.0)
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
    QOpenGLExtraFunctions *f = QOpenGLContext::currentContext()->extraFunctions();
    psp = new QOpenGLShaderProgram;
    psp->addShaderFromSourceFile(QOpenGLShader::Vertex, ":/shaders/triangle.vert");
    psp->addShaderFromSourceFile(QOpenGLShader::Fragment, ":/shaders/triangle.frag");
    psp->link();
    psp->bind();

    pspLight = new QOpenGLShaderProgram;
    pspLight->addShaderFromSourceFile(QOpenGLShader::Vertex, ":/shaders/lightcube.vert");
    pspLight->addShaderFromSourceFile(QOpenGLShader::Fragment, ":/shaders/lightcube.frag");
    pspLight->link();
    pspLight->bind();

    uniGreen = psp->uniformLocation("ourColor"); //qt里获取uniform变量指针位置

    //    program.addShaderFromSourceFile(QOpenGLShader::Vertex, ":/shaders/triangle_vert.glsl");
    //    program.addShaderFromSourceFile(QOpenGLShader::Fragment, ":/shaders/triangle_frag.glsl");
    //    program.link();
    //    program.bind();

    f->glClearColor(0.2f, 0.3f, 0.3f, 1.0f);

    vao = new QOpenGLVertexArrayObject;
    if(vao->create())
        vao->bind();

    vbo = new QOpenGLBuffer();
    vbo->create();
    vbo->bind();
    vbo->allocate(vertices, sizeof(vertices));
    vbo->setUsagePattern(QOpenGLBuffer::StaticDraw);

    //    veo = new QOpenGLBuffer(QOpenGLBuffer::IndexBuffer);
    //    //create()相当于glGenBuffers(1,&EBO)
    //    veo->create();
    //    //bind()相当于glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO)
    //    veo->bind();
    //    //allocate()相当于glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
    //    veo->allocate(indices, sizeof(indices));
    //    veo->setUsagePattern(QOpenGLBuffer::StaticDraw);

    f->glEnableVertexAttribArray(0);
    f->glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8*sizeof(float), reinterpret_cast<void*>(0));

    f->glEnableVertexAttribArray(1);
    f->glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8*sizeof(float), reinterpret_cast<void*>(3*sizeof(float))); //最后一个参数是字节的位移！

    f->glEnableVertexAttribArray(2);
    f->glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8*sizeof(float), reinterpret_cast<void*>(6*sizeof(float)));

    vbo->release();
    vao->release();

//    f->glEnableVertexAttribArray(1);
//    f->glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5*sizeof(float), reinterpret_cast<void*>(3*sizeof(float)));

    lightVAO = new QOpenGLVertexArrayObject;
    if(lightVAO->create())
        lightVAO->bind();

    vbo->bind();

    f->glEnableVertexAttribArray(0);
    f->glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8*sizeof(float), reinterpret_cast<void*>(0));

    vbo->release();
    lightVAO->release();



    //准备纹理
    texture1 = new QOpenGLTexture(QImage(":/res/textures/container2.png").mirrored()); //由于图像坐标与纹理坐标y轴相反，需要mirrored()
    //设置纹理环绕方式
    texture1->setWrapMode(QOpenGLTexture::DirectionS, QOpenGLTexture::Repeat);
    texture1->setWrapMode(QOpenGLTexture::DirectionT, QOpenGLTexture::Repeat);
    //设置纹理过滤
    texture1->setMinificationFilter(QOpenGLTexture::LinearMipMapLinear);
    texture1->setMagnificationFilter(QOpenGLTexture::Linear);

    texture2 = new QOpenGLTexture(QImage(":/res/textures/container2_specular.png").mirrored());

    texture2->setWrapMode(QOpenGLTexture::DirectionS, QOpenGLTexture::Repeat);
    texture2->setWrapMode(QOpenGLTexture::DirectionT, QOpenGLTexture::Repeat);
    //设置纹理过滤
    texture2->setMinificationFilter(QOpenGLTexture::LinearMipMapLinear);
    texture2->setMagnificationFilter(QOpenGLTexture::Linear);

    texture3 = new QOpenGLTexture(QImage(":/res/textures/matrix.jpg").mirrored());
    texture3->setWrapMode(QOpenGLTexture::DirectionS, QOpenGLTexture::Repeat);
    texture3->setWrapMode(QOpenGLTexture::DirectionT, QOpenGLTexture::Repeat);

    texture3->setMinificationFilter(QOpenGLTexture::LinearMipMapLinear);
    texture3->setMagnificationFilter(QOpenGLTexture::Linear);



    f->glEnable(GL_DEPTH_TEST);

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

    f->glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    f->glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    //    static boost::posix_time::ptime start_time = boost::posix_time::microsec_clock::local_time();
    //    boost::posix_time::time_duration timeValue = boost::posix_time::microsec_clock::local_time() - start_time;
        psp->bind();
//    if(psp->isLinked()){
        //        psp->setUniformValue(uniGreen, 0.0f, greenValue, 0.0f, 1.0f);
//                int tex1 = psp->uniformLocation("material.diffuse");
//        //        int tex2 = psp->uniformLocation("texture2");
//                psp->setUniformValue(tex1, 0);
        //        psp->setUniformValue(tex2, 1);
        psp->setUniformValue("material.diffuse", 0); //分配纹理单元位置，默认为0， 最少16个
        psp->setUniformValue("material.specular", 1);
        psp->setUniformValue("material.emission", 2);
//        psp->setUniformValue("texture2",2);  //将片段着色器中的uniform sampler2D texture1 绑定到位置0，这样，只要QOpenGLTexture::bind(0)，既可将纹理传入着色器

        float radius = 10.0f;
        float camX = sin(QTime::currentTime().msecsSinceStartOfDay()/1000.0)*radius;
        float camZ = cos(QTime::currentTime().msecsSinceStartOfDay()/1000.0)*radius;


        QMatrix4x4 view;
        view.lookAt(cameraPos, cameraPos+cameraFront, cameraUp);
//        view.lookAt(QVector3D(camX, 0.0, camZ), QVector3D(0.0, 0.0, 0.0), QVector3D(0.0,1.0,0.0));
//        view.translate(QVector3D(0.0,0.0,-3.0));

        QMatrix4x4 projection;
        projection.perspective(fov, (float)width()/height(), 0.1, 100);


        psp->setUniformValue("view", view);
        psp->setUniformValue("projection", projection);

//        psp->setUniformValue("objectColor", QVector3D(1.0, 0.5, 0.31));
//        psp->setUniformValue("lightColor", QVector3D(1.0, 1.0, 1.0));

        QVector3D lightColor;
        lightColor.setX(sin(QTime::currentTime().msecsSinceStartOfDay()/1000.0 * 2.0));
        lightColor.setY(sin(QTime::currentTime().msecsSinceStartOfDay()/1000.0 * 0.7));
        lightColor.setZ(sin(QTime::currentTime().msecsSinceStartOfDay()/1000.0 * 1.3));

        QVector3D diffuseColor = lightColor * QVector3D(0.5f, 0.5f, 0.5f);
        QVector3D ambientColor = diffuseColor * QVector3D(0.2f, 0.2f, 0.2f);


//        psp->setUniformValue("lightPos", lightPos);
        psp->setUniformValue("light.position", cameraPos);
        psp->setUniformValue("light.cutOff", cos(qDegreesToRadians(12.5f)));
        psp->setUniformValue("light.outerCutOff", cos(qDegreesToRadians(17.5f)));

        psp->setUniformValue("light.direction",cameraFront);
        psp->setUniformValue("light.ambient", 0.2f, 0.2f, 0.2f);
        psp->setUniformValue("light.diffuse",0.5f, 0.5f, 0.5f);
        psp->setUniformValue("light.specular", 1.0f, 1.0f, 1.0f);

        psp->setUniformValue("light.constant", 1.0f);
        psp->setUniformValue("light.linear", 0.09f);
        psp->setUniformValue("light.quadratic", 0.032f);

        psp->setUniformValue("viewPos", cameraPos);

//        psp->setUniformValue("material.ambient", 1.0f, 0.5f, 0.31f);
//        psp->setUniformValue("material.diffuse", 1.0f, 0.5f, 0.31f);
//        psp->setUniformValue("material.specular", 0.5f, 0.5f, 0.5f);
        psp->setUniformValue("material.shininess", 32.0f);


        vao->bind();
        //        qDebug() << "DRAW TRIANGLE" ;
        //        f->glDrawArrays(GL_TRIANGLES, 0 ,3);
        //需要加载OpenGL库，否则glPolygonMode()编译时会找不到reference
        //        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        texture1->bind(0); //必须在绘制之前绑定纹理，绑定位置值为0的纹理
        texture2->bind(1); //绑定位置值为2的纹理
        texture3->bind(2); //放射贴图
        glPolygonMode(GL_FRONT_AND_BACK, static_cast<GLenum>(PolygonMode));
        //        glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, reinterpret_cast<void*>(0));

        for(int i = 0; i < 10; i++)
        {
            QMatrix4x4 model;
            model.translate(cubePositions[i]);
//            model.rotate((float)QTime::currentTime().msecsSinceStartOfDay()*(-50.0)/1000.0, rotAxis[i]);
            psp->setUniformValue("model", model);
            glDrawArrays(GL_TRIANGLES,0,36);
        }

//    }
        lightVAO->bind();
//    if(pspLight->isLinked()){
        QMatrix4x4 model;
        model.translate(lightPos);
        model.scale(0.2);
        pspLight->bind();
        pspLight->setUniformValue("model", model);
        pspLight->setUniformValue("projection", projection);
        pspLight->setUniformValue("view", view);



        glDrawArrays(GL_TRIANGLES, 0, 36);
//    }
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
