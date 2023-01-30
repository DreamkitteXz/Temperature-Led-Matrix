<h2 align='center'>
  <b>Como exibir dados de um sensor de temperatura em uma matrix de LED.</b>
</h2>
<h3>
  Visão geral 
</h3>
<p>
  <p></p>
<p>Você irá brincar com a Matriz de LED Escrevendo alguma coisa e aparecendo no Letreiro.</p>
</p>
<p>
Voce irá aprender:
<ul>
    <li>Instalar uma biblioteca no Arduino IDE.</li>  
</ul>

  <h2 align='center'>Começando...</h2>
      <h3>Componentes utilizados</h3>
      <ul>
    <li>8x16 LED Dot Matrix with MAX7219 Controller.<p align='center'><img src="https://raw.githubusercontent.com/gist/DreamkitteXz/f73cf72a38741b16a3b242c1f9c6d438/raw/3cb9e826bdac35c51cb7cfd657911a2fa0955045/download.svg" alt="Screen" width="389" height="72"></p></li> 
    <li>Arduino Uno.<p align='center'><img src="https://upload.wikimedia.org/wikipedia/commons/7/7c/Arduino_Uno_%28Versi%C3%B3n_Inform%C3%A1tica%29.png" alt="Screen" width="417" height="212"></p></li> 
    <li>Termistor de 10K Ohm.<p align='center'></li>
    <li>Resistor de 10K Ohms.</li>
</ul>
    <h3>Conexões</h3>
      <p>Conecte as matrizes de LED e o termistor ao Arduino seguindo este diagrama:>
     <p align='center'><img src="https://www.circuitbasics.com/wp-content/uploads/2020/06/Four-Matrix-and-Thermistor-Wiring-Diagram-1451x1536.png" alt="Screen" width="725" height="768"></p>
     <p align='center'><a href="https://www.circuitbasics.com/how-to-setup-an-led-matrix-on-the-arduino/"><b>Fonte</b></a></p>
<h3 align='center'>Código Para Exibição De Dados Do Sensor Em Uma Matriz De LED</h3>
<p> Logo abaixo tem o código que mostra a temperatura, mas antes de executarmos esse código temos que instalar duas bibliotecas, <code>Max72xxPanel</code> <code> Adafruit GFX Library</code> para o código funcionar. Irei demonstrar como instalar cada uma delas.
</p> <h4 align='center'>Max72xxPanel</h4><p>Para instalar essa biblioteca clique <a href="https://github.com/markruys/arduino-Max72xxPanel/archive/master.zip">nesse link</a> e irá baixar a pasta compactada da biblioteca, uma vez feito isso vamos para o Arduino IDE e procurar por <code>Sketch</code> > <code>Incluir bibliioteca</code> > <code>Adicionar .ZIP</code> .
<p align='center'><img src="https://github.com/DreamkitteXz/8x8--LED-MATRIX-LETREIRO/raw/main/images/c.png" alt="Screen" width="641" height="357"></p>
<p> Procure pela pasta baixada e clique em <code>abrir</code></p>
<p align='center'><img src="https://github.com/DreamkitteXz/8x8--LED-MATRIX-LETREIRO/raw/main/images/pl.png" alt="Screen" width="800" height="650"></p>
 <h4 align='center'>Adafruit GFX Library</h4>
<p> Agora iremos instalar outra biblioteca <code> Adafruit GFX Library</code>, dessa vez iremos utilizar outra forma de instalar, basta clicar em <code>Ferramentas</code> > <code>Gerenciar bibliotecas</code>.
</p>
<p align='center'><img src="https://github.com/DreamkitteXz/8x8--LED-MATRIX-LETREIRO/raw/main/images/K.png" alt="Screen" width="584" height="408"></p>
<p> Procure por <code> Adafruit GFX Library</code> e instale.</p>
<p align='center'><img src="https://github.com/DreamkitteXz/8x8--LED-MATRIX-LETREIRO/raw/main/images/sa.png" alt="Screen" width="799" height="464"></p>
</p>

<h3>Código</h3>
<p align='center'><pre><code>#include "SPI.h"
#include "Adafruit_GFX.h"
#include "Max72xxPanel.h"

int pinCS = 10;
//Din conectado ao pino 11
//CLK conectado ao pino 13

int numberOfHorizontalDisplays = 2t ;
int numberOfVerticalDisplays = 1;

int thermistorPin = A0;
float R1 = 10000;
float R2, logR2, logR2Cube, tK, tC, tF; 
float A = 9.76086e-04, B = 2.38890e-04, C = 2.27e-07;

Max72xxPanel matrix = Max72xxPanel(pinCS, numberOfHorizontalDisplays, numberOfVerticalDisplays);

int wait = 50;
int spacer = 1;
int width = 5 + spacer;

void setup() {
  matrix.setIntensity(7);
  matrix.setRotation(1, 2);
  matrix.setRotation(3, 2);
}

void loop() {

  int Vout = analogRead(thermistorPin);

  R2 = R1 * (1023.0 / Vout - 1.0);
  logR2 = log(R2);
  logR2Cube = pow(logR2, 3);
  tK = (1.0 / (A + B * logR2 + C * logR2Cube));
  tC = tK - 273.15;
  //tF = (tC * 9.0) / 5.0 + 32.0; 

  String tape = "Temp: " + String(tC) + " C";

  for (int i = 0 ; i < width * tape.length() + matrix.width() - 1 - spacer; i++ ) {
    matrix.fillScreen(LOW);

    int letter = i / width;
    int x = (matrix.width() - 1) - i % width;
    int y = (matrix.height() - 8) / 2;

    while ( x + width - spacer >= 0 && letter >= 0 ) {
      if ( letter < tape.length() ) {
        matrix.drawChar(x, y, tape[letter], HIGH, LOW, 1);
      }

      letter--;
      x -= width;
    }

    matrix.write();
    delay(wait);
  }
}</code></pre></p>
<p>Espere o seguinte resultado:</p>
<p align='center'><img src="Images\ezgif.com-gif-maker (5).gif" alt="Screen" width="600" height="338">
<h3 align='center'>
  Explicando o código
</h3>
<p>Primeiro, declaramos as variáveis ​​flutuantes para os cálculos do termistor.

No <code>loop()</code>, as primeiras cinco linhas de código fazem uma leitura analógica do thermistorPin, executam um cálculo para converter o valor ADC em Celsius e armazenam a temperatura em uma variável chamada <code>tC</code>.

Em seguida, criamos o objeto <code>tape</code> da classe <code>String</code> e o definimos igual a uma string de texto regular que diz <code>Temp:</code> . As strings podem ser adicionadas ou “concatenadas” entre si com um sinal de +. Portanto, tudo o que precisamos fazer é concatenar a variável <code>tC</code> à string de texto. Mas como a variável <code>tC</code>é float, precisamos convertê-la em uma string antes que ela possa ser impressa. Podemos fazer isso com <code>String()</code> e o nome da variável entre parênteses. Também queremos as unidades de temperatura, então vamos concatenar a <code>C</code> para Celsius depois que a variável <code>tC</code> for impressa.</p>