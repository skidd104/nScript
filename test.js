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

//Variance
const data = [1, 2, 3, 4, 5];

const variance = numscrpt.var(data);
const stdDev = numscrpt.std(data);

console.log("Variance:", variance); // 2
console.log("Std Dev:", stdDev);     // 1.414 (sqrt of 2)

console.log(numscrpt.var([[10, 20], [30, 40]])); // 125
//Column
const dataset = [
    [25, 50000, 1], // [Age, Salary, Remote]
    [30, 60000, 0],
    [45, 95000, 1],
    [22, 42000, 0]
];

// 1. Extract just the Salary column (Index 1)
const salaries = numscrpt.column(dataset, 1); 

// 2. Perform Stats on just that column
const avgSalary = numscrpt.mean(salaries);
const maxSalary = numscrpt.max(salaries);

console.log(`Average Salary: ${avgSalary}`); // 61750

//Row
const dataset = [
    [1, 250000], // ID, Price
    [2, 310000],
    [3, 10000000] 
];

// Find the index of the max price
const prices = numscrpt.column(dataset, 1);
const maxVal = numscrpt.max(prices);
const outlierIndex = Array.from(prices).indexOf(maxVal);

// Grab the full record for that outlier
const record = numscrpt.row(dataset, outlierIndex);
console.log("Full Record of Outlier:", record); // [3, 10000000]

// Slice
const dataset = [
    [1, "Alice"],
    [2, "Bob"],
    [3, "Charlie"],
    [4, "David"],
    [5, "Eve"]
];

// Grab the middle three rows (Index 1, 2, 3)
const chunk = numscrpt.slice(dataset, 1, 4);

console.log(chunk[0][1]);
Output:
[
  [2, "Bob"],
  [3, "Charlie"],
  [4, "David"]
]
//IsNan
const sensorData = [10.5, NaN, 12.1, 11.8, NaN];

const mask = numscrpt.isnan(sensorData);
console.log(mask); // [false, true, false, false, true]

// Real-world EDA check:
const missingCount = mask.filter(x => x === true).length;
if (missingCount > 0) {
    console.log(`Warning: You have ${missingCount} holes in your data!`);
}
//DropNa
const dataset = [
    [10, 20, 30],
    [5, NaN, 15],  // This row will be deleted
    [1, 2, 3],
    [NaN, 0, 0]    // This row will be deleted
];

const cleaned = numscrpt.dropna(dataset);

console.log(cleaned.length); // 2
console.log(cleaned); 
[
  [10, 20, 30],
  [1, 2, 3]
]
//FillNA
const dataset = [10, NaN, 30, NaN, 50];

// Strategy 1: Fill with Zero
const zeros = numscrpt.fillna(dataset, 0); 
// [10, 0, 30, 0, 50]

// Strategy 2: Fill with Mean (The Professional Choice)
const average = numscrpt.mean(numscrpt.dropna(dataset)); // Get mean of existing data
const scientific = numscrpt.fillna(dataset, average);
console.log (scientific);
// [10, 30, 30, 30, 50]

//Correlation
const studyHours = [1, 2, 3, 4, 5];
const testScores = [52, 60, 71, 84, 95];

const relationship = numscrpt.corr(studyHours, testScores);
console.log(`Correlation: ${relationship.toFixed(4)}`); 
// Output: Correlation: 0.9984 (Extremely strong positive relationship!)

const randomNoise = [99, 2, 45, 12, 7];
console.log(numscrpt.corr(studyHours, randomNoise)); 
// Output: ~ -0.6 (A negative, weaker relationship)
*/


const arr = numscrpt.array([1,2,3]);
const ndim = numscrpt.ndim(arr);

console.log (ndim);
