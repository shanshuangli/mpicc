#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include"mpi.h"
#include <sys/time.h>

typedef struct {
	float x;
	float y;
	int time;
}Point;
int max=1;
int main(int argc, char *argv[])
{
    int size,rank,num=0,i=1;
    int m,offset=sizeof(int);
    float *array;

    double usec;

    struct timeval start, end;
    MPI_File fh;
    MPI_Status status;
    MPI_Init(&argc,&argv);
    MPI_Comm_rank(MPI_COMM_WORLD,&rank);
    MPI_Comm_size(MPI_COMM_WORLD,&size);

    gettimeofday( &start, NULL );

    MPI_File_open(MPI_COMM_WORLD,"traj_gps",MPI_MODE_RDONLY,MPI_INFO_NULL,&fh);
      
	int mytrajsize=max/(size-1);
	
	if(rank=0)
	{
		while(i<size){
			MPI_File_read_at_all(fh,offset,&m,1,MPI_INT,&status);
			if(num%mytrajsize==0){
				MPI_Send(&offset,1,MPI_INT,i,99,MPI_COMM_WORLD);
				i++;
			}
			offset=offset+m*(sizeof(int)+2*sizeof(float))+sizeof(int);
			num++;
		}
		
	}
	else
	{
		if(rank=size){
			mytrajsize+=max%(size-1);
		}
		MPI_Recv(&offset,1,MPI_INT,0,99,MPI_COMM_WORLD,&status);
		while(num<mytrajsize){
			MPI_File_read_at_all(fh,offset,&m,1,MPI_INT,&status);
			offset=offset+sizeof(int);
			Point p[m];
			for(int j=0;j<m;j++){
				MPI_File_read_at_all(fh,offset,&p[j].time,1,MPI_INT,&status);
				MPI_File_read_at_all(fh,offset+sizeof(int),&p[j].x,1,MPI_INT,&status);
				MPI_File_read_at_all(fh,offset+sizeof(int)+sizeof(float),&p[j].y,1,MPI_INT,&status);
				offset=offset+sizeof(int)+sizeof(float)*2;
			}
			printf("%d, %f, %f",p[0].time,p[0].x,p[0].y);
			num++;
		}
		
	}
	
    
    MPI_File_close(&fh);
    gettimeofday( &end, NULL );
    usec = 1000000 * ( end.tv_sec - start.tv_sec ) + end.tv_usec - start.tv_usec;
    usec /= 1000000;

    printf("Duration of process %2d is %10.6lf.\n\r", rank, usec);
	


    MPI_Finalize();
    return 0;
}

