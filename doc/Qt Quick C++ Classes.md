## Qt Quick C++ Classes

Qt Quick模块提供了用于在Qt / C ++应用程序中嵌入Qt Quick的类

| 类 | 功能 |
|--|--|
| QQuickFramebufferObject | 用于使用framebuffer对象(FBO)与Qt Quick集成OpenGL渲染的便利类 |
| QQuickFramebufferObject::Renderer ||
| QQuickItem | Qt Quick中最基本的可视项 |
| QQuickItem::ItemChangeData | 向QQuickItem::itemChange()函数添加补充信息 |
| QQuickItemGrabResult | 包含来自QQuickItem::grabToImage()的结果 |
| QQuickPaintedItem | 在QML场景图中使用QPainter API的方法 |
| QQuickRenderControl | 以完全由应用程序控制的方式将Qt Quick scenegraph渲染到屏幕外的渲染目标上的机制 |
| QQuickTextDocument | 访问QQuickTextEdit的QTextDocument |
| QQuickView | 用于显示Qt Quick用户界面的窗口 |
| QQuickWindow | 用于显示图形化QML场景的窗口 |
| QQuickWindow::GraphicsStateInfo | 描述在beginExternalCommands()调用时RHI的一些图形状态 |
| QSGAbstractRenderer | 提供对场景图节点的访问和一个QSGEngine的渲染 |
| QSGGeometry | QSGGeometry类为Qt Quick Scene Graph中的图形基元提供了低级存储 |
| QSGGeometry::Attribute | 该QSGGeometry::Attribute描述了一个顶点属性QSGGeometry |
| QSGGeometry::AttributeSet | 该QSGGeometry::AttributeSet中描述了如何在一个顶点QSGGeometry被建造 |
| QSGGeometry::ColoredPoint2D | 所述QSGGeometry::ColoredPoint2D结构是用于访问2D点与颜色的便利结构。 |
| QSGGeometry::Point2D | 所述 QSGGeometry::Point2D 结构是用于访问2D点一个便利结构。 |
| QSGGeometry::TexturedPoint2D | 所述QSGGeometry::TexturedPoint2D结构是用于访问二维点与纹理坐标一个便利结构。 |
| QSGMaterial | QSGMaterial类封装了着色器程序的渲染状态。 |
| QSGMaterialRhiShader | QSGMaterialRhiShader类表示独立于图形API的着色器程序。 |
| QSGMaterialRhiShader::GraphicsPipelineState | 描述材质要应用于当前活动图形管道状态的状态更改。 |
| QSGMaterialShader | QSGMaterialShader类表示渲染器中的OpenGL着色器程序。 |
| QSGMaterialShader::RenderState | 在调用QSGMaterialShader::updateState()时，QSGMaterialShader::RenderState封装了当前的渲染状态。 |
| QSGMaterialType | QSGMaterialType类与QSGMaterial结合用作唯一类型令牌。 |
| QSGBasicGeometryNode | QSGBasicGeometryNode类用作基于几何的节点的基类 |
| QSGClipNode | QSGClipNode类在场景图中实现剪辑功能。 |
| QSGGeometryNode | QSGClipNode类在场景图中实现剪辑功能。 |
| QSGNode | QSGNode类是场景图中所有节点的基类。 |
| QSGOpacityNode | QSGOpacityNode类用于更改节点的不透明度。 |
| QSGTransformNode | QSGTransformNode类在场景图中实现转换。 |
| QSGRendererInterface | 一个接口，提供对场景图形的某些图形API特定内部的访问。 |
| QSGRenderNode | QSGRenderNode类表示一组针对场景场景正在使用的图形API的自定义渲染命令。 |
| QSGDynamicTexture | QSGDynamicTexture类用作动态更改纹理（例如渲染到FBO的内容）的基类。 |
| QSGTexture | QSGTexture类是场景图中使用的纹理的基类。 |
| QSGEngine | QSGEngine类允许场景图的低级渲染。 |
| QSGFlatColorMaterial | QSGFlatColorMaterial类提供了一种在场景图中渲染纯色几何的便捷方法。 |
| QSGImageNode | 提供QSGImageNode类是为了方便使用QML场景图轻松绘制纹理内容。 |
| QSGRectangleNode | QSGRectangleNode类是用于使用Scenegraph绘制实心填充矩形的便捷类。 |
| QSGSimpleMaterial | QSGSimpleMaterial类是模板生成的类，用于存储与QSGSimpleMateralShader一起使用的状态。 |
| QSGSimpleMaterialShader | QSGSimpleMaterialShader类提供了一种方便的方法来为场景图构建基于OpenGL的自定义材质。 |
| QSGOpaqueTextureMaterial | QSGOpaqueTextureMaterial类提供了一种在场景图中渲染带纹理的几何图形的便捷方法。 |
| QSGTextureMaterial | QSGTextureMaterial类提供了一种在场景图中渲染带纹理的几何图形的便捷方法。 |
| QSGTextureProvider | QSGTextureProvider类将基于纹理的实体封装在QML中。 |
| QSGVertexColorMaterial | QSGVertexColorMaterial类提供了一种方便的方式来渲染场景图中的按顶点着色的几何图形。 |
| QQuickAsyncImageProvider | QQuickAsyncImageProvider类为QML图像请求的异步控制提供了一个接口。 |
| QQuickImageProvider | QQuickImageProvider类提供了一个接口，用于支持QML中的像素图和线程图像请求。 |
| QQuickImageResponse | 所述QQuickImageResponse类为异步图像加载的接口QQuickAsyncImageProvider。 |
| QQuickTextureFactory | QQuickTextureFactory类提供了一个用于从QML加载自定义纹理的接口。 |
