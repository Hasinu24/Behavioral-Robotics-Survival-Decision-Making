#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <webots/camera.h>
#include <webots/distance_sensor.h>
#include <webots/motor.h>
#include <webots/robot.h>
#include <webots/receiver.h>

#define MAX_SENSOR_NUMBER 16
#define RANGE (1024 / 2)
#define BOUND(x, a, b) (((x) < (a)) ? (a) : ((x) > (b)) ? (b) : (x))
#define COMMUNICATION_CHANNEL 1

static WbDeviceTag sensors[MAX_SENSOR_NUMBER], camera,camerak, left_motor, right_motor;
static WbDeviceTag communication;
static double matrix[MAX_SENSOR_NUMBER][2];
static int num_sensors;
static double range;
static int time_step = 0;
static double max_speed = 0.0;
static double speed_unit = 1.0;
static int camera_enabled;
static int width,height,pixels;

static int widthk,heightk,pixelsk;
int hunger = 4000;

int thirst = 3000;
int health = 10000;
int max_thirst = 4200;
int max_hunger = 4300;

static void initialize() {
  wb_robot_init();
  time_step = wb_robot_get_basic_time_step();
  
  communication =  wb_robot_get_device("receiver");
  wb_receiver_enable(communication,time_step);
  
  const char khepera_name[] = "ds0";
  char sensors_name[5];
  const double(*temp_matrix)[2];
  camera_enabled = 1;
  range = RANGE;
  const double khepera3_matrix[9][2] = {{-5000, -5000},  {-20000, 40000}, {-30000, 50000}, {-70000, 70000}, {70000, -60000},
                                        {50000, -40000}, {40000, -20000}, {-5000, -5000},  {-10000, -10000}};
  const double khepera3_max_speed = 19.1;
  const double khepera3_speed_unit = 0.00053429;
  num_sensors = 9;
  sprintf(sensors_name, "%s", khepera_name);
  temp_matrix = khepera3_matrix;
  range = 2000;
  max_speed = khepera3_max_speed;
  speed_unit = khepera3_speed_unit;
  int i;
  for (i = 0; i < num_sensors; i++) {
    sensors[i] = wb_robot_get_device(sensors_name);
    wb_distance_sensor_enable(sensors[i], time_step);
    if ((i + 1) >= 10) {
      sensors_name[2] = '1';
      sensors_name[3]++;
      if ((i + 1) == 10) {
        sensors_name[3] = '0';
        sensors_name[4] = '\0';
      }
    } else
      sensors_name[2]++;
      
    int j;
    for (j = 0; j < 2; j++)
      matrix[i][j] = temp_matrix[i][j];
  }

  left_motor = wb_robot_get_device("left wheel motor");
  right_motor = wb_robot_get_device("right wheel motor");
  wb_motor_set_position(left_motor, INFINITY);
  wb_motor_set_position(right_motor, INFINITY);
  wb_motor_set_velocity(left_motor, 0.0);
  wb_motor_set_velocity(right_motor, 0.0);
  if (camera_enabled == 1) {
    camera = wb_robot_get_device("camera");
    wb_camera_enable(camera, time_step);
    width = wb_camera_get_width(camera); // all camera use same 
    height = wb_camera_get_height(camera);
    pixels = height*width;
  }
  
  
  
  if (camera_enabled == 1) {
    camerak = wb_robot_get_device("camera(2)");
    wb_camera_enable(camerak, time_step);
    widthk = wb_camera_get_width(camerak); // all camera use same 
    heightk = wb_camera_get_height(camerak);
    pixelsk = heightk*widthk;
  }
  
  
  }

    /*  Your code under here. Don't touch the above, unless you are happy to fix it yourself! it. */


static void move(int l,int r){
    wb_motor_set_velocity(left_motor, l);
    wb_motor_set_velocity(right_motor, r);}
        
static int left=0;
static int right =0;
static int middle =0;  
static int center=0;

static void Ccamera(int *rgb){
  left =0;middle=0;right=0;
  const unsigned char *image = wb_camera_get_image(camera);

  for (int x = 0; x < width; x++) {
    for (int y = 0; y < height; y++) {
      rgb[0]= wb_camera_image_get_red(image, width, x, y);
      rgb[1]= wb_camera_image_get_blue(image, width, x, y);
      rgb[2]= wb_camera_image_get_green(image, width, x, y);

      
      
      
      if ( x<=width/3 && rgb[1]>150 && rgb[0]<50){
        left++; 
      }
      if( x<=width/3*2 && x>width/3 && rgb[1]>150 && rgb[0]<50){
        middle++;
      }
      if( x<=width && x>width/3*2 && rgb[1]>150 && rgb[1]<50){
        right++;
      }
       
    }
    
  }
    //rgb[0]/=pixels;
    //rgb[1]/=pixels;
   // rgb[2]/=pixels;
  
} 

static int left1=0;
static int right1 =0;
static int middle1 =0;  
static int center1=0;

static void Ccamerak(int *rgbk){
  left1 =0;middle1=0;right1=0;
  const unsigned char *image = wb_camera_get_image(camerak);

  for (int x = 0; x < widthk; x++) {
    for (int y = 0; y < heightk; y++) {
      rgbk[0]= wb_camera_image_get_red(image, widthk, x, y);
      rgbk[1]= wb_camera_image_get_blue(image, widthk, x, y);
      rgbk[2]= wb_camera_image_get_green(image, widthk, x, y);
      
      if ( x<=widthk/3 && rgbk[2]>150 && rgbk[1]<180){
        left1++; 
      }
      if( x<=widthk/3*2 && x>widthk/3 && rgbk[2]>150 && rgbk[1]<180){
        middle1++;
      }
      if( x<=widthk && x>widthk/3*2 && rgbk[2]>150 && rgbk[1]<180){
        right1++;
      }
       
    }
    
  }
    //rgbk[0]/=pixelsk;
    //rgbk[1]/=pixelsk;
   // rgbk[2]/=pixelsk;
  
} 

