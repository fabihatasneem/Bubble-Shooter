# include "iGraphics.h"

int clr[8000][8000],exist[8000][8000]; //for existance of the center and color of the circle
int x_p=400,y_p=60;      //center of projection line
int x2_p=400,y2_p=200,x2_p_A=389, y2_p_A=189, x2_p_B=411, y2_p_B=211;   // initial end point of projection line
double angle_p=0, angle_A=-0.1, angle_B=0.1;        // initial projection angle
int x_shoot=400,y_shoot=60; //initial position of shooter
int shoot=0;        // flag to determine whether shoot or not
int shoot_color=0;  // color of shooter
int shoot_color_flag=0,shoot_angle_flag=0; // flag for shooter color change or shooter angle change
double shoot_angle=0;  //shooting angle
int r,g,b;  // RGB color values
double p=0,q=0;
int shoot_slow=10;
void color() //function to determine initial colors of bubbles
{
    for(int i=20; i<=780; i+=40)
    {
        for(int j=490; j<=730 ; j+=40)
        {
            int rnd=rand()%5;
            clr[i][j]=rnd;
            exist[i][j]=1;
        }
    }
}
void movement() // shooter movement by iSetTimer()
{
    if(shoot==1 && y_shoot<730 )
    {
        if(shoot_angle_flag==0)
        {
            //determine shoot angle

            shoot_angle_flag=1;
            shoot_angle=angle_p;
        }

        y_shoot+=10;
        x_shoot+=tan(shoot_angle)*10;

        if(x_shoot<30 || x_shoot>780)
        {
            //reflection

            shoot_angle=-shoot_angle;

        }

        for(int i=-20; i<=20; i++)
        {
            for(int j=0; j<=40; j++)
            {
                if(exist[x_shoot+i][y_shoot+j])
                {
                    if(exist[x_shoot+i][y_shoot+j-40] && shoot_angle>0)
                    {
                        x_shoot+=i-40;
                        y_shoot+=j;
                    }

                    else if(exist[x_shoot+i][y_shoot+j-40] && shoot_angle<0)
                    {
                        x_shoot+=i+40;
                        y_shoot+=j;
                    }

                    else
                    {
                        x_shoot=x_shoot+i;
                        y_shoot=y_shoot+j-40;
                    }

                    shoot=0;
                }
            }
        }

        shoot_color_flag=0; // without this shoot color changes until shoot=1
    }
    else
    {
        //old shooter gone
        shoot=0;
        shoot_angle_flag=0;

        // new bubble added
        exist[x_shoot][y_shoot]=1;
        clr[x_shoot][y_shoot]=shoot_color;

        //new shooter added
        if(shoot_color_flag==0)
        {
            shoot_color=rand()%4;
            shoot_color_flag=1;
        }
        x_shoot=400;
        y_shoot=60;
    }

}


void iDraw()
{

    iClear();
    iSetColor(176,224,255);             //draw background
    iFilledRectangle(0,0,800,750);
    int ara[3]= {255,0};
    for(int i=100; i<=300; i++)
    {
        for(int j=100; j<=300; j++)
        {
            iGetPixelColor(i,j,ara);
        }
    }


    iSetColor(240,240,240);
    for(int i=0; i<=800; i+=7)
    {
        iLine(i,100,i+3,100);           //draw base
    }


    for(int i=0; i<=800; i++)           // draw bubble
    {
        for(int j=0; j<=750; j++)
        {
            if(clr[i][j]==0)
            {
                r=255,g=q, b=q;
            }
            if(clr[i][j]==1)
            {
                r=q,g=155,b=q;
            }
            if(clr[i][j]==2)
            {
                r=q,g=q,b=255;
            }
            if(clr[i][j]==3)
            {
                r=255,g=255,b=q;
                q=0;
                p=0;
            }
            if(clr[i][j]==4)
            {
                r=50+q,g=50+q,b=50+q;
            }
            if(exist[i][j])
            {

                while(p<20)
                {
                    iSetColor(r,g,b);
                    iFilledCircle(i,j,20-p);
                    p+=3;
                    q+=30;
                }
            }
        }
    }


// color for shooter
    if(shoot_color==0)
    {
//        int ara[3]= {255,p,p};
//        p+=10;
//        iGetPixelColor(x_shoot, y_shoot, ara);
        r=255,g=0,b=0;
    }
    if(shoot_color==1)
    {
        r=0,g=155,b=0;
    }
    if(shoot_color==2)
    {
        r=0,g=0,b=255;
    }
    if(shoot_color==3)
    {
        r=255,g=255,b=0;
    }

    iSetColor(r,g,b);
    iFilledCircle(x_shoot,y_shoot,20); //draw shooter

    iSetColor(100,100,100);
    iLine(x_p,y_p,x2_p,y2_p);      //draw projection

    double x_arrow[]= {x2_p,x2_p_A,x2_p_B};     //draw arrow head;
    double y_arrow[]= {y2_p,y2_p_A,y2_p_B};
    iSetColor(128,0,128);
    iFilledPolygon(x_arrow,y_arrow, 3);


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
    if(key==GLUT_KEY_RIGHT)     //shooter/projection angle change
    {
        if(angle_p<=1)
        {

            angle_p+=0.1;
            angle_A=angle_p-0.1;
            angle_B=angle_p+0.1;

            x2_p=x_p+140*sin(angle_p);
            y2_p=y_p+140*cos(angle_p);

            x2_p_A=x_p+110*sin(angle_A);
            y2_p_A=y_p+110*cos(angle_A);

            x2_p_B=x_p+110*sin(angle_B);
            y2_p_B=y_p+110*cos(angle_B);
        }
    }

    if(key==GLUT_KEY_LEFT)      //shooter/projection angle change
    {
        if(angle_p>=(-1))
        {
            angle_p-=0.1;
            angle_A=angle_p-0.1;
            angle_B=angle_p+0.1;

            x2_p=x_p+140*sin(angle_p);
            y2_p=y_p+140*cos(angle_p);

            x2_p_A=x_p+110*sin(angle_A);
            y2_p_A=y_p+110*cos(angle_A);

            x2_p_B=x_p+110*sin(angle_B);
            y2_p_B=y_p+110*cos(angle_B);
        }
    }

    if(key==GLUT_KEY_UP)       //shoot!!!
    {
        // final_destination();
        shoot=1;
    }

}


int main()
{

    iSetTimer(1,movement);
    color();
    iInitialize(800,750, "Bubble Shooter");
    return 0;
}


