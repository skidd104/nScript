#include <napi.h>
#include <vector>
#include <string>
#include <cmath>
#include <limits>
#include <algorithm>

//Array Function
//Not Updated to be the fastest im using the most basic shit
Napi::Value Array(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();
    
    if (info.Length() == 0) return env.Null();

    if (!info[0].IsArray()) {
        Napi::Array single = Napi::Array::New(env, 1);
        single.Set((uint32_t)0, info[0]);
        return single;
    }

    
    //1. info[0] is the OUTER array: [[1,2,3], [4,5,6]]
    Napi::Array outerArray = info[0].As<Napi::Array>();
    uint32_t rowCount =  outerArray.Length();


    //Parent Array Return Point
    Napi::Array resultMatrix = Napi::Array::New(env, rowCount);

    for (size_t i = 0; i < rowCount; i++) {
        Napi::Value element = outerArray.Get(i);
        //Geting the inner array at index i 
        //Here is the technique since the inner child is array we should get it as Array
        if (element.IsArray()) {

            Napi::Array innerArray = outerArray.Get(i).As<Napi::Array>();
            uint32_t colCount = innerArray.Length();

            Napi::Array resultRow = Napi::Array::New(env, colCount);

            for (uint32_t j = 0; j < colCount; j++) {
                resultRow.Set(j, innerArray.Get(j));
            }

            resultMatrix.Set(i, resultRow);

        } else {
            resultMatrix.Set(i, element);
        }
    }

    return resultMatrix;
}


//This is already good
Napi::Value Shape(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();

    // Safety Check
    if (!info[0].IsArray()) return env.Null();

    Napi::Array outerArray = info[0].As<Napi::Array>();

    uint32_t rows = outerArray.Length();

    uint32_t cols = 0;
    if (rows > 0 && outerArray.Get((uint32_t)0).IsArray()) {
        Napi::Array firstRow = outerArray.Get((uint32_t)0).As<Napi::Array>();
        cols = firstRow.Length();
    }
    
    Napi::Array shapeResult = Napi::Array::New(env, 2);
    shapeResult.Set((uint32_t)0, Napi::Number::New(env, rows));
    shapeResult.Set((uint32_t)1, Napi::Number::New(env, cols));
    return shapeResult;

}


//Recursive Math Engine Summation for the Sum Method
double recursiveSumHelper(Napi::Value value) {
    double total = 0;

    if (value.IsArray()) {
        Napi::Array arr = value.As<Napi::Array>();

        for (uint32_t i = 0; i < arr.Length(); i++) {
            total += recursiveSumHelper(arr.Get(i));
        }

    } else if (value.IsNumber()) {
        total = value.As<Napi::Number>().DoubleValue();
    }

    return total;
}
//Sum of Array Function
Napi::Value Sum(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();

    if (!info[0].IsArray()) return env.Null();

    double finalSum = recursiveSumHelper(info[0]);
    return Napi::Number::New(env, finalSum);
}


//Add Array Function
Napi::Value recursiveAdd(Napi::Env env, Napi::Value val1, Napi::Value val2) {
    
    if (val1.IsNumber() && val2.IsNumber()) {
        double sum = val1.As<Napi::Number>().DoubleValue() + val2.As<Napi::Number>().DoubleValue();
        return Napi::Number::New(env, sum);
    }

    if (val1.IsArray() && val2.IsArray()) {
        Napi::Array arr1 = val1.As<Napi::Array>();
        Napi::Array arr2 = val2.As<Napi::Array>();

        if (arr1.Length() != arr2.Length()) {
            Napi::TypeError::New(env, "Shapes must match for addition").ThrowAsJavaScriptException();
            return env.Null();

        }

        uint32_t len = arr1.Length();
        Napi::Array result = Napi::Array::New(env, len);

        for (uint32_t i = 0; i < len; i++) {
            result.Set(i, recursiveAdd(env, arr1.Get(i), arr2.Get(i)));

        }
        return result;
    }

    Napi::TypeError::New(env, "Invalid types for addition").ThrowAsJavaScriptException();
    return env.Null();
}

Napi::Value Add(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();
    
    if (info.Length() < 2) {
        Napi::TypeError::New(env, "Two arrays required").ThrowAsJavaScriptException();
        return env.Null();

    }

    return recursiveAdd(env, info[0], info[1]);
}

