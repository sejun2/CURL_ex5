package com.example.curl_ex5;

public class AesTool {
    static {
        System.loadLibrary("fooLib");
    }

    public static native String encode(String str);
    public static native String decode(String str);
}
