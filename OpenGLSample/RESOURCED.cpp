/*
Katie Stapleton
SNHU CS 330
Mod3 Milestone - Complex Object
05/23/2021
*/

#include <iostream>         // cout, cerr
#include <cstdlib>          // EXIT_FAILURE
#include <GL/glew.h>        // GLEW library
#include <GLFW/glfw3.h>     // GLFW library

// GLM Math Header inclusions
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/type_ptr.hpp>


// Shader program Macro
#ifndef GLSL
#define GLSL(Version, Source) "#version " #Version " core \n" #Source
#endif

using namespace std; // Standard namespace

namespace
{
    const char* const WINDOW_TITLE = "My Scene"; // Macro for window title

    // Variables for window width and height
    const int WINDOW_WIDTH = 800;
    const int WINDOW_HEIGHT = 600;

    // Stores the GL data relative to a given mesh
    struct GLMesh
    {
        GLuint vao;         // Handle for the vertex array object
        GLuint vbos[2];     // Handles for the vertex buffer objects
        GLuint nIndices;    // Number of indices of the mesh
    };

    // Main GLFW window
    GLFWwindow* gWindow = nullptr;
    // Triangle mesh data
    GLMesh gMesh;
    // Shader program
    GLuint gProgramId;
}



/////////////////////////////////
// define custom functions
// 
//  
// 
////////////////////////////////


bool initialize(int, char* [], GLFWwindow** window);
void resizeWindow(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);
void setCamera();
void setProjection();
bool createShaderProgram(const char* vtxShaderSource, const char* fragShaderSource, GLuint& programId);
void destroyShaderProgram(GLuint programId);

void draw1();
void draw2();

// PARTIAL COMPLETE - NEEDS RENDERING/DRAWING
// MAIN
int main(int argc, char* argv[])
{
    if (!initialize(argc, argv, &gWindow))
        return EXIT_FAILURE;

    // CREATE MESH
    cube

    // Create the shader program
    if (!createShaderProgram(vertexShaderSource, fragmentShaderSource, gProgramId))
        return EXIT_FAILURE;

    // render loop
    while (!glfwWindowShouldClose(gWindow))
    {
        // handles user input
        processInput(gWindow);

        // set project
        setCamera();
        setProjection();

        // draw/render frames
        Rendering();



        glfwPollEvents();
    }


    // RELEASE MESH


    // terminate shader program
    destroyShaderProgram(gProgramId);

    exit(EXIT_SUCCESS); // Terminates the program successfully
}


// DONE-----------------------
// Initialize GLFW, GLEW, and create a window with GLFW
bool initialize(int argc, char* argv[], GLFWwindow** window)
{
    // GLFW: initialize and configure
    // ------------------------------
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 4);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    // GLFW: window creation
    // ---------------------
    * window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_TITLE, NULL, NULL);
    if (*window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return false;
    }
    glfwMakeContextCurrent(*window);
    glfwSetFramebufferSizeCallback(*window, UResizeWindow);

    // GLEW: initialize
    // ----------------
    // Note: if using GLEW version 1.13 or earlier
    glewExperimental = GL_TRUE;
    GLenum GlewInitResult = glewInit();

    if (GLEW_OK != GlewInitResult)
    {
        std::cerr << glewGetErrorString(GlewInitResult) << std::endl;
        return false;
    }

    // Displays GPU OpenGL version
    cout << "INFO: OpenGL Version: " << glGetString(GL_VERSION) << endl;

    return true;
}


// DONE-----------------------
// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
void processInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}


// DONE-----------------------
// glfw: whenever the window size changed (by OS or user resize) this callback function executes
void resizeWindow(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}



// **** ADD TO FUNCTION ???? ********
// set projection for program (ortho or perspective)
// do not delete unused project. comment out only
void setProjection() 
{
    // creates orthogonal projection
    glm::mat4 projection = glm::ortho(-5.0f, 5.0f, -5.0f, 5.0f, 0.1f, 100.0f);

    /* ortho is currently active
    // creates a perspective projection
    glm::mat4 projection = glm::perspective(45.0f, (GLfloat)WINDOW_WIDTH / (GLfloat)WINDOW_HEIGHT, 0.1f, 100.0f);
    */
}

