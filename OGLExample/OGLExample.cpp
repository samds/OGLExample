//
//  OGLExampleColor.cpp
//  OpenGLExample
//
//  Created by samuel de santis on 26/08/2014.
//  Copyright (c) 2014 Samuel DE SANTIS. All rights reserved.
//

#include "OGLExample.h"
#include <OGLUIKit/OGLUIKit.h>

#include <vector>
#include <string>
#include <fstream>


////////////////////////////////////////////////////////////////////////////////
// OGLExample                                                                 //
////////////////////////////////////////////////////////////////////////////////

//OGLExample::~OGLExample() = default;

////////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////////////
// OGLExampleColor                                                            //
////////////////////////////////////////////////////////////////////////////////

OGLExampleColor::OGLExampleColor()
{
    _r = 0.0f;
    _g = 0.0f;
    _b = 0.0f;
    _a = 1.0f;
}

void OGLExampleColor::init(const void* arg)
{
    glDisable(GL_BLEND);
    glDisable(GL_CULL_FACE);
    glDisable(GL_DEPTH_TEST);
    glDisable(GL_LINE_SMOOTH);
    glDisable(GL_SCISSOR_TEST);
    GetGLError();
    
    glClearColor(_r,_g,_b,_a);
    GetGLError();
}

void OGLExampleColor::renderForTime(const CVTimeStamp * outputTime)
{
    glClear(GL_COLOR_BUFFER_BIT);
    GetGLError();
}

void OGLExampleColor::didUpdateWindowRect(NSRect rect)
{
    
}

void OGLExampleColor::setColor(float r,float g,float b,float a)
{
    _r = r;
    _g = g;
    _b = b;
    _a = a;
    glClearColor(r,g,b,a);
    GetGLError();
}

////////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////////////
// OGLExampleTriangle                                                         //
////////////////////////////////////////////////////////////////////////////////

void OGLExampleTriangle::init(const void* arg)
{
    glDisable(GL_BLEND);
    glDisable(GL_CULL_FACE);
    glDisable(GL_LINE_SMOOTH);
    glDisable(GL_SCISSOR_TEST);
    glDisable(GL_DEPTH_TEST);
    GetGLError();

    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    GetGLError();
    
    glGenVertexArrays(1, &_vertexArrayObjectName);
    GetGLError();
    glBindVertexArray(_vertexArrayObjectName);
    GetGLError();

    NSString *vhs = [[NSBundle mainBundle] pathForResource:@"RedTriangle"
                                                    ofType:@"vsh"];
    NSString *fhs = [[NSBundle mainBundle] pathForResource:@"RedTriangle"
                                                    ofType:@"fsh"];
    _programID = loadShaders(vhs.UTF8String,fhs.UTF8String);
    GetGLError();

    vhs = nil;
    fhs = nil;
}

void OGLExampleTriangle::renderForTime(const CVTimeStamp * outputTime)
{
//    glClear(GL_COLOR_BUFFER_BIT);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    GetGLError();
    
    // Use our shader
    glUseProgram(_programID);
    
    // An array of 3 vectors which represents 3 vertices
    static const GLfloat vertex_data[] = {
        -1.0f, -1.0f, 0.0f,
        1.0f, -1.0f, 0.0f,
        0.0f,  1.0f, 0.0f,
    };
    
    ///////////////////
    // Draw triangle //
    ///////////////////
    
    // This will identify our vertex buffer
    GLuint vertexbuffer;
    
    // Generate 1 buffer, put the resulting identifier in vertexbuffer
    glGenBuffers(1, &vertexbuffer);
    
    // The following commands will talk about our 'vertexbuffer' buffer
    glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
    
    // Give our vertices to OpenGL.
    GLsizeiptr size = sizeof(vertex_data);
    glBufferData(GL_ARRAY_BUFFER, size, vertex_data, GL_STATIC_DRAW);
    
    // 1rst attribute buffer : vertices
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
    glVertexAttribPointer(
                          0,                  // attribute 0. No particular
                                              // reason for 0, but must match
                                              // the layout in the shader.
                          3,                  // size
                          GL_FLOAT,           // type
                          GL_FALSE,           // normalized?
                          0,                  // stride
                          (void*)0            // array buffer offset
                          );
    
    /*
     * Draw the triangle !
     * Starting from vertex 0.
     * 3 vertices total -> 1 triangle
     */
    glDrawArrays(GL_TRIANGLES, 0, 3);
    
    glDisableVertexAttribArray(0);
    
    // Delete buffer
    glDeleteBuffers(1, &vertexbuffer);
}

void OGLExampleTriangle::didUpdateWindowRect(NSRect rect)
{
    glViewport(rect.origin.x, rect.origin.y, rect.size.width, rect.size.height);
}

void OGLExampleTriangle::setColor(float r,float g,float b,float a)
{
    glClearColor(r,g,b,a);
    GetGLError();
}

OGLExampleTriangle::~OGLExampleTriangle()
{
    glDeleteVertexArrays(1, &_vertexArrayObjectName);
    GetGLError();
}

////////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////////////
// OGLExampleScissor                                                          //
////////////////////////////////////////////////////////////////////////////////

OGLExampleScissor::OGLExampleScissor()
{
    _x = 0;
    _y = 0;
    _width = 0;
    _height = 0;
}

/*
 * Do not forget to enable "GL_SCISSOR_TEST"!
 */
void OGLExampleScissor::init(const void* arg)
{
    glDisable(GL_BLEND);
    glDisable(GL_CULL_FACE);
    glDisable(GL_DEPTH_TEST);
    glDisable(GL_LINE_SMOOTH);
    GetGLError();

    glEnable(GL_SCISSOR_TEST);
    GetGLError();
}

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
void OGLExampleScissor::renderForTime(const CVTimeStamp * outputTime)
{
    glViewport(0, 0, _width, _height);
    
    div_t halfWidth = div(_width, 2);
    div_t halfHeight = div(_height, 2);
    
    GLint x1,x2,x3,y1,y2,y3;
    GLsizei w1,w2,w3,h1,h2,h3;
    
    x1 = 0;                     y1 = halfHeight.quot;
    x2 = halfWidth.quot;        y2 = halfHeight.quot;
    x3 = 0;                     y3 = 0;
    w1 = halfWidth.quot;        h1 = halfHeight.quot + halfHeight.rem;
    w2 = w1 + halfWidth.rem;    h2 = halfHeight.quot + halfHeight.rem;
    w3 = _width;                h3 = halfHeight.quot;
    
    glScissor(x1, y1, w1, h1);
    glClearColor(1.0f,0.0f,0.0f,1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    GetGLError();
    
    glScissor(x2, y2, w2, h2);
    glClearColor(0.0f,1.0f,0.0f,1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    GetGLError();
    
    glScissor(x3, y3, w3, h3);
    glClearColor(0.0f,0.0f,1.0f,1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    GetGLError();
}

void OGLExampleScissor::didUpdateWindowRect(NSRect rect)
{
    _x = (GLint)rect.origin.x;
    _y = (GLint)rect.origin.y;
    _width = (GLsizei)rect.size.width;
    _height = (GLsizei)rect.size.height;
}

////////////////////////////////////////////////////////////////////////////////