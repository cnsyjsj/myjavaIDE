#include<cstdio>
#include"../lib.cpp"
int main(int argc,char **argv){
//	printf("%c",argv[1][0]);
	if(argv[1][0]=='0'){
		int i,li,ri;
		for(i=0;argv[2][i];i++)
		if(argv[2][i]=='.')ri=i;
		if(ri==0)	ri=i+1;
		for(;argv[2][i]!='\\'&&i>=0;i--);
		li=i+1;
		printf("%d %d ",li,ri);
		char c[256]="java ";i=5;
		for(;li!=ri;i++,li++)
		c[i]=argv[2][li];
		printf("%s",c);
		system(c);
	}if(argv[1][0]=='1'){
		FILE *F=fopen(argv[2],"rb");
		while(!feof(F)){
			uc c;do{
			fscanf(F,"%c",&c);
			}while(c!=1&&!feof(F));
			fpos_t t,y;us n;read2(F,&n);
			fgetpos(F,&t);
			y=ffind(F,argv[3],strlen(argv[3]));
			if(y<=0||t<=0)	return 0;
			printf("%X %X \n",t,y);
			fsetpos(F,&t);bool f=1;
			for(int i=t;i<y;i++){
				fscanf(F,"%c",&c);
			if(!canprint(c))f=0;}
			if(f)	printf("OK\n");
			if(f){fclose(F);
				fdelt(argv[2],"..\\waste.txt",y,y+strlen(argv[3]));
				finst(argv[2],y,argv[4],strlen(argv[4]));
				n+=strlen(argv[4])-strlen(argv[3]);
				FILE *O=fopen(argv[2],"rb+");t-=2;fsetpos(O,&t);
				writ2(O,&n);fclose(O);F=fopen(argv[2],"rb");fsetpos(F,&t);
			}fsetpos(F,&t);
		}
		char c[256],s[256];	int ri;
		for(int i=0;argv[2][i];i++)
		if(argv[2][i]=='.')	ri=i+1;
		sprintf(c,"rename \"%s\" \"%s%s\"",argv[2],argv[4],argv[2]+ri);
		system(c);
	}
}
