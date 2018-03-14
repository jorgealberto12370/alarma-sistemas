º//Detector de personas con alarma, la cual cuenta cuantas personas entran a la habitacion

#include<LiquidCrystal.h>  //se incluye la libreria para poder trabajar con pantalla lcd
LiquidCrystal lcd(12, 11, 5, 4, 3, 2); //los pines con los que vamos a trabajar,con el número de pin arduino al que está conectado
int pinoirent = 7;     //lelvara coneccion a la fotoresistencia
int valorirent = 0;   //comienza el valor en 0 , que guardara el valor de pinoirent que se va a leer
int led=13;         //variable de led que se conectara al pin 13
int content = 0;    //variable de contador que llevara la sumatoria de personas
int content1 = 0;   //variable de contador
int total =0;       //variable que nos dice cuantas personas han ingresado a la habitacion
int buzzer = 9;     // pin al que se conecta el buzzer

void setup()
{
  Serial.begin(9600);            //imprime los datos en el puerto serie, configura el puerto serie a 9600bps
  pinMode(pinoirent, INPUT); ;   //se declara pinoirent en modo salida
  lcd.begin(16,2);              //valores de lcd
  pinMode (led,OUTPUT);         //se declara el led en salida
  lcd.setCursor(0,0);           //posicion de fila y columna para ubicar el cursor
  lcd.print("Pers: 0");         //va imprimiendo las personas que van ingresando
  pinMode(buzzer,OUTPUT);       //se declara el buzzer en modo salida
  
}

void loop()
{
   valorirent=digitalRead(pinoirent); //lee el valor que tiene pinoirent y lo guarda en valorirent
  if(valorirent!=1)                   //si valorirent es diferente de uno hara las siguientes funciones y comenzara el conteo de personas
  {
    content++;                        //aumenta el contador (ha pasado una persona mas, para en 20 y de nuevo empieza en 0 pero la suma sigue en total)
    total++;                          //se agrega al numero total de personas al final del conteo
    tone(buzzer,100);                 //suena el buzzer al ser detectada una persona
     while(digitalRead(pinoirent)!=1) {  //se hace un ciclo donde digitalRead lee lo que obtiene pinoirent y si es diferente se aplica un efecto retardado de 100 
        delay(100);                       //funcion que demara tiempo (efecto retardado)
      }      
    lcd.setCursor(10,0);                  //se posiciona el cursor en fila 10 columna 0 
    lcd.print(content);                   //imprime en pantalla la sumatoria que se lleva de personas
    lcd.setCursor(0,1);                   //se posiciona en fila 0 y columna 1
    lcd.println("TOTAL: ");               //nos imprime el mensage de total 
    lcd.setCursor(7,1);                   //ahora nos colocamos en fila 7 columna 1 para poder juntar con otro resultado
    lcd.print(total);                     //imprime el total de personas
                                          
   if(content==20){                       //si content llega a 20 personas empieza ejecuta las siguientes instrucciones, asi comienza todo de cero par volver a contar
          lcd.clear();                    //limpia la pantalla
          lcd.setCursor(3,1);             //se pocisiona en fila 3 columna 0 para mandar mensaje
          lcd.println("Hab. llena   ");   //Imprime el mensaje de habitacion llena y el numero total de personas 
          digitalWrite(led,1);            //habilita el HIGH DEL LED
          delay (2000);                   //tiempo de retardo de 2000
          content=0;                      //se declara en 0 para empezar de nuevo
          lcd.clear();                    //limpia la parte de pantalla
          digitalWrite(led,0);            //desactiva a 0
          lcd.setCursor(0,0);             //se pocisiona en fila 0 columna 0 para empezar a mandar mensaje
          lcd.print("Pers: 0");           //manda el mensaje de personas  = 0 para volver a empezar el conteo
          lcd.setCursor(0,1);             //se coloca en fila 0 columna 1
          lcd.print("TOTAL: ");           //Imprime el mensaje con la palabra total para unirla con un siguiente mensaje
          lcd.setCursor(7,1);             //nos posicionamos en fila 7 columna 1 para asignar mensaje
          lcd.print(total);               //manda el total de personas que ingresaron     
    }
          noTone(buzzer);                 //desactiva el sonido
  }
}
