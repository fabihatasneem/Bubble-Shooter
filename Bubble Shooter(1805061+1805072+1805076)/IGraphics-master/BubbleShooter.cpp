# include "iGraphics.h"
# include "gl.h"

/*
	function iDraw() is called again and again by the system.
*/
double x_shoot = 400,y_shoot=60;
double m=0;
double clr[1000][1000],exist[1000][1000];

void color()
{
    for(int i=20; i<=780; i+=40)
    {
        for(int j=490; j<=690; j+=40)
        {
            int rnd=rand()%5;
            clr[i][j]=rnd;
        }
    }
}

void iDraw()
{

    iClear();


    iSetColor(104, 221, 247);
    iFilledRectangle(0,0,800,750);
    int r=0,g=0,b=0;
    for(int i=20; i<=780; i+=40)
    {
        for(int j=490; j<=690; j+=40)
        {
            if(clr[i][j]==0)
            {
                r=255,g=0,b=0;
            }
            if(clr[i][j]==1)
            {
                r=0,g=255,b=0;
            }
            if(clr[i][j]==2)
            {
                r=0,g=0,b=255;
            }
            if(clr[i][j]==3)
            {
                r=255,g=255,b=0;
            }
            if(clr[i][j]==4)
            {
                r=100,g=100,b=100;
            }
            iSetColor(r,g,b);
            if(exist[i][j]==0)
            {
                iFilledCircle(i,j,20,100);
            }
        }
    }
    iSetColor(255,0,0);
    iFilledCircle(400,60,20);

//Game Over Line

    for (int x_line = 0; x_line <= 800; x_line+= 10)
    {
        iSetColor(255, 255, 255);
        iLine(x_line, 100, x_line+3, 100);
    }

//Shooter's Path is a semicircle
//radius=90

    iSetColor(255,0,145);
    iLine(x_shoot, y_shoot, x_shoot+m, y_shoot+sqrt(8100-(m*m)));

//    for (int i = 80; i <= 470; i+= 15)
//    {
//        iSetColor(0, 0, 0);
//        iLine(x, i, x, i+7); // x = 400, y+dy = i
//    }
}

/*
	function iMouseMove() is called when the user presses and drags the mouse.
	(mx, my) is the position where the mouse pointer is.
*/
void iMouseMove(int mx, int my)
{
    //place your codes here
}

/*
	function iMouse() is called when the user presses/releases the mouse.
	(mx, my) is the position where the mouse pointer is.
*/
void iMouse(int button, int state, int mx, int my)
{
    if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
    {

    }
    if(button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
    {

    }
}

/*
	function iKeyboard() is called whenever the user hits a key in keyboard.
	key- holds the ASCII value of the key pressed.
*/
void iKeyboard(unsigned char key)
{

    //place your codes for other keys here
}

/*
	function iSpecialKeyboard() is called whenver user hits special keys like-
	function keys, home, end, pg up, pg down, arraows etc. you have to use
	appropriate constants to detect them. A list is:
	GLUT_KEY_F1, GLUT_KEY_F2, GLUT_KEY_F3, GLUT_KEY_F4, GLUT_KEY_F5, GLUT_KEY_F6,
	GLUT_KEY_F7, GLUT_KEY_F8, GLUT_KEY_F9, GLUT_KEY_F10, GLUT_KEY_F11, GLUT_KEY_F12,
	GLUT_KEY_LEFT, GLUT_KEY_UP, GLUT_KEY_RIGHT, GLUT_KEY_DOWN, GLUT_KEY_PAGE UP,
	GLUT_KEY_PAGE DOWN, GLUT_KEY_HOME, GLUT_KEY_END, GLUT_KEY_INSERT
*/
void iSpecialKeyboard(unsigned char key)
{

    if (key == GLUT_KEY_RIGHT)
    {
        if(m<90)
            m++;
    }
    if (key == GLUT_KEY_LEFT)
    {
        if(m>(-90))
            m--;
    }
    //place your codes for other keys here
}


int main()
{
    //const int CX_MAX = 1366;
    //const int CY_MAX = 768;

    // Initialize Sun's position and size.
    color();
    iInitialize(800, 750, "Bubbles!");


    return 0;
}
