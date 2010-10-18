/*
* Copyright 2009 NOR_/D Labs <http://labs.nortd.com>
*
* This file is part of VirtualAwesome.
* VirtualAwesome is free software: you can redistribute it and/or
* modify it under the terms of the GNU Lesser General Public License 
* as published by the Free Software Foundation, either version 3 of 
* the License, or (at your option) any later version. For details
* see <http://www.gnu.org/licenses/>.
*
* * *
* 
*/

#include <va/Node.h>

using namespace va;


Node::Node() {
    _xform = new osg::PositionAttitudeTransform();
    _xform->setUserData(this);
    _geode = new osg::Geode();
    _geode->setUserData(this);
    _xform->addChild(_geode.get());
    _bUseDualXforms = false;
}


void Node::enableDualXforms() {
	// use this before adding children, does not handle children yet
	if (!_bUseDualXforms) {
        // add a second transform, for transforming
        // independantly from the inital transform 
        // new hierarchy: _xform / _xform2 / _geode / drawable
        _xform2 = new osg::PositionAttitudeTransform();
        _xform->removeChild(_geode.get());
        _xform->addChild(_xform2);
        _xform2->addChild(_geode.get());
        _xform2->setUserData(this);
        _bUseDualXforms = true;
	}
}
void Node::disableDualXforms() {
	// use this before adding children, does not handle children yet
	if (_bUseDualXforms) {	
        _xform->removeChild(_xform2);
        _xform2->removeChild(_geode.get());
        _xform->addChild(_geode.get());
        _xform2->unref();
        _bUseDualXforms = false;
	}
}
        
osg::Matrix Node::getTransform() {
    osg::Matrix mat;
    if (_bUseDualXforms) {
        osg::Matrix mat1;
        osg::Matrix mat2;
        _xform->computeLocalToWorldMatrix(mat1, NULL);
        _xform2->computeLocalToWorldMatrix(mat2, NULL);
        mat = mat2 * mat1;
    } else {
        _xform->computeLocalToWorldMatrix(mat, NULL);
    }
    return mat;
}
osg::Matrix Node::getWorldTransform() {
    return _geode->getWorldMatrices()[0];
}

osg::Vec3f Node::getWorldFromLocal( const osg::Vec3f& local ) {
	return osg::Matrixd::transform3x3(local, getTransform());
}



// Resetting Transforms
//
void Node::resetTransform() {
    resetPosition();
    resetRotation();
    resetScale();
    resetPivot();
}
void Node::resetPosition() {
    _xform->setPosition(osg::Vec3(0,0,0));
}
void Node::resetRotation() {
    _xform->setAttitude(osg::Quat());
}
void Node::resetScale() {
    _xform->setScale(osg::Vec3(1,1,1));
}
void Node::resetPivot() {
    _xform->setPivotPoint(osg::Vec3(0,0,0));
}



// common states
//

void Node::setVisible( bool bShow ) {
    if(bShow) {
        _xform->removeCullCallback(_xform->getCullCallback());
    } else {
        _xform->setCullCallback(new ForceCullCallback());
    }
    
    // This traversal makes wigdget touch 
    // responsivness stays in sync with visibility.
    _widgetTouchEventVisitor.setMode(bShow);
    _xform->accept(_widgetTouchEventVisitor);    
}

void Node::enableLighting() {
    osg::StateSet* stateset = _xform->getOrCreateStateSet();
    stateset->setMode(GL_LIGHTING, osg::StateAttribute::ON);
}
void Node::disableLighting() {
    osg::StateSet* stateset = _xform->getOrCreateStateSet();
    stateset->setMode(GL_LIGHTING, osg::StateAttribute::OFF);
}
void Node::enableDepthTest() {
    osg::StateSet* stateset = _xform->getOrCreateStateSet();
    stateset->setMode(GL_DEPTH_TEST, osg::StateAttribute::ON);
}
void Node::disableDepthTest() {
    osg::StateSet* stateset = _xform->getOrCreateStateSet();
    stateset->setMode(GL_DEPTH_TEST, osg::StateAttribute::OFF);
}
void Node::enableBlending() {
    osg::StateSet* stateset = _xform->getOrCreateStateSet();
    osg::ref_ptr<osg::BlendFunc> blendFunc = new osg::BlendFunc();
    blendFunc->setFunction(osg::BlendFunc::SRC_ALPHA, osg::BlendFunc::ONE_MINUS_SRC_ALPHA);
    stateset->setMode(GL_BLEND, osg::StateAttribute::ON);
    stateset->setAttributeAndModes(blendFunc.get(), osg::StateAttribute::ON); 
}
void Node::disableBlending() {
    osg::StateSet* stateset = _xform->getOrCreateStateSet();
    stateset->setMode(GL_BLEND, osg::StateAttribute::OFF);
}

