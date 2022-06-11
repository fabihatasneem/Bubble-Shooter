#include "iGraphics.h"
#include "iostream"
#include "fstream"
#define pi acos(-1)
using namespace std;

int console_width=1400, console_height=780;
double t=0;
int centre_x=console_width/2, centre_y=console_height/2;

char *epochChar=NULL;
double epoch= 0, epoch2 ;
double del_epoch = pi/8;
int frequency=3, freq_ratio=1;
int amplitudeA=200, amplitudeB=200;

double x,y;
double multiplier=500;
int color_index=0;
int clearScreen=0;
int dir=1;

char buffer;

typedef struct linecolor
{
    int R;
    int G;
    int B;
};

struct linecolor color[] =
{
    {255,250,125},
    {250, 10, 10},
    {210, 250, 210},
    {10, 10, 250},
    {255,250,125}
};


void iDraw()
{
    iSetColor(255,255,255);
    iText(centre_x,450, )
    iClear();
//    if(clearScreen)
//    {
//        iClear();
//        //printf("\t YES \n");
//        clearScreen=0;
//    }
//printf("%d",clearScreen);

    iSetColor(color[color_index].R, color[color_index].G, color[color_index].B);
    iFilledCircle(x,y,2);

    iText(centre_x, 50, "Press 1 or 2 to change ratio of the frequency");
    iText(centre_x, 25, "Press Up arrow key to change the phase difference/epoch.");

    iSetColor(250,250,250);
    itoa(freq_ratio, buffer, 10);
    iText(centre_x, 450, buffer, 30);

}


void update_t(int n)         //here n=36000 or 3600
{
    if(t<n)
        t++;
    if(t==n)
        t=0;
}

void UpdateCoordinates()
{
    update_t(500*multiplier);//change later

    x = centre_x + amplitudeA*sin(2*pi*frequency*t*freq_ratio/multiplier + epoch);
    y = centre_y + amplitudeB*sin(2*pi*frequency*t/multiplier);
}


void iMouseMove(int mx, int my)
{

}

void iMouse(int button, int state, int mx, int my)
{

}

void ColorIndexChange()
{
    if(color_index<4 && dir==1)
    {
        color_index++;
    }
    else if(color_index==4 && dir==1)
    {
        dir=0;
        color_index--;
    }
    else if(color_index<4 && dir==0)
    {
        color_index--;
        //printf("\t YES \n");
    }
    if(color_index<0 && dir==0)
    {
        dir=1;
        color_index+=2;
    }

}

void iKeyboard(unsigned char key)
{
    if(key == '1')
    {
        ifstream infile("foo.txt");
        if(infile.is_open())
        {
            itoa()
            infile >> freq_ratio;
            cout << freq_ratio;
            infile.close();
        }
        ofstream outfile("foo.txt");
        if(outfile.is_open())
        {
            freq_ratio++;
            outfile << freq_ratio << endl;
            outfile.close();
        }
        ColorIndexChange();
    }
    if(key == '2')
    {
        ifstream infile("foo.txt");
        if(infile.is_open())
        {
            infile >> freq_ratio;
            cout << freq_ratio;
            infile.close();
        }
        ofstream outfile("foo.txt");
        if(outfile.is_open())
        {
            freq_ratio--;
            outfile << freq_ratio << endl;
            outfile.close();
        }
        ColorIndexChange();
    }
    if(key == 'q')
    {
        exit(0);
    }
    if(key == 'p')
    {
        iPauseTimer(0);
    }
    if(key == 'r')
    {
        iResumeTimer(0);
    }
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
    if(key == GLUT_KEY_UP)
    {
        epoch+=del_epoch;
        epoch2=epoch*180/pi;
        ColorIndexChange();
        clearScreen=1;
        //printf("%d\n", color_index);
    }
    if(key == GLUT_KEY_DOWN)
    {
        epoch-=del_epoch;
        epoch2=epoch*180/pi;
        ColorIndexChange();
        clearScreen=1;
    }
}


int main()
{
    iSetTimer(30,UpdateCoordinates);
    iInitialize(console_width, console_height, "Demo!");

    return 0;
}
