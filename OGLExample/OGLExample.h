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
#include <string>


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
    
    virtual std::string name();
//    virtual std::string descriptionFilename() = 0;
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
    std::string name();

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
    std::string name();
    
private:
    GLuint _programID;
    GLuint _vertexArrayObjectName;
};
////////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////////////
// OGLExampleCircle                                                           //
////////////////////////////////////////////////////////////////////////////////

class OGLExampleCircle : public OGLExample {
public:
    ~OGLExampleCircle();
    
    void init(const void *);
    void renderForTime(const CVTimeStamp *);
    void didUpdateWindowRect(NSRect);
    void setColor(float,float,float,float);
private:
    GLuint _programID;
    GLuint _vertexArrayObjectName;
    GLuint _vertexbufferObject;
};
////////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////////////
// OGLExampleTriangle2                                                        //
////////////////////////////////////////////////////////////////////////////////

class OGLExampleTriangle2 : public OGLExample {
public:
    ~OGLExampleTriangle2();
    
    void init(const void *);
    void renderForTime(const CVTimeStamp *);
    void didUpdateWindowRect(NSRect);
    std::string name();
private:
    GLuint _programID;
    GLuint _vertexArrayObjectName, _vertexBufferObjectName;
    GLuint _indexAttrib;
};
////////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////////////
// OGLExampleTriangle3                                                        //
////////////////////////////////////////////////////////////////////////////////

/*
 * This example use color as a uniform attribute (TriangleUniformColor.fsh)
 */
class OGLExampleTriangle3 : public OGLExample {
public:
    ~OGLExampleTriangle3();
    
    void init(const void *);
    void renderForTime(const CVTimeStamp *);
    void didUpdateWindowRect(NSRect);
    std::string name();

private:
    GLuint _programID;
    GLuint _vertexArrayObjectName, _vertexBufferObjectName;
    GLuint _indexAttrib;
};
////////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////////////
// OGLExampleTriangle4                                                        //
////////////////////////////////////////////////////////////////////////////////

/*
 * This example define color per vertex of 
 * the triangle (TriangleDynColor.vsh/fsh)
 */
class OGLExampleTriangle4 : public OGLExample {
public:
    ~OGLExampleTriangle4();
    
    void init(const void *);
    void renderForTime(const CVTimeStamp *);
    void didUpdateWindowRect(NSRect);
    std::string name();

private:
    GLuint _programID;
    GLuint _vertexArrayObjectName, _vertexBufferObjectName;
    GLuint _positionAttrib,_colorAttrib;
};
////////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////////////
// OGLExampleSquare                                                           //
////////////////////////////////////////////////////////////////////////////////

/*
 * A square simply defined as 2 triangles (without element buffer).
 */
class OGLExampleSquare : public OGLExample {
public:
    ~OGLExampleSquare();
    
    void init(const void *);
    void renderForTime(const CVTimeStamp *);
    void didUpdateWindowRect(NSRect);
    std::string name();

private:
    GLuint _programID;
    GLuint _vertexArrayObjectName, _vertexBufferObjectName;
    GLuint _positionAttrib,_colorAttrib;
};
////////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////////////
// OGLExampleSquare2                                                          //
////////////////////////////////////////////////////////////////////////////////

/*
 * A square defined as 2 triangles using element buffer.
 */
class OGLExampleSquare2 : public OGLExample {
public:
    ~OGLExampleSquare2();
    
    void init(const void *);
    void renderForTime(const CVTimeStamp *);
    void didUpdateWindowRect(NSRect);
    std::string name();
    
private:
    GLuint _programID;
    GLuint _vertexArrayObjectName;
    GLuint _vertexBufferObjectName;
    GLuint _elementBufferObjectName;
    GLuint _positionAttrib,_colorAttrib;
};
////////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////////////
// OGLExampleScissor                                                          //
////////////////////////////////////////////////////////////////////////////////

/*
 * We define 3 scissor boxes :
 *  BOX1 in Red
 *  BOX2 in Green
 *  BOX3 in Blue
 *
 *  -----------------
 *  |   1   |   2   |
 *  |       |       |
 *  |---------------|
 *  |       3       |
 *  |               |
 *  -----------------
 */
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


////////////////////////////////////////////////////////////////////////////////
// OGLExampleTexture1                                                         //
////////////////////////////////////////////////////////////////////////////////

/*
 * Display a basic texture made of 4 pixels.
 * Partially inspired by
 * http://en.wikibooks.org/wiki/OpenGL_Programming/Modern_OpenGL_Tutorial_06
 */
class OGLExampleTexture1 : public OGLExample {
public:
    ~OGLExampleTexture1();
    
    void init(const void *);
    void renderForTime(const CVTimeStamp *);
    void didUpdateWindowRect(NSRect);
    std::string name();

private:
    GLuint _programID;
    GLuint _vertexArrayObjectName;
    GLuint _vertexBufferObjectName[3]; // 0 vertex and 1 texture coordinate,3EBO
//    GLuint _textureBufferObjectName;
    GLuint _positionAttrib,_textureAttrib;
};
////////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////////////
// OGLExampleTexture2                                                         //
////////////////////////////////////////////////////////////////////////////////

/*
 * how to load a (Bitmap) texture,
 * how to reverse texture coordinate in fragment
 * ...
 */
class OGLExampleTexture2 : public OGLExample {
public:
    ~OGLExampleTexture2();
    
    void init(const void *);
    void renderForTime(const CVTimeStamp *);
    void didUpdateWindowRect(NSRect);
    std::string name();

private:
    GLuint _programID;
    GLuint _vertexArrayObjectName;
    GLuint _vertexBufferObjectName;
    GLuint _elementBufferObjectName;
    GLuint _textureBufferObjectName;
    GLuint _positionAttrib,_textureAttrib;
};
////////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////////////
// OGLExampleTexture3                                                         //
////////////////////////////////////////////////////////////////////////////////

/*
 * OGLExampleTexture2 with corrections :
 * - texture reversed (im the fragment shader)
 * - right color (replace the color format from GL_RGB to GL_BGR)
 */
class OGLExampleTexture3 : public OGLExample {
public:
    ~OGLExampleTexture3();
    
    void init(const void *);
    void renderForTime(const CVTimeStamp *);
    void didUpdateWindowRect(NSRect);
    std::string name();

private:
    GLuint _programID;
    GLuint _vertexArrayObjectName;
    GLuint _vertexBufferObjectName;
    GLuint _elementBufferObjectName;
    GLuint _textureBufferObjectName;
    GLuint _positionAttrib,_textureAttrib;
};
////////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////////////
// OGLExampleTexture4                                                         //
////////////////////////////////////////////////////////////////////////////////

/*
 * Pretty much the same as OGLExampleTexture3 except we use
 * GLKit to load our texture AND
 * we blend the texture with the color gradient
 *  -------------------
 *  |  red     green  |
 *  |  white   blue   |
 *  -------------------
 */
class OGLExampleTexture4 : public OGLExample {
public:
    ~OGLExampleTexture4();
    
    void init(const void *);
    void renderForTime(const CVTimeStamp *);
    void didUpdateWindowRect(NSRect);
    std::string name();

private:
    GLuint _programID;
    GLuint _vertexArrayObjectName;
    GLuint _vertexBufferObjectName;
    GLuint _elementBufferObjectName;
    GLuint _textureBufferObjectName;
    GLuint _positionAttrib,_colorAttrib,_textureAttrib;
};
////////////////////////////////////////////////////////////////////////////////
#endif /* defined(__OpenGLTutorial__OGLExample__) */
