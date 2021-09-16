#include<winbgim.h>
#include<stdio.h>


void imprime_pac(int);
void leer_teclado();
void puntaje();
void mapear();
void borra(int xx,int yy);
void galleta();
void guardayck(int i,int j);
void movfantasma(int);
void fantasma();

int panX=800,panY=600; //resolución de la ventana
int pos[18]={25,50,75,100,125,150,175,200,225,250,275,300,325,350,375,400,425,450};
int x=8,y=16; //posición inicial del pacman
int xf=8,yf=5; //posición del fantasma...
int Ngalletitas=0;
int mem[20][20];

         //Procedemos a crear la matriz....
int mapa[20][20]={
        0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
        0,1,1,1,1,0,1,1,1,1,1,1,1,1,0,1,1,1,1,0,
        0,1,0,0,1,0,1,0,0,0,0,0,0,1,0,1,0,0,1,0,
        0,1,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,1,0,
        0,1,0,1,0,0,1,0,0,1,1,0,0,1,0,0,1,0,1,0,
        0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,
        0,1,0,1,0,0,1,0,0,0,0,0,0,1,0,0,1,0,1,0,
        0,1,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,1,0,
        0,1,0,0,1,0,1,0,0,0,0,0,0,1,0,1,0,0,1,0,
        0,1,1,1,1,0,1,0,0,0,0,0,0,1,0,1,1,1,1,0,
        0,1,0,1,0,0,1,0,0,0,0,0,0,1,0,0,1,0,1,0,
        0,1,1,1,1,0,1,0,0,0,0,0,0,1,0,1,1,1,1,0,
        0,1,0,0,1,0,1,0,0,0,0,0,0,1,0,1,0,0,1,0,
        0,1,0,1,1,1,1,1,1,0,0,1,1,1,1,1,1,0,1,0,
        0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,
        0,1,0,1,0,0,1,0,0,0,0,0,0,1,0,0,1,0,1,0,
        0,1,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,1,0,
        0,1,0,0,1,0,1,0,0,1,1,0,0,1,0,1,0,0,1,0,
        0,1,1,1,1,0,1,1,1,1,1,1,1,1,0,1,1,1,1,0,
        0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,};
        
int mov[18][18]={
        1,1,1,1,0,1,1,1,1,1,1,1,1,0,1,1,1,1,
        1,0,0,1,0,1,0,0,0,0,0,0,1,0,1,0,0,1,
        1,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,1,
        1,0,1,0,0,1,0,0,1,1,0,0,1,0,0,1,0,1,
        1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
        1,0,1,0,0,1,0,0,0,0,0,0,1,0,0,1,0,1,
        1,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,1,
        1,0,0,1,0,1,0,0,0,0,0,0,1,0,1,0,0,1,
        1,1,1,1,0,1,0,1,1,1,1,0,1,0,1,1,1,1,
        1,0,1,0,0,1,0,1,1,1,1,0,1,0,0,1,0,1,
        1,1,1,1,0,1,0,1,1,1,1,0,1,0,1,1,1,1,
        1,0,0,1,0,1,0,0,0,0,0,0,1,0,1,0,0,1,
        1,0,1,1,1,1,1,1,0,0,1,1,1,1,1,1,0,1,
        1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
        1,0,1,0,0,1,0,0,0,0,0,0,1,0,0,1,0,1,
        1,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,1,
        1,0,0,1,0,1,0,0,1,1,0,0,1,0,1,0,0,1,
        1,1,1,1,0,1,1,1,1,1,1,1,1,0,1,1,1,1,};
        

int main()
{
    
    for(int l=0;l<20;l++)
        for(int o=0;o<20;o++)
            mem[l][o]=0;
    
    initwindow(panX,panY);
    
    //Imprimimos "pacman" 
    settextstyle(1,0,3);
    setcolor(COLOR(246,255,5));
    outtextxy((panX/2)-50,panY/2,"PACMAN");
    
    //Le pedimos al usuario que ingrese una letra para comenzar...
    settextstyle(1,0,1);
    setcolor(COLOR(255,255,255));
    outtextxy((panX/2)-200,(panY/2)+30,"Presione una tecla para comenzar...");
    
    //Limpiamos la presentación...
    while(!getch());
    fflush(stdin);
    cleardevice();
    setlinestyle( SOLID_LINE, 1, THICK_WIDTH );

      puntaje();
      mapear();
      galleta();
      imprime_pac(3);
      	
        
    //...
    while(getch()!=27)
    {                          
      puntaje();
      mapear();
      leer_teclado();
      if(Ngalletitas==600||x==xf&&y==yf) 
      break;
    }
    
    if(Ngalletitas==600)
    {
      settextstyle(1,0,3);
      setcolor(COLOR(0,209,10));
      outtextxy((panX/2)-50,panY/2,"GANASTE!");                    
    }
    else
    {
      settextstyle(1,0,3);
      setcolor(COLOR(209,10,0));
      outtextxy((panX/2)-50,panY/2,"PERDISTE!");
    }
    
    while(!getch());          
    closegraph();        
	return 0;
}