//Mean Action
void flattenMeanHelper(Napi::Value val, std::vector<double>& flatData) {
    if (val.IsNumber()) {
        flatData.push_back(val.As<Napi::Number>().DoubleValue());
    } else if (val.IsArray()) {
        Napi::Array arr = val.As<Napi::Array>();
        for (uint32_t i = 0; i < arr.Length(); i++) {
            flattenMeanHelper(arr.Get(i), flatData);
        }
    } else if (val.IsTypedArray()) {
        Napi::Float64Array ta = val.As<Napi::Float64Array>();
        for (size_t i = 0; i < ta.ElementLength(); i++) {
            flatData.push_back(ta[i]);
        }
    }

}

Napi::Value Mean(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();

    if (info.Length() < 1) {
        return Napi::Number::New(env, 0);
    }

    std::vector<double> flatData;
    flattenMeanHelper(info[0], flatData);

    if (flatData.empty()) {
        return Napi::Number::New(env, 0);
    }

    double sum = 0;
    for (double val : flatData) {
        sum += val;
    }

    double mean  = sum / static_cast<double>(flatData.size());

    return Napi::Number::New(env, mean);

}

Napi::Value Zeros(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();
    
    if (info.Length() < 1 ) {
        return env.Null();
    }

    if (info[0].IsArray()) {
        Napi::Array shape = info[0].As<Napi::Array>();

        if (shape.Length() < 2 ) return env.Null();

        uint32_t rows = shape.Get((uint32_t)0).As<Napi::Number>();
        uint32_t cols = shape.Get((uint32_t)1).As<Napi::Number>();

        Napi::Array matrix = Napi::Array::New(env, rows);

        for (uint32_t i = 0; i < rows; i++) {
            Napi::Array row = Napi::Array::New(env, cols);

            for  (uint32_t j = 0; j < cols; j++) {
                row.Set(j, Napi::Number::New(env, 0));
            }
            matrix.Set(i, row);

        }
        return matrix;
    }

    if (info[0].IsNumber()) {
        uint32_t count = info[0].As<Napi::Number>().Uint32Value();
        Napi::Array arr = Napi::Array::New(env, count);

        for (uint32_t i = 0; i < count; i++) {
            arr.Set(i, Napi::Number::New(env, 0));
        }
        return arr;
    }
    return env.Null();
}

Napi::Value Reshape(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();

    //First Safety Check
    if (info.Length() < 2 || !info[0].IsArray() || !info[1].IsArray() ) {
        return env.Null();
    }

    Napi::Array inputArr = info[0].As<Napi::Array>();
    Napi::Array shape = info[1].As<Napi::Array>();

    //Second Safety Check
    if (shape.Length() < 2) return env.Null();


    uint32_t rows = shape.Get((uint32_t)0).As<Napi::Number>().Uint32Value();
    uint32_t cols = shape.Get((uint32_t)1).As<Napi::Number>().Uint32Value();

    //Third Safety Check
    if (inputArr.Length() != (rows * cols)) {
        Napi::TypeError::New(env, "Mismatch rows and cols");
        return env.Null();
    }




    Napi::Array matrix = Napi::Array::New(env, rows);
    uint32_t k = 0;

    for (uint32_t i = 0; i < rows; i++) {
        Napi::Array row = Napi::Array::New(env, cols);
        for (uint32_t j = 0; j < cols; j++) {
            row.Set(j, inputArr.Get(k));
            k++;
        }

        matrix.Set(i, row);
    }

    return matrix;

}

//Ndim
// Helper function to count depth
uint32_t getDepth(Napi::Value val) {
    if (!val.IsArray()) {
        return 0;
    }

    Napi::Array arr = val.As<Napi::Array>();

    if (arr.Length() == 0) {
        return 1;
    }

    return 1 + getDepth(arr.Get((uint32_t)0));
}
Napi::Value NDim(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();

    if (info.Length() < 1) {
        return Napi::Number::New(env, 0);
    }

    uint32_t dims = getDepth(info[0]);
    return Napi::Number::New(env, dims);

}

//Size
//Able to support flat array for faster performance
uint32_t internalSizeCounter(Napi::Value val) {
    if (!val.IsArray()) return 1;

    Napi::Array arr = val.As<Napi::Array>();
    uint32_t count = 0;

    for (uint32_t i = 0; i < arr.Length(); i++) {
        count += internalSizeCounter(arr.Get(i));
    }

    return count;
}

