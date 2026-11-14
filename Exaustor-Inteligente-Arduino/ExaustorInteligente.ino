// ventoinha pwm auto lcd e tals com SENSOR ANALOGICO
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

// ---------------------------------------------------------
// 1. SETUP PEÇAS
// ---------------------------------------------------------
LiquidCrystal_I2C lcd(0x27, 16, 2);

const uint8_t POTENCIOMETRO = A0;
const uint8_t FAN = 9; 
const uint8_t SENSOR_TEMP = A1; // temperatura
const uint8_t BOTAO = 4;

// ---------------------------------------------------------
// 2. VARIÁVEIS DE ESTADO
// ---------------------------------------------------------
uint8_t modo = 0; // 0 = Automático, 1 = Manual
bool mostrandoTransicao = false;
float temperaturaAtual = 0.0;
uint8_t pwmAtual = 0;

// ---------------------------------------------------------
// 3. TIMERS MILLI
// ---------------------------------------------------------
unsigned long tempoTransicao = 0;
unsigned long ultimaLeituraSensores = 0;
unsigned long ultimaAtualizacaoLCD = 0;
unsigned long ultimoDebounce = 0;

// variaveis do botao games ultimate
bool estadoBotao = HIGH;
bool ultimoEstadoBotao = HIGH;

void setup() {
  // prescaler pra 1 pra tirar ruido do cooler
  TCCR1B = (TCCR1B & 0b11111000) | 0x01;
  
	lcd.init();
	lcd.backlight();
  
  pinMode(FAN, OUTPUT);
  pinMode(BOTAO, INPUT_PULLUP);
}

// debounce
bool botaoPressionado() {
  bool leitura = digitalRead(BOTAO);
  bool acionado = false;

  if (leitura != ultimoEstadoBotao) {
    ultimoDebounce = millis();
  }

  // se estabilizar por 50ms = válido
  if ((millis() - ultimoDebounce) > 50) {
    if (leitura != estadoBotao) {
      estadoBotao = leitura;
      if (estadoBotao == LOW) {
        acionado = true;
      }
    }
  }
  ultimoEstadoBotao = leitura;
  return acionado;
}

void loop() {
  unsigned long tempoAtual = millis();

  // =========================================================
  // CAPITULO 1: INTERFACE (HMI)
  // =========================================================
  if (botaoPressionado()) {
    modo = (modo == 0) ? 1 : 0; // Alterna o estado (Toggle)
    mostrandoTransicao = true;
    tempoTransicao = tempoAtual;
    
    lcd.clear();
    if (modo == 0) {
      lcd.setCursor(0, 0); lcd.print("      MODO      ");
      lcd.setCursor(0, 1); lcd.print("   AUTOMATICO   ");
    } else {
      lcd.setCursor(0, 0); lcd.print("      MODO      ");
      lcd.setCursor(0, 1); lcd.print("     MANUAL     ");
    }
  }

  // manter mensagem na tela usando milli (não bloqueia o processador)
  if (mostrandoTransicao) {
    if (tempoAtual - tempoTransicao >= 2000) {
      mostrandoTransicao = false;
      lcd.clear();
    } else {
      return;
    }
  }

  // =========================================================
  // capitulo 2: CÁLCULO E DADOS (A cada 100ms)
  // =========================================================
  if (tempoAtual - ultimaLeituraSensores >= 100) {
    ultimaLeituraSensores = tempoAtual;

    // 1. capturando temperatura
    uint16_t somaTemp = 0;
    for(uint8_t i = 0; i < 10; i++) somaTemp += analogRead(SENSOR_TEMP); // Oversampling rápido
    
    float voltagem = (somaTemp / 10.0) * (5.0 / 1023.0);
    temperaturaAtual = (voltagem - 0.5) * 100.0;

    // 2. >>>>>Calibrando limites do cooler AUTOMATICO<<<<<<
    if (modo == 0) {
      // --- MODO AUTOMÁTICO (Controle Proporcional) ---
      if (temperaturaAtual <= 25.0) {
        pwmAtual = 0;
      } else if (temperaturaAtual >= 45.0) {
        pwmAtual = 255;
      } else {
        // multiplica por 10 pq map não tem vírgula
        pwmAtual = map(temperaturaAtual * 10, 250, 450, 80, 255); 
      }
      
    } else {
      // >>>>>Calibrando limites do cooler MANUAL<<<<
      uint16_t somaPot = 0;
      for(uint8_t i = 0; i < 10; i++) somaPot += analogRead(POTENCIOMETRO);
      
      pwmAtual = map((somaPot / 10), 0, 1023, 0, 255);
      
      // zona morta pra eficiencia, pwm baixo não gira helice, mas gasta energia
      if (pwmAtual < 40) pwmAtual = 0; 
    }

    // 3. atuação de hardware
    analogWrite(FAN, pwmAtual);
  }

  // =========================================================
  // CAPITULO 3: LCD (A cada 250ms para evitar Flickering)
  // =========================================================
  if (!mostrandoTransicao && (tempoAtual - ultimaAtualizacaoLCD >= 250)) {
    ultimaAtualizacaoLCD = tempoAtual;

    // map do PWM pra porcentagem (facilitar pro usuario ne)
    uint8_t porcentagemRPM = map(pwmAtual, 0, 255, 0, 100);

    // Linha 0: (X) TMP: yyy.y°C
    lcd.setCursor(0, 0);
    lcd.print(modo == 0 ? "A)" : "M)");
    lcd.print(" TEMP: ");
    lcd.print(temperaturaAtual, 1); // forçando 1 casa decimal
    lcd.print("\262C  "); // "\262 é para o símbolo de grau

    // Linha 1: VELOCIDADE: zz%
    lcd.setCursor(0, 1);
    lcd.print("VELOCIDADE: ");
    
    // limpando caracteres pra evitar bugs visuais
    if(porcentagemRPM < 100) lcd.print(" "); 
    if(porcentagemRPM < 10)  lcd.print(" ");
    
    lcd.print(porcentagemRPM);
    lcd.print("%  ");
  }
}