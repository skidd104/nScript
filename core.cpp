#include <napi.h>
#include <string.h>

//Practice
Napi::Value Method(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();

    if (!info[0].IsString()) {
        Napi::TypeError::New(env, "String expected").ThrowAsJavaScriptException();
        return env.Null();
    }

    Napi::String mystr = info[0].As<Napi::String>();
    Napi::Number count = Napi::Number::New(env, mystr.Utf8Value().length());

    return count;
}



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

        if (argCount == 0) return env.Null();

        Napi::Float64Array data;
        Napi::Uint32Array shape;

        if (info[0].IsArray()) {
            Napi::Array input = info[0].As<Napi::Array>();
            data = Napi::Float64Array::New(env, input.Length());
            double* rawPtr = data.Data();

            for (uint32_t i = 0; i < input.Length(); i++) {
                rawPtr[i] = input.Get(i).As<Napi::Number>().DoubleValue();

            }

            if (argCount > 1 && info[1].IsArray()) {
                Napi::Array shapeInput = info[1].As<Napi::Array>();
                shape = Napi::Uint32Array::New(env, shapeInput.Length());
                uint32_t* shapePtr = shape.Data();

                for (uint32_t i = 0; i < shapeInput.Length(); i++) {
                    shapePtr[i] = shapeInput.Get(i).As<Napi::Number>().Uint32Value();

                }

            } else {
                shape = Napi::Uint32Array::New(env, 1);
                shape[0] = (uint32_t)data.ElementLength();

            }

            if (info.Length() > 1 && info[1].IsArray()) {
                size_t totalExpectedElements = 1;
                uint32_t* shapePtr = shape.Data();

                for (uint32_t i = 0; i < shape.ElementLength(); i++) {
                    totalExpectedElements *= shapePtr[i];

                }

                if (totalExpectedElements != data.ElementLength()) {
                    std::string errorMsg = "Value:: cannot reshape array of size " + std::to_string(data.ElementLength()) + " into shape (" ;
                    Napi::TypeError::New(env, errorMsg + "..)").ThrowAsJavaScriptException();
                        return env.Null();

                }

            }

        } else {
            data = Napi::Float64Array::New(env, argCount);
            double* rawPtr = data.Data();
            for (size_t i = 0; i < argCount; i++) {
                rawPtr[i] = info[i].As<Napi::Number>().DoubleValue();

            }

            shape = Napi::Uint32Array::New(env, 1);
            shape[0] = (uint32_t)argCount;

        }


        Napi::Object ndarray = Napi::Object::New(env);
        ndarray.Set("data", data);
        ndarray.Set("shape", shape);
        ndarray.Set("ndim", Napi::Number::New(env, shape.ElementLength()));

        return ndarray;

}



//Main Entry Point
Napi::Object Init(Napi::Env env, Napi::Object exports) {
        //Production
        exports.Set(Napi::String::New(env, "add"), Napi::Function::New(env, Add));
        exports.Set(Napi::String::New(env, "array"), Napi::Function::New(env, Array));

        //Prototypes
        exports.Set(Napi::String::New(env, "hello"), Napi::Function::New(env, Method));



        return exports;

}

NODE_API_MODULE(addon, Init);
