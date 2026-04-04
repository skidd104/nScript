<a id="readme-top"></a>

[![Contributors][contributors-shield]][contributors-url]
[![Forks][forks-shield]][forks-url]
[![Stargazers][stars-shield]][stars-url]
[![Issues][issues-shield]][issues-url]
[![MIT License][license-shield]][license-url]
[![LinkedIn][linkedin-shield]][linkedin-url]

<br />
<div align="center">
  <a href="https://github.com/skidd104/nScript">
    <img src="images/logo.png" alt="Logo" width="80" height="80">
  </a>

<h3 align="center">nScript</h3>

  <p align="center">
    A high-performance C++ powered engine for Linear Algebra and Exploratory Data Analysis in Node.js.
    <br />
    <a href="https://github.com/skidd104/nScript"><strong>Explore the docs »</strong></a>
    <br />
    <br />
    <a href="https://github.com/skidd104/nScript">View Demo</a>
    &middot;
    <a href="https://github.com/skidd104/nScript/issues">Report Bug</a>
    &middot;
    <a href="https://github.com/skidd104/nScript/issues">Request Feature</a>
  </p>
</div>

<details>
  <summary>Table of Contents</summary>
  <ol>
    <li>
      <a href="#about-the-project">About The Project</a>
      <ul>
        <li><a href="#built-with">Built With</a></li>
      </ul>
    </li>
    <li>
      <a href="#getting-started">Getting Started</a>
      <ul>
        <li><a href="#prerequisites">Prerequisites</a></li>
        <li><a href="#installation">Installation</a></li>
      </ul>
    </li>
    <li><a href="#usage">Usage</a></li>
    <li><a href="#linearalgebra">LinearAlgebra</a></li>
    <li><a href="#eda">EDA</a></li>
    <li><a href="#license">License</a></li>
    <li><a href="#contact">Contact</a></li>
  </ol>
</details>

## About The Project

nScript is a specialized mathematical library that bridges the gap between JavaScript's ease of use and C++'s raw computational power. Designed for developers working with large datasets, it provides an optimized suite for multidimensional array manipulation, matrix operations, and comprehensive exploratory data analysis (EDA).

### Built With

* [![C++][CPP-shield]][CPP-url]
* [![Node.js][Node-shield]][Node-url]
* [![Node-API][Napi-shield]][Napi-url]

<p align="right">(<a href="#readme-top">back to top</a>)</p>

## Getting Started

### Prerequisites

To build the native C++ core, you need `node-gyp` and a C++ compiler installed on your system.
* npm
  ```sh
  npm install npm@latest -g
  ```

## Usage

### Arrays
```JavaScript
const array1 = numscrpt.array([1,2,3,4,5]);
const array2 = numscrpt.array([1,2,3],[4,5,6]);
const array3 = numscrpt.array([[[1,2,3],[4,5,6]], [[1,2,3]]]);
const array4 = numscrpt.array([[1,2],[3,4],[5,6]]);
```

### Shape
```JavaScript
const Shape = numscrpt.shape(array);
```

### Sum 
```JavaScript
const Sum = numscrpt.sum(array);
```

### Zeros
```javascript
const zeros = numscrpt.zeros([3,4]);
const zeros = numscrpt.zero(5);
```

### Reshape
```javascript 
let arr = numscrpt.array([1,2,3,4]);
let reshapedArr = numscrpt.reshape(arr, [2,2]);
//Error Case
let reshapedArr = numscrpt.reshape(arr, [2,3]);
```

### Ndim
```JavaScript
const d1 = numscrpt.array([1,2,3]);
const d2 = numscrpt.array([[1,2,3],[4,5,6]]);
const d3 = numscrpt.array([[[1,2,3], [4,5,6]], [[1,2,3], [4,5,6]]]);
const dimension = numscrpt.ndim(d3);
```

### Size 
```javascript
const flatArr = new Float64Array([1,2,3,4]);
const multArr = ([[1,2,3],[4,5,6]]);
const totalSize = numscrpt.size(multArr);
```

