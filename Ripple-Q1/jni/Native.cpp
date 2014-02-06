#include <jni.h>
#include <omp.h>
#include <GLES2/gl2.h>
#include "glm/glm.hpp"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

GLuint       g_hShaderProgram = 0;
GLuint       g_VertexLoc = 0;
GLuint       g_ColorLoc  = 1;
GLint uniform_mytexture;
GLint uniform_m_transform;
GLint uniform_time;
GLint attribute_coord2d;
GLint attribute_texcoord;
GLuint texture_id;
GLuint vbo_triangle, vbo_cube_texcoords;
GLuint program;
glm::mat4 MVP;
glm::mat4 V, P;
glm::vec3 Scale;
//--------------------------------------------------------------------------------------
// Name: g_strVSProgram / g_strFSProgram
// Desc: The vertex and fragment shader programs
//--------------------------------------------------------------------------------------
const char* g_strVSProgram =
    "attribute vec2 coord2d;				\n"
	"uniform mat4 m_transform;			\n"
    "attribute vec4 g_vColor;				 \n"
    "varying   vec4 g_vVSColor;                            \n"
    "																	 \n"
    "void main()														 \n"
    "{																	 \n"
    "    gl_Position  = m_transform*vec4(coord2d, 0.0, 1.0);     \n"
    "                                             \n"
    "}																	 \n";

const char* g_strFSProgram =
    "#ifdef GL_FRAGMENT_PRECISION_HIGH									 \n"
    "   precision highp float;											 \n"
    "#else																 \n"
    "   precision mediump float;										 \n"
    "#endif																 \n"
    "																	 \n"
    "varying   vec4 g_vVSColor;                                          \n"
    "																	 \n"
    "void main()														 \n"
    "{																	 \n"
    "    gl_FragColor[0] = gl_FragCoord.x/640.0;                          \n"
	"    gl_FragColor[1] = gl_FragCoord.y/480.0;                      \n"
	"    gl_FragColor[2] = 0.99;                                      \n"
    "}																	 \n";

void InitializeOpenGL()
{
	glClearColor(1.0f, 1.0f, 0.0f, 1.0f);
	 // Create the shader program needed to render the texture
	    {
	        // Compile the shaders
	        GLuint hVertexShader = glCreateShader( GL_VERTEX_SHADER );
	        glShaderSource( hVertexShader, 1, &g_strVSProgram, NULL );
	        glCompileShader( hVertexShader );

	        GLuint hFragmentShader = glCreateShader( GL_FRAGMENT_SHADER );
	        glShaderSource( hFragmentShader, 1, &g_strFSProgram, NULL );
	        glCompileShader( hFragmentShader );

	        // Check for compile success
	        GLint nCompileResult = 0;
		    glGetShaderiv(hFragmentShader, GL_COMPILE_STATUS, &nCompileResult);
		    if (!nCompileResult)
		    {
			    char Log[1024];
			    GLint nLength;
			    glGetShaderInfoLog(hFragmentShader, 1024, &nLength, Log);
			    //return false;
		    }

	        // Attach the individual shaders to the common shader program
	        g_hShaderProgram = glCreateProgram();
	        glAttachShader( g_hShaderProgram, hVertexShader );
	        glAttachShader( g_hShaderProgram, hFragmentShader );

	        GLfloat triangle_vertices[] = {
	        		     -1.0,  1.0,
	        		    1.0, 1.0,
	        		     1.0, -1.0,
	        		     -1.0,  1.0,
	        		      1.0, -1.0,
	        		      -1.0, -1.0,
	        		  };
	        	  glGenBuffers(1, &vbo_triangle);
	        	  glBindBuffer(GL_ARRAY_BUFFER, vbo_triangle);
	        	  glBufferData(GL_ARRAY_BUFFER, sizeof(triangle_vertices),
	        			  triangle_vertices, GL_STATIC_DRAW);
	        	  glBindBuffer(GL_ARRAY_BUFFER, 0);

	        // Init attributes BEFORE linking

	        glBindAttribLocation(g_hShaderProgram, g_ColorLoc, "g_vColor");

	        // Link the vertex shader and fragment shader together
	        glLinkProgram( g_hShaderProgram );

	        // Check for link success
	        GLint nLinkResult = 0;
		    glGetProgramiv(g_hShaderProgram, GL_LINK_STATUS, &nLinkResult);

		    if (!nLinkResult)
		    {
			    char Log[1024];
			    GLint nLength;
			    glGetProgramInfoLog(g_hShaderProgram, 1024, &nLength, Log);
			    //return false;
		    }
			const char* attribute_name = "coord2d";
			attribute_coord2d = glGetAttribLocation(g_hShaderProgram,
					attribute_name);
			if (attribute_coord2d == -1) {
				fprintf(stderr, "Could not bind attribute %s\n", attribute_name);
				//return 0;
			}
			const char* uniform_transformc = "m_transform";
			uniform_m_transform = glGetUniformLocation(g_hShaderProgram, uniform_transformc);
			if (uniform_m_transform == -1) {
				fprintf(stderr, "Could not bind uniform %s\n", uniform_transformc);
				//return 0;
			}

	        glDeleteShader( hVertexShader );
	        glDeleteShader( hFragmentShader );
	    }

}
void resizeViewport(int newWidth, int newHeight)
{
	glViewport(0, 0, newWidth, newHeight);
}
void renderFrame()
{
	//glClear(GL_COLOR_BUFFER_BIT);

	// Clear the backbuffer and depth-buffer
	glClearColor( 0.0f, 0.0f, 0.5f, 1.0f );
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

	// Set the shader program and the texture
	glUseProgram( g_hShaderProgram );
	float angle=0.0f;
	  	float  move=0.0f;move=0.5*glm::sin(omp_get_wtime());glm::vec3 Scale(move,move,move);
	         glm::vec3 axis_z(1.0f, 1.0f, 1.0f);
	    	  glm::vec3 scale(0.5f,0.5f,0.5f);
	    	  glm::mat4 m_transform = glm::translate(glm::mat4(1.0f), Scale)
	    	    * glm::rotate(glm::mat4(1.0f), angle, axis_z)*glm::scale(glm::mat4(1.0f),scale);

	    	  glUniformMatrix4fv(uniform_m_transform, 1, GL_FALSE, glm::value_ptr(m_transform));

	// Draw the colored triangle
	glBindBuffer(GL_ARRAY_BUFFER,vbo_triangle);
	    	glEnableVertexAttribArray(attribute_coord2d);
	    	 glVertexAttribPointer(
	    	            attribute_coord2d, // attribute
	    	            2,                 // number of elements per vertex, here (x,y)
	    	            GL_FLOAT,          // the type of each element
	    	            GL_FALSE,          // take our values as-is
	    	            0,                 // no extra data between each position
	    	            0  // pointer to the C array
	    	          );
	    	 glDrawArrays(GL_TRIANGLES,0,6);


	glDisableVertexAttribArray( attribute_coord2d );
}
