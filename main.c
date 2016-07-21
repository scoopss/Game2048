//
//  main.c
//  Game2048
//
//  Created by Spoorthi on 15/07/16.
//  Copyright © 2016 Spoorthi. All rights reserved.
//

/* Algorithm
 
 1. Input - Swipe value (L,R,U,D)
 2. Based on swipe value eliminate 0's and combine if same values are present
 3. Exit if all cells are filled and cannot be combined with any other cell
 
 */

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <time.h>

#define MAX 4
#define DEBUG_2048

// Print the array for debug and user input purposes
void PrintArray(int arr[MAX][MAX]){
    printf("\n");
    for(int i=0; i<4; i++){
        for(int j=0; j<4; j++){
            printf("%6d",arr[i][j]);
        }
        printf("\n");
    }
}


int CheckIfInsertionRequired(int arr[MAX][MAX], int check_arr[MAX][MAX]){
#ifndef DEBUG_2048
    printf("\n%s\n",__func__);
#endif
    for(int i=0; i<=3; i++){
        for(int j=0; j<=3; j++){
            if(arr[i][j]!=check_arr[i][j]){
                return 1;
            }
        }
    }
    
    return 0;
}

//Insert 2 or 4 randomly in a cell which contains 0
void InsertRandomValue(int arr[MAX][MAX]){
    int count=0, random_cell=0, match_count=0, random_value=0;
    time_t t;
    
#ifndef DEBUG_2048
    printf("\n%s\n",__func__);
#endif
    
    for(int i=0; i<4; i++){
        for(int j=0; j<4; j++){
            if((arr[i][j])==0){
                count++;
            }
        }
    }
    
    //TODO: Check if this is required or whether it is handled by the GameEnd condition
    if(count==0){
        return;
    }
    
    srand((unsigned) time(&t));
    random_cell = rand()%count + 1;
    random_value = rand()%2 + 1;
    for(int i=0; i<4; i++){
        for(int j=0; j<4; j++){
            if((arr[i][j])==0){
                match_count++;
                if(random_cell == match_count){
                    arr[i][j] = random_value*2;
#ifndef DEBUG_2048
                    printf("\nRandom Value = %d | Random Cell = %d %d",arr[i][j], i, j);
#endif
                }
            }
        }
    }
    return;
}




//Evaluate the Game end condition
int GameEnd(int arr[MAX][MAX]){
#ifndef DEBUG_2048
    printf("\n%s\n",__func__);
#endif
    for(int i=0; i<4; i++){
        for(int j=0; j<4; j++){
            if(arr[i][j]==0){
                return 0;
            }
        }
    }
    
    for(int i=0; i<=3; i++){
        for(int j=0; j<=3; j++){
            if(i!=3 && j!=3){
                if(arr[i][j]==arr[i][j+1] || arr[i][j]==arr[i+1][j]){
                    return 0;
                }
            }
            if(i==3 && j!=3){
                
                if(arr[i][j]==arr[i][j+1]){
                    return 0;
                }
            }
            if(j==3 && i!=3){
                if(arr[i][j]==arr[i+1][j]){
                    return 0;
                }
            }
        }
    }

    return 1;
}


