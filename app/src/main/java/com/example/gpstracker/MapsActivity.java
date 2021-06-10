package com.example.gpstracker;

import android.Manifest;
import android.annotation.SuppressLint;
import android.bluetooth.BluetoothAdapter;
import android.bluetooth.BluetoothDevice;
import android.content.BroadcastReceiver;
import android.content.Context;
import android.content.Intent;
import android.content.IntentFilter;
import android.content.SharedPreferences;
import android.content.pm.PackageManager;
import android.graphics.Color;
import android.graphics.drawable.Drawable;
import android.location.Location;
import android.location.LocationListener;
import android.location.LocationManager;
import android.os.Build;
import android.os.Bundle;
import android.util.Log;
import android.view.MotionEvent;
import android.view.View;
import android.view.animation.Animation;
import android.view.animation.AnimationUtils;
import android.widget.AdapterView;
import android.widget.Button;
import android.widget.CheckBox;
import android.widget.CompoundButton;
import android.widget.EditText;
import android.widget.LinearLayout;
import android.widget.ListView;
import android.widget.NumberPicker;
import android.widget.RelativeLayout;
import android.widget.TextView;
import android.widget.Toast;

import androidx.annotation.NonNull;
import androidx.appcompat.app.AppCompatDelegate;
import androidx.cardview.widget.CardView;
import androidx.core.app.ActivityCompat;
import androidx.core.content.ContextCompat;
import androidx.fragment.app.FragmentActivity;
import androidx.localbroadcastmanager.content.LocalBroadcastManager;

import com.google.android.gms.location.FusedLocationProviderClient;
import com.google.android.gms.location.LocationServices;
import com.google.android.gms.maps.CameraUpdate;
import com.google.android.gms.maps.CameraUpdateFactory;
import com.google.android.gms.maps.GoogleMap;
import com.google.android.gms.maps.OnMapReadyCallback;
import com.google.android.gms.maps.SupportMapFragment;
import com.google.android.gms.maps.model.LatLng;
import com.google.android.gms.maps.model.Marker;
import com.google.android.gms.maps.model.MarkerOptions;
import com.google.android.gms.maps.model.Polyline;
import com.google.android.gms.maps.model.PolylineOptions;
import com.google.android.gms.tasks.OnCompleteListener;
import com.google.android.gms.tasks.Task;
import com.google.android.material.floatingactionbutton.FloatingActionButton;
import com.google.gson.Gson;
import com.google.gson.reflect.TypeToken;

import java.lang.reflect.Type;
import java.nio.charset.Charset;
import java.util.ArrayList;
import java.util.List;
import java.util.ListIterator;
import java.util.Map;
import java.util.UUID;

public class MapsActivity extends FragmentActivity implements OnMapReadyCallback,AdapterView.OnItemClickListener {

    private static final String TAG ="MapsActivity: " ;
    private GoogleMap mMap;
    private LocationListener locationListener;
    private LocationManager locationManager;
    Button btnEnableDisable_Discoverable;


    public BluetoothConnectionService mBluetoothConnection;
   // int flag_last_tour=0;
    CardView cardView_btn;
    CardView secMain;
    CardView cardView_speed;
    Button btnStartConnection;
    Button btnSend;
    Button btnstop;
    EditText etSend;
    TextView msgtxt;
    StringBuilder stringBuilder;
    RelativeLayout main;
    SupportMapFragment mapFragment;
    BluetoothDevice mBTDevice;
    CheckBox checkBox;
    CheckBox newcheck;
    int g=1;

    public ArrayList<BluetoothDevice> mBTDevices = new ArrayList<>();

    public DeviceListAdapter mDeviceListAdapter;

