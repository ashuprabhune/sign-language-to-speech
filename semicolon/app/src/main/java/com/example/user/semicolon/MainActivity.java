package com.example.user.semicolon;

import android.app.Activity;
import android.os.Bundle;
import android.os.StrictMode;
import android.speech.tts.TextToSpeech;
import android.util.Log;
import android.view.View;
import android.widget.Button;
import android.widget.EditText;

import java.util.Locale;
import java.util.concurrent.ArrayBlockingQueue;
import java.util.concurrent.BlockingQueue;
import java.util.concurrent.TimeUnit;
import java.util.concurrent.atomic.AtomicBoolean;

public class MainActivity extends Activity implements HttpAsyncResponse {
    TextToSpeech t1;
    EditText ed1;
    Button b1,b2;
    TextConverter tc;
    public static final BlockingQueue<String> DATA_STORE = new ArrayBlockingQueue<String>(100);
    public static AtomicBoolean FLAG = new AtomicBoolean(true);
    HttpApiRequestAsync getRequest =null;
    private long lastActiveTime = System.currentTimeMillis();

    @Override
    protected void onCreate(Bundle savedInstanceState) {

        StrictMode.ThreadPolicy policy = new StrictMode.ThreadPolicy.Builder().permitAll().build();
        StrictMode.setThreadPolicy(policy);
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        ed1 = (EditText) findViewById(R.id.editText);
        b1 = (Button) findViewById(R.id.speak);
        b2 = (Button) findViewById(R.id.stop);

        getRequest = new HttpApiRequestAsync(getApplicationContext());

        t1 = new TextToSpeech(getApplicationContext(), new TextToSpeech.OnInitListener() {
            @Override
            public void onInit(int status) {
                if (status != TextToSpeech.ERROR) {
                    t1.setLanguage(Locale.UK);
                }
            }
        });

        b1.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                //String toSpeak = ed1.getText().toString();
                String toSpeak = null;
                tc = new TextConverter(getApplicationContext());
                int i = 0;
                getRequest.execute("http://10.88.247.131:8080/bitsplease/gesture");
                try {
                    while (FLAG.get()) {

                        toSpeak = DATA_STORE.poll(1, TimeUnit.SECONDS);
                        if (toSpeak != null && toSpeak.trim() != "") {
                            Log.d("HttpApiRequestAsync", toSpeak);
                            tc.convertTextToSpeech(t1, toSpeak);
                            lastActiveTime = System.currentTimeMillis();
                        } else {
                            Log.d("HttpApiRequestAsync", "no data found");
                            if(System.currentTimeMillis() - lastActiveTime > 120000){
                                FLAG.set(false);
                            }
                        }
                    }

                } catch (InterruptedException e) {
                    e.printStackTrace();
                }
            }
        });
        b2.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                FLAG.set(false);
            }
        });

    }

    @Override
    public void onPause(){
        FLAG.set(false);
        super.onPause();
    }

    @Override
    protected void onResume() {
        FLAG.set(true);
        super.onResume();
    }

    @Override
    protected void onRestart() {
        FLAG.set(true);
        super.onRestart();
    }

    @Override
    public void processFinish(String output) {

    }
}