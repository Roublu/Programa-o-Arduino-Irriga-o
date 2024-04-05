
// Definir os pinos dos sensores de umidade
const int sensorPin1 = A0;
const int sensorPin2 = A1;
const int sensorPin3 = A2;

// Definir o pino para o relé
const int relePin = 8;

// Definir o intervalo de leitura (em milissegundos)
const unsigned long INTERVALO_LEITURA = 60000;  // 1 minuto

// Variáveis para contar as vezes que o relé foi ligado e desligado
int contadorReleLigado = 0;
int contadorReleDesligado = 0;

void setup() {
  // Iniciar a comunicação serial
  Serial.begin(9600);

  // Configurar o pino do relé como saída
  pinMode(relePin, OUTPUT);
  // Desligar o relé inicialmente
  digitalWrite(relePin, LOW);
}

void loop() {
  
  // Ler os valores dos sensores de umidade do solo
  int umidadeSensor1 = lerUmidade(sensorPin1);
  int umidadeSensor2 = lerUmidade(sensorPin2);
  int umidadeSensor3 = lerUmidade(sensorPin3);

  // Exibir os valores dos sensores no monitor serial
  Serial.print("Sensor 1: ");
  Serial.print(umidadeSensor1);
  Serial.print(" | Porcentagem: ");
  Serial.print(map(umidadeSensor1, 0, 1023, 0, 100));
  Serial.print("% | ");

  Serial.print("Sensor 2: ");
  Serial.print(umidadeSensor2);
  Serial.print(" | Porcentagem: ");
  Serial.print(map(umidadeSensor2, 0, 1023, 0, 100));
  Serial.print("% | ");

  Serial.print("Sensor 3: ");
  Serial.print(umidadeSensor3);
  Serial.print(" | Porcentagem: ");
  Serial.print(map(umidadeSensor3, 0, 1023, 0, 100));
  Serial.print("% | ");

  // Verificar se a umidade está abaixo de 25 e ligar o relé
  if (umidadeSensor1 < 250 || umidadeSensor2 < 250 || umidadeSensor3 < 250) {
    digitalWrite(relePin, LOW); // Desligar o relé
    Serial.println("Relé desligado!");
    contadorReleDesligado++; // Incrementar a contagem
  }

  // Verificar se a umidade está acima de 40 e desligar o relé
  if (umidadeSensor1 > 400 || umidadeSensor2 > 400 || umidadeSensor3 > 400) {
    digitalWrite(relePin, HIGH); // Ligar o relé
    Serial.println("Relé ligado!");
    contadorReleLigado++; // Incrementar a contagem
  }
  
  Serial.print("Contador de Relé Ligado: ");
  Serial.print(contadorReleLigado);
  Serial.print(" | Contador de Relé Desligado: ");
  Serial.println(contadorReleDesligado);
  
  // Aguardar o intervalo de leitura
  delay(INTERVALO_LEITURA);
}

int lerUmidade(int pin) {
  // Ler o valor analógico do pino
  int valor = analogRead(pin);

  return valor;
}