void Node::enableAutoNormalization() {
    osg::StateSet* stateset = _xform->getOrCreateStateSet();
    stateset->setMode(GL_NORMALIZE, osg::StateAttribute::ON);
}
void Node::disableAutoNormalization() {
    osg::StateSet* stateset = _xform->getOrCreateStateSet();
    stateset->setMode(GL_NORMALIZE, osg::StateAttribute::OFF);
}


// Scene Graph Hierarchy
//

bool Node::addChild( Node* node ) {
	bool ret = false;
    if( !node->hasParent() ){
		if (_bUseDualXforms) {
            ret = _xform2->addChild(node->getOsgXForm().get());
        } else {
            ret = _xform->addChild(node->getOsgXForm().get());
        }
        if (ret) {
            node->setParent(this);
        }    	
    } else {
    	osg::notify(osg::WARN) << "in addChild, child node already has a parent, remove first from other parent" << std::endl;
    }
    return ret;
}
bool Node::insertChild( unsigned int index, Node* node ) {
	bool ret = false;
    if( !node->hasParent() ){
		if (_bUseDualXforms) {
            ret = _xform2->insertChild(index, node->getOsgXForm().get());
        } else {
            ret = _xform->insertChild(index, node->getOsgXForm().get());
        }    
        if (ret) {
            node->setParent(this);
        }
    } else {
        osg::notify(osg::WARN) << "in insertChild, child node already has a parent, remove first from other parent" << std::endl;
    }
    return ret;
}
bool Node::removeChild( Node* node ) {
	bool ret;
    if (_bUseDualXforms) {
        ret = _xform2->removeChild(node->getOsgXForm().get());
    } else {
        ret = _xform->removeChild(node->getOsgXForm().get());
    }    
	if(ret) {node->removeParent();}
    return ret;
}
bool Node::replaceChild( Node* origNode, Node* newNode ) {    
	bool ret = false;
    if( !newNode->hasParent() ){
        if (_bUseDualXforms) {
            ret = _xform2->replaceChild(origNode->getOsgXForm().get(), newNode->getOsgXForm().get());
        } else {
            ret = _xform->replaceChild(origNode->getOsgXForm().get(), newNode->getOsgXForm().get());
        }       
        if (ret) {
            origNode->removeParent();
            newNode->setParent(this);
        }
    } else {
        osg::notify(osg::WARN) << "in replaceChild, newNode already has a parent, remove first from other parent" << std::endl;
    }
    return ret;
}
bool Node::bringChildToFront( Node* node ){
	bool ret = false;
    if (_bUseDualXforms) {
        unsigned int pos = _xform2->getChildIndex(node->getOsgXForm().get());
        if(pos+1 < _xform2->getNumChildren()){
            // valid pos AND not already in the "front"
            ret = _xform2->removeChildren(pos,1) &&
                  _xform2->addChild(node->getOsgXForm().get());
        }
    } else {
        unsigned int pos = _xform->getChildIndex(node->getOsgXForm().get());
        if(pos+1 < _xform->getNumChildren()){
            // valid pos AND not already in the "front"
            ret = _xform->removeChildren(pos,1) &&
                  _xform->addChild(node->getOsgXForm().get());
        }
    }    
    return ret;    
}
bool Node::sendChildToBack( Node* node ){
	bool ret = false;
    if (_bUseDualXforms) {
        unsigned int pos = _xform2->getChildIndex(node->getOsgXForm().get());
        if(pos != 0 && pos != _xform2->getNumChildren()){
            // valid pos AND not already in the "back"
            ret = _xform2->removeChildren(pos,1) &&
                  _xform2->insertChild(0,node->getOsgXForm().get());
        }
    } else {
        unsigned int pos = _xform->getChildIndex(node->getOsgXForm().get());
        if(pos != 0 && pos != _xform->getNumChildren()){
            // valid pos AND not already in the "back"
            ret = _xform->removeChildren(pos,1) &&
                  _xform->insertChild(0,node->getOsgXForm().get());
        }    }   
    return ret;
}
bool Node::removeChildren( unsigned int index, unsigned int numToRemove ){
	bool ret;
    if (_bUseDualXforms) {
		ret = _xform2->removeChildren(index,numToRemove);
    } else {
		ret = _xform->removeChildren(index,numToRemove);
    } 
    if (ret) {
        for(unsigned int i=index; i<index+numToRemove; ++i){
            getChild(i)->removeParent();
        }
	}    
    return ret;    
}
unsigned int Node::getNumChildren() {
    if (_bUseDualXforms) {
		return _xform2->getNumChildren();
    } else {
		return _xform->getNumChildren();
    } 
}
bool Node::setChild( unsigned int index, Node* node ) {
	bool ret = false;
    if( !node->hasParent() ){
    	Node* tempnode = getChild(index);        
        if (_bUseDualXforms) {
            ret = _xform2->setChild(index, node->getOsgXForm().get());
        } else {
            ret = _xform->setChild(index, node->getOsgXForm().get());
        }         
        if (ret) {
            tempnode->removeParent();
            node->setParent(this);
        }
    } else {
        osg::notify(osg::WARN) << "in setChild, child node already has a parent, remove first from other parent" << std::endl;
    }
    return ret;                
}
Node* Node::getChild( unsigned int index ) {
	osg::Node* node;
    if (_bUseDualXforms) {
        node = _xform2->getChild(index);
    } else {
        node = _xform->getChild(index);
    }         
    Node* vanode = dynamic_cast<Node*>(node->getUserData());
    if( !vanode ) {
        osg::notify(osg::WARN) << "in getChild, not a Node at index" << std::endl;
    }
    return vanode;
}
bool Node::containsNode( Node* node ) {
    if (_bUseDualXforms) {
        return _xform2->containsNode(node->getOsgXForm().get());
    } else {
        return _xform->containsNode(node->getOsgXForm().get());
    } 
}
unsigned int Node::getChildIndex( Node* node ) {
    if (_bUseDualXforms) {
        return _xform2->getChildIndex(node->getOsgXForm().get());
    } else {
        return _xform->getChildIndex(node->getOsgXForm().get());
    }
}

