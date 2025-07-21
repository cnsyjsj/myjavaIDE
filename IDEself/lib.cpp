#include<stdio.h>
#include<windows.h>
typedef unsigned long long ull;
typedef unsigned int ui;
typedef unsigned short us;
typedef unsigned char uc;
int   unsign(char a){ return a<0?a+256:a; }
void  out1(FILE *O,uc a){		fprintf(O,"%+02X",a);	}
void  out2(FILE *O,us a){	fprintf(O,"%+04X",a);	}
void  out4(FILE *O,ui a){			fprintf(O,"%+08X",a);	}
void  out8(FILE *O,fpos_t a){			fprintf(O,"%+016llX",a);	}
void read1(FILE *F,void *x){	fscanf(F,"%c",(char*)x);	}
void writ1(FILE *F,void *x){	fprintf(F,"%c",*((char*)x));}
void read2(FILE *F,void *x){	fscanf(F,"%c",(char*)x+1);		fscanf(F,"%c",(char*)x);	}
void writ2(FILE *F,void *x){	fprintf(F,"%c",*((char*)x+1));	fprintf(F,"%c",*((char*)x));}
void read4(FILE *F,void *x){	char *c=(char*)x;	fscanf(F,"%c",c+3);	fscanf(F,"%c",c+2);	fscanf(F,"%c",c+1);	fscanf(F,"%c",c);	}
void writ4(FILE *F,void *x){	char *c=(char*)x;	fprintf(F,"%c",*(c+3));	fprintf(F,"%c",*(c+2));	fprintf(F,"%c",*(c+1));	fprintf(F,"%c",*c);	}
void read8(FILE *F,void *x){	read4(F,x);	read4(F,(char*)x+4);}
void writ8(FILE *F,void *x){	writ4(F,x);	writ4(F,(char*)x+4);}
uc	 show1(FILE *F,FILE *O){	uc c;	fscanf(F,"%c",&c);	out1(O,c);	return c;	}
us	 show2(FILE *F,FILE *O){	us c;	read2(F,&c);		out2(O,c);	return c;	}
ui	 show4(FILE *F,FILE *O){unsigned c;	read4(F,&c);		out4(O,c);	return c;}
bool cmp(const char a[],const char b[]){	for(int i=0;b[i];i++)	if(a[i]!=b[i])	return false;	return true;	}
void mktab(FILE *O,int tab){fprintf(O,"\n");for(int i=0;i<tab;i++){fprintf(O,"\t");}}
void detab(FILE *F,int tab){char c;	for(int i=0;i<=tab;i++)	{fscanf(F,"%c",&c);}}
void show(FILE *F,int tab) {char c;	for(int i=0;i<=tab;i++)	{fscanf(F,"%c",&c);printf("%c",c);}}
FILE *freset(FILE*F,FILE*C){	long long p;	fgetpos(F,&p);	fsetpos(C,&p);	fclose(F);	return C;}
void fofst(FILE *F,int i)  {	fpos_t T;fgetpos(F,&T);	T+=i;fsetpos(F,&T);}
void forctop(){int *p=0;p++;*p=1;}
void openflagsR(FILE *F,FILE*O){
	char buf[2];	fscanf(F,"%c%c",buf+0,buf+1);//		ACC_
	fprintf(O,"\n模块=   %d",(buf[0]&0X80)!=0);//MOUDLE
	fprintf(O,"\n枚举抽象%d",(buf[0]&0X40)!=0);//ENUM 
	fprintf(O,"\n注解=   %d",(buf[0]&0X20)!=0);//ANNOTATION
	fprintf(O,"\n非用户= %d",(buf[0]&0X10)!=0);//SYNTHETIC
	fprintf(O,"\nSTRICT= %d",(buf[0]&0X08)!=0);
	fprintf(O,"\n抽象=   %d",(buf[0]&0X04)!=0);//ABSTRACT 接口/抽象 
	fprintf(O,"\n接口=   %d",(buf[0]&0X02)!=0);//INTERFACE
	fprintf(O,"\n本地=   %d",(buf[0]&0X01)!=0);
	fprintf(O,"\nTRANS=  %d",(buf[1]&0X80)!=0);//TRANSCIENT/VARAG
	fprintf(O,"\nVOLAT=  %d",(buf[1]&0X40)!=0);//VOLATILE
	fprintf(O,"\nSUP/SYN=%d",(buf[1]&0X20)!=0);
	fprintf(O,"\nFINAL=  %d",(buf[1]&0X10)!=0);
	fprintf(O,"\nSTATIC= %d",(buf[1]&0X08)!=0);
	fprintf(O,"\nPROTECT=%d",(buf[1]&0X04)!=0);
	fprintf(O,"\nPRIVATE=%d",(buf[1]&0X02)!=0);
	fprintf(O,"\nPUBLIC= %d",(buf[1]&0X01)!=0);
}
void openflagsW(FILE *F,FILE*O,int tab){
	int c=0,t;
	detab(F,tab);	fscanf(F,"模块=   %d",&t);c+=t*0x8000;
	detab(F,tab);	fscanf(F,"枚举抽象%d",&t);c+=t*0x4000;
	detab(F,tab);	fscanf(F,"注解=   %d",&t);c+=t*0x2000;
	detab(F,tab);	fscanf(F,"非用户= %d",&t);c+=t*0x1000;
	detab(F,tab);	fscanf(F,"STRICT= %d",&t);c+=t*0x0800;
	detab(F,tab);	fscanf(F,"抽象=   %d",&t);c+=t*0x0400;
	detab(F,tab);	fscanf(F,"接口=   %d",&t);c+=t*0x0200;
	detab(F,tab);	fscanf(F,"本地=   %d",&t);c+=t*0x0100;
	detab(F,tab);	fscanf(F,"TRANS=  %d",&t);c+=t*0x0080;
	detab(F,tab);	fscanf(F,"VOLAT=  %d",&t);c+=t*0x0040;
	detab(F,tab);	fscanf(F,"SUP/SYN=%d",&t);c+=t*0x0020;
	detab(F,tab);	fscanf(F,"FINAL=  %d",&t);c+=t*0x0010;
	detab(F,tab);	fscanf(F,"STATIC= %d",&t);c+=t*0x0008;
	detab(F,tab);	fscanf(F,"PROTECT=%d",&t);c+=t*0x0004;
	detab(F,tab);	fscanf(F,"PRIVATE=%d",&t);c+=t*0x0002;
	detab(F,tab);	fscanf(F,"PUBLIC= %d",&t);c+=t*0x0001;
	writ2(O,&c);
}
void fswap(const char *__file,long long a,long long b,long long c){
	r:FILE *F=fopen(__file,"rb+");
	if(F==0){printf("fswapF");getchar();goto r;}
	char s[b-a+1]={},s1[c-b+1]={};
	fsetpos(F,&a);
	for(int i=0;i<b-a;i++)	fscanf(F,"%c",s+i);
	for(int i=0;i<c-b;i++)	fscanf(F,"%c",s1+i);
	fclose(F);
	r1:FILE *O=fopen(__file,"rb+");
	if(O==0){printf("fswapO");getchar();goto r1;}
	fsetpos(O,&a);char ch;
	for(int i=0;i<c-b;i++)	fprintf(O,"%c",s1[i]);
	for(int i=0;i<b-a;i++)	fprintf(O,"%c",s[i]);
	fclose(O);
}
void finst(const char *__file,long long a,const char*s,long long len){
	char buf;
	FILE *F=fopen(__file,"rb+"),*O=fopen(__file,"rb+");
	if(F==0)		printf("F");
	fsetpos(F,&a);	fsetpos(O,&a);
	for(int i=0;i<len;i++){					fprintf(O,"%c",s[i]);
	if(i%0X100==0XFF)	O=freset(O,fopen(__file,"rb+"));
}	for(int i=0;fscanf(F,"%c",&buf)>0;i++){	fprintf(O,"%c",buf);
	if(i%0X100==0XFF)	O=freset(O,fopen(__file,"rb+"));
}	fclose(F);		fclose(O);
}
void fdelt(const char *__file,const char *__tmpf,long long a,long long b){
	FILE *F=fopen(__file,"rb"),*O=fopen(__tmpf,"wb");	char c;
	for(long long i=0;fscanf(F,"%c",&c)>=0;i++){fprintf(O,"%c",c);
	if(i%0X100==0XFF)	O=freset(O,fopen(__tmpf,"rb+"));
}	freopen(__file,"wb",F);	freopen(__tmpf,"rb",O);
	for(long long i=0;fscanf(O,"%c",&c)>=0;i++){if(i<a||i>=b)	fprintf(F,"%c",c);
	if(i%0X100==0XFF)	F=freset(F,fopen(__file,"rb+"));
}	fclose(F);	fclose(O);
}
ui tonum(char *c){
	return	((c[0]<'A')?(c[0]-'0'):((c[0]<'a')?(c[0]-'A'+10):(c[0]-'a'+10)))*16*16*16+
			((c[1]<'A')?(c[1]-'0'):((c[1]<'a')?(c[1]-'A'+10):(c[1]-'a'+10)))*16*16+
			((c[2]<'A')?(c[2]-'0'):((c[2]<'a')?(c[2]-'A'+10):(c[2]-'a'+10)))*16+
			((c[3]<'A')?(c[3]-'0'):((c[3]<'a')?(c[3]-'A'+10):(c[3]-'a'+10)));
}
