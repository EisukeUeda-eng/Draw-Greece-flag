// セーシェルの国旗を作成

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "mypnm.h"

#define WIDTH 640
#define HEIGHT 480

int sgn(int x)
{
  if ( x<0 ) return -1;
  if ( x>0 ) return 1;
  return 0;
}

int abs(int x)
{
  if ( x>=0 ) return x;
  return -x;
}

void swap(int *x,int *y)
{
  int tmp=*x;
  *x=*y;
  *y=tmp;
}


#if 1
unsigned char scr[WIDTH][HEIGHT];
unsigned char *red, *grn, *blu;

void Line(int x1, int x2, int y1, int y2, int X[HEIGHT], int nred, int ngrn, int nblu);
//直線を引くための関数Line
//引数は(x1,y1)から(x2,y2)に引くための各座標の値と赤色成分の値nred,緑色成分の値ngrn,青色成分の値nblu

int main(){
    int x, y;　//x, y座標を表すための変数
    int X1[HEIGHT] = {0};
    int X2[HEIGHT] = {0};
    int X3[HEIGHT] = {0};
    int X4[HEIGHT] = {0};
    //直線を引いた時に任意のy座標のx座標を記録しておくための配列
    //今回は直線を4本引くので4つ用意
    
    red = (unsigned char *)malloc(sizeof(char)*WIDTH*HEIGHT);
    grn = (unsigned char *)malloc(sizeof(char)*WIDTH*HEIGHT);
    blu = (unsigned char *)malloc(sizeof(char)*WIDTH*HEIGHT);
   

    Line(0, 200, HEIGHT-1, 0, X1, 0, 63, 135); //青色直線を(0,479)から(160,0)まで引く
    for(y = 0; y < HEIGHT; y++){
        for(x = 0; x < X1[y]; x++){
            red[y*WIDTH+x] = 0;
            grn[y*WIDTH+x] = 63;
            blu[y*WIDTH+x] = 135;
        }
    }
    //青色部分の塗りつぶし
    
    
    Line(0, 480, HEIGHT-1, 0, X2, 252, 216, 86);
       //黄色直線を(0,479)から(480,0)まで引く
    for(y = 0; y < HEIGHT; y++){
        for(x = X1[y]; x < X2[y]; x++){
            red[y*WIDTH+x] = 252;
            grn[y*WIDTH+x] = 216;
            blu[y*WIDTH+x] = 86;
        }
    }
    //黄色部分の塗りつぶし
    
    
    Line(0, WIDTH, HEIGHT-1, 160, X3, 214, 40, 40);
       //赤色直線を(0,479)から(640,160)まで引く
    for(y = 0; y < HEIGHT; y++){
        if(X3[y] == 0){
            for(x = X2[y]; x < WIDTH; x++){
                red[y*WIDTH+x] = 214;
                grn[y*WIDTH+x] = 40;
                blu[y*WIDTH+x] = 40;
            }
        }
        //配列の値が更新されていない場合はx座標が最大(640)になるまで塗りつぶす
        else{
            for(x = X2[y]; x < X3[y]; x++){
                red[y*WIDTH+x] = 214;
                grn[y*WIDTH+x] = 40;
                blu[y*WIDTH+x] = 40;
            }
        }
        //配列の値が更新されている場合は、赤色直線を引いた時に記録した配列に記録されているx座標になるまで塗りつぶす
           
    }
    //赤色部分の塗りつぶし
    
    
    Line(0, WIDTH, HEIGHT-1, 320, X4, 255, 255, 255);
    　　　//白色直線を(0,479)から(640,320)まで引く
    for(y = 160; y < HEIGHT; y++){
        if(X4[y] == 0){
            for(x = X3[y]; x < WIDTH; x++){
                red[y*WIDTH+x] = 255;
                grn[y*WIDTH+x] = 255;
                blu[y*WIDTH+x] = 255;
            }
        }
        //配列の値が更新されていない場合はx座標が最大(640)になるまで塗りつぶす
        else{
            for(x = X3[y]; x < X4[y]; x++){
                red[y*WIDTH+x] = 255;
                grn[y*WIDTH+x] = 255;
                blu[y*WIDTH+x] = 255;
            }
        }
        //配列の値が更新されている場合は、白色直線を引いた時に記録した配列に記録されているx座標になるまで塗りつぶす
    }
    //白色部分の塗りつぶし
    
    
    for(y = 320; y < HEIGHT; y++){
        for(x = X4[y]; x < WIDTH; x++){
            red[y*WIDTH+x] = 0;
            grn[y*WIDTH+x] = 122;
            blu[y*WIDTH+x] = 61;
        }
    }
    //緑色部分の塗りつぶし
    
    save_ppm( "Seychelles.ppm", red, grn, blu, WIDTH, HEIGHT ); //画像の保存
  
    free(red);
    free(grn);
    free(blu);
    
    return 0;
}

void Line(int x1, int x2, int y1, int y2, int X[HEIGHT], int nred, int ngrn, int nblu){
    int x, y, e, dx, dy, sx, sy;
    
    dx = abs(x2 - x1);
    dy = abs(y2 - y1);
    sx = sgn(x2 - x1);
    sy = sgn(y2 - y1);
    
    if(dx >= dy){
        if(x1 > x2){
            swap(&x1, &x2);
            swap(&y1, &y2);
            sy *= -1;
        }
        e = dx;
        for(x = x1, y = y1; x <= x2; x++){
            red[y*WIDTH+x] = nred;
            grn[y*WIDTH+x] = ngrn;
            blu[y*WIDTH+x] = nblu;
            X[y] = x;　　//y座標の値がyのときのx座標の値xを記録
            e += 2 * dy;
            if(e >= 2 * dx){
                y += sy;
                e -= 2 * dx;
            }
        }
    }
    else{
        if(y1 > y2){
            swap(&x1, &x2);
            swap(&y1, &y2);
            sx *= -1;
        }
        e = dy;
        for(x = x1, y = y1; y <= y2; y++){
            red[y*WIDTH+x] = nred;
            grn[y*WIDTH+x] = ngrn;
            blu[y*WIDTH+x] = nblu;
            X[y] = x;  //y座標の値がyのときのx座標の値xを記録
            e += 2 * dx;
            if(e >= 2 * dy){
                x += sx;
                e -= 2 * dy;
            }
        }
        
    }
}

#endif
