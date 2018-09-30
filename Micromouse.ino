//l298n pins (pwm)
#define in1 3
#define in2 4
#define ena 5
#define enb 6
#define in3 7
#define in4 8
//speed values
#define zero 0
#define one 51
#define two 51*2
#define three 51*3
#define four 51*4
#define five 51*5
//sensors bins
#define left_sen 9
#define right_sen 10
//loop variables
int lp = 0;
int curcase,read_front,read_middle,read_left,read_right;

void setup() {
  //l298n pins
  pinMode(ena,1);  
  pinMode(in1,1);  
  pinMode(in2,1);
  pinMode(in3,1);
  pinMode(in4,1);
  pinMode(enb,1);
  //IR pins
  pinMode(8,0);
  pinMode(9,0);
  pinMode(10,0);
  pinMode(11,0);  
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
      digitalWrite(in1,0);
      digitalWrite(in2,1);
      analogWrite(ena,speed);
      }else if(dir == 'f'){
              digitalWrite(in1,1);
              digitalWrite(in2,0);
              analogWrite(ena,speed);
        }else if(dir == 's'){//stop
          digitalWrite(in1,0); 
          digitalWrite(in2,0);
          analogWrite(ena,speed);
          }
    }else{
      if(dir == 'b'){
        digitalWrite(in3,0);
        digitalWrite(in4,1);
        analogWrite(enb,speed);
        }else if(dir == 'f'){
          digitalWrite(in3,1);
          digitalWrite(in4,0);
          analogWrite(enb,speed);
          }else if(dir == 's'){//stop
            digitalWrite(in3,0);
            digitalWrite(in4,0);
            analogWrite(enb,speed); 
            }
      }
  }
  /*
                                                                                                                                                        
                                                                                                                                                      
                         ___                            ___                            ___                                                            
                         `MM                            `MM                            `MM                                                            
                          MM                             MM                             MM                                                      /     
___   ___ ___  __     ____MM   ____  ___  __         ____MM   ____  ____    ___  ____   MM   _____  __ ____  ___  __    __     ____  ___  __   /M     
`MM    MM `MM 6MMb   6MMMMMM  6MMMMb `MM 6MM        6MMMMMM  6MMMMb `MM(    )M' 6MMMMb  MM  6MMMMMb `M6MMMMb `MM 6MMb  6MMb   6MMMMb `MM 6MMb /MMMMM  
 MM    MM  MMM9 `Mb 6M'  `MM 6M'  `Mb MM69 "       6M'  `MM 6M'  `Mb `Mb    d' 6M'  `Mb MM 6M'   `Mb MM'  `Mb MM69 `MM69 `Mb 6M'  `Mb MMM9 `Mb MM     
 MM    MM  MM'   MM MM    MM MM    MM MM'          MM    MM MM    MM  YM.  ,P  MM    MM MM MM     MM MM    MM MM'   MM'   MM MM    MM MM'   MM MM     
 MM    MM  MM    MM MM    MM MMMMMMMM MM           MM    MM MMMMMMMM   MM  M   MMMMMMMM MM MM     MM MM    MM MM    MM    MM MMMMMMMM MM    MM MM     
 MM    MM  MM    MM MM    MM MM       MM           MM    MM MM         `Mbd'   MM       MM MM     MM MM    MM MM    MM    MM MM       MM    MM MM     
 YM.   MM  MM    MM YM.  ,MM YM    d9 MM           YM.  ,MM YM    d9    YMP    YM    d9 MM YM.   ,M9 MM.  ,M9 MM    MM    MM YM    d9 MM    MM YM.  , 
  YMMM9MM__MM_  _MM_ YMMMMMM_ YMMMM9 _MM_           YMMMMMM_ YMMMM9      M      YMMMM9 _MM_ YMMMMM9  MMYMMM9 _MM_  _MM_  _MM_ YMMMM9 _MM_  _MM_ YMMM9 
                                                                                                     MM                                               
                                                                                                     MM                                               
                                                                                                    _MM_                                              


  */
