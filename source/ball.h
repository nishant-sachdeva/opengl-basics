#include "main.h"

#ifndef BALL_H
#define BALL_H


class Ball {
public:
    Ball() {}
    Ball(float x, float y, float z, color_t color);
    glm::vec3 position;
    float rotation;
    void draw(glm::mat4 VP);
    void set_position(float x, float y, float z);
    void set_speed(double new_speed);
    float * get_position();
    void tick();
    double speed;
    int number_of_vertices;
    float position_arr[3]; 
private:
    VAO *object;
};

#endif // BALL_H
