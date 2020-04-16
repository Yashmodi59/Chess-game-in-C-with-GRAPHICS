#include<conio.h>
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>
#include<dos.h>

int b[8][8]={{5,4,3,1,2,3,4,5},{6,6,6,6,6,6,6,6},{0},{0},{0},{0},{12,12,12,12,12,12,12,12},{11,10,9,7,8,9,10,11}};
void pb(char kp[][16],char n[][15]);
int validmove(int k,int pn,int r,int c,int nr,int nc,int pch[][2]);
int check(int k,int r,int c);
void swapb(int a[][8],int b[][8],char ckp[][16],char kp[][16],int cpch[][2],int pch[][2]);
int findking(int k,int *r,int *c);
void checkmate(int k,char n[][15]);
int convertp(int k);
void delay(int ms);
void loading(void);

void main()
{

int i,j,k,l,r,c,nr,nc,d,m,ch,chk,u,pn,gm=1,pch[2][2],cpch[2][2],mc=0,a[8][8];

char p[13]=" KQBHRPkqbhrp",n[2][15],kp[2][16]={"\0"},ckp[2][16]={"\0"};
clrscr();
loading();
pb(kp,n);
printf("#RULES:\n*Enter valid move.\nEnter row and column of the piece to be moved with its new row and new column.\n(Row_Column_Newrow_Newcolumn)\n*Enter r=0 to resign the match.\n*Game mode:PRO mode disables undo option while CASUAL mode allows undo option.\n");
printf("Enter players name:(player1-Black   player2-White)\n");
for(i=0;i<2;i++)
{
printf("Player name%d:",i+1);
scanf("%s",n[i]);
}
printf("Select game mode:\n1:CASUAL\n2:PRO\n");
scanf("%d",&gm);
swapb(a,b,ckp,kp,cpch,pch);
move:
mc++;
k=(mc%2!=0)?1:2;
again:
printf("%s:Enter your valid move.\n",n[k-1]);
scanf("%d %d %d %d",&r,&c,&nr,&nc);
if(r==0)
{
getch();
exit(0);
}
else if((k==1 && b[r-1][c-1]>6) || (k==2 && b[r-1][c-1]<7) || b[r-1][c-1]==0)
{
printf("Invalid piece!!\n");
goto again;
}
else
{
pn=b[r-1][c-1];
  if(pn==2)
  {
  pn=(nc==c || nr==r)?5:3;
  }
  else if(pn==8)
  {
  pn=(nc==c || nr==r)?11:9;
  }
}

 m=validmove(k,pn,r,c,nr,nc,pch);



  if((k==1 && pn==6 && r==7) || (k==2 && pn==12 && r==2))
  {
  b[r-1][c-1]=convertp(k);
  }
switch(m)
{
case 1:
d=b[nr-1][nc-1];
b[nr-1][nc-1]=b[r-1][c-1];
b[r-1][c-1]=d;
break;

case 2:
d=b[nr-1][nc-1];
b[nr-1][nc-1]=b[r-1][c-1];
b[r-1][c-1]=0;
i=(k==1)?1:0;
l=strlen(kp[i]);
kp[i][l]=p[d];
break;

case 3:
printf("Invalid move!!\n");
goto again;
}
if((pch[k-1][0]==0 || pch[k-1][1]==0) && (pn==1 || pn==7 || pn==5 || pn==11))
{
 if(c==7)
 {
 pch[k-1][1]=1;
 }
 else
 {
 pch[k-1][0]=1;
 }
}


  i=(k==1)?2:1;
  findking(i,&r,&c);
  if(check(i,r,c)==4)
  {
    if(chk==4)
    {
    printf("Invalid move since king remains on check!!\n");
    }
    else
    {
    printf("Invalid move since king comes on check!!\n");
    }
  swapb(b,a,kp,ckp,pch,cpch);
  goto again;
  }



pb(kp,n);

if(gm==1)
{
 printf("Press 0 to undo your move else press 1 to continue:\n");
 scanf("%d",&u);
 if(u==0)
 {
 swapb(b,a,kp,ckp,pch,cpch);
 printf(".....after undo:\n");
 pb(kp,n);
 goto again;
 }
}
findking(k,&r,&c);
chk=check(k,r,c);

 if(chk==4)
 {
 checkmate(k,n);
 textcolor(RED);
 cprintf("Check!!\n");
 }
 else
 {
 chk=0;
 }
swapb(a,b,ckp,kp,cpch,pch);
goto move;
}
void loading(void)
{
int i;
char bm[19]="Lets Play Chess!!!";
printf("\n\n\n\n\n\n\n\n\n\n\n");
textcolor(YELLOW);
cprintf("        Loading");
textbackground(RED);
for(i=0;i<50;i++)
{
//textbackground(i);
delay(1);
sound(100+i);
cprintf(" ");
}
nosound();
delay(10);
textbackground(BLACK);
textcolor(15);

for(i=5;i>=1;i--)
{
clrscr();
textcolor(i);
sound(250+i);
cprintf("\n\n\n\n\n\n\n\n\n\n\n                                       %d",i);
delay(10);
}
nosound();
clrscr();
printf("\n\n\n\n\n\n\n\n\n\n\n                                ");
for(i=0;i<18;i++)
{
textcolor(YELLOW);
cprintf("%c",bm[i]);
sound(150+i);
delay(5);
}
nosound();
delay(30);
textcolor(15);
clrscr();
return;
}


