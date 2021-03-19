#include "main.h"
#include "timer.h"
#include "ball.h"

using namespace std;

GLMatrices Matrices;
GLuint     programID;
GLFWwindow *window;

/**************************
* Customizable functions *
**************************/

Ball ball1;

float screen_zoom = 1, screen_center_x = 0, screen_center_y = 0;
float camera_rotation_angle = 0; // starter value to give effect of the 3d cube, since I don't know how to color vertices differently

bool rotate_camera = false;


glm::vec3 cameraPos   = glm::vec3(0.0f, 0.0f,  3.0f);
glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);   
glm::vec3 cameraUp    = glm::vec3(0.0f, 1.0f,  0.0f);

float cameraSpeed = 0.01f;

float theta = camera_rotation_angle*M_PI/180.0f;
float scale_value = 32.0f;

bool front_view = false;
bool side_view = false;
bool top_view = false;
bool normal_view = true;

Timer t60(1.0 / 60);



/* Render the scene with openGL */
/* Edit this function according to your assignment */
void draw() {
    // clear the color and depth in the frame buffer
    glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // use the loaded shader program
    // Don't change unless you know what you are doing
    glUseProgram (programID);


    // Eye - Location of camera. Don't change unless you are sure!!

    // Target - Where is the camera looking at.  Don't change unless you are sure!!
    glm::vec3 target (0, 0, 0);
    
    // Up - Up vector defines tilt of camera.  Don't change unless you are sure!!
    glm::vec3 up (0,1,0);

    glm::vec3 eye ( scale_value*cos(camera_rotation_angle*M_PI/180.0f), 0, scale_value*sin(camera_rotation_angle*M_PI/180.0f) );

    Matrices.view = glm::lookAt( eye, target, up ); // Rotating Camera for 3D

    if(front_view)
    {
        glm::vec3 eye1 ( scale_value, 0, 0 );
        Matrices.view = glm::lookAt( eye1, target, up ); // Rotating Camera for 3D
    }

    else if(side_view){
        glm::vec3 eye1 ( scale_value*cos(60*M_PI/180.0f), 0, scale_value*sin(60*M_PI/180.0f) );
        Matrices.view = glm::lookAt( eye1, target, up ); // Rotating Camera for 3D

    }
    else if(top_view){
        glm::vec3 eye1 ( scale_value*cos(60*M_PI/180.0f), scale_value*sin(60*M_PI/180.0f) , 0);
        Matrices.view = glm::lookAt( eye1, target, up ); // Rotating Camera for 3D

    }
    else{
        glm::vec3 eye1 ( scale_value*cos(camera_rotation_angle*M_PI/180.0f), 0, scale_value*sin(camera_rotation_angle*M_PI/180.0f) );
        Matrices.view = glm::lookAt( eye1, target, up ); // Rotating Camera for 3D
    }


    // Compute Camera matrix (view)

    // Matrices.view = glm::lookAt( eye, target, up ); // Rotating Camera for 3D
    // Matrices.view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);

    // Don't change unless you are sure!!
    // Matrices.view = glm::lookAt(glm::vec3(0, 0, 3), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0)); // Fixed camera for 2D (ortho) in XY plane

    // Compute ViewProject matrix as view/camera might not be changed for this frame (basic scenario)
    // Don't change unless you are sure!!
    glm::mat4 VP = Matrices.projection * Matrices.view;

    // Send our transformation to the currently bound shader, in the "MVP" uniform
    // For each model you render, since the MVP will be different (at least the M part)
    // Don't change unless you are sure!!
    glm::mat4 MVP;  // MVP = Projection * View * Model

    // Scene render
    ball1.draw(VP);
}

