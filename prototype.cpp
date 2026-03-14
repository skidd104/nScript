#include <napi.h>


//Template
Napi::Value Add(const Napi::CallbackInfo& info) {
    //Point to return
   Napi::Env env = info.Env();
    
    //Safety Check
    if (info.Length() < 2) {
        Napi::TypeError::New(env, "Wrong number of arguments").ThrowAsJavaScriptException();
        
            
    return env.Null();

    }

    if (!info[0].IsNumber() || !info[1].IsNumber()) {
            Napi::TypeError::New(env, "Wrong arguments").ThrowAsJavaScriptException();
            return env.Null();

    }

    //Arguments info[0].As<Napi::Number>().DoubleValue means you open the element 1;
    double arg0 = info[0].As<Napi::Number>().DoubleValue();
    double arg1 = info[1].As<Napi::Number>().DoubleValue();
    Napi::Number num = Napi::Number::New(env, arg0 + arg1);

    return num;
}



//Add Single Array Function 
Napi::Value SArray(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();

    if (info.Length() > 0 && info[0].IsArray()) {
    
        //Initialize Array
        Napi::Array array = info[0].As<Napi::Array>();
        uint32_t len = array.Length();

        //Array Return Point
        Napi::Array result = Napi::Array::New(env, len);

        for (size_t i = 0; i < len; i++) {
            Napi::Value val = array.Get(i);
            result.Set(i, val);

        }
        return result;
    }
    return Napi::Number::New(env, 0);
}


//MultiDimensional Array
Napi::Value DArray(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();
    
    //1. info[0] is the OUTER array: [[1,2,3], [4,5,6]]
    Napi::Array outerArray = info[0].As<Napi::Array>();
    uint32_t rowCount =  outerArray.Length();

    //Parent Array Return Point
    Napi::Array resultMatrix = Napi::Array::New(env, rowCount);

    for (size_t i = 0; i < rowCount; i++) {
        //Geting the inner array at index i 
        //Here is the technique since the inner child is array we should get it as Array
        Napi::Array innerArray = outerArray.Get(i).As<Napi::Array>();
        uint32_t colCount = innerArray.Length();

        Napi::Array resultRow = Napi::Array::New(env, colCount);

        for (uint32_t j = 0; j < colCount; j++) {
            resultRow.Set(j, innerArray.Get(j));
        }


        resultMatrix.Set(i, resultRow);
    }

    return resultMatrix;
}



Napi::Object Init(Napi::Env env, Napi::Object exports) {

        exports.Set(Napi::String::New(env, "add"), Napi::Function::New(env, Add));
        exports.Set(Napi::String::New(env, "sarray"), Napi::Function::New(env,SArray));

        return exports;
}

NODE_API_MODULE(numscrpt_core, Init);