Napi::Value Size(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();

    if (info.Length() < 1) return Napi::Number::New(env, 0);

    if (info[0].IsTypedArray()) {
        Napi::TypedArray typedArr = info[0].As<Napi::TypedArray>();
        return Napi::Number::New(env, typedArr.ElementLength());
    }

    if (info[0].IsArray()) {
        uint32_t total = internalSizeCounter(info[0]);
        return Napi::Number::New(env, total);
    }


    return Napi::Number::New(env, 0);
}

//Flatten
void flattenInternal(Napi::Value val, std::vector<double>& flatData) {
    if (val.IsNumber()) {
        flatData.push_back(val.As<Napi::Number>().DoubleValue());
    } else if (val.IsArray()) {
        Napi::Array arr = val.As<Napi::Array>();
        for (uint32_t i = 0; i < arr.Length(); i++) {
            flattenInternal(arr.Get(i), flatData);
        }
    } else if (val.IsTypedArray()) {
        Napi::Float64Array ta = val.As<Napi::Float64Array>();
        for (size_t i = 0; i < ta.ElementLength(); i++) {
            flatData.push_back(ta[i]);
        }
    }
}

Napi::Value Flatten(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();

    if (info.Length() < 1) return env.Null();

    std::vector<double> flatData;

    flattenInternal(info[0], flatData); 

    Napi::Float64Array result = Napi::Float64Array::New(env, flatData.size());

    for (size_t i = 0; i < flatData.size(); i++) {
        result[i] = flatData[i];
    }

    return result;
}

//Dtype Recursive Flattener
void flattenRecursive(Napi::Value val, std::vector<double>& flatData) {
    if (val.IsNumber()) {
        flatData.push_back(val.As<Napi::Number>().DoubleValue());
    } else if (val.IsArray()) {
        Napi::Array arr = val.As<Napi::Array>();
        for (uint32_t i = 0; i < arr.Length(); i++) {
            flattenRecursive(arr.Get(i), flatData);
        }
    } else if (val.IsTypedArray()) {
        Napi::Float64Array ta = val.As<Napi::Float64Array>();

        for (size_t i = 0; i < ta.ElementLength(); i++) {
            flatData.push_back(ta[i]);
        }
    }
}
//Dtype
Napi::Value Dtype(const Napi::CallbackInfo& info) {

    Napi::Env env = info.Env();

    if (info.Length() < 1) return env.Null();

    if (info.Length() == 1) {
        if (info[0].IsTypedArray()) {
            napi_typedarray_type type = info[0].As<Napi::TypedArray>().TypedArrayType();
            if (type == napi_int32_array) return Napi::String::New(env, "int32");
            if (type == napi_float64_array) return Napi::String::New(env, "float64");
            return Napi::String::New(env, "unknown_typed");
        }

        return Napi::String::New(env, "float64");
    }

    std::string code = info[1].As<Napi::String>().Utf8Value();

    std::vector<double> flatData;
    flattenRecursive(info[0], flatData);
    size_t len = flatData.size();

    if (code == "i") {
        Napi::Int32Array result = Napi::Int32Array::New(env, len);
        for (size_t i = 0; i < len; i++) {
            result[i] = static_cast<int32_t>(flatData[i]);
        }
        return result;
    } else if (code == "f") {
        Napi::Float64Array result = Napi::Float64Array::New(env, len);
        for (size_t i = 0; i < len; i++) {
            result[i] = flatData[i];
        }
        return result;
          
    } else if (code == "S") {
        Napi::Array result = Napi::Array::New(env, len);
        for (size_t i = 0; i < len; i++) {
            std::string s = std::to_string(flatData[i]);

            s.erase(s.find_last_not_of('0') + 1, std::string::npos);
            if (s.back() == '.') s.pop_back();
            result.Set(i, Napi::String::New(env, s));
        }
        return result;
    }
    return env.Null();;
}

Napi::Value Transpose(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();

    if (info.Length() < 1 || !info[0].IsArray()) {
        return env.Null();
    }

    Napi::Array inputMatrix = info[0].As<Napi::Array>();

    uint32_t rows = inputMatrix.Length();

    if (rows == 0) return Napi::Array::New(env, 0);

    Napi::Value firstRow = inputMatrix.Get((uint32_t)0);

    if (!firstRow.IsArray()) {
        return inputMatrix;
    }

    uint32_t cols = firstRow.As<Napi::Array>().Length();

    Napi::Array resultMatrix = Napi::Array::New(env, cols);

    for (uint32_t i = 0; i < cols; i++) {
        resultMatrix.Set(i, Napi::Array::New(env, rows));
    }

    for (uint32_t i = 0; i < rows; i++) {
        Napi::Array currentRow = inputMatrix.Get(i).As<Napi::Array>();

        for (uint32_t j = 0; j < cols; j++) {
            Napi::Array targetRow = resultMatrix.Get(j).As<Napi::Array>();
            targetRow.Set(i, currentRow.Get(j));

        }

    }

    return resultMatrix;
}