void tick_input(GLFWwindow *window) {
    if ( glfwGetKey(window, GLFW_KEY_K) )
        ball1.set_speed(1);
    // simple rotation around one axis

    else if (glfwGetKey(window, GLFW_KEY_L))
        ball1.set_speed(0);
    // simple rotation stops
    
    
    else if (glfwGetKey(window, GLFW_KEY_A))
    {
        // code to move front
        // float *arr = ball1.get_position();
        
        // ball1.set_position(arr[0] + 0.01, arr[1] , arr[2]);
        scale_value /= 1.2;
        
    }
    
    else if (glfwGetKey(window, GLFW_KEY_S))
    {
        // code to move behind
        // float *arr = ball1.get_position();
        // ball1.set_position(arr[0] - 0.01, arr[1] , arr[2]);
        scale_value *= 1.2 ;        
        
    } 
    
    else if (glfwGetKey(window, GLFW_KEY_D)){
        float *arr = ball1.get_position();
        
        ball1.set_position(arr[0] , arr[1] + 0.01 , arr[2]);
        
        // code to move up
    }
    
    else if (glfwGetKey(window, GLFW_KEY_F)){
        // code to move down
        float *arr = ball1.get_position();
        
        ball1.set_position(arr[0], arr[1] -0.01 , arr[2]);
       
    }
    
    else if (glfwGetKey(window, GLFW_KEY_G)){
        float *arr = ball1.get_position();
        ball1.set_position(arr[0] , arr[1] , arr[2] +0.01);
       
        // code to move left
    }
    
    else if (glfwGetKey(window, GLFW_KEY_H)){
        float *arr = ball1.get_position();
        
        ball1.set_position(arr[0], arr[1] , arr[2]-0.01);
       
        // code to move right
    }
    
    else if (glfwGetKey(window, GLFW_KEY_C)){
        
        ball1.set_position(0,0,0);
        camera_rotation_angle = 0;
        // code to recenter/reset  everything. Coming soon
    }

    else if (glfwGetKey(window, GLFW_KEY_U))
    {
        // code to take camera left 
        // code to take ball ( right ) 
        // cameraPos += cameraSpeed * cameraFront;
        float *arr = ball1.get_position();
        ball1.set_position(arr[0], arr[1] , arr[2] + 0.01);
       
    }

    else if (glfwGetKey(window, GLFW_KEY_I))
    {
        // cameraPos -= cameraSpeed * cameraFront;
        float *arr = ball1.get_position();
        ball1.set_position(arr[0], arr[1] , arr[2] - 0.01);
       
    }

    else if (glfwGetKey(window, GLFW_KEY_E))
    {
        // cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
        float *arr = ball1.get_position();
        ball1.set_position(arr[0], arr[1] + 0.01 , arr[2]);
    }

    else if (glfwGetKey(window, GLFW_KEY_R))
    {
        // cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
        float *arr = ball1.get_position();
        ball1.set_position(arr[0], arr[1] - 0.01 , arr[2]);
    }

    else if (glfwGetKey(window, GLFW_KEY_T))
    {
        // float *arr = ball1.get_position();
        // ball1.set_position(arr[0] + 0.01, arr[1] , arr[2]);

        scale_value /= 1.2;

    }

    else if (glfwGetKey(window, GLFW_KEY_Y))
    {
        scale_value *= 1.2;

        // float *arr = ball1.get_position();
        // ball1.set_position(arr[0] - 0.01, arr[1] , arr[2]);
    }
    
    else if (glfwGetKey(window, GLFW_KEY_O))
    {
        // code for camera rotation. Coming soon
        // ball1.set_speed (1);
        rotate_camera = true;
    }
    
    else if (glfwGetKey(window, GLFW_KEY_P))
    {        
        // Code to stop camera rotation. Coming soon
        // ball1.set_speed (0);
        rotate_camera = false;
    }

    else if (glfwGetKey(window, GLFW_KEY_V))
    {
        // front_view
        front_view = true;
        side_view = false;
        top_view = false;
        normal_view = false;
    }
    else if (glfwGetKey(window, GLFW_KEY_B))
    {        
        // side view
        front_view = false;
        side_view = true;
        top_view = false;
        normal_view = false;

    }
    else if (glfwGetKey(window, GLFW_KEY_N))
    {        
        // top view
        front_view = false;
        side_view = false;
        top_view = true;
        normal_view = false;

    }
    else if (glfwGetKey(window, GLFW_KEY_M))
    {
        front_view = false;
        side_view = false;
        top_view = false;
        normal_view = true;
    }
    return ;
}

void tick_elements() {
    ball1.tick();
    // camera_rotation_angle += 1;
    if ( rotate_camera == true ){
        camera_rotation_angle += 1;
        if (camera_rotation_angle == 360)
        {
            camera_rotation_angle = 0;
        }
    }
}

/* Initialize the OpenGL rendering properties */
/* Add all the models to be created here */
void initGL(GLFWwindow *window, int width, int height) {
    /* Objects should be created before any other gl function and shaders */
    // Create the models

    ball1       = Ball(0, 0, 0, COLOR_RED);

    // Create and compile our GLSL program from the shaders
    programID = LoadShaders("../source/shaders/shader.vert", "../source/shaders/shader.frag");
    // Get a handle for our "MVP" uniform
    Matrices.MatrixID = glGetUniformLocation(programID, "MVP");


    reshapeWindow (window, width, height);

    // Background color of the scene
    glClearColor (COLOR_BACKGROUND.r / 256.0, COLOR_BACKGROUND.g / 256.0, COLOR_BACKGROUND.b / 256.0, 0.0f); // R, G, B, A
    glClearDepth (2.0f);

    glEnable (GL_DEPTH_TEST);
    glDepthFunc (GL_LEQUAL);

    cout << "VENDOR: " << glGetString(GL_VENDOR) << endl;
    cout << "RENDERER: " << glGetString(GL_RENDERER) << endl;
    cout << "VERSION: " << glGetString(GL_VERSION) << endl;
    cout << "GLSL: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << endl;
}


int main(int argc, char **argv) {
    srand(time(0));
    int width  = 900;
    int height = 900;

    window = initGLFW(width, height);

    initGL (window, width, height);

    /* Draw in loop */
    // This is the main loop. All the drawing etc will happen here
    std::cout << "When the code starts, Z axis is the horizontal, Y axis is the vertical and X axis is perpendicular to the plane" << std::endl;
    while (!glfwWindowShouldClose(window)) {
        // Process timers

        if (t60.processTick()) {
            // 60 fps
            // OpenGL Draw commands
            draw();
            // Swap Frame Buffer in double buffering
            glfwSwapBuffers(window);

            tick_elements();
            tick_input(window);
        }

        // Poll for Keyboard and mouse events
        glfwPollEvents();
    }

    quit(window);
}

bool detect_collision(bounding_box_t a, bounding_box_t b) {
    return (abs(a.x - b.x) * 2 < (a.width + b.width)) &&
           (abs(a.y - b.y) * 2 < (a.height + b.height));
}

void reset_screen() {
    float top    = screen_center_y + 4 / screen_zoom;
    float bottom = screen_center_y - 4 / screen_zoom;
    float left   = screen_center_x - 4 / screen_zoom;
    float right  = screen_center_x + 4 / screen_zoom;
    Matrices.projection = glm::ortho(left, right, bottom, top, 0.1f, 500.0f);
}
