int forward_pin = 10;
int reverse_pin = 9;
int turn_on_en_input = 3;
int turn_on_en_output = 11;
int val;

void setup() {
  pinMode(turn_on_en_input,INPUT);
  pinMode(turn_on_en_output,OUTPUT);
  pinMode(forward_pin,OUTPUT);
  pinMode(reverse_pin,OUTPUT);
}

void forward(){
  digitalWrite(turn_on_en_output,HIGH);
  digitalWrite(forward_pin,HIGH);
  digitalWrite(reverse_pin,LOW);
}

void reverse(){
  digitalWrite(turn_on_en_output,HIGH);
  digitalWrite(forward_pin,LOW);
  digitalWrite(reverse_pin,HIGH);
}


//testing loop
void loop() {
  val = digitalRead(turn_on_en_input);
if (val == 1){
  forward();
}



}
