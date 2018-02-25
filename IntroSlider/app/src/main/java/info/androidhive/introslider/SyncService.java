package info.androidhive.introslider;

import android.app.Service;
import android.content.Intent;
import android.os.Handler;
import android.os.HandlerThread;
import android.os.IBinder;
import android.os.Looper;
import android.os.Message;
import android.os.Process;
import android.support.annotation.Nullable;
import android.util.Log;
import android.widget.Toast;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.net.HttpURLConnection;
import java.net.URL;

/**
 * Created by user on 25/2/18.
 */

public class SyncService extends Service {
    //private Looper mServiceLooper;
    private Handler mServiceHandler;
    private static final long DEFAULT_SYNC_INTERVAL = 1000;
    private Runnable runnableService = new Runnable() {
        @Override
        public void run() {
            String result = syncData();
            if(result!=null)
                Log.d("In thread",result);
            mServiceHandler.postDelayed(runnableService,DEFAULT_SYNC_INTERVAL);
        }
    };

    // Handler that receives messages from the thread


    @Override
    public void onCreate() {
        // Start up the thread running the service.  Note that we create a
        // separate thread because the service normally runs in the process's
        // main thread, which we don't want to block.  We also make it
        // background priority so CPU-intensive work will not disrupt our UI.
        super.onCreate();


    }

    @Override
    public int onStartCommand(Intent intent, int flags, int startId) {
        //Toast.makeText(this, "service starting", Toast.LENGTH_SHORT).show();

        mServiceHandler = new Handler(){};
        mServiceHandler.post(runnableService);
        // If we get killed, after returning from here, restart
        return START_STICKY;
    }

    @Override
    public IBinder onBind(Intent intent) {
        // We don't provide binding, so return null
        return null;
    }

    @Override
    public void onDestroy() {

    }

    private String syncData(){
        String returnText =null;
        BufferedReader br =null;
        try {
            URL url = new URL("http://10.88.247.131:8080/bitsplease/gesture");
            Log.d("HttpApiRequestAsync",url.toString() );
            int i = 0;
            HttpURLConnection conn = null;

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
}
