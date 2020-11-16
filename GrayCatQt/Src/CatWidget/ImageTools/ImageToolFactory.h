#ifndef IMAGETOOLFACTORY_H
#define IMAGETOOLFACTORY_H

#include <QWidget>

class ImageToolBase;

class ImageToolFactory
{

public:
    explicit ImageToolFactory(QWidget *parent = nullptr);
    ~ImageToolFactory();

public:
    enum TOOLS {SCREENSHOT, MAGNIFYINGGLASS, SPOTLIGHT};
    ImageToolBase* NewTool(TOOLS);

private:
    QWidget *m_pParent;

};

#endif // IMAGETOOLFACTORY_H
