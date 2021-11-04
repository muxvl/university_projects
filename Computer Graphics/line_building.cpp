#include <conio.h>
#include <locale.h>
#include <graphics.h>
#include <math.h>
#include <cmath>
#include <stdio.h>
#include <iostream>

using namespace std;

void mult (float **a, float (&b)[3][3])
{
    int m = 2;
    int q = 3;
    int i,j;
    float **c = new float *[m];
    for (i = 0; i < m; i++)
    {
        c[i] = new float [q];
    }

    for (i = 0; i < m; i++)
    {
        for (j = 0; j < q; j++)
{
c[i][j] = 0;
for (int k = 0; k <= q + 1; k++)
c[i][j] += (a[i][k]*b[k][j]);
}
    }
    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < q; j++ )
        {
            a[i][j] = c[i][j];
        }
    } 
for (int i = 0; i< m; i++)
{
delete [] c[i];
}
delete[] c;
}
void move(float **A, float DX, float DY)
{
float MP[3][3] = {
{1, 0, 0},
{0, 1, 0},
{DX, DY, 1}
};
mult(A, MP);
}
void mashtab(float **A, float s1)
{
float MM[3][3] = {
{s1, 0, 0},
{0, s1, 0},
{0, 0, 1}
};
mult(A, MM);
}
void povorot(float **A, float grad)
{
/*float alpha = 0.087;
float MP[3][3] = {
{grad*cos(alpha), grad*sin(alpha), 0},
{grad*(-sin(alpha)), grad*cos(alpha), 0},
{0, 0, 1}
};
mult(A, MP);*/
float dx = (A[0][0] + A[1][0]) / 2;
float dy = (A[0][1] + A[1][1]) / 2;
A[0][0]=dx+(A[0][0]-dx)*cosf(grad*3.14/180)-(A[0][1]-dy)*sinf(grad*3.14/180);
A[0][1]=dy+(A[0][0]-dx)*sinf(grad*3.14/180)+(A[0][1]-dy)*cosf(grad*3.14/180);
A[1][0]=dx+(A[1][0]-dx)*cosf(grad*3.14/180)-(A[1][1]-dy)*sinf(grad*3.14/180);
A[1][1]=dy+(A[1][0]-dx)*sinf(grad*3.14/180)+(A[1][1]-dy)*cosf(grad*3.14/180);
}
void line_Brezen (int x1, int y1, int x2, int y2)
{
int dx=(x2-x1>=0?1:-1);
int dy=(y2-y1>=0?1:-1);
int lengthX=abs(x2-x1);
int lengthY=abs(y2-y1);
int length=(lengthX>lengthY?lengthX:lengthY);
if (length==0)
putpixel(x1, y1, 5);
if (lengthY<=lengthX) {
int x=x1, y=y1;
int d=-lengthX;
length++;
while (length--) {
putpixel(x, y, 5);
x+=dx;
d+=2*lengthY;
if (d>0) {
d-=2*lengthX;
y+=dy;
}
}
}
else {
int x=x1, y=y1;
int d=-lengthY; 
length++;
while (length--) {
putpixel(x, y, 5);
y+=dy;
d+=2*lengthX;
if (d>0) {
d-=2*lengthY;
x+=dx;
}
}
}
}
void draw (float **B, int color)
{
//bresenham(round(B[0][0]),round(B[0][1]),round(B[1][0]),round(B[1][1]),color);
line_Brezen(round(B[0][0]),round(B[0][1]),round(B[1][0]),round(B[1][1]));
}
void draw_line(float **A)
{
line(A[0][0],A[0][1],A[1][0],A[1][1]);
}
int main()
{
setlocale(LC_ALL,"Rus");
initwindow(800, 800);
float DX, DY;
int code;
int n = 3;
int m = 2;
float **first = new float *[m];
for (int i = 0; i < m; i++){
first[i] = new float [n];
}
first[0][0] = 10;
first[0][1] = 10;
first[1][0] = 10;
first[1][1] = 60;
first[0][2] = first[1][2] = 1;
float **second = new float *[m];//áðåçåíõåì
for (int i = 0; i < m; i++){
second[i] = new float [n];
}
second[0][0] = 50;
second[0][1] = 50;
second[1][0] = 30;
second[1][1] = 30;
second[0][2] = second[1][2] = 1;
setcolor(4);
draw_line(first);
draw(second, 5);
cout << ("действия с линиями->\nфиолетовая линия->вверх-стрелка вверх\nвниз-стрелка
вниз\nвправо-стрелка вправо\nвлево-стрелка влево\nувеличить-пробел\n"
"уменьшить-backspase\nкрутить по часовой стрелке-9\nкрутить против часовой стрелки-7\n");
cout << ("действия с линиями->\nкрасная линия->вверх-'w'\nвниз-'s'\nвправо-'d'\nвлево-
'a'\nувеличить-'z'\n"
"уменьшить-'x'\nкрутить по часовой стрелке-'e'\nкрутить против часовой стрелк-'e'\n");
while(true) {
if ( kbhit() ) {
code = getch(); 
if ( code == 27 )
break;
switch ( code ) {
case 75:
move(first,-1,0);
break ;
case 'a':
move(second,-1,0);
break;
case 77:
move(first,1,0);
break;
case 'd':
move(second,1,0);;
break;
case 72:
move(first,0,-1);
break;
case 'w':
move(second,0,-1);
break;
case 80:
move(first,0,1);
break;
case 's':
move(second,0,1);
break;
case 32:
mashtab(first,1.05);
break;
case 'z':
mashtab(second,1.05);
break;
case 8:
mashtab(first,0.95);
break;
case 'x':
mashtab(second,0.95);
break;
case '0':
povorot(first,1);
break;
case 'r':
povorot(second,1);
break;
case '9':
povorot(first, -1);
break;
case 'e':
povorot(second, -1);
break;
default:
break;
}
cleardevice() ;
draw_line(first);
draw(second, 5);
}
}
for (int i = 0; i< m; i++)
{
delete [] first[i];
}
delete[] first;
for (int i = 0; i< m; i++)
{ 
delete [] second[i];
}
delete[] second;
getch();
closegraph();
return 0;
}