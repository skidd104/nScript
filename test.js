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

const array1 = numscrpt.array([1,2,3,4,5]);
const array2 = numscrpt.array([[1,2,3],[4,5,6]]);
const array3 = numscrpt.array([[[1,2,3], [4,5,6]], [[1,2,3],[4,5,6]]]);


//const rows = array3.length;
//const columns = array3[0].length;

//console.log (`Dimension: ${rows}x${columns}`);
//
//
const array5 = numscrpt.array([[1,2],[3,4],[5,6]]);
const shape = numscrpt.shape(array5);


console.log (array5);
console.log (shape);

const test = numscrpt.add(array3);

console.log (test);