// *** ADD TO FUNCTION ???? *************
// sets camera position and viewing direction
void setCamera() {

    // Enable z-depth
    glEnable(GL_DEPTH_TEST);


 
      / //glMatrixMode(GL_MODELVIEW);
        //glLoadIdentity();
        //gluLookAt(posX, posY, posZ, targetX, targetY, targetZ, 0, 1, 0); // eye(x,y,z), focal(x,y,z), up(x,y,z)


    // Transforms the camera: move the camera back (z axis)
    glm::mat4 view = glm::translate(glm::vec3(0.0f, 0.0f, -5.0f));
}
/**/
void cube()
{
    // Position and Color data
    GLfloat verts[] = {
        // CUBE/cuboid  
        // SOURCE: Triangle strips https://stackoverflow.com/questions/28375338/cube-using-single-gl-triangle-strip
        // Vertex Positions    // Colors (r,g,b,a)
        1.0f,  1.0f, 1.0f,   1.0f, 0.0f, 0.0f, 1.0f, // 0 right top front 
        0.0f,  1.0f, 1.0f,   1.0f, 0.0f, 0.0f, 1.0f, // 1 left top front
        1.0f,  1.0f, 0.0f,   1.0f, 1.0f, 0.0f, 1.0f, // 2 right top back
        0.0f,  1.0f, 0.0f,   1.0f, 1.0f, 0.0f, 1.0f, // 3 left top back

         1.0f, 0.0f,  1.0f,  0.0f, 1.0f, 1.0f, 1.0f, // 4 right bottom front
         0.0f, 0.0f,  1.0f,  0.0f, 1.0f, 1.0f, 1.0f, // 5 left bottom front
         0.0f, 0.0f,  0.0f,  0.0f, 0.0f, 1.0f, 1.0f, // 6 right bottom back
         1.0f, 0.0f,  0.0f,  0.0f, 0.0f, 1.0f, 1.0f  // 7 left bottom back

    };

    // Index data to share position data
    GLushort indices[] = {
         3, 2, 6, 7, 4, 2, 0,
         3, 1, 6, 5, 4, 1, 0

    };

    createMesh(GLMesh & mesh)
};
*/
// Implements the UCreateMesh function
void createMesh(GLMesh& mesh)
{
    GLfloat verts[] = {
        // CUBE/cuboid  
        // SOURCE: Triangle strips https://stackoverflow.com/questions/28375338/cube-using-single-gl-triangle-strip
        // Vertex Positions    // Colors (r,g,b,a)
        1.0f,  1.0f, 1.0f,   1.0f, 0.0f, 0.0f, 1.0f, // 0 right top front 
        0.0f,  1.0f, 1.0f,   1.0f, 0.0f, 0.0f, 1.0f, // 1 left top front
        1.0f,  1.0f, 0.0f,   1.0f, 1.0f, 0.0f, 1.0f, // 2 right top back
        0.0f,  1.0f, 0.0f,   1.0f, 1.0f, 0.0f, 1.0f, // 3 left top back

         1.0f, 0.0f,  1.0f,  0.0f, 1.0f, 1.0f, 1.0f, // 4 right bottom front
         0.0f, 0.0f,  1.0f,  0.0f, 1.0f, 1.0f, 1.0f, // 5 left bottom front
         0.0f, 0.0f,  0.0f,  0.0f, 0.0f, 1.0f, 1.0f, // 6 right bottom back
         1.0f, 0.0f,  0.0f,  0.0f, 0.0f, 1.0f, 1.0f  // 7 left bottom back

    };

    // Index data to share position data
    GLushort indices[] = {
         3, 2, 6, 7, 4, 2, 0,
         3, 1, 6, 5, 4, 1, 0

    };


    GLfloat verts[] = {
        // CUBE/cuboid  
        // SOURCE: Triangle strips https://stackoverflow.com/questions/28375338/cube-using-single-gl-triangle-strip
        // Vertex Positions    // Colors (r,g,b,a)
        0.0f,  1.0f, 1.0f,   .0f, 0.0f, 0.0f, 1.0f, // 0 right top front 
        0.0f,  1.0f, 0.0f,   .0f, 0.0f, 0.0f, 1.0f, // 1 left top front
        1.0f,  1.0f, 0.0f,  .0f, 1.0f, 0.0f, 1.0f, // 2 right top back
        0.0f,  1.0f, 0.0f,  1.0f, 1.0f, 0.0f, 1.0f, // 3 left top back

         1.0f, 0.0f,  1.0f,  0.0f, 1.0f, 1.0f, 1.0f, // 4 right bottom front
         0.0f, 0.0f,  1.0f,  0.0f, 1.0f, 1.0f, 1.0f, // 5 left bottom front
         0.0f, 0.0f,  0.0f,  0.0f, 0.0f, 1.0f, 1.0f, // 6 right bottom back
         1.0f, 0.0f,  0.0f,  0.0f, 0.0f, 1.0f, 1.0f  // 7 left bottom back

    };

    // Index data to share position data
    GLushort indices[] = {
         2, 2, 6, 2, 4, 2, 0,
         3, 1, 6, 5, 4, 3, 0

    };



    const GLuint floatsPerVertex = 3;
    const GLuint floatsPerColor = 4;

    glGenVertexArrays(1, &mesh.vao+1); // we can also generate multiple VAOs or buffers at the same time
    glBindVertexArray(mesh.vao+1);

    // Create 2 buffers: first one for the vertex data; second one for the indices
    glGenBuffers(2, mesh.vbos);
    glBindBuffer(GL_ARRAY_BUFFER, mesh.vbos[0]); // Activates the buffer
    glBufferData(GL_ARRAY_BUFFER, sizeof(verts), verts, GL_STATIC_DRAW); // Sends vertex or coordinate data to the GPU

    mesh.nIndices = sizeof(indices) / sizeof(indices[0]);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh.vbos[1]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    // Strides between vertex coordinates is 6 (x, y, z, r, g, b, a). A tightly packed stride is 0.
    GLint stride = sizeof(float) * (floatsPerVertex + floatsPerColor);// The number of floats before each

    // Create Vertex Attribute Pointers
    glVertexAttribPointer(0, floatsPerVertex, GL_FLOAT, GL_FALSE, stride, 0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, floatsPerColor, GL_FLOAT, GL_FALSE, stride, (char*)(sizeof(float) * floatsPerVertex));
    glEnableVertexAttribArray(1);
}





