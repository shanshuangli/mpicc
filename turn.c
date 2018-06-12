//将数组文本文件转换为二进制文件。要求文本文件的内容：行数 列数 数组元素
#include <stdio.h>
#include <stdlib.h>

typedef float type;

int main()
{

    float tmp;
    int t,t1;
    FILE *fp,*fq;
    fp=fopen("traj_gps.txt","r");
    fq=fopen("traj_gps","wb");
    int i=1;

    fscanf(fp,"%d",&t);
fwrite(&t,sizeof(int),1,fq);
printf("%d\n",t);
    fscanf(fp,"%d",&t);
printf("%d\n",t);
fwrite(&t,sizeof(int),1,fq);
    while(i<t+1)
    {
	fscanf(fp,"%d",&t1);
	fwrite(&t1,sizeof(int),1,fq);
printf("%d\n",t1);
        fscanf(fp,"%f",&tmp);
printf("%f\n",tmp);
	fwrite(&tmp,sizeof(float),1,fq);
        fscanf(fp,"%f",&tmp);
	printf("%f\n",tmp);
        fwrite(&tmp,sizeof(float),1,fq);
	i++;	
    }    

    fclose(fp);
    fclose(fq);
    fprintf(stdout,"Successfully!\n");
}
