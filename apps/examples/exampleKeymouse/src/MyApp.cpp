
#include "MyApp.h"



MyApp::MyApp(){
    rect = new va::RectangleShape(200,100);
    rect->setPivot(100,50,0);
    rect->setPosition(scene->getWidth()*0.5, scene->getHeight()*0.5, 0.0);
    rect->setColor(0.6, 0.1, 0.3, 1.0);
    scene->addChild(rect);
    
    text = new va::TextShape();
    text->reshape(200,100);
    text->setPivot(100,50,0);
    text->setPadding(5);
    text->setPosition(scene->getWidth()*0.5+300, scene->getHeight()*0.5, 0.0);    
    text->appendText("Press [r], [g], [b] to change the color of the Rectangle. \n");
    text->appendText("Mouse scrolling rotates the thing.");
    scene->addChild(text);
}

MyApp::~MyApp(){}



void MyApp::keyPress( va::Key& key ){
    if (key.getKey() == 'r') {
        rect->setColor(1,0,0,0);
    } else if (key.getKey() == 'g') {
        rect->setColor(0,1,0,0);
    } else if (key.getKey() == 'b') {
        rect->setColor(0,0,1,0);
    } else if (key.getKey() == va::Key::KEY_Space) {
        rect->addRotationY(va::PI*0.2);
    }
}

void MyApp::keyRelease( va::Key& key ){}



void MyApp::touchDown( va::Touch& touch ){
    rect->setScale(2);
}

void MyApp::touchMove( va::Touch& touch ){}

void MyApp::touchUp( va::Touch& touch ){
    rect->setScale(1);
}



void MyApp::mouseButton( va::Mouse& mouse ){
    // The mouse button event is only of interest when it's
    // neccessary to distingush between left, middle, right button
    // otherwise simply use touchDown, touchUp
    // They are the universals for all pointing devices.
    
    if (mouse.getButtonDirection() == va::Mouse::RELEASE) {
        if (mouse.getButton() == va::Mouse::MIDDLE_BUTTON) {
            rect->setColor(0,1,1,0);
        } else if (mouse.getButton() == va::Mouse::RIGHT_BUTTON) {
            rect->setColor(1,0,1,0);
        }
    }
}

void MyApp::mouseScroll( va::Mouse& mouse ){
    rect->addRotationY(-mouse.getScrollingDeltaX()*0.01);
    rect->addRotationX(-mouse.getScrollingDeltaY()*0.01);
}




