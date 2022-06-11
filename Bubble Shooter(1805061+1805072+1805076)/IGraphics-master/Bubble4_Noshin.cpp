# include "iGraphics.h"
#include "Windows.h"

int clr[8000][8000],exist[8000][8000]; //for existance of the center and color of the circle
int x_p=400,y_p=60;      //center of projection line
int x2_p=400,y2_p=200,x2_p_A=389, y2_p_A=170, x2_p_B=411, y2_p_B=170;   // initial end point of projection line and arrow
double angle_p=0, angle_A=-0.1, angle_B=0.1;        // initial projection angle
int x_shoot=400,y_shoot=60; //initial position of shooter
int shoot=0;        // flag to determine whether shoot or not
int shoot_color=0;  // color of shooter
int shoot_color_flag=0,shoot_angle_flag=0; // flag for shooter color change or shooter angle change
double shoot_angle=0;  //shooting angle
int r,g,b;  // RGB color values
int shooter_gone=0; //flag if shooter should go or stay after dfs

//necessary var for dfs
int cnt=0;
int dx[]= {-40,40,0,0};
int dy[]= {0,0,40,-40};
int vis[8000][8000];

void dfs(int x,int y)
{
    cnt++;
    vis[x][y]=1;
    for(int i=0; i<4; i++)
    {
        int u=x+dx[i],v=y+dy[i];
        if(vis[u][v]==0 && clr[u][v]==clr[x][y] && exist[u][v]==1 && u>0 && u<800 && v>0 && v<750)
        {
            dfs(u,v);
            if(cnt>=3)
            {
                shooter_gone=1;
                //PlaySound((LPCSTR) "C:\\Users\\Public\\Music\\Sample Music\\Sleep Away.mp3", NULL, SND_FILENAME | SND_ASYNC);
                exist[u][v]=0;
            }
        }
    }
}

void island()     //eliminate bubble if it's not attached to any ceiling anymore
{
    for(int i=20; i<=780; i+=40)
    {
        for(int j=90; j<730; j+=4)
        {
            if(exist[i][j]==1 && exist[i][j+40]==0)
            {
                exist[i][j]=0;
            }
        }
    }
}


void color() //function to determine initial colors of bubbles
{
    for(int i=20; i<=780; i+=40)
    {
        for(int j=490; j<=4730 ; j+=40)
        {
            int rnd=rand()%5;
            clr[i][j]=rnd;
            exist[i][j]=1;
        }
    }

}

void newline()
{
    for(int i=20; i<=780; i+=40)
    {
        for(int j=90; j<4330; j+=40)
        {
            clr[i][j-40]=clr[i][j];
            exist[i][j-40]=exist[i][j];
            if(j<=90 && exist[i][j]==1)
            {
                exit(0);
            }
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

        y_shoot+=20;
        x_shoot+=tan(shoot_angle)*20;

        if(x_shoot<25 || x_shoot>780)
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
                    //new position

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
                        x_shoot+=i;
                        y_shoot+=j-40;
                    }

                    //making default for dfs

                    for(int i=0; i<800; i++)
                    {
                        for(int j=0; j<750; j++)
                        {
                            vis[i][j]=0;
                        }
                    }
                    cnt=0;
                    shooter_gone=0;
                    clr[x_shoot][y_shoot]=shoot_color;

                    dfs(x_shoot,y_shoot);
                    island();
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
        if(shooter_gone==0)
        {
            exist[x_shoot][y_shoot]=1;
            clr[x_shoot][y_shoot]=shoot_color;

        }


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
    iSetColor(240,240,240);
    for(int i=0; i<=800; i+=7)
    {
        iLine(i,100,i+3,100);           //draw base
    }
    for(int i=0; i<=800; i++) // draw bubble
    {
        for(int j=0; j<=750; j++)
        {
            if(clr[i][j]==0)
            {
                r=243,g=36,b=22;
            }
            if(clr[i][j]==1)
            {
                r=61,g=83,b=173;
            }
            if(clr[i][j]==2)
            {
                r=39,g=210,b=58;
            }
            if(clr[i][j]==3)
            {
                r=241,g=231,b=28;
            }
            if(clr[i][j]==4)
            {
                r=132,g=144,b=132;
            }
            if(exist[i][j])
            {
                iSetColor(r,g,b);
                iFilledCircle(i,j,20);

                iSetColor(r+10,g+10,b+10);
                iFilledCircle(i-2,j+2,16);

                iSetColor(r+30,g+30,b+30);
                iFilledCircle(i-4,j+4,13);

                iSetColor(r+50,g+50,b+50);
                iFilledCircle(i-6,j+6,10);

                iSetColor(r+70,g+70,b+70);
                iFilledCircle(i-8,j+8,6);

                iSetColor(245,245,245);
                iFilledCircle(i-10,j+10,3);
            }
        }
    }

    // color for shooter
    if(shoot_color==0)
    {
        r=243,g=36,b=22;
    }
    if(shoot_color==1)
    {
        r=61,g=83,b=173;
    }
    if(shoot_color==2)
    {
        r=39,g=210,b=58;
    }
    if(shoot_color==3)
    {
        r=241,g=231,b=28;
    }

    iSetColor(r,g,b);
    iFilledCircle(x_shoot,y_shoot,20);

    iSetColor(r+10,g+10,b+10);
    iFilledCircle(x_shoot-2,y_shoot+2,16);

    iSetColor(r+30,g+30,b+30);
    iFilledCircle(x_shoot-4,y_shoot+4,13);

    iSetColor(r+50,g+50,b+50);
    iFilledCircle(x_shoot-6,y_shoot+6,10);

    iSetColor(r+70,g+70,b+70);
    iFilledCircle(x_shoot-8,y_shoot+8,6);

    iSetColor(245,245,245);
    iFilledCircle(x_shoot-10,y_shoot+10,3);

    //draw shooter
    iSetColor(100,100,100);
    iLine(x_p,y_p,x2_p,y2_p);      //draw projection

    double x_arrow[]= {x2_p,x2_p_A,x2_p_B},y_arrow[]= {y2_p,y2_p_A,y2_p_B}; //draw arrow
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
        if(angle_p<1)
        {

            angle_p+=0.1;
            angle_A=angle_p-0.1;
            angle_B=angle_p+0.1;

            x2_p=x_p+140*sin(angle_p);
            y2_p=y_p+140*cos(angle_p);

            //for arrow
            x2_p_A=x_p+110*sin(angle_A);
            y2_p_A=y_p+110*cos(angle_A);

            x2_p_B=x_p+110*sin(angle_B);
            y2_p_B=y_p+110*cos(angle_B);
        }
    }

    if(key==GLUT_KEY_LEFT)      //shooter/projection angle change
    {
        if(angle_p>-1)
        {
            angle_p-=0.1;
            angle_A=angle_p-0.1;
            angle_B=angle_p+0.1;

            x2_p=x_p+140*sin(angle_p);
            y2_p=y_p+140*cos(angle_p);

            //for arrow
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

    iSetTimer(0.5,movement);
    iSetTimer(8000,newline);
    color();
    iInitialize(800,750, "Bubble Shooter");
    return 0;
}




