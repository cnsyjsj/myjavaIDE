#include"wsize.cpp"
#include"windows.h"
#include"iostream"
enum cc_sgn{
	_class_name,
	_string_text,
	_class,
	_info,
	_info_type,
	_info_name,
	_short_class,
	_short_other,
	_method,
	_method_name,
	_method_type,
	_atri_type
};
enum sh_num{
	_consw,
	_flagw,
	_confw,
	_intfw,
	_fielw,
	_methw,
	_codew,
	_exmpw,
	_trysw,
	_linsw,
	_variw,
	_endw
};
enum po_num{
	_methp,
	_codep,
	_trysp,
	_linsp,
	_varip,
	_endmp=7
};
enum fi_num{
	_fielp,
	_consp
};
enum config{
	_cchk,
	_csug,
	_tofi,
	_help,
	_opfi
};
char c2x(char c){
	if(c>='0'&&c<='9')
		return c-'0';
	else if(c>='A'&&c<='F')
		return c-'A'+10;
	else return -1;
}
//int _CPOS=0,_LPOS=0,_VPOS=0;
void copy(char *a,const char *b){
for(int i=0;b[i];i++)a[i]=b[i];}
#define dbgf do{FILE *N=fopen("bytecode.txt","rb");if(N->_file>100)	printf("XXX!!!");printf("!%d",N->_file);fclose(N);}while(0);
void stdlop(int &s,int &i,int &c,int m){
	if(key(VK_RBUTTON)||key(VK_ESCAPE))
		s=-1;
	 else if(i>0&&s<=0&&key(VK_UP))
		i--;
	 else if(i<c&&s<=0&&key(VK_DOWN))
		i++;
	 else if(s!=getmousey()+i&&
	getmousey()+i<=c-(m==_consw?1:0)&&
	getmousey()>0&&
	getmousey()<getheight()-1&&key(VK_LBUTTON))
		s=getmousey()+i-(m!=_consw?1:0);
	 else if(getmousey()==0&&key(VK_LBUTTON))
	 	{system("cls");scanf("%X",&i);}
	 else if(s!=i+(m==_consw?1:0)&&key(VK_RETURN))
		s=i+(m==_consw?1:0);
}
