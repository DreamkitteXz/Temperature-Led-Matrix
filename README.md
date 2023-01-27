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
<p> Logo abaixo tem o código que mostra a temperatura, mas antes de executarmos esse código temos que instalar algumas bibliotecas, <code>Max72xxPanel</code> <code> SPI</code> <code> Adafruit GFX Library</code> para o código funcionar. Irei demonstrar como instalar cada uma delas.
</p> <h4 align='center'>Max72xxPanel</h4><p>Para instalar essa biblioteca clique <a href="https://github.com/markruys/arduino-Max72xxPanel/archive/master.zip">nesse link</a> e irá baixar a pasta compactada da biblioteca, uma vez feito isso vamos para o Arduino IDE e procurar por <code>Sketch</code> > <code>Incluir bibliioteca</code> > <code>Adicionar .ZIP</code> .
</p>


<p align='center'><pre><code >
#include "SPI.h"
#include "Adafruit_GFX.h"
#include "Max72xxPanel.h"
 
int pinCS = 10; // Conecte CS a este pino, DIN(11) a MOSI e CLK(13) a SCK
int numberOfHorizontalDisplays = 1;
int numberOfVerticalDisplays = 3;
 
Max72xxPanel matrix = Max72xxPanel(pinCS, numberOfHorizontalDisplays, numberOfVerticalDisplays);
 
String txtDisplay = "ETEFMC";
int width = 5 + 1; // A largura da fonte é de 5 pixels
 
void setup() 
{
 
  matrix.setIntensity(15); // Use um valor entre 0 e 15 para brilho
  matrix.setPosition(0, 0, 0); // A primeira exibição está em <0, 0>
  matrix.setPosition(1, 0, 1); // A segunda tela está em <1, 0>
  matrix.setPosition(2, 0, 2); // A terceira tela está em <2, 0>
  matrix.setRotation(1);    // A mesma espera para a última exibição
 matrix.fillScreen(LOW);
 matrix.write();
 delay(400);
 matrix.print("ETE");
 matrix.write();
 delay(2000);
}
 
void loop() 
{
  for ( int i = 0 ; i < width * txtDisplay.length() + matrix.width() - 1 - 1; i++ ) 
  {
    matrix.fillScreen(LOW);
 
    int letter = i / width;
    int x = (matrix.width() - 1) - i % width;
    int y = (matrix.height() - 8) / 2; // centraliza o texto verticalmente
 
    while ( x + width - 1 >= 0 && letter >= 0 ) 
    {
      if ( letter < txtDisplay.length() ) 
      {
        matrix.drawChar(x, y, txtDisplay[letter], HIGH, LOW, 1);
      }
      letter--;
      x -= width;
    }
 
    matrix.write(); // Envia bitmap para exibição
    delay(100);
  }
}</code></pre></p>
<p>Espere o seguinte resultado:</p>
<p align='center'><img src="Images\ETEFMC.gif" alt="Screen" width="600" height="338">