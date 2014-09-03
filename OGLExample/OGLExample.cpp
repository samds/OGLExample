//
//  OGLExampleColor.cpp
//  OpenGLExample
//
//  Created by samuel de santis on 26/08/2014.
//  Copyright (c) 2014 Samuel DE SANTIS. All rights reserved.
//

#include "OGLExample.h"
#include <OGLUIKit/OGLUIKit.h>
#include <GLKit/GLKTextureLoader.h>

#include <vector>
#include <string>
#include <fstream>
#include "LoadBitmap.h"

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
    glGenVertexArrays(1, &_vertexArrayObjectName);
    GetGLError();
    glBindVertexArray(_vertexArrayObjectName);
    GetGLError();
    
    glDisable(GL_BLEND);
    glDisable(GL_CULL_FACE);
    glDisable(GL_LINE_SMOOTH);
    glDisable(GL_SCISSOR_TEST);
    glDisable(GL_DEPTH_TEST);
    GetGLError();

    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    GetGLError();

    NSString *vhs = [[NSBundle mainBundle] pathForResource:@"RedTriangle"
                                                    ofType:@"vsh"];
    NSString *fhs = [[NSBundle mainBundle] pathForResource:@"RedTriangle"
                                                    ofType:@"fsh"];
    _programID = loadShaders(vhs.UTF8String,fhs.UTF8String);
    GetGLError();

    vhs = nil;
    fhs = nil;
    
    // Unbind VAO
    glBindVertexArray(0);
    GetGLError();
}