void delay(int s)
{
int ms=1*s;
clock_t start_time=clock();
while(clock()<start_time+ms);
return;
}


int convertp(int k)
{
 int ch,pn;
 printf("Choose a piece:\n1=Queen\n2=Bishop\n3=Knight\n4=Rook\n");
 scanf("%d",&ch);
 pn=(k==1)?ch+1:ch+7;
 return(pn);
}

void swapb(int a[][8],int b[][8],char ckp[][16],char kp[][16],int cpch[][2],int pch[][2])
{
int i,j;
for(i=0;i<8;i++)
{
 for(j=0;j<8;j++)
 {
  a[i][j]=b[i][j];
 }
}
for(i=0;i<2;i++)
{
strcpy(ckp[i],kp[i]);
}
for(i=0;i<2;i++)
{
 for(j=0;j<2;j++)
 {
 cpch[i][j]=pch[i][j];
 }
}

return;
}
void checkmate(int k,char n[][15])
{
int i,r,c,chk=0;
for(i=1;i<=8;i++)
{
findking(k,&r,&c);
 switch(i)
 {
    case 1:
    if(r==0)
    {
    goto skip;
    }
    else
    {
    c=c;
    r--;
    }
   break;

    case 2:
     if(r==0 || c==7)
     {
     goto skip;
     }
     else
     {
     r--;
     c++;
     }
   break;

   case 3:
    if(c==7)
    {
    goto skip;
    }
    else
    {
    r=r;
    c++;
    }
   break;

   case 4:
    if(c==7 || r==7)
    {
    goto skip;
    }
    else
    {
    r++;
    c++;
    }
   break;

   case 5:
    if(r==7)
    {
    goto skip;
    }
    else
    {
    r=r;
    c++;
    }
   break;

   case 6:
    if(r==7 || c==0)
    {
    goto skip;
    }
    else
    {
    r++;
    c--;
    }
   break;

   case 7:
    if(c==0)
    {
    goto skip;
    }
    else
    {
    r=r;
    c--;
    }
   break;

   case 8:
    if(r==0 || c==0)
    {
    goto skip;
    }
    else
    {
    r--;
    c--;
    }
 }
if(b[r-1][c-1]==0 || (k==1 && b[r-1][c-1]<7) || (k==2 && b[r-1][c-1]>6))
{
 chk=check(k,r,c);

 if(chk!=4)
  {
  break;
  }
}
skip:
}
 if(i==9)
 {
 textcolor(RED);
 cprintf("CHECKMATE!!!!!!\n");
 getch();
 clrscr();
 char wm[23];
 strcpy(wm,n[k-1]);
 strcat(wm," Wins!!");
 printf("\n\n\n\n\n\n\n\n\n\n\n                                   ");
 for(i=0;wm[i]!='\0';i++)
 {
 textcolor(YELLOW);
 cprintf("%c",wm[i]);
 delay(10);
 }
 getch();
 exit(0);
 }
return;
}
int findking(int k,int *r,int *c)
{
int i,j;
for(i=0;i<8;i++)
{
 for(j=0;j<8;j++)
  {
  if((k==1 && b[i][j]==7) || (k==2 && b[i][j]==1) )
   {
   goto end;
   }
  }
}
end:
*r=i;
*c=j;
}