    ListView lvNewDevices;
    private String p1,p2;
    private static final UUID MY_UUID_INSECURE =
            UUID.fromString("00001101-0000-1000-8000-00805F9B34FB");

MarkerOptions place1,place2;
Polyline currentPolyline;
List<Double>latlang;
    BluetoothAdapter mBluetoothAdapter;
    Marker change;

Button rightbtn,leftbtn,upbtn,downbtn;
int lat_index=2;
int lon_index=3;
int z=4;
List<Integer> prev;
List<Integer> prev_l;
NumberPicker numberPicker;
    PolylineOptions options;
    private final BroadcastReceiver mBroadcastReceiver1 = new BroadcastReceiver() {
        public void onReceive(Context context, Intent intent) {
            String action = intent.getAction();
            // When discovery finds a device
            if (action.equals(mBluetoothAdapter.ACTION_STATE_CHANGED)) {
                final int state = intent.getIntExtra(BluetoothAdapter.EXTRA_STATE, mBluetoothAdapter.ERROR);

                switch(state){
                    case BluetoothAdapter.STATE_OFF:
                        Log.d(TAG, "onReceive: STATE OFF");
                        break;
                    case BluetoothAdapter.STATE_TURNING_OFF:
                        Log.d(TAG, "mBroadcastReceiver1: STATE TURNING OFF");
                        break;

                    case BluetoothAdapter.STATE_ON:
                        Log.d(TAG, "mBroadcastReceiver1: STATE ON");
                        break;
                    case BluetoothAdapter.STATE_TURNING_ON:
                        Log.d(TAG, "mBroadcastReceiver1: STATE TURNING ON");
                        break;
                }
            }
        }
    };

    /**
     * Broadcast Receiver for changes made to bluetooth states such as:
     * 1) Discoverability mode on/off or expire.
     */
    private final BroadcastReceiver mBroadcastReceiver2 = new BroadcastReceiver() {

        @Override
        public void onReceive(Context context, Intent intent) {
            final String action = intent.getAction();

            if (action.equals(BluetoothAdapter.ACTION_SCAN_MODE_CHANGED)) {

                int mode = intent.getIntExtra(BluetoothAdapter.EXTRA_SCAN_MODE, BluetoothAdapter.ERROR);

                switch (mode) {
                    //Device is in Discoverable Mode
                    case BluetoothAdapter.SCAN_MODE_CONNECTABLE_DISCOVERABLE:
                        Log.d(TAG, "mBroadcastReceiver2: Discoverability Enabled.");
                        break;
                    //Device not in discoverable mode
                    case BluetoothAdapter.SCAN_MODE_CONNECTABLE:
                        Log.d(TAG, "mBroadcastReceiver2: Discoverability Disabled. Able to receive connections.");
                        break;
                    case BluetoothAdapter.SCAN_MODE_NONE:
                        Log.d(TAG, "mBroadcastReceiver2: Discoverability Disabled. Not able to receive connections.");
                        break;
                    case BluetoothAdapter.STATE_CONNECTING:
                        Log.d(TAG, "mBroadcastReceiver2: Connecting....");
                        break;
                    case BluetoothAdapter.STATE_CONNECTED:
                        Log.d(TAG, "mBroadcastReceiver2: Connected.");
                        break;
                }

            }
        }
    };

    private final BroadcastReceiver mBroadcastReceiver3 = new BroadcastReceiver() {
        @Override
        public void onReceive(Context context, Intent intent) {
            final String action = intent.getAction();
            Log.d(TAG, "onReceive: ACTION FOUND.");

            if (action.equals(BluetoothDevice.ACTION_FOUND)){
                BluetoothDevice device = intent.getParcelableExtra (BluetoothDevice.EXTRA_DEVICE);
                mBTDevices.add(device);
                Log.d(TAG, "onReceive: " + device.getName() + ": " + device.getAddress());
                mDeviceListAdapter = new DeviceListAdapter(context, R.layout.device_adapter_view, mBTDevices);
                lvNewDevices.setAdapter(mDeviceListAdapter);
            }
        }
    };