//Dot Function
Napi::Value Dot(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();

    if (info.Length() < 2 || !info[0].IsArray() || !info[1].IsArray()) {
        Napi::TypeError::New(env, "Two matrices (arrays) required").ThrowAsJavaScriptException();
        return env.Null();
    }

    Napi::Array A = info[0].As<Napi::Array>();
    Napi::Array B = info[1].As<Napi::Array>();

    uint32_t rowsA = A.Length();
    uint32_t colsA = A.Get((uint32_t)0).As<Napi::Array>().Length();
    uint32_t rowsB = B.Length();
    uint32_t colsB = B.Get((uint32_t)0).As<Napi::Array>().Length();

    if (colsA != rowsB) {
        Napi::Error::New(env, "Incompatible dimensions for dot product: ciks if A must match rows of B").ThrowAsJavaScriptException();

        return env.Null();
    }

    Napi::Array result  = Napi::Array::New(env, rowsA);

    for (uint32_t i = 0; i < rowsA; i++) {
        Napi::Array rowA = A.Get(i).As<Napi::Array>();
        Napi::Array newRow = Napi::Array::New(env, colsB);

        for (uint32_t j = 0; j < colsB; j++) {
            double sum = 0;
            for (uint32_t k = 0; k < colsA; k++) {
                double valA = rowA.Get(k).As<Napi::Number>().DoubleValue();
                double valB = B.Get(k).As<Napi::Array>().Get(j).As<Napi::Number>().DoubleValue();
                sum += valA * valB;
            }
            newRow.Set(j, Napi::Number::New(env, sum));

        }
        result.Set(i, newRow);
    }
    return result;
}

Napi::Value Inverse(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();

    if (info.Length() < 1 || !info[0].IsArray()) return env.Null();
    Napi::Array input = info[0].As<Napi::Array>();
    uint32_t n = input.Length();

    std::vector<std::vector<double>> mat(n, std::vector<double>(n));
    std::vector<std::vector<double>> inv(n, std::vector<double>(n, 0.0));

    for (uint32_t i = 0; i < n; i++) {
        Napi::Array row = input.Get(i).As<Napi::Array>();
        if (row.Length() != n) {
            Napi::Error::New(env, "Matrix must be square").ThrowAsJavaScriptException();
            return env.Null();
        }

        for(uint32_t j = 0; j < n; j++) {
            mat[i][j] = row.Get(j).As<Napi::Number>().DoubleValue();
            if (i == j) inv[i][j] = 1.0;
        }
    }

    for (uint32_t i = 0; i < n; i++) {
        uint32_t pivot = i;

        for (uint32_t j = i + 1; j < n; j++) {
            if (std::abs(mat[j][i]) > std::abs(mat[pivot][i])) pivot = j;
        }

        std::swap(mat[i], mat[pivot]);
        std::swap(inv[i], inv[pivot]);

        double diagVal = mat[i][i];

        if (std::abs(diagVal) < 1e-10) {
            Napi::Error::New(env, "Matrix is singular and cannot be inverted").ThrowAsJavaScriptException();
            return env.Null();
        }

        for (uint32_t j = 0; j < n; j++) {
            mat[i][j] /= diagVal;
            inv[i][j] /= diagVal;
        }

        for (uint32_t k = 0; k < n; k++) {
            if (k == i) continue;
            double factor = mat[k][i];
            for (uint32_t j = 0; j < n; j++) {
                mat[k][j] -= factor * mat[i][j];
                inv[k][j] -= factor * inv[i][j];

            }

        }
    }

    Napi::Array result = Napi::Array::New(env, n);
    for (uint32_t i = 0; i < n; i++) {
        Napi::Array row = Napi::Array::New(env, n);
        for (uint32_t j = 0; j < n; j++) {
            row.Set(j, Napi::Number::New(env, inv[i][j]));

        }
        result.Set(i, row);
    }

    return result;

}

