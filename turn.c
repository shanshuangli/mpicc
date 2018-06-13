
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
   
while(!feof(fp)){
 int i=1;
    fscanf(fp,"%d",&t);
    fwrite(&t,sizeof(int),1,fq);

    fscanf(fp,"%d",&t);

    fwrite(&t,sizeof(int),1,fq);
    while(i<t+1)
    {
	fscanf(fp,"%d",&t1);
	fwrite(&t1,sizeof(int),1,fq);

        fscanf(fp,"%f",&tmp);
 
	fwrite(&tmp,sizeof(float),1,fq);
        fscanf(fp,"%f",&tmp);
	
        fwrite(&tmp,sizeof(float),1,fq);
	i++;	
    }  
}  

    fclose(fp);
    fclose(fq);

}
