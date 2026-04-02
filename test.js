//const numscrpt = require('./build/Release/numscrpt_core');
const numscrpt = require('bindings')('numscrpt_core')

//Test Array Function
/*
const arr = numscrpt.array([1,2,3,5,6,7,8], [6, 1]);

console.log ("Full Object:", arr);
console.log ("The Numbers:", arr.data);
console.log ("Array Shape:", arr.shape);
console.log ("Array Dimension:", arr.ndim);
*/ 

/*
//Array Decleration
const array1 = numscrpt.array([1,2,3,4,5]);
const array2 = numscrpt.array([[1,2,3],[4,5,6]]);
const array3 = numscrpt.array([[[1,2,3], [4,5,6]], [[1,2,3],[4,5,6]]]);
const array5 = numscrpt.array([[1,2],[3,4],[5,6]]);
//Shape Decleration
const shape = numscrpt.shape(array5);
//Sum Decleration
const test = numscrpt.sum(array3);
//Zeros Decleration
const zeros = numscrpt.zeros([3,4]);
const zeros = numscrpt.zeros(5);
//Reshape Decleration
let arr = numscrpt.array([1,2,3,4,5,6]);
let reshaped_arr = numscrpt.reshape(arr, [2,3]);
//Ndim Decleration
const d1 = numscrpt.array([1,2,3]);
const d2 = numscrpt.array([[1,2,3],[4,5,6]]);
const d3 = numscrpt.array([[[1, 2, 3], [4, 5, 6]], [[1, 2, 3], [4, 5, 6]]]);
const dimension = numscrpt.ndim(d2);
//Size Decleration
const flat_arr = new Float64Array([1,2,3,4]);
const mult_arr = ([[1,2,3],[4,5,6]]); 
const totalsize = numscrpt.size(mult_arr);
//Dtype Decleration
// 1. Casting a 3D Nested Array to a Flat Int32Array
const d3 = [[[1.1, 2.2], [3.3, 4.4]]];
const intArr = numscrpt.dtype(d3, 'i'); 
console.log(intArr); 

// 2. Casting to Strings
const strArr = numscrpt.dtype([10.5, 20.9], 'S');
console.log(strArr); 
// 3. Simple Inspection
console.log(numscrpt.dtype(intArr)); 

//Add Decleration
// 1D Addition
const a = [1,2,3];
const b = [10,20,30];
console.log (numscrpt.add(a, b));

// 2D Addition
const matrix1 = [[1,1], [1,1]];
const matrix2 = [[5,5], [5,5]];
console.log(numscrpt.add(matrix1, matrix2));

// Error Case
numscrpt.add([1,2], [1,2,3]);

//Mean Decleration
// 1 D Array
console.log(numscrpt.mean([1,2,3,4,5]));

// 2 D Array
const matrix = [
    [10, 20],
    [30, 40]
];
console.log (numscrpt.mean(matrix));

// 3 D array 
const d3 = [ [[1,1], [1,1]], [[2,2], [2,2]]];
console.log (numscrpt.mean(d3));

//Flatten Decleration
const matrix = [[1, 2, 3], [4, 5, 6]];

const flat = numscrpt.flatten(matrix);
console.log(flat); 

const deep = [[[1]], [[2]], [[3]]];
console.log(numscrpt.flatten(deep)); 

//Transpose
const matrix = [
    [1,2,3],
    [4,5,6]

];
const flipped = numscrpt.transpose(matrix);
console.log(flipped);

//Dot
const A = [
    [1,2,3],
    [4,5,6]
];

const B = [
    [7, 8],
    [9, 10],
    [11, 12]
];
const result = numscrpt.dot(A, B);
console.log (result);
// Inverse
const A = [
    [4, 7],
    [2, 6]
];

const invA = numscrpt.inv(A);
console.log(invA); 

const clean = (matrix) => {
    return matrix.map(row => 
        row.map(val => Math.abs(val) < 1e-10 ? 0 : val)
    );
}
const result = numscrpt.dot(A, invA);
console.log(clean(result));
//STD
const lowSpread = [10, 11, 10, 9, 10];
console.log (numscrpt.std(lowSpread));

const highSpread = [0, 10, 20, 30 ,40];
console.log (numscrpt.std(highSpread));

const matrix = [[1,2], [10,20]];
console.log (numscrpt.std(matrix));
//Min-Max
const stockPrices = [
    [150.25, 155.10, 148.00],
    [152.00, 158.50, 151.20]
];

const low = numscrpt.min(stockPrices);
const high = numscrpt.max(stockPrices);

console.log(`The chart range should be: ${low} to ${high}`);
//Median
console.log(numscrpt.median([10, 2, 38, 23, 38])); 
// Sorted: [2, 10, 23, 38, 38] -> Result: 23

console.log(numscrpt.median([10, 2, 38, 23])); 
// Sorted: [2, 10, 23, 38] -> Result: 16.5 (Avg of 10 and 23)

const prices = [[200], [250], [10000]];
console.log(numscrpt.median(prices)); 
// 250
*/