bool Node::hasParent(){
	return _parent.valid();
}
bool Node::setParent( Node* parent ){
	// returns false and ignores request if
    // this node already has a parent
	bool ret = false;
	if (!_parent.valid()) {
    	_parent = parent;
        ret = true;
    }
    return ret;
}
void Node::removeParent() {
	if (_parent.valid()) {
    	_parent.release();
    }
}
osg::ref_ptr<Node> Node::getParent(){
	return _parent;
}



// Scene Graph Geometry
//

bool Node::addDrawable( Drawable* drawable ) {
    return _geode->addDrawable(drawable->getOsgDrawable().get());
}
bool Node::removeDrawable( Drawable* drawable ) {
    return _geode->removeDrawable(drawable->getOsgDrawable().get());
}
bool Node::removeDrawables( unsigned int index, unsigned int numToRemove ){
	return _geode->removeDrawables(index,numToRemove);
}
bool Node::replaceDrawable( Drawable* origDrawable, Drawable* newDrawable ) {
    return _geode->replaceDrawable(origDrawable->getOsgDrawable().get(), newDrawable->getOsgDrawable().get());    
}
unsigned int Node::getNumDrawables() {
    return _geode->getNumDrawables();
}
bool Node::setDrawable( unsigned int index, Drawable* drawable ) {
    return _geode->setDrawable( index, drawable->getOsgDrawable().get());
}
Drawable* Node::getDrawable( unsigned int index ) {
    osg::Drawable* drawable = _geode->getDrawable(index);
    Drawable* vadrawable = dynamic_cast<Drawable*>(drawable->getUserData());
    if( !vadrawable ) {
        osg::notify(osg::WARN) << "in getDrawable, not a Drawable at index" << std::endl;
    }
    return vadrawable;
}
bool Node::containsDrawable( Drawable* drawable ) {
    return _geode->containsDrawable(drawable->getOsgDrawable().get());
}
unsigned int Node::getDrawableIndex( Drawable* drawable ) {
    return _geode->getDrawableIndex(drawable->getOsgDrawable().get());
}



    
// Translation
//
float Node::getX() {
    return _xform->getPosition()[0];
}
float Node::getY() {
    return _xform->getPosition()[1];
}
float Node::getZ() {
    return _xform->getPosition()[2];
}
const osg::Vec3d& Node::getPosition() {
    return _xform->getPosition();
}

