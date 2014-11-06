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
std::string OGLExample::name()
{
    return "Il Mio Nome E Nessuno";
}

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
    OGL_GET_GL_ERROR();
    
    this->setColor(1.0f, 0.0f, 0.0f, 1.0f);
}

void OGLExampleColor::renderForTime(const CVTimeStamp * outputTime)
{
    glClearColor(_r,_g,_b,_a);
    OGL_GET_GL_ERROR();
    
    glClear(GL_COLOR_BUFFER_BIT);
    OGL_GET_GL_ERROR();
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
}

std::string OGLExampleColor::name()
{
    return "Red background";
}

////////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////////////
// OGLExampleTriangle                                                         //
////////////////////////////////////////////////////////////////////////////////

void OGLExampleTriangle::init(const void* arg)
{
    // Create VAO
    glGenVertexArrays(1, &_vertexArrayObjectName);
    OGL_GET_GL_ERROR();
    
    // Bind VAO
    glBindVertexArray(_vertexArrayObjectName);
    OGL_GET_GL_ERROR();
    
    glDisable(GL_BLEND);
    glDisable(GL_CULL_FACE);
    glDisable(GL_LINE_SMOOTH);
    glDisable(GL_SCISSOR_TEST);
    glDisable(GL_DEPTH_TEST);
    OGL_GET_GL_ERROR();

    NSString *vhs = [[NSBundle mainBundle] pathForResource:@"RedTriangle"
                                                    ofType:@"vsh"];
    NSString *fhs = [[NSBundle mainBundle] pathForResource:@"RedTriangle"
                                                    ofType:@"fsh"];
    _programID = load_shaders(vhs.UTF8String,fhs.UTF8String);
    OGL_GET_GL_ERROR();
    
    // Unbind VAO
    glBindVertexArray(0);
    OGL_GET_GL_ERROR();
}

std::string OGLExampleTriangle::name()
{
    return "Triangle Red Basic";
}

void OGLExampleTriangle::renderForTime(const CVTimeStamp * outputTime)
{
    // Bind VAO
    glBindVertexArray(_vertexArrayObjectName);
    OGL_GET_GL_ERROR();
    
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    OGL_GET_GL_ERROR();
    glClear(GL_COLOR_BUFFER_BIT);
    OGL_GET_GL_ERROR();
    
    // Use our shader
    glUseProgram(_programID);
    OGL_GET_GL_ERROR();

    // An array of 3 vectors which represents 3 vertices
    static const GLfloat vertex_data[] = {
        -0.5f, -0.5f, 0.0f,
         0.5f, -0.5f, 0.0f,
         0.0f,  0.5f, 0.0f
    };
    
    ///////////////////
    // Draw triangle //
    ///////////////////
    
    // This will identify our vertex buffer
    GLuint vertexbuffer;
    
    // Generate 1 buffer, put the resulting identifier in vertexbuffer
    glGenBuffers(1, &vertexbuffer);
    OGL_GET_GL_ERROR();
    // The following commands will talk about our 'vertexbuffer' buffer
    glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
    OGL_GET_GL_ERROR();
    // Give our vertices to OpenGL.
    GLsizeiptr size = sizeof(vertex_data);
    glBufferData(GL_ARRAY_BUFFER, size, vertex_data, GL_STATIC_DRAW);
    OGL_GET_GL_ERROR();

    // 1rst attribute buffer : vertices
    // Specify the layout of the vertex data
    glEnableVertexAttribArray(0); // 0 because we have the following line
                                  // "layout(location = 0) in vec3 position;"
                                  // in our shader program.
    OGL_GET_GL_ERROR();
    glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
    OGL_GET_GL_ERROR();
    glVertexAttribPointer(
                          0,                  // attribute 0. No particular
                                              // reason for 0, but must match
                                              // the layout in the shader.
                          3,                  // size
                          GL_FLOAT,           // type
                          GL_FALSE,           // normalized?
                          0,                  // stride
                          OGL_BUFFER_OFFSET(0)// array buffer offset
                          );
    OGL_GET_GL_ERROR();

    
    // Draw the triangle ( 3 vertices ).
    // Starting from vertex 0.
    glDrawArrays(GL_TRIANGLES, 0, 3);
    OGL_GET_GL_ERROR();

    // Disable Attrib
    glDisableVertexAttribArray(0);
    OGL_GET_GL_ERROR();

    // Delete buffer
    glDeleteBuffers(1, &vertexbuffer);
    OGL_GET_GL_ERROR();
    
    // Unbind VAO
    glBindVertexArray(0);
    OGL_GET_GL_ERROR();
}

void OGLExampleTriangle::didUpdateWindowRect(NSRect rect)
{
    glViewport(rect.origin.x, rect.origin.y, rect.size.width, rect.size.height);
    OGL_GET_GL_ERROR();
}

OGLExampleTriangle::~OGLExampleTriangle()
{
    // Delete VAO
    glDeleteVertexArrays(1, &_vertexArrayObjectName);
    OGL_GET_GL_ERROR();
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
    OGL_GET_GL_ERROR();
    glBindVertexArray(_vertexArrayObjectName);
    OGL_GET_GL_ERROR();
    
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
    OGL_GET_GL_ERROR();
    // The following commands will talk about our 'vertexbuffer' buffer
    glBindBuffer(GL_ARRAY_BUFFER, _vertexBufferObjectName);
    OGL_GET_GL_ERROR();
    // Give our vertices to OpenGL.
    GLsizeiptr size = sizeof(vertex_data);
    glBufferData(GL_ARRAY_BUFFER, size, vertex_data, GL_STATIC_DRAW);
    OGL_GET_GL_ERROR();

    ///////////////////
    // Others        //
    ///////////////////
    
    glDisable(GL_BLEND);
    glDisable(GL_CULL_FACE);
    glDisable(GL_LINE_SMOOTH);
    glDisable(GL_SCISSOR_TEST);
    glDisable(GL_DEPTH_TEST);
    OGL_GET_GL_ERROR();
    
    ///////////////////
    // Load Shaders  //
    ///////////////////
    
    NSString *vhs = [[NSBundle mainBundle] pathForResource:@"RedTriangle"
                                                    ofType:@"vsh"];
    NSString *fhs = [[NSBundle mainBundle] pathForResource:@"TriangleUniformColor"
                                                    ofType:@"fsh"];
    _programID = load_shaders(vhs.UTF8String,fhs.UTF8String);
    OGL_GET_GL_ERROR();
    
    ////////////////////////////////
    // Draw into the back buffer  //
    ////////////////////////////////
    
    // Specify the layout of the vertex data
    _indexAttrib = glGetAttribLocation(_programID, "position");
    OGL_GET_GL_ERROR();
    glEnableVertexAttribArray(_indexAttrib);
    OGL_GET_GL_ERROR();
    glVertexAttribPointer(
                          _indexAttrib,       // index attribute
                          3,                  // size
                          GL_FLOAT,           // type
                          GL_FALSE,           // normalized?
                          0,                  // stride
                          OGL_BUFFER_OFFSET(0)// array buffer offset
                          );
    OGL_GET_GL_ERROR();

    // Set the color
    GLint uniColor = glGetUniformLocation(_programID, "triangleColor");
    OGL_GET_GL_ERROR();
    
    // Sets the vertices' color
    // glUniform* point to the current program,
    // that's why we need to call glUseProgram().
    glUseProgram(_programID);
    OGL_GET_GL_ERROR();
    glUniform3f(uniColor, 0.0f, 0.0f, 0.0f);
    OGL_GET_GL_ERROR();
    glUseProgram(0);
    OGL_GET_GL_ERROR();
    
    // Unbind VAO
    glBindVertexArray(0);
    OGL_GET_GL_ERROR();
}

