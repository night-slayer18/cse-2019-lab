#include<stdio.h>
#include<stdlib.h>
#include<string.h>
void main()
{
	FILE *f1,*f2,*f3,*f4,*f5;
	int lc,sa,i=0,k=0,j=0,pgmlen,len,
	l=0;
	char name[10],opnd[10],la[10],mne[10],s1[10],mne1[10],opnd1[10];
	char lcs[10],m[10][10],s2[10];
	char sym[10],symaddr[10],obj1[10],obj2[10];
	f1=fopen("in.txt","r");
	f2=fopen("optab.txt","r");
	f3=fopen("symtab1.txt","w+");
	f4=fopen("symtab2.txt","w+");
	f5=fopen("out.txt","w+");
	fscanf(f1,"%s%s%s",la,mne,opnd);
	if(strcmp(mne,"START")==0)
	{
		sa=atoi(opnd);
		strcpy(name,la);
		lc=sa;
	}
	strcpy(s1,"*");
	fscanf(f1,"%s%s%s",la,mne,opnd);
	while(strcmp(mne,"END")!=0)
	{
		if(strcmp(la,"-")==0)
		{
			fscanf(f2,"%s%s",mne1,opnd1);
			while(!feof(f2))
			{
				if(strcmp(mne1,mne)==0)
				{
					
					fprintf(f3,"%s\t%s\n",opnd,s1);
					fprintf(f5,"%s\t%s\n",opnd1,opnd);
					lc=lc+3;
					break;
				}
				else
					fscanf(f2,"%s%s",mne1,opnd1);
			}
		}
		else
		{
			fseek(f3,SEEK_SET,0);
			fscanf(f3,"%s%s",sym,symaddr);
			while(!feof(f3))
			{	
				if(strcmp(sym,la)==0)
				{	
					sprintf(lcs,"%d",lc);
					fprintf(f4,"%s\t%s\n",la,lcs);
					if(strcmp(mne,"RESW")==0)
					lc=lc+3*atoi(opnd);
					else if(strcmp(mne,"BYTE")==0)
					{
						len=strlen(opnd);
						for(k=2;k<len-1;k++)
						{
							s2[l]=opnd[k];
							l=l+1;
						}			
						sprintf(m[i],"%s",s2);
						i=i+1;
						lc=lc+1;
					}
					else if(strcmp(mne,"RESB")==0)
						lc=lc+atoi(opnd);
					else if(strcmp(mne,"WORD")==0)
					{
						sprintf(m[i],"%s",opnd);
						//m[i][0]=opnd;
						i=i+1;
						lc=lc+3;
										
					}
					
					
					break;
				}
				else
					fscanf(f3,"%s%s",sym,symaddr);
			} 
			
		} 
		fseek(f2,SEEK_SET,0);
		fscanf(f1,"%s%s%s",la,mne,opnd);
	}
	fseek(f5,SEEK_SET,0);
	fseek(f4,SEEK_SET,0);

	pgmlen=lc-sa;
	printf("H^%s^00%d^0%d\n",name,sa,pgmlen);
	printf("T^");
	printf("00%d^0%d",sa,pgmlen);
	fscanf(f5,"%s%s",obj1,obj2);
	j=i;
	while(!feof(f5))
	{
		fscanf(f4,"%s%s",la,lcs);
		while(!feof(f4))
		{
			if(strcmp(obj2,la)==0)
			{
				printf("^%s%s",obj1,lcs);
				break;
			}
			fscanf(f4,"%s%s",la,lcs);
		}
		
			
		
		fscanf(f5,"%s%s",obj1,obj2);
		fseek(f4,SEEK_SET,0);

	}
	for(i=0;i<j;i++)
	printf("^%s",m[i]);
	printf("\nE^00%d",sa);
}
	

