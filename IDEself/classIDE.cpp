#include <windows.h>
#include<cstring>
#include"wsize.cpp"
#include <stdio.h>
#include"lib.cpp"
#include"me.cpp"
#include<map>
using namespace std;
char inpnam[256]="new.class",typnam[256]="class";
#define tnam "waste.txt"
//#define lockname "copy C:\\Users\\86139\\Desktop\\projects\\myIDE\\test\\out\\production\\test\\test.class input.class"
#define lockname "copy EXAMPLE\\prog prog.class"
//#define lockname "copy ..\\mods\\test\\net\\mcreator\\test\\TestMod.class input.class"
//#define lockname "copy ..\\mods\\test\\net\\mcreator\\test\\item\\SpawnerhandleItem.class input.class"
struct posln{
	fpos_t a=0;
	posln* n=0;
	int t;
};
map<int,fpos_t> copos;
map<int,posln*> cupos;
struct meth{
	fpos_t tpos[32]={};//ui len[32]={};
	map <int,fpos_t> prpos;//code poses
	map <int,posln*> vupos;//var user poses
	map <int,posln*> pupos;//cod user poses
	int is[32]={},ss[32]={},cnt[32]={};
	meth(){for(int i=0;i<32;i++)	ss[i]=cnt[i]=-1;}
} m[65536];
struct fiel{
	fpos_t tpos[8]={};
} fe[65536];
struct anno{
	int		typ,c,is,ss;
	map <int,fpos_t>pos;
} anos[65536];
struct bsm{
	int 		c,is,ss;
	map <int,fpos_t>pos;
} bsms[65536];
map<int,int> codln;
map<int,char[256]> codnm;
int fis[32]={},fss[32]={},fcnt[32]={};
us tn;		bool cchk=1,csug=1;
int showno=_flagw,tmpw;bool dbf=0,zab=0;//config
void readconst(fpos_t pos,char *buf){
	r:FILE *T=fopen(inpnam,"rb+");
	if(T==0){
		fprintf(stderr,"readconst");getchar();
		fclose(T);goto r;}
	fsetpos(T,&pos);
	char c;	fscanf(T,"%c",&c);
	if(c!=1){	buf[0]=0;fclose(T);	return;}
	us num;	read2(T,&num);
	for(int j=0;j<num&&j<256;j++){	fscanf(T,"%c",buf+j);buf[j+1]=0;}
	fclose(T);
}
void repc(posln *a,us b){
	r:FILE *F=fopen(inpnam,"rb+");
	if(F==0){fprintf(stderr,"repc");getchar();goto r;}
	for(;a;a=a->n){
		fsetpos(F,&(a->a));	if(a->t!=_short_class&&a->t!=_short_other)
		writ2(F,&b);	else	fprintf(F,"%c",(unsigned char)b);
	}	fclose(F);
}
void addc(int x,int k){
	for(int i=x;i<fcnt[_const_pool];i++)
		repc(cupos[i],i+1);
	copos[0]=copos[1]-2;
	fcnt[_const_pool]++;
	pa2(inpnam,copos[0],1);
	char s[16]={};	s[0]=k+1;
	char n[256]={2,0,4,4,8,8,2,2,4,4,4,4,0,0,3,2,0,3};
	finst(inpnam,copos[fss[_const_pool]],s,n[k]+1);
}
void delc(int x){
	for(int i=x+1;i<fcnt[_const_pool];i++)
		repc(cupos[i],i-1);
	copos[0]=copos[1]-2;
	fcnt[_const_pool]--;
	pa2(inpnam,copos[0],-1);
	fdelt(inpnam,tnam,copos[fss[_const_pool]],copos[fss[_const_pool]+1]);
}
unsigned short outv(FILE *F,FILE *O,int type,map<int,posln*> &h){
	fpos_t p;
	fgetpos(F,&p);
	unsigned short a=(type!=_short_other&&type!=_short_class)?show2(F,O):show1(F,O);
	posln *n=new posln;
	n->n=h[a];	h[a]=n;//bug
	n->a=p;		n->t=type;
	return a;
}
#define outc(F,O,t) (outv(F,O,t,cupos))
void printconst(FILE *F,FILE *O,us i,int m=1){
	if(m==2){	for(int i=1;i<fcnt[_const_pool];i++)
		{printf("\n%+04X",i);	printconst(F,O,i,1);}
		rewind(stdin);	getchar();	return;}
	if(i==0)	return;
	fpos_t C;	fgetpos(F,&C);	fsetpos(F,&(copos[i]));
	char c;fscanf(F,"%c",&c);
	switch (unsign(c)){	case 0X01:
			fprintf(O,"文本=\t字数=");
			unsigned j;	j=show2(F,O);	fprintf(O,"\t");
			for(int k=0;k<j;k++){fscanf(F,"%c",&c);
			if(k+32>=getweight()&&m==0)	continue;
				switch (c) {
				case '\\':	fprintf(O,"\\\\");break;
				case '\n':	fprintf(O,"\\n");break;
				case '\t':	fprintf(O,"\\t");break;
				case '\a':	fprintf(O,"\\a");break;
				case '\b':	fprintf(O,"\\b");break;
				case '\f':	fprintf(O,"\\f");break;
				case '\r':	fprintf(O,"\\r");break;
				case '\v':	fprintf(O,"\\v");break;
				case '\0':	fprintf(O,"\\0");break;
				default:
				if(c>=0X20&&c<=0X7F)	fprintf(O,"%c",c);
				else{	fprintf(O,"\\x");	out1(O,c);}
				break;	}
			}
			break;	case 0X03:
			int ti;		 read4(F,&ti);	fprintf(O,"整数=   %+08X\t=%d",ti,ti);
			break;	case 0X04:
			float tf;	 read4(F,&tf);	fprintf(O,"小数=   %f",tf);
			break;	case 0X05:
			long long tl;read8(F,&tl);	fprintf(O,"长数=   %+016llX=\t%lld",tl,tl);
			break;	case 0X06:
			double td;	 read8(F,&td);	fprintf(O,"长小=   %lf",td);
			break;	case 0X07:
			fprintf(O,"类=\t    #");	tn=outc(F,O,_class_name);
			if(m==1){fprintf(O,"\n");	printconst(F,O,tn,1);	fprintf(O,"\n");}
			break;	case 0X08:
			fprintf(O,"字串=\t    #");	tn=outc(F,O,_string_text);
			if(m==1){fprintf(O,"\n");	printconst(F,O,tn,1);	fprintf(O,"\n");}
			break;	case 0X09:
			fprintf(O,"字段\t类= #");	tn=outc(F,O,_class);
			if(m==1){fprintf(O,"\n");	printconst(F,O,tn,1);	fprintf(O,"\n");}
			fprintf(O,"\t定义=    #");	tn=outc(F,O,_info);
			if(m==1){fprintf(O,"\n");	printconst(F,O,tn,1);	fprintf(O,"\n");}
			break;	case 0X0A:
			fprintf(O,"方法\t类= #");	tn=outc(F,O,_class);
			if(m==1){fprintf(O,"\n");	printconst(F,O,tn,1);	fprintf(O,"\n");}
			fprintf(O,"\t定义=    #");	tn=outc(F,O,_info);
			if(m==1){fprintf(O,"\n");	printconst(F,O,tn,1);	fprintf(O,"\n");}
			break;	case 0X0B:
			fprintf(O,"接口\t类= #");	tn=outc(F,O,_class);
			if(m==1){fprintf(O,"\n");	printconst(F,O,tn,1);	fprintf(O,"\n");}
			fprintf(O,"\t定义=    #");	tn=outc(F,O,_info);
			if(m==1){fprintf(O,"\n");	printconst(F,O,tn,1);	fprintf(O,"\n");}
			break;	case 0X0C:
			fprintf(O,"定义\t名字#");	tn=outc(F,O,_info_name);
			if(m==1){fprintf(O,"\n");	printconst(F,O,tn,1);	fprintf(O,"\n");}
			fprintf(O,"\t类型=    #");	tn=outc(F,O,_info_type);
			if(m==1){fprintf(O,"\n");	printconst(F,O,tn,1);	fprintf(O,"\n");}
			break;	case 0X0F:
			fprintf(O,"句柄\t名字#");	tn=outc(F,O,_short_other);
			if(m==1){fprintf(O,"\n");	printconst(F,O,tn,1);	fprintf(O,"\n");}
			fprintf(O,"\t方法     #");	tn=outc(F,O,_method);
			if(m==1){fprintf(O,"\n");	printconst(F,O,tn,1);	fprintf(O,"\n");}
			break;	case 0X10:
			fprintf(O,"法类=\t   #");	tn=outc(F,O,_class_name);
			if(m==1){fprintf(O,"\n");	printconst(F,O,tn,1);	fprintf(O,"\n");}
			break;	case 0X12:
			fprintf(O,"INVD\t名字#");	tn=outc(F,O,_string_text);
			if(m==1){fprintf(O,"\n");	printconst(F,O,tn,1);	fprintf(O,"\n");}
			fprintf(O,"\t定义     #");	tn=outc(F,O,_info);
			if(m==1){fprintf(O,"\n");	printconst(F,O,tn,1);	fprintf(O,"\n");}
			break;	default:
			fprintf(O,"奇怪常量%X",unsign(c));
			break;
	}
	if(m>0)	fsetpos(F,&C);
}
us inpc(FILE *F,FILE *O,FILE *C,int type){
	system("cls");	int conti=0;us c=0;
	if(type!=_short_class)	read2(F,&c);
	else	fscanf(F,"%c",&c);
	printconst(F,O,c,1);
	fprintf(O,"\nchange?[Y/ ]");
	char tc=getchar();	if(tc!='Y'&&tc!='y')	return c;
	key(VK_RETURN);	int a[65536]={},p=0;
	for(int i=0;i<65536;i++)	for(posln *j=cupos[i];j;j=j->n)
	if(j->t==type||type==_allc){a[p++]=i;break;}//bug
	while(1){	system("cls");		int k;
		fprintf(O,"候选V 直接输入->\n");
		for(int i=conti;i<conti+getheight()-2&&i<p;i++)
		{if(getmousey()-1==i-conti)	fprintf(O,"->");	fprintf(O,"#%+04X\n",a[i]);}
		if(key(VK_UP)&&conti>0)		conti--;
		if(key(VK_DOWN)&&conti<p)	conti++;
		if(keydn(VK_LBUTTON)||keydn(VK_RETURN)){
			if(key(VK_LBUTTON))	k=getmousey();
			if(key(VK_RETURN))	k=1;
			if(k+conti>p)		return c;
			if(k+conti>0)		{writ2(C,a+conti+k-1);return a[conti+k-1];}
			if(k+conti==0){inpn:
				out2(O,c);	fprintf(O,"->");	scanf("%X",&c);
				rewind(stdin);	key(VK_RETURN);
				if(type!=_short_class)	writ2(C,&c);
				else	fprintf(C,"%c",c);	return c;}
		}
		if(key(VK_SHIFT))	goto inpn;
		if(key(VK_ESCAPE)||key(VK_RBUTTON))	return c;
	}
}
bool chkc(int p,uc t){
	r:FILE *T=fopen(inpnam,"rb+");
	if(T==0){fprintf(stderr,"chkc");getchar();goto r;}
	fsetpos(T,&(copos[p]));//bug
	uc c=0;	fscanf(T,"%c",&c);
	fclose(T);	return c==t||p==0;
}
void chkl(FILE *F,ui l,int t,int i){
		if(cchk&&fofst(F,0)-m[i].tpos[t]-4!=l)
		pr4(inpnam,m[i].tpos[t],fofst(F,0)-m[i].tpos[t]-4);
}
us fndc(const char c[256]){
	int ti=0;char b[256];
	for(int i=1;i<fcnt[_const_pool];i++)
	if(chkc(i,1)){
		readconst(copos[i],b);
		if(cmp(b,c))
		{ti=i;break;}
	}if(ti==0){
		ti=fcnt[_const_pool]++;
		b[0]=1;
		for(int i=0;c[i];i++)
		{b[i+3]=c[i];b[1]=i&0XFF00;b[2]=i&0X00FF;}
		finst(inpnam,copos[ti],b,b[1]+3);
	}	return ti;
}
void delall(int x=0){
	for(int i=1;i<fcnt[_const_pool];i++){
	for(;cupos[i];cupos[i]=cupos[i]->n)
	delete cupos[i];	copos[i]=-1;}//bug
	for(int i=0;i<fcnt[_methods];i++)	for(int j=0;j<32;j++)
			m[i].tpos[j]=m[i].cnt[j]=fe[i].tpos[j]=-1;
	for(int i=0;i<32;i++)	fcnt[i]=0;
	if(x==0)	return;
	for(int i=0;i<32;i++)
	{fss[i]=-1;fis[i]=0;}
}
//=============================================
us temp;ui temp4;
#define errcall getchar();goto file_end;
int main(int argc,char **argv){
	system(lockname);
	delall(1);
	while(1)	if(issel(hwnd)){
		file_start:	char c[1024];
		FILE *G=fopen("conf.txt","rb");if(G){
		fscanf(G,"%d%d%d",&cchk,&csug,&showno,c);
		getline(c,G);	getline(typnam,G);	getline(inpnam,G);
		}	fclose(G);	system("cls");
		if(keydn(VK_CONTROL)&&key('O')){
			opfi:printf("文件名");	getline(inpnam);}
		if(keydn(VK_CONTROL)&&key('N')){
			system("DIR EXAMPLE");
			printf("以上是可用类型,输入\n类型\n名称");
			getline(typnam);	getline(inpnam);
			sprintf(c,"copy EXAMPLE\\%s \"%s\"",typnam,inpnam);	system(c);}
		if(keydn(VK_CONTROL)&&key('R')){
			char n[256];	getline(n);
			sprintf(c,"EXAMPLE\\%s,exe");if(isfile(c))
			sprintf(c,"EXAMPLE\\%s.exe 1 %s %s",typnam,inpnam,n);else
			sprintf(c,"EXAMPLE\\prog.exe 1 %s %s",inpnam,n);	system(c);
			getchar();}
		if(keydn(VK_CONTROL)&&key('A')){
			sprintf(c,"EXAMPLE\\%s,exe");if(isfile(c))
			sprintf(c,"EXAMPLE\\%s.exe 0 \"%s\"",typnam,inpnam);else
			sprintf(c,"EXAMPLE\\prog.exe 0 \"%s\"",inpnam);	system(c);
			getchar();}
		FILE *Z;
		FILE *F=fopen(inpnam,"rb+"), *O;
		FILE *W=fopen("waste.txt","wb");
		if(F==0){printf("没有文件");
		fclose(F);fclose(W);goto file_start;}
		delall(0);	rewind(stdin);
//		showno=_codew;zab=1;fis[_methods]=1; 
		//infos
		O=(showno==_flagw)?stdout:W;
		temp4=show4(F,W);
		if(temp4!=0XCAFEBABE){printf("not a file%X",temp4);getchar();}
		fprintf(O,"ver:");show4(F,O);
	#define O_EXMP_myIDE
		{FILE *T=fopen("bytecode_extension.txt","rb");
		O=(showno==_exmpw)?stdout:W;
		fprintf(O,"查找\n");
		for(int i=0;!feof(T);i++){
			codln[i]=1;	fscanf(T,"%d ",&codln[i]);
			O=(showno==_exmpw&&i>=m[fis[_methods]].is[_exmpw]&&i<m[fis[_methods]].is[_exmpw]-2+getheight())?stdout:W;
			fprintf(O,"%+02X",i);	getline(codnm[i],T);fprintf(O,"%s\n",codnm[i]);
		}fclose(T);
		}fgetpos(F,&copos[fcnt[_const_pool]+_file_atri]);
		//infos
	#define O_CONST_myIDE
		//const
		rewind(W);
		O=(showno==_consw)?stdout:W;
		read2(F,&fcnt[_const_pool]);
		fprintf(O,"const:");out2(O,fis[_const_pool]);
		fprintf(O,"/");		out2(O,fss[_const_pool]);
		fprintf(O,"/");		out2(O,fcnt[_const_pool]);
		for(int i=1;i<fcnt[_const_pool];i++){
			O=(i-1<fis[_const_pool]+getheight()-2
			&&i-1>=fis[_const_pool]&&showno==_consw)
			?stdout:W;
			fprintf(O,"\n");
			if(i==fss[_const_pool])	fprintf(O,"[");
			if(i-fis[_const_pool]==getmousey())	fprintf(O,"-");
			out2(O,i);
			fprintf(O,"\t");
			fgetpos(F,&(copos[i]));
			printconst(F,O,i,0);
		}
		//const
	#define O_FLAG_myIDE
		//flag
		rewind(W);
		fgetpos(F,&(copos[fcnt[_const_pool]]));
		O=(showno==_flagw&&!zab)?stdout:W;
		openflagsR(F,O);
		fprintf(O,"\n我叫:   #");	outc(F,O,_class);
		fprintf(O,"\n爹是:   #");	outc(F,O,_class);
		//flag
		
		//debug
		O=(showno==_confw?stdout:W);
		fprintf(O,"常量检查=%d\n",cchk);
		fprintf(O,"常量建议=%d\n",csug);
		fprintf(O,"帮助\n");
		//debug
	#define O_INTF_myIDE
		//interface
		rewind(W);
		fgetpos(F,&(copos[fcnt[_const_pool]+_interfaces]));
		O=(showno==_intfw)?stdout:W;
		fprintf(O,"接口:");
		us intercnt=show2(F,O);
		//interface
		
		//field
		rewind(W);
		fgetpos(F,&(copos[fcnt[_const_pool]+_fields]));
		O=(showno==_fielw)?stdout:W;
		fprintf(O,"字段:");			out2(O,fis[_fields]);
		fprintf(O,"/");	us fieldcnt=show2(F,O);
		for(int i=0;i<fieldcnt;i++){
			fgetpos(F,&(fe[i].tpos[_fielp]));
			O=(showno==_fielw&&fis[_fields]==i)?stdout:W;
			openflagsR(F,O);
			fprintf(O,"\n名字:");outc(F,O,_field_name);
			fprintf(O,"\n类型:");outc(F,O,_field_type);
			fprintf(O,"\n附加:");us temp=show2(F,O);
			char buf[256];
			for(int j=0;j<temp;j++){
				readconst(copos[outc(F,W,_atri_type)],buf);
				if(cmp(buf,"ConstantValue")){
					fgetpos(F,&fe[i].tpos[_consp]);
					show4(F,W);
					mktab(O,1);	fprintf(O,"是常量:");outc(F,O,_allc);
				}
			}
		}
		//field
	#define O_METHOD_myIDE
		//method
		fgetpos(F,&(copos[fcnt[_const_pool]+_methods]));
		O=(showno==_methw)?stdout:W;
		fprintf(O,"方法:");			out2(O,fis[_methods]);
		fprintf(O,"/");				fcnt[_methods]=show2(F,O);
		for(int i=0;i<fcnt[_methods];i++){
			rewind(W);	for(int j=0;j<8;j++)
			{m[i].cnt[j]=-1;m[i].tpos[j]=-1;}
			O=(showno==_methw&&fis[_methods]==i&&!zab)?stdout:W;
			fgetpos(F,&(m[i].tpos[_methp]));
			openflagsR(F,O);
			fprintf(O,"\n名字:\t#");	outc(F,O,_method_name);
			fprintf(O,"\n类型:\t#");	outc(F,O,_method_type);
			us atrc;			atrc=	show2(F,W); 
			for(int j=0;j<atrc;j++){
				int typ=outc(F,W,_atri_type);
				char s[256]={};readconst(copos[typ],s);
				if(cmp(s,"Code")){
					fgetpos(F,&(m[i].tpos[_codep]));
					ui tlen=show4(F,W);
					O=(showno==_codew&&fis[_methods]==i)?stdout:W;
					fprintf(O,"栈大小=");	show2(F,O);
					fprintf(O,"\t变量数=");	show2(F,O);
					fprintf(O,"\t长度=");
					unsigned len;		len=show4(F,O);
					rewind(W);
					fprintf(O,"\n");
					O=W;	m[i].cnt[_codep]=0;
					for(int j=0;j<len;){
						fgetpos(F,&(m[i].prpos[m[i].cnt[_codep]]));
						int ct=unsign(show1(F,O));
						fprintf(O,"%.9s",codnm[ct]);
						j+=codln[ct];m[i].cnt[_codep]++;
						for(int i=0;codnm[ct][i];i++){
							if(codnm[ct][i]=='<'&&codnm[ct][i+4]=='>')
							switch (codnm[ct][i+1]){
										case '+':
									if(codnm[ct][i+2]=='1')	show1(F,O);
									if(codnm[ct][i+2]=='2')	show2(F,O);
								break;	case '#':
									if(codnm[ct][i+2]=='s')
									outc(F,O,_short_other);
									if(codnm[ct][i+2]=='l')
									switch(codnm[ct][i+3]){
										case 's':	fprintf(O,"#");	outc(F,O,_ls);		break;
										case 'l':	fprintf(O,"#");	outc(F,O,_ll);		break;
										case 'n':	fprintf(O,"#");	outc(F,O,_info);	break;
										case 'c':	fprintf(O,"#");	outc(F,O,_class);	break;
									}
								break;	case '$':
									if(codnm[ct][i+2]=='v')
									outv(F,O,0,m[i].vupos);
									if(codnm[ct][i+2]=='v')
									outv(F,O,_short_other,m[i].vupos);	
								break;
							}
						}fprintf(O,"\n");
					}fgetpos(F,&(m[i].prpos[m[i].cnt[_codep]]));
					freopen("waste.txt","rb+",W);
					for(int j=0;j<m[i].cnt[_codep];j++){
						char c=0;
						if(showno==_codew&&fis[_methods]==i&&j>=m[i].is[_codew]&&j<m[i].is[_codew]+getheight()-2){
						if(j==m[i].ss[_codew])	printf("[");
						if(j==m[i].is[_codew]+getmousey()-1)	printf("-");}
						for(;c!='\n';){
							fscanf(W,"%c",&c);
							if(showno==_codew&&fis[_methods]==i&&j>=m[i].is[_codew]&&j<m[i].is[_codew]+getheight()-2)
							printf("%c",c);
						}
					}
					freopen("waste.txt","wb",W);
					O=(showno==_codew&&fis[_methods]==i)?stdout:W;
					fprintf(O,"程序%+08X/%+08X/%+08X",m[i].is[_codew],m[i].cnt[_codep],m[i].ss[_codew]);
					O=(showno==_trysw&&fis[_methods]==i)?stdout:W;
					fgetpos(F,&(m[i].tpos[_trysp]));
					fprintf(O,"错误表%+04X/",m[i].is[_trysw]);	m[i].cnt[_trysp]=show2(F,O);
					for(int j=0;j<m[i].cnt[_trysp];j++){
						O=(showno==_trysw&&fis[_methods]==i&&j>=m[i].is[_trysw]&&j<m[i].is[_trysw]+getheight())?stdout:W;
						fprintf(O,"\n从  ={\t");	show2(F,O);
						fprintf(O,"\t到  ={\t");	show2(F,O);
						fprintf(O,"\t处理={\t");	show2(F,O);
						fprintf(O,"\t类别=#\t");	outc(F,O,_allc);
					}
		#define O_ATRI_myIDE
					unsigned short atril;
					read2(F,&atril);
					for(int j=0;j<atril;j++){
						typ=outc(F,W,_atri_type);
						readconst(copos[typ],s);
								if(cmp(s,"LineNumberTable")){
							O=(showno==_linsw&&fis[_methods]==i)?stdout:W;
							fgetpos(F,&(m[i].tpos[_linsp]));ui tlen=show4(F,W);
							fprintf(O,"行数表%+04X/%+04X/",m[i].is[_linsw],m[i].ss[_linsw]);	m[i].cnt[_linsp]=show2(F,O);
							for(int k=0;k<m[i].cnt[_linsp];k++){
								O=(showno==_linsw&&fis[_methods]==i&&k>=m[i].is[_linsw]&&k<m[i].is[_linsw]+getheight())?stdout:W;
								fprintf(O,"\n");
								if(k==m[i].ss[_linsw])	fprintf(O,"[");
								if(k==getmousey()+m[i].is[_linsw]-1)	fprintf(O,"-");
								show2(F,O);	fprintf(O,"行-\t");	show2(F,O);	fprintf(O,"行");
							}	chkl(F,tlen,_linsp,i);
						}else	if(cmp(s,"LocalVariableTable")){
							O=(showno==_variw&&fis[_methods]==i&&!zab)?stdout:W;
							fgetpos(F,&(m[i].tpos[_varip]));ui tlen=show4(F,W);
							fprintf(O,"变量表:%+04X/%+04X/",m[i].is[_variw],m[i].ss[_variw]);	m[i].cnt[_varip]=show2(F,O);
							for(int k=0;k<m[i].cnt[_varip];k++){
								O=(showno==_variw&&fis[_methods]==i&&k>=m[i].is[_variw]&&k<m[i].is[_variw]+getheight()&&!zab)?stdout:W;
								fprintf(O,"\n");
								if(k==m[i].ss[_variw])	fprintf(O,"[");
								if(k==getmousey()+m[i].is[_variw]-1)	fprintf(O,"-");
								fprintf(O,"定义位置={");	show2(F,O);
								fprintf(O,"\t可用长度={");	show2(F,O);
								fprintf(O,"\t名字=#");		outc(F,O,_string_text);
								fprintf(O,"\t类型=#");		outc(F,O,_field_type);
								fprintf(O,"\t槽位=[");		outv(F,O,0,m[i].vupos);
							}
							chkl(F,tlen,_varip,i);
							fprintf(O,"\n%X",getmousey()+m[i].is[_variw]-1);
						}else	if(cmp(s,"LocalVariableTypeTable")){
							O=(showno==_variw&&fis[_methods]==i&&zab)?stdout:W;
							fgetpos(F,&(m[i].tpos[_vartp]));ui tlen=show4(F,W);
							fprintf(O,"扩展变量表:%+04X/%+04X/",m[i].is[_variw],m[i].ss[_variw]);	m[i].cnt[_vartp]=show2(F,O);
							for(int k=0;k<m[i].cnt[_vartp];k++){
								O=(showno==_variw&&fis[_methods]==i&&k>=m[i].is[_variw]&&k<m[i].is[_variw]+getheight()&&zab)?stdout:W;
								fprintf(O,"\n");
								if(k==m[i].ss[_variw])	fprintf(O,"[");
								if(k==getmousey()+m[i].is[_variw]-1)	fprintf(O,"-");
								fprintf(O,"定义位置={");	show2(F,O);
								fprintf(O,"\t可用长度={");	show2(F,O);
								fprintf(O,"\t名字=#");		outc(F,O,_string_text);
								fprintf(O,"\t类型=#");		outc(F,O,_field_type);
								fprintf(O,"\t槽位=[");		outv(F,O,0,m[i].vupos);
							}
							chkl(F,tlen,_vartp,i);
							fprintf(O,"\n%X",getmousey()+m[i].is[_variw]-1);
						}else	if(cmp(s,"StackMapTable")){
							O=(showno==_methw&&fis[_methods]==i&&!zab)?stdout:W;
							fgetpos(F,&(m[i].tpos[_smttp]));ui tlen=show4(F,W);
							showh(F,O,m[i].cnt[_smttp]=show2(F,O));
							chkl(F,tlen,_smttp,i);
						}		else{
							O=stderr;
							printf("\n:%d %d??? %s\n",i,j,s);
							fpos_t tpos;
							fgetpos(F,&tpos);
							printf("@%llX:\n",tpos);
							errcall
						}
					}
					chkl(F,tlen,_codep,i);
				}else if(cmp(s,"Signature")){
					O=(showno==_methw&&fis[_methods]==i&&!zab)?stdout:W;
					fgetpos(F,&(m[i].tpos[_signp]));
					show4(F,W);fprintf(O,"\n签名:");
					outc(F,O,_string_text);
				}else{	printf("\n:%d??%X %s\n",i,typ,s);fpos_t tpos;
				fgetpos(F,&tpos);printf("@%llX:\n",tpos);errcall}
			}
			fgetpos(F,&(m[i].tpos[_endmp]));
			O=(showno==_methw&&fis[_methods]==i&&zab)?stdout:W;		fprintf(O,"\n");
			if(m[i].tpos[_codep]>0)	fprintf(O,"代码");		fprintf(O,"\n");
			if(m[i].tpos[_trysp]>0)	fprintf(O,"测试表");	fprintf(O,"\n");
			if(m[i].tpos[_linsp]>0)	fprintf(O,"行数表");	fprintf(O,"\n");
			if(m[i].tpos[_linsp]<=0&&showno==_linsw)	printf("行数表");	fprintf(O,"\n");
			if(m[i].tpos[_varip]>0)	fprintf(O,"变量表");	fprintf(O,"\n");
			if(m[i].tpos[_varip]<=0&&showno==_variw)	printf("变量表");	fprintf(O,"\n");
			if(m[i].tpos[_smttp]>0)	fprintf(O,"栈表");		fprintf(O,"\n");
			if(m[i].tpos[_signp]>0)	fprintf(O,"签名");		fprintf(O,"\n");
		}
		//method
	#define O_FATRI_myIDE
		//info
		temp=show2(F,W);
		for(;temp;temp--){
			char s[256];	int t;
			O=(showno==_flagw&&!zab)?stdout:W;
			readconst(copos[t=outc(F,W,_atri_type)],s);
			if(cmp(s,"SourceFile")){
				fgetpos(F,&copos[fcnt[_const_pool]+_source]);
				show4(F,W);	fprintf(O,"\n源文件  #");	outc(F,O,_string_text);
			}else if(cmp(s,"InnerClass")){
				fgetpos(F,&copos[fcnt[_const_pool]+_inclp]);
				show4(F,W);	fprintf(O,"\n内部类");	O=(showno==_inclw?stdout:W);
				fprintf(O,"INC:%+04X",fis[_inclp]);	fcnt[_inclp]=show2(F,O);
				for(int k=0;k<fcnt[_inclp];k++){
					O=(showno==_inclw&&k==fis[_inclp])?stdout:W;
					fprintf(O,"\n内类=#");	outc(F,O,_class);
					fprintf(O,"\n外类=#");	outc(F,O,_class);
					fprintf(O,"\n类名=#");	outc(F,O,_string_text);
					openflagsR(F,O);
				}
			}else if(cmp(s,"RuntimeVisibleAnnotations")){
				fgetpos(F,&copos[fcnt[_const_pool]+_rvanp]);
				show4(F,W);	fprintf(O,"\n元素");	O=(showno==_rvanw&&!zab?stdout:W);
				fprintf(O,"RVA:%+04X/%+04X/",fis[_rvanp],fss[_rvanp]);	fcnt[_rvanp]=show2(F,O);
				for(int i=0;i<fcnt[_rvanp];i++){
					O=(showno==_rvanw&&!zab&&i>=fis[_rvanp]&&i<fis[_rvanp]+getheight()&&!zab)?stdout:W;
					fprintf(O,"\n");
					if(i==getmousey()+fis[_rvanp]-1)	fprintf(O,"-");
					if(i==fss[_rvanp])					fprintf(O,"[");
					fprintf(O,"注解=#");	outc(F,O,_field_type);
					O=(showno==_rvanw&&zab&&i==max(fis[_rvanp],fss[_rvanp]))?stdout:W;
					fprintf(O,"ANO:%+04X/",anos[i].is);	anos[i].c=show2(F,O);
					for(int k=0;k<anos[i].c;k++){
						fgetpos(F,&anos[i].pos[k]);
						O=(showno==_rvanw&&zab&&k>=anos[i].is&&k<anos[i].is+getheight()&&i==max(fis[_rvanp],fss[_rvanp]))?stdout:W;
						fprintf(O,"\n");
						if(k==getmousey()+anos[i].is-1)	fprintf(O,"-");
						fprintf(O,"名字=#");	outc(F,O,_string_text);
						fprintf(O,"\t类型=");	char c;
						fscanf(F,"%c",&c);fprintf(O,"%c",c);
						fprintf(O,"\t值:");
						switch (c) {
							case'B':case'C':case'I':case'S':
							case'Z':   outc(F,O,_int);break;
							case'F': outc(F,O,_float);break;
							case'D':outc(F,O,_double);break;
							case's':printconst(F,O,outc(F,O,_string_text));break;
						}
					}fgetpos(F,&anos[i].pos[anos[i].c]);
				}fgetpos(F,&anos[fcnt[_rvanp]].pos[0]);anos[fcnt[_rvanp]].pos[0]+=4;
			}else if(cmp(s,"BootstrapMethods")){
				fgetpos(F,&copos[fcnt[_const_pool]+_bootp]);
				show4(F,W);	fprintf(O,"\n启动项");	O=(showno==_bootw&&!zab?stdout:W);
				fprintf(O,"BSM:%+04X/",fis[_bootp]);	fcnt[_bootp]=show2(F,O);
				for(int i=0;i<fcnt[_bootp];i++){
					O=(showno==_bootw&&!zab&&i>=fis[_bootp]&&i<fis[_bootp]+getheight()&&!zab)?stdout:W;
					fprintf(O,"\n");
					if(i==getmousey()+fis[_bootp]-1)	fprintf(O,"-");
					if(i==fss[_bootp])	fprintf(O,"[");
					fprintf(O,"类型=#");	outc(F,O,_meth_hand);
					O=(showno==_bootw&&zab&&i==max(fis[_bootp],fss[_bootp]))?stdout:W;
					fprintf(O,"ARG:%+04X/",fis[_bootp]);	bsms[i].c=show2(F,O);
					for(int k=0;k<bsms[i].c;k++){
						fgetpos(F,&bsms[i].pos[k]);
						O=(showno==_bootw&&zab&&k>=bsms[i].is&&k<bsms[i].is+getheight()&&i==max(fis[_bootp],fss[_bootp]))?stdout:W;
						fprintf(O,"\n");
						if(k==getmousey()+bsms[i].is-1)	fprintf(O,"-");
						fprintf(O,"\t值:");outc(F,O,_string_text);
					}
				}
			}else{
				printf("\n%+04X???%s@%+08llX",t,s,fofst(F,0));
				errcall
			}
		}
		O=(showno==_flagw&&zab)?stdout:W;		fprintf(O,"\n");
		if(copos[fcnt[_const_pool]+_source]>0)	fprintf(O,"源文件");	fprintf(O,"\n");
		if(copos[fcnt[_const_pool]+_inclp]>0)	fprintf(O,"内部类");	fprintf(O,"\n");
		if(copos[fcnt[_const_pool]+_rvanp]>0)	fprintf(O,"注解");		fprintf(O,"\n");
		if(copos[fcnt[_const_pool]+_bootp]>0)	fprintf(O,"启动项");	fprintf(O,"\n");
		fgetpos(F,&(copos[fcnt[_const_pool]+_filend]));
		
		if(fscanf(F,"%c",&c)<=0)
		fprintf(O,"\n未完待续");
		while(!feof(F)){
			fscanf(F,"%c",c);	out1(O,*c);
			fpos_t tpos=fofst(F,0);
			fprintf(O,"---%p\n",tpos);
		}
		//info
/*=============
=============*/
//		rend:key(VK_RETURN);
/*=============		
=============*/
		O=stdout;
	#define I_CONST_myIDE
		if(showno==_consw){
		stdlop(fss[_const_pool],fis[_const_pool],fcnt[_const_pool],_consw);
			  if(fss[_const_pool]>0&&fss[_const_pool]>1&&key(VK_UP)){
			repc(cupos[fss[_const_pool]-1],fss[_const_pool]);
			repc(cupos[fss[_const_pool]],fss[_const_pool]-1);
			fswap(inpnam,copos[fss[_const_pool]-1],copos[fss[_const_pool]],copos[fss[_const_pool]+1]);
			fss[_const_pool]--;	if(fis[_const_pool]>0)	fis[_const_pool]--;
		}else if(fss[_const_pool]>0&&fss[_const_pool]<fcnt[_const_pool]-1&&key(VK_DOWN)){
			repc(cupos[fss[_const_pool]+1],fss[_const_pool]);
			repc(cupos[fss[_const_pool]],fss[_const_pool]+1);
			fswap(inpnam,copos[fss[_const_pool]],copos[fss[_const_pool]+1],copos[fss[_const_pool]+2]);
			fss[_const_pool]++;	if(fis[_const_pool]<fcnt[_const_pool])	fis[_const_pool]++;
		}else if((fss[_const_pool]>0
		&&getmousey()==fss[_const_pool]-fis[_const_pool]&&key(VK_LBUTTON))
		||(fss[_const_pool]==fis[_const_pool]+1&&key(VK_RETURN))){
			system("cls");
			printconst(F,O,fss[_const_pool],1);printf("\nchange?[Y/ ]");
			char tc=getchar();
			if(tc!='Y'&&tc!='y')	goto file_end;
			FILE *C=fopen(inpnam,"rb+");
			fsetpos(F,&(copos[fss[_const_pool]]));
			fsetpos(C,&(copos[fss[_const_pool]]));
			char c;fscanf(F,"%c",&c);	fprintf(C,"%c",c);
			switch (c){	case 0X01:
				unsigned short len,tln;	tln=0;	read2(F,&len);
				fpos_t tmppos;	fgetpos(F,&tmppos);
				char s[65536];	for(int i=0;i<65536;i++)	s[i]=0;
				rewind(stdin);	scanf("%s",s);
				for(int i=0;s[i];i++){	tln++;
					if(s[i]=='\\'){
						switch (s[i+1]) {
						case '\\':	s[i]='\\';	break;
						case 'n':	s[i]='\n';	break;
						case 't':	s[i]='\t';	break;
						case 'a':	s[i]='\a';	break;
						case 'b':	s[i]='\b';	break;
						case 'f':	s[i]='\f';	break;
						case 'r':	s[i]='\r';	break;
						case 'v':	s[i]='\v';	break;
						default:
						s[i]=h2c(s[i+1])*16+h2c(s[i+2]);
						i++;s[i]=0;break;}i++;s[i+1]=0;
					}
				}
				printf("%d\nY/N",tln);rewind(stdin);
				for(int i=0,j=0;j<65536;i++,j++){
					while(s[j]==0)j++;s[i]=s[j];}
				char c;c=getchar();
				if(c=='Y'||c=='y'){
					writ2(C,&tln);
					fdelt(inpnam,tnam,tmppos,tmppos+len);
					finst(inpnam,tmppos,s,tln);
				}	break;
#define incn2(a,t,o) fprintf(O,a);	tn=show2(F,O);	fprintf(O,"->#");scanf("%X",&tn);if(!chkc(tn,t)&&cchk)	{fprintf(O,o);	getchar();	getchar();	break;}	writ2(C,&tn);
#define incn1(a,t,o) fprintf(O,a);	tc=show1(F,O);	fprintf(O,"->#");scanf("%X",&tc);if(!chkc(tc,t)&&cchk)	{fprintf(O,o);	getchar();	getchar();	break;}	writ1(C,&tc);
//问a 类型非t->输出o 
						case 0X03:
				int ti;		read4(F,&ti);
				fprintf(O,"%+08X=%d->",ti,ti);
				if(!scanf("%X%*2s",&ti))	scanf("%*2s%d",&ti);
				writ4(C,&ti);	break;
				case 0X04:
				float tf;	read4(F,&tf);
				fprintf(O,"%f->",tf);
				scanf("%f",&tf);	writ4(C,&tf);
				break;	case 0X05:
				long long tl;	read8(F,&tl);
				fprintf(O,"%+016llX=%lld->",tl);
				if(!scanf("%llX%*2s",&tl))	scanf("%*2s%lld",&tl);
				writ8(C,&tl);	break;
						case 0X06:
				double td;	read8(F,&td);
				fprintf(O,"%lf->",td);
				scanf("%lf",&td);	writ8(C,&td);
				break;	case 0X07:
				if(csug){inpc(F,O,C,_class_name);}
				else	{incn2("类=      #",0X01,"类名 -> 文本\n");}
				break;	case 0X08:
				if(csug){inpc(F,O,C,_string_text);}
				else	{incn2("字符串=  #",0X01,"字符串 -> 文本\n");}
				break;	case 0X09:
				if(csug){inpc(F,O,C,_class);inpc(F,O,C,_info);}
				else	{incn2("字段=    #",0X07,"字段 -> 类 + 定义\n");
						incn2("info=    #",0X0C,"字段 -> 类 + 定义\n");}
				break;	case 0X0A:
				if(csug){inpc(F,O,C,_class);inpc(F,O,C,_info);}
				else	{incn2("方法=    #",0X07,"方法 -> 类 + 定义\n");
						incn2("info=    #",0X0C,"方法 -> 类 + 定义\n");}
				break;	case 0X0B:
				if(csug){inpc(F,O,C,_class);inpc(F,O,C,_info);}
				else	{incn2("接口=    #",0X07,"接口 -> 类 + 定义\n");
						incn2("info=    #",0X0C,"接口 -> 类 + 定义\n");}
				break;	case 0X0C:
				if(csug){inpc(F,O,C,_info_name);inpc(F,O,C,_info_type);}
				else	{incn2("info=    #",0X01,"定义 -> 名字 + 类型\n");
						incn2("name=    #",0X01,"定义 -> 名字 + 类型\n");}
				break;	case 0X0F:
				if(csug){inpc(F,O,C,_short_other);inpc(F,O,C,_info_type);}
				else	{incn1("名字=    #",0X01,"句柄 -> 名字 + 方法\n");
						incn2("方法=    #",0X0A,"句柄 -> 名字 + 方法\n");}
				break;	case 0X10:
				if(csug){inpc(F,O,C,_info_name);inpc(F,O,C,_info_type);}
				else	{incn2("类名=    #",0X01,"类名 -> 文本");}
				break;	case 0X12:
				if(csug){inpc(F,O,C,_short_other);inpc(F,O,C,_info_type);	}
				else	{incn1("名字=    #",0X01,"INVD -> 名字 + 定义\n");
						incn2("定义=    #",0X0C,"INVD -> 名字 + 定义\n");}
				break;	}
				fclose(C);	goto file_end;
			}else if(fss[_const_pool]>0&&key(VK_OEM_MINUS)){
				if(cupos[fss[_const_pool]]){	fprintf(O,"正在用!");getchar();goto file_end;}
				if(chkc(fss[_const_pool],0X01)){
					rewind(stdin);	fprintf(O,"确定?[Y/N]");	char c;
					scanf("%c",&c);	if(c!='Y'&&c!='y')	goto file_end;
				}
				for(int i=fss[_const_pool]+1;i<fcnt[_const_pool]-1;i++)
					repc(cupos[i],i-1);
				delc(fss[_const_pool]);
			}else if(key(VK_OEM_PLUS)){
				fprintf(O,"01/1文本\n02/2NO\n03/3整数\n04/4小数\n05/5长数\n06/6长小\n07/7类\n08/8字符串\n09/9字段\n");
				fprintf(O,"0A/A方法\n0B/B接口\n0C/C定义\n0D/DNO\n0E/ENO\n0F/F句柄\n10/G法类\n11/H\n12/IINVD");
				int k=0;	while(!key(VK_LBUTTON)){
					if(key(VK_RBUTTON)||key(VK_ESCAPE))	goto file_end;
					k=getmousey();
					if(key('1')){	k=0X01;	break;}
					if(key('3')){	k=0X03;	break;}
					if(key('4')){	k=0X04;	break;}
					if(key('5')){	k=0X05;	break;}
					if(key('6')){	k=0X06;	break;}
					if(key('7')){	k=0X07;	break;}
					if(key('8')){	k=0X08;	break;}
					if(key('9')){	k=0X09;	break;}
					if(key('A')){	k=0X0A;	break;}
					if(key('B')){	k=0X0B;	break;}
					if(key('C')){	k=0X0C;	break;}
					if(key('D')){	k=0X0D;	break;}
					if(key('E')){	k=0X0E;	break;}
					if(key('F')){	k=0X0F;	break;}
					if(key('G')){	k=0X10;	break;}
					if(key('H')){	k=0X11;	break;}
					if(key('I')){	k=0X12;	break;}
				}
				if(k==0X02||k==0X0E||k==0X0F||k==0X11||k>0X12)	goto file_end;
				if(fss[_const_pool]<=0)	addc(fcnt[_const_pool]-1,k);
				else					addc(fss[_const_pool],k);
			}
		}
	#define I_FLAG_myIDE
		if(showno==_flagw&&!zab&&key(VK_LBUTTON)){
			int k=getmousey();
			FILE *C=fopen(inpnam,"rb+");
			fsetpos(F,&(copos[fcnt[_const_pool]]));
			fsetpos(C,&(copos[fcnt[_const_pool]]));
			unsigned short temp=0;
			read2(F,&temp);	if(k>=1&&k<=16)
			temp^=65536>>k;	writ2(C,&temp);
			if(k==17){
				if(csug){inpc(F,O,C,_class_name);}
				else	{incn2("我:   #",0X07,"我 -> 类\n");}
			}else{	fofst(F,2);fofst(C,2);
		}	if(k==18){
				if(csug){inpc(F,O,C,_class_name);}
				else	{incn2("爹:   #",0X07,"爹 -> 类\n");}
			}else{	fofst(F,2);fofst(C,2);
		}	fsetpos(F,&copos[fcnt[_const_pool]+5]);	fofst(F,-2);
			fsetpos(C,&copos[fcnt[_const_pool]+5]);	fofst(C,-2);
			if(k==19){
				if(csug){inpc(F,O,C,_string_text);}
				else	{incn2("源:   #",0X01,"源 -> 文件\n");}
			}fclose(C);	goto file_end;
		}
		if(showno==_flagw&&zab&&key(VK_LBUTTON)){
			zab=0;tmpw=_flagw;
			switch (getmousey()){
			case 2:	showno=_inclw;	break;
			case 3:	showno=_rvanw;	break; 
			case 4:	showno=_bootw;	break;	}
		}
		if(key('C')){
			char s[1024];	scanf("%s",s);
			int i=0;for(;s[i];i++);
			temp=tonum(s+i-4);
			if(temp==0)	printconst(F,O,0,2);
			else		printconst(F,O,temp);
			key(VK_RETURN);
			getchar();	getchar();
		}
		if(key('Z'))	zab=!zab;
		if(showno>=0&&showno<_enofw){
		if(key(VK_LEFT)&&showno>0)			showno--;
		if(key(VK_RIGHT)&&showno<_enofw-1)	showno++;
		}
		if(key(VK_SPACE))
		swap(showno,tmpw);
		if(showno==_confw&&key(VK_LBUTTON)){
			int k=getmousey();
			if(k==_cchk)	cchk=!cchk;
			if(k==_csug)	csug=!csug;
			if(k==_help){	system("cls");
				printf("上下键翻列表,左右键翻页,Z键切换前后界面\n"); 
				printf("鼠标左键选择\t右键不选\n");
				printf("选中后上下键调整上下\t左键修改\n");
				printf("输入数字时打问号表示不改\n");
				printf("C键+0000打常量表,C+编号输出对应常量\n");
				printf("CTRLA运行\tCTRLR重命名\nCTRLN新建\tCTRLO打开");
				getchar();}
		}
	#define I_FIEL_myIDE
		if(showno==_fielw){
			if(fis[_fields]>=fieldcnt)	fis[_fields]=fieldcnt-1;
			if(fis[_fields]<0)	fis[_fields]=0;
				  if(fis[_fields]>0&&key(VK_UP))
				fis[_fields]--;
			 else if(fis[_methods]<fieldcnt-1&&key(VK_DOWN))
				fis[_fields]++;
			 else if(key(VK_LBUTTON)){
				int k=getmousey();
				FILE *C=fopen(inpnam,"rb+");
				fsetpos(F,&(fe[fis[_fields]].tpos[_fielp]));
				fsetpos(C,&(fe[fis[_fields]].tpos[_fielp]));
				unsigned short temp=0;
				read2(F,&temp);	if(k>=1&&k<=16)
					temp^=65536>>k;	writ2(C,&temp);
				read2(F,&temp);	if(k==17){
				if(csug){fofst(F,-2);inpc(F,O,C,_field_name);fclose(C);goto file_end;}
				fprintf(O,"\n名:   #");	out2(O,temp);
				fprintf(O,"->#");scanf("%x",&temp);
				if(!chkc(temp,0X01)&&cchk){
					fprintf(O,"\n不是名字");
					getchar();	getchar();	fclose(C);		goto file_end;}
				}	writ2(C,&temp);
				read2(F,&temp);	if(k==18){
				if(csug){fofst(F,-2);inpc(F,O,C,_field_type);fclose(C);goto file_end;}
				fprintf(O,"\n类:   #");	out2(O,temp);
				fprintf(O,"->#");scanf("%x",&temp);
				if(!chkc(temp,0X01)&&cchk){
					fprintf(O,"\n不是类型");
					getchar();	getchar();	fclose(C);		goto file_end;}
			 	}	writ2(C,&temp);
			 	if(k==20){
				 	if(fe[fis[_fields]].tpos[_consp]){
					 	fsetpos(F,&(fe[fis[_fields]].tpos[_consp]));	fofst(F,4);
						fsetpos(C,&(fe[fis[_fields]].tpos[_consp]));	fofst(C,4);
						if(csug)	temp=inpc(F,O,C,_allc);	else{
						read2(F,&temp);	fprintf(O,"\n值:   #");	out2(O,temp);
						fprintf(O,"->#");scanf("%x",&temp);	writ2(C,&temp);}
						printf("%d",temp);while(!key(VK_RETURN));
						C=freset(C,fopen(inpnam,"r+"));
						if(temp==0){
							fdelt(inpnam,tnam,fe[fis[_fields]].tpos[_consp]-2,fe[fis[_fields]].tpos[_consp]+6);
							printf("%llX",fe[fis[_fields]].tpos[_consp]-2);
							fsetpos(F,&(fe[fis[_fields]].tpos[_fielp]));fofst(F,6);
							fsetpos(C,&(fe[fis[_fields]].tpos[_fielp]));fofst(C,6);
							read2(F,&temp);	temp--;	writ2(C,&temp);
						}
					}else{
						read2(F,&temp);	temp++;	writ2(C,&temp);
						char c[16]={0X0F,0X0F,0X00,0X00,0X00,0X02,0X00,0X01};
						temp=fndc("ConstantValue");
						c[0]=temp&0XFF00;c[1]=temp&0X00FF;
						fclose(F);fclose(C);
						finst(inpnam,fe[fis[_fields]].tpos[_fielp]+8,c,8);
						goto file_end;
					}
				}
				fclose(C);
			}
		}
	#define I_METH_myIDE
		if(showno==_methw){
				  if(fis[_methods]>0&&key(VK_UP))
				fis[_methods]--;
			 else if(fis[_methods]<fcnt[_methods]-1&&key(VK_DOWN))
			 	fis[_methods]++;
				  if(!zab&&key(VK_LBUTTON)){
				int k=getmousey();
				FILE *C=fopen(inpnam,"rb+");
				fsetpos(F,&(m[fis[_methods]].tpos[_methp]));
				fsetpos(C,&(m[fis[_methods]].tpos[_methp]));
				unsigned short temp=0;
				read2(F,&temp);	if(k>=1&&k<=16)
					temp^=65536>>k;	writ2(C,&temp);
				read2(F,&temp);	if(k==17){
				if(csug){fofst(F,-2);inpc(F,O,C,_method_name);fclose(C);goto file_end;}
				fprintf(O,"\n名:   #");	out2(O,temp);
				fprintf(O,"->#");scanf("%x",&temp);
				if(!chkc(temp,0X01)&&cchk)
					{fprintf(O,"\n不是名字");
					getchar();	getchar();	fclose(C);		goto file_end;}
				}	writ2(C,&temp);
				read2(F,&temp);	if(k==18){
				if(csug){fofst(F,-2);inpc(F,O,C,_method_type);fclose(C);goto file_end;}
				fprintf(O,"\n类:   #");	out2(O,temp);
				fprintf(O,"->#");scanf("%x",&temp);
				if(!chkc(temp,0X01)&&cchk)
					{fprintf(O,"\n不是类型");
					getchar();	getchar();	fclose(C);		goto file_end;}
			 	}	writ2(C,&temp);
				fclose(C);
			}else if(key(VK_OEM_MINUS)){
				fsetpos(F,&(m[fis[_methods]].tpos[_methp]));
				char s[256];read4(F,&temp4);
				readconst(copos[temp4&0XFFFF],s);
				if(cmp(s,"<init>"))
				{system("cls");printf("不能删init方法");	goto file_end;} 
				printf("确定?[T/F]");
				if(getchar()=='T'){
					FILE *C=fopen(inpnam,"rb+");
					fsetpos(F,&(copos[fcnt[_const_pool]+_methods]));
					fsetpos(C,&(copos[fcnt[_const_pool]+_methods]));
					int tn=0;	read2(F,&tn);
					tn--;		writ2(C,&tn);
					fclose(C);
					out4(O,m[fis[_methods]].tpos[_methp]);
					out4(O,m[fis[_methods]].tpos[_endmp]);
					fdelt(inpnam,tnam,m[fis[_methods]].tpos[_methp],m[fis[_methods]].tpos[_endmp]);
					fis[_methods]--;
				}
			}else if(key(VK_OEM_PLUS)){
				unsigned char s[256]={
				0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X01,
				0XFF,0XFF,0X00,0X00,0X00,0X0C,0X00,0X00,
				0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
				0X00,0X00};
				int ti=fndc("Code");
				s[8]=ti&0XFF00;	s[9]=ti&0X00FF;
				FILE *C=fopen(inpnam,"rb+");
				fsetpos(F,&(copos[fcnt[_const_pool]+_methods]));
				fsetpos(C,&(copos[fcnt[_const_pool]+_methods]));
				int tn=0;	read2(F,&tn);
				tn++;		writ2(C,&tn);
				fclose(C);
				finst(inpnam,m[fis[_methods]].tpos[_endmp],(char *)s,26);
				fis[_methods]++;
			}else if(zab&&key(VK_LBUTTON)){
				zab=0;	tmpw=showno;
				switch (getmousey()){
					case 1:	showno=_codew;	break;
					case 2:	showno=_trysw;	break;
					case 3:	showno=_linsw;	break;
					case 4:	showno=_variw;	break;
					case 5:
						if(m[fis[_methods]].tpos[_smttp]>0){
						FILE *C=fopen(inpnam,"rb+");
						fsetpos(C,&m[fis[_methods]].tpos[_smttp]);	fofst(C,4);
						char s[65536*2+1]={};scanf("%s",s);
						int i=0;for(;s[i];i++);out2(C,(i+1)/2);
						for(int i=0;s[i];i+=2)
						out1(C,h2c(s[i])*16+h2c(s[i+1]));
						fclose(C);	if(i==0){
						fdelt(inpnam,tnam,m[fis[_methods]].tpos[_smttp]-2,
						m[fis[_methods]].tpos[_smttp]+2+m[fis[_methods]].cnt[_smttp]);
						pa2(inpnam,m[fis[_methods]].tpos[_methp]+6,-1);}
						}	break;
					case 6:
						if(m[fis[_methods]].tpos[_signp]>0){
						FILE *C=fopen(inpnam,"rb+");	us tn;
						fsetpos(F,&m[fis[_methods]].tpos[_signp]);	fofst(F,4);
						fsetpos(C,&m[fis[_methods]].tpos[_signp]);	fofst(C,4);
						if(csug){tn=inpc(F,O,C,_string_text);}
						else	{incn2("签名=    #",0X01,"签名 -> 文本\n");	}
						fclose(C);	if(tn==0){
						fdelt(inpnam,tnam,m[fis[_methods]].tpos[_signp]-2,m[fis[_methods]].tpos[_signp]+6);
						pa2(inpnam,m[fis[_methods]].tpos[_methp]+6,-1);}
						}	break;
				}
			}
		}
	#define I_CODE_myIDE
		if(showno==_codew){
			stdlop(m[fis[_methods]].ss[_codew],m[fis[_methods]].is[_codew],m[fis[_methods]].cnt[_codep],_codew);
			fpos_t tpos=max(m[fis[_methods]].ss[_codew],m[fis[_methods]].cnt[_codep]-1);
				  if(m[fis[_methods]].ss[_codew]>=0
			&&m[fis[_methods]].ss[_codew]>0
			&&key(VK_UP)){//go_up
				fswap(inpnam,m[fis[_methods]].prpos[tpos-1]
							,m[fis[_methods]].prpos[tpos]
							,m[fis[_methods]].prpos[tpos+1]);
				if(m[fis[_methods]].is[_codew]>0)	m[fis[_methods]].is[_codew]--;
				m[fis[_methods]].ss[_codew]--;
			}else if(m[fis[_methods]].ss[_codew]>=0
			&&m[fis[_methods]].ss[_codew]<m[fis[_methods]].cnt[_codep]-1
			&&key(VK_DOWN)){//go_dn
				fswap(inpnam,m[fis[_methods]].prpos[tpos]
							,m[fis[_methods]].prpos[tpos+1]
							,m[fis[_methods]].prpos[tpos+2]);
				if(m[fis[_methods]].is[_codew]<m[fis[_methods]].cnt[_codep])	m[fis[_methods]].is[_codew]++;
				m[fis[_methods]].ss[_codew]++;
			}else if(m[fis[_methods]].cnt[_codep]>0
			&&key(VK_OEM_MINUS)){//del
				int dt=m[fis[_methods]].prpos[tpos+1]-m[fis[_methods]].prpos[tpos];
				fpos_t cpos=m[fis[_methods]].tpos[_codep]+8;
				pa2(inpnam,cpos,-dt);
				for(int i=m[fis[_methods]].ss[_codew]+1;i<m[fis[_methods]].cnt[_codep];i++)
					repc(m[fis[_methods]].pupos[i],i-1);
				fdelt(inpnam,tnam,m[fis[_methods]].prpos[tpos],m[fis[_methods]].prpos[tpos+1]);
			}else if((m[fis[_methods]].ss[_codew]>=0
			&&m[fis[_methods]].ss[_codew]==getmousey()+m[fis[_methods]].is[_codew]-1
			&&key(VK_LBUTTON))
			||(m[fis[_methods]].ss[_codew]==m[fis[_methods]].is[_codew]
			&&key(VK_RETURN))){//change
				system("cls");
				FILE *C=fopen(inpnam,"rb+");
				fsetpos(F,&(m[fis[_methods]].prpos[tpos]));
				fsetpos(C,&(m[fis[_methods]].prpos[tpos]));
				uc c[256];	fscanf(F,"%c",c);
				printf("%d\n",codln[c[0]]);
				for(int i=1;i<codln[c[0]];i++)
				{	fscanf(F,"%c",c+i);	out1(O,c[i]);}
				fprintf(O,"\n");
				uc s[256];	scanf("%s",s);
				for(int i=0,j=1;s[i]&&j<codln[c[0]];i++){
						  if(c2x(s[i])>=0&&c2x(s[i+1])>=0){
						c[j]=c2x(s[i])*16+c2x(s[i+1]);	i++;j++;
					}else if(s[i]=='*')	j++;
					 else{printf("不理解%c",s[i]);
						key(VK_RETURN);	while(!key(VK_RETURN));}
				}
				for(int i=0;i<codln[c[0]];i++)
					fprintf(C,"%c",c[i]);
				fclose(C);	key(VK_RETURN);
			}
		}
	#define I_EXMP_myIDE
		if(showno==_exmpw){
				printf("%X",m[fis[_methods]].is[_exmpw]);
				  if(m[fis[_methods]].is[_exmpw]>0&&key(VK_UP))
				m[fis[_methods]].is[_exmpw]--;
			 else if(m[fis[_methods]].is[_exmpw]<codln.size()&&key(VK_DOWN))
				m[fis[_methods]].is[_exmpw]++;
			 else if(getmousey()>0&&getmousey()<getheight()-1&&key(VK_LBUTTON)){
				int i=m[fis[_methods]].is[_exmpw]+getmousey()-1;
				if(i<203){
					char s[8]={};s[0]=i;
					ll t=m[fis[_methods]].prpos[m[fis[_methods]].cnt[_codep]];
					if(m[fis[_methods]].ss[_codew]!=-1)
						t=m[fis[_methods]].prpos[m[fis[_methods]].ss[_codew]];
					for(int i=m[fis[_methods]].ss[_codew];i<m[fis[_methods]].cnt[_codep];i++)
						repc(m[fis[_methods]].pupos[i],i+1);
					if(t<=0)	forctop();
					finst(inpnam,t,s,codln[i]);
					if(m[fis[_methods]].ss[_codew]!=-1)	m[fis[_methods]].ss[_codew]++;
					FILE *C=fopen(inpnam,"rb+");
					int dt=codln[i];
					fpos_t cpos=m[fis[_methods]].tpos[_codep]+8;
					pa2(inpnam,cpos,dt);
				}
			}else if(getmousey()==0&&key(VK_LBUTTON))
				scanf("%X",&(m[fis[_methods]].is[_exmpw]));
		}
	#define I_TRYS_myIDE
		if(showno==_trysw){
			stdlop(m[fis[_methods]].ss[_trysw],m[fis[_methods]].is[_trysw],m[fis[_methods]].cnt[_trysp],_trysw);
			fpos_t tpos=m[fis[_methods]].ss[_trysw]*8+m[fis[_methods]].tpos[_trysp]+2;
				  if(m[fis[_methods]].ss[_trysw]>=0
			&&m[fis[_methods]].ss[_trysw]<m[fis[_methods]].cnt[_trysp]
			&&key(VK_UP)){//go_up
				fswap(inpnam,tpos-8,tpos,tpos+8);
				if(m[fis[_methods]].is[_trysw]>0)	m[fis[_methods]].is[_trysw]--;
				m[fis[_methods]].ss[_trysw]--;
			}else if(m[fis[_methods]].ss[_trysw]>=0
			&&m[fis[_methods]].ss[_trysw]<m[fis[_methods]].cnt[_trysp]
			&&key(VK_DOWN)){//go_dn
				fswap(inpnam,tpos,tpos+8,tpos+16);
				if(m[fis[_methods]].is[_trysw]<m[fis[_methods]].cnt[_trysp])	m[fis[_methods]].is[_trysw]++;
				m[fis[_methods]].ss[_trysw]++;
			}else if(m[fis[_methods]].ss[_trysw]>=0
			&&key(VK_OEM_PLUS)){//add
				char s[8]={};
				pa2(inpnam,m[fis[_methods]].tpos[_trysp]+4,1);
				finst(inpnam,tpos,s,8);
			}else if(m[fis[_methods]].ss[_trysw]>=0
			&&key(VK_OEM_MINUS)){//del
				pa2(inpnam,m[fis[_methods]].tpos[_trysp]+4,-1);
				fdelt(inpnam,tnam,tpos,tpos+8);
			}else if((m[fis[_methods]].ss[_trysw]>=0
			&&m[fis[_methods]].ss[_trysw]==getmousey()+m[fis[_methods]].is[_trysw]-1
			&&key(VK_LBUTTON))
			||(m[fis[_methods]].ss[_trysw]==m[fis[_methods]].is[_trysw]
			&&key(VK_RETURN))){//change
				system("cls");
				FILE *C=fopen(inpnam,"rb+");
				fsetpos(F,&tpos);
				fsetpos(C,&tpos);
				int tn;
				rewind(stdin);
				fprintf(O,"从  ={\n");		tn=show2(F,O);
				fprintf(O,"->");	scanf("%X",&tn);	writ2(C,&tn);
				rewind(stdin);
				fprintf(O,"到  ={\n");		tn=show2(F,O);
				fprintf(O,"->");	scanf("%X",&tn);	writ2(C,&tn);
				rewind(stdin);	fprintf(O,"处理={");	tn=show2(F,O);
				fprintf(O,"\n");	printconst(F,O,tn);
				fprintf(O,"\n->");	scanf("%X",&tn);	writ2(C,&tn);
				rewind(stdin);	fprintf(O,"类别:");	tn=show2(F,O);
				fprintf(O,"\n");	printconst(F,O,tn);
				fprintf(O,"\n->");	scanf("%X",&tn);	writ2(C,&tn);
				fclose(C);
				key(VK_RETURN);
			}
		}
	#define I_ATRI_myIDE
		if(showno==_linsw){
			if(m[fis[_methods]].tpos[_linsp]>=0){
			stdlop(m[fis[_methods]].ss[_linsw],m[fis[_methods]].is[_linsw],m[fis[_methods]].cnt[_linsp],_linsw);
			fpos_t tpos=max(m[fis[_methods]].is[_linsw],m[fis[_methods]].ss[_linsw])*4+m[fis[_methods]].tpos[_linsp]+6;
				  if(m[fis[_methods]].ss[_linsw]>0
			&&m[fis[_methods]].ss[_linsw]<m[fis[_methods]].cnt[_linsp]
			&&key(VK_UP)){//go_up
				fswap(inpnam,tpos-4,tpos,tpos+4);
				if(m[fis[_methods]].is[_linsw]>0)	m[fis[_methods]].is[_linsw]--;
				m[fis[_methods]].ss[_linsw]--;
			}else if(m[fis[_methods]].ss[_linsw]>=0
			&&m[fis[_methods]].ss[_linsw]<m[fis[_methods]].cnt[_linsp]-1
			&&key(VK_DOWN)){//go_dn
				fswap(inpnam,tpos,tpos+4,tpos+8);
				if(m[fis[_methods]].is[_linsw]<m[fis[_methods]].cnt[_linsp])	m[fis[_methods]].is[_linsw]++;
				m[fis[_methods]].ss[_linsw]++;
			}else if(m[fis[_methods]].cnt[_linsp]>=0
			&&key(VK_OEM_PLUS)){//add
				char s[4]={};
				pa2(inpnam,m[fis[_methods]].tpos[_linsp]+4,1);
				finst(inpnam,tpos,s,4);
				if(m[fis[_methods]].is[_linsw]<m[fis[_methods]].cnt[_linsp])	m[fis[_methods]].is[_linsw]++;
			}else if(m[fis[_methods]].cnt[_linsp]>0
			&&key(VK_OEM_MINUS)
			){//del
				pa2(inpnam,m[fis[_methods]].tpos[_linsp]+4,-1);
				fdelt(inpnam,tnam,tpos,tpos+4);
				if(m[fis[_methods]].is[_linsw]>0)	m[fis[_methods]].is[_linsw]--;
			}else if((m[fis[_methods]].ss[_linsw]>=0
			&&m[fis[_methods]].ss[_linsw]==getmousey()+m[fis[_methods]].is[_linsw]-1
			&&key(VK_LBUTTON))
			||(m[fis[_methods]].ss[_linsw]==m[fis[_methods]].is[_linsw]
			&&key(VK_RETURN))){//change
				system("cls");
				FILE *C=fopen(inpnam,"rb+");
				fsetpos(F,&tpos);
				fsetpos(C,&tpos);
				int tn;
				rewind(stdin);
				tn=show2(F,O);	fprintf(O,"行");
				fprintf(O,"->{");	scanf("%X",&tn);	writ2(C,&tn);
				rewind(stdin);
				tn=show2(F,O);	fprintf(O,"行");
				fprintf(O,"->{");	scanf("%X",&tn);	writ2(C,&tn);
				fclose(C);
				key(VK_RETURN);
			}
			}	  if(m[fis[_methods]].cnt[_linsp]>=0&&keydn(VK_DELETE)&&key(VK_BACK)
			||m[fis[_methods]].cnt[_linsp]==0&&key(VK_OEM_MINUS)){
				fpos_t mi=m[fis[_methods]].cnt[_trysp]*8+m[fis[_methods]].tpos[_trysp]+2;
				fpos_t l=m[fis[_methods]].cnt[_linsp]*4+6;
				FILE *C=fopen(inpnam,"rb+");
				pa2(inpnam,mi,-1);
				fclose(C);
				fdelt(inpnam,tnam,m[fis[_methods]].tpos[_linsp]-2,m[fis[_methods]].tpos[_linsp]+l);
				m[fis[_methods]].tpos[_linsp]=-1;
			}else if(m[fis[_methods]].tpos[_linsp]<=0&&key(VK_OEM_PLUS)){
				fpos_t mi=m[fis[_methods]].cnt[_trysp]*8+m[fis[_methods]].tpos[_trysp]+2;
				fpos_t l=m[fis[_methods]].tpos[_endmp];
				char c[65536];	int ti=fndc("LineNumberTable");
				FILE *C=fopen(inpnam,"rb+");
				pa2(inpnam,mi,1);
				fclose(C);
				char s[16]={
				0X0F,0X0F,0X00,0X00,0X00,0X02,0X00,0X00};
				s[0]=ti&0XFF00;	s[1]=ti&0X00FF;
				printf("%llX",l);	getchar();
				finst(inpnam,l,s,8);	dbf=true;
			}
		}
	//lines/varib
		if(showno==_variw){
			stdlop(m[fis[_methods]].ss[_variw],m[fis[_methods]].is[_variw],m[fis[_methods]].cnt[_varip],_codew);
			us ss=max(m[fis[_methods]].is[_variw],m[fis[_methods]].ss[_variw]);
			fpos_t tpos=ss*10+m[fis[_methods]].tpos[_varip]+6;
			fpos_t tpo1=ss*10+m[fis[_methods]].tpos[_vartp]+6;
				  if(m[fis[_methods]].ss[_variw]>0
			&&m[fis[_methods]].ss[_variw]<m[fis[_methods]].cnt[_varip]
			&&key(VK_UP)){//go_up
				fswap(inpnam,tpos-10,tpos,tpos+10);
				if(m[fis[_methods]].is[_variw]>0)	m[fis[_methods]].is[_variw]--;
				m[fis[_methods]].ss[_variw]--;
			}else if(m[fis[_methods]].ss[_variw]>=0
			&&m[fis[_methods]].ss[_variw]<m[fis[_methods]].cnt[_varip]-1
			&&key(VK_DOWN)){//go_dn
				fswap(inpnam,tpos,tpos+10,tpos+20);
				if(m[fis[_methods]].is[_variw]<m[fis[_methods]].cnt[_varip])	m[fis[_methods]].is[_variw]++;
				m[fis[_methods]].ss[_variw]++;
			}else if(m[fis[_methods]].tpos[_varip]>=0&&
			key(VK_OEM_PLUS)){//add
				char s[10]={};
				s[8]=ss&0XFF00;
				s[9]=ss&0x00FF;
				pa2(inpnam,m[fis[_methods]].tpos[_varip]+4,1);
				for(int i=ss;i<m[fis[_methods]].cnt[_varip];i++)
					repc(m[fis[_methods]].vupos[i],i+1);
				out8(stdout,tpos);//return 0;
				finst(inpnam,tpos,s,10);
				if(m[fis[_methods]].is[_variw]<m[fis[_methods]].cnt[_varip])	m[fis[_methods]].is[_variw]++;
			}else if(m[fis[_methods]].cnt[_varip]>0
			&&key(VK_OEM_MINUS)){//del
				pa2(inpnam,m[fis[_methods]].tpos[_varip]+4,-1);
				for(int i=ss+1;i<m[fis[_methods]].cnt[_varip];i++)
					repc(m[fis[_methods]].vupos[i],i-1);
				fdelt(inpnam,tnam,tpos,tpos+10);
				if(m[fis[_methods]].is[_variw]>0)	m[fis[_methods]].is[_variw]--;
			}else if((m[fis[_methods]].ss[_variw]>=0
			&&m[fis[_methods]].ss[_variw]==getmousey()+m[fis[_methods]].is[_variw]-1
			&&key(VK_LBUTTON))
			||(m[fis[_methods]].ss[_variw]==m[fis[_methods]].is[_variw]
			&&key(VK_RETURN))){//change
				system("cls");
				FILE *C0=fopen(inpnam,"rb+"),*C1=fopen(inpnam,"rb+");
				fsetpos(F,&tpos);fsetpos(C0,&tpos);fsetpos(C1,&tpo1); 
				int tn;
				rewind(stdin);	fprintf(O,"\n定义位置");tn=show2(F,O);
				fprintf(O,"->#");	scanf("%X",&tn);	writ2(C0,&tn);
				if(m[fis[_methods]].tpos[_vartp]>=0)	writ2(C1,&tn);
				rewind(stdin);	fprintf(O,"可用长度");	tn=show2(F,O);
				fprintf(O,"->#");	scanf("%X",&tn);	writ2(C0,&tn);
				if(m[fis[_methods]].tpos[_vartp]>=0)	writ2(C1,&tn);
				rewind(stdin);	fprintf(O,"名字=#");	tn=show2(F,O);
				fprintf(O,"\n");	printconst(F,O,tn);
				fprintf(O,"\n->#");	scanf("%X",&tn);	writ2(C0,&tn);
				if(m[fis[_methods]].tpos[_vartp]>=0)	writ2(C1,&tn);
				rewind(stdin);	fprintf(O,"类型=#");	tn=show2(F,O);
				fprintf(O,"\n");	printconst(F,O,tn);
				fprintf(O,"\n->#");	scanf("%X",&tn);	writ2(C0,&tn);
				if(m[fis[_methods]].tpos[_vartp]>=0){
					fsetpos(F,&tpo1);fofst(F,4);
				rewind(stdin);	fprintf(O,"描述=#");	tn=show2(F,O);
				fprintf(O,"\n");	printconst(F,O,tn);
				fprintf(O,"\n->#");	scanf("%X",&tn);	writ2(C1,&tn);}
				fclose(C0);	fclose(C1);	key(VK_RETURN);
			}	if(m[fis[_methods]].cnt[_varip]>=0&&keydn(VK_DELETE)&&key(VK_BACK)
			||m[fis[_methods]].cnt[_varip]==0&&key(VK_OEM_MINUS)){
				fpos_t mi=m[fis[_methods]].cnt[_trysp]*8+m[fis[_methods]].tpos[_trysp]+2;
				fpos_t l=m[fis[_methods]].cnt[_varip]*10+6;
				FILE *C=fopen(inpnam,"rb+");
				pa2(inpnam,mi,-1);
				printf("%d",tn);	fclose(C);
				fdelt(inpnam,tnam,m[fis[_methods]].tpos[_varip]-2,m[fis[_methods]].tpos[_varip]+l);
				m[fis[_methods]].tpos[_varip]=-1;
			}else if(m[fis[_methods]].tpos[_varip]<=0&&key(VK_OEM_PLUS)){
				fpos_t mi=m[fis[_methods]].cnt[_trysp]*8+m[fis[_methods]].tpos[_trysp]+2;
				fpos_t l=0;
				for(int i=3;i<8;i++)
					if(m[fis[_methods]].tpos[i]>=0)
					{l=m[fis[_methods]].tpos[i]-2;break;}
				char c[65536];	int ti=fndc("LocalVariableTable");
				FILE *C=fopen(inpnam,"rb+");
				pa2(inpnam,mi,1);
				fclose(C);
				char s[16]={
				0X0F,0X0F,0X00,0X00,0X00,0X02,0X00,0X00};
				s[0]=ti&0XFF00;	s[1]=ti&0X00FF;
				out8(stdout,l);	return 0;
				finst(inpnam,l,s,8);	dbf=true;
			}
		}
	#define I_FATRI_myIDE
		if(showno==_inclw){
			fpos_t tpos=max(fss[_inclp],fis[_inclp])*8+copos[fcnt[_const_pool]+_inclp]+6;
				  if(fis[_inclp]>0&&key(VK_UP))
				fis[_inclp]--;
			 else if(fis[_inclp]<fcnt[_inclp]-1&&key(VK_DOWN))
			 	fis[_inclp]++;
				  if(!zab&&key(VK_LBUTTON)){
				int k=getmousey();
				FILE *C=fopen(inpnam,"rb+");
				fsetpos(F,&copos[fcnt[_const_pool]+_inclp]);	fofst(F,6+8*fis[_inclp]);
				fsetpos(C,&copos[fcnt[_const_pool]+_inclp]);	fofst(C,6+8*fis[_inclp]);
				read2(F,&temp);	if(k==1){
				if(csug){fofst(F,-2);inpc(F,O,C,_method);fclose(C);goto file_end;}
				fprintf(O,"\n内:   #");	out2(O,temp);
				fprintf(O,"->#");scanf("%x",&temp);
				if(!chkc(temp,0X07)&&cchk)
					{fprintf(O,"\n不是类");
					getchar();	getchar();	fclose(C);		goto file_end;}
				}	writ2(C,&temp);
				read2(F,&temp);	if(k==2){
				if(csug){fofst(F,-2);inpc(F,O,C,_method);fclose(C);goto file_end;}
				fprintf(O,"\n外:   #");	out2(O,temp);
				fprintf(O,"->#");scanf("%x",&temp);
				if(!chkc(temp,0X07)&&cchk)
					{fprintf(O,"\n不是类");
					getchar();	getchar();	fclose(C);		goto file_end;}
				}	writ2(C,&temp);
				read2(F,&temp);	if(k==3){
				if(csug){fofst(F,-2);inpc(F,O,C,_method_name);fclose(C);goto file_end;}
				fprintf(O,"\n名:   #");	out2(O,temp);
				fprintf(O,"->#");scanf("%x",&temp);
				if(!chkc(temp,0X01)&&cchk)
					{fprintf(O,"\n不是名");
					getchar();	getchar();	fclose(C);		goto file_end;}
				}	writ2(C,&temp);
				read2(F,&temp);	if(k>=4&&k<=19)
				temp^=65536>>k-3;	writ2(C,&temp);
				fclose(C);
			}else if(key(VK_OEM_PLUS)){//add
				char s[10]={};
				if(fss[_inclp]<0){
					tpos=copos[fcnt[_const_pool]+_inclp]+6;
					s[8]=0;s[9]=0;}
				else{
				s[8]=fss[_inclp]&0XFF00;
				s[9]=fss[_inclp]&0x00FF;}
				FILE *C=fopen(inpnam,"rb+");
				fsetpos(F,&(copos[fcnt[_const_pool]+_inclp]));
				fsetpos(C,&(copos[fcnt[_const_pool]+_inclp]));
				tn=0;		read4(F,&tn);
				tn+=8;		writ4(C,&tn);
				tn=0;		read2(F,&tn);
				tn++;		writ2(C,&tn);
				fclose(C);
				finst(inpnam,tpos,s,8);
			}else if(fcnt[_inclp]>0
			&&key(VK_OEM_MINUS)){//del
				if(fss[_inclp]<0)
					tpos=copos[fcnt[_const_pool]+_inclp]+6;
				FILE *C=fopen(inpnam,"rb+");
				fsetpos(F,&(copos[fcnt[_const_pool]+_inclp]));
				fsetpos(C,&(copos[fcnt[_const_pool]+_inclp]));
				tn=0;		read4(F,&tn);
				tn-=8;		writ4(C,&tn);
				tn=0;		read2(F,&tn);
				tn--;		writ2(C,&tn);
				fclose(C);
				fdelt(inpnam,tnam,tpos,tpos+8);
			}else if(fcnt[_inclp]>=0&&keydn(VK_DELETE)&&key(VK_BACK)
			||fcnt[_inclp]==0&&key(VK_OEM_MINUS)){
				fpos_t l=fcnt[_inclp]*8+6;
				FILE *C=fopen(inpnam,"rb+");
				fsetpos(F,&copos[fcnt[_const_pool]+_file_atri]);
				fsetpos(C,&copos[fcnt[_const_pool]+_file_atri]);
				tn=0;		read2(F,&tn);
				tn--;		writ2(C,&tn);
				fclose(C);
				fdelt(inpnam,tnam,copos[fcnt[_const_pool]+_inclp]-2,copos[fcnt[_const_pool]+_inclp]+l);
				copos[fcnt[_const_pool]+_inclp]=-1;
			}
		}
//		IC/RVA
		if(showno==_rvanw&&!zab){
			stdlop(fss[_rvanp],fis[_rvanp],fcnt[_rvanp],_rvanw);
			fpos_t tpos=anos[max(fis[_rvanp],fss[_rvanp])].pos[0]-4;
			fpos_t tpo1=anos[max(fis[_rvanp],fss[_rvanp])+1].pos[0]-4;
				  if(fss[_rvanp]>0
			&&fss[_rvanp]<fcnt[_rvanp]
			&&key(VK_UP)){//go_up
				fswap(inpnam,tpos-10,tpos,tpos+10);
				if(fis[_rvanp]>0)	fis[_rvanp]--;
				fss[_rvanp]--;
			}else if(fss[_rvanp]>=0
			&&fss[_rvanp]<fcnt[_rvanp]-1
			&&key(VK_DOWN)){//go_dn
				fswap(inpnam,tpos,tpos+10,tpos+20);
				if(fis[_rvanp]<fcnt[_rvanp])	fis[_rvanp]++;
				fss[_rvanp]++;
			}else if(copos[fcnt[_const_pool]+_rvanp]>=0
			&&key(VK_OEM_PLUS)){//add
				char s[10]={0X00,0X00,0X00,0X00};
				FILE *C=fopen(inpnam,"rb+");
				fsetpos(F,&(copos[fcnt[_const_pool]+_rvanp]));
				fsetpos(C,&(copos[fcnt[_const_pool]+_rvanp]));
				tn=0;		read4(F,&tn);
				tn+=4;		writ4(C,&tn);
				tn=0;		read2(F,&tn);
				tn++;		writ2(C,&tn);
				fclose(C);
				finst(inpnam,tpos,s,4);
			}else if(fcnt[_rvanp]>0
			&&key(VK_OEM_MINUS)){//del
				FILE *C=fopen(inpnam,"rb+");
				fsetpos(F,&(copos[fcnt[_const_pool]+_rvanp]));
				fsetpos(C,&(copos[fcnt[_const_pool]+_rvanp]));
				tn=0;		read4(F,&tn);
				tn-=tpo1-tpos;		writ4(C,&tn);
				tn=0;		read2(F,&tn);
				tn--;		writ2(C,&tn);
				fclose(C);
				fdelt(inpnam,tnam,tpos,tpo1);
			}else if((fss[_rvanp]>=0
			&&fss[_rvanp]==getmousey()+fis[_rvanp]-1
			&&key(VK_LBUTTON))
			||(fss[_rvanp]==fis[_rvanp]
			&&key(VK_RETURN))){//change
				system("cls");
				FILE *C=fopen(inpnam,"rb+");
				fsetpos(F,&tpos);fsetpos(C,&tpos);
				int tn;
				rewind(stdin);	fprintf(O,"\n定义位置");tn=show2(F,O);
				fprintf(O,"->#");	scanf("%X",&tn);	writ2(C,&tn);
				fclose(C);	key(VK_RETURN);
				zab=1;
			}	if(fcnt[_rvanp]>=0&&keydn(VK_DELETE)&&key(VK_BACK)
			||fcnt[_rvanp]==0&&key(VK_OEM_MINUS)){
				fpos_t mi=copos[fcnt[_const_pool]+_file_atri];
				fpos_t l0=copos[fcnt[_const_pool]+_rvanp]-2;
				fpos_t l1=anos[fcnt[_rvanp]].pos[0]-4;
				FILE *C=fopen(inpnam,"rb+");
				fsetpos(F,&mi);
				fsetpos(C,&mi);
				tn=0;		read2(F,&tn);
				tn--;		writ2(C,&tn);
				printf("%d",tn);	fclose(C);
				fdelt(inpnam,tnam,l0,l1);
				copos[fcnt[_const_pool]+_rvanp]=-1;
			}else if(copos[fcnt[_const_pool]+_rvanp]<=0&&key(VK_OEM_PLUS)){
				fpos_t mi=copos[fcnt[_const_pool]+_file_atri];
				int ti=fndc("RuntimeVisibleAnnotations");
				FILE *C=fopen(inpnam,"rb+");
				fsetpos(F,&mi);
				fsetpos(C,&mi);
				tn=0;		read2(F,&tn);
				tn++;		writ2(C,&tn);
				fclose(C);
				char s[16]={
				0X0F,0X0F,0X00,0X00,0X00,0X02,0X00,0X00};
				s[0]=ti&0XFF00;
				s[1]=ti&0X00FF;
				finst(inpnam,mi+2,s,8);
				dbf=true;
			}
		}
#define FEND_myIDE
		file_end:
		key(VK_RETURN);
		fclose(F);	fclose(W);
		G=fopen("conf.txt","wb");
		fprintf(G,"%d %d %d\n",cchk,csug,showno);
		fprintf(G,"%s\n",typnam);fprintf(G,"%s\n",inpnam);
		fclose(G);	Z=fopen(inpnam,"r");if(Z->_file>3){system("cls");printf("file%d",Z->_file);inpnam[0]=0;}fclose(Z);
	}
}
