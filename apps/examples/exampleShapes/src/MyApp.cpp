
#include "MyApp.h"



MyApp::MyApp(){
    //scene->enableMultisampling();
    scene->enableLighting();

    // Shapes
    //

    va::TriangleShape* myTri = new va::TriangleShape(0,0,0, 40,0,0, 20,30,0);
    myTri->setPosition(100, 630, 0);
    myTri->setPivot(20,15,0);
    myTri->setColor(1.0, 0.19, 0.14, 1.0);
    scene->addChild(myTri);

    va::RectangleShape* myRect = new va::RectangleShape(50, 20);
    myRect->setPosition(200, 630, 0);
    myRect->setPivot(25,10,0);
    myRect->addRotationZ(45);
    myRect->setColor(1.0, 0.19, 0.14, 1.0);
    scene->addChild(myRect);

    va::EllipseShape* myElli = new va::EllipseShape(50, 50);
    myElli->setPosition(300, 630, 0);
    myElli->setResolution(60);
    myElli->setColor(1.0, 0.19, 0.14, 1.0);
    scene->addChild(myElli);

    va::LineShape* myLine = new va::LineShape();
    myLine->addVertex(10, 5, 0);
    myLine->addVertex(20, -8, 0);
    myLine->addVertex(30, 2, 0);
    myLine->addVertex(40, -5, 0);
    myLine->addVertex(50, 0, 0);
    myLine->setPosition(400, 630, 0);
    myLine->setPivot(25, 0, 0);
    myLine->setLineWidth(2.0);
    myLine->setColor(1.0, 0.19, 0.14, 1.0);
    scene->addChild(myLine);

    va::MonsterShape* myMonster = new va::MonsterShape();
    myMonster->setPosition(500, 580, 0);
    myMonster->setScale(0.5);
    myMonster->setColor(1.0, 0.19, 0.14, 1.0);
    scene->addChild(myMonster);


    // Images
    //

    imagepng = new va::ImageShape("image.png");
    imagepng->setPivot(0.5*imagepng->getWidth(), 0.0f, 0.0f);
    imagepng->setPosition(200,400,0);
    imagepng->setScale(0.5);
    scene->addChild(imagepng);

    imagejpg = new va::ImageShape("image.jpg");
    imagejpg->setPivot(0.5*imagejpg->getWidth(), 0.0f, 0.0f);
    imagejpg->setPosition(420,400,0);
    imagejpg->setScale(0.3);
    imagejpg->setColor(1.0, 0.0, 0.0, 1.0);
    scene->addChild(imagejpg);

    imagebmp = new va::ImageShape("image.bmp");
    imagebmp->setPivot(0.5*imagebmp->getWidth(), 0.0f, 0.0f);
    imagebmp->setPosition(600,400,0);
    imagebmp->setScale(0.6f);
    imagebmp->setColor(1.0, 0.0, 0.3, 1.0);
    scene->addChild(imagebmp);


    // Models
    //

    spaceship = new va::Model();
    spaceship->loadModel("spaceship.osg");
    spaceship->setPosition(200,200,0);
    spaceship->setScale(5);
    scene->addChild(spaceship);

    modelobj = new va::Model();
    modelobj->loadModel("samurai.obj");
    modelobj->setPosition(300,200,0);
    modelobj->setScale(10);
    scene->addChild(modelobj);

    model3ds = new va::Model();
    model3ds->loadModel("katana.3ds");
    model3ds->setPosition(400,200,0);
    model3ds->setScale(10);
    scene->addChild(model3ds);

    modelstl = new va::Model();
    modelstl->loadModel("dome.stl");
    modelstl->setPosition(520,200,0);
    modelstl->setScale(10);
    scene->addChild(modelstl);

    va::SliderWidget* rotSlider = new va::SliderWidget(400,40);
    rotSlider->setLabel("Rotation");
    rotSlider->setPosition(150,80);
    rotSlider->setValueMin(-va::PI);
    rotSlider->setValueMax(va::PI);
    rotSlider->addEventHandler(this);
    scene->addChild(rotSlider);

}

MyApp::~MyApp(){}


void MyApp::widget( va::SliderWidget& slider ) {

    // make objects respond to slider
    //

    imagepng->setRotation(-6*slider.getValue(), 0.0f, 1.0f, 0.0f);
    imagejpg->setRotation(6*slider.getValue(), 0.0f, 1.0f, 0.0f);
    imagebmp->setRotation(-6*slider.getValue(), 0.0f, 1.0f, 0.0f);

    spaceship->resetRotation();
    spaceship->addRotationY(slider.getValue());
    spaceship->addRotationX(0.25*slider.getValue());

    modelobj->setRotation(slider.getValue(), 0.0f, 1.0f, 0.0f);
    model3ds->setRotation(-slider.getValue(), 0.0f, 0.0f, 1.0f);
    modelstl->setRotation(-slider.getValue(), 1.0f, 0.0f, 0.0f);
}


