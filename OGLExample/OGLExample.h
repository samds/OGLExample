//
//  OGLExampleColor.h
//  OpenGLExample
//
//  Created by samuel de santis on 26/08/2014.
//  Copyright (c) 2014 Samuel DE SANTIS. All rights reserved.
//

#ifndef __OpenGLTutorial__OGLExample__
#define __OpenGLTutorial__OGLExample__

#include <CoreVideo/CVBase.h>
#include <Foundation/NSGeometry.h>

////////////////////////////////////////////////////////////////////////////////
// OGLExample                                                                 //
////////////////////////////////////////////////////////////////////////////////

/*
 * Base class for all shape
 */
class OGLExample {
public:
    // We can set a pure virtual destructor to 'force' the derived classes
    // to implement a destructor.
    virtual ~OGLExample() = default;
    virtual void init(const void *) = 0;
    virtual void renderForTime(const CVTimeStamp *) = 0;
    virtual void didUpdateWindowRect(NSRect) = 0;
};
////////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////////////
// OGLExampleColor                                                            //
////////////////////////////////////////////////////////////////////////////////

class OGLExampleColor : public OGLExample {
public:
    OGLExampleColor();
    
    void init(const void *);
    void renderForTime(const CVTimeStamp *);
    void didUpdateWindowRect(NSRect);
    void setColor(float,float,float,float);
private:
    float _r,_g,_b,_a;
};
////////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////////////
// OGLExampleTriangle                                                         //
////////////////////////////////////////////////////////////////////////////////

class OGLExampleTriangle : public OGLExample {
public:
    ~OGLExampleTriangle();
    
    void init(const void *);
    void renderForTime(const CVTimeStamp *);
    void didUpdateWindowRect(NSRect);
    void setColor(float,float,float,float);
private:
    GLuint _programID;
    GLuint _vertexArrayObjectName;
};
////////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////////////
// OGLExampleScissor                                                          //
////////////////////////////////////////////////////////////////////////////////

class OGLExampleScissor : public OGLExample {
public:
    OGLExampleScissor();
    
    void init(const void *);
    void renderForTime(const CVTimeStamp *);
    void didUpdateWindowRect(NSRect);
private:
    GLint _x,_y;
    GLsizei _width,_height;
};
////////////////////////////////////////////////////////////////////////////////


#endif /* defined(__OpenGLTutorial__OGLExample__) */