static void delay(int milliseconds) {
    int steps = milliseconds / time_step; // Calculate the number of steps needed.
    for (int i = 0; i < steps; i++) {
        wb_robot_step(time_step); // Advance the simulation by one step.
    }
}
static void random_walk(){
      const char *direction[] = {"forward","right","left","backward"};
      const char *go =direction[rand() %4];
      
      if (go == direction[0]) { 
        move(2, 2);
        delay(5000);
    } else if (go == direction[1]) { 
        move(2, 0);
        delay(1000);
    } else if (go == direction[2]) { 
        move(0, 2);
        delay(1000);
    } else if (go == direction[3]) {
        move(-2, -2);
        delay(1000);
    }
}

static void compare(int left,int middle,int right){
 int max=0;
 center =0;
 if(left>right ){
   left =max;
   center=1;
 }else{
   center =2;
 }
 if(max<middle){
   center =0;
 }
}

static void compare1(int left1,int middle1,int right1){
 int max1=0;
 center1 =0;
 if(left1>right1 ){
   left1 =max1;
   center1=1;
 }else{
   center1 =2;
 }
 if(max1<middle1){
   center1 =0;
 }
}
static void control_direction(int center){
  if(center ==0){
    move(10,10);
    printf("go straight \n");
  }else if(center==1){
    move(0,8);
    printf("go left \n");
  }else if(center ==2){
    move(8,0);
    printf("go right \n");
  }else{
    random_walk();}
}

static void control_direction1(int center1){
  if(center1 ==0){
    move(10,10);
    printf("go straight \n");
  }else if(center1==1){
    move(0,8);
    printf("go left \n");
  }else if(center1 ==2){
    move(8,0);
    printf("go right \n");
  }
}

static int meta(){
      thirst --;
      hunger --;
      if (thirst <= 0 || hunger <=0 || health <= 0 ){
          return true;
          }
      else {
      return false;
      }    
    } 
    

static void drink(int b) {
    if (b > 200 && thirst < max_thirst) {
        printf("Drinking... \n");
        move(0, 0);  // Stop to "drink."
        thirst+=2;
        printf(" thirst value=%d \n", thirst);
        if (thirst > max_thirst) {
            thirst = max_thirst;
            printf(" drink finished \n");
            
        }
    } 
    else if (b <= 200) {
        printf("Searching for water...\n");
        
        compare(left, middle, right);  // Compare sectors.
        control_direction(center);    // Move in direction of water.
    }
}   

static void eat(int g) {
    if (g > 203 && hunger < max_hunger) {
        printf("Eating... \n");
        move(0, 0);  // Stop to "eat."
        delay(100);
        hunger+=2;
        printf(" hunger value=%d \n", hunger);
        if (hunger > max_hunger) {
            hunger = max_hunger;
        }
    } else if (g <= 203) {
        printf("Searching for food...\n");
        compare1(left1, middle1, right1);  // Compare sectors.
        control_direction1(center1);    // Move in direction of food.
    }
}
            

static void message() {
    // Be cautious with any changes to this function!
    int message_printed = 0;
    // Check if there are any messages in the queue
    if (wb_receiver_get_queue_length(communication) > 0) {
        const char *buffer = wb_receiver_get_data(communication);
        
        

        
        if (message_printed != 1) {
            message_printed = 1;
        }
        
        // Check for specific messages
        int redCheck = strcmp(buffer, "Red");
        int blueCheck = strcmp(buffer, "Blue");

        // Respond to "Red" message
        if (redCheck == 0) {
            health --;
            printf("CAUTION I hear red  \n");
            move(-10,-10);
            delay(500);
            
        }

        // Move to the next packet in the queue
        wb_receiver_next_packet(communication);
    }
}

static int prioritize() {
    

    if (thirst < hunger-500 && thirst < health ) {
        printf("drink\n");
        return 1; // Thirst is the highest priority.
    } else if (hunger <= thirst-500 && hunger < health ) {
        printf("eat\n");
        return 2; // Hunger is the highest priority.
    }
}


int main() {
  initialize();
  
  while (wb_robot_step(time_step) != -1 && meta()==false) {
    
    int rgb[3] = {0, 0, 0};
    int rgbk[3] = {0, 0, 0};
    
    // Capture camera data for both sensors.
    Ccamera(rgb);
    Ccamerak(rgbk);
    compare(left, middle, right);
    compare1(left1, middle1, right1);
    message();
    if(thirst>100000  ){
      random_walk();}
    
    // Print debug information.
    printf("red= %d  blue =%d green =%d\n", rgb[0], rgb[1], rgb[2]);
    printf("red1= %d  blue1 =%d green1 =%d\n", rgbk[0], rgbk[1], rgbk[2]);
    
    
    int action = prioritize();
    
    printf("%d\n", action);
    printf("hunger value = %d\n", hunger);
    printf("thirst value =%d\n", thirst);
    if (action == 1) {
        drink(rgb[1]); // Handle water-seeking logic.
    } else if (action == 2) {
        eat(rgbk[2]); // Handle food-seeking logic.
    }  
    
    // Handle any communication messages.
    message();
    }

  return 0;
}