void OGLExampleTriangle3::renderForTime(const CVTimeStamp * outputTime)
{
    // Bind VAO
    glBindVertexArray(_vertexArrayObjectName);
    OGL_GET_GL_ERROR();
    
    glClearColor(1.0f, 0.0f, 0.0f, 0.0f);
    OGL_GET_GL_ERROR();
    glClear(GL_COLOR_BUFFER_BIT);
    OGL_GET_GL_ERROR();

    // Use our shader
    glUseProgram(_programID);
    OGL_GET_GL_ERROR();

    // Draw the triangle ( 3 vertices ).
    // Starting from vertex 0.
    glDrawArrays(GL_TRIANGLES, 0, 3);
    OGL_GET_GL_ERROR();

    // Unbind VAO
    glBindVertexArray(0);
    OGL_GET_GL_ERROR();
}

void OGLExampleTriangle3::didUpdateWindowRect(NSRect rect)
{
    glViewport(rect.origin.x, rect.origin.y, rect.size.width, rect.size.height);
}

std::string OGLExampleTriangle3::name()
{
    return "Triangle Uniform Color";
}

OGLExampleTriangle3::~OGLExampleTriangle3()
{
    ////////////////////////////////
    // Free the memory            //
    ////////////////////////////////
    
    // Bind VAO
    glBindVertexArray(_vertexArrayObjectName);
    OGL_GET_GL_ERROR();
    
    // Unbind VBO
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    OGL_GET_GL_ERROR();
    
    // Delete VBO
    glDeleteBuffers(1, &_vertexBufferObjectName);
    OGL_GET_GL_ERROR();

    // Delete shader program
    glDeleteProgram(_programID);
    OGL_GET_GL_ERROR();
    
    // Unbind VAO
    glBindVertexArray(0);
    OGL_GET_GL_ERROR();
    
    // Delete VAO
    glDeleteVertexArrays(1, &_vertexArrayObjectName);
    OGL_GET_GL_ERROR();
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
    OGL_GET_GL_ERROR();
    glBindVertexArray(_vertexArrayObjectName);
    OGL_GET_GL_ERROR();
    
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
    OGL_GET_GL_ERROR();
    // The following commands will talk about our 'vertexbuffer' buffer
    glBindBuffer(GL_ARRAY_BUFFER, _vertexBufferObjectName);
    OGL_GET_GL_ERROR();
    // Give our vertices to OpenGL.
    GLsizeiptr size = sizeof(vertex_data);
    glBufferData(GL_ARRAY_BUFFER, size, vertex_data, GL_STATIC_DRAW);
    OGL_GET_GL_ERROR();

    ///////////////////
    // Others        //
    ///////////////////
    
    glDisable(GL_BLEND);
    glDisable(GL_CULL_FACE);
    glDisable(GL_LINE_SMOOTH);
    glDisable(GL_SCISSOR_TEST);
    glDisable(GL_DEPTH_TEST);
    OGL_GET_GL_ERROR();
    
    ///////////////////
    // Load Shaders  //
    ///////////////////
    
    NSString *vhs = [[NSBundle mainBundle] pathForResource:@"RedTriangle"
                                                    ofType:@"vsh"];
    NSString *fhs = [[NSBundle mainBundle] pathForResource:@"RedTriangle"
                                                    ofType:@"fsh"];
    _programID = load_shaders(vhs.UTF8String,fhs.UTF8String);
    OGL_GET_GL_ERROR();
    
    ////////////////////////////////
    // Draw into the back buffer  //
    ////////////////////////////////
    
    // Use our shader
    glUseProgram(_programID);
    OGL_GET_GL_ERROR();

    // Specify the layout of the vertex data
    _indexAttrib = glGetAttribLocation(_programID, "position");
    assert(_indexAttrib!=-1);
    OGL_GET_GL_ERROR();

    glVertexAttribPointer(
                          _indexAttrib,       // attribute index
                          3,                  // size
                          GL_FLOAT,           // type
                          GL_FALSE,           // normalized?
                          0,                  // stride
                          (void*)0            // array buffer offset
                          );
    OGL_GET_GL_ERROR();

    // Enable attribute array
    glEnableVertexAttribArray(_indexAttrib);
    OGL_GET_GL_ERROR();

    // Unbind VAO
    glBindVertexArray(0);
    OGL_GET_GL_ERROR();
}

void OGLExampleTriangle2::renderForTime(const CVTimeStamp * outputTime)
{
    // Bind VAO
    glBindVertexArray(_vertexArrayObjectName);
    OGL_GET_GL_ERROR();
    
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    OGL_GET_GL_ERROR();
    glClear(GL_COLOR_BUFFER_BIT);
    OGL_GET_GL_ERROR();
    
    // Use our shader
    // The OpenGL program is a global state, and only one program can be active.
    // So if you have more than one program, then you need to enable each of
    // them every time you use them.
    glUseProgram(_programID);
    
    // Draw the triangle ( 3 vertices ).
    // Starting from vertex 0.
    glDrawArrays(GL_TRIANGLES, 0, 3);
    
    // Unbind VAO
    glBindVertexArray(0);
    OGL_GET_GL_ERROR();
}

void OGLExampleTriangle2::didUpdateWindowRect(NSRect rect)
{
    glViewport(rect.origin.x, rect.origin.y, rect.size.width, rect.size.height);
}

std::string OGLExampleTriangle2::name()
{
    return "Triangle Red Optimized";
}

OGLExampleTriangle2::~OGLExampleTriangle2()
{
    ////////////////////////////////
    // Free the memory            //
    ////////////////////////////////
    
    // Bind VAO
//    glBindVertexArray(_vertexArrayObjectName);
//    OGL_GET_GL_ERROR();
    
    // Unbind VBO
//    glBindBuffer(GL_ARRAY_BUFFER, 0);
//    OGL_GET_GL_ERROR();
    
    // Delete VBO
    glDeleteBuffers(1, &_vertexBufferObjectName);
    OGL_GET_GL_ERROR();
    
    // Delete shader program
    glDeleteProgram(_programID);
    OGL_GET_GL_ERROR();
    
    // Disable Attribute
//    glDisableVertexAttribArray(_indexAttrib);
//    OGL_GET_GL_ERROR();
    
    // Unbind VAO
//    glBindVertexArray(0);
//    OGL_GET_GL_ERROR();
    
    // Delete VAO
    glDeleteVertexArrays(1, &_vertexArrayObjectName);
    OGL_GET_GL_ERROR();
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
    OGL_GET_GL_ERROR();
    glBindVertexArray(_vertexArrayObjectName);
    OGL_GET_GL_ERROR();
    
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
    OGL_GET_GL_ERROR();
    // The following commands will talk about our 'vertexbuffer' buffer
    glBindBuffer(GL_ARRAY_BUFFER, _vertexBufferObjectName);
    OGL_GET_GL_ERROR();
    // Give our vertices to OpenGL.
    GLsizeiptr size = sizeof(vertex_data);
    glBufferData(GL_ARRAY_BUFFER, size, vertex_data, GL_STATIC_DRAW);
    OGL_GET_GL_ERROR();
    
    ///////////////////
    // Others        //
    ///////////////////
    
    glDisable(GL_BLEND);
    glDisable(GL_CULL_FACE);
    glDisable(GL_LINE_SMOOTH);
    glDisable(GL_SCISSOR_TEST);
    glDisable(GL_DEPTH_TEST);
    OGL_GET_GL_ERROR();
    
    ///////////////////
    // Load Shaders  //
    ///////////////////
    
    NSString *vhs = [[NSBundle mainBundle] pathForResource:@"TriangleDynColor"
                                                    ofType:@"vsh"];
    NSString *fhs = [[NSBundle mainBundle] pathForResource:@"TriangleDynColor"
                                                    ofType:@"fsh"];
    _programID = load_shaders(vhs.UTF8String,fhs.UTF8String);
    OGL_GET_GL_ERROR();
    
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
                          OGL_BUFFER_OFFSET(0)// array buffer offset
                          );
    
    _colorAttrib = glGetAttribLocation(_programID, "inColor");
    glEnableVertexAttribArray(_colorAttrib);
    glVertexAttribPointer(_colorAttrib,
                          3,
                          GL_FLOAT,
                          GL_FALSE,
                          5*sizeof(float),
                          OGL_BUFFER_OFFSET(2*sizeof(GLfloat))
                          );
    
    // Unbind VAO
    glBindVertexArray(0);
    OGL_GET_GL_ERROR();
}

