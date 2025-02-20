/* -----------------------------------------------------------------------------
 Sunfounder.
     Esta versão do robô tem 4 pernas e cada perna é acionada por 3 servos.
   Este robô é acionado por uma placa Ardunio Nano com uma placa de expansão.
   Recomendamos que você consulte a documentação do produto antes de usar.
   - Solicitar
   - Este projeto requer alguns arquivos de biblioteca, que você pode encontrar na cabeça de
     este ficheiro. Certifique-se de ter instalado esses arquivos.
   - Como
   - Antes de usar, você deve ajustar o robô, a fim de torná-lo mais preciso.
     - Operação de ajuste
     1. descomente ADJUST, faça e execute
     2. comente ADJUST, descomente VERIFY
     3. medir sites reais e definir como real_site[4][3], criar e executar
     4. comente VERIFICAR, faça e execute
   O documento descreve em detalhes como operar.
   ---------------------------------------------------------------------------*/

// modified by Regis for spider project, 2015/09/11

#include <SoftwareSerial.h> 

int bluetoothTx = 0; // bluetooth tx to 12 pin
int bluetoothRx = 1; // bluetooth rx to 9 pin

SoftwareSerial bluetooth(bluetoothTx, bluetoothRx);

/* Includes ------------------------------------------------------------------*/
#include <FlexiTimer2.h>//to set a timer to manage all servos
#include <Servo.h>
/* Servos --------------------------------------------------------------------*/
//define 12 servos for 4 legs
Servo servo[4][3]; // define arai por 4 pernas de 3 motores
//define servos' ports
//const int servo_pin[4][3] = { {12, 11, 13}, {9, 8, 10}, {6, 5, 7}, {3, 2, 4 }  };
const int servo_pin[4][3] = { {11, 12, 13}, {8, 9, 10}, {5, 6, 7}, {2, 3, 7}  };
/*tamanho do robo ---------------------------------------------------------*/
const float length_a = 55;
const float length_b = 77.5;
const float length_c = 27.5;
const float length_side = 71;
const float z_absolute = -28;
/* Constantes de movimento ----------------------------------------------------*/
const float z_default = -50, z_up = -30, z_boot = z_absolute;
const float x_default = 62, x_offset = 0;
const float y_start = 0, y_step = 40;
const float y_default = x_default;
/* variáveis para movimento ----------------------------------------------------*/
volatile float site_now[4][3];    //coordenadas em tempo real do final de cada perna
volatile float site_expect[4][3]; //coordenadas esperadas do final de cada perna
float temp_speed[4][3];   //velocidade de cada eixo, precisa ser recalculada antes de cada movimento
float move_speed;     //velocidade de movimento
float speed_multiple = 1; //velocidade de movimento múltipla
const float spot_turn_speed = 4;
const float leg_move_speed = 8;
const float body_move_speed = 3;
const float stand_seat_speed = 1;
volatile int rest_counter;      //+1/0.02s, para descanso automático
//parametro das funcoes
const float KEEP = 255;
//define PI para cálculo
const float pi = 3.1415926;
/* Constantes por turno --------------------------------------------------------*/
//comprimento temporário
const float temp_a = sqrt(pow(2 * x_default + length_side, 2) + pow(y_step, 2));
const float temp_b = 2 * (y_start + y_step) + length_side;
const float temp_c = sqrt(pow(2 * x_default + length_side, 2) + pow(2 * y_start + y_step + length_side, 2));
const float temp_alpha = acos((pow(temp_a, 2) + pow(temp_b, 2) - pow(temp_c, 2)) / 2 / temp_a / temp_b);
// local da virada
const float turn_x1 = (temp_a - length_side) / 2;
const float turn_y1 = y_start + y_step / 2;
const float turn_x0 = turn_x1 - temp_b * cos(temp_alpha);
const float turn_y0 = temp_b * sin(temp_alpha) - turn_y1 - length_side;
/* ---------------------------------------------------------------------------*/

void setup()
{
  setup_org();
}

void loop()
{
  loop_org();
}
