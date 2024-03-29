# include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <time.h> 
using namespace std;
struct menu{
	 int stt;
	 char ten[200];
	 int gia;
};
typedef struct menu m; 
typedef struct number{
	int num;
	int price;
} count;
void in(m a[]){
	printf("FOOD & DRINK:\n");
	for (int i = 0; i < 10; i++)
    printf("    %d. %s - %d vnd\n", a[i].stt, a[i].ten, a[i].gia); 
    printf("COMBO:\n");
    for(int i=10;i<=13;i++)
    printf("    %d. %s - %d vnd\n",a[i].stt, a[i].ten, a[i].gia);
}
void readmenu(m a[]){
	FILE *read;
	read=fopen("D:\\C&C++\\PBL\\menuvn.txt","r");
	if(read==NULL)  {
		printf("Can't open the file!");
		return;
	}
	 
	for(int i=0;i<14;i++){ 
		 fscanf(read, " %[^\n] %d",&a[i].ten,&a[i].gia); 
	} 
	fclose(read); 
} 
void cart(m a[],count b[]){
	int total =0;
	tt:
	while(1){
		 int x;
	        printf("Add number of food & drink or combo to cart 1-14 ( press 0 to end ):");
	        scanf("%d", &x);
		 if (x==0) break;
		 else if(x<=14) {
			int q; int s=0;
			printf("%.*s quantity:",18,a[x-1].ten);
			scanf("%d", &q);
			s += q*a[x-1].gia;
			total += s;
			printf("Price: %d vnd\n",s);
			b[x-1].num=b[x-1].num+q;
			b[x-1].price=b[x-1].price+s;
			}
		else printf("invalid number! Please re-enter!\n");
	} 
	while(1){
	printf("Do you want to order more? (yes:1  no:0):");
	int c;
    scanf("%d",&c);
	if(c == 1)
        {goto tt;} 
    else if(c == 0) { break;}
    else if(c != 1 || c != 0){ printf("ERROR\n"); continue;
	} 
  }
    while(1){
	printf("Do you want to confirm?(yes:1  no:0):");
	int c;
    scanf("%d",&c);
	if(c == 1)
        {printf("\n TOTAL: %d vnd\n",total);break;} 
    else if(c == 0) {printf(" Thank you for using our service <3\n"); break;}
    else if(c != 1 || c != 0){ printf("ERROR\n"); continue;
	} 
  }
}
void Bill(m a[],count b[]){
	FILE *f,*d;
	int r; 
	time_t now;  
    time(&now);     
	srand((int) now);    
	r=rand(); 
    struct tm *local = localtime(&now);
	d=fopen("D:\\C&C++\\PBL\\day.txt","r");
	int day;
	fscanf(d, "%d",&day);
	if(day==local->tm_mday)
	{ 
	f=fopen("D:\\C&C++\\PBL\\bill.txt","a");
    }
    else
	f=fopen("D:\\C&C++\\PBL\\bill.txt","w"); 
	if(f==NULL) {
		printf("Can't open the file!");
		return;
	}
	fclose(d); 
	d=fopen("D:\\C&C++\\PBL\\day.txt","w"); 
	fprintf(d,"%d",local->tm_mday);
	fclose(d); 
	fprintf(f,"Bill:\n"); 
    int total =0;
    fprintf(f,"Bill code:%d\n",r); 
    fprintf(f,"Date and time of the bill: %s\n", asctime(local));
	for(int i=0;i<14;i++)
		if(b[i].num!=0){
		 fprintf(f,"%d %.*s - %d vnd\n",b[i].num,18,a[i].ten,b[i].price);
		 total+= b[i].price;
		 } fprintf(f,"total: %d vnd\n", total);
		
    fclose(f);
    
}
 
int main() {
	
	m a[50]; 
	count foodcount[50];
	for(int n=0;n<14;n++) {
	foodcount[n].num=0;a[n].stt=n+1;  foodcount[n].price=0.0;}
	readmenu(a);
	in(a); 
	tt: 
	cart(a,foodcount);
	Bill(a,foodcount);
	 while (1) {
        printf("Would you like to create a new order? (yes:1 no:0) ");
        int n;
        scanf("%d", &n);
        if (n == 1)
            goto tt;
        else if (n == 0) {
            break;
        } else if (n != 1 || n != 0) {
            printf("ERROR\n");
            continue;
        }
    }
    return 0;
}