void OGLExampleTriangle4::renderForTime(const CVTimeStamp * outputTime)
{
    // Bind VAO
    glBindVertexArray(_vertexArrayObjectName);
    OGL_GET_GL_ERROR();
    
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    OGL_GET_GL_ERROR();
    glClear(GL_COLOR_BUFFER_BIT);
    OGL_GET_GL_ERROR();
    
    // Use our shader
    glUseProgram(_programID);
    OGL_GET_GL_ERROR();

    // Draw the triangle ( 3 vertices ).
    // Starting from vertex 0.
    glDrawArrays(GL_TRIANGLES, 0, 3);
    OGL_GET_GL_ERROR();
    
    // Unbind VAO
    glBindVertexArray(0);
    OGL_GET_GL_ERROR();
}

void OGLExampleTriangle4::didUpdateWindowRect(NSRect rect)
{
    glViewport(rect.origin.x, rect.origin.y, rect.size.width, rect.size.height);
}

std::string OGLExampleTriangle4::name()
{
    return "Triangle Dyn Color";
}

OGLExampleTriangle4::~OGLExampleTriangle4()
{
    ////////////////////////////////
    // Free the memory            //
    ////////////////////////////////
    
    // Bind VAO
//    glBindVertexArray(_vertexArrayObjectName);
//    OGL_GET_GL_ERROR();
    
//    glDisableVertexAttribArray(_positionAttrib);
//    glDisableVertexAttribArray(_colorAttrib);
    
    // Unbind VBO
//    glBindBuffer(GL_ARRAY_BUFFER, 0);
//    OGL_GET_GL_ERROR();
    
    // Delete VBO
    glDeleteBuffers(1, &_vertexBufferObjectName);
    OGL_GET_GL_ERROR();
    
    // Delete shader program
    glDeleteProgram(_programID);
    OGL_GET_GL_ERROR();
    
    // Unbind VAO
//    glBindVertexArray(0);
//    OGL_GET_GL_ERROR();
    
    // Delete VAO
    glDeleteVertexArrays(1, &_vertexArrayObjectName);
    OGL_GET_GL_ERROR();
}

////////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////////////
// OGLExampleSquare                                                           //
////////////////////////////////////////////////////////////////////////////////

std::string OGLExampleSquare::name()
{
    return "Square Basic (6 vertices)";
}

void OGLExampleSquare::init(const void* arg)
{
    ///////////////////
    // Create VAO    //
    ///////////////////
    
    // Create and Bind VAO
    glGenVertexArrays(1, &_vertexArrayObjectName);
    OGL_GET_GL_ERROR();
    glBindVertexArray(_vertexArrayObjectName);
    OGL_GET_GL_ERROR();
    
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
    OGL_GET_GL_ERROR();
    
    ///////////////////
    // Load Shaders  //
    ///////////////////
    
    NSString *vhs = [[NSBundle mainBundle] pathForResource:@"TriangleDynColor"
                                                    ofType:@"vsh"];
    NSString *fhs = [[NSBundle mainBundle] pathForResource:@"TriangleDynColor"
                                                    ofType:@"fsh"];
    _programID = load_shaders(vhs.UTF8String,fhs.UTF8String);
    OGL_GET_GL_ERROR();
    
    ////////////////////////////////
    // Draw into the back buffer  //
    ////////////////////////////////
    
    // Specify the layout of the vertex data
    _positionAttrib = glGetAttribLocation(_programID, "inPosition");
    glEnableVertexAttribArray(_positionAttrib);
    glVertexAttribPointer(
                          _positionAttrib,    // attribute index
                          2,                  // size
                          GL_FLOAT,           // type
                          GL_FALSE,           // normalized?
                          5*sizeof(GLfloat),  // stride
                          OGL_BUFFER_OFFSET(0)// array buffer offset
                          );
    
    _colorAttrib = glGetAttribLocation(_programID, "inColor");
    glEnableVertexAttribArray(_colorAttrib);
    glVertexAttribPointer(_colorAttrib,
                          3,
                          GL_FLOAT,
                          GL_FALSE,
                          5*sizeof(float),
                          OGL_BUFFER_OFFSET(2*sizeof(GLfloat))
                          );
    
    // Unbind VAO
    glBindVertexArray(0);
    OGL_GET_GL_ERROR();
}

void OGLExampleSquare::renderForTime(const CVTimeStamp * outputTime)
{
    // Bind VAO
    glBindVertexArray(_vertexArrayObjectName);
    OGL_GET_GL_ERROR();
    
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    OGL_GET_GL_ERROR();
    glClear(GL_COLOR_BUFFER_BIT);
    OGL_GET_GL_ERROR();
    
    // Use our shader
    glUseProgram(_programID);
    OGL_GET_GL_ERROR();
    
    // Draw the square ( 2 triangles => 6 vertices ).
    // Starting from vertex 0.
    glDrawArrays(GL_TRIANGLES, 0, 6);
    OGL_GET_GL_ERROR();

    // Unbind VAO
    glBindVertexArray(0);
    OGL_GET_GL_ERROR();
}

void OGLExampleSquare::didUpdateWindowRect(NSRect rect)
{
    glViewport(rect.origin.x, rect.origin.y, rect.size.width, rect.size.height);
}

OGLExampleSquare::~OGLExampleSquare()
{
    ////////////////////////////////
    // Free the memory            //
    ////////////////////////////////
    
    // Bind VAO
    glBindVertexArray(_vertexArrayObjectName);
    OGL_GET_GL_ERROR();
    
    glDisableVertexAttribArray(_positionAttrib);
    glDisableVertexAttribArray(_colorAttrib);
    
    // Unbind VBO
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    OGL_GET_GL_ERROR();
    
    // Delete VBO
    glDeleteBuffers(1, &_vertexBufferObjectName);
    OGL_GET_GL_ERROR();
    
    // Delete shader program
    glDeleteProgram(_programID);
    OGL_GET_GL_ERROR();
    
    // Unbind VAO
    glBindVertexArray(0);
    OGL_GET_GL_ERROR();
    
    // Delete VAO
    glDeleteVertexArrays(1, &_vertexArrayObjectName);
    OGL_GET_GL_ERROR();
}

////////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////////////
// OGLExampleSquare2                                                          //
////////////////////////////////////////////////////////////////////////////////

std::string OGLExampleSquare2::name()
{
    return "Square Optimized (4 vertices)";
}