//Standard Deviation
void flattenForStd(Napi::Value val, std::vector<double>& flatData) {
    if (val.IsNumber()) {
        flatData.push_back(val.As<Napi::Number>().DoubleValue());
    } else if (val.IsArray()) {
        Napi::Array arr = val.As<Napi::Array>();
        for (uint32_t i = 0; i < arr.Length(); i++) {
            flattenForStd(arr.Get(i), flatData);
        }
    } else if (val.IsTypedArray()) {
        Napi::Float64Array ta = val.As<Napi::Float64Array>();

        for (size_t i = 0; i < ta.ElementLength(); i++) {
            flatData.push_back(ta[i]);
        }
    }
}
Napi::Value Std(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();

    if (info.Length() < 1 ) return Napi::Number::New(env, 0);

    std::vector<double> data;
    flattenForStd(info[0], data);

    if (data.empty()) return Napi::Number::New(env, 0);

    double sum = 0;
    for (double v : data) sum += v;
    double mean = sum / data.size();

    double sqDiffSum = 0;
    for (double v : data) {
        sqDiffSum += std::pow(v - mean, 2);

    }

    double variance = sqDiffSum / data.size();

    double stdDev = std::sqrt(variance);

    return Napi::Number::New(env, stdDev);

}


//Min - Max
void flattenMinMax(Napi::Value val, std::vector<double>& flatData) {
    if (val.IsNumber()) {
        flatData.push_back(val.As<Napi::Number>().DoubleValue());
    } else if (val.IsArray()) {
        Napi::Array arr = val.As<Napi::Array>();
        for (uint32_t i = 0; i < arr.Length(); i++) {
            flattenInternal(arr.Get(i), flatData);
        }
    } else if (val.IsTypedArray()) {
        Napi::Float64Array ta = val.As<Napi::Float64Array>();
        for (size_t i = 0; i < ta.ElementLength(); i++) {
            flatData.push_back(ta[i]);
        }
    }
}

Napi::Value Min(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();

    if (info.Length() < 1) return env.Null();

    std::vector<double> data;

    flattenMinMax(info[0], data);

    if (data.empty()) return env.Null();

    double currentMin = std::numeric_limits<double>::infinity();
    for (double v : data) {
        if (v < currentMin) currentMin = v;
    }

    return Napi::Number::New(env, currentMin);
}
Napi::Value Max(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();

    if (info.Length() < 1) return env.Null();

    std::vector<double> data;
    flattenMinMax(info[0], data);

    if (data.empty()) return env.Null();

    double currentMax = -std::numeric_limits<double>::infinity();

    for (double v: data) {
        if (v > currentMax) currentMax = v;

    }
    return Napi::Number::New(env, currentMax);
}

//Median
Napi::Value Median(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();

    if (info.Length() < 1) return env.Null();

    std::vector<double> data;

    flattenInternal(info[0], data);

    if (data.empty()) return Napi::Number::New(env, 0);

    std::sort(data.begin(), data.end());

    size_t size = data.size();
    double median;

    if (size % 2 == 0) {
        median = (data[size / 2-1] + data[size / 2]) / 2.0;

    } else {
        median = data[size / 2];
    }

    return Napi::Number::New(env, median);
}
//Variance
Napi::Value Var(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();

    if (info.Length() < 1) return Napi::Number::New(env, 0);

    std::vector<double> data;


    flattenInternal(info[0], data);

    if (data.empty()) return Napi::Number::New(env, 0);

    double sum = 0;
    for (double v : data) sum += v;
    double mean = sum / data.size();

    double sqDiffSum = 0;

    for (double v : data) {
        sqDiffSum += std::pow(v - mean, 2);

    }

    double variance = sqDiffSum / data.size();
    return Napi::Number::New(env, variance);
}

Napi::Value Column(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();

    if (info.Length() < 2 || !info[0].IsArray() || !info[1].IsNumber()) {
        Napi::TypeError::New(env, "Usage: .col(matrix, index)").ThrowAsJavaScriptException();
        return env.Null();
    }

    Napi::Array matrix = info[0].As<Napi::Array>();
    uint32_t colIndex = info[1].As<Napi::Number>().Uint32Value();
    uint32_t rows = matrix.Length();

    if (rows == 0) return Napi::Array::New(env, 0);

    Napi::Float64Array result = Napi::Float64Array::New(env, rows);

    for (uint32_t i = 0; i < rows; i++) {
        Napi::Value rowVal = matrix.Get(i);

        if (rowVal.IsArray()) {
            Napi::Array row = rowVal.As<Napi::Array>();

            if (colIndex < row.Length()) {
                result[i] = row.Get(colIndex).As<Napi::Number>().DoubleValue();

            } else {
                result[i] = 0.0;
            }

        } else {
            result[i] = 0.0;

        }

    }

    return result;
}

