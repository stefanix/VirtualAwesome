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

#ifndef VA_NODE
#define VA_NODE

#include <osg/Geode>
#include <osg/Geometry>
#include <osg/Material>
#include <osg/Vec3>
#include <osg/MatrixTransform>
#include <osg/PositionAttitudeTransform>
#include <osg/BlendFunc>

#include <va/Constants.h>
#include <va/Types.h>
#include <va/Visitors.h>

namespace va {


class ForceCullCallback : public osg::NodeCallback {
    public:
        // empty callback, no further traversal
        virtual void operator() (osg::Node* node, osg::NodeVisitor* nv) {}
};



class Node: public osg::NodeCallback {

    public:
        
        Node();
        
        osg::Matrix getTransform();
        osg::Matrix getWorldTransform();
            
        // Resetting Transforms
        //
        void resetTransform();
        void resetPosition();
        void resetRotation();
        void resetScale();
        void resetPivot();
                        
        // common states
        //
        void setVisible( bool bShow );
        void enableLighting();
        void disableLighting();
        void enableDepthTest();
        void disableDepthTest();
        void enableBlending();
        void disableBlending();
        void enableAutoNormalization();
        void disableAutoNormalization();
        
                
        // Scene Graph Hierarchy
        //
        virtual bool addChild( Node* node );
        virtual bool insertChild( unsigned int index, Node* node );
        virtual bool removeChild( Node* node );
        virtual bool removeChildren( unsigned int index, unsigned int numToRemove );
        virtual bool replaceChild( Node* origNode, Node* newNode );
        virtual bool bringChildToFront( Node* node );
        virtual bool sendChildToBack( Node* node );                              
        unsigned int getNumChildren();
        virtual bool setChild( unsigned int index, Node* node );
        Node*        getChild( unsigned int index );
        bool         containsNode( Node* node );
        unsigned int getChildIndex( Node* node );
        
        virtual bool hasParent();
        virtual bool setParent( Node* parent );
        virtual void removeParent();
        virtual osg::ref_ptr<Node> getParent();


        // Scene Graph Geometry
        //
        virtual bool addDrawable( Drawable* drawable );
        virtual bool removeDrawable( Drawable* drawable );
        virtual bool removeDrawables( unsigned int index, unsigned int numToRemove );        
        virtual bool replaceDrawable( Drawable* origDrawable, Drawable* newDrawable );
        unsigned int getNumDrawables();
        virtual bool setDrawable( unsigned int index, Drawable* drawable );
        Drawable*    getDrawable( unsigned int index );
        bool         containsDrawable( Drawable* drawable );
        unsigned int getDrawableIndex( Drawable* drawable );
        
            
        
        // Translation
        //
        float getX();
        float getY();
        float getZ();
        const osg::Vec3d& getPosition();

        void setX( float x );
        void setY( float y );
        void setZ( float z );
        void setPosition( float x, float y, float z );
        void setPosition( const osg::Vec3& pnt );
           
        void addX( float x );
        void addY( float y );
        void addZ( float z );
        void addPosition( float x, float y, float z );
        void addPosition( const osg::Vec3& pnt );

                    
        // Rotation
        //
        float getRotationAngle();
        osg::Vec3 getRotationAxis();
        const osg::Quat& getRotation();

        void setRotation( float angle, float x, float y, float z );
        void setRotation( const osg::Quat& quat );
        void setRotation( float x1, float y1, float z1, float x2, float y2, float z2 );
        void setRotation( const osg::Vec3& vec1, const osg::Vec3& vec2 );
        void setRotation( float slerpPct, const osg::Quat& quat1, const osg::Quat& quat2 );

        void addRotationX( float x );
        void addRotationY( float y );
        void addRotationZ( float z );
        void addRotation( float angle, float x, float y, float z );
        void addRotation( const osg::Quat& quat );
        void addRotation( float x1, float y1, float z1, float x2, float y2, float z2 );
        void addRotation( const osg::Vec3& vec1, const osg::Vec3& vec2 );
        
        
        // Scale
        //    
        float getScaleX();
        float getScaleY();
        float getScaleZ();
        const osg::Vec3d& getScale();

        void setScaleX( float x );
        void setScaleY( float y );
        void setScaleZ( float z );
        void setScale( float x, float y, float z );
        void setScale( const osg::Vec3& scale );
        void setScale( float scale );
        
           
        void multScaleX( float x );
        void multScaleY( float y );
        void multScaleZ( float z );
        void multScale( float x, float y, float z );
        void multScale( const osg::Vec3& scale );    
        
        
        // Pivot
        //    
        float getPivotX();
        float getPivotY();
        float getPivotZ();
        const osg::Vec3d& getPivot();

        void setPivotX( float x );
        void setPivotY( float y );
        void setPivotZ( float z );
        void setPivot( float x, float y, float z );
        void setPivot( const osg::Vec3& pnt );
           
        void addPivotX( float x );
        void addPivotY( float y );
        void addPivotZ( float z );
        void addPivot( float x, float y, float z );
        void addPivot( const osg::Vec3& pnt );
        
        
        // OSG stuff
        //
        osg::ref_ptr<osg::PositionAttitudeTransform> getOsgXForm() {return _xform;}
        osg::ref_ptr<osg::Geode> getOsgGeode() {return _geode;}    
        
        // update callback
        // when registered, operator() is called during updateTraversal
        virtual void update() {}
        virtual void operator() (osg::Node* node, osg::NodeVisitor* nv) {update(); traverse(node,nv);}
        void enableUpdateCallback() {_geode->setUpdateCallback(this);}  
        void disableUpdateCallback() {_geode->removeUpdateCallback(this);}  
            
    
    protected:
        osg::ref_ptr<Node> _parent;
        osg::ref_ptr<osg::PositionAttitudeTransform> _xform;
        osg::ref_ptr<osg::Geode> _geode;
        
        WidgetTouchEventVisitor _widgetTouchEventVisitor;
};


}
#endif

