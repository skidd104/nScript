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


const arr = numscrpt.sarray([1,2,3,4]);

console.log (arr);
console.log (arr.length);

for (let i = 0; i < arr.length; i++) {
    console.log (arr[i]);
}