void OGLExampleTriangle::renderForTime(const CVTimeStamp * outputTime)
{
    glBindVertexArray(_vertexArrayObjectName);
    GetGLError();
    
    glClear(GL_COLOR_BUFFER_BIT);
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
    
    // Unbind VAO
    glBindVertexArray(0);
    GetGLError();
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
// OGLExampleTriangle3                                                        //
////////////////////////////////////////////////////////////////////////////////

void OGLExampleTriangle3::init(const void* arg)
{
    ///////////////////
    // Create VAO    //
    ///////////////////
    
    // Create and Bind VAO
    glGenVertexArrays(1, &_vertexArrayObjectName);
    GetGLError();
    glBindVertexArray(_vertexArrayObjectName);
    GetGLError();
    
    ///////////////////
    // Create VBO    //
    ///////////////////
    
    // An array of 3 vectors which represents 3 vertices
    static const GLfloat vertex_data[] = {
        -0.5f, -0.5f, 0.0f,
        0.5f, -0.5f, 0.0f,
        0.0f,  0.5f, 0.0f
    };
    
    // Generate 1 buffer, put the resulting identifier in vertexbuffer
    glGenBuffers(1, &_vertexBufferObjectName);
    // The following commands will talk about our 'vertexbuffer' buffer
    glBindBuffer(GL_ARRAY_BUFFER, _vertexBufferObjectName);
    // Give our vertices to OpenGL.
    GLsizeiptr size = sizeof(vertex_data);
    glBufferData(GL_ARRAY_BUFFER, size, vertex_data, GL_STATIC_DRAW);

    ///////////////////
    // Others        //
    ///////////////////
    
    glDisable(GL_BLEND);
    glDisable(GL_CULL_FACE);
    glDisable(GL_LINE_SMOOTH);
    glDisable(GL_SCISSOR_TEST);
    glDisable(GL_DEPTH_TEST);
    GetGLError();
    
    ///////////////////
    // Load Shaders  //
    ///////////////////
    
    NSString *vhs = [[NSBundle mainBundle] pathForResource:@"RedTriangle"
                                                    ofType:@"vsh"];
    NSString *fhs = [[NSBundle mainBundle] pathForResource:@"TriangleUniformColor"
                                                    ofType:@"fsh"];
    _programID = loadShaders(vhs.UTF8String,fhs.UTF8String);
    GetGLError();
    
    // Free memory
    vhs = nil;
    fhs = nil;
    
    ////////////////////////////////
    // Draw into the back buffer  //
    ////////////////////////////////
    
    // Use our shader
    glUseProgram(_programID);
    
    // Specify the layout of the vertex data
    _indexAttrib = glGetAttribLocation(_programID, "position");
    glVertexAttribPointer(
                          _indexAttrib,       // attribute 0. No particular
                                              // reason for 0, but must match
                                              // the layout in the shader.
                          3,                  // size
                          GL_FLOAT,           // type
                          GL_FALSE,           // normalized?
                          0,                  // stride
                          (void*)0            // array buffer offset
                          );
    
    // Set the color
    GLint uniColor = glGetUniformLocation(_programID, "triangleColor");
    glUniform3f(uniColor, 0.2f, 1.0f, 0.5f);

    // Unbind VAO
    glBindVertexArray(0);
    GetGLError();
}

void OGLExampleTriangle3::renderForTime(const CVTimeStamp * outputTime)
{
    // Bind VAO
    glBindVertexArray(_vertexArrayObjectName);
    GetGLError();
    
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    GetGLError();
    glClear(GL_COLOR_BUFFER_BIT);
    GetGLError();

    /*
     * Draw the triangle !
     * Starting from vertex 0.
     * 3 vertices total -> 1 triangle
     */
    glEnableVertexAttribArray(_indexAttrib);
    glDrawArrays(GL_TRIANGLES, 0, 3);
    glDisableVertexAttribArray(_indexAttrib);

    // Unbind VAO
    glBindVertexArray(0);
    GetGLError();
}

void OGLExampleTriangle3::didUpdateWindowRect(NSRect rect)
{
    glViewport(rect.origin.x, rect.origin.y, rect.size.width, rect.size.height);
}

void OGLExampleTriangle3::setColor(float r,float g,float b,float a)
{
    glClearColor(r,g,b,a);
    GetGLError();
}

OGLExampleTriangle3::~OGLExampleTriangle3()
{
    ////////////////////////////////
    // Free the memory            //
    ////////////////////////////////
    
    // Bind VAO
    glBindVertexArray(_vertexArrayObjectName);
    GetGLError();
    
    // Unbind VBO
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    GetGLError();
    
    // Delete VBO
    glDeleteBuffers(1, &_vertexBufferObjectName);
    GetGLError();

    // Delete shader program
    glDeleteProgram(_programID);
    GetGLError();
    
    // Unbind VAO
    glBindVertexArray(0);
    GetGLError();
    
    // Delete VAO
    glDeleteVertexArrays(1, &_vertexArrayObjectName);
    GetGLError();
}

////////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////////////
// OGLExampleTriangle2                                                        //
////////////////////////////////////////////////////////////////////////////////

void OGLExampleTriangle2::init(const void* arg)
{
    ///////////////////
    // Create VAO    //
    ///////////////////
    
    // Create and Bind VAO
    glGenVertexArrays(1, &_vertexArrayObjectName);
    GetGLError();
    glBindVertexArray(_vertexArrayObjectName);
    GetGLError();
    
    ///////////////////
    // Create VBO    //
    ///////////////////
    
    // An array of 3 vectors which represents 3 vertices
    static const GLfloat vertex_data[] = {
        -0.5f, -0.5f, 0.0f,
        0.5f, -0.5f, 0.0f,
        0.0f,  0.5f, 0.0f
    };
    
    // Generate 1 buffer, put the resulting identifier in vertexbuffer
    glGenBuffers(1, &_vertexBufferObjectName);
    // The following commands will talk about our 'vertexbuffer' buffer
    glBindBuffer(GL_ARRAY_BUFFER, _vertexBufferObjectName);
    // Give our vertices to OpenGL.
    GLsizeiptr size = sizeof(vertex_data);
    glBufferData(GL_ARRAY_BUFFER, size, vertex_data, GL_STATIC_DRAW);
    
    ///////////////////
    // Others        //
    ///////////////////
    
    glDisable(GL_BLEND);
    glDisable(GL_CULL_FACE);
    glDisable(GL_LINE_SMOOTH);
    glDisable(GL_SCISSOR_TEST);
    glDisable(GL_DEPTH_TEST);
    GetGLError();
    
    ///////////////////
    // Load Shaders  //
    ///////////////////
    
    NSString *vhs = [[NSBundle mainBundle] pathForResource:@"RedTriangle"
                                                    ofType:@"vsh"];
    NSString *fhs = [[NSBundle mainBundle] pathForResource:@"RedTriangle"
                                                    ofType:@"fsh"];
    _programID = loadShaders(vhs.UTF8String,fhs.UTF8String);
    GetGLError();
    
    // Free memory
    vhs = nil;
    fhs = nil;
    
    ////////////////////////////////
    // Draw into the back buffer  //
    ////////////////////////////////
    
    // Use our shader
    glUseProgram(_programID);
    
    // Specify the layout of the vertex data
    _indexAttrib = glGetAttribLocation(_programID, "position");
    glVertexAttribPointer(
                          _indexAttrib,       // attribute index
                          3,                  // size
                          GL_FLOAT,           // type
                          GL_FALSE,           // normalized?
                          0,                  // stride
                          (void*)0            // array buffer offset
                          );
    
    // Unbind VAO
    glBindVertexArray(0);
    GetGLError();
}

void OGLExampleTriangle2::renderForTime(const CVTimeStamp * outputTime)
{
    // Bind VAO
    glBindVertexArray(_vertexArrayObjectName);
    GetGLError();
    
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    GetGLError();
    glClear(GL_COLOR_BUFFER_BIT);
    GetGLError();
    
    /*
     * Draw the triangle !
     * Starting from vertex 0.
     * 3 vertices total -> 1 triangle
     */
    glEnableVertexAttribArray(_indexAttrib);
    glDrawArrays(GL_TRIANGLES, 0, 3);
    glDisableVertexAttribArray(_indexAttrib);
    
    // Unbind VAO
    glBindVertexArray(0);
    GetGLError();
}

void OGLExampleTriangle2::didUpdateWindowRect(NSRect rect)
{
    glViewport(rect.origin.x, rect.origin.y, rect.size.width, rect.size.height);
}

void OGLExampleTriangle2::setColor(float r,float g,float b,float a)
{
    glClearColor(r,g,b,a);
    GetGLError();
}

OGLExampleTriangle2::~OGLExampleTriangle2()
{
    ////////////////////////////////
    // Free the memory            //
    ////////////////////////////////
    
    // Bind VAO
    glBindVertexArray(_vertexArrayObjectName);
    GetGLError();
    
    // Unbind VBO
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    GetGLError();
    
    // Delete VBO
    glDeleteBuffers(1, &_vertexBufferObjectName);
    GetGLError();
    
    // Delete shader program
    glDeleteProgram(_programID);
    GetGLError();
    
    // Unbind VAO
    glBindVertexArray(0);
    GetGLError();
    
    // Delete VAO
    glDeleteVertexArrays(1, &_vertexArrayObjectName);
    GetGLError();
}

////////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////////////
// OGLExampleTriangle4                                                        //
////////////////////////////////////////////////////////////////////////////////

void OGLExampleTriangle4::init(const void* arg)
{
    ///////////////////
    // Create VAO    //
    ///////////////////
    
    // Create and Bind VAO
    glGenVertexArrays(1, &_vertexArrayObjectName);
    GetGLError();
    glBindVertexArray(_vertexArrayObjectName);
    GetGLError();
    
    ///////////////////
    // Create VBO    //
    ///////////////////
    
    // An array of 3 vectors which represents 3 vertices
    static const GLfloat vertex_data[] = {
        0.0f,  0.5f,  1.0f,  0.0f,  0.0f,
        0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
       -0.5f, -0.5f,  0.0f,  0.0f,  1.0f
    };

    // Generate 1 buffer, put the resulting identifier in vertexbuffer
    glGenBuffers(1, &_vertexBufferObjectName);
    // The following commands will talk about our 'vertexbuffer' buffer
    glBindBuffer(GL_ARRAY_BUFFER, _vertexBufferObjectName);
    // Give our vertices to OpenGL.
    GLsizeiptr size = sizeof(vertex_data);
    glBufferData(GL_ARRAY_BUFFER, size, vertex_data, GL_STATIC_DRAW);
    
    ///////////////////
    // Others        //
    ///////////////////
    
    glDisable(GL_BLEND);
    glDisable(GL_CULL_FACE);
    glDisable(GL_LINE_SMOOTH);
    glDisable(GL_SCISSOR_TEST);
    glDisable(GL_DEPTH_TEST);
    GetGLError();
    
    ///////////////////
    // Load Shaders  //
    ///////////////////
    
    NSString *vhs = [[NSBundle mainBundle] pathForResource:@"TriangleDynColor"
                                                    ofType:@"vsh"];
    NSString *fhs = [[NSBundle mainBundle] pathForResource:@"TriangleDynColor"
                                                    ofType:@"fsh"];
    _programID = loadShaders(vhs.UTF8String,fhs.UTF8String);
    GetGLError();
    
    // Free memory
    vhs = nil;
    fhs = nil;
    
    ////////////////////////////////
    // Draw into the back buffer  //
    ////////////////////////////////
    
    // Use our shader
    glUseProgram(_programID);
    
    // Specify the layout of the vertex data
    _positionAttrib = glGetAttribLocation(_programID, "inPosition");
    glEnableVertexAttribArray(_positionAttrib);
    glVertexAttribPointer(
                          _positionAttrib,    // attribute index
                          2,                  // size
                          GL_FLOAT,           // type
                          GL_FALSE,           // normalized?
                          5*sizeof(GLfloat),  // stride
                          BUFFER_OFFSET(0)    // array buffer offset
                          );
    
    _colorAttrib = glGetAttribLocation(_programID, "inColor");
    glEnableVertexAttribArray(_colorAttrib);
    glVertexAttribPointer(_colorAttrib,
                          3,
                          GL_FLOAT,
                          GL_FALSE,
                          5*sizeof(float),
                          BUFFER_OFFSET(2*sizeof(GLfloat))
                          );
    
    // Unbind VAO
    glBindVertexArray(0);
    GetGLError();
}

void OGLExampleTriangle4::renderForTime(const CVTimeStamp * outputTime)
{
    // Bind VAO
    glBindVertexArray(_vertexArrayObjectName);
    GetGLError();
    
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    GetGLError();
    glClear(GL_COLOR_BUFFER_BIT);
    GetGLError();
    
    /*
     * Draw the triangle !
     * Starting from vertex 0.
     * 3 vertices total -> 1 triangle
     */
    glDrawArrays(GL_TRIANGLES, 0, 3);
    
    // Unbind VAO
    glBindVertexArray(0);
    GetGLError();
}

void OGLExampleTriangle4::didUpdateWindowRect(NSRect rect)
{
    glViewport(rect.origin.x, rect.origin.y, rect.size.width, rect.size.height);
}

void OGLExampleTriangle4::setColor(float r,float g,float b,float a)
{
    glClearColor(r,g,b,a);
    GetGLError();
}

OGLExampleTriangle4::~OGLExampleTriangle4()
{
    ////////////////////////////////
    // Free the memory            //
    ////////////////////////////////
    
    // Bind VAO
    glBindVertexArray(_vertexArrayObjectName);
    GetGLError();
    
    glDisableVertexAttribArray(_positionAttrib);
    glDisableVertexAttribArray(_colorAttrib);
    
    // Unbind VBO
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    GetGLError();
    
    // Delete VBO
    glDeleteBuffers(1, &_vertexBufferObjectName);
    GetGLError();
    
    // Delete shader program
    glDeleteProgram(_programID);
    GetGLError();
    
    // Unbind VAO
    glBindVertexArray(0);
    GetGLError();
    
    // Delete VAO
    glDeleteVertexArrays(1, &_vertexArrayObjectName);
    GetGLError();
}

////////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////////////
// OGLExampleSquare                                                           //
////////////////////////////////////////////////////////////////////////////////

void OGLExampleSquare::init(const void* arg)
{
    ///////////////////
    // Create VAO    //
    ///////////////////
    
    // Create and Bind VAO
    glGenVertexArrays(1, &_vertexArrayObjectName);
    GetGLError();
    glBindVertexArray(_vertexArrayObjectName);
    GetGLError();
    
    ///////////////////
    // Create VBO    //
    ///////////////////
    
    // An array of 3 vectors which represents 3 vertices
    static const GLfloat vertex_data[] = {
        -0.5f,  0.5f, 1.0f, 0.0f, 0.0f, // Top-left
         0.5f,  0.5f, 0.0f, 1.0f, 0.0f, // Top-right
         0.5f, -0.5f, 0.0f, 0.0f, 1.0f, // Bottom-right
        
         0.5f, -0.5f, 0.0f, 0.0f, 1.0f, // Bottom-right
        -0.5f, -0.5f, 1.0f, 1.0f, 1.0f, // Bottom-left
        -0.5f,  0.5f, 1.0f, 0.0f, 0.0f  // Top-left
    };
    
    // Generate 1 buffer, put the resulting identifier in vertexbuffer
    glGenBuffers(1, &_vertexBufferObjectName);
    // The following commands will talk about our 'vertexbuffer' buffer
    glBindBuffer(GL_ARRAY_BUFFER, _vertexBufferObjectName);
    // Give our vertices to OpenGL.
    GLsizeiptr size = sizeof(vertex_data);
    glBufferData(GL_ARRAY_BUFFER, size, vertex_data, GL_STATIC_DRAW);
    
    ///////////////////
    // Others        //
    ///////////////////
    
    glDisable(GL_BLEND);
    glDisable(GL_CULL_FACE);
    glDisable(GL_LINE_SMOOTH);
    glDisable(GL_SCISSOR_TEST);
    glDisable(GL_DEPTH_TEST);
    GetGLError();
    
    ///////////////////
    // Load Shaders  //
    ///////////////////
    
    NSString *vhs = [[NSBundle mainBundle] pathForResource:@"TriangleDynColor"
                                                    ofType:@"vsh"];
    NSString *fhs = [[NSBundle mainBundle] pathForResource:@"TriangleDynColor"
                                                    ofType:@"fsh"];
    _programID = loadShaders(vhs.UTF8String,fhs.UTF8String);
    GetGLError();
    
    // Free memory
    vhs = nil;
    fhs = nil;
    
    ////////////////////////////////
    // Draw into the back buffer  //
    ////////////////////////////////
    
    // Use our shader
    glUseProgram(_programID);
    
    // Specify the layout of the vertex data
    _positionAttrib = glGetAttribLocation(_programID, "inPosition");
    glEnableVertexAttribArray(_positionAttrib);
    glVertexAttribPointer(
                          _positionAttrib,    // attribute index
                          2,                  // size
                          GL_FLOAT,           // type
                          GL_FALSE,           // normalized?
                          5*sizeof(GLfloat),  // stride
                          BUFFER_OFFSET(0)    // array buffer offset
                          );
    
    _colorAttrib = glGetAttribLocation(_programID, "inColor");
    glEnableVertexAttribArray(_colorAttrib);
    glVertexAttribPointer(_colorAttrib,
                          3,
                          GL_FLOAT,
                          GL_FALSE,
                          5*sizeof(float),
                          BUFFER_OFFSET(2*sizeof(GLfloat))
                          );
    
    // Unbind VAO
    glBindVertexArray(0);
    GetGLError();
}

void OGLExampleSquare::renderForTime(const CVTimeStamp * outputTime)
{
    // Bind VAO
    glBindVertexArray(_vertexArrayObjectName);
    GetGLError();
    
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    GetGLError();
    glClear(GL_COLOR_BUFFER_BIT);
    GetGLError();
    
    /*
     * Draw the triangle !
     * Starting from vertex 0.
     * 3 vertices total -> 1 triangle
     */
    glDrawArrays(GL_TRIANGLES, 0, 6);
    
    // Unbind VAO
    glBindVertexArray(0);
    GetGLError();
}

void OGLExampleSquare::didUpdateWindowRect(NSRect rect)
{
    glViewport(rect.origin.x, rect.origin.y, rect.size.width, rect.size.height);
}

void OGLExampleSquare::setColor(float r,float g,float b,float a)
{
    glClearColor(r,g,b,a);
    GetGLError();
}

OGLExampleSquare::~OGLExampleSquare()
{
    ////////////////////////////////
    // Free the memory            //
    ////////////////////////////////
    
    // Bind VAO
    glBindVertexArray(_vertexArrayObjectName);
    GetGLError();
    
    glDisableVertexAttribArray(_positionAttrib);
    glDisableVertexAttribArray(_colorAttrib);
    
    // Unbind VBO
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    GetGLError();
    
    // Delete VBO
    glDeleteBuffers(1, &_vertexBufferObjectName);
    GetGLError();
    
    // Delete shader program
    glDeleteProgram(_programID);
    GetGLError();
    
    // Unbind VAO
    glBindVertexArray(0);
    GetGLError();
    
    // Delete VAO
    glDeleteVertexArrays(1, &_vertexArrayObjectName);
    GetGLError();
}

////////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////////////
// OGLExampleSquare2                                                          //
////////////////////////////////////////////////////////////////////////////////

void OGLExampleSquare2::init(const void* arg)
{
    ///////////////////
    // Create VAO    //
    ///////////////////
    
    // Create and Bind VAO
    glGenVertexArrays(1, &_vertexArrayObjectName);
    GetGLError();
    glBindVertexArray(_vertexArrayObjectName);
    GetGLError();
    
    ///////////////////
    // Create VBO    //
    ///////////////////
    
    // An array of 3 vectors which represents 3 vertices
    static const GLfloat vertex_data[] = {
        -0.5f,  0.5f, 1.0f, 0.0f, 0.0f, // Top-left
         0.5f,  0.5f, 0.0f, 1.0f, 0.0f, // Top-right
         0.5f, -0.5f, 0.0f, 0.0f, 1.0f, // Bottom-right
        -0.5f, -0.5f, 1.0f, 1.0f, 1.0f, // Bottom-left
    };
    
    // Generate 1 buffer, put the resulting identifier in vertexbuffer
    glGenBuffers(1, &_vertexBufferObjectName);
    // The following commands will talk about our 'vertexbuffer' buffer
    glBindBuffer(GL_ARRAY_BUFFER, _vertexBufferObjectName);
    // Give our vertices to OpenGL.
    GLsizeiptr size = sizeof(vertex_data);
    glBufferData(GL_ARRAY_BUFFER, size, vertex_data, GL_STATIC_DRAW);
    
    ///////////////////
    // Others        //
    ///////////////////
    
    glDisable(GL_BLEND);
    glDisable(GL_CULL_FACE);
    glDisable(GL_LINE_SMOOTH);
    glDisable(GL_SCISSOR_TEST);
    glDisable(GL_DEPTH_TEST);
    GetGLError();
    
    ///////////////////
    // Load Shaders  //
    ///////////////////
    
    NSString *vhs = [[NSBundle mainBundle] pathForResource:@"TriangleDynColor"
                                                    ofType:@"vsh"];
    NSString *fhs = [[NSBundle mainBundle] pathForResource:@"TriangleDynColor"
                                                    ofType:@"fsh"];
    _programID = loadShaders(vhs.UTF8String,fhs.UTF8String);
    GetGLError();
    
    // Free memory
    vhs = nil;
    fhs = nil;
    
    //////////////////////////////////
    // Create Element Buffer Object //
    //////////////////////////////////
    
    GLuint elements[] = {
        0, 1, 2,
        2, 3, 0
    };
    
    glGenBuffers(1, &_elementBufferObjectName);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _elementBufferObjectName);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER,
                 sizeof(elements),
                 elements,
                 GL_STATIC_DRAW
                 );
    
    ////////////////////////////////
    // Draw into the back buffer  //
    ////////////////////////////////
    
    // Use our shader
    glUseProgram(_programID);
    
    // Specify the layout of the vertex data
    _positionAttrib = glGetAttribLocation(_programID, "inPosition");
    glEnableVertexAttribArray(_positionAttrib);
    glVertexAttribPointer(
                          _positionAttrib,    // attribute index
                          2,                  // size
                          GL_FLOAT,           // type
                          GL_FALSE,           // normalized?
                          5*sizeof(GLfloat),  // stride
                          BUFFER_OFFSET(0)    // array buffer offset
                          );
    
    _colorAttrib = glGetAttribLocation(_programID, "inColor");
    glEnableVertexAttribArray(_colorAttrib);
    glVertexAttribPointer(_colorAttrib,
                          3,
                          GL_FLOAT,
                          GL_FALSE,
                          5*sizeof(float),
                          BUFFER_OFFSET(2*sizeof(GLfloat))
                          );
    
    // Unbind VAO
    glBindVertexArray(0);
    GetGLError();
}

