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
    xOut = x * cos(angle) - y * sin(angle);
    yOut = x * sin(angle) + y * cos(angle); 
}

Tiro* Robo::Atira() {
    /** graus p radianos */
    GLfloat conversao = M_PI / 180.0;
    GLfloat rad1 = gTheta1 * conversao;
    GLfloat rad2 = gTheta2 * conversao;
    GLfloat rad3 = gTheta3 * conversao;

    /**  Base da haste 3 */
    GLfloat x_base = 0.0;
    GLfloat y_base = 0.0;

    /**  Ponta da haste 3 */
    GLfloat x_tip = 0.0;
    GLfloat y_tip = paddleHeight; 

    /** refaz os ajustes  */
    RotatePoint(x_tip, y_tip, rad3, x_tip, y_tip);

    /** corrige alturas */
    y_base += paddleHeight; y_tip += paddleHeight;


    RotatePoint(x_base, y_base, rad2, x_base, y_base);
    RotatePoint(x_tip, y_tip, rad2, x_tip, y_tip);

    // Translação de paddleHeight em y (da base da haste 1 para a base da haste 2)
    y_base += paddleHeight;
    y_tip += paddleHeight;

    // Rotação de gTheta1
    RotatePoint(x_base, y_base, rad1, x_base, y_base);
    RotatePoint(x_tip, y_tip, rad1, x_tip, y_tip);

    // Translação de baseHeight em y (da base do robô para a base da haste 1)
    y_base += baseHeight;
    y_tip += baseHeight;

    // Translação para a posição no mundo gX e gY
    x_base += gX;
    y_base += gY;
    x_tip += gX;
    y_tip += gY;

    // 3. Calcula a direção (ângulo)
    // DICA 3: Usar atan2
    // O ângulo é o vetor da base da haste 3 até a ponta da haste 3
    GLfloat angle_rad = atan2(y_tip - y_base, x_tip - x_base);
    
    // Converte de radianos para graus
    GLfloat angle_deg = angle_rad * (180.0 / M_PI);

    // 4. Cria o tiro
    // A posição do tiro é a ponta da última haste
    return new Tiro(x_tip, y_tip, angle_deg);
}