// DONE-----------------------
// create shader program
bool createShaderProgram(const char* vtxShaderSource, const char* fragShaderSource, GLuint& programId)
{
    // Compilation and linkage error reporting
    int success = 0;
    char infoLog[512];

    // Create a Shader program object.
    programId = glCreateProgram();

    // Create the vertex and fragment shader objects
    GLuint vertexShaderId = glCreateShader(GL_VERTEX_SHADER);
    GLuint fragmentShaderId = glCreateShader(GL_FRAGMENT_SHADER);

    // Retrive the shader source
    glShaderSource(vertexShaderId, 1, &vtxShaderSource, NULL);
    glShaderSource(fragmentShaderId, 1, &fragShaderSource, NULL);

    // Compile the vertex shader, and print compilation errors (if any)
    glCompileShader(vertexShaderId); // compile the vertex shader
    // check for shader compile errors
    glGetShaderiv(vertexShaderId, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(vertexShaderId, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;

        return false;
    }

    glCompileShader(fragmentShaderId); // compile the fragment shader
    // check for shader compile errors
    glGetShaderiv(fragmentShaderId, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(fragmentShaderId, sizeof(infoLog), NULL, infoLog);
        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;

        return false;
    }

    // Attached compiled shaders to the shader program
    glAttachShader(programId, vertexShaderId);
    glAttachShader(programId, fragmentShaderId);

    glLinkProgram(programId);   // links the shader program
    // check for linking errors
    glGetProgramiv(programId, GL_LINK_STATUS, &success);
    if (!success)
    {
        glGetProgramInfoLog(programId, sizeof(infoLog), NULL, infoLog);
        std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;

        return false;
    }

    glUseProgram(programId);    // Uses the shader program

    return true;
}


// DONE-----------------------
// destroys shader program
void destroyShaderProgram(GLuint programId)
{
    glDeleteProgram(programId);
}