void OGLExampleSquare2::renderForTime(const CVTimeStamp * outputTime)
{
    // Bind VAO
    glBindVertexArray(_vertexArrayObjectName);
    GetGLError();
    
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    GetGLError();
    glClear(GL_COLOR_BUFFER_BIT);
    GetGLError();
    
    // Draw the square ( 2 triangles )
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    
    // Unbind VAO
    glBindVertexArray(0);
    GetGLError();
}

void OGLExampleSquare2::didUpdateWindowRect(NSRect rect)
{
    glViewport(rect.origin.x, rect.origin.y, rect.size.width, rect.size.height);
}

void OGLExampleSquare2::setColor(float r,float g,float b,float a)
{
    glClearColor(r,g,b,a);
    GetGLError();
}

OGLExampleSquare2::~OGLExampleSquare2()
{
    ////////////////////////////////
    // Free the memory            //
    ////////////////////////////////
    
    // Bind VAO
    glBindVertexArray(_vertexArrayObjectName);
    GetGLError();
    
    glDisableVertexAttribArray(_positionAttrib);
    glDisableVertexAttribArray(_colorAttrib);
    
    // Delete EBO
    glDeleteBuffers(1, &_elementBufferObjectName);
    GetGLError();
    
    // Unbind VBO
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    GetGLError();
    
    // Delete VBO
    glDeleteBuffers(1, &_vertexBufferObjectName);
    GetGLError();
    
    // Delete shader program
    glDeleteProgram(_programID);
    GetGLError();
    
    // Unbind VAO
    glBindVertexArray(0);
    GetGLError();
    
    // Delete VAO
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
 *
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


////////////////////////////////////////////////////////////////////////////////
// OGLExampleTexture1                                                         //
////////////////////////////////////////////////////////////////////////////////

void OGLExampleTexture1::init(const void* arg)
{
    ///////////////////
    // Create VAO    //
    ///////////////////
    
    // Create and Bind VAO
    glGenVertexArrays(1, &_vertexArrayObjectName);
    GetGLError();
    glBindVertexArray(_vertexArrayObjectName);
    GetGLError();
    
    ///////////////////
    // Others        //
    ///////////////////
    
    glDisable(GL_BLEND);
    glDisable(GL_CULL_FACE);
    glDisable(GL_LINE_SMOOTH);
    glDisable(GL_SCISSOR_TEST);
    glDisable(GL_DEPTH_TEST);
    GetGLError();
    
    ///////////////////
    // Create VBO    //
    ///////////////////
    
    // Generate 1 buffer, put the resulting identifier in vertexbuffer
    glGenBuffers(3, _vertexBufferObjectName);
    GetGLError();
    
    // Vertices
    static const GLfloat vertex_data[] = {
        -1.0f,  1.0f, // Top-left
         1.0f,  1.0f, // Top-right
         1.0f, -1.0f, // Bottom-right
        -1.0f, -1.0f, // Bottom-left
    };
    
    // Bind our vertices
    glBindBuffer(GL_ARRAY_BUFFER, _vertexBufferObjectName[0]);
    GetGLError();
    // Give our vertices to OpenGL.
    glBufferData(GL_ARRAY_BUFFER,
                 sizeof(vertex_data),
                 vertex_data,
                 GL_STATIC_DRAW
                 );
    GetGLError();
    
    // Texture coordinate
    static const GLfloat textureCoor_data[] = {
        0.0f, 0.0f, // Top-left
        1.0f, 0.0f, // Top-right
        1.0f, 1.0f, // Bottom-right
        0.0f, 1.0f  // Bottom-left
    };
    
    // Bind the texture coordinates
    glBindBuffer(GL_ARRAY_BUFFER, _vertexBufferObjectName[1]);
    GetGLError();
    // Give the coordinates to OpenGL.
    glBufferData(GL_ARRAY_BUFFER,
                 sizeof(textureCoor_data),
                 textureCoor_data,
                 GL_STATIC_DRAW
                 );
    GetGLError();
    
    // Element Buffer Object
    GLuint elements[] = {
        0, 1, 2,
        2, 3, 0
    };
    
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _vertexBufferObjectName[2]);
    GetGLError();
    glBufferData(GL_ELEMENT_ARRAY_BUFFER,
                 sizeof(elements),
                 elements,
                 GL_STATIC_DRAW
                 );
    GetGLError();
    
    ///////////////////
    // Load Shaders  //
    ///////////////////
    
    NSString *vhs = [[NSBundle mainBundle] pathForResource:@"Texture1"
                                                    ofType:@"vsh"];
    NSString *fhs = [[NSBundle mainBundle] pathForResource:@"Texture1"
                                                    ofType:@"fsh"];
    _programID = loadShaders(vhs.UTF8String,fhs.UTF8String);
    GetGLError();
    
    // Free memory
    vhs = nil;
    fhs = nil;
    
    ////////////////////////////////////////////
    // Specify the layout of the vertex data  //
    ////////////////////////////////////////////
    
    // Use our shader
    glUseProgram(_programID);
    GetGLError();
    
    _positionAttrib = glGetAttribLocation(_programID, "inPosition");
    GetGLError();
    glEnableVertexAttribArray(_positionAttrib);
    GetGLError();
    glBindBuffer(GL_ARRAY_BUFFER, _vertexBufferObjectName[0]);
    GetGLError();
    glVertexAttribPointer(
                          _positionAttrib,    // attribute index
                          2,                  // size
                          GL_FLOAT,           // type
                          GL_FALSE,           // normalized?
                          0,                  // stride
                          BUFFER_OFFSET(0)    // array buffer offset
                          );
    GetGLError();
    
    _textureAttrib = glGetAttribLocation(_programID, "inTextureCoord");
    GetGLError();
    glEnableVertexAttribArray(_textureAttrib);
    GetGLError();
    glBindBuffer(GL_ARRAY_BUFFER, _vertexBufferObjectName[1]);
    GetGLError();
    glVertexAttribPointer(_textureAttrib,
                          2,
                          GL_FLOAT,
                          GL_FALSE,
                          0,
                          BUFFER_OFFSET(0)
                          );
    GetGLError();
    
    ////////////////////////////////
    // Load Texture               //
    ////////////////////////////////
/*
 The following seems set by default
 
    // Get a handle for our "tex" uniform
    // Default is already 0
    GLint textureUniformLocation = glGetUniformLocation(_programID, "tex");
    GetGLError();
    glUniform1i(textureUniformLocation, 0);                 // Set our "tex" sampler to user Texture Unit 0
    GetGLError();
    glActiveTexture(GL_TEXTURE0);                           // Bind our texture in Texture Unit 0
    GetGLError();
    
    // Not needed?
    glGenTextures( 1, &_textureBufferObjectName );
    glBindTexture(GL_TEXTURE_2D, _textureBufferObjectName);
    GetGLError();
*/
    
    // Specify MAG and MIN filter is mandatory
    // WRAP is optional
    
    // Setting the minification and magnification filters
    // to nearest instead of linear, may run faster on some
    // platforms, with possibly lower quality
    //
    glTexParameterf(GL_TEXTURE_2D,
                    GL_TEXTURE_MAG_FILTER,
                    GL_NEAREST
                    );

    // Set the minification filter to something other than
    // the default (GL_NEAREST_MIPMAP_LINEAR)
    //
    glTexParameterf(GL_TEXTURE_2D,
                    GL_TEXTURE_MIN_FILTER,
                    GL_NEAREST
                    );
    
    glTexParameteri(GL_TEXTURE_2D,
                    GL_TEXTURE_WRAP_S,
                    GL_CLAMP_TO_EDGE
                    );
    glTexParameteri(GL_TEXTURE_2D,
                    GL_TEXTURE_WRAP_T,
                    GL_CLAMP_TO_EDGE
                    );

    float pixels[] = {
        1.0f, 1.0f, 1.0f,  0.1f, 1.0f, 0.1f,
        0.1f, 1.0f, 0.1f,  1.0f, 1.0f, 1.0f,
    };
    GLsizei width = 2, height = 2;
    unsigned char* image = (unsigned char*)pixels;
    glTexImage2D(GL_TEXTURE_2D,
                 0,
                 GL_RGB,
                 width,
                 height,
                 0,
                 GL_RGB,
                 GL_FLOAT,
                 (const GLvoid*)image
                 );
    GetGLError();
    
    // Unbind VAO
    glBindVertexArray(0);
    GetGLError();
}