//Main Program begins
int main() {
    
    
    
    printf("\nGAME 2048 BEGINS\n");
    
    int arr[MAX][MAX] = {0};
    int check_arr[MAX][MAX]={0};
    
    InsertRandomValue(arr);
    
    PrintArray(arr);
    
    
    
    while(1){
        int ret = GameEnd(arr);
        if(ret==1){
            printf("\nGAME ENDS\n");
            return 0;
        }
        
        for(int i=0; i<=3; i++){
            for(int j=0; j<=3; j++){
                check_arr[i][j]=arr[i][j];
            }
        }
        
        char user_input=0, valid_input=0;
        while(valid_input==0){
            
            printf("\nINSERT INPUT - Right=R, Left=L, Up=U, Down=D\n");
            scanf(" %c", &user_input);
            
            user_input = toupper(user_input);
            if((user_input == 'L') || (user_input == 'R') || (user_input == 'U') || (user_input == 'D')){
                valid_input = 1;
            }
            else{
                printf("Input error - Try again\n");
            }
            
        }
        
        // Switch to the respective condition with each input
        switch(user_input){
                
            //Left Input
            case 'L':
                for(int k=0; k<3; k++){
                    for(int j=0; j<3; j++){
                        for(int i=0; i<=3; i++){
                            if(arr[i][j]==0){
                                arr[i][j] = arr[i][j+1];
                                arr[i][j+1]=0;
                            }
                        }
                    }
                }
                
                for(int j=0; j<3; j++){
                    for(int i=0; i<=3; i++){
                        if(arr[i][j]==arr[i][j+1]){
                            arr[i][j] = arr[i][j] + arr[i][j+1];
                            arr[i][j+1]=0;
                        }
                    }
                }
                
                for(int j=0; j<3; j++){
                    for(int i=0; i<=3; i++){
                        if(arr[i][j]==0){
                            arr[i][j] = arr[i][j+1];
                            arr[i][j+1]=0;
                        }
                    }
                }
                if(CheckIfInsertionRequired(arr,check_arr)){
                    InsertRandomValue(arr);
                }
                PrintArray(arr);
                
                break;
                
                
            //Right Input
            case 'R':
                for(int k=0; k<3; k++){
                    for(int j=3; j>0; j--){
                        for(int i=0; i<=3; i++){
                            if(arr[i][j]==0){
                                arr[i][j] = arr[i][j-1];
                                arr[i][j-1]=0;
                            }
                        }
                    }
                }
                
                for(int j=3; j>0; j--){
                    for(int i=0; i<=3; i++){
                        if(arr[i][j]==arr[i][j-1]){
                            arr[i][j] = arr[i][j] + arr[i][j-1];
                            arr[i][j-1]=0;
                        }
                    }
                }
                
                for(int j=3; j>0; j--){
                    for(int i=0; i<=3; i++){
                        if(arr[i][j]==0){
                            arr[i][j] = arr[i][j-1];
                            arr[i][j-1]=0;
                        }
                    }
                }

                if(CheckIfInsertionRequired(arr,check_arr)){
                    InsertRandomValue(arr);
                }
                PrintArray(arr);
                
                break;
                
                
            //Up Input
            case 'U':
                for(int k=0; k<3; k++){
                    for(int i=0; i<3; i++){
                        for(int j=0; j<=3; j++){
                            if(arr[i][j]==0){
                                arr[i][j] = arr[i+1][j];
                                arr[i+1][j]=0;
                            }
                        }
                    }
                }
                
                for(int i=0; i<3; i++){
                    for(int j=0; j<=3; j++){
                        if(arr[i][j] == arr[i+1][j]){
                            arr[i][j] = arr[i][j] + arr[i+1][j];
                            arr[i+1][j] = 0;
                        }
                    }
                }
                
                for(int i=0; i<3; i++){
                    for(int j=0; j<=3; j++){
                        if(arr[i][j]==0){
                            arr[i][j] = arr[i+1][j];
                            arr[i+1][j]=0;
                        }
                    }
                }
                
                if(CheckIfInsertionRequired(arr,check_arr)){
                    InsertRandomValue(arr);
                }
                PrintArray(arr);
                
                break;
                
                
            // Down Input
            case 'D':
                for(int k=0; k<3; k++){
                    for(int i=3; i>0; i--){
                        for(int j=0; j<=3; j++){
                            if(arr[i][j]==0){
                                arr[i][j] = arr[i-1][j];
                                arr[i-1][j]=0;
                            }
                        }
                    }
                }
                
                for(int i=3; i>0; i--){
                    for(int j=0; j<=3; j++){
                        if(arr[i][j]==arr[i-1][j]){
                            arr[i][j] = arr[i][j] + arr[i-1][j];
                            arr[i-1][j]=0;
                        }
                    }
                }
                
                for(int i=3; i>0; i--){
                    for(int j=0; j<=3; j++){
                        if(arr[i][j]==0){
                            arr[i][j] = arr[i-1][j];
                            arr[i-1][j]=0;
                        }
                    }
                }
                
                if(CheckIfInsertionRequired(arr,check_arr)){
                    InsertRandomValue(arr);
                }
                PrintArray(arr);
                
                break;
                
        }
        
    }
    
}