void imprime_pac(int a)
{
      
      setcolor(COLOR(255,252,2));
      setfillstyle(SOLID_FILL,COLOR(255,252,2)); 
      switch(a)
       {
            case 0: //arriba
                 pieslice(pos[x]+10,pos[y]+10,0,60,9);
	             pieslice(pos[x]+10,pos[y]+10,120,360,9);
                 borra(x,y+1);
	             break;
            case 1: //abajo
                 pieslice(pos[x]+10,pos[y]+10,0,240,9);
	             pieslice(pos[x]+10,pos[y]+10,300,360,9);
	             borra(x,y-1);
                 break;
	        case 2: //izquierda
                 pieslice(pos[x]+10,pos[y]+10,0,150,9);
	             pieslice(pos[x]+10,pos[y]+10,210,360,9);
	             borra(x+1,y);
                 break;
	        case 3: //derecha
	             pieslice(pos[x]+10,pos[y]+10,30,330,9);
                 borra(x-1,y);
                 break;
       }
}

void leer_teclado()
{
     
     char tecla=getch();
	 if(tecla==80&&mov[y+1][x]==1&&(y+1)!=18){y++;imprime_pac(1);movfantasma(1);}       //abajo
	 else if(tecla==72&&mov[y-1][x]==1&&(y-1)!=-1){y--;imprime_pac(0);movfantasma(0);} //arriba
	 else if(tecla==75&&mov[y][x-1]==1&&(x-1)!=-1){x--;imprime_pac(2);movfantasma(2);} //izquierda
	 else if(tecla==77&&mov[y][x+1]==1&&(x+1)!=18){x++;imprime_pac(3);movfantasma(3);} //derecha
	
}

void puntaje()
{
    char cad[5];
    guardayck(x,y);
    itoa((int)Ngalletitas,cad,10);
     
    settextstyle(0,0,3);
    setcolor(COLOR(255,255,255));
	outtextxy(panX-200,60,"PUNTOS");
	settextstyle(0,0,2);
	outtextxy(panX-300,200,"Junta 600 puntos");
	outtextxy(panX-300,230,"para ganar!");
	
//	outtextxy(panX-300,260,"presiona g para guardar");
//	outtextxy(panX-300,290,"presiona r para cargar");
	
	settextstyle(0,0,2);
	outtextxy(panX-200,90,cad);
}

void mapear()
{
        
        
    //La impimimos
    setcolor(COLOR(0,51,255));
    for(int i=0;i<20;i++)
    {
        for(int j=0;j<20;j++)
	    {
            if(mapa[i][j]==1)
            {
              if(mapa[i][j-1]==0)line(j*25,i*25,j*25,(i+1)*25);
	          if(mapa[i][j+1]==0)line((j+1)*25,i*25,(j+1)*25,(i+1)*25);
	          if(mapa[i-1][j]==0)line(j*25,i*25,(j+1)*25,i*25);
	          if(mapa[i+1][j]==0)line(j*25,(i+1)*25,(j+1)*25,(i+1)*25);
            }  
	    }
	}
     
}


//borra un cuadro del juego
void borra(int xx,int yy)
{
     setfillstyle(SOLID_FILL,0);
     bar(pos[xx],pos[yy],pos[xx]+23,pos[yy]+23);
}



void galleta()
{
             
    setcolor(COLOR(211,211,40));
    
    
    for(int i=0;i<20;i++)
    {
        for(int j=0;j<20;j++)
	    {
            if(mapa[i][j]==1)circle((j*25)+11,(i*25)+11,2);                   
	    }
	}
	 
}

void guardayck(int i,int j)
{
      
      if(mem[i][j]==0)
      {
        Ngalletitas+=5;
        mem[i][j]=1;
      }
}

void fantasma()
{
    setfillstyle(SOLID_FILL,COLOR(230,230,230));
    bar(pos[xf]+10,pos[yf]+8,pos[xf]+20,pos[yf]+17);
	bar(pos[xf]+6,pos[yf]+15,pos[xf]+11,pos[yf]+20);
	bar(pos[xf]+13,pos[yf]+15,pos[xf]+16,pos[yf]+20);
	bar(pos[xf]+18,pos[yf]+15,pos[xf]+23,pos[yf]+20);
	setfillstyle(SOLID_FILL,BLACK);
	bar(pos[xf]+12,pos[yf]+11,pos[xf]+14,pos[yf]+14);
	bar(pos[xf]+16,pos[yf]+11,pos[xf]+18,pos[yf]+14);
}

void movfantasma(int a)
{
    if(a==0 && mov[yf-1][xf]==1 && (yf-1)!=-1)
    {
      yf++;
      fantasma();
      borra(xf,yf-1); 
    }
    else if(a==1 && mov[yf+1][xf]==1 && (yf+1)!=18)
    {
      yf--;
      fantasma();
      borra(xf,yf+1);   
    }
    else if(a==2 && mov[yf][xf-1]==1 && (xf-1)!=-1)
    {
      xf--;
      fantasma();
      borra(xf+1,yf);   
    }
    else if(a==3 && mov[yf][xf+1]==1 && (xf+1)!=18)     
    {
      xf++;
      fantasma();
      borra(xf-1,yf);     
    }
}