void OGLExampleTexture1::renderForTime(const CVTimeStamp * outputTime)
{
    // Bind VAO
    glBindVertexArray(_vertexArrayObjectName);
    GetGLError();
    
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    GetGLError();
    glClear(GL_COLOR_BUFFER_BIT);
    GetGLError();
    
    // Draw the square ( 2 triangles )
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    
    // Unbind VAO
    glBindVertexArray(0);
    GetGLError();
}

void OGLExampleTexture1::didUpdateWindowRect(NSRect rect)
{
    glViewport(rect.origin.x, rect.origin.y, rect.size.width, rect.size.height);
}

OGLExampleTexture1::~OGLExampleTexture1()
{
    ////////////////////////////////
    // Free the memory            //
    ////////////////////////////////
    
    // Bind VAO
    glBindVertexArray(_vertexArrayObjectName);
    GetGLError();
    
    glDisableVertexAttribArray(_positionAttrib);
    glDisableVertexAttribArray(_textureAttrib);
    
    // Delete Texture
//    glDeleteTextures(1, &_textureBufferObjectName);
//    GetGLError();
    
    // Unbind VBO
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    GetGLError();
    
    // Delete VBO
    glDeleteBuffers(3, _vertexBufferObjectName);
    GetGLError();
    
    // Delete shader program
    glDeleteProgram(_programID);
    GetGLError();
    
    // Unbind VAO
    glBindVertexArray(0);
    GetGLError();
    
    // Delete VAO
    glDeleteVertexArrays(1, &_vertexArrayObjectName);
    GetGLError();
}

