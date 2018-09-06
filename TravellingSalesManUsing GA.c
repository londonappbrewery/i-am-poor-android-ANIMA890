#include <stdio.h>
#include<math.h>
#include <stdlib.h>
#include <time.h>
int sum_fitness();
void transfer_nextgen();
int chrom_selector();
void mutation();
void minfit();
void prev_fitvalues_sum();
void new_fitness_fun();
void generate_population();
void input_distance_matrix();
int random_num();
void crossover(int chrom1[],int chrom2[]);
void fitness_fun();
void rootFun(int ds[]);
int roundoff(float num);
int cities;
int distance_matrix[20][20],initial_population[100][20],fitness_values[100],next_gen[100][20],new_fitness_val[100],sumfit_old=0,sumfit_new=0;
int prev_sum[100],chrom_select,selected_chrom[100],selected_chrom_index=0,nextgen_index=0,num_of_gen=1,mindis=0,path_index;
int minRoot=0;
int minDis=0;
int mindistance[100],d=0;
void main(){
  int m ,n,chrom1[20],chrom2[20],chrom1_indx,chrom2_indx;
  time_t t;
  srand((unsigned) time(&t));
  input_distance_matrix();
//printing distance matrix
  for(m=0;m<cities;m++)
   {
     for(n=0;n<cities;n++)
       {
          printf(" %d",distance_matrix[m][n]);
       }
     printf("\n");
   }
printf("generating population----------------------\n");
 generate_population();
for(m=0;m<100;m++)
   {
     for(n=0;n<cities;n++)
       {
          printf("   %d",initial_population[m][n]);
       }
     printf("\n");
   }

//running for 100 generation
for(num_of_gen=1;num_of_gen<=100;num_of_gen++){
	selected_chrom_index=0;
	nextgen_index=0;
	sumfit_old=0;
	sumfit_new=0;
printf("--------%d generation-------",num_of_gen);
printf(" fitness of popuation----------\n");
fitness_fun();
     for(n=0;n<100;n++)
       {
          printf("      %d",fitness_values[n]);
       }
       printf("\n");

sumfit_old=sum_fitness(fitness_values);
 printf("toatal sum of fitness is : %d\n ",sumfit_old);
new_fitness_fun();
printf("new fitness values calculated using roullet wheel..............\n");
for(n=0;n<100;n++)
       {
          printf("   %d",new_fitness_val[n]);
       }

        printf("\n");
  sumfit_new=sum_fitness(new_fitness_val);
 printf("toatal sum of fitness for roullet wheel is : %d\n ",sumfit_new);      
prev_fitvalues_sum();
for(n=0;n<100;n++)
       {
          selected_chrom[n]=-1;
       }
transfer_nextgen();

// selecting chromosomes out of 40 population
for(n=0;n<40;n++){
 chrom1_indx= chrom_selector();
 chrom2_indx= chrom_selector();
 printf("\n");
 printf("\n");
printf("chromosomeIndex1  %d     \n",chrom1_indx);
printf("chromosomeIndex2  %d     \n",chrom2_indx);  
 for(m=0;m<cities;m++){
    chrom1[m]=initial_population[chrom1_indx][m];
    chrom2[m]=initial_population[chrom2_indx][m];
}

  
printf("\n");
for(m=0;m<cities;m++)
    printf("%d  ",chrom1[m]);
printf("\n");
for(m=0;m<cities;m++)
    printf("%d  ",chrom2[m]);
printf("\n");

crossover(chrom1,chrom2);
}

printf("\nselected chrome list\n");
for(m=0;m<100;m++)
  printf("   %d",selected_chrom[m]);

printf("\n");
printf("printing popultion of next genration................\n");
for(m=0;m<100;m++)
   {
     for(n=0;n<cities;n++)
       {
          printf("   %d",next_gen[m][n]);
       }
     printf("\n");
   }

mutation();
printf("\ngeneration after mutation----------\n");
for(m=0;m<100;m++)
   {
     for(n=0;n<cities;n++)
       {
          printf("   %d",next_gen[m][n]);
       }
     printf("\n");
   }
for(m=0;m<100;m++)
   {
     for(n=0;n<cities;n++)
       {
         initial_population[m][n]=next_gen[m][n];
       }
   }


printf("hello-----------Done!");
fitness_fun();
minfit();
mindistance[d++]=mindis;
printf("\n minimum distance is %d\n",mindis);
printf("and that path is-----------");
 for(n=0;n<cities;n++)
       {
         printf("  %d",initial_population[path_index][n]);
       }
 printf("\n");

}
rootFun(mindistance);
//printf("  minimum root is: %d\n", minDis);
//printf("  minimum root is: %d\n", minDis);

}//ends main here


