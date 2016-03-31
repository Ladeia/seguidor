int SENSOR1, SENSOR2, SENSOR3;

//deslocamentos de calibracao
int leftOffset = 0, rightOffset = 0, centre = 0;
//pinos para a velocidade e direcao do motor
int speed1 = 3, speed2 = 11, direction1 = 12, direction2 = 13;
//velocidade inicial e deslocamento de rotacao
int startSpeed = 70, rotate = 30;
//limiar do sensor
int threshold = 5;
//velocidades iniciais dos motores esquerdo e direito
int left = startSpeed, right = startSpeed;

//Rotina de calibracao do sensor
void calibrate()
{
 for (int x=0; x<10; x++) //Executa 10 vezes para obter uma media
 {
   Serial.println("Calibrate");
   delay(100);
   SENSOR1 = analogRead(0);
   SENSOR2 = analogRead(1);
   SENSOR3 = analogRead(2);
   Serial.println("sensor 1 ");
   Serial.println(SENSOR1);
   Serial.println("sensor 2 ");
   Serial.println(SENSOR2);
   Serial.println("sensor 3 ");
   Serial.println(SENSOR3);
   leftOffset = leftOffset + SENSOR1;
   centre = centre + SENSOR2;
   rightOffset = rightOffset + SENSOR3;
   Serial.print("leftOffset ");
   Serial.println(leftOffset);
   Serial.print("centre ");
   Serial.println(centre);
   Serial.print("rightOffset ");
   Serial.println(rightOffset);
   delay(100);
 }
 //obtem a media para cada sensor
 leftOffset = leftOffset /10;
 rightOffset = rightOffset /10;
 centre = centre / 10;
 //calcula os deslocamentos para os sensores esquerdo e direito
 leftOffset = centre - leftOffset;
 rightOffset = centre - rightOffset;
}

void setup() {
    Serial.begin(9600);
    while (!Serial) {
      ; // wait for serial port to connect. Needed for native USB port only
    }
    calibrate();
    delay(3000);
}

void loop() {
  //utiliza a mesma velocidade em ambos os motores
  left = startSpeed;
  right = startSpeed;
 
  //le os sensores e adiciona os deslocamentos
  SENSOR1 = analogRead(0) + leftOffset;
  SENSOR2 = analogRead(1);
  SENSOR3 = analogRead(2) + rightOffset;

  
   Serial.println("sensor 1 ");
   Serial.println(SENSOR1);
   Serial.println("sensor 2 ");
   Serial.println(SENSOR2);
   Serial.println("sensor 3 ");
   Serial.println(SENSOR3);
  
  //Se SENSOR1 for maior do que o sensor do centro + limiar,
  // vire para a direita
  if (SENSOR1 > SENSOR2+threshold)
  {
    Serial.println("virando para a direita");
    left = startSpeed + rotate;
    right = startSpeed - rotate;
    Serial.println(left);
    Serial.println(right);
  }
 
  //Se SENSOR3 for maior do que o sensor do centro + limiar,
  // vire para a esquerda
  if (SENSOR3 > (SENSOR2+threshold))
  {
    Serial.println("virando para a esquerda");
    left = startSpeed - rotate;
    right = startSpeed + rotate;
    Serial.println(left);
    Serial.println(right);
  }
  delay(1000);
}