////////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////////////
// OGLExampleTexture2                                                         //
////////////////////////////////////////////////////////////////////////////////

void OGLExampleTexture2::init(const void* arg)
{
    ///////////////////
    // Create VAO    //
    ///////////////////
    
    // Create and Bind VAO
    glGenVertexArrays(1, &_vertexArrayObjectName);
    GetGLError();
    glBindVertexArray(_vertexArrayObjectName);
    GetGLError();
    
    ///////////////////
    // Others        //
    ///////////////////
    
    glDisable(GL_BLEND);
    glDisable(GL_CULL_FACE);
    glDisable(GL_LINE_SMOOTH);
    glDisable(GL_SCISSOR_TEST);
    glDisable(GL_DEPTH_TEST);
    GetGLError();
    
    ///////////////////
    // Create VBO    //
    ///////////////////
    
    // A square
    static const GLfloat vertex_data[] = {
    //   Position    | Texcoords
        -1.0f,  1.0f,  0.0f, 0.0f, // Top-left
         1.0f,  1.0f,  1.0f, 0.0f, // Top-right
         1.0f, -1.0f,  1.0f, 1.0f, // Bottom-right
        -1.0f, -1.0f,  0.0f, 1.0f  // Bottom-left
    };
    
    // Generate 1 buffer, put the resulting identifier in vertexbuffer
    glGenBuffers(1, &_vertexBufferObjectName);
    // The following commands will talk about our 'vertexbuffer' buffer
    glBindBuffer(GL_ARRAY_BUFFER, _vertexBufferObjectName);
    // Give our vertices to OpenGL.
    GLsizeiptr size = sizeof(vertex_data);
    glBufferData(GL_ARRAY_BUFFER, size, vertex_data, GL_STATIC_DRAW);
    
    ///////////////////
    // Load Shaders  //
    ///////////////////
    
    NSString *vhs = [[NSBundle mainBundle] pathForResource:@"Texture2"
                                                    ofType:@"vsh"];
    NSString *fhs = [[NSBundle mainBundle] pathForResource:@"Texture2"
                                                    ofType:@"fsh"];
    _programID = loadShaders(vhs.UTF8String,fhs.UTF8String);
    GetGLError();
    
    // Free memory
    vhs = nil;
    fhs = nil;
    
    ////////////////////////////////
    // Draw into the back buffer  //
    ////////////////////////////////
    
    // Use our shader
    glUseProgram(_programID);
    GetGLError();
    
    // Specify the layout of the vertex data
    _positionAttrib = glGetAttribLocation(_programID, "inPosition");
    GetGLError();
    glEnableVertexAttribArray(_positionAttrib);
    GetGLError();
    glVertexAttribPointer(
                          _positionAttrib,    // attribute index
                          2,                  // size
                          GL_FLOAT,           // type
                          GL_FALSE,           // normalized?
                          4*sizeof(GLfloat),  // stride
                          BUFFER_OFFSET(0)    // array buffer offset
                          );
    GetGLError();

    _textureAttrib = glGetAttribLocation(_programID, "inTextureCoord");
    GetGLError();
    glEnableVertexAttribArray(_textureAttrib);
    GetGLError();
    glVertexAttribPointer(_textureAttrib,
                          2,
                          GL_FLOAT,
                          GL_FALSE,
                          4*sizeof(GLfloat),
                          BUFFER_OFFSET(2*sizeof(GLfloat))
                          );
    GetGLError();

    ////////////////////////////////
    // Load Texture               //
    ////////////////////////////////

     // Get a handle for our "myTextureSampler" uniform
     // Default ?????
    GLint textureUniformLocation = glGetUniformLocation(_programID, "tex");
    GetGLError();
    glUniform1i(textureUniformLocation, 0); // Set our "myTextureSampler" sampler to user Texture Unit 0
    GetGLError();
    glActiveTexture(GL_TEXTURE0); // Bind our texture in Texture Unit 0
    GetGLError();

    // Not needed?
    glGenTextures( 1, &_textureBufferObjectName );
    glBindTexture(GL_TEXTURE_2D, _textureBufferObjectName);
    GetGLError();
    
    // Setting the minification and magnification filters
    // to nearest instead of linear, may run faster on some
    // platforms, with possibly lower quality
    //
    glTexParameterf(GL_TEXTURE_2D,
                    GL_TEXTURE_MAG_FILTER,
                    GL_NEAREST
                    );
    
    // Set the minification filter to something other than
    // the default (GL_NEAREST_MIPMAP_LINEAR)
    //
    glTexParameterf(GL_TEXTURE_2D,
                    GL_TEXTURE_MIN_FILTER,
                    GL_NEAREST
                    );
    
    glTexParameteri(GL_TEXTURE_2D,
                    GL_TEXTURE_WRAP_S,
                    GL_CLAMP_TO_EDGE
                    );
    glTexParameteri(GL_TEXTURE_2D,
                    GL_TEXTURE_WRAP_T,
                    GL_CLAMP_TO_EDGE
                    );
    
    GLsizei width = 128, height = 128;
    const char *path = [[[NSBundle mainBundle] pathForResource:@"sample"
                                                       ofType:@"bmp"]
                        UTF8String];
    unsigned char* image = readBMP(path);
    glTexImage2D(GL_TEXTURE_2D,
                 0,
                 GL_RGB,
                 width,
                 height,
                 0,
                 GL_RGB,
                 GL_UNSIGNED_BYTE,
                 (const GLvoid*)image
                 );
    GetGLError();

    //////////////////////////////////
    // Create Element Buffer Object //
    //////////////////////////////////
    
    GLuint elements[] = {
        0, 1, 2,
        2, 3, 0
    };
    
    glGenBuffers(1, &_elementBufferObjectName);
    GetGLError();
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _elementBufferObjectName);
    GetGLError();
    glBufferData(GL_ELEMENT_ARRAY_BUFFER,
                 sizeof(elements),
                 elements,
                 GL_STATIC_DRAW
                 );
    GetGLError();

    // Unbind VAO
    glBindVertexArray(0);
    GetGLError();
}

