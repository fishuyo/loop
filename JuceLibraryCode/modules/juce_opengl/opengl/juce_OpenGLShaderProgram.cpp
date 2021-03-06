/*
  ==============================================================================

   This file is part of the JUCE library - "Jules' Utility Class Extensions"
   Copyright 2004-11 by Raw Material Software Ltd.

  ------------------------------------------------------------------------------

   JUCE can be redistributed and/or modified under the terms of the GNU General
   Public License (Version 2), as published by the Free Software Foundation.
   A copy of the license is included in the JUCE distribution, or can be found
   online at www.gnu.org/licenses.

   JUCE is distributed in the hope that it will be useful, but WITHOUT ANY
   WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR
   A PARTICULAR PURPOSE.  See the GNU General Public License for more details.

  ------------------------------------------------------------------------------

   To release a closed-source product which uses JUCE, commercial licenses are
   available: visit www.rawmaterialsoftware.com/juce for more information.

  ==============================================================================
*/

#if JUCE_USE_OPENGL_SHADERS

OpenGLShaderProgram::OpenGLShaderProgram (const OpenGLContext& context_) noexcept
    : context (context_)
{
    // This object can only be created and used when the current thread has an active OpenGL context.
    jassert (OpenGLHelpers::isContextActive());

    programID = context.extensions.glCreateProgram();
}

OpenGLShaderProgram::~OpenGLShaderProgram() noexcept
{
    context.extensions.glDeleteProgram (programID);
}

double OpenGLShaderProgram::getLanguageVersion()
{
   #if JUCE_OPENGL_ES
    jassertfalse; // doesn't work in ES
    return 0;
   #else
    return String ((const char*) glGetString (GL_SHADING_LANGUAGE_VERSION))
            .upToFirstOccurrenceOf (" ", false, false).getDoubleValue();
   #endif
}

bool OpenGLShaderProgram::addShader (const char* const code, GLenum type)
{
    GLuint shaderID = context.extensions.glCreateShader (type);
    context.extensions.glShaderSource (shaderID, 1, (const GLchar**) &code, nullptr);
    context.extensions.glCompileShader (shaderID);

    GLint status = GL_FALSE;
    context.extensions.glGetShaderiv (shaderID, GL_COMPILE_STATUS, &status);

    if (status == GL_FALSE)
    {
        GLchar infoLog [16384];
        GLsizei infologLength = 0;
        context.extensions.glGetShaderInfoLog (shaderID, sizeof (infoLog), &infologLength, infoLog);
        errorLog = String (infoLog, infologLength);

       #if JUCE_DEBUG
        DBG (errorLog);
        jassertfalse;
       #endif

        return false;
    }

    context.extensions.glAttachShader (programID, shaderID);
    context.extensions.glDeleteShader (shaderID);
    return true;
}

bool OpenGLShaderProgram::link() noexcept
{
    context.extensions.glLinkProgram (programID);

    GLint status = GL_FALSE;
    context.extensions.glGetProgramiv (programID, GL_LINK_STATUS, &status);

    if (status == GL_FALSE)
    {
        GLchar infoLog [16384];
        GLsizei infologLength = 0;
        context.extensions.glGetProgramInfoLog (programID, sizeof (infoLog), &infologLength, infoLog);
        errorLog = String (infoLog, infologLength);

       #if JUCE_DEBUG
        DBG (errorLog);
        jassertfalse;
       #endif
    }

    return status != GL_FALSE;
}

void OpenGLShaderProgram::use() const noexcept
{
    context.extensions.glUseProgram (programID);
}

OpenGLShaderProgram::Uniform::Uniform (const OpenGLShaderProgram& program, const char* const name)
    : uniformID (program.context.extensions.glGetUniformLocation (program.programID, name)), context (program.context)
{
    jassert (uniformID >= 0);
}

OpenGLShaderProgram::Attribute::Attribute (const OpenGLShaderProgram& program, const char* name)
    : attributeID (program.context.extensions.glGetAttribLocation (program.programID, name))
{
    jassert (attributeID >= 0);
}

void OpenGLShaderProgram::Uniform::set (GLfloat n1) const noexcept                                    { context.extensions.glUniform1f (uniformID, n1); }
void OpenGLShaderProgram::Uniform::set (GLint n1) const noexcept                                      { context.extensions.glUniform1i (uniformID, n1); }
void OpenGLShaderProgram::Uniform::set (GLfloat n1, GLfloat n2) const noexcept                        { context.extensions.glUniform2f (uniformID, n1, n2); }
void OpenGLShaderProgram::Uniform::set (GLfloat n1, GLfloat n2, GLfloat n3) const noexcept            { context.extensions.glUniform3f (uniformID, n1, n2, n3); }
void OpenGLShaderProgram::Uniform::set (GLfloat n1, GLfloat n2, GLfloat n3, float n4) const noexcept  { context.extensions.glUniform4f (uniformID, n1, n2, n3, n4); }
void OpenGLShaderProgram::Uniform::set (GLint n1, GLint n2, GLint n3, GLint n4) const noexcept        { context.extensions.glUniform4i (uniformID, n1, n2, n3, n4); }
void OpenGLShaderProgram::Uniform::set (const GLfloat* values, GLsizei numValues) const noexcept      { context.extensions.glUniform1fv (uniformID, numValues, values); }

#endif