    /**
     * Broadcast Receiver that detects bond state changes (Pairing status changes)
     */
    private  BroadcastReceiver mBroadcastReceiver4 = new BroadcastReceiver() {
        @Override
        public void onReceive(Context context, Intent intent) {
            final String action = intent.getAction();

            if(action.equals(BluetoothDevice.ACTION_BOND_STATE_CHANGED)){
                BluetoothDevice mDevice = intent.getParcelableExtra(BluetoothDevice.EXTRA_DEVICE);
                //3 cases:
                //case1: bonded already
                if (mDevice.getBondState() == BluetoothDevice.BOND_BONDED){
                    Log.d(TAG, "BroadcastReceiver: BOND_BONDED.");
                    //inside BroadcastReceiver4
                    mBTDevice = mDevice;
                }
                //case2: creating a bone
                if (mDevice.getBondState() == BluetoothDevice.BOND_BONDING) {
                    Log.d(TAG, "BroadcastReceiver: BOND_BONDING.");
                }
                //case3: breaking a bond
                if (mDevice.getBondState() == BluetoothDevice.BOND_NONE) {
                    Log.d(TAG, "BroadcastReceiver: BOND_NONE.");
                }
            }
        }
    };

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_maps);
        main=findViewById(R.id.activity_main);


        // Obtain the SupportMapFragment and get notified when the map is ready to be used.
         mapFragment = (SupportMapFragment) getSupportFragmentManager()
                .findFragmentById(R.id.map);
        ActivityCompat.requestPermissions(this,
                new String[]{Manifest.permission.ACCESS_FINE_LOCATION}, PackageManager.PERMISSION_GRANTED);
        ActivityCompat.requestPermissions(this,
                new String[]{Manifest.permission.ACCESS_COARSE_LOCATION}, PackageManager.PERMISSION_GRANTED);
        Button btnONOFF = (Button) findViewById(R.id.btnONOFF);
        btnEnableDisable_Discoverable = (Button) findViewById(R.id.btnDiscoverable_on_off);
        lvNewDevices = (ListView) findViewById(R.id.lvNewDevices);
        mBTDevices = new ArrayList<>();
        btnstop=findViewById(R.id.stopbtn);

        btnStartConnection = (Button) findViewById(R.id.btnStartConnection);
        btnSend = (Button) findViewById(R.id.btnSend);
        etSend = (EditText) findViewById(R.id.editText);
        cardView_btn=findViewById(R.id.btn_lay);
        cardView_speed=findViewById(R.id.speed_lay);
        msgtxt=(TextView) findViewById(R.id.incomingmsg);
        stringBuilder=new StringBuilder();
        LocalBroadcastManager.getInstance(this).registerReceiver(mReceiver,new IntentFilter("IncomingMessage"));
        //Broadcasts when bond state changes (ie:pairing)
        IntentFilter filter = new IntentFilter(BluetoothDevice.ACTION_BOND_STATE_CHANGED);
        registerReceiver(mBroadcastReceiver4, filter);
        checkBox=findViewById(R.id.checkLast);
        mBluetoothAdapter = BluetoothAdapter.getDefaultAdapter();
newcheck=findViewById(R.id.checknew);
        lvNewDevices.setOnItemClickListener((AdapterView.OnItemClickListener) MapsActivity.this);
secMain=findViewById(R.id.secondMain);

        btnONOFF.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                Log.d(TAG, "onClick: enabling/disabling bluetooth.");
                enableDisableBT();
            }
        });

        btnStartConnection.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                startConnection();


            }
        });
        btnstop.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                String s="s.";
                byte[] bytes = s.getBytes(Charset.defaultCharset());
                if(mBluetoothConnection!=null && bytes!=null)
                    mBluetoothConnection.write(bytes);
            }
        });
        checkBox.setOnCheckedChangeListener(new CompoundButton.OnCheckedChangeListener() {
            @Override
            public void onCheckedChanged(CompoundButton buttonView, boolean isChecked) {
                String s="@.";
                byte[] bytes = s.getBytes(Charset.defaultCharset());
                if(mBluetoothConnection!=null && bytes!=null)
                    mBluetoothConnection.write(bytes);

            }
        });
        newcheck.setOnCheckedChangeListener(new CompoundButton.OnCheckedChangeListener() {
            @Override
            public void onCheckedChanged(CompoundButton buttonView, boolean isChecked) {

                String s="n.";
                byte[] bytes = s.getBytes(Charset.defaultCharset());
                if(mBluetoothConnection!=null && bytes!=null)
                    mBluetoothConnection.write(bytes);}

        });

        btnSend.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                String s=etSend.getText().toString()+".";
                    byte[] bytes = s.getBytes(Charset.defaultCharset());

                if(mBluetoothConnection!=null && bytes!=null)
                    mBluetoothConnection.write(bytes);

            }
        });
        leftbtn=findViewById(R.id.left_btn);
        rightbtn=findViewById(R.id.right_btn);
        upbtn=findViewById(R.id.up_btn);
        downbtn=findViewById(R.id.down_btn);

        numberPicker=findViewById(R.id.numberpicker);