//function to generate population
void generate_population(){
int num,temp,count=0,i,j,k;

//setting all values of initial matrix to -1
for(i=0;i<100;i++)
  {
   for(j=0;j<cities;j++)
   {
     initial_population[i][j]=-1;
}
}

//generating random number and assigning to initial population
for(i=0;i<100;i++)
  {
   for(j=0;j<cities;j++)
     {
      temp=1;
      while(temp!=0)
        {
          k=0;
         num=rand()%cities;
         for(k=0;k<cities;k++)
             {
              if(num==initial_population[i][k])
                 {
                   temp=1;
                   break;
                 }
               else
                   temp=0;
             }
         }
       initial_population[i][j]=num;
     }
  }
}




// function for generating disatance matrix
void input_distance_matrix(){
int i,j,num;
printf("enter the no. of cities    ");
scanf("%d",&cities);
for(i=0;i<cities;i++)
{
 for(j=0;j<cities;j++)
   {
     num=random_num();
     distance_matrix[i][j]=distance_matrix[j][i]=random_num();
   }
}
for(i=0;i<cities;i++)
{
     distance_matrix[i][i]=0;
}

}



//function for generating random number
int random_num(){
int num;
  num=rand()%cities+1;
 return num;
}




//function to calculate fitness of chromosomes
void fitness_fun(){
int x,y,i,j,sum;
for(i=0;i<100;i++)
  {
   sum=0;
   for(j=0;j<cities-1;j++)
     {
       x=initial_population[i][j];
       y=initial_population[i][j+1];
       sum=sum+distance_matrix[x][y];
     }
   fitness_values[i]=sum;
   }
}

void crossover(int parent1[],int parent2[]){
  int cross_point1,cross_point2,temp2=0;
  int child_chrom1[20],child_chrom2[20];
  int num,i,j,k;
for(i=0;i<cities;i++){
child_chrom1[i]=-1;
child_chrom2[i]=-1;
}
while(temp2!=1){
cross_point1=rand()%cities;
if(cross_point1==cities-1)
  temp2=0;
else
  temp2=1;
}
temp2=0;
  while(temp2!=1){
  cross_point2=rand()%cities;
  if(cross_point2==cross_point1 || cross_point2==cities-1)
     temp2=0;
  else
     temp2=1;
}
   if(cross_point1>cross_point2)
       {
         temp2=cross_point1;
         cross_point1=cross_point2;
         cross_point2=temp2;
      }

printf("\ncross1  %d      \n",cross_point1);
printf("\ncross2  %d      \n",cross_point2);
  
//generating child1 from crossover
for(i=cross_point1;i<=cross_point2;i++){
child_chrom1[i]=parent1[i];
     }
j=(cross_point2+1);
do{
 if(i==cross_point1)
     break;
 else{
     num=parent2[j];
   for(k=0;k<cities;k++){
       if(num==child_chrom1[k]){
         temp2=0;
         break;
         }
        else
          temp2=1;
    }
 if(temp2==1){
    child_chrom1[i]=num;
     i=(i+1)%cities;
  }
j=(j+1)%cities;
 }
}while(j!=cross_point2+1);
for(i=cross_point1;i<=cross_point2;i++){
child_chrom2[i]=parent2[i];
     }
j=(cross_point2+1);
do{
 if(i==cross_point1)
     break;
 else{
     num=parent1[j];
   for(k=0;k<cities;k++){
       if(num==child_chrom2[k]){
         temp2=0;
         break;
         }
        else
          temp2=1;
    }
 if(temp2==1){
    child_chrom2[i]=num;
     i=(i+1)%cities;
  }
j=(j+1)%cities;
 }
}while(j!=cross_point2+1);
for(i=0;i<cities;i++)
   printf("%d  ",child_chrom1[i]);
printf("\n");
for(i=0;i<cities;i++)
   printf("%d  ",child_chrom2[i]);


for(i=0;i<cities;i++){
  next_gen[nextgen_index][i]=child_chrom1[i];
}
nextgen_index++;
for(i=0;i<cities;i++){
  next_gen[nextgen_index][i]=child_chrom2[i];
}
nextgen_index++;

}



