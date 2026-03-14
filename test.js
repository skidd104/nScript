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
//Add Decleration
const test = numscrpt.add(array3);
//Zeros Decleration
const zeros = numscrpt.zeros([3,4]);
const zeros = numscrpt.zeros(5);
//Reshape Decleration
let arr = numscrpt.array([1,2,3,4,5,6]);
let reshaped_arr = numscrpt.reshape(arr, [2,3]);
*/





