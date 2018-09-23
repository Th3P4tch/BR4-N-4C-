//l298n pins (pwm)
#define in1 3
#define in2 5
#define in3 6
#define in4 9
//speed values
#define zero 0
#define one 51
#define two 51*2
#define three 51*3
#define four 51*4
#define five 51*5
//sensors bins
#define front_sen 8
#define middle_sen 10
#define left_sen 12
#define right_sen 13
//loop variables
int lp = 0;
int curcase,read_front,read_middle,read_left,read_right;

void setup() {
  //l298n pins
  pinMode(in1,1);  
  pinMode(in2,1);
  pinMode(in3,1);
  pinMode(in4,1);
  //IR pins
  pinMode(8,0);
  pinMode(10,0);
  pinMode(12,0);
  pinMode(13,0);  
  Serial.begin(9600);
}

void loop() {
read_all();
forward();
}

//0 -> white
//1 -> black
void read_all(){
  read_front = read(front_sen);
  read_middle = read(middle_sen);
  read_left = read(left_sen); 
  read_right = read(right_sen);
  }
int read(int sensor){
  return digitalRead(sensor);
  }

void stop(){
  move('l','s');
  move('r','s');
  }
void backward(char speed = one){
  move('l','b',speed);
  move('r','b',speed);
  }

void right(char speed = one){
  move('l','b',zero);
  move('r','f',speed);
  }

void left(char speed = one){
  move('l','f',speed);
  move('r','b',zero);
  }

void forward(char speed = one){
move('l','f',speed);
move('r','f',speed);
  }
//left motor: l
//  in1 back b
//  out1 => -ve
//  out2 => +ve
//  in2 forward f
//  out1 => +ve
//  out2 => -ve
//right motor: r
//  in3 back  b
//  out3 => -ve
//  out4 => +ve
//  in4 forward f
//  out3 => +ve
//  out4 => -ve
//  left -> l
//  right -> r
void move(char motor,char dir,char speed = zero){
  if(motor == 'l'){
    if(dir == 'b'){
      analogWrite(in1,0);
      analogWrite(in2,speed);
      }else if(dir == 'f'){
              analogWrite(in1,speed);
              analogWrite(in2,0);
        }else if(dir == 's'){//stop
          analogWrite(in1,0); 
          analogWrite(in2,0);  
          }
    }else{
      if(dir == 'b'){
        analogWrite(in3,0);
        analogWrite(in4,speed);
        }else if(dir == 'f'){
          analogWrite(in3,speed);
          analogWrite(in4,0);
          }else if(dir == 's'){//stop
            analogWrite(in3,0);
            analogWrite(in4,0); 
            }
      }
  }
