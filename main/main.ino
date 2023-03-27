#include "all_constants.h" //Pour retrouver toutes les constantes, veuillez ouvrir le ficher "all_constants.h"

void setup() {
  //Permet l'affichage dans le terminal
  Serial.begin(9600);
  Serial.println("STAAAAAAAAAAAAAAAAAAAAAAART!!!");

  //Initialise la carte SD
  pinMode(CS_PIN, OUTPUT);
  //initializeSD();
  SD_init();

  //Serial1 permettant de communiquer avec ThingStream
  Serial1.begin(115200);
  //initThingstream(&init_flag);

  //Pin permettant la mesure des courants entrées/sorties des batteries
  //pinMode(INPUT_CURRENT_PIN, INPUT);  
  //pinMode(OUTPUT_CURRENT_PIN, OUTPUT);
}

void loop() {
  //determine_SOC();
  publish_test(&init_flag);
  //saveSD("test.txt", "Hello World! from main");
  
}

void SD_init(){
  if(!SD.begin(4)){
    Serial.println("Big Fail!");
  }
  else{
    Serial.println("Hehe perfect!");
  }
}

void print_sentence(char* variable_name, float value){
  char sentence[100] = "Voici la valeur de ";
  strcat(sentence, variable_name);
  strcat(sentence, " : ");
  char buffer[64];
  snprintf(buffer, sizeof buffer, "%f", value);
  strcat(sentence, buffer);
  Serial.println(sentence);
}