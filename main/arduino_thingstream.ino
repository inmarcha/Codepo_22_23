int initThingstream(int *flag_init) {
  delay(10000); // wait for the modem to initialize
  if (*flag_init == 0 ){
    // ERROR : reset the Thingstream click
    Serial.println("DEBUG");
    Serial1.println("AT+IOTDEBUG=0");
  if(checkReception() == 1) { 
      *flag_init = 1; 
        Serial.println("Debug : success");
      } else {
        Serial.println("Debug : fail");
      }
  }
  if(*flag_init == 1){
    Serial.println("CREATE");
    Serial1.println("AT+IOTCREATE");  
    if(checkReception() == 1) { 
        *flag_init = 2; 
        Serial.println("Create : success");
     } else {
        Serial.println("Create : fail");
     }
  }
  if(*flag_init == 2){
    Serial.println("CONNECT");
    Serial1.println("AT+IOTCONNECT=true"); 
    if(checkReception() == 1) { 
        *flag_init = 3; 
        Serial.println("Connect : success");
    } else {
        Serial.println("Connect : fail");
    }
  }
  if(*flag_init == 3) {
    Serial.println("SUBSCRIBE");
    Serial1.println("AT+IOTSUBSCRIBE=\"TEST1\",1");
    if(checkReception() == 1) { 
        *flag_init = 4; 
        Serial.println("Subscribe : success");
    } else {
        Serial.println("Subscribe : fail");
    }
  }
}
void publish_test(int *init_flag){
  if(!already_publish && *init_flag==4){
    publish_initial(0.3); // publish the test message
    already_publish = !already_publish;
  }
}
void publish(float SOC_lvl){

  char message[10000] = "\0";
  char res[500];
  sprintf(res, "Error: le SOC est de : %f. Veuillez envoyer quelqu'un", SOC_lvl);
  strcat(message, res);

  Serial.print("message : ");//Print le message sur Serial Monitor
  Serial.println(message); 

  Serial1.println(message);//COMMUNICATION
}

void publish_initial(float SOC_lvl){

  char message[10000] = "\0";
  char res[500];
  char mask[50] = "AT+IOTPUBLISH=\"TEST1\",1," ;
  sprintf(res, "AT+IOTPUBLISH=\"TEST1\",1,\"Error: le SOC est de : %f. Veuillez envoyer quelqu'un\"", SOC_lvl);
  strcat(message, res);

  Serial.print("message : ");//Print le message sur Serial Monitor
  Serial.println(message); 

  Serial1.println(message);//COMMUNICATION
}
int checkReception() {
  unsigned long timeInit = millis()*0.001;
  char message[150];
  int count = 0;
  
  while(true) {
    // If maximum time (20s) to wait for message reception exceeded
    if(millis()*0.001 - timeInit > 50.0) { 
      Serial.println("To Long Time");
      return 0;
     }
    // If not yet exceeded
    //Serial.println(Serial1.available());
    //delay(500);
    if (Serial1.available()){
        char st = Serial1.read();
        message[count] = st;  
        message[count+1] = '\0';  
        count += 1;
        
        if(message[count-1] == '\n'){
          Serial.print("Le message recu : ");          
          Serial.print(String(message));  //Affiche le message recu
          if (analyse(message) ==  1) {
            return 1;
          } else {
            return 0;
          }
        }
     }
  }}

int analyse (String st) {
  // Arret de la publication si le mot STOP est reçu par le Click

  //Serial.println("Analyse has been called");
  int res = 1;  
  if(st.indexOf("GO") > 0 || st.indexOf("SUCCESS") > 0) {
    res = 1;
  } else {
    res = 0;
  }
  return res;
}
