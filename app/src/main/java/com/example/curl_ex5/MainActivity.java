package com.example.curl_ex5;

import androidx.appcompat.app.AppCompatActivity;

import android.os.Bundle;
import android.util.Log;

public class MainActivity extends AppCompatActivity {
static{
    System.loadLibrary("native-lib");
}
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        System.out.println(foo());

        String tmp = AesTool.encode("A");
        System.out.println("tmp : "+tmp);
        String result = AesTool.decode(tmp);
        System.out.println("result : "+result);

    }
    //cURL methods
    private native String foo();

}