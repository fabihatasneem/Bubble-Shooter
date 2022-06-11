# include "iGraphics.h"

int clr[8000][8000],exist[8000][8000]; //for existance of the center and color of the circle
int x_p=400,y_p=60;      //center of projection line
int x2_p=400,y2_p=200,x2_p_A=389, y2_p_A=170, x2_p_B=411, y2_p_B=170;   // initial end point of projection line and arrow
double angle_p=0, angle_A=-0.1, angle_B=0.1;        // initial projection angle
int x_shoot=400,y_shoot=60; //initial position of shooter
int shoot=0;        // flag to determine whether shoot or not
int shoot_color=0;  // color of shooter
int rep_shoot_color=0,rep_shoot_color_flag=0;
int shoot_color_flag=0,shoot_angle_flag=0; // flag for shooter color change or shooter angle change
double shoot_angle=0;  //shooting angle
int r,g,b;  // RGB color values
int shooter_gone=0; //flag if shooter should go or stay after dfs
int n = 0, p = 1; // cover to game page linkup


//necessary var for dfs
int cnt=0;
int dx[]={-40,40,0,0};
int dy[]={0,0,40,-40};
int vis[8000][8000];


void dfs(int x,int y)
{
    cnt++;
    vis[x][y]=1;
    for(int i=0;i<4;i++)
    {
        int u=x+dx[i],v=y+dy[i];
        if(u>0 && u<800 && v>0 && v<690)
        {
            if(vis[u][v]==0 && clr[u][v]==clr[x][y] && exist[u][v]==1)
            {
                dfs(u,v);
                if(cnt>=3)
                {
                    shooter_gone=1;
                    exist[u][v]=0;
                }

            }

        }

    }

}

