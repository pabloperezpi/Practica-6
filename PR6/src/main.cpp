    #include <Arduino.h>
    #include <SPI.h>
    #include <SD.h>
    File myFile;
    
    void writeFile(fs::FS &fs, const char * path, const char * message){
        Serial.printf("Escribiendo archivo... %s\r\n", path);

        File file = fs.open(path, FILE_WRITE);
        if(!file){
            Serial.println("- No se ha podido abrir el archivo");
            return;
        }
        if(file.print(message)){
            Serial.println("- Archivo escirto");
        } else {
            Serial.println("- Error en escritura");
        }
        file.close();
    }
    void setup()
    {

    Serial.begin(115200);
    SPI.begin(36, 37, 35);
    Serial.print("Iniciando SD ...");

    if (!SD.begin(39, SPI)) {
        Serial.println("No se pudo inicializar");
    return;
    }

    Serial.println("inicializacion exitosa");
    writeFile(SD, "/hello.txt", "Hello world :)"); 

    myFile = SD.open("/arxivo.txt");//abrimos el archivo 

    if (myFile) {
        Serial.println("arxivo.txt:");
    while (myFile.available()) {
        Serial.write(myFile.read());
    }
    myFile.close(); //cerramos el archivo
    } else {
        Serial.println("Error al abrir el arxivo");
    }
    }

    void loop()
    {
    }
