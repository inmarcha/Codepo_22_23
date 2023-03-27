int initializeSD(){
  if(is_SD_ready() != 1){
    return 0;
  }
  if(createFileRead("test.txt") != 1){
    return 0;
  }
  writeToFile("Hello World! from moduleSD");

  char mon_text[8000];
  readFile(mon_text);
  closeFile();
  return 1;
}

int is_SD_ready(){
  Serial.println("Initializing SD card...");
  

  if (SD.begin(4)) {
    Serial.println("SD card is ready to use.");
    return 1;
  } else {
    Serial.println("SD card initialization failed");
    return 0;
  }
}

int createFileWrite(const char *filename){
  file = SD.open(filename, FILE_WRITE);

  if(file)
  {
    Serial.println("File created successfully.");
    return 1;
  } else
  {
    Serial.println("Error while creating file.");
    return 0;
  }
}


int createFileRead(const char *filename){
  file = SD.open(filename);

  if(file)
  {
    Serial.println("File created successfully.");
    return 1;
  } else
  {
    Serial.println("Error while creating file.");
    return 0;
  }
}

int writeToFile(char *text){
  if (file) {
    file.println(text);
    Serial.println("Writing to file: ");
    Serial.println(text);
    return 1;
  } else {
    Serial.println("Couldn't write to file");
    return 0;
  }
}

int readFile(char *text) {
  if (file) {
    const char *res;
    while (file.available()) {
      res = file.readString().c_str();
      Serial.print("Reading file: ");
      Serial.println(res);
    }
    sprintf(text, "\0");
    strcat(text, res); //Concatener
    
    return 1;
  } else {
    Serial.println("Couldn't read file");
    return 0;
  }
}

void closeFile(){
  if(file)
  {
    file.close();
    Serial.println("File closed");
  }
}

void saveSD(const char *filename, char* text) {
  char input[800];
  sprintf(input, text);
  SD.remove(filename);
  if(createFileWrite(filename)) {
      writeToFile(input);
      closeFile();
  }
}

void ReadSD(char *input, const char *filename) {
  if(createFileRead(filename)) {
      readFile(input);
      closeFile();
    }
}