void OGLExampleSquare2::init(const void* arg)
{
    ///////////////////
    // Create VAO    //
    ///////////////////
    
    // Create and Bind VAO
    glGenVertexArrays(1, &_vertexArrayObjectName);
    OGL_GET_GL_ERROR();
    glBindVertexArray(_vertexArrayObjectName);
    OGL_GET_GL_ERROR();
    
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
    OGL_GET_GL_ERROR();
    // The following commands will talk about our 'vertexbuffer' buffer
    glBindBuffer(GL_ARRAY_BUFFER, _vertexBufferObjectName);
    OGL_GET_GL_ERROR();
    // Give our vertices to OpenGL.
    GLsizeiptr size = sizeof(vertex_data);
    glBufferData(GL_ARRAY_BUFFER, size, vertex_data, GL_STATIC_DRAW);
    OGL_GET_GL_ERROR();

    ///////////////////
    // Others        //
    ///////////////////
    
    glDisable(GL_BLEND);
    glDisable(GL_CULL_FACE);
    glDisable(GL_LINE_SMOOTH);
    glDisable(GL_SCISSOR_TEST);
    glDisable(GL_DEPTH_TEST);
    OGL_GET_GL_ERROR();
    
    ///////////////////
    // Load Shaders  //
    ///////////////////
    
    NSString *vhs = [[NSBundle mainBundle] pathForResource:@"TriangleDynColor"
                                                    ofType:@"vsh"];
    NSString *fhs = [[NSBundle mainBundle] pathForResource:@"TriangleDynColor"
                                                    ofType:@"fsh"];
    _programID = load_shaders(vhs.UTF8String,fhs.UTF8String);
    OGL_GET_GL_ERROR();
    
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
    
    // Specify the layout of the vertex data
    _positionAttrib = glGetAttribLocation(_programID, "inPosition");
    glEnableVertexAttribArray(_positionAttrib);
    glVertexAttribPointer(
                          _positionAttrib,    // attribute index
                          2,                  // size
                          GL_FLOAT,           // type
                          GL_FALSE,           // normalized?
                          5*sizeof(GLfloat),  // stride
                          OGL_BUFFER_OFFSET(0)    // array buffer offset
                          );
    
    _colorAttrib = glGetAttribLocation(_programID, "inColor");
    glEnableVertexAttribArray(_colorAttrib);
    glVertexAttribPointer(_colorAttrib,
                          3,
                          GL_FLOAT,
                          GL_FALSE,
                          5*sizeof(float),
                          OGL_BUFFER_OFFSET(2*sizeof(GLfloat))
                          );
    
    // Unbind VAO
    glBindVertexArray(0);
    OGL_GET_GL_ERROR();
}

void OGLExampleSquare2::renderForTime(const CVTimeStamp * outputTime)
{
    // Bind VAO
    glBindVertexArray(_vertexArrayObjectName);
    OGL_GET_GL_ERROR();
    
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    OGL_GET_GL_ERROR();
    glClear(GL_COLOR_BUFFER_BIT);
    OGL_GET_GL_ERROR();
    
    // Use our shader
    glUseProgram(_programID);
    OGL_GET_GL_ERROR();

    // Draw the square ( 2 triangles => 6 vertices ).
    // Starting from vertex 0.
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    
    // Unbind VAO
    glBindVertexArray(0);
    OGL_GET_GL_ERROR();
}

void OGLExampleSquare2::didUpdateWindowRect(NSRect rect)
{
    glViewport(rect.origin.x, rect.origin.y, rect.size.width, rect.size.height);
}

