#include <napi.h>
#include <vector>
#include <string>

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




Napi::Object Init(Napi::Env env, Napi::Object exports) {
        exports.Set(Napi::String::New(env, "array"), Napi::Function::New(env, Array));
        exports.Set(Napi::String::New(env, "shape"), Napi::Function::New(env, Shape));
        exports.Set(Napi::String::New(env, "sum"), Napi::Function::New(env, Sum));
        exports.Set(Napi::String::New(env, "zeros"), Napi::Function::New(env, Zeros));
        exports.Set(Napi::String::New(env, "add"), Napi::Function::New(env, Add));
        exports.Set(Napi::String::New(env, "reshape"), Napi::Function::New(env, Reshape));
        exports.Set(Napi::String::New(env, "ndim"), Napi::Function::New(env, NDim));
        exports.Set(Napi::String::New(env, "size"), Napi::Function::New(env, Size));
        exports.Set(Napi::String::New(env, "dtype"), Napi::Function::New(env, Dtype));
        return exports;
}
NODE_API_MODULE(numscrpt_core, Init);
