#include <stdio.h>  //Welcome
#include <stdlib.h>
#include <time.h>

//Course List, No of Classes per week list, Lab List, No of labs per week list
// Later the labs can be visualised as continuos classes
/*
[
 ["MAT","EVS","FDS","BEEE","MEN","HSE"]
 [                                    ]
 [                                    ]
 [                                    ]
 [                                    ]
                                       ]
*/


int Constraints(int CourseNoOfHoursPerWeek[],int MainHoursPerWeek[],int CourseNoOfHoursPerDay[],int MainHoursPerDay[],int index){
    if (CourseNoOfHoursPerWeek[index]<MainHoursPerWeek[index]){
        if (CourseNoOfHoursPerDay[index]<MainHoursPerDay[index]){
            return 1;
        }
    }
    return 0;
}

int randomPeriods(int NoOfCourses,int NoOfPeriods,int NoOfDays,int NoOfLabCourses,int FinalTimeTableIndex[][6],int CourseNoOfHoursPerWeek[],int MainHoursPerWeek[],int CourseNoOfHoursPerDay[],int MainHoursPerDay[]){   
    
    for (int i=0;i<NoOfDays;i++){
        for (int m=0;m<NoOfCourses;m++){
            CourseNoOfHoursPerDay[m]=0;
        }
        for (int j=0;j<NoOfPeriods;j++){
            //FinalTimeTable[i][j]=index i.e Index should be a valid subject index randomly selected and validated...
            // Freeballing down here
            //printf("i=%d, j=%d\n",i,j);
            if (FinalTimeTableIndex[i][j]==-1){
                int count=0;
                while (1){
                    int index=rand()%(NoOfCourses-NoOfLabCourses);
                    //printf("index=%d, i=%d, j=%d\n",index,i,j);
                    if (Constraints(CourseNoOfHoursPerWeek,MainHoursPerWeek,CourseNoOfHoursPerDay,MainHoursPerDay,index)==1){
                        FinalTimeTableIndex[i][j]=index;
                        CourseNoOfHoursPerDay[index]++;
                        CourseNoOfHoursPerWeek[index]++;
                        break;
                    }    
                    count++;
                    if (count>10000){
                        return -1;
                    }
                    /*for (int a=0;a<5;a++){
                        for(int b=0;b<6;b++){
                            int index=FinalTimeTableIndex[a][b];
                            printf("%d,",index);
                        }
                        printf("\n");
                    }
                    printf("\n");
                    */
                }
   
            } 
        }
            
            
    }
    return 1;
}

