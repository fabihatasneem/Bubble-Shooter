# include "iGraphics.h"
# include "Windows.h"
# include "stdlib.h"
# include "stdio.h"
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
int n = 0, p = 1, w1 = 0, w2 = 0, w3 = 0, w4 = 0, q1 = 0, q2 = 0, yes = 0, no = 0, bk = 0, opt = 0, no_sound = 0, pause = 0, resume = 0, option = 0, made = 0; // cover to game page linkup
int game_over = 0;

//necessary var for special balls
int wait_for_bomb=0;
int bomb_color;

//necessary var for scoring
int score=0;
char pscore[1000], arr[1000];

//necessary var for saving game
char buffer;
char cur_score[100], buf[100], hi_sc[100];

void show_score()
{
    //char cur_score[100], buf[100];
    strcpy(cur_score,"YOUR SCORE: ");
    strcat(cur_score,itoa(score,buf,10));
    iSetColor(255,0,0);
    iText(20,720,cur_score, GLUT_BITMAP_TIMES_ROMAN_24);
}
//necessary var for dfs
int cnt=0, hi_score, congo = 0;
int dx[]= {-40,40,0,0};
int dy[]= {0,0,40,-40};
int vis[8000][8000];

void high (int n)
{
    FILE *fp = fopen("highscore.txt", "r");
    fscanf(fp, "%d", &hi_score);
    fclose(fp);
    if (score > hi_score)
    {
        congo = 1;
        FILE *fp1 = fopen("highscore.txt", "w");
        fprintf(fp1, "%d", score);
        fclose(fp1);
    }
}

void dfs(int x,int y)
{
    cnt++;
    vis[x][y]=1;
    for(int i=0; i<4; i++)
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
                    score += 10;
                    sprintf(pscore,"%d",score);
                }
            }
        }
    }
}

void island()     //eliminate ceilles bubble
{
    for(int i=20; i<=780; i+=40)
    {
        for(int j=690; j>=90; j-=40)
        {
            if(exist[i][j]==1 && exist[i][j+40]==0 && exist[i+40][j]==0 && exist[i-40][j]==0)
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
            if(j<=130 && exist[i][j]==1)
            {
                game_over = 1;
                if (!no_sound)
                    PlaySound("Game_Over.wav", NULL, SND_ASYNC | SND_ASYNC);
            }
        }
    }
}

void movement() // shooter movement by iSetTimer()
{
    if(shoot==1 && y_shoot<=690 )
    {
        wait_for_bomb++;
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
        else
        {
            y_shoot+=10;
            x_shoot+=tan(shoot_angle)*10;
        }
        if(x_shoot<30 || x_shoot>780)
        {
            //reflection

            shoot_angle=-shoot_angle;

        }

        for(int i=-20; i<=20; i++)
        {
            for(int j=0; j<=40; j++)
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

                        else
                        {
                            x_shoot=x_shoot+i;
                            y_shoot=y_shoot+j-40;

                        }

                    }
                    else
                    {
                        if(shoot_angle>0)
                        {
                            if(exist[x_shoot+i-40][y_shoot+j]==0)
                            {
                                x_shoot+=i-40;
                                y_shoot=y_shoot+j;
                            }
                            else
                            {
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
                            else
                            {
                                x_shoot=x_shoot+i;
                                y_shoot=y_shoot+j-40;

                            }
                        }

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

                    //Fabiha needs to vanish all the balls in a certain range using Special ball-1 !
                    if(shoot_color==5)
                    {
                        for(int i=-120; i<=120; i+=40)
                        {
                            for(int j=0; j<=120; j+=40)
                            {
                                exist[x_shoot+i][y_shoot+j]=0;
                                score += 10;
                                sprintf(pscore,"%d",score);
                            }
                        }
                        shooter_gone=1;
                    }

                    island();
                    shoot=0;
                }
            }
        }

        shoot_color_flag=0; // without this shoot color changes until shoot=1
        rep_shoot_color_flag=0;
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
            //Because Fabiha has to wait patiently for those bombs to appear!
            if(wait_for_bomb==5)
            {
                rep_shoot_color=5;
                wait_for_bomb=0;
            }
            else
            {
                rep_shoot_color=rand()%4;
            }
            rep_shoot_color_flag=1;
        }
    }

}