OGLExampleSquare2::~OGLExampleSquare2()
{
    ////////////////////////////////
    // Free the memory            //
    ////////////////////////////////
    
    // Bind VAO
    glBindVertexArray(_vertexArrayObjectName);
    OGL_GET_GL_ERROR();
    
    glDisableVertexAttribArray(_positionAttrib);
    glDisableVertexAttribArray(_colorAttrib);
    
    // Delete EBO
    glDeleteBuffers(1, &_elementBufferObjectName);
    OGL_GET_GL_ERROR();
    
    // Unbind VBO
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    OGL_GET_GL_ERROR();
    
    // Delete VBO
    glDeleteBuffers(1, &_vertexBufferObjectName);
    OGL_GET_GL_ERROR();
    
    // Delete shader program
    glDeleteProgram(_programID);
    OGL_GET_GL_ERROR();
    
    // Unbind VAO
    glBindVertexArray(0);
    OGL_GET_GL_ERROR();
    
    // Delete VAO
    glDeleteVertexArrays(1, &_vertexArrayObjectName);
    OGL_GET_GL_ERROR();
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
    OGL_GET_GL_ERROR();

    glEnable(GL_SCISSOR_TEST);
    OGL_GET_GL_ERROR();
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
    OGL_GET_GL_ERROR();
    
    glScissor(x2, y2, w2, h2);
    glClearColor(0.0f,1.0f,0.0f,1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    OGL_GET_GL_ERROR();
    
    glScissor(x3, y3, w3, h3);
    glClearColor(0.0f,0.0f,1.0f,1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    OGL_GET_GL_ERROR();
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
// OGLExampleCircle                                                           //
////////////////////////////////////////////////////////////////////////////////

/*
 * Function that handles the drawing of a circle using the triangle fan
 * method. This will create a filled circle.
 *
 * Params:
 *	x (GLFloat) - the x position of the center point of the circle
 *	y (GLFloat) - the y position of the center point of the circle
 *	radius (GLFloat) - the radius that the painted circle will have
 */
GLfloat* drawFilledCircle(GLfloat x, GLfloat y, GLfloat radius){
    GLfloat triangleAmount = 100.0f; //# of triangles used to draw circle
    
    //GLfloat radius = 0.8f; //radius
    GLfloat twicePi = 2.0f * M_PI;
    GLfloat *vertices = (GLfloat*)malloc(triangleAmount*3*sizeof(GLfloat));
    if (vertices == NULL) {
        abort();
    }
    
    for(unsigned i = 0; i <= triangleAmount;i++) {
        float theta = twicePi * float(i) / float(triangleAmount);//get the current angle
        float cx = radius * cosf(theta);//calculate the x component
        float cy = radius * sinf(theta);//calculate the y component
        
        vertices[3*i] = cx;//x + (radius * cos(i *  twicePi / triangleAmount));
        vertices[3*i + 1] = cy;// y + (radius * sin(i * twicePi / triangleAmount));
        vertices[3*i + 2] = 0.0f;
    }
    return vertices;
}

void OGLExampleCircle::init(const void* arg)
{
    glGenVertexArrays(1, &_vertexArrayObjectName);
    OGL_GET_GL_ERROR();
    glBindVertexArray(_vertexArrayObjectName);
    OGL_GET_GL_ERROR();
    
    glDisable(GL_BLEND);
    glDisable(GL_CULL_FACE);
    glDisable(GL_LINE_SMOOTH);
    glDisable(GL_SCISSOR_TEST);
    glDisable(GL_DEPTH_TEST);
    OGL_GET_GL_ERROR();
    
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    OGL_GET_GL_ERROR();
    
    NSString *vhs = [[NSBundle mainBundle] pathForResource:@"RedTriangle"
                                                    ofType:@"vsh"];
    NSString *fhs = [[NSBundle mainBundle] pathForResource:@"RedTriangle"
                                                    ofType:@"fsh"];
    _programID = load_shaders(vhs.UTF8String,fhs.UTF8String);
    OGL_GET_GL_ERROR();
    
    vhs = nil;
    fhs = nil;
    
    // Use our shader
    glUseProgram(_programID);
    
    // An array of 3 vectors which represents 3 vertices
//    static const GLfloat vertex_data[] = {
//        -1.0f, -1.0f, 0.0f,
//        1.0f, -1.0f, 0.0f,
//        0.0f,  1.0f, 0.0f,
//    };
    GLfloat *vertex_data = drawFilledCircle(0,0,1);
    
    ///////////////////
    // Draw triangle //
    ///////////////////
    
    // Generate 1 buffer, put the resulting identifier in vertexbuffer
    glGenBuffers(1, &_vertexbufferObject);
    
    // The following commands will talk about our 'vertexbuffer' buffer
    glBindBuffer(GL_ARRAY_BUFFER, _vertexbufferObject);
    
    // Give our vertices to OpenGL.
    GLsizeiptr size = sizeof(vertex_data);
    glBufferData(GL_ARRAY_BUFFER, size, vertex_data, GL_STATIC_DRAW);
    
    // 1rst attribute buffer : vertices
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, _vertexbufferObject);
    glVertexAttribPointer(
                          0,                  // attribute 0. No particular
                          // reason for 0, but must match
                          // the layout in the shader.
                          3,                  // size
                          GL_FLOAT,           // type
                          GL_FALSE,           // normalized?
                          3*sizeof(GLfloat),                  // stride
                          (void*)0            // array buffer offset
                          );

    // Unbind VAO
    glBindVertexArray(0);
    OGL_GET_GL_ERROR();
}

void OGLExampleCircle::renderForTime(const CVTimeStamp * outputTime)
{
    // Bind VAO
    glBindVertexArray(_vertexArrayObjectName);
    OGL_GET_GL_ERROR();
    
    glClear(GL_COLOR_BUFFER_BIT);
    OGL_GET_GL_ERROR();
    
    glDrawArrays(GL_LINE_LOOP, 0, 20);
    
    // Unbind VAO
    glBindVertexArray(0);
    OGL_GET_GL_ERROR();
}

void OGLExampleCircle::didUpdateWindowRect(NSRect rect)
{
    glViewport(rect.origin.x, rect.origin.y, rect.size.width, rect.size.height);
}

void OGLExampleCircle::setColor(float r,float g,float b,float a)
{
    glClearColor(r,g,b,a);
    OGL_GET_GL_ERROR();
}

OGLExampleCircle::~OGLExampleCircle()
{
    // Is it really usefull?
    glDisableVertexAttribArray(0);

    // Delete buffer
    glDeleteBuffers(1, &_vertexbufferObject);
    OGL_GET_GL_ERROR();

    glDeleteVertexArrays(1, &_vertexArrayObjectName);
    OGL_GET_GL_ERROR();
}

////////////////////////////////////////////////////////////////////////////////











////////////////////////////////////////////////////////////////////////////////
// OGLExampleTexture1                                                         //
////////////////////////////////////////////////////////////////////////////////

std::string OGLExampleTexture1::name()
{
    return "Texture Basic";
}

void OGLExampleTexture1::init(const void* arg)
{
    ///////////////////
    // Create VAO    //
    ///////////////////
    
    // Create and Bind VAO
    glGenVertexArrays(1, &_vertexArrayObjectName);
    OGL_GET_GL_ERROR();
    glBindVertexArray(_vertexArrayObjectName);
    OGL_GET_GL_ERROR();
    
    ///////////////////
    // Others        //
    ///////////////////
    
    glDisable(GL_BLEND);
    glDisable(GL_CULL_FACE);
    glDisable(GL_LINE_SMOOTH);
    glDisable(GL_SCISSOR_TEST);
    glDisable(GL_DEPTH_TEST);
    OGL_GET_GL_ERROR();
    
    ///////////////////
    // Create VBO    //
    ///////////////////
    
    // Generate 3 buffers
    // first : vertices
    // Second : Texture Coordinate
    // Third : EBO
    glGenBuffers(3, _vertexBufferObjectName);
    OGL_GET_GL_ERROR();
    
    // Vertices
    static const GLfloat vertex_data[] = {
        -1.0f,  1.0f, // Top-left
         1.0f,  1.0f, // Top-right
         1.0f, -1.0f, // Bottom-right
        -1.0f, -1.0f, // Bottom-left
    };
    
    // Bind our vertices
    glBindBuffer(GL_ARRAY_BUFFER, _vertexBufferObjectName[0]);
    OGL_GET_GL_ERROR();
    // Give our vertices to OpenGL.
    glBufferData(GL_ARRAY_BUFFER,
                 sizeof(vertex_data),
                 vertex_data,
                 GL_STATIC_DRAW
                 );
    OGL_GET_GL_ERROR();
    
    // Texture coordinate
    static const GLfloat textureCoor_data[] = {
        0.0f, 0.0f, // Top-left
        1.0f, 0.0f, // Top-right
        1.0f, 1.0f, // Bottom-right
        0.0f, 1.0f  // Bottom-left
    };
    
    // Bind the texture coordinates
    glBindBuffer(GL_ARRAY_BUFFER, _vertexBufferObjectName[1]);
    OGL_GET_GL_ERROR();
    // Give the coordinates to OpenGL.
    glBufferData(GL_ARRAY_BUFFER,
                 sizeof(textureCoor_data),
                 textureCoor_data,
                 GL_STATIC_DRAW
                 );
    OGL_GET_GL_ERROR();
    
    // Element Buffer Object
    GLuint elements[] = {
        0, 1, 2,
        2, 3, 0
    };
    
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _vertexBufferObjectName[2]);
    OGL_GET_GL_ERROR();
    glBufferData(GL_ELEMENT_ARRAY_BUFFER,
                 sizeof(elements),
                 elements,
                 GL_STATIC_DRAW
                 );
    OGL_GET_GL_ERROR();
    
    ///////////////////
    // Load Shaders  //
    ///////////////////
    
    NSString *vhs = [[NSBundle mainBundle] pathForResource:@"Texture1"
                                                    ofType:@"vsh"];
    NSString *fhs = [[NSBundle mainBundle] pathForResource:@"Texture1"
                                                    ofType:@"fsh"];
    _programID = load_shaders(vhs.UTF8String,fhs.UTF8String);
    OGL_GET_GL_ERROR();
    
    // Use our shader
    glUseProgram(_programID);
    OGL_GET_GL_ERROR();
    
    ////////////////////////////////////////////
    // Specify the layout of the vertex data  //
    ////////////////////////////////////////////
    
    _positionAttrib = glGetAttribLocation(_programID, "inPosition");
    OGL_GET_GL_ERROR();
    glEnableVertexAttribArray(_positionAttrib);
    OGL_GET_GL_ERROR();
    glBindBuffer(GL_ARRAY_BUFFER, _vertexBufferObjectName[0]);
    OGL_GET_GL_ERROR();
    glVertexAttribPointer(
                          _positionAttrib,    // attribute index
                          2,                  // size
                          GL_FLOAT,           // type
                          GL_FALSE,           // normalized?
                          0,                  // stride
                          OGL_BUFFER_OFFSET(0)// array buffer offset
                          );
    OGL_GET_GL_ERROR();
    
    _textureAttrib = glGetAttribLocation(_programID, "inTextureCoord");
    OGL_GET_GL_ERROR();
    glEnableVertexAttribArray(_textureAttrib);
    OGL_GET_GL_ERROR();
    glBindBuffer(GL_ARRAY_BUFFER, _vertexBufferObjectName[1]);
    OGL_GET_GL_ERROR();
    glVertexAttribPointer(_textureAttrib,
                          2,
                          GL_FLOAT,
                          GL_FALSE,
                          0,
                          OGL_BUFFER_OFFSET(0)
                          );
    OGL_GET_GL_ERROR();
    
    ////////////////////////////////
    // Load Texture               //
    ////////////////////////////////

    // The following seems set by default
 
    // Get a handle for our "tex" uniform
    // Default is already 0
    GLint textureUniformLocation = glGetUniformLocation(_programID, "tex");
    OGL_GET_GL_ERROR();
    glUniform1i(textureUniformLocation, 0);                 // Set our "tex" sampler to user Texture Unit 0
    OGL_GET_GL_ERROR();
    glActiveTexture(GL_TEXTURE0);                           // Bind our texture in Texture Unit 0
    OGL_GET_GL_ERROR();
    
    // Not needed?
    glGenTextures( 1, &_textureBufferObjectName );
    glBindTexture(GL_TEXTURE_2D, _textureBufferObjectName);
    OGL_GET_GL_ERROR();
    
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

    // Texture looks like
    //     -----------------
    //     | WHITE | GREEN |
    //     -----------------
    //     | GREEN | WHITE |
    //     -----------------
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
    OGL_GET_GL_ERROR();
    
    // Unbind current program
    glUseProgram(0);
    OGL_GET_GL_ERROR();
    
    // Unbind VAO
    glBindVertexArray(0);
    OGL_GET_GL_ERROR();
}

void OGLExampleTexture1::renderForTime(const CVTimeStamp * outputTime)
{
    // Bind VAO
    glBindVertexArray(_vertexArrayObjectName);
    OGL_GET_GL_ERROR();
    
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    OGL_GET_GL_ERROR();
    glClear(GL_COLOR_BUFFER_BIT);
    OGL_GET_GL_ERROR();
    
    // Use our shader
    glUseProgram(_programID);
    OGL_GET_GL_ERROR();
    
    // Use our texture
    glActiveTexture(GL_TEXTURE0);
    OGL_GET_GL_ERROR();
    glBindTexture(GL_TEXTURE_2D, _textureBufferObjectName);
    OGL_GET_GL_ERROR();
    
    // Draw the square ( 2 triangles )
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    OGL_GET_GL_ERROR();

    // Unbind current program
    glUseProgram(0);
    OGL_GET_GL_ERROR();
    
    // Unbind VAO
    glBindVertexArray(0);
    OGL_GET_GL_ERROR();
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
    OGL_GET_GL_ERROR();
    
    glDisableVertexAttribArray(_positionAttrib);
    glDisableVertexAttribArray(_textureAttrib);
    
    // Delete Texture
//    glDeleteTextures(1, &_textureBufferObjectName);
//    GetGLError();
    
    // Unbind VBO
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    OGL_GET_GL_ERROR();
    
    // Delete VBO
    glDeleteBuffers(3, _vertexBufferObjectName);
    OGL_GET_GL_ERROR();
    
    // Delete shader program
    glDeleteProgram(_programID);
    OGL_GET_GL_ERROR();
    
    // Unbind VAO
    glBindVertexArray(0);
    OGL_GET_GL_ERROR();
    
    // Delete VAO
    glDeleteVertexArrays(1, &_vertexArrayObjectName);
    OGL_GET_GL_ERROR();
}

////////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////////////
// OGLExampleTexture2                                                         //
////////////////////////////////////////////////////////////////////////////////

std::string OGLExampleTexture2::name()
{
    return "Texture Bitmap Wrong";
}

void OGLExampleTexture2::init(const void* arg)
{
    ///////////////////
    // Create VAO    //
    ///////////////////
    
    // Create and Bind VAO
    glGenVertexArrays(1, &_vertexArrayObjectName);
    OGL_GET_GL_ERROR();
    glBindVertexArray(_vertexArrayObjectName);
    OGL_GET_GL_ERROR();
    
    ///////////////////
    // Others        //
    ///////////////////
    
    glDisable(GL_BLEND);
    glDisable(GL_CULL_FACE);
    glDisable(GL_LINE_SMOOTH);
    glDisable(GL_SCISSOR_TEST);
    glDisable(GL_DEPTH_TEST);
    OGL_GET_GL_ERROR();
    
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
    _programID = load_shaders(vhs.UTF8String,fhs.UTF8String);
    OGL_GET_GL_ERROR();
    
    // Use our shader
    glUseProgram(_programID);
    OGL_GET_GL_ERROR();
    
    ////////////////////////////////
    // Draw into the back buffer  //
    ////////////////////////////////
    
    // Specify the layout of the vertex data
    _positionAttrib = glGetAttribLocation(_programID, "inPosition");
    OGL_GET_GL_ERROR();
    glEnableVertexAttribArray(_positionAttrib);
    OGL_GET_GL_ERROR();
    glVertexAttribPointer(
                          _positionAttrib,    // attribute index
                          2,                  // size
                          GL_FLOAT,           // type
                          GL_FALSE,           // normalized?
                          4*sizeof(GLfloat),  // stride
                          OGL_BUFFER_OFFSET(0)// array buffer offset
                          );
    OGL_GET_GL_ERROR();

    _textureAttrib = glGetAttribLocation(_programID, "inTextureCoord");
    OGL_GET_GL_ERROR();
    glEnableVertexAttribArray(_textureAttrib);
    OGL_GET_GL_ERROR();
    glVertexAttribPointer(_textureAttrib,
                          2,
                          GL_FLOAT,
                          GL_FALSE,
                          4*sizeof(GLfloat),
                          OGL_BUFFER_OFFSET(2*sizeof(GLfloat))
                          );
    OGL_GET_GL_ERROR();

    ////////////////////////////////
    // Load Texture               //
    ////////////////////////////////

     // Get a handle for our "myTextureSampler" uniform
     // Default ?????
    GLint textureUniformLocation = glGetUniformLocation(_programID, "tex");
    OGL_GET_GL_ERROR();
    glUniform1i(textureUniformLocation, 0); // Set our "myTextureSampler" sampler to user Texture Unit 0
    OGL_GET_GL_ERROR();
    glActiveTexture(GL_TEXTURE0); // Bind our texture in Texture Unit 0
    OGL_GET_GL_ERROR();

    // Not needed?
    glGenTextures( 1, &_textureBufferObjectName );
    glBindTexture(GL_TEXTURE_2D, _textureBufferObjectName);
    OGL_GET_GL_ERROR();
    
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
    const char *path = [[[NSBundle mainBundle] pathForResource:@"sample2"
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
    OGL_GET_GL_ERROR();

    //////////////////////////////////
    // Create Element Buffer Object //
    //////////////////////////////////
    
    GLuint elements[] = {
        0, 1, 2,
        2, 3, 0
    };
    
    glGenBuffers(1, &_elementBufferObjectName);
    OGL_GET_GL_ERROR();
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _elementBufferObjectName);
    OGL_GET_GL_ERROR();
    glBufferData(GL_ELEMENT_ARRAY_BUFFER,
                 sizeof(elements),
                 elements,
                 GL_STATIC_DRAW
                 );
    OGL_GET_GL_ERROR();
    
    // Unbind current program
    glUseProgram(0);
    OGL_GET_GL_ERROR();

    // Unbind VAO
    glBindVertexArray(0);
    OGL_GET_GL_ERROR();
}

void OGLExampleTexture2::renderForTime(const CVTimeStamp * outputTime)
{
    // Bind VAO
    glBindVertexArray(_vertexArrayObjectName);
    OGL_GET_GL_ERROR();
    
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    OGL_GET_GL_ERROR();
    glClear(GL_COLOR_BUFFER_BIT);
    OGL_GET_GL_ERROR();
    
    // Use our shader
    glUseProgram(_programID);
    OGL_GET_GL_ERROR();

    // Use our texture
    glActiveTexture(GL_TEXTURE0);
    OGL_GET_GL_ERROR();
    glBindTexture(GL_TEXTURE_2D, _textureBufferObjectName);
    OGL_GET_GL_ERROR();
    
    // Draw the square ( 2 triangles )
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    OGL_GET_GL_ERROR();

    // Unbind current program
    glUseProgram(0);
    OGL_GET_GL_ERROR();
    
    // Unbind VAO
    glBindVertexArray(0);
    OGL_GET_GL_ERROR();
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
    OGL_GET_GL_ERROR();
    
    glDisableVertexAttribArray(_positionAttrib);
    glDisableVertexAttribArray(_textureAttrib);

    // Delete EBO
    glDeleteBuffers(1, &_elementBufferObjectName);
    OGL_GET_GL_ERROR();
    
    // Delete Texture
    glDeleteBuffers(1, &_textureBufferObjectName);
    OGL_GET_GL_ERROR();

    // Unbind VBO
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    OGL_GET_GL_ERROR();
    
    // Delete VBO
    glDeleteBuffers(1, &_vertexBufferObjectName);
    OGL_GET_GL_ERROR();
    
    // Delete shader program
    glDeleteProgram(_programID);
    OGL_GET_GL_ERROR();
    
    // Unbind VAO
    glBindVertexArray(0);
    OGL_GET_GL_ERROR();
    
    // Delete VAO
    glDeleteVertexArrays(1, &_vertexArrayObjectName);
    OGL_GET_GL_ERROR();
}

////////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////////////
// OGLExampleTexture3                                                         //
////////////////////////////////////////////////////////////////////////////////

std::string OGLExampleTexture3::name()
{
    return "Texture Bitmap Correct";
}

void OGLExampleTexture3::init(const void* arg)
{
    ///////////////////
    // Create VAO    //
    ///////////////////
    
    // Create and Bind VAO
    glGenVertexArrays(1, &_vertexArrayObjectName);
    OGL_GET_GL_ERROR();
    glBindVertexArray(_vertexArrayObjectName);
    OGL_GET_GL_ERROR();
    
    ///////////////////
    // Others        //
    ///////////////////
    
    glDisable(GL_BLEND);
    glDisable(GL_CULL_FACE);
    glDisable(GL_LINE_SMOOTH);
    glDisable(GL_SCISSOR_TEST);
    glDisable(GL_DEPTH_TEST);
    OGL_GET_GL_ERROR();
    
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
    _programID = load_shaders(vhs.UTF8String,fhs.UTF8String);
    OGL_GET_GL_ERROR();
    
    // Use our shader
    glUseProgram(_programID);
    OGL_GET_GL_ERROR();
    
    ////////////////////////////////
    // Draw into the back buffer  //
    ////////////////////////////////
    
    // Specify the layout of the vertex data
    _positionAttrib = glGetAttribLocation(_programID, "inPosition");
    OGL_GET_GL_ERROR();
    glEnableVertexAttribArray(_positionAttrib);
    OGL_GET_GL_ERROR();
    glVertexAttribPointer(
                          _positionAttrib,    // attribute index
                          2,                  // size
                          GL_FLOAT,           // type
                          GL_FALSE,           // normalized?
                          4*sizeof(GLfloat),  // stride
                          OGL_BUFFER_OFFSET(0)// array buffer offset
                          );
    OGL_GET_GL_ERROR();
    
    _textureAttrib = glGetAttribLocation(_programID, "inTextureCoord");
    OGL_GET_GL_ERROR();
    glEnableVertexAttribArray(_textureAttrib);
    OGL_GET_GL_ERROR();
    glVertexAttribPointer(_textureAttrib,
                          2,
                          GL_FLOAT,
                          GL_FALSE,
                          4*sizeof(GLfloat),
                          OGL_BUFFER_OFFSET(2*sizeof(GLfloat))
                          );
    OGL_GET_GL_ERROR();
    
    ////////////////////////////////
    // Load Texture               //
    ////////////////////////////////
    
    // Get a handle for our "tex" uniform
    // Default ?????
    GLint textureUniformLocation = glGetUniformLocation(_programID, "tex");
    OGL_GET_GL_ERROR();
    glUniform1i(textureUniformLocation, 0); // Set our "tex" sampler to user Texture Unit 0
    OGL_GET_GL_ERROR();
    glActiveTexture(GL_TEXTURE0); // Bind our texture in Texture Unit 0
    OGL_GET_GL_ERROR();
    
    // Not needed?
    glGenTextures( 1, &_textureBufferObjectName );
    glBindTexture(GL_TEXTURE_2D, _textureBufferObjectName);
    OGL_GET_GL_ERROR();
    
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
    const char *path = [[[NSBundle mainBundle] pathForResource:@"sample2"
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
    OGL_GET_GL_ERROR();
    
    //////////////////////////////////
    // Create Element Buffer Object //
    //////////////////////////////////
    
    GLuint elements[] = {
        0, 1, 2,
        2, 3, 0
    };
    
    glGenBuffers(1, &_elementBufferObjectName);
    OGL_GET_GL_ERROR();
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _elementBufferObjectName);
    OGL_GET_GL_ERROR();
    glBufferData(GL_ELEMENT_ARRAY_BUFFER,
                 sizeof(elements),
                 elements,
                 GL_STATIC_DRAW
                 );
    OGL_GET_GL_ERROR();
    
    // Unbind current program
    glUseProgram(0);
    OGL_GET_GL_ERROR();
    
    // Unbind VAO
    glBindVertexArray(0);
    OGL_GET_GL_ERROR();
}

void OGLExampleTexture3::renderForTime(const CVTimeStamp * outputTime)
{
    // Bind VAO
    glBindVertexArray(_vertexArrayObjectName);
    OGL_GET_GL_ERROR();
    
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    OGL_GET_GL_ERROR();
    glClear(GL_COLOR_BUFFER_BIT);
    OGL_GET_GL_ERROR();
    
    // Use our shader
    glUseProgram(_programID);
    OGL_GET_GL_ERROR();
    
    // Use our texture
    glActiveTexture(GL_TEXTURE0);
    OGL_GET_GL_ERROR();
    glBindTexture(GL_TEXTURE_2D, _textureBufferObjectName);
    OGL_GET_GL_ERROR();
    
    // Draw the square ( 2 triangles )
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    OGL_GET_GL_ERROR();

    // Unbind current program
    glUseProgram(0);
    OGL_GET_GL_ERROR();
    
    // Unbind VAO
    glBindVertexArray(0);
    OGL_GET_GL_ERROR();
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
    OGL_GET_GL_ERROR();
    
    glDisableVertexAttribArray(_positionAttrib);
    glDisableVertexAttribArray(_textureAttrib);
    
    // Delete EBO
    glDeleteBuffers(1, &_elementBufferObjectName);
    OGL_GET_GL_ERROR();
    
    // Delete Texture
    glDeleteBuffers(1, &_textureBufferObjectName);
    OGL_GET_GL_ERROR();
    
    // Unbind VBO
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    OGL_GET_GL_ERROR();
    
    // Delete VBO
    glDeleteBuffers(1, &_vertexBufferObjectName);
    OGL_GET_GL_ERROR();
    
    // Delete shader program
    glDeleteProgram(_programID);
    OGL_GET_GL_ERROR();

    // Delete Texture
    glDeleteTextures(1, &_textureBufferObjectName);

    // Unbind VAO
    glBindVertexArray(0);
    OGL_GET_GL_ERROR();
    
    // Delete VAO
    glDeleteVertexArrays(1, &_vertexArrayObjectName);
    OGL_GET_GL_ERROR();
}

////////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////////////
// OGLExampleTexture4                                                         //
////////////////////////////////////////////////////////////////////////////////

std::string OGLExampleTexture4::name()
{
    return "Texture Blend";
}

void OGLExampleTexture4::init(const void* arg)
{
    ///////////////////
    // Create VAO    //
    ///////////////////
    
    // Create and Bind VAO
    glGenVertexArrays(1, &_vertexArrayObjectName);
    OGL_GET_GL_ERROR();
    glBindVertexArray(_vertexArrayObjectName);
    OGL_GET_GL_ERROR();
    
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
    OGL_GET_GL_ERROR();
    // The following commands will talk about our 'vertexbuffer' buffer
    glBindBuffer(GL_ARRAY_BUFFER, _vertexBufferObjectName);
    OGL_GET_GL_ERROR();
    // Give our vertices to OpenGL.
    GLsizeiptr size = sizeof(vertex_data);
    glBufferData(GL_ARRAY_BUFFER, size, vertex_data, GL_STATIC_DRAW);
    OGL_GET_GL_ERROR();

    ///////////////////
    // Others        //
    ///////////////////
    
    glDisable(GL_BLEND);
    glDisable(GL_CULL_FACE);
    glDisable(GL_LINE_SMOOTH);
    glDisable(GL_SCISSOR_TEST);
    glDisable(GL_DEPTH_TEST);
    OGL_GET_GL_ERROR();
    
    ///////////////////
    // Load Shaders  //
    ///////////////////
    
    NSString *vhs = [[NSBundle mainBundle] pathForResource:@"Texture4"
                                                    ofType:@"vsh"];
    NSString *fhs = [[NSBundle mainBundle] pathForResource:@"Texture4"
                                                    ofType:@"fsh"];
    _programID = load_shaders(vhs.UTF8String,fhs.UTF8String);
    OGL_GET_GL_ERROR();
    
    // Use our shader
    glUseProgram(_programID);
    OGL_GET_GL_ERROR();
    
    ////////////////////////////////
    // Draw into the back buffer  //
    ////////////////////////////////
    
    // Specify the layout of the vertex data
    _positionAttrib = glGetAttribLocation(_programID, "inPosition");
    glEnableVertexAttribArray(_positionAttrib);
    glVertexAttribPointer(
                          _positionAttrib,    // attribute index
                          2,                  // size
                          GL_FLOAT,           // type
                          GL_FALSE,           // normalized?
                          7*sizeof(GLfloat),  // stride
                          OGL_BUFFER_OFFSET(0)// array buffer offset
                          );
    
    _colorAttrib = glGetAttribLocation(_programID, "inColor");
    glEnableVertexAttribArray(_colorAttrib);
    glVertexAttribPointer(_colorAttrib,
                          3,
                          GL_FLOAT,
                          GL_FALSE,
                          7*sizeof(GLfloat),
                          OGL_BUFFER_OFFSET(2*sizeof(GLfloat))
                          );
    
    _textureAttrib = glGetAttribLocation(_programID, "inTextureCoord");
    glEnableVertexAttribArray(_textureAttrib);
    glVertexAttribPointer(_textureAttrib,
                          2,
                          GL_FLOAT,
                          GL_FALSE,
                          7*sizeof(GLfloat),
                          OGL_BUFFER_OFFSET(5*sizeof(GLfloat))
                          );
    
    ////////////////////////////////
    // Load Texture               //
    ////////////////////////////////
    
     NSString *path = [[NSBundle mainBundle] pathForResource:@"sample2"
                                                      ofType:@"bmp"];
     NSDictionary *options = @{GLKTextureLoaderOriginBottomLeft:@NO};
     GLKTextureInfo* info =
     [GLKTextureLoader textureWithContentsOfFile:path
                                         options:options
                                           error:nil];
     
     // Optional : Default is already set to 0
     // Bind our texture in Texture Unit 0
     glActiveTexture(GL_TEXTURE10);
     OGL_GET_GL_ERROR();
     glBindTexture(GL_TEXTURE_2D, info.name);
     OGL_GET_GL_ERROR();
     GLint textureUniformLocation  = glGetUniformLocation(_programID, "tex");
     OGL_GET_GL_ERROR();
     // Set our "myTextureSampler" sampler to user Texture Unit 0
     glUniform1i(textureUniformLocation, 10);
     OGL_GET_GL_ERROR();
    
    //////////////////////////////////
    // Create Element Buffer Object //
    //////////////////////////////////
    
    GLuint elements[] = {
        0, 1, 2,
        2, 3, 0
    };
    
    glGenBuffers(1, &_elementBufferObjectName);
    OGL_GET_GL_ERROR();
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _elementBufferObjectName);
    OGL_GET_GL_ERROR();
    glBufferData(GL_ELEMENT_ARRAY_BUFFER,
                 sizeof(elements),
                 elements,
                 GL_STATIC_DRAW
                 );
    OGL_GET_GL_ERROR();
    
    // Unbind current program
    glUseProgram(0);
    OGL_GET_GL_ERROR();
    
    // Unbind VAO
    glBindVertexArray(0);
    OGL_GET_GL_ERROR();
}

void OGLExampleTexture4::renderForTime(const CVTimeStamp * outputTime)
{
    // Bind VAO
    glBindVertexArray(_vertexArrayObjectName);
    OGL_GET_GL_ERROR();
    
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    OGL_GET_GL_ERROR();
    glClear(GL_COLOR_BUFFER_BIT);
    OGL_GET_GL_ERROR();
    
    // Use our shader
    glUseProgram(_programID);
    OGL_GET_GL_ERROR();

    // Use our texture
    glActiveTexture(GL_TEXTURE0);
    OGL_GET_GL_ERROR();
    glBindTexture(GL_TEXTURE_2D, _textureBufferObjectName);
    OGL_GET_GL_ERROR();
    
    // Draw the square ( 2 triangles )
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    OGL_GET_GL_ERROR();
    
    // Unbind current program
    glUseProgram(0);
    OGL_GET_GL_ERROR();
    
    // Unbind VAO
    glBindVertexArray(0);
    OGL_GET_GL_ERROR();
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
    OGL_GET_GL_ERROR();
    
    glDisableVertexAttribArray(_positionAttrib);
    glDisableVertexAttribArray(_colorAttrib);
    glDisableVertexAttribArray(_textureAttrib);
    
    // Delete EBO
    glDeleteBuffers(1, &_elementBufferObjectName);
    OGL_GET_GL_ERROR();
    
    // Unbind VBO
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    OGL_GET_GL_ERROR();
    
    // Delete VBO
    glDeleteBuffers(1, &_vertexBufferObjectName);
    OGL_GET_GL_ERROR();
    
    // Delete shader program
    glDeleteProgram(_programID);
    OGL_GET_GL_ERROR();
    
    // Delete Texture
    glDeleteTextures(1, &_textureBufferObjectName);
    
    // Unbind VAO
    glBindVertexArray(0);
    OGL_GET_GL_ERROR();
    
    // Delete VAO
    glDeleteVertexArrays(1, &_vertexArrayObjectName);
    OGL_GET_GL_ERROR();
}

////////////////////////////////////////////////////////////////////////////////

