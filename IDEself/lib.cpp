#include<stdio.h>
#include<windows.h>
typedef unsigned long long ull;
typedef unsigned int ui;
typedef unsigned short us;
typedef unsigned char uc;
typedef const char cc;
typedef long long ll;
int   unsign(char a){ return a<0?a+256:a; }
void  out1(FILE *O,uc a){		fprintf(O,"%+02X",a);	}
void  out2(FILE *O,us a){		fprintf(O,"%+04X",a);	}
void  out4(FILE *O,ui a){		fprintf(O,"%+08X",a);	}
void  out8(FILE *O,ull a){		fprintf(O,"%+016llX",a);	}
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
ui	 show4(FILE *F,FILE *O){unsigned c;	read4(F,&c);		out4(O,c);	return c;	}
bool cmp(cc a[],cc b[])	   {	for(int i=0;b[i];i++)	if(a[i]!=b[i])	return 0;	return 1;	}
void mktab(FILE *O,int tab){fprintf(O,"\n");for(int i=0;i<tab;i++){fprintf(O,"\t");}}
void detab(FILE *F,int tab){char c;	for(int i=0;i<=tab;i++)	{fscanf(F,"%c",&c);}	}
void show(FILE *F,int tab) {char c;	for(int i=0;i<tab;i++)	{fscanf(F,"%c",&c);printf("%c",c);}}
FILE *freset(FILE*F,FILE*C){	long long p;	fgetpos(F,&p);	fsetpos(C,&p);	fclose(F);	return C;}
ll  fofst(FILE *F,int i)  {	fpos_t T;	fgetpos(F,&T);	T+=i;	fsetpos(F,&T);	return T;}
void forctop(){int *p=0;p++;*p=1;}
void showh(FILE *F,FILE *O,int tab){uc c;	for(int i=0;i<tab;i++)	{fscanf(F,"%c",&c);fprintf(O,".%+02X",c);}}
uc h2c(char c)	{return	((c<'A')?(c-'0'):((c<'a')?(c-'A'+10):(c-'a'+10)));			}
ui tonum(char*c){return	h2c(c[0])*16*16*16+h2c(c[1])*16*16+h2c(c[2])*16+h2c(c[3]);	}
inline bool canprint(char c){return c>=32||c=='\n'||c=='\t';}
inline void getline(char *c,FILE *F=stdin){bool f=1;for(int i=0;;i++){do{fscanf(F,"%c",c+i);if(c[i]=='\n'&&f==1||feof(F)){c[i]=0;return;}if(c[i]!='\n')f=1;}while(!canprint(c[i])||(f==0&&c[i]=='\n'));}}
inline void outstr(char *c,FILE *O=stdout){for(int i=0;c[i];i++)	fprintf(O,"%c%+02x",c[i],c[i]);}
bool isfile(cc *__file){FILE *F=fopen(__file,"r");fclose(F);return F;}
void pr4(cc __file[256],ll pos,ui n){FILE *C=fopen(__file,"rb+");fofst(C,pos);writ4(C,&n);fclose(C);}
us	 pa2(cc __file[256],ll pos,us n){FILE *F=fopen(__file,"rb+"),*C=fopen(__file,"rb+");fofst(F,pos);fofst(C,pos);us tn;read2(F,&tn);tn+=n;writ2(C,&tn);fclose(F);fclose(C);return tn;}
ui	 pa4(cc __file[256],ll pos,ui n){FILE *F=fopen(__file,"rb+"),*C=fopen(__file,"rb+");fofst(F,pos);fofst(C,pos);ui tn;read4(F,&tn);tn+=n;writ4(C,&tn);fclose(F);fclose(C);return tn;}
void openflagsR(FILE *F,FILE*O){
	char buf[2];	fscanf(F,"%c%c",buf+0,buf+1);
	fprintf(O,"\n模块=   %d",(buf[0]&0X80)!=0);
	fprintf(O,"\n枚举抽象%d",(buf[0]&0X40)!=0);
	fprintf(O,"\n注解=   %d",(buf[0]&0X20)!=0);
	fprintf(O,"\n非用户= %d",(buf[0]&0X10)!=0);
	fprintf(O,"\nSTRICT= %d",(buf[0]&0X08)!=0);
	fprintf(O,"\n抽象=   %d",(buf[0]&0X04)!=0);
	fprintf(O,"\n接口=   %d",(buf[0]&0X02)!=0);
	fprintf(O,"\n本地=   %d",(buf[0]&0X01)!=0);
	fprintf(O,"\nTRANS=  %d",(buf[1]&0X80)!=0);
	fprintf(O,"\nVOLAT=  %d",(buf[1]&0X40)!=0);
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
void fswap(cc *__file,ll a,ll b,ll c){
	r:FILE *F=fopen(__file,"rb+");
	if(F==0){printf("fswapF");getchar();goto r;}
	char s[b-a+1]={},s1[c-b+1]={};
	fsetpos(F,&a);
	for(ll i=0;i<b-a;i++)	fscanf(F,"%c",s+i);
	for(ll i=0;i<c-b;i++)	fscanf(F,"%c",s1+i);
	fclose(F);
	r1:FILE *O=fopen(__file,"rb+");
	if(O==0){printf("fswapO");getchar();goto r1;}
	fsetpos(O,&a);char ch;
	for(ll i=0;i<c-b;i++)	fprintf(O,"%c",s1[i]);
	for(ll i=0;i<b-a;i++)	fprintf(O,"%c",s[i]);
	fclose(O);
}
void finst(cc *__file,ll a,cc *s,ll len){
	char buf;
	FILE *F=fopen(__file,"rb+"),*O=fopen(__file,"rb+");
	if(F==0)		printf("F");
	fsetpos(F,&a);	fsetpos(O,&a);
	for(ll i=0;i<len;i++){					fprintf(O,"%c",s[i]);
	if(i%0X100==0XFF)	O=freset(O,fopen(__file,"rb+"));
}	for(ll i=0;fscanf(F,"%c",&buf)>0;i++){	fprintf(O,"%c",buf);
	if(i%0X100==0XFF)	O=freset(O,fopen(__file,"rb+"));
}	fclose(F);		fclose(O);
}
void fdelt(cc *__file,cc *__tmpf,ll a,ll b){
	FILE *F=fopen(__file,"rb"),*O=fopen(__tmpf,"wb");	char c;
	for(ll i=0;fscanf(F,"%c",&c)>=0;i++){fprintf(O,"%c",c);
	if(i%0X100==0XFF)	O=freset(O,fopen(__tmpf,"rb+"));
}	freopen(__file,"wb",F);	freopen(__tmpf,"rb",O);
	for(ll i=0;fscanf(O,"%c",&c)>=0;i++){if(i<a||i>=b)	fprintf(F,"%c",c);
	if(i%0X100==0XFF)	F=freset(F,fopen(__file,"rb+"));
}	fclose(F);	fclose(O);
}
void frepc(cc *__file,cc *__tmpf,cc *fr,cc *to,ll fl,ll tl){
	FILE *F=fopen(__file,"rb");
	FILE *O=fopen(__tmpf,"wb");
	char c[fl+1]={};rest:
	for(int i=0;i<fl;i++)
	fscanf(F,"%c",c+i);
	while(!feof(F)){
		bool t=true;
		for(int i=0;i<fl;i++)
		if(c[i]!=fr[i])  t=0;
						if(t)
		for(int i=0;i<tl;i++)
		fprintf(O,"%c",to[i]);
		if(t)	goto rest;
		fprintf(O,"%c",c[0]);
		for(int i=1;i<fl;i++)
		c[i-1]=c[i];
		fscanf(F,"%c",c+fl-1);
	}	char s[512];
	fclose(F);	fclose(O);
	sprintf(s,"copy %s %s",__tmpf,__file);
	system(s);
}
int ffind(FILE *F,cc *s,ll l,int m=0){
	char c[l+1];
	if(m==0)
	while(!feof(F)){
		for(int i=1;i<l;i++)
		c[i-1]=c[i];
		fscanf(F,"%c",c+l-1);
		bool t=true;
		for(int i=0;i<l;i++)
		if(c[i]!=s[i])  t=0;
		if(t){fpos_t tp;	fofst(F,-l);
			fgetpos(F,&tp);	return tp;
		}
	}
	if(m==1)
	while(fofst(F,0)>0){
		fofst(F,-1);
		for(int i=1;i<l;i++)
		c[i]=c[i-1];
		fscanf(F,"%c",c);
		fofst(F,-1);
		bool t=true;
		for(int i=0;i<l;i++)
		if(c[i]!=s[i])  t=0;
		if(t){fpos_t tp;fgetpos(F,&tp);
			return tp;
		}
	}
	return -1;
}