//calculating new fitness value using roullet wheel

void new_fitness_fun(){
int n;
float h;
for(n=0;n<100;n++)
       {
         h=(1/(fitness_values[n]*1.0))*(sumfit_old*1.0);
        new_fitness_val[n]=roundoff(h);
       }

}
//calculating sum of fitness of all chromosomes
int sum_fitness(int arr[]){
   int n,fit=0;
  for(n=0;n<100;n++)
       {
          fit=fit+arr[n];
       }
 return fit;
}


//function to calculate round off a float number
int roundoff(float num){
int x;
  x=num;
 if(num-x<0.5)
    return x;
 else
    return x+1;
}


//function to calculate sum of previous fitness at given index
void prev_fitvalues_sum(){
  int i,sum=0;
  for(i=0;i<100;i++)
     {
       sum=sum+new_fitness_val[i];
       prev_sum[i]=sum;
    }
}


//function to select a chromosome
int chrom_selector(){
   int i,j,temp1=0;
 while(temp1!=1){
   chrom_select=rand()%sumfit_new;
   for(i=0;i<99;i++)
     {
       if(prev_sum[i]>chrom_select)
        break;
     }
   for(j=0;j<100;j++)
     {
      if(selected_chrom[j]==i){
        temp1=0;
        break;
       }
      else
       temp1=1;
     }
   }
   selected_chrom[selected_chrom_index]=i;
   selected_chrom_index++;
  return i;
}

//send 20% of initial population to next generation
void transfer_nextgen(){
int i,j,temp1=0,ch;
for(i=0;i<20;i++){
  temp1=0;
 while(temp1!=1){
   ch=rand()%100;
   for(j=0;j<100;j++)
     {
      if(selected_chrom[j]==ch){
        temp1=0;
        break;
       }
      else
       temp1=1;
     }
   }
   selected_chrom[selected_chrom_index]=ch;
   selected_chrom_index++;
  for(j=0;j<cities;j++)
     next_gen[nextgen_index][j]=initial_population[i][j];
  nextgen_index++;
}
}

//function for mutation
void mutation(){
   int i,num1,num2,num3,temp=0;
 for(i=0;i<5;i++){
  num3=rand()%100;
  num1=rand()%cities;
  temp=0;
  while(temp!=1){
    num2=rand()%cities;
    if(num2==num1)
       temp=0;
    else
      temp=1;
  }
   temp=next_gen[num3][num1];
   next_gen[num3][num1]=next_gen[num3][num2];
   next_gen[num3][num2]=temp;
}
}

//function to calculate minimum fitness
void minfit()
{
int i,path_index=0;
mindis=fitness_values[0];
   for(i=1;i<100;i++){ 
    if(mindis>fitness_values[i])
    {
       mindis=fitness_values[i];
       path_index=i;
    }
    }
	//mindistance[d++]=mindis;
	
}
     //printf("  %d  %d ", mindis,path_index);
	 void rootFun(int ds[])
	 {
		 int i,j,temp;
		 //minDis=ds[i];
		 
		 //printf("\n");
		
		 for(i=0;i<d-1;i++)
		 {
			 for(j=0;j<d-1-i;j++)
			 {
				 if(ds[j]>ds[j+1])
				 {
					temp=ds[j];
					ds[j]=ds[j+1];
					ds[j+1]=temp;
				 }
			 }
		 }
		 for(i=d-2;i>=0;i--)
		 {
			 printf("  %d\n",ds[i]); 
		 }
		 
 printf("minimum root is:  %d\n",ds[0]);		 
			
		 
}

