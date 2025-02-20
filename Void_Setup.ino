 /* 
   - função de configuração
   ---------------------------------------------------------------------------*/
void setup_org() {

  
  //inicia serial para depuração
  Serial.begin(9600);//115200
  bluetooth.begin(9600);
 
  Serial.println("Robot starts initialization");
  //inicializa parâmetro padrão
  set_site(0, x_default - x_offset, y_start + y_step, z_boot);
  set_site(1, x_default - x_offset, y_start + y_step, z_boot);
  set_site(2, x_default + x_offset, y_start, z_boot);
  set_site(3, x_default + x_offset, y_start, z_boot);
  for (int i = 0; i < 4; i++)
  {
    for (int j = 0; j < 3; j++)
    {
      site_now[i][j] = site_expect[i][j];
    }
  }
  //inicia serviço servo
  FlexiTimer2::set(20, servo_service);
  FlexiTimer2::start();//*/

  Serial.println("Servo service started");
  //inicializa os servos
  servo_attach();
  Serial.println("Servos initialized");
  Serial.println("Robot initialization Complete");
}


void servo_attach(void) // anexar servos
{
  for (int i = 0; i < 4; i++)
  {
    for (int j = 0; j < 3; j++)
    {
      servo[i][j].attach(servo_pin[i][j]);
      delay(100);
    }
  }
}

void servo_detach(void) //desanexar servos
{
  for (int i = 0; i < 4; i++)
  {
    for (int j = 0; j < 3; j++)
    {
      servo[i][j].detach();
      delay(100);
    }
  }
}
/*
  - função de loop
   ---------------------------------------------------------------------------*/