void OGLExampleTexture2::renderForTime(const CVTimeStamp * outputTime)
{
    // Bind VAO
    glBindVertexArray(_vertexArrayObjectName);
    GetGLError();
    
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    GetGLError();
    glClear(GL_COLOR_BUFFER_BIT);
    GetGLError();
    
    // Draw the square ( 2 triangles )
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

    // Unbind VAO
    glBindVertexArray(0);
    GetGLError();
}

void OGLExampleTexture2::didUpdateWindowRect(NSRect rect)
{
    glViewport(rect.origin.x, rect.origin.y, rect.size.width, rect.size.height);
}

OGLExampleTexture2::~OGLExampleTexture2()
{
    ////////////////////////////////
    // Free the memory            //
    ////////////////////////////////
    
    // Bind VAO
    glBindVertexArray(_vertexArrayObjectName);
    GetGLError();
    
    glDisableVertexAttribArray(_positionAttrib);
    glDisableVertexAttribArray(_textureAttrib);

    // Delete EBO
    glDeleteBuffers(1, &_elementBufferObjectName);
    GetGLError();
    
    // Delete Texture
    glDeleteBuffers(1, &_textureBufferObjectName);
    GetGLError();

    // Unbind VBO
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    GetGLError();
    
    // Delete VBO
    glDeleteBuffers(1, &_vertexBufferObjectName);
    GetGLError();
    
    // Delete shader program
    glDeleteProgram(_programID);
    GetGLError();
    
    // Unbind VAO
    glBindVertexArray(0);
    GetGLError();
    
    // Delete VAO
    glDeleteVertexArrays(1, &_vertexArrayObjectName);
    GetGLError();
}

////////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////////////
// OGLExampleTexture3                                                         //
////////////////////////////////////////////////////////////////////////////////

