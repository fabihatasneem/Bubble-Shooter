# include "iGraphics.h"
int clr[8000][8000],exist[8000][8000];
double x_shoot=400,y_shoot=60;
double x_p=x_shoot,y_p=y_shoot;
double x2_p=400, y2_p=200, x2_p_A=389, y2_p_A=189, x2_p_B=411, y2_p_B=211;
double angle=0, angle_A=-0.1, angle_B=0.1;
int shoot=0;


void movement()
{
    if(shoot==1 && y_shoot<730 )
    {
        y_shoot+=10;                               //Reflection in side walls
        x_shoot+=tan(angle)*10;
        if(x_shoot<20 || x_shoot>780)
        {
           angle=-angle;
        }
    }
}

void iDraw()
{
    iClear();
    iSetColor(176,224,255);             //draw background
    iFilledRectangle(0,0,800,750);


    iSetColor(255,0,0);
    iFilledCircle(400,60,20);


    iSetColor(255,255,255);
    for(int i=0;i<=800;i+=7)
    {
        iLine(i,100,i+5,100);           //draw game over line
    }


    iSetColor(255,0,0);
    iFilledCircle(x_shoot,y_shoot,20);
    iSetColor(100,100,100);
    iLine(x_p,y_p,x2_p,y2_p);      //draw projection


    double x_arrow[]={x2_p,x2_p_A,x2_p_B};      //draw arrow head
    double y_arrow[]={y2_p,y2_p_A,y2_p_B};
    iSetColor(128,0,128);
    iFilledPolygon(x_arrow, y_arrow, 3);

}


void iMouseMove(int mx, int my)
{

}

void iMouse(int button, int state, int mx, int my)
{


}


void iKeyboard(unsigned char key)
{

}
/*
	function iSpecialKeyboard() is called whenever user hits special keys like-
	function keys, home, end, pg up, pg down, arrows etc. you have to use
	appropriate constants to detect them. A list is:
	GLUT_KEY_F1, GLUT_KEY_F2, GLUT_KEY_F3, GLUT_KEY_F4, GLUT_KEY_F5, GLUT_KEY_F6,
	GLUT_KEY_F7, GLUT_KEY_F8, GLUT_KEY_F9, GLUT_KEY_F10, GLUT_KEY_F11, GLUT_KEY_F12,
	GLUT_KEY_LEFT, GLUT_KEY_UP, GLUT_KEY_RIGHT, GLUT_KEY_DOWN, GLUT_KEY_PAGE UP,
	GLUT_KEY_PAGE DOWN, GLUT_KEY_HOME, GLUT_KEY_END, GLUT_KEY_INSERT
*/
void iSpecialKeyboard(unsigned char key)
{
    if(key==GLUT_KEY_RIGHT)
    {
        if(angle<1.1)
        {
            angle+=0.1;
            angle_A=angle-0.1;
            angle_B=angle+0.1;

            x2_p=x_p+140*sin(angle);
            y2_p=y_p+140*cos(angle);

            x2_p_A=x_p+110*sin(angle_A);
            y2_p_A=y_p+110*cos(angle_A);

            x2_p_B=x_p+110*sin(angle_B);
            y2_p_B=y_p+110*cos(angle_B);
        }
    }

    if(key==GLUT_KEY_LEFT)
    {
        if(angle>-1.1)
        {
            angle-=0.1;
            angle_A=angle-0.1;
            angle_B=angle+0.1;

            x2_p=x_p+140*sin(angle);
            y2_p=y_p+140*cos(angle);

            x2_p_A=x_p+110*sin(angle_A);
            y2_p_A=y_p+110*cos(angle_A);

            x2_p_B=x_p+110*sin(angle_B);
            y2_p_B=y_p+110*cos(angle_B);
        }
    }

    if(key==GLUT_KEY_UP)
    {
        shoot=1;
    }

}



int main()
{

    iSetTimer(10,movement);
    iInitialize(800,750 , "Bubbles!");
    return 0;
}
