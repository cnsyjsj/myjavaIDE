#include <windows.h>
#include"wsize.cpp"
#include <stdio.h>
#include"lib.cpp"
#include"me.cpp"
#include<map>
using namespace std;
const char *inpn;
#define inpnam inpn
#define tnam "waste.txt"
//#define lockname "copy ..\\java\\test\\out\\production\\test\\mainclass.class input.class"
//#define lockname "copy java.class input.class"
#define lockname "copy ..\\mods\\test\\net\\mcreator\\test\\TestMod.class input.class"
struct posln{
	fpos_t a=0;
	posln* n=0;
	int t;
};
map<int,fpos_t> copos;
map<int,posln*> cupos;
struct lstln{
	posln *a;
	lstln *n=0;
	~lstln(){
		for(;this->a;this->a=this->a->n)
			delete this->a;
	}
};
struct meth{
	fpos_t tpos[8]={};
	map <int,fpos_t> prpos;//code poses
	map <int,posln*> vupos;//var user poses
	map <int,posln*> pupos;//cod user poses
	int codei=00,trysi=00,linsi=00,varii=00,exmpi=00;//index
	int codes=-1,tryss=-1,linss=-1,varis=-1;//
	int cocnt[8]={};
} m[65536];
struct fiel{
	fpos_t tpos[8]={};
} fe[65536];
int consi=0X24,methi=0X00,fieli=0X01,showno=_fielw,conss=0X00;//s=select<window>
fpos_t flen;
int concnt;//const_cnt
bool cchk=true,csug=true,cvew=true,dbf=false;//config
void readconst(fpos_t pos,char *buf){
	r:FILE *T=fopen(inpnam,"rb+");
	if(T==0){
		fprintf(stderr,"readconst");getchar();
		fclose(T);goto r;}
	fsetpos(T,&pos);
	char c;	fscanf(T,"%c",&c);
	if(c!=1){
		fprintf(stderr,"readconst");
	buf[0]=0;fclose(T);	return;}
	us num;	read2(T,&num);
	for(int j=0;j<num;j++){	fscanf(T,"%c",buf+j);buf[j+1]=0;}
	fclose(T);
}
void repc(posln *a,us b){
	r:FILE *F=fopen(inpnam,"rb+");
	if(F==0){fprintf(stderr,"repc");getchar();goto r;}
	for(;a;a=a->n){
		fsetpos(F,&(a->a));
		if(a->t!=_short_class)
			writ2(F,&b);
		else
			fprintf(F,"%c",(unsigned char)b);
		printf("\n!%llX\n",a->a);
	}
	fclose(F);
	printf("\n");
}
void addc(int x,int k){
	for(int i=x;i<concnt-1;i++)
		repc(cupos[i],i+1);
	r:FILE *C=fopen(inpnam,"rb+");
	if(C==0){fprintf(stderr,"addc");getchar();goto r;}
	copos[0]=copos[1]-2;	fsetpos(C,&(copos[0]));
	concnt++;	writ2(C,&concnt);
	fclose(C);
	char s[16]={};	s[0]=k+1;
	char n[16]={2,0,4,4,8,8,2,2,4,4,4,4};
	finst(inpnam,copos[conss],s,n[k]+1);
}
void delc(int x){
	for(int i=x+1;i<concnt;i++)
		repc(cupos[i],i-1);
	r:FILE *C=fopen(inpnam,"rb+");
	if(C==0){fprintf(stderr,"delc");getchar();goto r;}
	copos[0]=copos[1]-2;
	fsetpos(C,&(copos[0]));
	concnt--;
	writ2(C,&concnt);
	fclose(C);
	fdelt(inpnam,tnam,copos[conss],copos[conss+1]);
}
unsigned short outv(FILE *F,FILE *O,int type,map<int,posln*> &h){
	fpos_t p;
	fgetpos(F,&p);
	unsigned short a=(type!=_short_other&&type!=_short_other)?show2(F,O):show1(F,O);
	posln *n=new posln;
	n->n=h[a];	h[a]=n;//bug
	n->a=p;		n->t=type;
	return a;
}
#define outc(F,O,t) (outv(F,O,t,cupos))
void printconst(FILE *F,FILE *O,us i,int m=1){
	if(m==2){
		for(int i=1;i<concnt;i++){
			printf("\n%+04X",i);
			printconst(F,O,i,1);
		}
		rewind(stdin);	getchar();	return;
	}
	fpos_t C;	fgetpos(F,&C);
	fsetpos(F,&(copos[i]));
	char c;fscanf(F,"%c",&c);
	switch (unsign(c)){
		case 0X01:
			fprintf(O,"文本=\t字数=");
			unsigned j;
			j=show2(F,O);	fprintf(O,"\t");
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
					break;
				}
			}
			break;
		case 0X03:
			int ti;	read4(F,&ti);
			fprintf(O,"整数=   %+08X\t=%d",ti,ti);
			break;
		case 0X04:
			float tf;	read4(F,&tf);
			fprintf(O,"小数=   %f",tf);
			break;
		case 0X05:
			long long tl;	read8(F,&tl);
			fprintf(O,"长数=   %+016llX=\t%lld",tl,tl);
			break;
		case 0X06:
			double td;	read8(F,&td);
			fprintf(O,"长小=   %lf",td);
			break;
		case 0X07:
			us tn;
			fprintf(O,"类=\t    #");	tn=outc(F,O,_class_name);
			if(m==1){fprintf(O,"\n");	printconst(F,O,tn,1);	fprintf(O,"\n");}
			break;
		case 0X08:
			fprintf(O,"字串=\t    #");	tn=outc(F,O,_string_text);
			if(m==1){fprintf(O,"\n");	printconst(F,O,tn,1);	fprintf(O,"\n");}
			break;
		case 0X09:
			fprintf(O,"字段\t类= #");	tn=outc(F,O,_class);
			if(m==1){fprintf(O,"\n");	printconst(F,O,tn,1);	fprintf(O,"\n");}
			fprintf(O,"\t函数=    #");	tn=outc(F,O,_info);
			if(m==1){fprintf(O,"\n");	printconst(F,O,tn,1);	fprintf(O,"\n");}
			break;
		case 0X0A:
			fprintf(O,"方法\t类= #");	tn=outc(F,O,_class);
			if(m==1){fprintf(O,"\n");	printconst(F,O,tn,1);	fprintf(O,"\n");}
			fprintf(O,"\t函数=    #");	tn=outc(F,O,_info);
			if(m==1){fprintf(O,"\n");	printconst(F,O,tn,1);	fprintf(O,"\n");}
			break;
		case 0X0B:
			fprintf(O,"接口\t类= #");	tn=outc(F,O,_class);
			if(m==1){fprintf(O,"\n");	printconst(F,O,tn,1);	fprintf(O,"\n");}
			fprintf(O,"\t函数=    #");	tn=outc(F,O,_info);
			if(m==1){fprintf(O,"\n");	printconst(F,O,tn,1);	fprintf(O,"\n");}
			break;
		case 0X0C:
			fprintf(O,"函数\t名字#");	tn=outc(F,O,_info_name);
			if(m==1){fprintf(O,"\n");	printconst(F,O,tn,1);	fprintf(O,"\n");}
			fprintf(O,"\t类型=    #");	tn=outc(F,O,_info_type);
			if(m==1){fprintf(O,"\n");	printconst(F,O,tn);	fprintf(O,"\n");}
			break;
		case 0X0F:
			fprintf(O,"0F文法\t名字#");	tn=outc(F,O,_short_other);
			if(m==1){fprintf(O,"\n");	printconst(F,O,tn,1);	fprintf(O,"\n");}
			fprintf(O," \t方法#");		tn=outc(F,O,_method);
			if(m==1){fprintf(O,"\n");	printconst(F,O,tn,1);	fprintf(O,"\n");}
			break;
		case 0X10:
			fprintf(O,"10字串=\t   #");	tn=outc(F,O,_class_name);
			if(m==1){fprintf(O,"\n");	printconst(F,O,tn,1);	fprintf(O,"\n");}
			break;
		case 0X12:
			fprintf(O,"12文函\t名字#");	tn=outc(F,O,_string_text);
			if(m==1){fprintf(O,"\n");	printconst(F,O,tn,1);	fprintf(O,"\n");}
			fprintf(O,"\t函数#");		tn=outc(F,O,_info);
			if(m==1){fprintf(O,"\n");	printconst(F,O,tn,1);	fprintf(O,"\n");}
			break;
		default:
			fprintf(O,"奇怪常量%X",unsign(c));
