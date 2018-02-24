package info.androidhive.introslider;

import android.os.StrictMode;
import android.speech.tts.TextToSpeech;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.util.Log;
import android.view.View;
import android.widget.Button;

import java.util.Locale;
import java.util.concurrent.ArrayBlockingQueue;
import java.util.concurrent.BlockingQueue;
import java.util.concurrent.TimeUnit;
import java.util.concurrent.atomic.AtomicBoolean;

public class TextSpeechActivity extends AppCompatActivity {
    Button speakButton,stopButton;
    TextToSpeech t1;
    HttpApiRequestAsync asyncRequest;
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
        setContentView(R.layout.activity_text_speech);
        speakButton = (Button) findViewById(R.id.btn_speak);
        stopButton = (Button) findViewById(R.id.btn_stop);
        asyncRequest = new HttpApiRequestAsync(getApplicationContext());

        t1 = new TextToSpeech(getApplicationContext(), new TextToSpeech.OnInitListener() {
            @Override
            public void onInit(int status) {
                if (status != TextToSpeech.ERROR) {
                    t1.setLanguage(Locale.UK);
                }
            }
        });

        speakButton.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                //String toSpeak = ed1.getText().toString()
                String toSpeak = null;
                tc = new TextConverter(getApplicationContext());
                int i = 0;
                asyncRequest.execute("http://10.88.247.131:8080/bitsplease/gesture");
                try {
                    while (FLAG.get()) {

                        toSpeak = DATA_STORE.poll(1, TimeUnit.SECONDS);
                        if (toSpeak != null && toSpeak.trim() != "") {
                            Log.d("HttpApiRequestAsync", toSpeak);
                            tc.convertTextToSpeech(t1, toSpeak);
                            lastActiveTime = System.currentTimeMillis();
                        } else {
                            Log.d("HttpApiRequestAsync", "no data found");
                            if(System.currentTimeMillis() - lastActiveTime > 30000){
                                FLAG.set(false);
                            }
                        }
                    }

                } catch (InterruptedException e) {
                    e.printStackTrace();
                }
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


}
