#include "define.h"
#include "/home/hung52852/SPMM_kernel/scheduled_weight_par_8_block/schedule_weight0.h"
#include "/home/hung52852/SPMM_kernel/scheduled_weight_par_8_block/schedule_weight1.h"
#include "/home/hung52852/SPMM_kernel/scheduled_weight_par_8_block/schedule_weight2.h"
#include "/home/hung52852/SPMM_kernel/scheduled_weight_par_8_block/schedule_weight3.h"
#include "/home/hung52852/SPMM_kernel/scheduled_weight_par_8_block/schedule_weight4.h"
#include "/home/hung52852/SPMM_kernel/scheduled_weight_par_8_block/schedule_weight5.h"
#include "/home/hung52852/SPMM_kernel/scheduled_weight_par_8_block/schedule_weight6.h"
#include "/home/hung52852/SPMM_kernel/scheduled_weight_par_8_block/schedule_weight7.h"
#include "/home/hung52852/SPMM_kernel/scheduled_weight_par_8_block/schedule_weight8.h"
#include "/home/hung52852/SPMM_kernel/scheduled_weight_par_8_block/schedule_weight9.h"

using namespace std;
void print_matrix(const output_t to_print[4][48]){
    for(int i = 0; i < 4 ; i++){
        for(int j = 0 ;j < 48 ; j++){
            cout << to_print[i][j] <<" ";
        }
        cout<<"\n";
    }
}
int main(){
    ifstream infile, infile2;
    infile.open("/home/hung52852/SPMM_kernel/A_matrix.txt");
    infile2.open("/home/hung52852/SPMM_kernel/matrix.txt");
    if(!infile ){
        cout <<"open file fail!!";
        return 1;
    }
    input_t A_matrix[4][12];
    value_t B_matrix[10][12][48];
    output_t golden_matrix[10][4][48];
    output_t out_matrix[10][4][48];
    for(int i = 0; i < 4 ; i ++){
        for(int j = 0 ; j < 12 ; j++){
            infile >> A_matrix[i][j];
        }
    }
    for(int i = 0; i < 10 ; i++){
        for(int j = 0; j < 12; j++){
            for(int k = 0 ; k < 48; k++){
                infile2 >> B_matrix[i][j][k];
            }
        }
        for(int j = 0; j < 4 ; j++){
            for(int k = 0; k < 48 ; k++){
                golden_matrix[i][j][k] = 0;
            }
        }
    }
    // calculate
    for(int i = 0; i < 10 ; i++){
        for(int j = 0; j < 4 ;j ++){
            for(int k = 0 ; k < 48 ; k++){
                for(int a = 0; a < 12 ; a++){
                    golden_matrix[i][j][k] += A_matrix[j][a] * B_matrix[i][a][k];
                }
            }
        }
    }
    // cout << "A_matrix\n =============================== \n";
    // for(int i = 0; i < 4; i++){
    //     for(int j = 0 ;j < 12; j++){
    //         cout << A_matrix[i][j];
    //     }
    //     cout << "\n";
    // }
    // cout << "B_matrix\n ================================ \n";
    // for(int i = 0; i < 12; i++){
    //     for(int j = 0 ;j < 48; j++){
    //         cout << B_matrix[0][i][j];
    //     }
    //     cout <<"\n";
    // }
    // hardware cal
    for(int i = 0; i < 10; i++){
        switch(i){
            case 0:{
                cout<<i<<"th outcome\n==============================================\n";
                top_model(A_matrix, scheduled_weight0, out_matrix[i]);
                cout<<"==============================================\n";
                cout<<"golden_matrix\n";
                print_matrix(golden_matrix[0]);
                cout<<"my matrix\n";
                print_matrix(out_matrix[0]);
                break;
            }
            case 1:{
                cout<<i<<"th outcome\n==============================================\n";
                top_model(A_matrix, scheduled_weight1, out_matrix[i]);
                 cout<<"==============================================\n";
                break;
            }
            case 2:{
                cout<<i<<"th outcome\n==============================================\n";
                top_model(A_matrix, scheduled_weight2, out_matrix[i]);
                 cout<<"==============================================\n";
                break;
            }
            case 3:{
                cout<<i<<"th outcome\n==============================================\n";
                top_model(A_matrix, scheduled_weight3, out_matrix[i]);
                 cout<<"==============================================\n";
                break;
            }
            case 4:{
                cout<<i<<"th outcome\n==============================================\n";
                top_model(A_matrix, scheduled_weight4, out_matrix[i]);
                 cout<<"==============================================\n";
                break;
            }
            case 5:{
                cout<<i<<"th outcome\n==============================================\n";
                top_model(A_matrix, scheduled_weight5, out_matrix[i]);
                 cout<<"==============================================\n";
                break;
            }
            case 6:{
                cout<<i<<"th outcome\n==============================================\n";
                top_model(A_matrix, scheduled_weight6, out_matrix[i]);
                 cout<<"==============================================\n";
                break;
            }
            case 7:{
                cout<<i<<"th outcome\n==============================================\n";
                top_model(A_matrix, scheduled_weight7, out_matrix[i]);
                 cout<<"==============================================\n";
                break;
            }
            case 8:{
                cout<<i<<"th outcome\n==============================================\n";
                top_model(A_matrix, scheduled_weight8, out_matrix[i]);
                 cout<<"==============================================\n";
                break;
            }
            case 9:{
                cout<<i<<"th outcome\n==============================================\n";
                top_model(A_matrix, scheduled_weight9, out_matrix[i]);
                 cout<<"==============================================\n";
                 cout<<"golden_matrix\n";
                print_matrix(golden_matrix[9]);
                cout<<"my matrix\n";
                print_matrix(out_matrix[9]);
                break;
            }
        }
    }
    // check ans
    for(int i = 0; i < 10 ; i++){
        for(int j = 0; j < 4; j++){
            for(int k = 0; k < 48 ; k++){
                if(out_matrix[i][j][k] != golden_matrix[i][j][k]){
                    cout << "wrong ans\n";
                    cout << "golden_matrix\n==================================================\n";
                    print_matrix(golden_matrix[i]);
                    cout << "output\n ========================================================\n";
                    print_matrix(out_matrix[i]);
                    return 1;
                }
                else{
                    // cout << "golden_matrix\n==================================================\n";
                    // print_matrix(golden_matrix[i]);
                    // cout << "output\n ========================================================\n";
                    // print_matrix(out_matrix[i]);
                }   
            }
        }
    }

    return 0;
}