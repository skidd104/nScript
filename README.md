# nScript
Array - Done
Sum - Done
Add - Done
Zeros - Done
Reshape - Done
Ndim - Done
Size - Done
Dtype - Done

## Arrays 
Support 1d,2d,3d Array
##Usage: 
-const array1 = numscrpt.array([1,2,3,4,5]);
-const array2 = numscrpt.array([1,2,3],[4,5,6]);
-const array3 = numscrpt.array([[[1,2,3],[4,5,6]], [[1,2,3]]]);
-const array4 = numscrpt.array([[1,2],[3,4],[5,6]]);

## Shape
Returns shape of array
-const Shape = numscrpt.shape(array4);

## Sum 
-const Add = numscrpt.Sum(array3);

## Zeros
-const zeros = numscrpt.zeros([3,4]);
-const zeros = numscrpt.zero(5);

## Reshape Decleration
-let arr = numscrpt.array([1,2,3,4]);
-let reshapedArr = numscrpt.reshape(arr, [2,3]);

## Ndim Decleration
-const d1 = numscrpt.array([1,2,3]);
-const d2 = numscrpt.array([[1,2,3],[4,5,6]]);
-const d3 = numscrpt.array([[[1,2,3], [4,5,6]], [[1,2,3], [4,5,6]]]);

## Size Decleration
-const flatArr = new Float64Array([1,2,3,4]);
-const multArr = ([[1,2,3],[4,5,6]]);
-const totalSize = numscrpt.size(multArr);

## Dtype Decleration
### 1. Casting a 3D Nested Array to a Flat Int32Array
-const d3 = [[[1.1, 2.2], [3.3, 4.4]]];
-const intArr = numscrpt.dtype(d3, 'i');

### 2. Casting to Strings
-const strArr = numscrpt.dtype([10.5, 20.9], 'S');

### 3. Simple Operation
-console.log(numscrpt.dtype(intArr);

## Add Decleration
-1D Addition
-const a = [1,2,3];
-const b = [10,20,30];
-console.log (numscrpt.add(a, b));

-2D Addition
-const matrix1 = [[1,1], [1,1]];
-const matrix2 = [[5,5], [5,5]];
-console.log(numscrpt.add(matrix1, matrix2));

-Error Case
-numscrpt.add([1,2], [1,2,3]);

