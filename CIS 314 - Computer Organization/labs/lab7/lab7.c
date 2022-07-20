// Cole Pendergraft


void g(int **arr, int *res) {
    *res = 0; // movq $0, (%res)
    for (int j = 0; j < numColumns(arr); ++j) {
        for (int i = 0; i < numRows(arr); ++i) {
            *res &= arr[i][0] + arr[i][j];
        }
    }
}

void g(int **arr, int *res){
  int result = 0;
  int rows = numRows(arr);
  int cols = numColumns(arr);

  for (int j = 0; j < cols; ++j) {
    int rowVal = arr[i][0];
      for (int i = 0; i < rows; ++i) {
          //result &= rowVal + arr[i][j]; // ( arr + i * cols + j )
          //row++;
          result &= rowVal + arr[i][j]
          //result &= rowVal + *row++;
      }
  }
*res = result;
}
