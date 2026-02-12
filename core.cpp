#include <napi.h>

//Template
Napi::Value Add(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();
    
    if (info.Length() < 2) {
        Napi::TypeError::New(env, "Wrong number of arguments").ThrowAsJavaScriptException();
        
            
    return env.Null();

    }


    if (!info[0].IsNumber() || !info[1].IsNumber()) {
            Napi::TypeError::New(env, "Wrong arguments").ThrowAsJavaScriptException();
            return env.Null();

    }

    double arg0 = info[0].As<Napi::Number>().DoubleValue();
    double arg1 = info[1].As<Napi::Number>().DoubleValue();
    Napi::Number num = Napi::Number::New(env, arg0 + arg1);

    return num;

}

//Array Function
Napi::Value Array(const Napi::CallbackInfo& info) {
        Napi::Env env = info.Env();
        size_t argCount = info.Length();

        if (argCount == 0) {
            return Napi::Float64Array::New(env, 0);

        }

        Napi::Float64Array data;

        if (argCount == 1 && (info[0].IsArray() || info[0].IsTypedArray())) {
            Napi::Array input = info[0].As<Napi::Array>();
            data = Napi::Float64Array::New(env, input.Length());

            double* rawPtr = data.Data();
            for (uint32_t i = 0; i < input.Length(); i++) {

                rawPtr[i] = input.Get(i).As<Napi::Number>().DoubleValue();
            }
        } else {
            data = Napi::Float64Array::New(env, argCount);

            double* rawPtr = data.Data();
            for (size_t i = 0; i < argCount; i++) {
                if (!info[i].IsNumber()) {
                    Napi::TypeError::New(env, "All arguments be numbers").ThrowAsJavaScriptException();
                    return env.Null();

                }

                rawPtr[i] = info[i].As<Napi::Number>().DoubleValue();

            }

        }





        //Enable for debugging
        //Napi::Object ndarray = Napi::Object::New(env);
        //ndarray.Set("data", data);
        //ndarray.Set("length", Napi::Number::New(env, data.ElementLength()));
        //ndarray.Set("type", Napi::String::New(env, "float64"));
        //
        return data;

}



Napi::Object Init(Napi::Env env, Napi::Object exports) {
        exports.Set(Napi::String::New(env, "add"), Napi::Function::New(env, Add));
        exports.Set(Napi::String::New(env, "array"), Napi::Function::New(env, Array));
        return exports;

}

NODE_API_MODULE(addon, Init);
