# 1 "d:\\AKSANTARA\\FW KRTI 2018\\code\\Tracker_v2.0_noTilt_r2\\Tracker_v2.0_noTilt_r2.ino"
# 1 "d:\\AKSANTARA\\FW KRTI 2018\\code\\Tracker_v2.0_noTilt_r2\\Tracker_v2.0_noTilt_r2.ino"
//Mapping PWM from Pixhawk to Motor Driver
//by ramhdi, 23/02/2018, 20.23

//Tracker_v2.0, updated 20/03/2018
//added tilt feature
//uses TrackerMotor.h
// 02/06/2018
// removed tilt
// 26/08/2018
// added map
// 27/08/2018
// uses BTS7960 class
// uses PWM read library from github.com/xkam1x/Arduino-PWM-Reader

/*

 * Mode kerja Tracker Antenna:

 * 1. Position -> Pixhawk mengeluarkan sinyal PWM yang menandakan posisi (1100 <= PWM <= 1900) -> cocok untuk servo standar

 * 2. Continuous -> Pixhawk mengeluarkan sinyal PWM yang menandakan kecepatan dan arah gerak (1100 <= PWM <= 1900) -> cocok untuk servo continuous

 * 3. On-off -> Pixhawk mengeluarkan sinyal yang menandakan hanya arah gerak (PWM == 1100 || PWM == 1900) -> tidak ada informasi kecepatan yang dibutuhkan

 * 

 * Program ini dibuat untuk Tracker dengan mode continuous

 */
# 24 "d:\\AKSANTARA\\FW KRTI 2018\\code\\Tracker_v2.0_noTilt_r2\\Tracker_v2.0_noTilt_r2.ino"
/*

 * Cara kerja:

 * Pixhawk mengeluarkan PWM 1100 - 1500, pesawat ada di kiri tracker (tracker gerak CCW) 

 * Pixhawk mengeluarkan PWM 1500 - 1900, pesawat ada di kanan tracker (tracker gerak CW)

 * Pixhawk mengeluarkan PWM  +/- 1500, pesawat ada di depan tracker (tracker diam)

 * PWM terdeteksi di luar range (PWM < 1100 || PWM > 1900) masukan tidak valid (tracker diam)

 */
# 32 "d:\\AKSANTARA\\FW KRTI 2018\\code\\Tracker_v2.0_noTilt_r2\\Tracker_v2.0_noTilt_r2.ino"
# 33 "d:\\AKSANTARA\\FW KRTI 2018\\code\\Tracker_v2.0_noTilt_r2\\Tracker_v2.0_noTilt_r2.ino" 2
# 34 "d:\\AKSANTARA\\FW KRTI 2018\\code\\Tracker_v2.0_noTilt_r2\\Tracker_v2.0_noTilt_r2.ino" 2
# 35 "d:\\AKSANTARA\\FW KRTI 2018\\code\\Tracker_v2.0_noTilt_r2\\Tracker_v2.0_noTilt_r2.ino" 2


# 36 "d:\\AKSANTARA\\FW KRTI 2018\\code\\Tracker_v2.0_noTilt_r2\\Tracker_v2.0_noTilt_r2.ino"
//deklarasi param motor pan dan tilt
BTS7960 pan(7, 8, 5, 6);

//deklarasi pembacaan pwm
PWM pwm_pan(2);

int pan_dir, pan_speed, pan_val = 0;
String dbg;

const int pan_speed_max = 57;
const int pan_speed_min = 29;
const int db_mid = 5;
const int db_edge = 5;

uint32_t t_now, t_last = 0;

void setup()
{
  Serial.begin(115200); // Serial for debug

  pwm_pan.begin(1); //1 = high

  pan.attach();
}

void loop()
{
  t_now = millis();
  if (t_now - t_last >= 10)
  {
    t_last = millis();

    // baca nilai pwm pan
    pan_val = pwm_pan.getValue();

    // print nilai pwm pan
    Serial.print("PWM pan = "); Serial.println(pan_val);

    // default: motor pan diam
    pan_dir = 0;
    pan_speed = 0;
    dbg = "PAN_STOP";

    if (pan_val >= 1100 - db_edge && pan_val <= 1500 - db_mid) // 1095 <= pan_val <= 1475
    {
      // motor pan cw
      pan_dir = 1;
      pan_speed = map(pan_val, 1475, 1095, pan_speed_min, pan_speed_max);
      dbg = "PAN_CW spd = " + String(pan_speed);
    }

    else if (pan_val >= 1500 + db_mid && pan_val <= 1900 + db_edge) // 1525 <= pan_val <= 1905
    {
      // motor pan ccw
      pan_dir = 2;
      pan_speed = map(pan_val, 1525, 1905, pan_speed_min, pan_speed_max);
      dbg = "PAN_CCW spd = " + String(pan_speed);
    }

    pan.move(pan_dir, pan_speed);
    Serial.println(dbg);

  }
}
