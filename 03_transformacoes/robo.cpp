#include "includes/robo.h"
#include <math.h>

void Robo::DesenhaRect(GLint height, GLint width, GLfloat R, GLfloat G, GLfloat B) {
    glBegin(GL_POLYGON);
        glColor3f(R, G, B);
        glVertex3f(-width/2, height, 0); // D
        glVertex3f(-width/2, 0, 0); // A
        glVertex3f(width/2, 0, 0); // B
        glVertex3f(width/2, height, 0); // C
    glEnd();
}

void Robo::DesenhaCirc(GLint radius, GLfloat R, GLfloat G, GLfloat B) {
    glPointSize(1.0);
    glColor3f(R, G, B);
    
    glBegin(GL_POINTS);
        for(double i = 0; i < 2*M_PI; i+= M_PI/24) {
            float x = radius * cos(i);
            float y = radius * sin(i);
                glVertex3f(x, y, 0);
            }
    glEnd();
}

void Robo::DesenhaRoda(GLfloat x, GLfloat y, GLfloat thetaWheel, GLfloat R, GLfloat G, GLfloat B) {
    glPushMatrix();

    glTranslatef(x, y, 0);
    glRotatef(thetaWheel, 0, 0, 1);
    DesenhaCirc(radiusWheel, R, G, B);

    glPopMatrix();
}

void Robo::DesenhaBraco(GLfloat x, GLfloat y, GLfloat theta1, GLfloat theta2, GLfloat theta3) {
    glPushMatrix();

    glTranslatef(x, y, 0);
    glRotatef(theta1, 0, 0, 1);
    DesenhaRect(paddleHeight, paddleWidth, 0, 0, 1);
    
    glTranslatef(0, paddleHeight, 0);
    glRotatef(theta2, 0, 0, 1);
    DesenhaRect(paddleHeight, paddleWidth, 1, 1, 0);

    glTranslatef(0, paddleHeight, 0);
    glRotatef(theta3, 0, 0, 1);
    DesenhaRect(paddleHeight, paddleWidth, 0, 1, 0);

    glPopMatrix();
}

void Robo::DesenhaRobo(GLfloat x, GLfloat y, GLfloat thetaWheel, GLfloat theta1, GLfloat theta2, GLfloat theta3) {
    glPushMatrix();

    glTranslatef(x, y, 0);
    DesenhaRect(baseHeight, baseWidth, 1, 0, 0);
    DesenhaBraco(0, baseHeight, theta1, theta2, theta3);
    DesenhaRoda(-baseWidth/2, 0, thetaWheel, 1, 1, 1);
    DesenhaRoda(baseWidth/2, 0, thetaWheel, 1, 1, 1);

    glPopMatrix();
}

void Robo::RodaBraco1(GLfloat inc) {
    this->gTheta1 += inc;
}

void Robo::RodaBraco2(GLfloat inc) {
    this->gTheta2 += inc;
}

void Robo::RodaBraco3(GLfloat inc) {
    this->gTheta3 += inc;
}

void Robo::MoveEmX(GLfloat dx) {
    this->gX = this->ObtemX() + dx*200;
    this->gThetaWheel = this->gThetaWheel + dx*200;
}

//Funcao auxiliar de rotacao
void RotatePoint(GLfloat x, GLfloat y, GLfloat angle, GLfloat &xOut, GLfloat &yOut) {

}

Tiro* Robo::Atira() {

    GLfloat x = 0, y = 0;

    // rotate t3
    glTranslatef(0, paddleHeight, 0);

    // rotate t2
    glTranslatef(0, paddleHeight, 0);

    // rotate t1
    glTranslatef(0, baseHeight, 0);



    Tiro *tiro = new Tiro(x, y, 0);
    return tiro;
}