void Node::setX( float x ) {
    const osg::Vec3d& pos = _xform->getPosition(); 
    setPosition(x, pos[1], pos[2]);    
}
void Node::setY( float y ) {
    const osg::Vec3d& pos = _xform->getPosition(); 
    setPosition(pos[0], y, pos[2]);    
}
void Node::setZ( float z ) {
    const osg::Vec3d& pos = _xform->getPosition(); 
    setPosition(pos[0], pos[1], z);    
}
void Node::setPosition( float x, float y, float z ) {
    _xform->setPosition(osg::Vec3(x,y,z));
}
void Node::setPosition( const osg::Vec3& pnt ) {
    _xform->setPosition(pnt);
}

void Node::addX( float x ) {
    const osg::Vec3d& pos = _xform->getPosition(); 
    setPosition(pos[0]+x, pos[1], pos[2]);    
}
void Node::addY( float y ) {
    const osg::Vec3d& pos = _xform->getPosition(); 
    setPosition(pos[0], pos[1]+y, pos[2]);    
}
void Node::addZ( float z ) {
    const osg::Vec3d& pos = _xform->getPosition(); 
    setPosition(pos[0], pos[1], pos[2]+z);    
}
void Node::addPosition( float x, float y, float z ) {
    const osg::Vec3d& pos = _xform->getPosition();
    setPosition(pos[0]+x,pos[1]+y,pos[2]+z);
}
void Node::addPosition( const osg::Vec3& pnt ) {
    const osg::Vec3d& pos = _xform->getPosition();
    _xform->setPosition(pnt+pos);
}



// Rotation
//

float Node::getRotationAngle() {
    double angle;
    osg::Vec3f axis;
    _xform->getAttitude().getRotate(angle, axis);
    return static_cast<float>(angle);
}
osg::Vec3 Node::getRotationAxis() {
    double angle;
    osg::Vec3f axis;
    _xform->getAttitude().getRotate(angle, axis);
    return axis;
}
const osg::Quat& Node::getRotation() {
    return _xform->getAttitude();
}

void Node::setRotation( float angle, float x, float y, float z ) {
    _xform->setAttitude(osg::Quat(angle, osg::Vec3f(x,y,z)));
}
void Node::setRotation( const osg::Quat& quat ) {
    _xform->setAttitude(quat);
}
void Node::setRotation( float x1, float y1, float z1, float x2, float y2, float z2 ) {
    osg::Quat quat;
    quat.makeRotate(osg::Vec3f(x1,y1,z1), osg::Vec3f(x2,y2,z2));
    _xform->setAttitude(quat);
}
void Node::setRotation( const osg::Vec3f& vec1, const osg::Vec3f& vec2 ) {
    osg::Quat quat;
    quat.makeRotate(vec1, vec2);
    _xform->setAttitude(quat);
}
void Node::setRotation( float slerpPct, const osg::Quat& from, const osg::Quat& to ) {
    osg::Quat quat;
    quat.slerp(slerpPct, from, to);
    _xform->setAttitude(quat);
}

void Node::addRotationX( float x ) {
    const osg::Quat& attitude = _xform->getAttitude();
    _xform->setAttitude(attitude * osg::Quat(x, osg::Vec3(1,0,0)));
}
void Node::addRotationY( float y ) {
    const osg::Quat& attitude = _xform->getAttitude();
    _xform->setAttitude(attitude * osg::Quat(y, osg::Vec3(0,1,0)));
}
void Node::addRotationZ( float z ) {
    const osg::Quat& attitude = _xform->getAttitude();
    _xform->setAttitude(attitude * osg::Quat(z, osg::Vec3(0,0,1)));
}
void Node::addRotation( float angle, float x, float y, float z ) {
    const osg::Quat& attitude = _xform->getAttitude();
    _xform->setAttitude(attitude * osg::Quat(angle, osg::Vec3f(x,y,z)));
}
void Node::addRotation( const osg::Quat& quat ) {
    const osg::Quat& attitude = _xform->getAttitude();
    _xform->setAttitude(attitude * quat);
}
void Node::addRotation( float x1, float y1, float z1, float x2, float y2, float z2 ) {
    const osg::Quat& attitude = _xform->getAttitude();
    osg::Quat quat;
    quat.makeRotate(osg::Vec3f(x1,y1,z1), osg::Vec3f(x2,y2,z2));
    _xform->setAttitude(attitude * quat);
}
void Node::addRotation( const osg::Vec3f& vec1, const osg::Vec3f& vec2 ) {
    const osg::Quat& attitude = _xform->getAttitude();
    osg::Quat quat;
    quat.makeRotate(vec1, vec2);
    _xform->setAttitude(attitude * quat);
}


