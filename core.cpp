#include <napi.h>

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


Napi::Object Init(Napi::Env env, Napi::Object exports) {
        exports.Set(Napi::String::New(env, "array"), Napi::Function::New(env, Array));
        exports.Set(Napi::String::New(env, "shape"), Napi::Function::New(env, Shape));
        exports.Set(Napi::String::New(env, "add"), Napi::Function::New(env, Sum));

        return exports;
}
NODE_API_MODULE(numscrpt_core, Init);
