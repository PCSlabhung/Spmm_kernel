/*
this program handle partition version of schedule weight
you can input your favor partition factor
output will be stored in folder : scheduled_weight_(partition_factor)
*/
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>
#include <iomanip>
// check true max non_zero and modify here
#define MAX_NON_ZERO 46
using namespace std;
struct Schedule_data{
	int row;
	int col;
	float value;
};
int find_non_zero(float matrix[12], int start_index){
	bool flag = 0;
	for(int i = start_index + 1; i < 12; i++){
		if(matrix[i] != 0){
			return i;
		}
	}
	return -1;
}
void schedule(const float matrix[12][48], int par_factor, int code, ofstream& outfile){
	Schedule_data **schedule_matrix = new Schedule_data*[par_factor];
	for(int i = 0; i < par_factor; i++){
		schedule_matrix[i] = new Schedule_data[MAX_NON_ZERO];
	}
	
	int col_non_zero[48];
	for(int i = 0; i < 48 ; i++){
		int flag = 0;
		for(int j = 0 ; j < 12; j++){
			if(matrix[j][i] != 0){
				flag = 1;
				col_non_zero[i] = j;
				break; 
			}
		}
		if(flag == 0){
			col_non_zero[i] = -1;
		}
	}
	cout << "finish finding first non-zero\n";
	int *cur_col_index = new int[par_factor];
	int *cur_row_index = new int[par_factor];
	int *total_non_zero = new int[par_factor];
	for(int i = 0; i < par_factor; i++){
		total_non_zero[i] = 0;
		int flag = 0;
		for(int j = i; j < 48; j += par_factor){
			if(col_non_zero[j] != -1){
				cur_col_index[i] = j;
				cur_row_index[i] = col_non_zero[j];
				flag = 1;
				break;
			}
		}
		if(flag == 0){
			cur_col_index[i] = i;
			cur_row_index[i] = 0;
		}
	}
	for(int i = 0 ; i <  par_factor ; i++){
		cout<<cur_col_index[i] <<" "<<cur_row_index[i] << endl;
	}
	// start scheduling
	for(int i = 0; i < par_factor;i++){
		int non_zero_index = 0;
		while(true){
			cout<<"cur col = "<<cur_col_index[i]<<" cur row = "<<cur_row_index[i]<<endl;
			schedule_matrix[i][non_zero_index].col = cur_col_index[i];
			schedule_matrix[i][non_zero_index].row = cur_row_index[i];
			schedule_matrix[i][non_zero_index].value = matrix[cur_row_index[i]][cur_col_index[i]];
			float this_col[12];
			for(int j = 0 ; j < 12 ; j++){
				this_col[j] = matrix[j][cur_col_index[i]];
			}
			col_non_zero[cur_col_index[i]] = find_non_zero(this_col, cur_row_index[i]);
			int row_index = 0;
			int col_index = 0;
			bool flag = 0;
			// find the non_zero from col_index = cur_col_index + par_factor , cur_col_index + par_factor * 2, 48
			for(int j = cur_col_index[i] + par_factor; j < 48 ; j += par_factor){
				if(col_non_zero[j] != -1){
					row_index = col_non_zero[j];
					col_index = j;
					flag = 1;
					break;
				}
			}
			// find the non_zero from col_index = i, i + par_factor ~ cur_col_index - par_factor
			if(flag == 0){
				for(int j = i; j < cur_col_index[i]; j+= par_factor){
					if(col_non_zero[j] != -1){
						row_index = col_non_zero[j];
						col_index = j;
						flag = 1;
						break;
					}
				}
			}
			// find the non zero col_index = cur_col_index
			if(flag == 0){
				if(col_non_zero[cur_col_index[i]] != -1){
					row_index = col_non_zero[cur_col_index[i]];
					col_index = cur_col_index[i];
					flag = 1;
				}
				else{
					break;
				}
			}
			cur_col_index[i] = col_index;
			cur_row_index[i] = row_index;
			non_zero_index ++;
			cout<<i<<"th matrix"<<"next row = "<<cur_row_index[i]<<"next col = "<<cur_col_index[i]<<endl;	
		}
	}
	cout<< "output stage\n";
	// output 
	outfile << "#ifndef _SCHEDULED_WEIGHT_H" + to_string(code) + "_\n";
	outfile << "#define _SCHEDULED_WEIGHT_H" + to_string(code) + "_\n";
	outfile << "#include \"define.h\" \n";
	outfile << "B_value scheduled_weight" + to_string(code) + "[4]" + "[" + to_string(par_factor) + "]" + "[46] = {";
	for(int k = 0; k < 4 ; k++){
		outfile << "{";
		for(int i = 0; i < par_factor; i++){
			outfile << "{";
			for(int j = 0; j < MAX_NON_ZERO; j++){
				if(j != MAX_NON_ZERO - 1){
					outfile << "{" << schedule_matrix[i][j].value << ","<<schedule_matrix[i][j].row<<","<<schedule_matrix[i][j].col<<"},\n";
				}
				else{
					outfile << "{" << schedule_matrix[i][j].value << ","<<schedule_matrix[i][j].row<<","<<schedule_matrix[i][j].col<<"}\n";
				}
			}
			if(i == par_factor - 1){
				outfile <<"}\n";
			}
			else{
				outfile <<"},\n";
			}
		}
		if(k == 3){
			outfile <<"}\n";
		}
		else{
			outfile <<"},\n";
		}
	}
	outfile << "};\n";
	outfile <<"#endif";
	cout<<"finish\n";
}
void schedule_block(float matrix[12][48], int par_factor, int code, ofstream& outfile){
	Schedule_data **schedule_matrix = new Schedule_data*[par_factor];
	for(int i = 0; i < par_factor; i++){
		schedule_matrix[i] = new Schedule_data[MAX_NON_ZERO];
	}
	for(int i = 0; i < par_factor; i++){
		for(int j = 0 ; j < MAX_NON_ZERO; j++){
			schedule_matrix[i][j] = {0,0,0};
		}
	}
	int col_non_zero[48];
	for(int i = 0; i < 48 ; i++){
		int flag = 0;
		for(int j = 0 ; j < 12; j++){
			if(matrix[j][i] != 0){
				flag = 1;
				col_non_zero[i] = j;
				break; 
			}
		}
		if(flag == 0){
			col_non_zero[i] = -1;
		}
	}
	for(int i = 0; i < 48 ; i++){
		cout << col_non_zero[i] <<" ";
		if(i % 6 == 0 && i != 0){
			cout << endl;
		}
	}
	cout << "finish finding first non-zero\n";
	int *cur_col_index = new int[par_factor];
	int *cur_row_index = new int[par_factor];
	int *total_non_zero = new int[par_factor];
	for(int i = 0; i < par_factor; i++){
		total_non_zero[i] = 0;
		int flag = 0;
		for(int j = i * 48 / par_factor; j < i * 48 / par_factor + 48 / par_factor; j ++){
			if(col_non_zero[j] != -1){
				cur_col_index[i] = j;
				cur_row_index[i] = col_non_zero[j];
				flag = 1;
				break;
			}
		}
		if(flag == 0){
			cur_col_index[i] = i;
			cur_row_index[i] = 0;
		}
	}
	for(int i = 0; i < par_factor; i++){
		cout<< "cur col index = "<<cur_col_index[i] << "cur row index = "<<cur_row_index[i]<<endl;
	}
	cout<< "finish setting col & row index\n";
	// start scheduling
	for(int i = 0; i <  par_factor;i++){
		int non_zero_index = 0;
		while(true){
			if(matrix[cur_row_index[i]][cur_col_index[i]] == 0){
				break;
			}
			cout<<i<<"th matrix"<<"next row = "<<cur_row_index[i]<<"next col = "<<cur_col_index[i]<<" ";
			cout<<"value = "<<matrix[cur_row_index[i]][cur_col_index[i]]<<endl;	
			schedule_matrix[i][non_zero_index].col = cur_col_index[i];
			schedule_matrix[i][non_zero_index].row = cur_row_index[i];
			schedule_matrix[i][non_zero_index].value = matrix[cur_row_index[i]][cur_col_index[i]];
			float this_col[12];
			for(int j = 0 ; j < 12 ; j++){
				this_col[j] = matrix[j][cur_col_index[i]];
			}
			col_non_zero[cur_col_index[i]] = find_non_zero(this_col, cur_row_index[i]);
			int row_index = 0;
			int col_index = 0;
			bool flag = 0;
			// find the non_zero from col_index = cur_col_index ~ i + par_factor
			for(int j = cur_col_index[i] + 1; j < i * 48 / par_factor + 48  / par_factor ; j ++){
				if(col_non_zero[j] != -1){
					row_index = col_non_zero[j];
					col_index = j;
					flag = 1;
					break;
				}
			}
			// find the non_zero from col_index = i, cur_col_index - 1
			if(flag == 0){
				for(int j = i * 48 / par_factor; j < cur_col_index[i]; j++){
					if(col_non_zero[j] != -1){
						row_index = col_non_zero[j];
						col_index = j;
						flag = 1;
						break;
					}
				}
			}
			// find the non zero col_index = cur_col_index
			if(flag == 0){
				if(col_non_zero[cur_col_index[i]] != -1){
					row_index = col_non_zero[cur_col_index[i]];
					col_index = cur_col_index[i];
					flag = 1;
				}
				else{
					break;
				}
			}
			cur_col_index[i] = col_index;
			cur_row_index[i] = row_index;
			non_zero_index ++;
		
		}
		cout << "finish"<<i<<"th round\n";
	}
	for(int i = 0; i < par_factor; i++){
		for(int j = 0; j < MAX_NON_ZERO; j++){
			cout << schedule_matrix[i][j].row <<" "<< schedule_matrix[i][j].col <<" "<< schedule_matrix[i][j].value<<" " ;
		}
		cout << endl;
	}
	// output 
	outfile << "#ifndef _SCHEDULED_WEIGHT_H" + to_string(code) + "_\n";
	outfile << "#define _SCHEDULED_WEIGHT_H" + to_string(code) + "_\n";
	outfile << "#include \"define.h\" \n";
	outfile << "weight_t scheduled_weight" + to_string(code)  + "[" + to_string(par_factor) + "]" + "[46] = {";
	//for(int k = 0; k < 4 ; k++){
		//outfile << "{";
		for(int i = 0; i <  par_factor; i++){
			outfile << "{";
			for(int j = 0; j < MAX_NON_ZERO; j++){
				if(j != MAX_NON_ZERO - 1){
					outfile << "{" << schedule_matrix[i][j].value << ","<<schedule_matrix[i][j].row<<","<<schedule_matrix[i][j].col<<"},\n";
				}
				else{
					outfile << "{" << schedule_matrix[i][j].value << ","<<schedule_matrix[i][j].row<<","<<schedule_matrix[i][j].col<<"}\n";
				}
			}
			if(i == par_factor - 1){
				outfile <<"}\n";
			}
			else{
				outfile <<"},\n";
			}
		}
//		if(k == 3){
//			outfile <<"}\n";
//		}
//		else{
//			outfile <<"},\n";
//		}
	//}
	outfile << "};\n";
	outfile <<"#endif";
	
}
int main(){
	cout << " how many parts do you want to seperate ?? 4 / 6 / 8\n";
	int partition;
	cin >> partition;
	ifstream infile, infile2;
	ofstream outfile, outfile2;
	string dir_path = "scheduled_weight_par_" + to_string(partition);
	infile.open("matrix.txt");
	
	float B_matrix[10][12][48];
	for(int i = 0; i < 10 ; i++){
		for(int j = 0; j < 12 ;j++){
			for(int k = 0 ; k < 48 ; k++){
				infile >> B_matrix[i][j][k]; 
			}
		}
	}
//	for(int i = 0; i < 10; i++){
//		string path = "scheduled_weight_par_4_block/schedule_weight" + to_string(i) + ".h"; 
//		outfile.open(path);
//		//schedule(B_matrix[i], 4, i, outfile);
//		schedule_block(B_matrix[i], 4, i,outfile);
//		outfile.close();
//	}
//	for(int i = 0; i < 10; i++){
//		string path = "scheduled_weight_par_6_block/schedule_weight" + to_string(i) + ".h"; 
//		outfile.open(path);
//		//schedule(B_matrix[i], 6, i, outfile);
//		schedule_block(B_matrix[i], 6, i, outfile);
//		outfile.close();
//	}
//	cout << "finish par 4 & par 6\n";
//	for(int i = 0; i < 10; i++){
//		string path = "scheduled_weight_par_8_block/schedule_weight" + to_string(i) + ".h"; 
//		outfile.open(path);
//		//schedule(B_matrix[i], 8, i, outfile);
//		schedule_block(B_matrix[i], 8, i, outfile);
//		outfile.close();
//		cout<<i<<"th .h file completed\n";
//	}
	string path = "scheduled_weight_par_8_block/schedule_weight" + to_string(0) + ".h";
	outfile.open("path");
	schedule_block(B_matrix[0], 8, 0, outfile);
	outfile.close();
	cout<<0<<"th .h file completed\n";
	return 1;
}
