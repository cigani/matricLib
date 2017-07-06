# matricLib

# Basics
Any and all matrix operations

# Data setup
1D vectors {1, 2, 3, 4, .... N} are passed to the matrix class with type

``` matrix<TYPE> matrix_class_vector(YOUR_MATRIX, COLUMNS, ROWS); ```

All operations must be done on a matrix class and be self-contained. 

i.e., a binary operation (e.x., addition) must be user accessable via 

```
matrix<TYPE> RECV_MATRIX_CLASS_VECTOR(COLUMNS, ROWS);
RECV_MATRIX_CLASS_VECTOR.add(FIRST_MATRIX_CLASS_VECTOR, SECOND_MATRIX_CLASS_VECTOR, RECV_MATRIX_CLASS_VECTOR);
```
TODO: Clean up the above to imply the 3rd argument i.e., 
```
ECV_MATRIX_CLASS_VECTOR.add(FIRST_MATRIX_CLASS_VECTOR, SECOND_MATRIX_CLASS_VECTOR);
```

# Matrix Class

The matrix class accepts a 1D vector of any type along with ROWS and COLUMNS.

The matrix class has two primary constructors: One that accepts a vector of type <T> and another that generates a pre-allocated matrix of size(Columns * Rows)

The matrix class has a overloaded () operator which allows psuedo-2D access. i.e.,

```MY_MATRIX_CLASS_VECTOR(4, 3)```
Returns the fouth ROW of the third COLUMN. 


# Tests

##All functions must have tests before commiting