int randomAllotment(char main_courses[][10],int MainHoursPerWeek[],int FinalTimeTableIndex[][6],int MainHoursPerDay[]){
    int NoOfCourses=11; //Change Varaibles
    int NoOfPeriods=6;
    int NoOfDays=5;
    int NoOfLabCourses=3;
    int Lunch_index=4;



    int LabHoursPerWeek[NoOfLabCourses];
    for (int i=0;i<NoOfLabCourses;i++){
        LabHoursPerWeek[i]=MainHoursPerWeek[NoOfCourses-NoOfLabCourses+i];
    }
    int CourseNoOfHoursPerWeek[NoOfCourses];
    int CourseNoOfHoursPerDay[NoOfCourses];
    for (int i=0;i<NoOfCourses;i++){
        CourseNoOfHoursPerWeek[i]=0;
        CourseNoOfHoursPerDay[i]=0;
    }
    int LabHours[NoOfLabCourses];
    for (int i=0;i<NoOfLabCourses;i++){
        LabHours[i]=0;
    }
    int LabHoursWeek[NoOfDays];
    for (int i=0;i<NoOfDays;i++){
        LabHoursWeek[i]=0;
    }
    int LabHoursCount=0;
    int TotalLabHours=0;
    for (int i=0;i<NoOfDays;i++){
        for (int j=0;j<NoOfPeriods;j++){
            FinalTimeTableIndex[i][j]=-1;
        }
    }

    /*for (int a=0;a<5;a++){
        for(int b=0;b<6;b++){
            int index=FinalTimeTableIndex[a][b];
            printf("%d,",index);
        }
        printf("\n");
    }
    printf("\n");
    */

    for (int i=0;i<NoOfLabCourses;i++){
        TotalLabHours+=LabHoursPerWeek[i];
    }
    
    while (LabHoursCount<TotalLabHours){
        int index_col=rand()%NoOfPeriods;
        int index_row=(rand())%NoOfDays;
        int index=rand()%NoOfLabCourses;
        if (LabHours[index]==0){
            if (LabHoursWeek[index_row]==0){
                if (((Lunch_index-index_col)>=LabHoursPerWeek[index])||((index_col)-Lunch_index>=LabHoursPerWeek[index])){
                    for (int i=0;i<LabHoursPerWeek[index];i++){
                        FinalTimeTableIndex[index_row][index_col+i]=index+NoOfCourses-NoOfLabCourses;
                    }
                    LabHours[index]=LabHoursPerWeek[index];
                    LabHoursCount+=LabHours[index];
                    LabHoursWeek[index_row]=1;
                }
            }
        }

    }
    /*
    for (int a=0;a<5;a++){
        for(int b=0;b<6;b++){
            int index=FinalTimeTableIndex[a][b];
            printf("%d,",index);
        }
        printf("\n");
    }
    printf("\n");
    */
    int Copy_FinalTimeTableIndex[NoOfDays][NoOfPeriods];
    for (int i=0;i<NoOfDays;i++){
        for (int j=0;j<NoOfPeriods;j++){
            Copy_FinalTimeTableIndex[i][j]=FinalTimeTableIndex[i][j];
        }
    }

    int Number=randomPeriods(NoOfCourses,NoOfPeriods,NoOfDays,NoOfLabCourses,FinalTimeTableIndex,CourseNoOfHoursPerWeek,MainHoursPerWeek,CourseNoOfHoursPerDay,MainHoursPerDay);
    //printf("Number=%d\n",Number);
    int mycount=0;
    
    while (Number==-1){
        for (int i=0;i<NoOfDays;i++){
            for (int j=0;j<NoOfPeriods;j++){
                FinalTimeTableIndex[i][j]=Copy_FinalTimeTableIndex[i][j];
            }
        }
        for (int i=0;i<NoOfCourses;i++){
            CourseNoOfHoursPerWeek[i]=0;
        }
        Number=randomPeriods(NoOfCourses,NoOfPeriods,NoOfDays,NoOfLabCourses,FinalTimeTableIndex,CourseNoOfHoursPerWeek,MainHoursPerWeek,CourseNoOfHoursPerDay,MainHoursPerDay);
        
        //mycount++;
        //printf("Try no: %d\n",mycount);
    }

}

int main(){
    srand(time(0));
    printf("Enter no of Classes: ");
    int NoOfClasses=0;
    scanf("%d",&NoOfClasses);
    
    printf("Started\n");
    for (int num=0;num<NoOfClasses;num++){
        char main_courses[][10]={"MAT ","EVS ","FDS ","FPSD","BEEE","MEN ","SPR ","HSE ","Lab-FPSD","Lab-HSE","Lab-EPL"};
        int MainHoursPerWeek[]={5,3,3,3,4,1,1,2,3,2,3};
        int MainHoursPerDay[]= {2,1,1,1,1,1,1,1,3,2,3};
        int FinalTimeTableIndex[5][6];
        
        randomAllotment(main_courses,MainHoursPerWeek,FinalTimeTableIndex,MainHoursPerDay);
        /*
        for (int i=0;i<11;i++){
            printf("%d: %s, ",i,main_courses[i]);
        }

        printf("\n\n");


        for (int i=0;i<5;i++){
            for(int j=0;j<6;j++){
                int index=FinalTimeTableIndex[i][j];
                printf("%d,",index);
                }
            printf("\n");
            
        }
        printf("\n\n");

        */
        printf("TimeTable: %d\n\n",num+1);

        char WeekDays[5][3]={{'M','O','N'},{'T','U','E'},{'W','E','D'},{'T','H','U'},{'F','R','I'}};
        for (int i=0;i<5;i++){
            for (int k=0;k<3;k++){
                printf("%c",WeekDays[i][k]);
            }
            printf(": ");
            for(int j=0;j<6;j++){
                int index=FinalTimeTableIndex[i][j];
                if (index!=-1){
                    printf("%s,",main_courses[index]);
                }else{
                    printf("%s,","---");
                }
            }
            printf("\n");
        }
        printf("\n");
    }
    printf("Done!");

    
    
}