void OGLExampleTexture3::init(const void* arg)
{
    ///////////////////
    // Create VAO    //
    ///////////////////
    
    // Create and Bind VAO
    glGenVertexArrays(1, &_vertexArrayObjectName);
    GetGLError();
    glBindVertexArray(_vertexArrayObjectName);
    GetGLError();
    
    ///////////////////
    // Others        //
    ///////////////////
    
    glDisable(GL_BLEND);
    glDisable(GL_CULL_FACE);
    glDisable(GL_LINE_SMOOTH);
    glDisable(GL_SCISSOR_TEST);
    glDisable(GL_DEPTH_TEST);
    GetGLError();
    
    ///////////////////
    // Create VBO    //
    ///////////////////
    
    // A square
    static const GLfloat vertex_data[] = {
        //   Position    | Texcoords
        -1.0f,  1.0f,  0.0f, 0.0f, // Top-left
         1.0f,  1.0f,  1.0f, 0.0f, // Top-right
         1.0f, -1.0f,  1.0f, 1.0f, // Bottom-right
        -1.0f, -1.0f,  0.0f, 1.0f  // Bottom-left
    };
    
    // Generate 1 buffer, put the resulting identifier in vertexbuffer
    glGenBuffers(1, &_vertexBufferObjectName);
    // The following commands will talk about our 'vertexbuffer' buffer
    glBindBuffer(GL_ARRAY_BUFFER, _vertexBufferObjectName);
    // Give our vertices to OpenGL.
    GLsizeiptr size = sizeof(vertex_data);
    glBufferData(GL_ARRAY_BUFFER, size, vertex_data, GL_STATIC_DRAW);
    
    ///////////////////
    // Load Shaders  //
    ///////////////////
    
    NSString *vhs = [[NSBundle mainBundle] pathForResource:@"Texture3"
                                                    ofType:@"vsh"];
    NSString *fhs = [[NSBundle mainBundle] pathForResource:@"Texture3"
                                                    ofType:@"fsh"];
    _programID = loadShaders(vhs.UTF8String,fhs.UTF8String);
    GetGLError();
    
    // Free memory
    vhs = nil;
    fhs = nil;
    
    ////////////////////////////////
    // Draw into the back buffer  //
    ////////////////////////////////
    
    // Use our shader
    glUseProgram(_programID);
    GetGLError();
    
    // Specify the layout of the vertex data
    _positionAttrib = glGetAttribLocation(_programID, "inPosition");
    GetGLError();
    glEnableVertexAttribArray(_positionAttrib);
    GetGLError();
    glVertexAttribPointer(
                          _positionAttrib,    // attribute index
                          2,                  // size
                          GL_FLOAT,           // type
                          GL_FALSE,           // normalized?
                          4*sizeof(GLfloat),  // stride
                          BUFFER_OFFSET(0)    // array buffer offset
                          );
    GetGLError();
    
    _textureAttrib = glGetAttribLocation(_programID, "inTextureCoord");
    GetGLError();
    glEnableVertexAttribArray(_textureAttrib);
    GetGLError();
    glVertexAttribPointer(_textureAttrib,
                          2,
                          GL_FLOAT,
                          GL_FALSE,
                          4*sizeof(GLfloat),
                          BUFFER_OFFSET(2*sizeof(GLfloat))
                          );
    GetGLError();
    
    ////////////////////////////////
    // Load Texture               //
    ////////////////////////////////
    
    // Get a handle for our "tex" uniform
    // Default ?????
    GLint textureUniformLocation = glGetUniformLocation(_programID, "tex");
    GetGLError();
    glUniform1i(textureUniformLocation, 0); // Set our "tex" sampler to user Texture Unit 0
    GetGLError();
    glActiveTexture(GL_TEXTURE0); // Bind our texture in Texture Unit 0
    GetGLError();
    
    // Not needed?
    glGenTextures( 1, &_textureBufferObjectName );
    glBindTexture(GL_TEXTURE_2D, _textureBufferObjectName);
    GetGLError();
    
    // Setting the minification and magnification filters
    // to nearest instead of linear, may run faster on some
    // platforms, with possibly lower quality
    //
    glTexParameterf(GL_TEXTURE_2D,
                    GL_TEXTURE_MAG_FILTER,
                    GL_NEAREST
                    );
    
    // Set the minification filter to something other than
    // the default (GL_NEAREST_MIPMAP_LINEAR)
    //
    glTexParameterf(GL_TEXTURE_2D,
                    GL_TEXTURE_MIN_FILTER,
                    GL_NEAREST
                    );
    
    glTexParameteri(GL_TEXTURE_2D,
                    GL_TEXTURE_WRAP_S,
                    GL_CLAMP_TO_EDGE
                    );
    glTexParameteri(GL_TEXTURE_2D,
                    GL_TEXTURE_WRAP_T,
                    GL_CLAMP_TO_EDGE
                    );
    
    GLsizei width = 128, height = 128;
    const char *path = [[[NSBundle mainBundle] pathForResource:@"sample"
                                                        ofType:@"bmp"]
                        UTF8String];
    unsigned char* image = readBMP(path);
    glTexImage2D(GL_TEXTURE_2D,
                 0,
                 GL_RGB,
                 width,
                 height,
                 0,
                 GL_BGR,                // readBMP return the color as BGR
                 GL_UNSIGNED_BYTE,
                 (const GLvoid*)image
                 );
    GetGLError();
    
    //////////////////////////////////
    // Create Element Buffer Object //
    //////////////////////////////////
    
    GLuint elements[] = {
        0, 1, 2,
        2, 3, 0
    };
    
    glGenBuffers(1, &_elementBufferObjectName);
    GetGLError();
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _elementBufferObjectName);
    GetGLError();
    glBufferData(GL_ELEMENT_ARRAY_BUFFER,
                 sizeof(elements),
                 elements,
                 GL_STATIC_DRAW
                 );
    GetGLError();
    
    // Unbind VAO
    glBindVertexArray(0);
    GetGLError();
}

void OGLExampleTexture3::renderForTime(const CVTimeStamp * outputTime)
{
    // Bind VAO
    glBindVertexArray(_vertexArrayObjectName);
    GetGLError();
    
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    GetGLError();
    glClear(GL_COLOR_BUFFER_BIT);
    GetGLError();
    
    // Draw the square ( 2 triangles )
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    
    // Unbind VAO
    glBindVertexArray(0);
    GetGLError();
}

void OGLExampleTexture3::didUpdateWindowRect(NSRect rect)
{
    glViewport(rect.origin.x, rect.origin.y, rect.size.width, rect.size.height);
}

OGLExampleTexture3::~OGLExampleTexture3()
{
    ////////////////////////////////
    // Free the memory            //
    ////////////////////////////////
    
    // Bind VAO
    glBindVertexArray(_vertexArrayObjectName);
    GetGLError();
    
    glDisableVertexAttribArray(_positionAttrib);
    glDisableVertexAttribArray(_textureAttrib);
    
    // Delete EBO
    glDeleteBuffers(1, &_elementBufferObjectName);
    GetGLError();
    
    // Delete Texture
    glDeleteBuffers(1, &_textureBufferObjectName);
    GetGLError();
    
    // Unbind VBO
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    GetGLError();
    
    // Delete VBO
    glDeleteBuffers(1, &_vertexBufferObjectName);
    GetGLError();
    
    // Delete shader program
    glDeleteProgram(_programID);
    GetGLError();

    // Delete Texture
    glDeleteTextures(1, &_textureBufferObjectName);

    // Unbind VAO
    glBindVertexArray(0);
    GetGLError();
    
    // Delete VAO
    glDeleteVertexArrays(1, &_vertexArrayObjectName);
    GetGLError();
}