int check(int k,int r,int c)
{

int i,j,ch,m;
//printf("r=%d \n c=%d b[%d][%d]=%d",r+1,c+1,r,c,b[r][c]);
for(ch=1;ch<=8;ch++)
{
  i=r;
  j=c;
  do
  {
   switch(ch)
   {
   case 1:
    if(r==0 || (i==0 && b[i][j]==0))
    {
    goto skip;
    }
    else
    {
    j=j;
    i--;
    }
   break;

    case 2:
     if(r==0 || c==7 || ((j==7 || i==0) && b[i][j]==0))
     {
     goto skip;
     }
     else
     {
     i--;
     j++;
     }
   break;

   case 3:
    if(c==7 || (j==7 && b[i][j]==0))
    {
    goto skip;
    }
    else
    {
    i=i;
    j++;
    }
   break;

   case 4:
    if(c==7 || r==7 || ((i==7 || j==7) && b[i][j]==0))
    {
    goto skip;
    }
    else
    {
    i++;
    j++;
    }
   break;

   case 5:
    if(r==7 || (i==7 && b[i][j]==0))
    {
    goto skip;
    }
    else
    {
    j=j;
    i++;
    }
   break;

   case 6:
    if(r==7 || c==0 || ((i==0 || j==7) && b[i][j]==0))
    {
    goto skip;
    }
    else
    {
    i++;
    j--;
    }
   break;

   case 7:
    if(c==0 || (j==0 && b[i][j]==0))
    {
    goto skip;
    }
    else
    {
    i=i;
    j--;
    }
   break;

   case 8:
    if(r==0 || c==0 || ((i==0 || j==0) && b[i][j]==0))
    {
    goto skip;
    }
    else
    {
    i--;
    j--;
    }
   }


    if(b[i][j]!=0 && (b[i][j]!=1 || b[i][j]!=7))
     {
       if((ch%2!=0) && ((k==1 && (b[i][j]==2 || b[i][j]==5)) || (k==2 && (b[i][j]==8 || b[i][j]==11))))
       {
       m=4;
       }
       else if((ch%2==0) && ((k==1 && (b[i][j]==2 || b[i][j]==3 || ( i==r-1 && b[i][j]==6))) || (k==2 && (b[i][j]==8 || b[i][j]==9 || (i==r+1  && b[i][j]==12)))))
       {
       m=4;
       }
     }


  }while(b[i][j]==0);

  skip:
}
   //knight
    if( k==1  && (((r!=0 && c!=0 && c!=1) && b[r-1][c-2]==4) || ((r!=7 && c!=0 && c!=1) && b[r+1][c-2]==4) || ((r!=7 && c!=7 && c!=6) && b[r+1][c+2]==4) || ((r!=0 && c!=7 && c!=6) && b[r-1][c+2]==4) ) )
    {
    m=4;
    }
    else if( k==2  && (((r!=0 && c!=0 && c!=1) && b[r-1][c-2]==10) || ((r!=7 && c!=0 && c!=1) && b[r+1][c-2]==10) || ((r!=7 && c!=7 && c!=6) && b[r+1][c+2]==10) || ((r!=0 && c!=7 && c!=6) && b[r-1][c+2]==10) ) )
    {
    m=4;
    }
if(m!=4)
{
m=5;
}

return(m);
}

