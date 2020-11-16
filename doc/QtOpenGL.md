## 使用OpenGL 绘制图形介绍

QOpenGLWidget 类是一个用来渲染OpenGL图形的部件，它提供了在Qt应用程序中显示OpenGL图形的功能。这个类使用起来很简单，只需要继承该类，然后像使用其他QWidget部件一样来使用它即可。QOpenGLWidget提供了3个方便的虚函数，可以在子类中重新实现它们来执行典型的OpenGL任务:

    * initializeGL() : 设置OpenGL资源和状态。该函数只在第一次调用resizeGL()或paintGL()前被调用一次。
    * resizeGL() : 设置 OpenGL 的视口，投影等, 每次部件改变大小时都会调用该函数。
    * paintGL() : 渲染OpenGL场景，每当部件需要更新时都会调用该函数。

从OpenGl2.0 开始引入着色器的概念，除了固定功能的管线以外，增加了一种可编程着色管线，可以通过着色器控制顶点和片段的处理。从OpenGL 3.1开始，固定功能的管线被废弃并删除了，于是必须使用着色器来完成工作，着色器是使用OpenGL着色器语言(OpenGL Shading Language, GLSL) 编写的一个小型函数。绘图时需要至少指定两个着色器，顶点着色器(vertexshader)和片段着色器(fragmentshader, 也称为片元着色器)。Qt中QOpenGLShader类用来创建和编译着色器，支持使用OpenGL着色语言GLSL，和OpenGL/ES 着色语言GLSL/ES编写的着色器。QOpenGLShaderProgram类用来创建并设置着色器程序，可以链接多个着色器，并在OpenGL当前环境(current context, 也称为当前上下文)中绑定着色器程序。QOpenGLFunctions 类提供了对OpenGL ES2.0 API的访问接口，QOpenGLExtraFunctions 提供了对OpenGL ES 3.0 和 3.1 API 的访问接口。 QAbstractOpenGLFunctions 是一个类族的基类，类族中的类涉及了所有OpenGL版本，并为相应版本OpenGL的所有函数提供了访问接口。