Napi::Value Row(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();

    if (info.Length() < 2 || !info[0].IsArray() || !info[1].IsNumber()) {
        Napi::TypeError::New(env, "Usage: .row(matrix, index)").ThrowAsJavaScriptException();
        return env.Null();
    }

    Napi::Array matrix = info[0].As<Napi::Array>();
    uint32_t rowIndex = info[1].As<Napi::Number>().Uint32Value();

    if (rowIndex >= matrix.Length()) {
        Napi::Error::New(env, "Row index out of bounds").ThrowAsJavaScriptException();
        return env.Null();
    }

    Napi::Value row = matrix.Get(rowIndex);

    if (!row.IsArray()) {
        return row;

    }

    return row.As<Napi::Array>();
}

Napi::Value Slice(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();

    if (info.Length() < 3 || !info[0].IsArray() || !info[1].IsNumber() || !info[2].IsNumber()) {
        Napi::TypeError::New(env, "Usage: .slice(matrix, start, end)").ThrowAsJavaScriptException();
        return env.Null();
    }

    Napi::Array inputMatrix = info[0].As<Napi::Array>();
    uint32_t totalRows = inputMatrix.Length();

    int32_t startReq = info[1].As<Napi::Number>().Int32Value();
    int32_t endReq = info[2].As<Napi::Number>().Int32Value();

    uint32_t start = std::max(0, std::min((int)totalRows, startReq));
    uint32_t end = std::max(0, std::min((int)totalRows, endReq));

    if (start >= end) {
        return Napi::Array::New(env, 0);

    }
    
    uint32_t resultSize = end - start;
    Napi::Array result = Napi::Array::New(env, resultSize);

    for (uint32_t i = 0; i < resultSize; i++) {

        result.Set(i, inputMatrix.Get(start + i));
    }

    return result;
}



Napi::Object Init(Napi::Env env, Napi::Object exports) {
        exports.Set(Napi::String::New(env, "array"), Napi::Function::New(env, Array));
        exports.Set(Napi::String::New(env, "shape"), Napi::Function::New(env, Shape));
        exports.Set(Napi::String::New(env, "sum"), Napi::Function::New(env, Sum));
        exports.Set(Napi::String::New(env, "zeros"), Napi::Function::New(env, Zeros));
        exports.Set(Napi::String::New(env, "mean"), Napi::Function::New(env, Mean));
        exports.Set(Napi::String::New(env, "add"), Napi::Function::New(env, Add));
        exports.Set(Napi::String::New(env, "reshape"), Napi::Function::New(env, Reshape));
        exports.Set(Napi::String::New(env, "flatten"), Napi::Function::New(env, Flatten));
        exports.Set(Napi::String::New(env, "transpose"), Napi::Function::New(env, Transpose));
        exports.Set(Napi::String::New(env, "inv"), Napi::Function::New(env, Inverse));
        exports.Set(Napi::String::New(env, "dot"), Napi::Function::New(env, Dot));
        exports.Set(Napi::String::New(env, "ndim"), Napi::Function::New(env, NDim));
        exports.Set(Napi::String::New(env, "size"), Napi::Function::New(env, Size));
        exports.Set(Napi::String::New(env, "dtype"), Napi::Function::New(env, Dtype));
        exports.Set(Napi::String::New(env, "std"), Napi::Function::New(env, Std));
        exports.Set(Napi::String::New(env, "min"), Napi::Function::New(env, Min));
        exports.Set(Napi::String::New(env, "max"), Napi::Function::New(env, Max));
        exports.Set(Napi::String::New(env, "median"), Napi::Function::New(env, Median));
        exports.Set(Napi::String::New(env, "var"), Napi::Function::New(env, Var));
        exports.Set(Napi::String::New(env, "column"), Napi::Function::New(env, Column));
        exports.Set(Napi::String::New(env, "row"), Napi::Function::New(env, Row));

        exports.Set(Napi::String::New(env, "slice"), Napi::Function::New(env, Slice));


        return exports;
}
NODE_API_MODULE(numscrpt_core, Init);