void pb(char kp[][16],char n[][15])
{
int a=0,i,j;
char h=3,p[13]=" KQBHRPkqbhrp";
textcolor(RED);
cprintf("                    %c   ",h);
for(i=1;i<9;i++)
{
printf(" %d ",i);
}
textcolor(RED);
cprintf("   %c",h);
printf("\n                     -|--------------------------|- \n");
for(i=0;i<8;i++)
{
printf("                    %d ",i+1);
printf("| ");
 for(j=0;j<8;j++)
 {
 if(b[i][j]==0)
 {
 textcolor(0);
 }
 else if(b[i][j]>6)
 {
 textcolor(15);
 }
 else if(b[i][j]<7)
 {
 textcolor(0);
 }
 a++;
   if(a%2==0)
   {
    textbackground(6);
   }
   else
   {
   textbackground(4);
   }
 cprintf(" %c ",p[b[i][j]]);
 }
 textbackground(0);
 printf(" | ");
 a++;
 printf("%d\n",i+1);
}
printf("                     -|--------------------------|-\n");
textcolor(RED);
cprintf("                    %c   ",h);
for(i=1;i<9;i++)
{
printf(" %d ",i);
}
textcolor(RED);
cprintf("   %c\n",h);
printf("\n                    ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
 for(i=0;i<2;i++)
 {
  if(strlen(kp[i])==0)
  {
   continue;
  }
 printf("                    %s:%s\n",n[i],kp[i]);
 }
printf("                    ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
return;
}

int validmove(int k,int pn,int r,int c,int nr,int nc,int pch[][2])
{
int m,i,j;
switch(pn)
{
//pawn 1+2
case 6:
case 12:
 if(((r==2 && nr>r && nr<=4 && nc==c && b[r][c-1]==0) || (r==7 && nr<r && nr>=5 && nc==c && b[r-2][c-1]==0)) && b[nr-1][nc-1]==0)
  {
   m=1;
  }
 else if(((nr>r && nc==c && nr==r+1) || (nr<r && nc==c && nr==r-1)) && b[nr-1][nc-1]==0)
  {
   m=1;
  }
  else if(((nr==r+1 && (nc==c+1 || nc==c-1) && b[nr-1][nc-1]>6) || (nr==r-1 && (nc==c+1 || nc==c-1) && b[nr-1][nc-1]<7)) && b[nr-1][nc-1]!=0)
  {
   m=2;
  }
  else
  {
  m=3;
  }
 break;

		      //rook 1+2
case 5:
case 11:
  if(nc==c && nr!=r)
  {
   if(b[nr-1][nc-1]==0)
       {
       m=1;
       }
       else if( (k==1 && b[nr-1][nc-1]>6) || (k==2 && b[nr-1][nc-1]<7) )
       {
       m=2;
       }
       else
       {
       m=3;
       }

   i=r-1;
    while(i!=nr-1)
    {
     if(nr>r)
       {
       i++;
       }
       else
       {
       i--;
       }
       if(i==nr-1)
       {
       break;
       }

     if(b[i][c-1]!=0)
     {
       m=3;
       break;
     }
    }
  }
  else if(nr==r && nc!=c)
  {
  if(b[nr-1][nc-1]==0)
       {
       m=1;
       }
       else if( (k==1 && b[nr-1][nc-1]>6) || (k==2 && b[nr-1][nc-1]<7) )
       {
       m=2;
       }
       else
       {
       m=3;
       }


   i=c-1;
    while(i!=nc-1)
    {
      if(nc>c)
       {
       i++;
       }
       else
       {
       i--;
       }
       if(i==nc-1)
       {
       break;
       }

     if(b[r-1][i]!=0)
     {
     m=3;
     break;
     }

    }
  }
  else
  {
  m=3;
  }
break;
       //knight 1+2
case 4:
case 10:
 if(((nr==r+2 || nr==r-2) && (nc==c+1 || nc==c-1)) || ((nc==c+2 || nc==c-2) && (nr==r+1 || nr==r-1)))
 {
   if(b[nr-1][nc-1]==0)
   {
   m=1;
   }
   else if((k==1 && b[nr-1][nc-1]>6) || (k==2 && b[nr-1][nc-1]<7))
   {
   m=2;
   }
   else
   {
   m=3;
   }
 }
 else
 {
 m=3;
 }
break;
	       //king 1+2
case 1:
case 7:
if((nr==r+1 || nr==r-1 || nr==r) && (nc==c+1 || nc==c-1 || nc==c))
  {
   if(b[nr-1][nc-1]==0)
   {
   m=1;
   }
   else if((k==1 && b[nr-1][nc-1]>6) || (k==2 && b[nr-1][nc-1]<7))
   {
   m=2;
   }
   else
   {
   m=3;
   }
  }
 else if((pch[k-1][0]==0 && pch[k-1][1]==0) && (nc==1 || nc==5) && nr==r && ((b[nr-1][1]==0 && b[nr-1][2]==0) || (b[nr-1][4]==0 && b[nr-1][5]==0)) )
 {

  i=(k==1)?2:1;
  if(check(i,r-1,c-1)==4)
  {
  printf("Invalid castling move since king is on check!\n");
  m=3;
  }
  else if(check(i,r-1,2)==4 || check(i,r-1,4)==4)
  {
  printf("Invalid castling move since king moves through a square that is attacked by a piece of the opponent!!\n");
  m=3;
  }

  else
  {
   if(nc==1)
   {
   b[r-1][2]=b[r-1][0];
   b[r-1][0]=0;
   }
   else
   {
   b[r-1][4]=b[r-1][7];
   b[r-1][7]=0;
   }
   m=1;
  }
 }
 else
  {
  m=3;
  }
break;
	  //bishop 1+2
case 3:
case 9:
 if(nr!=r && nc!=c)
 {
  if(b[nr-1][nc-1]==0)
  {
  m=1;
  }
  else if((k==1 && b[nr-1][nc-1]>6) || (k==2 && b[nr-1][nc-1]<7))
  {
  m=2;
  }
  else
  {
  m=3;
  }

 i=r-1;
 j=c-1;
  while(i!=nr-1 && j!=nc-1)
  {
    if(nr>r && nc<c)
    {
    i++;
    j--;
    }
    else if(nr>r && nc>c)
    {
    i++;
    j++;
    }
    else if(nr<r && nc<c)
    {
    i--;
    j--;
    }
    else if(nr<r && nc>c)
    {
    i--;
    j++;
    }
    if(i==nr-1 && j==nc-1)
    {
    break;
    }

    if(b[i][j]!=0)
    {
    m=3;
    break;
    }

  }
 }
 else
 {
 m=3;
 }


}
return(m);
}