// Scale
//    
float Node::getScaleX() {
    return _xform->getScale()[0];
}
float Node::getScaleY() {
    return _xform->getScale()[1];
}
float Node::getScaleZ() {
    return _xform->getScale()[2];
}
const osg::Vec3d& Node::getScale() {
    return _xform->getScale();
}

void Node::setScaleX( float x ) {
    const osg::Vec3d& scale = _xform->getScale(); 
    setScale(x, scale[1], scale[2]);    
}
void Node::setScaleY( float y ) {
    const osg::Vec3d& scale = _xform->getScale(); 
    setScale(scale[0], y, scale[2]);    
}
void Node::setScaleZ( float z ) {
    const osg::Vec3d& scale = _xform->getScale(); 
    setScale(scale[0], scale[1], z);    
}
void Node::setScale( float x, float y, float z ) {
    _xform->setScale(osg::Vec3(x,y,z));
}
void Node::setScale( const osg::Vec3& scale ) {
    _xform->setScale(scale);
}
void Node::setScale( float scale ) {
    _xform->setScale(osg::Vec3(scale,scale,scale));
}

void Node::multScaleX( float x ) {
    const osg::Vec3d& scale = _xform->getScale(); 
    setScale(scale[0]*x, scale[1], scale[2]);    
}
void Node::multScaleY( float y ) {
    const osg::Vec3d& scale = _xform->getScale(); 
    setScale(scale[0], scale[1]*y, scale[2]);    
}
void Node::multScaleZ( float z ) {
    const osg::Vec3d& scale = _xform->getScale(); 
    setScale(scale[0], scale[1], scale[2]*z);    
}
void Node::multScale( float x, float y, float z ) {
    const osg::Vec3d& scale = _xform->getScale();
    setScale(scale[0]*x,scale[1]*y,scale[2]*z);
}
void Node::multScale( const osg::Vec3& scale ) {
    const osg::Vec3d& current = _xform->getScale();
    _xform->setScale(osg::Vec3d(scale[0]*current[0], scale[1]*current[1], scale[2]*current[2]));
}



// Pivot
//    
float Node::getPivotX() {
    return _xform->getPivotPoint()[0];
}
float Node::getPivotY() {
    return _xform->getPivotPoint()[1];
}
float Node::getPivotZ() {
    return _xform->getPivotPoint()[2];
}
const osg::Vec3d& Node::getPivot() {
    return _xform->getPivotPoint();
}

void Node::setPivotX( float x ) {
    const osg::Vec3d& pivot = _xform->getPivotPoint();
    _xform->setPivotPoint(osg::Vec3d(x, pivot[1], pivot[2]));
}
void Node::setPivotY( float y ) {
    const osg::Vec3d& pivot = _xform->getPivotPoint();
    _xform->setPivotPoint(osg::Vec3d(pivot[0], y, pivot[2]));
}
void Node::setPivotZ( float z ) {
    const osg::Vec3d& pivot = _xform->getPivotPoint();
    _xform->setPivotPoint(osg::Vec3d(pivot[0], pivot[1], z));
}
void Node::setPivot( float x, float y, float z ) {
    _xform->setPivotPoint(osg::Vec3d(x, y, z));
}
void Node::setPivot( const osg::Vec3& pnt ) {
    _xform->setPivotPoint(pnt);
}

void Node::addPivotX( float x ) {
    const osg::Vec3d& pivot = _xform->getPivotPoint();
    _xform->setPivotPoint(osg::Vec3d(pivot[0]+x, pivot[1], pivot[2]));  
}
void Node::addPivotY( float y ) {
    const osg::Vec3d& pivot = _xform->getPivotPoint();
    _xform->setPivotPoint(osg::Vec3d(pivot[0], pivot[1]+y, pivot[2]));  
}
void Node::addPivotZ( float z ) {
    const osg::Vec3d& pivot = _xform->getPivotPoint();
    _xform->setPivotPoint(osg::Vec3d(pivot[0], pivot[1], pivot[2]+z));  
}
void Node::addPivot( float x, float y, float z ) {
    const osg::Vec3d& pivot = _xform->getPivotPoint();
    _xform->setPivotPoint(osg::Vec3d(pivot[0]+x, pivot[1]+y, pivot[2]+z));  
}
void Node::addPivot( const osg::Vec3& pnt ) {
    const osg::Vec3d& pivot = _xform->getPivotPoint();
    _xform->setPivotPoint(pnt+pivot);  
}