void island()     //eliminate ceilles bubble
{
    for(int i=20;i<=780;i+=40)
    {
        for(int j=690;j>=90;j-=40)
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
    for(int i=20;i<=780;i+=40)
    {
        for(int j=90;j<4330;j+=40)
        {
            clr[i][j-40]=clr[i][j];
            exist[i][j-40]=exist[i][j];
            if(j<=130 && exist[i][j]==1)
            {
                exit(0);
            }
        }
    }
}

void movement() // shooter movement by iSetTimer()
{
    if(shoot==1 && y_shoot<=690 )
    {
        if(shoot_angle_flag==0)
        {
            //determine shoot angle

            shoot_angle_flag=1;
            shoot_angle=angle_p;
        }
        if(abs(shoot_angle)<=0.5)
        {
            y_shoot+=20;
            x_shoot+=tan(shoot_angle)*20;
        }
        else{
            y_shoot+=10;
            x_shoot+=tan(shoot_angle)*10;
        }
        if(x_shoot<30 || x_shoot>780)
        {
           //reflection

           shoot_angle=-shoot_angle;

        }

        for(int i=-20;i<=20;i++)
        {
            for(int j=0;j<=40;j++)
            {
                if(exist[x_shoot+i][y_shoot+j]==1)
                {
                    //new position
                    if(abs(j)>abs(i))
                    {
                        if(exist[x_shoot+i][y_shoot+j-40]==1 && shoot_angle>0)
                        {
                            x_shoot+=i-40;
                            y_shoot=y_shoot+j;
                        }

                        else if(exist[x_shoot+i][y_shoot+j-40]==1 && shoot_angle<0)
                        {
                            x_shoot+=i+40;
                            y_shoot=y_shoot+j;
                        }

                        else{
                            x_shoot=x_shoot+i;
                            y_shoot=y_shoot+j-40;

                        }

                    }
                    else {
                        if(shoot_angle>0)
                        {
                            if(exist[x_shoot+i-40][y_shoot+j]==0)
                            {
                                x_shoot+=i-40;
                                y_shoot=y_shoot+j;
                            }
                            else{
                                x_shoot=x_shoot+i;
                                y_shoot=y_shoot+j-40;

                            }
                        }
                        else if(shoot_angle<0)
                        {
                            if(exist[x_shoot+i+40][y_shoot+j]==0)
                            {
                                x_shoot+=i+40;
                                y_shoot=y_shoot+j;
                            }
                            else{
                                x_shoot=x_shoot+i;
                                y_shoot=y_shoot+j-40;

                            }
                        }

                    }

                    //making default for dfs

                    for(int i=0;i<800;i++)
                    {
                        for(int j=0;j<750;j++)
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

                    //Fabiha needs to vanish all the balls in a certain range using Special ball-1

                    if(shoot_color==4)
                    {
                        for(int i=-120; i<=120; i+=40)
                        {
                            for(int j=0; j<=120; j+=40)
                            {
                                exist[x_shoot+i][y_shoot+j]=0;
                            }
                        }
                        shooter_gone=1;
                    }

                    //Fabiha needs to vanish all the balls of same color using Special ball-2

                    if(shoot_color==5)
                    {
                        for(int i=20; i<=780; i+=40)
                        {
                            for(int j=130; j<=730; j+=40)
                            {
                                if(clr[i][j]==clr[x_shoot][y_shoot+40])
                                {
                                    exist[i][j]=0;
                                }
                            }
                        }
                        shooter_gone=1;
                    }
                }
            }
        }

        shoot_color_flag=0; // without this shoot color changes until shoot=1
        rep_shoot_color_flag=0;
    }
    else{
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
            int temp=rep_shoot_color;
            rep_shoot_color=shoot_color;
            shoot_color=temp;
            shoot_color_flag=1;
        }
        x_shoot=400;
        y_shoot=60;

        // replace shooter added
        if(rep_shoot_color_flag==0)
        {
            rep_shoot_color=rand()%6;
            rep_shoot_color_flag=1;
        }
    }

}


void iDraw()
{

    iClear();
    if (!n)
    {
        iShowBMP(0, 0, "wheel.bmp"); // cover image
        //iSetColor(255, 255, 255);
        //iText(250, 450, "Hello");
    }
    else
    {
        iSetColor(176,224,255);             //draw background
        iFilledRectangle(0,0,800,750);
        iSetColor(240,240,240);
        for(int i=0;i<=800;i+=7)
        {
            iLine(i,110,i+3,110);           //draw base
        }

        for(int i=0;i<=800;i+=7)
        {
            iLine(i,710,i+3,710);           //draw ceil
        }

        //let's draw grass

        iSetColor(81,190,49);
        for(int i=0; i<=800; i+=20)
        {
            double x_grass_a[3]={i,i+5,i+10};
            double y_grass_a[3]={0,40,0};
            iFilledPolygon(x_grass_a,y_grass_a,3);
            double x_grass_b[3]={i+10,i+15,i+20};
            double y_grass_b[3]={0,30,0};
            iFilledPolygon(x_grass_b,y_grass_b,3);
        }

        //let's draw some flowers

        for(int i=40; i<800; i+=80)
        {
            if(i<330 || i>440)
            {
                iSetColor(81,210,49);
                iLine(i,0,i,70);

                iSetColor(242,35,83);
                iFilledEllipse(i+10,70,8,7);
                iFilledEllipse(i-10,70,8,7);
                iFilledEllipse(i,80,7,8);
                iFilledEllipse(i,60,7,8);

                iSetColor(255,247,0);
                iFilledCircle(i,70,7);
            }
        }

        for(int i=0;i<=800;i++) // draw bubble
        {
            for(int j=0;j<=710;j++)
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
        iFilledCircle(x_shoot,y_shoot,20);      //draw shooter

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

        if(shoot_color==4)              //Special Ball 1 - vanish all bubbles in a certain range Boom!
        {
            iSetColor(210,0,0);
            iFilledCircle(x_shoot, y_shoot, 20);

            iSetColor(255,255,0);
            iFilledEllipse(x_shoot, y_shoot,10,20);

            iSetColor(255,102,0);
            iFilledEllipse(x_shoot, y_shoot,5,20);

            iSetColor(255,255,0);
            iFilledEllipse(x_shoot, y_shoot,20,10);

            iSetColor(255,102,0);
            iFilledEllipse(x_shoot, y_shoot,20,5);

            iSetColor(255,30,0);
            iFilledCircle(x_shoot, y_shoot, 10);
        }

        if(shoot_color==5)              //Special Ball 2 - vanish all bubbles of same color!
        {
            iSetColor(0,0,255);
            iFilledCircle(x_shoot, y_shoot, 20);

            iSetColor(255,255,0);
            iFilledCircle(x_shoot, y_shoot,15);

            iSetColor(255,0,85);
            iFilledCircle(x_shoot, y_shoot, 10);

            iSetColor(0,255,0);
            iFilledCircle(x_shoot, y_shoot,5);
        }

                                                        // draw replacing shooter

        if(rep_shoot_color==0)
        {
            r=243,g=36,b=22;
        }
        if(rep_shoot_color==1)
        {
            r=61,g=83,b=173;
        }
        if(rep_shoot_color==2)
        {
            r=39,g=210,b=58;
        }
        if(rep_shoot_color==3)
        {
            r=241,g=231,b=28;
        }

        iSetColor(r,g,b);
        iFilledCircle(460,55,15);

        iSetColor(r+10,g+10,b+10);
        iFilledCircle(458,57,10);

        iSetColor(r+30,g+30,b+30);
        iFilledCircle(456,59,8);

        iSetColor(r+50,g+50,b+50);
        iFilledCircle(454,60,6);

        iSetColor(r+70,g+70,b+70);
        iFilledCircle(452,61,4);

        iSetColor(245,245,245);
        iFilledCircle(450,62,2);

        if(rep_shoot_color==4)              //Special Ball 1 - vanish all bubbles in a certain range Boom!
        {
            iSetColor(210,0,0);
            iFilledCircle(460,55, 15);

            iSetColor(255,255,0);
            iFilledEllipse(460,55,8,15);

            iSetColor(255,102,0);
            iFilledEllipse(460,55,5,15);

            iSetColor(255,255,0);
            iFilledEllipse(460,55,15,8);

            iSetColor(255,102,0);
            iFilledEllipse(460,55,15,5);

            iSetColor(255,30,0);
            iFilledCircle(460,55, 8);
        }

        if(shoot_color==5)              //Special Ball 2 - vanish all bubbles of same color!
        {
            iSetColor(0,0,255);
            iFilledCircle(460,55, 15);

            iSetColor(255,255,0);
            iFilledCircle(460,55,11);

            iSetColor(255,0,85);
            iFilledCircle(460,55, 8);

            iSetColor(0,255,0);
            iFilledCircle(460,55,4);
        }



        iSetColor(100,100,100);
        iLine(x_p,y_p,x2_p,y2_p);      //draw projection

        double x_arrow[]={x2_p,x2_p_A,x2_p_B},y_arrow[]={y2_p,y2_p_A,y2_p_B}; //draw arrow
        iSetColor(128,0,128);
        iFilledPolygon(x_arrow,y_arrow, 3);
    }
    if (!p)
    {
        //n = 1;
        iShowBMP(0, 0, "wheel (2).bmp");
    }

}






void iMouseMove(int mx, int my)
{

}

void iMouse(int button, int state, int mx, int my)
{
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN && (mx >= 250 && mx <= 500) && (my >= 420 && my <= 480))
    {
        n = 1;
    }
    else if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN && (mx >= 700 && mx <= 800) && (my >= 20 && my <= 200))
    {
        exit(0);
    }
    else if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN && (mx >= 250 && mx <= 500) && (my >= 360 && my <= 400))
    {
        p = 0;
    }

}


void iKeyboard(unsigned char key)
{

}

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
        shoot=1;
    }

    if(key==GLUT_KEY_DOWN)       //swap rep shooter and current shooter
    {
         int temp=rep_shoot_color;
         rep_shoot_color=shoot_color;
         shoot_color=temp;
    }
}


int main()
{

    iSetTimer(1,movement);
    iSetTimer(8000,newline);
    color();
    iInitialize(800,750 , "Bubble Shooter");
    return 0;
}





