package com.example.user.semicolon;

import android.content.Context;
import android.speech.tts.TextToSpeech;
import android.util.Log;
import android.widget.Toast;

import java.util.Locale;

/**
 * Created by user on 24/2/18.
 */

public class TextConverter {
    private Context context;


    public TextConverter(Context context) {
        this.context = context;
    }


    public void convertTextToSpeech(TextToSpeech t1,String toSpeak) {

        if (toSpeak != null && toSpeak.trim() != "") {
            Log.d("TextConverter", toSpeak);
            Toast.makeText(context, toSpeak, Toast.LENGTH_SHORT).show();
            t1.speak(toSpeak, android.speech.tts.TextToSpeech.QUEUE_FLUSH, null);
        }
    }
}