////////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////////////
// OGLExampleTexture4                                                         //
////////////////////////////////////////////////////////////////////////////////

void OGLExampleTexture4::init(const void* arg)
{
    ///////////////////
    // Create VAO    //
    ///////////////////
    
    // Create and Bind VAO
    glGenVertexArrays(1, &_vertexArrayObjectName);
    GetGLError();
    glBindVertexArray(_vertexArrayObjectName);
    GetGLError();
    
    ///////////////////
    // Create VBO    //
    ///////////////////
    
    // An array of 3 vectors which represents 3 vertices
    static const GLfloat vertex_data[] = {
    //   Position    | Color            | Texcoords
        -1.0f,  1.0f,  1.0f, 0.0f, 0.0f,  0.0f, 0.0f, // Top-left
         1.0f,  1.0f,  0.0f, 1.0f, 0.0f,  1.0f, 0.0f, // Top-right
         1.0f, -1.0f,  0.0f, 0.0f, 1.0f,  1.0f, 1.0f, // Bottom-right
        -1.0f, -1.0f,  1.0f, 1.0f, 1.0f,  0.0f, 1.0f  // Bottom-left
    };
    
    // Generate 1 buffer, put the resulting identifier in vertexbuffer
    glGenBuffers(1, &_vertexBufferObjectName);
    // The following commands will talk about our 'vertexbuffer' buffer
    glBindBuffer(GL_ARRAY_BUFFER, _vertexBufferObjectName);
    // Give our vertices to OpenGL.
    GLsizeiptr size = sizeof(vertex_data);
    glBufferData(GL_ARRAY_BUFFER, size, vertex_data, GL_STATIC_DRAW);
    
    ///////////////////
    // Others        //
    ///////////////////
    
    glDisable(GL_BLEND);
    glDisable(GL_CULL_FACE);
    glDisable(GL_LINE_SMOOTH);
    glDisable(GL_SCISSOR_TEST);
    glDisable(GL_DEPTH_TEST);
    GetGLError();
    
    ///////////////////
    // Load Shaders  //
    ///////////////////
    
    NSString *vhs = [[NSBundle mainBundle] pathForResource:@"Texture4"
                                                    ofType:@"vsh"];
    NSString *fhs = [[NSBundle mainBundle] pathForResource:@"Texture4"
                                                    ofType:@"fsh"];
    _programID = loadShaders(vhs.UTF8String,fhs.UTF8String);
    GetGLError();
    
    // Free memory
    vhs = nil;
    fhs = nil;
    
    ////////////////////////////////
    // Draw into the back buffer  //
    ////////////////////////////////
    
    // Use our shader
    glUseProgram(_programID);
    
    // Specify the layout of the vertex data
    _positionAttrib = glGetAttribLocation(_programID, "inPosition");
    glEnableVertexAttribArray(_positionAttrib);
    glVertexAttribPointer(
                          _positionAttrib,    // attribute index
                          2,                  // size
                          GL_FLOAT,           // type
                          GL_FALSE,           // normalized?
                          7*sizeof(GLfloat),  // stride
                          BUFFER_OFFSET(0)    // array buffer offset
                          );
    
    _colorAttrib = glGetAttribLocation(_programID, "inColor");
    glEnableVertexAttribArray(_colorAttrib);
    glVertexAttribPointer(_colorAttrib,
                          3,
                          GL_FLOAT,
                          GL_FALSE,
                          7*sizeof(GLfloat),
                          BUFFER_OFFSET(2*sizeof(GLfloat))
                          );
    
    _textureAttrib = glGetAttribLocation(_programID, "inTextureCoord");
    glEnableVertexAttribArray(_textureAttrib);
    glVertexAttribPointer(_textureAttrib,
                          2,
                          GL_FLOAT,
                          GL_FALSE,
                          7*sizeof(GLfloat),
                          BUFFER_OFFSET(5*sizeof(GLfloat))
                          );
    
    ////////////////////////////////
    // Load Texture               //
    ////////////////////////////////
    
     NSString *path = [[NSBundle mainBundle] pathForResource:@"sample"
                                                      ofType:@"bmp"];
     NSDictionary *options = @{GLKTextureLoaderOriginBottomLeft:@NO};
     GLKTextureInfo* info =
     [GLKTextureLoader textureWithContentsOfFile:path
                                         options:options
                                           error:nil];
     
     // Optional : Default is already set to 0
     // Bind our texture in Texture Unit 0
     glActiveTexture(GL_TEXTURE0);
     GetGLError();
     glBindTexture(GL_TEXTURE_2D, info.name);
     GetGLError();
     GLint textureUniformLocation  = glGetUniformLocation(_programID, "tex");
     GetGLError();
     // Set our "myTextureSampler" sampler to user Texture Unit 0
     glUniform1i(textureUniformLocation, 0);
     GetGLError();
    
    //////////////////////////////////
    // Create Element Buffer Object //
    //////////////////////////////////
    
    GLuint elements[] = {
        0, 1, 2,
        2, 3, 0
    };
    
    glGenBuffers(1, &_elementBufferObjectName);
    GetGLError();
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _elementBufferObjectName);
    GetGLError();
    glBufferData(GL_ELEMENT_ARRAY_BUFFER,
                 sizeof(elements),
                 elements,
                 GL_STATIC_DRAW
                 );
    GetGLError();
    
    // Unbind VAO
    glBindVertexArray(0);
    GetGLError();
}

void OGLExampleTexture4::renderForTime(const CVTimeStamp * outputTime)
{
    // Bind VAO
    glBindVertexArray(_vertexArrayObjectName);
    GetGLError();
    
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    GetGLError();
    glClear(GL_COLOR_BUFFER_BIT);
    GetGLError();
    
    // Draw the square ( 2 triangles )
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    
    // Unbind VAO
    glBindVertexArray(0);
    GetGLError();
}

void OGLExampleTexture4::didUpdateWindowRect(NSRect rect)
{
    glViewport(rect.origin.x, rect.origin.y, rect.size.width, rect.size.height);
}

OGLExampleTexture4::~OGLExampleTexture4()
{
    ////////////////////////////////
    // Free the memory            //
    ////////////////////////////////
    
    // Bind VAO
    glBindVertexArray(_vertexArrayObjectName);
    GetGLError();
    
    glDisableVertexAttribArray(_positionAttrib);
    glDisableVertexAttribArray(_colorAttrib);
    glDisableVertexAttribArray(_textureAttrib);
    
    // Delete EBO
    glDeleteBuffers(1, &_elementBufferObjectName);
    GetGLError();
    
    // Unbind VBO
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    GetGLError();
    
    // Delete VBO
    glDeleteBuffers(1, &_vertexBufferObjectName);
    GetGLError();
    
    // Delete shader program
    glDeleteProgram(_programID);
    GetGLError();
    
    // Delete Texture
    glDeleteTextures(1, &_textureBufferObjectName);
    
    // Unbind VAO
    glBindVertexArray(0);
    GetGLError();
    
    // Delete VAO
    glDeleteVertexArrays(1, &_vertexArrayObjectName);
    GetGLError();
}

////////////////////////////////////////////////////////////////////////////////