void iDraw()
{

    iClear();
    if (!n)
    {
        // cover image to different pg linkup
        // Maneesha's code, don't dare touch it
        iShowBMP(0, 0, "menu.bmp");
        iSetColor(0, 0, 0);
        iFilledRectangle(260, 440, 280, 50);
        iSetColor(250, 225, 190);
        iFilledRectangle(263, 443, 273, 43);
        iSetColor(0, 0, 0);
        iText(330, 460, "NEW GAME", GLUT_BITMAP_TIMES_ROMAN_24);
        if (w1)
        {
            w2 = 0, w3 = 0;
            iSetColor(220, 20, 60);
            iFilledRectangle(260, 440, 280, 50);
            iSetColor(0, 0, 0);
            iText(330, 460, "NEW GAME", GLUT_BITMAP_TIMES_ROMAN_24);
        }
        iFilledRectangle(260, 370, 280, 50);
        iSetColor(250, 225, 190);
        iFilledRectangle(263, 373, 273, 43);
        iSetColor(0, 0, 0);
        iText(315, 390, "HOW TO PLAY", GLUT_BITMAP_TIMES_ROMAN_24);
        if (w2)
        {
            w1 = 0, w3 = 0, w4 = 0;
            iSetColor(220, 20, 60);
            iFilledRectangle(260, 370, 280, 50);
            iSetColor(0, 0, 0);
            iText(315, 390, "HOW TO PLAY", GLUT_BITMAP_TIMES_ROMAN_24);
        }
        iFilledRectangle(260, 300, 280, 50);
        iSetColor(250, 225, 190);
        iFilledRectangle(263, 303, 273, 43);
        iSetColor(0, 0, 0);
        iText(320, 320, "HIGH SCORES", GLUT_BITMAP_TIMES_ROMAN_24);
        if (w3)
        {
            w1 = 0, w2 = 0, w4 = 0;
            iSetColor(220, 20, 60);
            iFilledRectangle(260, 300, 280, 50);
            iSetColor(0, 0, 0);
            iText(320, 320, "HIGH SCORES", GLUT_BITMAP_TIMES_ROMAN_24);
        }

        iFilledRectangle(260, 230, 280, 50);
        iSetColor(250, 225, 190);
        iFilledRectangle(263, 233, 273, 43);
        iSetColor(0, 0, 0);
        iText(360, 250, "ABOUT", GLUT_BITMAP_TIMES_ROMAN_24);
        if (w4)
        {
            w1 = 0, w2 = 0, w3 = 0;
            iSetColor(220, 20, 60);
            iFilledRectangle(260, 230, 280, 50);
            iSetColor(0, 0, 0);
            iText(360, 250, "ABOUT", GLUT_BITMAP_TIMES_ROMAN_24);
        }

        iRectangle(720, 40, 60, 60);
        iSetColor(220, 20, 60);
        iLine(720, 40, 780, 100);
        iLine(720, 100, 780, 40);
        if (q1)
        {
            iSetColor(255, 0, 0);
            iFilledRectangle(720, 40, 60, 60);
            iSetColor(0, 0, 00);
            iLine(720, 40, 780, 100);
            iLine(720, 100, 780, 40);
            if (q2)
            {
                iSetColor(0, 0, 0);
                iFilledRectangle(197, 297, 427, 157);
                iSetColor(255, 127, 80);
                iFilledRectangle(201, 300, 420, 150);
                iSetColor(0, 0, 255);
                iText(215, 400, "DO YOU REALLY WANT TO QUIT?", GLUT_BITMAP_TIMES_ROMAN_24);
                iSetColor(0, 0, 0);
                iRectangle(220, 320, 100, 50);
                iRectangle(480, 320, 100, 50);
                iSetColor(0, 0, 255);
                iText(240, 335, "YES", GLUT_BITMAP_TIMES_ROMAN_24);
                iText(510, 335, "NO", GLUT_BITMAP_TIMES_ROMAN_24);
                if (yes == 1)
                {
                    iSetColor(255, 0, 0);
                    iFilledRectangle(220, 320, 100, 50);
                    iSetColor(0, 0, 255);
                    iText(240, 335, "YES", GLUT_BITMAP_TIMES_ROMAN_24);
                    //if (yes == 2) exit(0);

                }
                else if (no == 1)
                {
                    iSetColor(255, 0, 0);
                    iFilledRectangle(480, 320, 100, 50);
                    iSetColor(0, 0, 255);
                    iText(510, 335, "NO", GLUT_BITMAP_TIMES_ROMAN_24);
                }
            }
        }
    }
    else
    {
        iShowBMP(0, 0, "sea.bmp");

        iSetColor(0,0,0);
        for(int i=0; i<=800; i+=7)
        {
            iLine(i,110,i+3,110);           //draw base
        }

        for(int i=0; i<=800; i+=7)
        {
            iLine(i,710,i+3,710);           //draw ceil
        }
        iSetColor(0, 0, 0);                 // draw score and options
        //iRectangle(10, 715, 200, 30);

//        iText(20, 720, "SCORE: ", GLUT_BITMAP_TIMES_ROMAN_24);
//        sprintf(buf, "%d", score);
        //iText(50, 720, pscore, GLUT_BITMAP_TIMES_ROMAN_24);
        iRectangle(570, 715, 50, 30); // pause/resume
        if (pause == 1)
        {
            iSetColor(255, 255, 255);
            iFilledRectangle(570, 715, 50, 30);
            iSetColor(0, 0, 0);
            iLine(590, 740, 590, 720);
            iLine(598, 740, 598, 720);
        }
        else if (pause == 2)
        {
            iLine(585, 740, 585, 720);
            iLine(585, 740, 610, 730);
            iLine(585, 720, 610, 730);
        }
        else if (!pause)
        {
            iLine(590, 740, 590, 720);
            iLine(598, 740, 598, 720);
        }
        iRectangle(640, 715, 50, 30);
        iFilledRectangle(655, 735, 20, 5); // sound on/off
        iLine(656, 740, 656, 720);
        iLine(676, 740, 676, 720);
        iFilledEllipse(650, 722, 6, 3);
        iFilledEllipse(670, 722, 6, 3);
        if (no_sound)
        {
            iLine(650, 740, 680, 718);
        }
        iRectangle(710, 715, 50, 30); // quit
        iLine(715, 720, 750, 740);
        iLine(715, 740, 750, 720);

        for(int i=0; i<=800; i++) // draw bubble
        {
            for(int j=0; j<=710; j++)
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
                    r=60,g=60,b=60;
                }
                if(exist[i][j] && clr[i][j]!=4)
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
                if(exist[i][j] && clr[i][j]==4)                 //different design for the gray stones
                {
                    iSetColor(r,g,b);
                    iFilledCircle(i,j,20);

                    iSetColor(r+30,g+30,b+30);
                    iFilledEllipse(i,j,14,20);

                    iSetColor(r+60,g+60,b+60);
                    iFilledEllipse(i,j,9,20);

                    iSetColor(r+90,g+90,b+90);
                    iFilledEllipse(i,j,4,20);
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
        iFilledCircle(x_shoot,y_shoot,20); //draw shooter
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

        if(shoot_color==5)              //Special Ball 1 - vanish all bubbles in a certain range Boom!
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
        iFilledCircle(457,59,8);

        iSetColor(r+50,g+50,b+50);
        iFilledCircle(456,60,6);

        iSetColor(r+70,g+70,b+70);
        iFilledCircle(455,61,4);

        iSetColor(245,245,245);
        iFilledCircle(454,62,2);

        if(rep_shoot_color==5)              //Special Ball 1 - vanish all bubbles in a certain range Boom!
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




        iSetColor(100,100,100);
        iLine(x_p,y_p,x2_p,y2_p);      //draw projection

        double x_arrow[]= {x2_p,x2_p_A,x2_p_B},y_arrow[]= {y2_p,y2_p_A,y2_p_B}; //draw arrow
        iSetColor(128,0,128);
        iFilledPolygon(x_arrow,y_arrow, 3);
    }
    if (n && q1)
    {
        iSetColor(255, 255, 255);
        iFilledRectangle(710, 715, 50, 30);
        iSetColor(0, 0, 0);
        iLine(715, 720, 750, 740);
        iLine(715, 740, 750, 720);
        if (q2)
        {
            iSetColor(255, 127, 80);
            iFilledRectangle(200, 300, 420, 150);
            iSetColor(0, 0, 255);
            iText(215, 400, "DO YOU REALLY WANT TO QUIT?", GLUT_BITMAP_TIMES_ROMAN_24);
            iSetColor(0, 0, 0);
            iRectangle(220, 320, 100, 50);
            iRectangle(480, 320, 100, 50);
            iSetColor(0, 0, 255);
            iText(240, 335, "YES", GLUT_BITMAP_TIMES_ROMAN_24);
            iText(510, 335, "NO", GLUT_BITMAP_TIMES_ROMAN_24);
            if (yes == 1)
            {
                iSetColor(255, 0, 0);
                iFilledRectangle(220, 320, 100, 50);
                iSetColor(0, 0, 255);
                iText(240, 335, "YES", GLUT_BITMAP_TIMES_ROMAN_24);
                //if (yes == 2) exit(0);

            }
            else if (no == 1)
            {
                iSetColor(255, 0, 0);
                iFilledRectangle(480, 320, 100, 50);
                iSetColor(0, 0, 255);
                iText(510, 335, "NO", GLUT_BITMAP_TIMES_ROMAN_24);
            }
        }
    }
    if (game_over)
    {
        iPauseTimer(1);
        iShowBMP(0, 0, "gameOver.bmp");
        high(score);
        iText(250, 420, "YOUR SCORE: ", GLUT_BITMAP_TIMES_ROMAN_24);
        iText(420, 420, pscore, GLUT_BITMAP_TIMES_ROMAN_24);
        if (congo)
        {
            iText(250, 380, "Congratulations!!! New high score", GLUT_BITMAP_TIMES_ROMAN_24);
        }
        else if (!congo)
        {

            iText(250, 380, "HIGH SCORE: ", GLUT_BITMAP_TIMES_ROMAN_24);
            iText(420, 380, itoa(hi_score, hi_sc, 10), GLUT_BITMAP_TIMES_ROMAN_24);
        }
    }
    if (!p)
    {
        iShowBMP(0, 0, "instruction.bmp");
        iSetColor(255, 29, 206);
        iRectangle(650, 100, 100, 50);
        iText(670, 120, "BACK", GLUT_BITMAP_TIMES_ROMAN_24);
        if (bk)
        {
            iSetColor(255, 255, 255);
            iFilledRectangle(650, 100, 100, 50);
            iSetColor(255, 29, 206);
            iText(670, 120, "BACK", GLUT_BITMAP_TIMES_ROMAN_24);
        }
    }
    if (made)
    {
        iShowBMP(0, 0, "madeby.bmp");
        iSetColor(255, 29, 206);
        iRectangle(650, 100, 100, 50);
        iText(670, 120, "BACK", GLUT_BITMAP_TIMES_ROMAN_24);
        if (bk)
        {
            iSetColor(255, 255, 255);
            iFilledRectangle(650, 100, 100, 50);
            iSetColor(255, 29, 206);
            iText(670, 120, "BACK", GLUT_BITMAP_TIMES_ROMAN_24);
        }
    }

    if (n) show_score();
}

void iMouseMove(int mx, int my)
{

}

void iMouse(int button, int state, int mx, int my) // menu to game linkup and settings
{

    if (!n && button == GLUT_LEFT_BUTTON && (mx >= 260 && mx <= 540) && (my >= 440 && my <= 490)) // new game
    {
        if (state == GLUT_DOWN)
            w1 = 1;
        else
            n = 1;
        iResumeTimer(0);
        iResumeTimer(1);
        PlaySound(NULL, NULL, SND_ASYNC | SND_LOOP);
    }
    else if (!n && button == GLUT_LEFT_BUTTON &&(mx >= 260 && mx <= 540) && (my >= 370 && my <= 420)) // how to play
    {
        if (state == GLUT_DOWN)
            w2 = 1;
        else
            p = 0;
        iPauseTimer(1);
    }
    else if (!n && (!p) && button == GLUT_LEFT_BUTTON &&(mx >= 650 && mx <= 750) && (my >= 100 && my <= 150))
    {
        if (state == GLUT_DOWN)
        {
            bk = 1;
        }
        else
        {
            p = 1;
            w2 = 0;
            bk = 0;
            n = 0;
        }
    }
    else if (!n && button == GLUT_LEFT_BUTTON &&(mx >= 260 && mx <= 540) && (my >= 300 && my <= 350))
    {
        if (state == GLUT_DOWN)
            w3 = 1;
    }
    else if (!n && button == GLUT_LEFT_BUTTON &&(mx >= 260 && mx <= 540) && (my >= 230 && my <= 270))
    {
        if (state == GLUT_DOWN)
            w4 = 1;
        else if (state == GLUT_UP)
        {
            made = 1;
            iPauseTimer(1);
        }
    }
    else if (!n && (made) && button == GLUT_LEFT_BUTTON &&(mx >= 650 && mx <= 750) && (my >= 100 && my <= 150))
    {
        if (state == GLUT_DOWN)
        {
            bk = 1;
        }
        else
        {
            made = 0;
            w4 = 0;
            bk = 0;
            n = 0;
        }
    }
    else if (!n && button == GLUT_LEFT_BUTTON &&(mx >= 720 && mx <= 780) && (my >= 40 && my <= 100))
    {
        if (state == GLUT_DOWN)
            q1 = 1;
        else
        {
            q2 = 1;
            //exit(0);
        }
    }
    if (!n && (q2) && button == GLUT_LEFT_BUTTON && (mx >= 220 && mx <= 320) && (my >= 320 && my <= 370))
    {
        if (state == GLUT_DOWN)
            yes = 1;
        else if (state == GLUT_UP)
            exit(0);
    }
    else if (!n && (q2) && button == GLUT_LEFT_BUTTON && (mx >= 480 && mx <= 580) && (my >= 320 && my <= 370))
    {
        if (state == GLUT_DOWN)
            no = 1;
        else if (state == GLUT_UP)
            n = 0;
        q1 = 0;
        q2 = 0;
        yes = 0;
        no = 0;
        iResumeTimer(1);
        iResumeTimer(0);
    }
    if (n && button == GLUT_LEFT_BUTTON)
    {
        if ((mx >= 570 && mx <= 620) && (my >= 715 && my <= 745))
        {
            if (!pause && state == GLUT_DOWN)
            {
                pause = 1;
                resume = 1;
            }
            else if (pause == 1 && state == GLUT_UP && resume == 1)
            {
                pause = 2;
                resume = 0;
                iPauseTimer(1);
                iPauseTimer(0);

            }
            else if (pause == 2 && state == GLUT_DOWN && resume == 0)
            {
                pause = 1;
            }
            else if (pause == 1 && state == GLUT_UP && resume == 0)
            {
                pause = 0;
                iResumeTimer(1);
                iResumeTimer(0);
            }
        }
        else if ((mx >= 710 && mx <= 760) && (my >= 715 && my <= 745))
        {
            if (state == GLUT_DOWN)
                q1 = 1;
            else
            {
                q2 = 1;
                iPauseTimer(0);
                iPauseTimer(1);
                //exit(0);
            }
        }
        if ((q2) && (mx >= 220 && mx <= 320) && (my >= 320 && my <= 370))
        {
            iPauseTimer(1);
            iPauseTimer(0);
            if (state == GLUT_DOWN)
                yes = 1;
            else if (state == GLUT_UP)
                exit(0);
        }
        else if ((q2) && (mx >= 480 && mx <= 580) && (my >= 320 && my <= 370))
        {
            if (state == GLUT_DOWN)
                no = 1;
            else if (state == GLUT_UP)
                n = 0;
            q1 = 0;
            q2 = 0;
            yes = 0;
            no = 0;
            iResumeTimer(1);
            iResumeTimer(0);
        }
        else if (!no_sound && (mx >= 640 && mx <= 690) && (my >= 715 && my <= 745))
        {
            if (state == GLUT_DOWN)
                no_sound = 1;
            PlaySound(NULL, NULL, SND_ASYNC | SND_LOOP);
        }
        else if (no_sound && (mx >= 640 && mx <= 690) && (my >= 715 && my <= 745))
        {
            if (state == GLUT_DOWN)
                no_sound = 0;
        }
    }
}

void iKeyboard(unsigned char key)
{

}

void iSpecialKeyboard(unsigned char key)
{
    if(!pause && !q1 && key==GLUT_KEY_RIGHT)     //shooter/projection angle change
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

    if(!pause && !q1 && key==GLUT_KEY_LEFT)      //shooter/projection angle change
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

    if(!pause && !q1 && key==GLUT_KEY_UP)       //shoot!!!
    {
        shoot=1;
        if (!no_sound)
            PlaySound("shoot.wav", NULL, SND_ASYNC | SND_ASYNC);
    }

    if(!pause && !q1 && key==GLUT_KEY_DOWN)       //swap rep shooter and current shooter
    {
        int temp=rep_shoot_color;
        rep_shoot_color=shoot_color;
        shoot_color=temp;
    }

}

void menu_music()
{
    PlaySound("menu.wav", NULL, SND_ASYNC | SND_LOOP);
}

int main()
{
    iSetTimer(1,movement);
    iSetTimer(5000,newline);
    color();
    menu_music();
    if (!n)
    {
        iPauseTimer(0);
        iPauseTimer(1);
    }
    iInitialize(800,750, "Bubble Shooter");
    return 0;
}