//			fscanf(F,"%c",&c);
			break;
	}
	if(m>0)	fsetpos(F,&C);
}
void inpc(FILE *F,FILE *O,FILE *C,int type){
	system("cls");
	int conti=0;us c=0;
	if(type!=_short_class)	read2(F,&c);
	else	fscanf(F,"%c",&c);
	printconst(F,O,c,1);
	fprintf(O,"\nchange?[Y/ ]");
	char tc=getchar();
	if(tc!='Y'&&tc!='y')	return;
	int a[65536]={},p=0;
	for(int i=0;i<65536;i++)
		for(posln *j=cupos[i];j;j=j->n)
			if(j->t==type){a[p++]=i;break;}//bug
	while(1){
		system("cls");
		fprintf(O,"候选V 直接输入->\n");
		for(int i=conti;i<conti+getheight()-2&&i<p;i++)
			{if(getmousey()-1==i-conti)	fprintf(O,"->");	fprintf(O,"#%+04X\n",a[i]);}
		int k=getmousey();
		if(key(VK_UP)&&conti>0)		conti--;
		if(key(VK_DOWN)&&conti<p)	conti++;
		if(key(VK_LBUTTON)||key(VK_RETURN)){
			if(key(VK_RETURN))	k=1;
			if(k+conti>p)		return;
			if(k+conti>0)		writ2(C,a+conti+k-1);
			if(k+conti==0){inpn:
				out2(O,c);	fprintf(O,"->");	scanf("%X",&c);rewind(stdin);
				key(VK_RETURN);
				if(type!=_short_class)	writ2(C,&c);
				else	fprintf(C,"%c",c);
			}	return;
		}
		if(key(VK_SHIFT))	goto inpn;
		if(key(VK_ESCAPE)||key(VK_RBUTTON))	return;
	}
}
bool chkc(int p,int t){
	r:FILE *T=fopen(inpnam,"rb+");
	if(T==0){fprintf(stderr,"chkc");getchar();goto r;}
	fsetpos(T,&(copos[p]));//bug
	char c;
	fscanf(T,"%c",&c);
	return c==t||p==0;
	fclose(T);
}
us fndc(const char c[256]){
	int ti=0;char b[256];
	for(int i=1;i<concnt;i++)
	if(chkc(i,1)){
		readconst(copos[i],b);
		if(cmp(b,"Code"))
		{ti=i;break;}
	}
	if(ti==0){
		ti=concnt;
		b[0]=1;
		for(int i=0;c[i];i++)
		{b[i+2]=c[i];b[1]=i;}
		finst(inpnam,copos[ti],b,b[1]+2);
	}	return ti;
}
void delall(){
	for(int i=1;i<concnt;i++){
		for(;cupos[i];cupos[i]=cupos[i]->n)
			delete cupos[i];}
}//bug
//=============================================
int main(int argc,char **argv){
//	inpn=argv[1];
//	hwnd=gmyhwnd();
	inpn="input.class";
	system(lockname);
	bool _tofile=false;
	FILE *E;
//	FILE *F=fopen(inpnam,"rb+");
//	if(F==0){printf("打开文件");
//	scanf("%s",inpn);}
//	fclose(F);
	while(1)	if(issel(hwnd)){
		file_start:
		system("cls");
		delall();
		FILE *F=fopen(inpnam,"rb+");
		FILE *O;
		FILE *W=fopen("waste.txt","wb");
		freopen("nothing.txt","w",stderr);
		if(F==0||W==0){	printf("打不开");getchar();continue;}
		rewind(stdin);
		//infos
		O=(showno==_flagw)?stdout:W;
		if(_tofile)	O=E;
		unsigned temp4;read4(F,&temp4);
		if(temp4!=0XCAFEBABE){printf("not a file");getchar();return 0;}
		fprintf(O,"ver:");show4(F,O);
		//infos
	#define O_CONST_myIDE
		//const
		rewind(W);
		O=(showno==_consw)?stdout:W;
		if(_tofile)	O=E;
		read2(F,&concnt);
		fprintf(O,"const:");out2(O,consi);
		fprintf(O,"/");		out2(O,getheight());
		fprintf(O,"/");		out2(O,concnt);
		for(int i=1;i<concnt;i++){
			O=(i-1<consi+getheight()-2
			&&i-1>=consi&&showno==_consw)
			?stdout:W;
			if(_tofile)	O=E;
			fprintf(O,"\n");
			if(i==conss)	fprintf(O,"[");
			if(i-consi==getmousey())	fprintf(O,"-");
			out2(O,i);
			fprintf(O,"\t");
			fgetpos(F,&(copos[i]));
			printconst(F,O,i,0);
		}
		fgetpos(F,&(copos[concnt]));
		O=(showno==_consw)?stdout:W;
//		fprintf(O,"\nconst%+04x",conss);
		//const
	#define O_FLAG_myIDE
		//flag
		rewind(W);
		O=(showno==_flagw)?stdout:W;
		if(_tofile)	O=E;
		openflagsR(F,O);
		fprintf(O,"\n我叫:   #");	outc(F,O,_class);
		fprintf(O,"\n爹是:   #");	outc(F,O,_class);
		fgetpos(F,&(copos[concnt+1]));
		//flag
		
		//debug
		rewind(W);
		O=(showno==_confw?stdout:W);
		if(_tofile)	O=W;
		fprintf(O,"常量检查=%d\n",cchk);
		fprintf(O,"常量建议=%d\n",csug);
		fprintf(O,"输出\n");
		fprintf(O,"帮助\n");
		fprintf(O,"打开文件\n");
		//debug
	#define O_INTF_myIDE
		//interface
		O=(showno==_intfw)?stdout:W;
		fprintf(O,"接口:");
		us intercnt=show2(F,O);
		fgetpos(F,&(copos[concnt+2]));
		//interface
		
		//field
		O=(showno==_fielw)?stdout:W;
		fprintf(O,"字段:");			out2(O,fieli);
		fprintf(O,"/");	us fieldcnt=show2(F,O);
		fgetpos(F,&(copos[concnt+3]));
		for(int i=0;i<fieldcnt;i++){
			fgetpos(F,&(fe[i].tpos[_fielp]));
			O=(showno==_fielw&&fieli==i)?stdout:W;
			openflagsR(F,O);
			fprintf(O,"\n名字:");outc(F,O,_string_text);
			fprintf(O,"\n类型:");outc(F,O,_info_type);
			fprintf(O,"\n附加:");us temp=show2(F,O);
			fprintf(O,"[+][*][-]");
			char buf[256];
			for(int j=0;j<temp;j++){
				readconst(copos[show2(F,W)],buf);fprintf(O,"\n-------#%X",j);
				if(cmp(buf,"ConstantValue")){
					fgetpos(F,&fe[i].tpos[_consp]);
					show4(F,W);
					mktab(O,1);	fprintf(O,"是常量:");show2(F,O);
				}
			}
		}
		//field
	#define O_METHOD_myIDE
		//method
		O=(showno==_methw)?stdout:W;
		if(_tofile)	O=E;
		fprintf(O,"方法:");			out2(O,methi);
		fprintf(O,"/");	us methocnt=show2(F,O);
		for(int i=0;i<methocnt;i++){
			rewind(W);
			for(int j=0;j<8;j++)
			{m[i].cocnt[j]=-1;m[i].tpos[j]=-1;}
			O=(showno==_methw&&methi==i)?stdout:W;
			if(_tofile)	O=E;
			fgetpos(F,&(m[i].tpos[_methp]));
			openflagsR(F,O);
			fprintf(O,"\n名字:\t#");	outc(F,O,_method_name);
			fprintf(O,"\n类型:\t#");	outc(F,O,_method_type);
			show2(F,W);
			int typ=outc(F,W,_atri_type);
			char s[256]={};readconst(copos[typ],s);
			if(cmp(s,"Code")){
	#define O_CODE_myIDE
				fgetpos(F,&(m[i].tpos[_codep]));
				fprintf(O,"\n代码");	show4(F,O);
				O=(showno==_codew&&methi==i)?stdout:W;
				fprintf(O,"栈大小=");	show2(F,O);
				fprintf(O,"\t变量数=");	show2(F,O);
				fprintf(O,"\t长度=");
				unsigned len;		len=show4(F,O);
				rewind(W);
				fprintf(O,"\n");
				FILE *T=fopen("bytecode.txt","rb");
				if(T->_file>5)	printf("398!!!");
				if(T==0){printf("T@398");return 0;}
				O=W;
				m[i].cocnt[_codep]=0;
				for(int j=0;j<len;){
					if(_tofile)	O=E;
					fgetpos(F,&(m[i].prpos[m[i].cocnt[_codep]]));
					int ct=unsign(show1(F,O));
					fpos_t tpos=(ct)*11;	fsetpos(T,&tpos);
					for(int k=0;k<9;k++){	char c;	fscanf(T,"%c",&c);	fprintf(O,"%c",c);	}
					if(ct==0X10){	show1(F,O);	j++;}
					if(ct==0X11){	show2(F,O);	j+=2;}
					if(ct==0X12){	fprintf(O,"#");	outc(F,O,_short_other);	j++;	}
					if(ct==0X13||ct==0X14){	show2(F,O);	j+=2;	}
					if(ct>=0X15&&ct<=0X19){	fprintf(O,"#");	outv(F,O,_short_other,m[i].vupos);	j++;	}
					if(ct==0X36||ct==0X38||ct==0X3A){	fprintf(O,"[");	outv(F,O,_short_other,m[i].vupos);	j++;}
					if(ct==0X84){	fprintf(O,"[");	outv(F,O,_short_other,m[i].vupos);	fprintf(O,"+");	show1(F,O);	j+=2;	}
					if(ct>=0XB2&&ct<=0XB3){	fprintf(O,"#");	outc(F,O,_info);	j+=2;	}
					if(ct>=0XB6&&ct<=0XBA){	fprintf(O,"#");	outc(F,O,_info);	j+=2;	}
					if(ct==0XBB){	fprintf(O,"#");	outc(F,O,_class);	j+=2;	}
					m[i].cocnt[_codep]++;j++;
					fprintf(O,"\n");
				}
				fgetpos(F,&(m[i].prpos[m[i].cocnt[_codep]]));
//				if(i==methi)	printf("%llX/",(m[methi].prpos[m[methi].cocnt[_codep]]));
				freopen("waste.txt","rb+",W);
				for(int j=0;j<m[i].cocnt[_codep];j++){
					char c=0;
					if(showno==_codew&&methi==i&&j>=m[i].codei&&j<m[i].codei+getheight()-2){
					if(j==m[i].codes)	printf("[");
					if(j==m[i].codei+getmousey()-1)	printf("-");}
					for(;c!='\n';){
						fscanf(W,"%c",&c);
						if(showno==_codew&&methi==i&&j>=m[i].codei&&j<m[i].codei+getheight()-2)
						printf("%c",c);
					}
				}fclose(T);
				freopen("waste.txt","wb",W);
				O=(showno==_codew&&methi==i)?stdout:W;
				fprintf(O,"%+08X/%+08X",m[i].codei,m[i].cocnt[_codep]);
				O=(showno==_methw&&methi==i)?stdout:W;
				if(_tofile)	O=E;
				fprintf(O,"\n错误处理");
				O=(showno==_trysw&&methi==i)?stdout:W;
				if(_tofile)	O=E;
				fgetpos(F,&(m[i].tpos[_trysp]));
				fprintf(O,"%+04X/",m[i].trysi);	m[i].cocnt[_trysp]=show2(F,O);
				for(int j=0;j<m[i].cocnt[_trysp];j++){
					O=(showno==_trysw&&methi==i&&j>=m[i].trysi&&j<m[i].trysi+getheight())?stdout:W;
					if(_tofile)	O=E;
					fprintf(O,"\n从  ={\t");	show2(F,O);
					fprintf(O,"\t到  ={\t");	show2(F,O);
					fprintf(O,"\t处理={\t");	show2(F,O);
					fprintf(O,"\t类别:\t");		show2(F,O);
				}
	#define O_ATRI_myIDE
				unsigned short atril;
				read2(F,&atril);
				for(int j=0;j<atril;j++){
					O=(showno==_methw&&methi==i)?stdout:W;
					if(_tofile)	O=E;
					typ=outc(F,W,_atri_type);
					readconst(copos[typ],s);
					if(cmp(s,"LineNumberTable")){
						fprintf(O,"\n行数表");
						O=(showno==_linsw&&methi==i)?stdout:W;
						fgetpos(F,&(m[i].tpos[_linsp]));show4(F,W);
						fprintf(O,"%+04X/%+04X/",m[i].linsi,m[i].linss);	m[i].cocnt[_linsp]=show2(F,O);
						for(int k=0;k<m[i].cocnt[_linsp];k++){
							O=(showno==_linsw&&methi==i&&k>=m[i].linsi&&k<m[i].linsi+getheight())?stdout:W;
							if(_tofile)	O=E;
							fprintf(O,"\n");
							if(k==m[i].linss)	fprintf(O,"[");
							if(k==getmousey()+m[i].linsi-1)	fprintf(O,"-");
							show2(F,O);	fprintf(O,"行-\t");	show2(F,O);	fprintf(O,"行");
						}
					}else
					if(cmp(s,"LocalVariableTable")){
						fprintf(O,"\n变量表");
						O=(showno==_variw&&methi==i)?stdout:W;
						fgetpos(F,&(m[i].tpos[_varip]));show4(F,W);
						fprintf(O,"%+04X/%+04X/",m[i].varii,m[i].varis);	m[i].cocnt[_varip]=show2(F,O);
						for(int k=0;k<m[i].cocnt[_varip];k++){
							O=(showno==_variw&&methi==i&&k>=m[i].varii&&k<m[i].varii+getheight())?stdout:W;
							if(_tofile)	O=E;
							fprintf(O,"\n");
							if(k==m[i].varis)	fprintf(O,"[");
							if(k==getmousey()+m[i].varii-1)	fprintf(O,"-");
							fprintf(O,"定义位置={");	show2(F,O);	fprintf(O,"\t可用长度={");	show2(F,O);
							fprintf(O,"\t名字=#");		show2(F,O);	fprintf(O,"\t类型=#");		show2(F,O);
							fprintf(O,"\t槽位=[");		outv(F,O,0,m[i].vupos);
						}
						fprintf(O,"\n%X",getmousey()+m[i].varii-1);
					}
					else{
						O=stderr;
						printf("\n:%d %d??? %s\n",i,j,s);
						fpos_t tpos;
						fgetpos(F,&tpos);
						printf("@%llX:\n",tpos);
//						return 0;
					}
				}
			}//else return 0;
//			else{	printf("\n:%d??%X %s\n",i,typ,s);fpos_t tpos;
//			fgetpos(F,&tpos);printf("@%llX:\n",tpos);getchar();return 0;}
//			fgetpos(F,&(m[i].tpos[_endmp]));
		}
		//code
		if(E)	fclose(E);
		rend:
		_tofile=false;
	#define O_EXMP_myIDE
		map<int,int> codln;
		FILE *T=fopen("bytecode_extension.txt","rb");
		O=(showno==_exmpw)?stdout:W;
		fprintf(O,"查找\n");
		for(int i=0;!feof(T);i++){
			codln[i]=1;
			fscanf(T,"%d ",&codln[i]);
			O=(showno==_exmpw&&i>=m[methi].exmpi&&i<m[methi].exmpi-2+getheight())?stdout:W;
			fprintf(O,"%+02X",i);
			char c;
			do{
				fscanf(T,"%c",&c);
					fprintf(O,"%c",c);
			}while(c!='\n');
		}fclose(T);
		O=(showno==_flagw)?stdout:W;
		us temp=show2(F,W);
		for(int i=0;i<temp;i++){
			char s[256];
			readconst(copos[show2(F,W)],s);
			if(cmp(s,"SourceFile")){
				read4(F,&temp4);
				fprintf(O,"\n源文件  #");
				outc(F,O,_string_text);
			}
		}
		fgetpos(F,&flen);
		if(!feof(F)){
		char c;fscanf(F,"%c",&c);
		if(!feof(F))fprintf(O,"\n未完待续");}
		while(!feof(F)){
			unsigned char c;
			fscanf(F,"%c",&c);
			out1(O,c);
			fpos_t tpos;
			fgetpos(F,&tpos);
			fprintf(O,"---%p\n",tpos);
		}
	#define I_CONST_myIDE
		O=stdout;
		if(showno==_consw){
		stdlop(conss,consi,concnt,_consw);
			  if(conss>0&&conss>1&&key(VK_UP)){
			repc(cupos[conss-1],conss);
			repc(cupos[conss],conss-1);
			fswap(inpnam,copos[conss-1],copos[conss],copos[conss+1]);
			conss--;
			if(consi>0)
				consi--;
		}else if(conss>0&&conss<concnt-1&&key(VK_DOWN)){
			repc(cupos[conss+1],conss);
			repc(cupos[conss],conss+1);
			fswap(inpnam,copos[conss],copos[conss+1],copos[conss+2]);
			conss++;
			if(consi<concnt)
				consi++;
		}else if((conss>0
		&&getmousey()==conss-consi&&key(VK_LBUTTON))
		||(conss==consi+1&&key(VK_RETURN))){
			system("cls");
			printconst(F,O,conss,1);printf("\nchange?[Y/ ]");
			char tc=getchar();
			if(tc!='Y'&&tc!='y')	goto file_end;
			FILE *C=fopen(inpnam,"rb+");
			fsetpos(F,&(copos[conss]));
			fsetpos(C,&(copos[conss]));
			char c;fscanf(F,"%c",&c);
			fprintf(C,"%c",c);
				switch (c){
					case 0X01:
						unsigned short len,tln;
						tln=0;
						read2(F,&len);
						fpos_t tmppos;
						fgetpos(F,&tmppos);
						char s[65536];
						for(int i=0;i<65536;i++)
							s[i]=0;
						rewind(stdin);
						for(int i=0;;i++){
							scanf("%c",s+i);
							if(s[i]=='\\'){
								scanf("%c",s+i);
								switch (s[i]) {
									case '\\':
										s[i]='\\';	break;
									case 'n':
										s[i]='\n';	break;
									case 't':
										s[i]='\t';	break;
									case 'a':
										s[i]='\a';	break;
									case 'b':
										s[i]='\b';	break;
									case 'f':
										s[i]='\f';	break;
									case 'r':
										s[i]='\r';	break;
									case 'v':
										s[i]='\v';	break;
									default:
										scanf("%X",s+i);
										break;
								}
							}
							else if(s[i]=='\n')
							{	s[i]=0;	break;}
							tln=i+1;
						}
						printf("%d\nY/N",tln);
						char c;c=getchar();
						if(c=='Y'||c=='y'){
							writ2(C,&tln);
							fdelt(inpnam,tnam,tmppos,tmppos+len);
							finst(inpnam,tmppos,s,tln);
						}
						break;
#define incn2(a,t,o) fprintf(O,a);	tn=show2(F,O);	fprintf(O,"->#");rewind(stdin);	scanf("%X",&tn);rewind(stdin);	if(!chkc(tn,t)&&cchk)	{fprintf(O,o);	getchar();	getchar();	break;}	writ2(C,&tn);
#define incn1(a,t,o) fprintf(O,a);	tc=show1(F,O);	fprintf(O,"->#");rewind(stdin);	scanf("%X",&tc);rewind(stdin);	if(!chkc(tc,t)&&cchk)	{fprintf(O,o);	getchar();	getchar();	break;}	writ1(C,&tc);
//问a 类型非t->输出o 
					case 0X03:
						int ti;		read4(F,&ti);
						fprintf(O,"%+08X=%d->",ti,ti);
						if(!scanf("%X%*2s",&ti))
							scanf("%*2s%d",&ti);
						writ4(C,&ti);	break;
					case 0X04:
						float tf;	read4(F,&tf);
						fprintf(O,"%f->",tf);
						scanf("%f",&tf);
						writ4(C,&tf);	break;
					case 0X05:
						long long tl;	read8(F,&tl);
						fprintf(O,"%+016llX=%lld->",tl);
						if(!scanf("%llX%*2s",&tl))
							scanf("%*2s%lld",&tl);
						writ8(C,&tl);	break;
					case 0X06:
						double td;
						read8(F,&td);
						fprintf(O,"%lf->",td);
						scanf("%lf",&td);
						writ8(C,&td);
						break;
					case 0X07:
						unsigned short tn;unsigned char tc;
						if(csug){inpc(F,O,C,_class_name);break;}
						incn2("类=      #",0X01,"类名 -> 文本\n");
						break;
					case 0X08:
						if(csug){inpc(F,O,C,_string_text);break;}
						incn2("字符串=  #",0X01,"字符串 -> 文本\n");
						break;
					case 0X09:
						if(csug){inpc(F,O,C,_class);inpc(F,O,C,_info);	break;}
						incn2("字段=    #",0X07,"字段 -> 类 + 函数\n");
						incn2("info=    #",0X0C,"字段 -> 类 + 函数\n");
						break;
					case 0X0A:
						if(csug){inpc(F,O,C,_class);inpc(F,O,C,_info);	break;}
						incn2("方法=    #",0X07,"方法 -> 类 + 函数\n");
						incn2("info=    #",0X0C,"方法 -> 类 + 函数\n");
						writ2(C,&tn);
						break;
					case 0X0B:
						if(csug){inpc(F,O,C,_class);inpc(F,O,C,_info);	break;}
						incn2("接口=    #",0X07,"接口 -> 类 + 函数\n");
						incn2("info=    #",0X0C,"接口 -> 类 + 函数\n");
						break;
					case 0X0C:
						if(csug){inpc(F,O,C,_info_name);inpc(F,O,C,_info_type);	break;}
						incn2("info=    #",0X01,"函数 -> 名字 + 类型\n");
						incn2("name=    #",0X01,"函数 -> 名字 + 类型\n");
						break;
					case 0X0F:
						if(csug){inpc(F,O,C,_info_name);inpc(F,O,C,_info_type);	break;}
						incn1("名字=    #",0X01,"文法 -> 名字 + 方法\n");
						incn2("方法=    #",0X0A,"文法 -> 名字 + 方法\n");
						break;
					case 0X10:
						if(csug){inpc(F,O,C,_info_name);inpc(F,O,C,_info_type);	break;}
						incn2("类名=    #",0X01,"类名 -> 文本"); 
						break;
					case 0X12:
						if(csug){inpc(F,O,C,_info_name);inpc(F,O,C,_info_type);	break;}
						incn1("名字=    #",0X01,"文函 -> 名字 + 函数\n");
						incn2("函数=    #",0X0C,"文函 -> 名字 + 函数\n");
						break;
					default:
						break;
				}
				fclose(C);
				goto file_end;
			}else if(conss>0&&key(VK_OEM_MINUS)){
 				char c;
				if(cupos[conss]){	fprintf(O,"正在用!");getchar();goto file_end;}
				if(chkc(conss,0X01)){
					rewind(stdin);
					fprintf(O,"确定?[Y/N]");
					scanf("%c",&c);
					if(c!='Y'&&c!='y')	goto file_end;
				}
				for(int i=conss+1;i<concnt-1;i++)
					repc(cupos[i],i-1);
				delc(conss);
			}else if((conss>0||concnt<1)&&key(VK_OEM_PLUS)){
				system("cls");if(concnt<1)	conss=0;
				fprintf(O,"1:文本\n2:NO/right_click\n3:整数\n4:小数\n5:长数\n6:长小\n7:类\n8:字符串\n9:字段\nA:方法\nB:接口\nC:函数\n下面:NOOOOOOOOOOOOO!!!!!!!!!!");
				int k=0;
				while(!key(VK_LBUTTON)){
					if(key('2')||key(VK_RBUTTON)||key(VK_ESCAPE))	goto file_end;
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
				}
				if(k==2||k>0X0C)	goto file_end;
				addc(conss,k);
			}
		}
	#define I_FLAG_myIDE
		if(showno==_flagw&&key(VK_LBUTTON)){
			int k=getmousey();
			FILE *C=fopen(inpnam,"rb+");
			fsetpos(F,&(copos[concnt]));
			fsetpos(C,&(copos[concnt]));
			unsigned short temp=0;
			read2(F,&temp);	if(k>=1&&k<=16)
				temp^=65536>>k;	writ2(C,&temp);
			read2(F,&temp);	if(k==17){
			if(csug){fofst(F,-2);inpc(F,O,C,_class);fclose(C);goto file_end;}
			fprintf(O,"\n我:   #");	out2(O,temp);
			fprintf(O,"->#");scanf("%x",&temp);
			if(!chkc(temp,0X07)&&cchk)
				{fprintf(O,"\n不是类");
				getchar();	getchar();	fclose(C);	goto file_end;}
			}	writ2(C,&temp);
			read2(F,&temp);	if(k==18){
			if(csug){fofst(F,-2);inpc(F,O,C,_class);fclose(C);goto file_end;}
			fprintf(O,"\n爹:   #");	out2(O,temp);
			fprintf(O,"->#");scanf("%x",&temp);
			if(!chkc(temp,0X07)&&cchk)
				{fprintf(O,"\n也不是类");
				getchar();	getchar();	fclose(C);	goto file_end;}
			}	writ2(C,&temp);
			fpos_t t=flen-2;
			fsetpos(F,&(t));
			fsetpos(C,&(t));
			read2(F,&temp);	if(k==19)
			{fprintf(O,"\n源:   #");	out2(O,temp);
			fprintf(O,"->#");scanf("%x",&temp);}
			if(!chkc(temp,0X01)&&cchk){
				fprintf(O,"\n不是文件名");
				getchar();	getchar();	fclose(C);	goto file_end;
			}	writ2(C,&temp);
			fclose(C);	goto file_end;
		}
		if(key('C'))	printconst(F,O,0,2);
		if(key(VK_LEFT)&&showno>0)	showno--;
		if(key(VK_RIGHT)&&showno<_endw)	showno++;
		if(showno==_confw){
			if(key(VK_LBUTTON)){
				int k=getmousey();
				if(k==_cchk)
					cchk=!cchk;
				if(k==_csug)
					csug=!csug;
				if(k==_tofi){	_tofile=true;
					char s[256]="output.txt";
					scanf("%s",s);
					E=fopen(s,"wb");
				}
				if(k==_help){
					system("cls");
					printf("鼠标左键选择\t右键不选\n");
					printf("输入数字时打问号可以跳过\n");
					printf("常量界面双击可展开并修改常量\n");
					printf("代码界面不能展开常量,但是C键打常量表\n");
					printf("其他界面单击展开修改\n");
					getchar();
				}
				if(k==_opfi){newf:
					printf("打开文件:");
					scanf("%s",inpn);
				}
			}
		}
	#define I_INTF_myIDE
		if(showno==_fielw){
			if(fieli>=fieldcnt)	fieli=fieldcnt-1;
			if(fieli<0)	fieli=0;
				  if(fieli>0&&key(VK_UP))
				fieli--;
			 else if(methi<fieldcnt-1&&key(VK_DOWN))
				fieli++;
			 else if(key(VK_LBUTTON)){
				int k=getmousey();
				FILE *C=fopen(inpnam,"rb+");
				fsetpos(F,&(fe[fieli].tpos[_fielp]));
				fsetpos(C,&(fe[fieli].tpos[_fielp]));
				unsigned short temp=0;
				read2(F,&temp);	if(k>=1&&k<=16)
					temp^=65536>>k;	writ2(C,&temp);
				read2(F,&temp);	if(k==17){
				if(csug){fofst(F,-2);inpc(F,O,C,_method_name);fclose(C);goto file_end;}
				fprintf(O,"\n名:   #");	out2(O,temp);
				fprintf(O,"->#");scanf("%x",&temp);
				if(!chkc(temp,0X01)&&cchk){
					fprintf(O,"\n不是名字");
					getchar();	getchar();	fclose(C);		goto file_end;}
				}	writ2(C,&temp);
				read2(F,&temp);	if(k==18){
				if(csug){fofst(F,-2);inpc(F,O,C,_method_type);fclose(C);goto file_end;}
				fprintf(O,"\n类:   #");	out2(O,temp);
				fprintf(O,"->#");scanf("%x",&temp);
				if(!chkc(temp,0X01)&&cchk){
					fprintf(O,"\n不是名字");
					getchar();	getchar();	fclose(C);		goto file_end;}
			 	}	writ2(C,&temp);
				fclose(C);
			}
		}
	#define I_METHOD_myIDE
		if(showno==_methw){
				  if(methi>0&&key(VK_UP))
				methi--;
			 else if(methi<methocnt-1&&key(VK_DOWN))
			 	methi++;
			 else if(key(VK_LBUTTON)){
				int k=getmousey();
				FILE *C=fopen(inpnam,"rb+");
				fsetpos(F,&(m[methi].tpos[_methp]));
				fsetpos(C,&(m[methi].tpos[_methp]));
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
				fsetpos(F,&(m[methi].tpos[_methp]));
				char s[256];read4(F,&temp4);
				readconst(copos[temp4&0XFFFF],s);
				if(cmp(s,"<init>"))
				{system("cls");printf("不能删init函数");	goto file_end;} 
				printf("确定?[T/F]");
				if(getchar()=='T'){
					FILE *C=fopen(inpnam,"rb+");
					fsetpos(F,&(copos[concnt+3]));
					fsetpos(C,&(copos[concnt+3]));
					int tn=0;	read2(F,&tn);
					tn--;		writ2(C,&tn);
					fclose(C);
					out4(O,m[methi].tpos[_methp]);
					out4(O,m[methi].tpos[_endmp]);
					fdelt(inpnam,tnam,m[methi].tpos[_methp],m[methi].tpos[_endmp]);
					methi--;
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
				fsetpos(F,&(copos[concnt+3]));
				fsetpos(C,&(copos[concnt+3]));
				int tn=0;	read2(F,&tn);
				tn++;		writ2(C,&tn);
				fclose(C);
				fsetpos(F,&(copos[concnt+3]));read2(F,&tn);
//				printf("OK %llX",m[methi].tpos[_endmp]);getchar();
				finst(inpnam,m[methi].tpos[_endmp],(char *)s,26);
				methi++;
			}
		}
	#define I_CODE_myIDE
		if(showno==_codew){
				 if(m[methi].codei<0)
				m[methi].codei=0;
				 if(m[methi].codei>m[methi].cocnt[_codep])
				m[methi].codei=m[methi].cocnt[_codep];
			stdlop(m[methi].codes,m[methi].codei,m[methi].cocnt[_codep],_codew);
			fpos_t tpos=m[methi].codes;
				  if(m[methi].codes>=0
			&&m[methi].codes>0
			&&key(VK_UP)){//go_up
				fswap(inpnam,m[methi].prpos[tpos-1]
							,m[methi].prpos[tpos]
							,m[methi].prpos[tpos+1]);
				if(m[methi].codei>0)	m[methi].codei--;
				m[methi].codes--;
			}else if(m[methi].codes>=0
			&&m[methi].codes<m[methi].cocnt[_codep]-1
			&&key(VK_DOWN)){//go_dn
				fswap(inpnam,m[methi].prpos[tpos]
							,m[methi].prpos[tpos+1]
							,m[methi].prpos[tpos+2]);
				if(m[methi].codei<m[methi].cocnt[_codep])	m[methi].codei++;
				m[methi].codes++;
			}else if(m[methi].codes>=0
			&&key(VK_OEM_MINUS)){//del
				FILE *C=fopen(inpnam,"rb+");
				fsetpos(F,&(m[methi].tpos[_codep]));
				fsetpos(C,&(m[methi].tpos[_codep]));
				int dt=m[methi].prpos[tpos+1]-m[methi].prpos[tpos];
				int tn=0;	read4(F,&tn);
				tn-=dt;		writ4(C,&tn);
				fpos_t cpos=m[methi].tpos[_codep]+8;
				fsetpos(F,&cpos);
				fsetpos(C,&cpos);
				tn=0;		read4(F,&tn);
				tn-=dt;		writ4(C,&tn);
				fclose(C);
				for(int i=m[methi].codes+1;i<m[methi].cocnt[_codep];i++)
					repc(m[methi].pupos[i],i-1);
				fdelt(inpnam,tnam,m[methi].prpos[tpos],m[methi].prpos[tpos+1]);
			}else if((m[methi].codes>=0
			&&m[methi].codes==getmousey()+m[methi].codei-1
			&&key(VK_LBUTTON))
			||(m[methi].codes==m[methi].codei
			&&key(VK_RETURN))){//change
				system("cls");
				FILE *C=fopen(inpnam,"rb+");
				fsetpos(F,&(m[methi].prpos[tpos]));
				fsetpos(C,&(m[methi].prpos[tpos]));
				unsigned char c[256];
				fscanf(F,"%c",c);
				printf("%d\n",codln[c[0]]);
				for(int i=1;i<codln[c[0]];i++){
					fscanf(F,"%c",c+i);
					out1(O,c[i]);
				}fprintf(O,"\n");
				unsigned char s[256];
				scanf("%s",s);
				for(int i=0,j=1;s[i]&&j<codln[c[0]];i++){
						  if(c2x(s[i])>=0&&c2x(s[i+1])>=0){
						c[j]=c2x(s[i])*16+c2x(s[i+1]);
						i++;j++;
					}else if(s[i]=='*')
						j++;
					 else{printf("不理解%c",s[i]);
						key(VK_RETURN);
						while(!key(VK_RETURN));}
				}
				for(int i=0;i<codln[c[0]];i++)
					fprintf(C,"%c",c[i]);
				fclose(C);
				key(VK_RETURN);
			}
		}
	#define I_EXMP_myIDE
		if(showno==_exmpw){
				  if(m[methi].exmpi>0&&key(VK_UP))
				m[methi].exmpi--;
			 else if(m[methi].exmpi<codln.size()&&key(VK_DOWN))
				m[methi].exmpi++;
			 else if(getmousey()>0&&getmousey()<getheight()-1&&key(VK_LBUTTON)){
				int i=m[methi].exmpi+getmousey()-1;
				if(i<203){
					char s[8]={};s[0]=i;
					long long t=m[methi].prpos[m[methi].cocnt[_codep]];
					if(m[methi].codes!=-1)
						t=m[methi].prpos[m[methi].codes];
					for(int i=m[methi].codes;i<m[methi].cocnt[_codep];i++)
						repc(m[methi].pupos[i],i+1);
					if(t<=0)	goto file_end;
					printf("\t%x\t",t);return 0;
//					printf(" %+016llX %+016llX ",m[methi].codes,t);
					finst(inpnam,t,s,codln[i]);
					if(m[methi].codes!=-1)	m[methi].codes++;
//					printf("%d",copos[0X1F00]);getchar();
					FILE *C=fopen(inpnam,"rb+");
					fsetpos(F,&(m[methi].tpos[_codep]));
					fsetpos(C,&(m[methi].tpos[_codep]));
					int dt=codln[i];
					int tn=0;	read4(F,&tn);
					tn+=dt;		writ4(C,&tn);
					fpos_t cpos=m[methi].tpos[_codep]+8;
					fsetpos(F,&cpos);
					fsetpos(C,&cpos);
					tn=0;		read4(F,&tn);
					tn+=dt+0;	writ4(C,&tn);
					fclose(C);
				}
			}else if(getmousey()==0&&key(VK_LBUTTON))
				scanf("%X",&(m[methi].exmpi));
		}
		if(showno==_trysw){
			stdlop(m[methi].tryss,m[methi].trysi,m[methi].cocnt[_trysp],_trysw);
			fpos_t tpos=m[methi].tryss*8+m[methi].tpos[_trysp]+2;
				  if(m[methi].tryss>=0
			&&m[methi].tryss<m[methi].cocnt[_trysp]
			&&key(VK_UP)){//go_up
				fswap(inpnam,tpos-8,tpos,tpos+8);
				if(m[methi].trysi>0)	m[methi].trysi--;
				m[methi].tryss--;
			}else if(m[methi].tryss>=0
			&&m[methi].tryss<m[methi].cocnt[_trysp]
			&&key(VK_DOWN)){//go_dn
				fswap(inpnam,tpos,tpos+8,tpos+16);
				if(m[methi].trysi<m[methi].cocnt[_trysp])	m[methi].trysi++;
				m[methi].tryss++;
			}else if(m[methi].tryss>=0
			&&key(VK_OEM_PLUS)){//add
				char s[8]={};
				FILE *C=fopen(inpnam,"rb+");
				fsetpos(F,&(m[methi].tpos[_codep]));
				fsetpos(C,&(m[methi].tpos[_codep]));
				int tn=0;	read4(F,&tn);
				tn+=8;		writ4(C,&tn);
				fsetpos(F,&(m[methi].tpos[_trysp]));
				fsetpos(C,&(m[methi].tpos[_trysp]));
				tn=0;		read2(F,&tn);
				tn++;		writ2(C,&tn);
				fclose(C);
				finst(inpnam,tpos,s,8);
			}else if(m[methi].tryss>=0
			&&key(VK_OEM_MINUS)){//del
				FILE *C=fopen(inpnam,"rb+");
				fsetpos(F,&(m[methi].tpos[_codep]));
				fsetpos(C,&(m[methi].tpos[_codep]));
				int tn=0;	read4(F,&tn);
				tn-=8;		writ4(C,&tn);
				fsetpos(F,&(m[methi].tpos[_trysp]));
				fsetpos(C,&(m[methi].tpos[_trysp]));
				tn=0;		read2(F,&tn);
				tn--;		writ2(C,&tn);
				fclose(C);
				fdelt(inpnam,tnam,tpos,tpos+8);
			}else if((m[methi].tryss>=0
			&&m[methi].tryss==getmousey()+m[methi].trysi-1
			&&key(VK_LBUTTON))
			||(m[methi].tryss==m[methi].trysi
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
			if(m[methi].tpos[_linsp]>=0){
			stdlop(m[methi].linss,m[methi].linsi,m[methi].cocnt[_linsp],_linsw);
			fpos_t tpos=m[methi].linss*4+m[methi].tpos[_linsp]+6;
				  if(m[methi].linss>0
			&&m[methi].linss<m[methi].cocnt[_linsp]
			&&key(VK_UP)){//go_up
				fswap(inpnam,tpos-4,tpos,tpos+4);
				if(m[methi].linsi>0)	m[methi].linsi--;
				m[methi].linss--;
			}else if(m[methi].linss>=0
			&&m[methi].linss<m[methi].cocnt[_linsp]-1
			&&key(VK_DOWN)){//go_dn
				fswap(inpnam,tpos,tpos+4,tpos+8);
				if(m[methi].linsi<m[methi].cocnt[_linsp])	m[methi].linsi++;
				m[methi].linss++;
			}else if(
			key(VK_OEM_PLUS)){//add
				if(m[methi].linss<0)
					tpos=m[methi].tpos[_linsp]+6;
				char s[4]={};
				FILE *C=fopen(inpnam,"rb+");
				fsetpos(F,&(m[methi].tpos[_codep]));
				fsetpos(C,&(m[methi].tpos[_codep]));
				int tn=0;	read4(F,&tn);
				tn+=4;		writ4(C,&tn);
				fsetpos(F,&(m[methi].tpos[_linsp]));
				fsetpos(C,&(m[methi].tpos[_linsp]));
				tn=0;		read4(F,&tn);
				tn+=4;		writ4(C,&tn);
				tn=0;		read2(F,&tn);
				tn++;		writ2(C,&tn);
				fclose(C);
				finst(inpnam,tpos,s,4);
			}else if(m[methi].cocnt[_linsp]>0
			&&key(VK_OEM_MINUS)
			){//del
				if(m[methi].linss<0)
					tpos=m[methi].tpos[_linsp]+6;
				FILE *C=fopen(inpnam,"rb+");
				fsetpos(F,&(m[methi].tpos[_codep]));
				fsetpos(C,&(m[methi].tpos[_codep]));
				int tn=0;	read4(F,&tn);
				tn-=4;		writ4(C,&tn);
				fsetpos(F,&(m[methi].tpos[_linsp]));
				fsetpos(C,&(m[methi].tpos[_linsp]));
				tn=0;		read4(F,&tn);
				tn-=4;		writ4(C,&tn);
				tn=0;		read2(F,&tn);
				tn--;		writ2(C,&tn);
				fclose(C);
				fdelt(inpnam,tnam,tpos,tpos+4);
			}else if((m[methi].linss>=0
			&&m[methi].linss==getmousey()+m[methi].linsi-1
			&&key(VK_LBUTTON))
			||(m[methi].linss==m[methi].linsi
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
			}	  if(key(VK_DELETE)&&key(VK_BACK)&&m[methi].cocnt[_linsp]>=0
			||m[methi].cocnt[_linsp]==0&&key(VK_OEM_MINUS)){
				fpos_t mi=m[methi].cocnt[_trysp]*8+m[methi].tpos[_trysp]+2;
				fpos_t l=m[methi].cocnt[_linsp]*4+6;
				FILE *C=fopen(inpnam,"rb+");
				fsetpos(F,&(m[methi].tpos[_codep]));
				fsetpos(C,&(m[methi].tpos[_codep]));
				int tn=0;	read4(F,&tn);
				tn-=l;		writ4(C,&tn);
				fsetpos(F,&mi);
				fsetpos(C,&mi);
				tn=0;		read2(F,&tn);
				tn--;		writ2(C,&tn);
				fclose(C);
				fdelt(inpnam,tnam,m[methi].tpos[_linsp]-2,m[methi].tpos[_linsp]+l);
				m[methi].tpos[_linsp]=-1;
//				}
			}else if(key(VK_OEM_PLUS)&&m[methi].tpos[_linsp]<=0){
				fpos_t mi=m[methi].cocnt[_trysp]*8+m[methi].tpos[_trysp]+2;
				fpos_t l=0;
				for(int i=3;i<8;i++)
					if(m[methi].tpos[i]>=0)
					{l=m[methi].tpos[i]-2;break;}
				char c[65536];
				int ti=0;
				for(int i=1;i<concnt;i++)
					if(chkc(i,1)){
						readconst(copos[i],c);
						if(cmp(c,"LineNumberTable"))
						{ti=i;break;}
					}
				if(ti==0){
					ti=concnt;
					char s[256]="  LineNumberTable";
					s[0]=1;	s[1]=15;
					finst(inpnam,copos[ti],s,17);
				}
				FILE *C=fopen(inpnam,"rb+");
				fsetpos(F,&(m[methi].tpos[_codep]));
				fsetpos(C,&(m[methi].tpos[_codep]));
				int tn=0;	read4(F,&tn);
				tn+=6;		writ4(C,&tn);
				fsetpos(F,&mi);
				fsetpos(C,&mi);
				tn=0;		read2(F,&tn);
				tn++;		writ2(C,&tn);
				fclose(C);
				char s[16]={
				0X0F,0X0F,0X00,0X00,
				0X00,0X02,0X00,0X00};
				s[0]=ti&0XFF00;
				s[1]=ti&0X00FF;
				printf("%llX",l);
				getchar();
				finst(inpnam,l,s,8);
				dbf=true;
			}
		}
	//lines/varib
		if(showno==_variw){
			stdlop(m[methi].varis,m[methi].varii,m[methi].cocnt[_varip],_codew);
			fpos_t tpos=m[methi].varis*10+m[methi].tpos[_varip]+6;
				  if(m[methi].varis>0
			&&m[methi].varis<m[methi].cocnt[_varip]
			&&key(VK_UP)){//go_up
				fswap(inpnam,tpos-10,tpos,tpos+10);
				if(m[methi].varii>0)	m[methi].varii--;
				m[methi].varis--;
			}else if(m[methi].varis>=0
			&&m[methi].varis<m[methi].cocnt[_varip]-1
			&&key(VK_DOWN)){//go_dn
				fswap(inpnam,tpos,tpos+10,tpos+20);
				if(m[methi].varii<m[methi].cocnt[_varip])	m[methi].varii++;
				m[methi].varis++;
			}else if(
			key(VK_OEM_PLUS)){//add
				char s[10]={};
				if(m[methi].varis<0){
					tpos=m[methi].tpos[_varip]+6;
					s[8]=0;s[9]=0;}
				else{
				s[8]=m[methi].varis&0XFF00;
				s[9]=m[methi].varis&0x00FF;}
				FILE *C=fopen(inpnam,"rb+");
				fsetpos(F,&(m[methi].tpos[_codep]));
				fsetpos(C,&(m[methi].tpos[_codep]));
				int tn=0;	read4(F,&tn);
				tn+=10;		writ4(C,&tn);
				tn=0;read2(F,&tn);writ2(C,&tn);
				tn=0;		read2(F,&tn);
				tn++;		writ2(C,&tn);
				fsetpos(F,&(m[methi].tpos[_varip]));
				fsetpos(C,&(m[methi].tpos[_varip]));
				tn=0;		read4(F,&tn);
				tn+=10;		writ4(C,&tn);
				tn=0;		read2(F,&tn);
				tn++;		writ2(C,&tn);
				fclose(C);
				for(int i=m[methi].varis;i<m[methi].cocnt[_varip];i++)
					repc(m[methi].vupos[i],i+1);
				finst(inpnam,tpos,s,10);
			}else if(m[methi].cocnt[_varip]>0
			&&key(VK_OEM_MINUS)){//del
				if(m[methi].varis<0)
					tpos=m[methi].tpos[_varip]+6;
				FILE *C=fopen(inpnam,"rb+");
				fsetpos(F,&(m[methi].tpos[_codep]));
				fsetpos(C,&(m[methi].tpos[_codep]));
				int tn=0;	read4(F,&tn);
				tn-=10;		writ4(C,&tn);
				tn=0;read2(F,&tn);writ2(C,&tn);
				tn=0;		read2(F,&tn);
				tn++;		writ2(C,&tn);
				fsetpos(F,&(m[methi].tpos[_varip]));
				fsetpos(C,&(m[methi].tpos[_varip]));
				tn=0;		read4(F,&tn);
				tn-=10;		writ4(C,&tn);
				tn=0;		read2(F,&tn);
				tn--;		writ2(C,&tn);
				fclose(C);
				for(int i=m[methi].varis+1;i<m[methi].cocnt[_varip];i++)
					repc(m[methi].vupos[i],i-1);
				fdelt(inpnam,tnam,tpos,tpos+10);
			}else if((m[methi].varis>=0
			&&m[methi].varis==getmousey()+m[methi].varii-1
			&&key(VK_LBUTTON))
			||(m[methi].varis==m[methi].varii
			&&key(VK_RETURN))){//change
				system("cls");
				FILE *C=fopen(inpnam,"rb+");
				fsetpos(F,&tpos);
				fsetpos(C,&tpos);
				int tn;
				rewind(stdin);	fprintf(O,"\n定义位置");tn=show2(F,O);
				fprintf(O,"->#");	scanf("%X",&tn);	writ2(C,&tn);
				rewind(stdin);	fprintf(O,"可用长度");	tn=show2(F,O);
				fprintf(O,"->#");	scanf("%X",&tn);	writ2(C,&tn);
				rewind(stdin);	fprintf(O,"名字=#");	tn=show2(F,O);
				fprintf(O,"\n");	printconst(F,O,tn);
				fprintf(O,"\n->#");	scanf("%X",&tn);	writ2(C,&tn);
				rewind(stdin);	fprintf(O,"类型=#");	tn=show2(F,O);
				fprintf(O,"\n");	printconst(F,O,tn);
				fprintf(O,"\n->#");	scanf("%X",&tn);	writ2(C,&tn);
				fclose(C);	key(VK_RETURN);
			}	if(key(VK_DELETE)&&key(VK_BACK)&&m[methi].cocnt[_varip]>=0
			||m[methi].cocnt[_varip]==0&&key(VK_OEM_MINUS)){
				fpos_t mi=m[methi].cocnt[_trysp]*8+m[methi].tpos[_trysp]+2;
				fpos_t l=m[methi].cocnt[_varip]*10+6;
				FILE *C=fopen(inpnam,"rb+");
				fsetpos(F,&(m[methi].tpos[_codep]));
				fsetpos(C,&(m[methi].tpos[_codep]));
				int tn=0;	read4(F,&tn);
				tn-=l;		writ4(C,&tn);
				fsetpos(F,&mi);
				fsetpos(C,&mi);
				tn=0;		read2(F,&tn);
				tn--;		writ2(C,&tn);
				printf("%d",tn);	fclose(C);
				fdelt(inpnam,tnam,m[methi].tpos[_varip]-2,m[methi].tpos[_varip]+l);
				m[methi].tpos[_varip]=-1;
			}else if(key(VK_OEM_PLUS)&&m[methi].tpos[_varip]<=0){
				fpos_t mi=m[methi].cocnt[_trysp]*8+m[methi].tpos[_trysp]+2;
				fpos_t l=0;
				for(int i=3;i<8;i++)
					if(m[methi].tpos[i]>=0)
					{l=m[methi].tpos[i]-2;break;}
				char c[65536];
				int ti=0;
				for(int i=1;i<concnt;i++)
					if(chkc(i,1)){
						readconst(copos[i],c);
						if(cmp(c,"LocalVariableTable"))
						{ti=i;break;}
					}
				if(ti==0){
					ti=concnt;
					char s[256]="  LocalVariableTable";
					s[0]=1;	s[1]=18;
					finst(inpnam,copos[ti],s,20);
				}
				FILE *C=fopen(inpnam,"rb+");
				fsetpos(F,&(m[methi].tpos[_codep]));
				fsetpos(C,&(m[methi].tpos[_codep]));
				int tn=0;	read4(F,&tn);
				tn+=6;		writ4(C,&tn);
				fsetpos(F,&mi);
				fsetpos(C,&mi);
				tn=0;		read2(F,&tn);
				tn++;		writ2(C,&tn);
				fclose(C);
				char s[16]={
				0X0F,0X0F,0X00,0X00,0X00,0X02,0X00,0X00};
				s[0]=ti&0XFF00;
				s[1]=ti&0X00FF;
				finst(inpnam,l,s,8);
				dbf=true;
			}
		}
#define FILE_END_myIDE
		file_end:
		key(VK_RETURN);
		fclose(F);	fclose(W);
		FILE *Z=fopen(inpnam,"r");
		if(Z->_file>3){system("cls");
		printf("file%d",Z->_file);
		return 0;	}fclose(Z);
	}
}
