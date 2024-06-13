
# PRÁCTICA 6: Buses de comunicación II (SPI)
## Práctico A

Código:

```cpp
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

```
Descripcion:

En este código se utiliza una tarjeta SD para escribir y leer archivos. Primero, se incluyen las bibliotecas necesarias, como SPI y SD. Luego, se define una función llamada writeFile(), que toma un sistema de archivos (fs), una ruta de archivo y un mensaje para escribir en el archivo.

En la función setup(), que se ejecuta una vez al inicio, se inicia la comunicación serial para la depuración, se configura la comunicación SPI y se intenta inicializar la tarjeta SD. Si la inicialización tiene éxito, se crea un archivo llamado "hello1.txt" con el contenido "Hello world 1, PD" utilizando la función writeFile(). Después, se intenta abrir y leer un archivo llamado "arxivo.txt", mostrando su contenido si se abre correctamente.

## Ejercicio Práctico 2
Código:

```cpp
#include <Arduino.h>
    #include <SPI.h>
    #include <MFRC522.h>

    #define RST_PIN 9 
    #define SS_PIN 10 

    MFRC522 mfrc522(SS_PIN, RST_PIN); 

    void setup() {
    Serial.begin(115200); //Iniciamos la comunicación serial
    SPI.begin(36, 37, 35); //Iniciamos el Bus SPI
    mfrc522.PCD_Init(); // Iniciamos el MFRC522
    Serial.println("Lectura del UID");
    }

    void loop() {
    // Revisamos si hay nuevas tarjetas presentes
    if ( mfrc522.PICC_IsNewCardPresent()) 
    { 
        //Seleccionamos una tarjeta
        if ( mfrc522.PICC_ReadCardSerial()) 
        {
        // Enviamos serialemente su UID
        Serial.print("Tarjeta UID:");
        for (byte i = 0; i < mfrc522.uid.size; i++) {
            Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0"
            : " ");
            Serial.print(mfrc522.uid.uidByte[i], HEX); 
        } 
        Serial.println();
        // Terminamos la lectura de la tarjeta actual
        mfrc522.PICC_HaltA(); 
        } 
    } 
    }
```
Descripción:

Este código implementa la funcionalidad para leer tarjetas de identificación por radiofrecuencia (RFID) utilizando el módulo MFRC522. El objetivo principal es detectar tarjetas RFID cercanas y leer sus identificadores únicos (UID).

Para lograr esta funcionalidad, se emplean las bibliotecas necesarias para la comunicación con el módulo MFRC522 y la interfaz de comunicación SPI. Se especifican los pines utilizados para el reinicio del módulo y el pin de selección (SDA o SS) del módulo MFRC522.

En la función setup(), se inicializa la comunicación serial para permitir la interacción con el monitor serial y se configura la comunicación SPI con los pines definidos. Además, se prepara el módulo MFRC522 para la lectura de tarjetas.

La función loop() se ejecuta en un ciclo continuo. En esta función, se verifica si hay una tarjeta RFID presente. Si se detecta una tarjeta, se procede a leer su UID utilizando las funciones de la biblioteca MFRC522. Una vez leído el UID de la tarjeta, se muestra en el monitor serial para su visualización.

## CONCLUSIONES
Se establece la comunicación con la tarjeta SD, se escribe en un archivo y luego se lee desde otro archivo.
Facilita la detección y lectura de tarjetas RFID mediante la integración del módulo MFRC522, ofreciendo una forma sencilla para que dispositivos RFID interactúen en proyectos electrónicos.
