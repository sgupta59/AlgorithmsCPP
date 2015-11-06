// Copyright (c) 2015 Elements of Programming Interviews. All rights reserved.

#include <cassert>
#include <cmath>
#include <deque>
#include <vector>

using std::deque;
using std::vector;

bool HasDuplicate(const vector<vector<int>>&, int, int, int, int);

// @include
// Check if a partially filled matrix has any conflicts.
bool IsValidSudoku(const vector<vector<int>>& partial_assignment) {
  // Check row constraints.
  for (int i = 0; i < partial_assignment.size(); ++i) {
    if (HasDuplicate(partial_assignment, i, i + 1, 0,
                     partial_assignment.size())) {
      return false;
    }
  }

  // Check column constraints.
  for (int j = 0; j < partial_assignment.size(); ++j) {
    if (HasDuplicate(partial_assignment, 0, partial_assignment.size(), j,
                     j + 1)) {
      return false;
    }
  }

  // Check region constraints.
  int region_size = sqrt((float)partial_assignment.size());
  for (int I = 0; I < region_size; ++I) {
    for (int J = 0; J < region_size; ++J) {
      if (HasDuplicate(partial_assignment, region_size * I,
                       region_size * (I + 1), region_size * J,
                       region_size * (J + 1))) {
        return false;
      }
    }
  }
  return true;
}

// Return true if subarray partial_assignment[start_row : end_row -
// 1][start_col : end_col - 1] contains any duplicates in {1, 2, ...,
// partial_assignment.size()}; otherwise return false.
bool HasDuplicate(const vector<vector<int>>& partial_assignment, int start_row,
                  int end_row, int start_col, int end_col) {
  deque<bool> is_present(partial_assignment.size() + 1, false);
  for (int i = start_row; i < end_row; ++i) {
    for (int j = start_col; j < end_col; ++j) {
      if (partial_assignment[i][j] != 0 &&
          is_present[partial_assignment[i][j]]) {
        return true;
      }
      is_present[partial_assignment[i][j]] = true;
    }
  }
  return false;
}

bool isValidSudoku(vector<vector<int> >& board)
{
	// check all rows.
	deque<bool> values(board.size(),false);

	for (int ri = 0; ri < board.size(); ++ri)
	{
		vector<int>& row = board.at(ri);
		for (int col = 0; col < row.size(); ++col)
		{
			if (row[col] != 0 && values[col] == true)
				return false;
			if (row[col] != 0 && values[col] == false)
				values[col] = true;
		}
	}
	for (int i = 0; i < board.size(); ++i)
		values[i] = false;

	for (int ci = 0; ci < board.size(); ++ci)
	{
		for (int ri = 0; ri < board.at(ci).size(); ++ri)
		{
			if (board.at(ri)[ci] != 0 && values[ci] == true)
				return false;
			if (board.at(ri)[ci] != 0 && values[ci] == false)
				values[ci] = true;
		}
	}

	// check each sector.
	int block = 3;
	for (int i = 0; i < 9; i = i + block)
	{
		for (int j = 0; j < 9; j = j + block)
		{
			// check the block corresponding to b[i,j].
			for (int i = 0; i < board.size(); ++i)
				values[i] = false;
			int r_block = i + block;
			int c_block = j + block;
			for (int ri = i; ri < r_block; ++ri)
			{
				for (int ci = j; ci < c_block; ++ci)
				{
					if (board.at(ri)[ci] != 0 && values[ci] == true)
						return false;
					if (board.at(ri)[ci] != 0 && values[ci] == false)
						values[ci] = true;
				}
			}
			--block;
			if (block == 0)
			{
				block = 3;
				break;
			}
		}
	}
}
// @exclude

int main(int argc, char* argv[]) {
  vector<vector<int>> A(9, vector<int>(9, 0));
  int A0[10] = {0, 2, 6, 0, 0, 0, 8, 1, 0};
  int A1[10] = {3, 0, 0, 7, 0, 8, 0, 0, 6};
  int A2[10] = {4, 0, 0, 0, 5, 0, 0, 0, 7};
  int A3[10] = {0, 5, 0, 1, 0, 7, 0, 9, 0};
  int A4[10] = {0, 0, 3, 9, 0, 5, 1, 0, 0};
  int A5[10] = {0, 4, 0, 3, 0, 2, 0, 5, 0};
  int A6[10] = {1, 0, 0, 0, 3, 0, 0, 0, 2};
  int A7[10] = {5, 0, 0, 2, 0, 4, 0, 0, 9};
  int A8[10] = {0, 3, 8, 0, 0, 0, 4, 6, 0};

  A[0].insert(A[0].begin(), A0, A0+9);
  A[1].insert(A[1].begin(), A1, A1+9);
  A[2].insert(A[2].begin(), A2, A2+9);
  A[3].insert(A[3].begin(), A3, A3+9);
  A[4].insert(A[4].begin(), A4, A4+9);
  A[5].insert(A[5].begin(), A5, A5+9);
  A[6].insert(A[6].begin(), A6, A6+9);
  A[7].insert(A[7].begin(), A7, A7+9);
  A[8].insert(A[8].begin(), A8, A8+9);
  assert(IsValidSudoku(A));
  // There are two 3s.
  int A8a[10] = {3, 3, 8, 0, 0, 0, 4, 6, 0};
  A[8].clear();
   A[8].insert(A[8].begin(), A8a, A8a+9);
   
  assert(!IsValidSudoku(A));
  return 0;
}