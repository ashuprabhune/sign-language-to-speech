package info.androidhive.introslider;

import android.content.Context;
import android.os.AsyncTask;
import android.speech.tts.TextToSpeech;
import android.util.Log;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.net.HttpURLConnection;
import java.net.URL;

/**
 * Created by user on 24/2/18.
 */

public class HttpApiRequestAsync extends AsyncTask<String, Void, String> {


    private static final String logtag = "HttpApiRequestAsync";
    private Context context;
    TextToSpeech t1;

    public HttpApiRequestAsync(Context context){
        this.context = context;

    }

    @Override
    protected void onPreExecute() {
        super.onPreExecute();


    }

    @Override
    protected String doInBackground(String... strings) {
        String returnText =null;
        BufferedReader br =null;
        try {
            URL url = new URL(strings[0]);
            Log.d("HttpApiRequestAsync", strings[0]);
            int i = 0;
            HttpURLConnection conn = null;

            while (true){
                if(isCancelled()){
                    break;
                }
                conn = (HttpURLConnection) url.openConnection();
                Log.d("HttpApiRequestAsync", "" + conn.getResponseCode());
                if (conn.getResponseCode() != 200) {
                    throw new RuntimeException("Failed : HTTP error code : "
                        + conn.getResponseCode());
                    }

                br = new BufferedReader(new InputStreamReader(
                    (conn.getInputStream())));
                returnText = br.readLine();
                if(returnText!=null && !returnText.trim().equals("")){
                    TextSpeechActivity.DATA_STORE.put(returnText);
                }

                conn.disconnect();
                Thread.sleep(1000);
             }

        } catch (IOException e) {
            e.printStackTrace();
        } catch (InterruptedException e) {
            e.printStackTrace();
        } finally {
            if(br!=null){
                try {
                    br.close();
                } catch (IOException e) {
                    e.printStackTrace();
                }
            }
        }
        return returnText;
    }

    protected void onPostExecute(String returnText){
        super.onPostExecute(returnText);

    }

}