### Dtype 
1.)Casting a 3D Nested Array to a Flat Int32Array
```javascript
const d3 = [[[1.1, 2.2], [3.3, 4.4]]];
const intArr = numscrpt.dtype(d3, 'i');
```

2.)Casting to Strings
```javascript
const strArr = numscrpt.dtype([10.5, 20.9], 'S');
```
3.)Simple Operations
```javascript
console.log(numscrpt.dtype(intArr);
```


### Add
```javascript
//1D Add Operations
const a = [1,2,3];
const b = [10,20,30];
console.log (numscrpt.add(a, b));

//2D Add Operations
const matrix1 = [[1,1], [1,1]];
const matrix2 = [[5,5], [5,5]];
console.log(numscrpt.add(matrix1, matrix2));

//Error Case
numscrpt.add([1,2], [1,2,3]);
```

### Mean
```javascript
//1D Declerations
console.log(numscrpt.mean([1, 2, 3, 4, 5]));

//2D Array
const matrix = [
   [10, 20],
    [30, 40]
];
console.log(numscrpt.mean(matrix));

//3D Array
const d3 = [ [[1, 1], [1, 1]], [[2, 2], [2, 2]] ];
console.log(numscrpt.mean(d3));
```

### Flatten
```javascript
const matrix = [[1,2,3], [4,5,6]];
const flat = numscrpt.flatten(matrix);

```

### Transpose
```javascript
const matrix = [
    [1,2,3],
    [4,5,6]

];
const flipped = numscrpt.transpose(matrix);

```

## LinearAlgebra

### Dot
```javascript
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

```

### Inverse
```javascript
const A = [
    [4, 7],
    [2, 6]
];

const invA = numscrpt.inv(A);
const clean = (matrix) => {
    return matrix.map(row => 
        row.map(val => Math.abs(val) < 1e-10 ? 0 : val)
    );
}
const result = numscrpt.dot(A, invA);

```

## EDA
Exploratory Data Analysis

### Std
```javascript
const lowSpread = [10, 11, 10, 9, 10];
console.log(numscrpt.std(lowSpread)); 

const highSpread = [0, 10, 20, 30, 40];
console.log(numscrpt.std(highSpread)); 

const matrix = [[1, 2], [10, 20]];
console.log(numscrpt.std(matrix));

```






[contributors-shield]: https://img.shields.io/github/contributors/skidd104/nScript.svg?style=for-the-badge
[contributors-url]: https://github.com/skidd104/nScript/graphs/contributors
[forks-shield]: https://img.shields.io/github/forks/github_username/nScript.svg?style=for-the-badge
[forks-url]: https://github.com/github_username/nScript/network/members
[stars-shield]: https://img.shields.io/github/stars/github_username/nScript.svg?style=for-the-badge
[stars-url]: https://github.com/github_username/nScript/stargazers
[issues-shield]: https://img.shields.io/github/issues/github_username/nScript.svg?style=for-the-badge
[issues-url]: https://github.com/github_username/nScript/issues
[license-shield]: https://img.shields.io/github/license/github_username/nScript.svg?style=for-the-badge
[license-url]: https://github.com/github_username/nScript/blob/master/LICENSE.txt
[linkedin-shield]: https://img.shields.io/badge/-LinkedIn-black.svg?style=for-the-badge&logo=linkedin&colorB=555
[linkedin-url]: https://linkedin.com/in/linkedin_username

[CPP-shield]: https://img.shields.io/badge/C++-00599C?style=for-the-badge&logo=c%2B%2B&logoColor=white
[CPP-url]: https://isocpp.org/
[Node-shield]: https://img.shields.io/badge/Node.js-339933?style=for-the-badge&logo=nodedotjs&logoColor=white
[Node-url]: https://nodejs.org/
[Napi-shield]: https://img.shields.io/badge/Node--API-FFD700?style=for-the-badge&logo=node.js&logoColor=black
[Napi-url]: https://nodejs.org/api/n-api.html
