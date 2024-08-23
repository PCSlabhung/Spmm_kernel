#ifndef _DEFINE_H_
#define _DEFINE_H_
#include <iostream>
#include <fstream>
#include "ap_fixed.h"
#include "ap_int.h"

#define MAX_NON_ZERO 46
#define IN_ROW_DIM 4
#define IN_COL_DIM 12
#define OUT_ROW_DIM 4
#define OUT_COL_DIM 48
// related to scheduling weight
#define B_MATRIX_PAR 8
#define PE_NUM 8
// related to number of row or A_matrix
#define A_MATEIX_PAR 4

typedef ap_fixed<16,8> value_t;
typedef ap_fixed<8,4> input_t;
typedef ap_fixed<8,4> output_t;
typedef ap_int<16> index_t;


constexpr int B_matrix_par_col = OUT_COL_DIM / PE_NUM;
constexpr int output_par_col_index = OUT_COL_DIM % PE_NUM;
struct weight_t{
    value_t value;
    index_t row;
    index_t col;
    weight_t& operator=(const weight_t& rhs){
        col = rhs.col;
        row = rhs.row;
        value = rhs.value;
        return *this;
    }
};
void top_model(const input_t A_matrix[IN_ROW_DIM][IN_COL_DIM],const weight_t non_zero_list[PE_NUM][MAX_NON_ZERO], output_t output_matrix[OUT_ROW_DIM][OUT_COL_DIM]);


#endif