numberPicker.setMaxValue(100);
numberPicker.setMinValue(0);
numberPicker.setValue(50);
        numberPicker.setOnValueChangedListener(new NumberPicker.OnValueChangeListener() {
    @Override
    public void onValueChange(NumberPicker picker, int oldVal, int newVal) {
        StringBuilder s=new StringBuilder();
        s.append(newVal);
        s.append('.');
        byte[] bytes = s.toString().getBytes(Charset.defaultCharset());
        if(mBluetoothConnection!=null && bytes!=null)
        {mBluetoothConnection.write(bytes);
        }
        Log.d(TAG,s.toString());
    }
});



        leftbtn.setOnTouchListener(new View.OnTouchListener() {
            @Override
            public boolean onTouch(View v, MotionEvent event) {

                if(event.getAction()==MotionEvent.ACTION_DOWN || event.getAction()==MotionEvent.ACTION_UP) {
                    String c = "l.";
                    if(event.getAction()==MotionEvent.ACTION_DOWN)
                    leftbtn.setBackground(ContextCompat.getDrawable(MapsActivity.this,R.drawable.arrowbaxk2));
                    else
                        leftbtn.setBackground(ContextCompat.getDrawable(MapsActivity.this,R.drawable.ic_baseline_arrow_back_24));

                    byte[] bytes = c.getBytes(Charset.defaultCharset());
                    if (mBluetoothConnection != null && bytes != null) {
                        mBluetoothConnection.write(bytes);
                    }
                    Log.d(TAG, c);

                }


                return true;   }


        });

        rightbtn.setOnTouchListener(new View.OnTouchListener() {
            @Override
            public boolean onTouch(View v, MotionEvent event) {
                if(event.getAction()==MotionEvent.ACTION_DOWN || event.getAction()==MotionEvent.ACTION_UP) {
                    if(event.getAction()==MotionEvent.ACTION_DOWN)
                        rightbtn.setBackground(ContextCompat.getDrawable(MapsActivity.this,R.drawable.forward_2));
                    else
                    rightbtn.setBackground(ContextCompat.getDrawable(MapsActivity.this,R.drawable.ic_baseline_arrow_forward_24));
                    String c = "r.";
                    byte[] bytes = c.getBytes(Charset.defaultCharset());
                    if (mBluetoothConnection != null && bytes != null) {
                        mBluetoothConnection.write(bytes);
                    }
                    Log.d(TAG, c);

                }

                return true;   }
        });
        downbtn.setOnTouchListener(new View.OnTouchListener() {
            @Override
            public boolean onTouch(View v, MotionEvent event) {
                if(event.getAction()==MotionEvent.ACTION_DOWN || event.getAction()==MotionEvent.ACTION_UP) {
                    if(event.getAction()==MotionEvent.ACTION_DOWN)
                        downbtn.setBackground(ContextCompat.getDrawable(MapsActivity.this,R.drawable.downword2));
                    else
                        downbtn.setBackground(ContextCompat.getDrawable(MapsActivity.this,R.drawable.ic_baseline_arrow_downward_24));
                    String c = "d.";
                    byte[] bytes = c.getBytes(Charset.defaultCharset());
                    if (mBluetoothConnection != null && bytes != null) {
                        mBluetoothConnection.write(bytes);


                    }
                    Log.d(TAG, c);

                }
                return true;   }

        });
        upbtn.setOnTouchListener(new View.OnTouchListener() {
            @Override
            public boolean onTouch(View v, MotionEvent event) {
                if(event.getAction()==MotionEvent.ACTION_DOWN || event.getAction()==MotionEvent.ACTION_UP) {
                    if(event.getAction()==MotionEvent.ACTION_DOWN)
                        upbtn.setBackground(ContextCompat.getDrawable(MapsActivity.this,R.drawable.up2));
                    else
                        upbtn.setBackground(ContextCompat.getDrawable(MapsActivity.this,R.drawable.up));
                    String c="u.";
                    byte[] bytes = c.getBytes(Charset.defaultCharset());
                    if(mBluetoothConnection!=null && bytes!=null)
                    {mBluetoothConnection.write(bytes);


                    }
                    Log.d(TAG, c);

                }

                return true;   }

        });



        stringBuilder=new StringBuilder();
        latlang=new ArrayList<>();
        place2 = new MarkerOptions();

 prev=new ArrayList<>();
        prev_l=new ArrayList<>();
        prev.add(0);
        prev_l.add(0);
         options = new PolylineOptions().width(5).color(Color.BLUE).geodesic(true);
        mapFragment.getMapAsync(this);
    }
    BroadcastReceiver mReceiver=new BroadcastReceiver() {

        @Override
        public void onReceive(Context context, Intent intent) {
            String txt = intent.getStringExtra("msg");
            if (txt.equals("y")) {

                msgtxt.setText("Correct Password");

                try {
                    Thread.sleep(500);
                } catch (InterruptedException e) {
                    e.printStackTrace();
                }

                mapFragment.getMapAsync(MapsActivity.this);
                cardView_btn.setVisibility(View.VISIBLE);
                btnstop.setVisibility(View.VISIBLE);
                main.setVisibility(View.INVISIBLE);
                secMain.setVisibility(View.VISIBLE);
                cardView_speed.setVisibility(View.VISIBLE);


            }

            stringBuilder.append(txt);
            String s = stringBuilder.toString();
            Log.d(TAG, "String Builder: " + s);

            if (txt.contains(" ") ) {
                int f1 = 0;
                int f2 = 0;
                int x = 0;
                int y = 0;

                if (s.contains("/")) {
                    for (int i = 0; i < s.length(); i++) {

                        if (s.charAt(i) == '/' && !prev.contains(i) && f1 == 0) {
                            prev.add(i);
                           stringBuilder.replace(i,i+1,"/");
                            x = i;
                            Log.d(TAG, "index/ : " + i);

                            f1 = 1;

                        }
                        if (s.charAt(i) == ' ' && !prev_l.contains(i) && f2 == 0 && (f1==1|| g==2)) {
                            Log.d(TAG, "index space : " + i);
                            prev_l.add(i);
                            y = i;
                            f2 = 1;


                        }
                        if (f1 == 1 && f2 == 1) break;

                    }
                    if (g == 1) {
                        try{
                            latlang.add(Double.parseDouble(s.substring(x+1, y)));}
                        catch (Exception e){
                            Log.e(TAG,e.getMessage());
                        }
                        //Log.d(TAG, latlang.toString());

                        g = 2;
                    } else if (g == 2) {
                       try{ latlang.add( Double.parseDouble(s.substring(prev_l.get(prev_l.size()-2),x)));}
                         catch (Exception e){
                            Log.e(TAG,e.getMessage());
                        }
                        g = 1;
                    }

                    Log.d(TAG, latlang.toString());
                    if (latlang.size() == 2) {
                        Log.d(TAG, "---------------------------------------------------------------------");

                        options.add(new LatLng(latlang.get(0), latlang.get(1)));
                        currentPolyline = mMap.addPolyline(options);
                        place1 = new MarkerOptions().position(new LatLng(latlang.get(0), latlang.get(1))).title("Start Location");
                        mMap.addMarker(place1);
                        mMap.moveCamera(CameraUpdateFactory.newLatLngZoom(new LatLng(latlang.get(0), latlang.get(1)),14f));
                    } else if (latlang.size() == z) {

                       double dis=distance(latlang.get(lat_index-2),latlang.get(lon_index-2),latlang.get(lat_index),latlang.get(lon_index));
                       if(dis<5){
                        Log.d(TAG, "Distance is:"+dis);

                        place2.position(new LatLng(latlang.get(lat_index), latlang.get(lon_index))).title(" New Location");
                        if(change!=null)change.remove();
                       change=mMap.addMarker(place2);

                        options.add(new LatLng(latlang.get(lat_index), latlang.get(lon_index)));
                        currentPolyline = mMap.addPolyline(options);
                        lat_index += 2;
                        lon_index += 2;
                        z += 2;
                        }

                       else  Log.d(TAG, "Distance is:"+dis);

                    }


                }
            }
        }
    };

    @Override
    public void onMapReady(GoogleMap googleMap) {
        mMap = googleMap;
        /*if(flag_last_tour==1){

            SharedPreferences sharedPreferences=getSharedPreferences("last",MODE_PRIVATE);
            Gson gson=new Gson();
            String json=sharedPreferences.getString("list",null);
            Type type=new TypeToken<ArrayList<Double>>(){}.getType();
            latlang=gson.fromJson(json,type);
            if(latlang!=null){

                for(int i=0;i<latlang.size();i+=2){


                    options.add(new LatLng(latlang.get(i), latlang.get(i+1)));

                }
                mMap.addPolyline(options);


            }


        }*/

    }





    private double distance(double lat1, double lon1, double lat2, double lon2) {
        double theta = lon1 - lon2;
        double dist = Math.sin(deg2rad(lat1))
                * Math.sin(deg2rad(lat2))
                + Math.cos(deg2rad(lat1))
                * Math.cos(deg2rad(lat2))
                * Math.cos(deg2rad(theta));
        dist = Math.acos(dist);
        dist = rad2deg(dist);
        dist = dist * 60 * 1.1515;
        return (dist);
    }

    private double deg2rad(double deg) {
        return (deg * Math.PI / 180.0);
    }

    private double rad2deg(double rad) {
        return (rad * 180.0 / Math.PI);
    }


    /**
     * starting chat service method
     */

   public void startConnection(){
        startBTConnection(mBTDevice,MY_UUID_INSECURE);
    }

    /**
     * starting chat service method
     */
    public void startBTConnection(BluetoothDevice device, UUID uuid){
        Log.d(TAG, "startBTConnection: Initializing RFCOM Bluetooth Connection.");

        if(mBluetoothConnection!=null)
            mBluetoothConnection.startClient(device,uuid);
    }



    public void enableDisableBT(){
        if(mBluetoothAdapter == null){
            Log.d(TAG, "enableDisableBT: Does not have BT capabilities.");
        }
        else if(!mBluetoothAdapter.isEnabled()){
            Log.d(TAG, "enableDisableBT: enabling BT.");
            Intent enableBTIntent = new Intent(BluetoothAdapter.ACTION_REQUEST_ENABLE);
            startActivity(enableBTIntent);

            IntentFilter BTIntent = new IntentFilter(BluetoothAdapter.ACTION_STATE_CHANGED);
            registerReceiver(mBroadcastReceiver1, BTIntent);
        }
        else  if(mBluetoothAdapter.isEnabled()){
            Log.d(TAG, "enableDisableBT: disabling BT.");
            mBluetoothAdapter.disable();

            IntentFilter BTIntent = new IntentFilter(BluetoothAdapter.ACTION_STATE_CHANGED);
            registerReceiver(mBroadcastReceiver1, BTIntent);
        }

    }


    public void btnEnableDisable_Discoverable(View view) {

        Log.d(TAG, "btnEnableDisable_Discoverable: Making device discoverable for 300 seconds.");

        Intent discoverableIntent = new Intent(BluetoothAdapter.ACTION_REQUEST_DISCOVERABLE);
        discoverableIntent.putExtra(BluetoothAdapter.EXTRA_DISCOVERABLE_DURATION, 300);
        startActivity(discoverableIntent);

        IntentFilter intentFilter = new IntentFilter(mBluetoothAdapter.ACTION_SCAN_MODE_CHANGED);
        registerReceiver(mBroadcastReceiver2,intentFilter);

    }

    public void btnDiscover(View view) {

        Log.d(TAG, "btnDiscover: Looking for unpaired devices.");

        if(mBluetoothAdapter!=null && mBluetoothAdapter.isDiscovering()){
            mBluetoothAdapter.cancelDiscovery();
            Log.d(TAG, "btnDiscover: Canceling discovery.");

            //check BT permissions in manifest
            checkBTPermissions();

            mBluetoothAdapter.startDiscovery();
            IntentFilter discoverDevicesIntent = new IntentFilter(BluetoothDevice.ACTION_FOUND);
            registerReceiver(mBroadcastReceiver3, discoverDevicesIntent);
        }
        else if(mBluetoothAdapter!=null && !mBluetoothAdapter.isDiscovering()){

            //check BT permissions in manifest
            checkBTPermissions();

            mBluetoothAdapter.startDiscovery();
            IntentFilter discoverDevicesIntent = new IntentFilter(BluetoothDevice.ACTION_FOUND);
            registerReceiver(mBroadcastReceiver3, discoverDevicesIntent);
        }
    }

    /**
     * This method is required for all devices running API23+
     * Android must programmatically check the permissions for bluetooth. Putting the proper permissions
     * in the manifest is not enough.
     *
     * NOTE: This will only execute on versions > LOLLIPOP because it is not needed otherwise.
     */
    private void checkBTPermissions() {
        if(Build.VERSION.SDK_INT > Build.VERSION_CODES.LOLLIPOP){
            int permissionCheck = 0;
            if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.M) {
                permissionCheck = this.checkSelfPermission("Manifest.permission.ACCESS_FINE_LOCATION");
            }
            if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.M) {
                permissionCheck += this.checkSelfPermission("Manifest.permission.ACCESS_COARSE_LOCATION");
            }
            if (permissionCheck != 0) {

                if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.M) {
                    this.requestPermissions(new String[]{Manifest.permission.ACCESS_FINE_LOCATION, Manifest.permission.ACCESS_COARSE_LOCATION}, 1001); //Any number
                }
            }
        }else{
            Log.d(TAG, "checkBTPermissions: No need to check permissions. SDK version < LOLLIPOP.");
        }
    }

    @Override
    public void onItemClick(AdapterView<?> adapterView, View view, int i, long l) {
        //first cancel discovery because its very memory intensive.
        mBluetoothAdapter.cancelDiscovery();

        Log.d(TAG, "onItemClick: You Clicked on a device.");
        String deviceName = mBTDevices.get(i).getName();
        String deviceAddress = mBTDevices.get(i).getAddress();

        Log.d(TAG, "onItemClick: deviceName = " + deviceName);
        Log.d(TAG, "onItemClick: deviceAddress = " + deviceAddress);

        //create the bond.
        //NOTE: Requires API 17+? I think this is JellyBean
        if(Build.VERSION.SDK_INT > Build.VERSION_CODES.JELLY_BEAN_MR2){
            Log.d(TAG, "Trying to pair with " + deviceName);
            mBTDevices.get(i).createBond();

            mBTDevice = mBTDevices.get(i);
            mBluetoothConnection = new BluetoothConnectionService(MapsActivity.this);
        }
    }

    @Override
    protected void onDestroy() {
        super.onDestroy();
        unregisterReceiver(mBroadcastReceiver4);
      //SharedPreferences sharedPreferences=getSharedPreferences("last",MODE_PRIVATE);
      //  SharedPreferences.Editor editor=sharedPreferences.edit();
        //Gson gson=new Gson();
        //String json=gson.toJson(latlang);
       // editor.putString("list",json);
       //editor.apply();
       //editor.commit();
    }
}