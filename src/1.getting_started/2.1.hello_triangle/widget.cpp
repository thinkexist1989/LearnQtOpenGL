#include "widget.h"
#include "./ui_widget.h"

float vertices[]={
    -0.5f, -0.5f, 0.0f,
     0.5f, -0.5f, 0.0f,
     0.0f,  0.5f, 0.0f
};

Widget::Widget(QOpenGLWidget *parent)
    : QOpenGLWidget(parent)
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

//    int uni = psp->uniformLocation("uni"); //qt里获取uniform变量指针位置

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
    vbo->allocate(vertices, 3*sizeof(GL_FLOAT)*3);
    vbo->setUsagePattern(QOpenGLBuffer::StaticDraw);
    f->glEnableVertexAttribArray(0);
    f->glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3*sizeof(float), (void*)0);

    vbo->release();
    vao->release();
//    glGenVertexArrays(1, &VAO);
//    glGenBuffers(1, &VBO);
//    glBindVertexArray(VAO);

//    glBindBuffer(GL_ARRAY_BUFFER, VAO);
//    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

//    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
//    glEnableVertexAttribArray(0);

//    // note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
//    glBindBuffer(GL_ARRAY_BUFFER, 0);

//    // You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
//    // VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
    //    glBindVertexArray(0);
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

    if(psp->isLinked()){
        vao->bind();
        qDebug() << "DRAW TRIANGLE" ;
        f->glDrawArrays(GL_TRIANGLES, 0 ,3);
    }
}

