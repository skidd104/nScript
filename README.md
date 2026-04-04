# nScript
Array - Done
Sum - Done
Add - Done
Zeros - Done
Reshape - Done
Ndim - Done
Size - Done
Dtype - Done
Mean - Done
Flatten - Done
Transpose - Done
Dot - Done
Inverse - Done
Std - Done
Min - Done
Max - Done
Median - Done
Variance - Done
Column - Done
Row - Done
Slice - Done
Isnan - Done
Dropna - Done
Fillna - Done
Correlation - Done


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
-let reshapedArr = numscrpt.reshape(arr, [2,2]);
--Error Case--
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

## Mean Decleration
### 1D Array
-console.log(numscrpt.mean([1, 2, 3, 4, 5])); // 3

### 2D Matrix
-const matrix = [
    [10, 20],
    [30, 40]
];
-console.log(numscrpt.mean(matrix)); // 25

### 3D Array
-const d3 = [ [[1, 1], [1, 1]], [[2, 2], [2, 2]] ];
-console.log(numscrpt.mean(d3)); // 1.5

## Flatten
-const matrix = [[1,2,3], [4,5,6]];
-const flat = numscrpt.flatten(matrix);


## Transpose
-const matrix = [
    [1,2,3],
    [4,5,6]

];
-const flipped = numscrpt.transpose(matrix);


# Linear Algebra Functions

## Dot
-const A = [
    [1,2,3],
    [4,5,6]
];

-const B = [
    [7, 8],
    [9, 10],
    [11, 12]
];
-const result = numscrpt.dot(A, B);

## Inverse

-const A = [
    [4, 7],
    [2, 6]
];

-const invA = numscrpt.inv(A);
-const clean = (matrix) => {
    return matrix.map(row => 
        row.map(val => Math.abs(val) < 1e-10 ? 0 : val)
    );
}
-const result = numscrpt.dot(A, invA);

# Exploratory Data Analysis 

## Std
-const lowSpread = [10, 11, 10, 9, 10];
-console.log(numscrpt.std(lowSpread)); 

-const highSpread = [0, 10, 20, 30, 40];
-console.log(numscrpt.std(highSpread)); 

-const matrix = [[1, 2], [10, 20]];
-console.log(numscrpt.std(matrix));

## Min-Max
-const stockPrices = [
    [150.25, 155.10, 148.00],
    [152.00, 158.50, 151.20]
];

-const low = numscrpt.min(stockPrices);
-const high = numscrpt.max(stockPrices);

-console.log(`The chart range should be: ${low} to ${high}`);

## Median
-console.log(numscrpt.median([10, 2, 38, 23, 38])); 
-console.log(numscrpt.median([10, 2, 38, 23])); 
-const prices = [[200], [250], [10000]];
-console.log(numscrpt.median(prices)); // 251

## Variance
-const data = [1, 2, 3, 4, 5];

-const variance = numscrpt.var(data);
-const stdDev = numscrpt.std(data);

-console.log("Variance:", variance); // 2
-console.log("Std Dev:", stdDev);     // 1.414 (sqrt of 2)

-console.log(numscrpt.var([[10, 20], [30, 40]])); // 125

## Column
-const dataset = [
    [25, 50000, 1], // [Age, Salary, Remote]
    [30, 60000, 0],
    [45, 95000, 1],
    [22, 42000, 0]
];

// 1. Extract Salaray only
-const salaries = numscrpt.column(dataset, 1); 

// 2. Perform Stats on just that column
-const avgSalary = numscrpt.mean(salaries);
-const maxSalary = numscrpt.max(salaries);
-console.log(`Average Salary: ${avgSalary}`);

## Row

-const dataset = [
    [1, 250000], // ID, Price
    [2, 310000],
    [3, 10000000] 
];

-const prices = numscrpt.column(dataset, 1);
-const maxVal = numscrpt.max(prices);
-const outlierIndex = Array.from(prices).indexOf(maxVal);

-const record = numscrpt.row(dataset, outlierIndex);
-console.log("Full Record of Outlier:", record);

## Slice
const dataset = [
    [1, "Alice"],
    [2, "Bob"],
    [3, "Charlie"],
    [4, "David"],
    [5, "Eve"]
];

const chunk = numscrpt.slice(dataset, 1, 4);

## IsNaN
-const sensorData = [10.5, NaN, 12.1, 11.8, NaN];

-const mask = numscrpt.isnan(sensorData);
-console.log(mask); 

-const missingCount = mask.filter(x => x === true).length;
if (missingCount > 0) {
    console.log(`Warning: You have ${missingCount} holes in your data!`);
}

## DropNa
-const dataset = [
    [10, 20, 30],
    [5, NaN, 15], 
    [1, 2, 3],
    [NaN, 0, 0] 
];

-const cleaned = numscrpt.dropna(dataset);

-console.log(cleaned.length); 
-console.log(cleaned); 
[
  [10, 20, 30],
  [1, 2, 3]
]

## FillNA
-const dataset = [10, NaN, 30, NaN, 50];

-const zeros = numscrpt.fillna(dataset, 0); 

-const average = numscrpt.mean(numscrpt.dropna(dataset));
-const scientific = numscrpt.fillna(dataset, average);

## Correlation
-const studyHours = [1, 2, 3, 4, 5];
-const testScores = [52, 60, 71, 84, 95];

-const relationship = numscrpt.corr(studyHours, testScores);
-console.log(`Correlation: ${relationship.toFixed(4)}`); 

-const randomNoise = [99, 2, 45, 12, 7];
-console.log(numscrpt.corr(studyHours, randomNoise)); 
