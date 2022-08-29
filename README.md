# Processamento de matrizes por segmentação de arquivo

[![Linguagem C++](https://img.shields.io/badge/Linguagem-C%2B%2B-green.svg)]()
[![requirement](https://img.shields.io/badge/IDE-Sublime%20Text-orange)](https://www.sublimetext.com)
![ISO](https://img.shields.io/badge/ISO-Linux-blueviolet)

Neste trabalho, cada aluno deve implementar um sistema de multiplicação de matrizes baseando-se em uma estratégia de segmentação em arquivo. Um arquivo M grande é fornecido no formato NxN com valores de ponto flutuante ou inteiros como entrada. Este é processado a partir de várias coordenadas introduzidas por um segundo arquivo, o coordenadas.txt. Em coordenadas.txt deve ser descrito por linha uma dupla de i e j correspondendo a posição inicial e final a ser lida. Por exemplo, as posições 2,4,6,10 indica que a leitura em M deve iniciar na linha 2 coluna 4 e seguir até a linha 6 coluna 10. 

Feito a leitura da composição de M para um tipo matriz em C, a segunda etapa é produzir a transposta de M -= MT. Feito isso, produza a multiplicação e armazene em uma hash o resultado da multiplicação como valor para a dupla de i's e j's, os quais deverão ser utilizados como chaves da hash. Assim, para cada novo calculo, antes o sistema deve consular a hash para identificar se a multiplicação já foi realizada. Em caso afirmativo, retorne apenas a resposta já calculada. Caso contrário, elabore a multiplicação e armazene o conteúdo em cache. 

## Sobre o código

Foi utilizado um arquivo <code>.txt</code>, encontrado também no repositório , chamado <i>matrix.txt</i>. Nesse arquivo foi feita a criação da matriz de Tamanho NxN, que pode ser alterada pelo usuário alterando o valor da váriavel <i>MAXTAM</i> no arquivo <code>aquecimento.hpp</code>. Essa matriz será utilizada para fazer o recorte de uma matriz menor, achar sua transposta e realizar a multiplicação entre as duas matrizes.

### Função <i>writeText()</i>

Nessa função foi realizada apenas a criação da matriz NxN no arquivo <code>.txt</code>. Segue o corpo de código da função:

```C++
  void writeText(){
	int value;
	ofstream file;

	file.open("matrix.txt");

	srand(time(NULL));

	for(int i = 0; i < MAXTAM; i++){
		for(int j = 0; j < MAXTAM; j++){
			value = rand() % 100;
			file << value << "\t";
		}
		file << endl;
	}

	file.close();
}
```

### Função <i>keyFunction()</i>

Nesta função, tem-se como parâmetro as coordenadas passadas pelo usuário, que transforma essa coordenadas em uma chave única para acesso na Tabela Hash. Segue o corpo de código da função:

```C++
double keyFunction(int iLine, int fLine, int iColumn, int fColumn){
	return stoi((to_string(iLine)) + to_string(fLine) + to_string(iColumn) + to_string(fColumn));
}
```

### Função <i>verify()</i>

Nesta função, é feita a verificação se a Tabela Hash já possui aquela chave. Se possuir a chave retorna 1, se não possuir retorna 0. Segue o corpo de código da função:

```C++
int verify(int key, unordered_map <int, int**> hashMatrix){
	auto item = hashMatrix.find(key);

	if(item != hashMatrix.end()){
		return 1;
	}

	return 0;
}
```

### Função <i>execute()</i>

Nessa função foi executado tudo que deveria ser feito no problema, desde a leitura da matriz interna até o calculo de multiplicação entre a matriz interna e sua transposta e implementação na Tabela Hash. 

Iniciamos a função declarando as variáveis necessárias e pedindo ao usuário as coordenadas da matriz interna, começando as linhas e colunas em 0 e não em 1. Logo após pedir ao usuário as coordenadas, é utilizado os valores das coordenadas para calcular o máximo de elementos que essa matriz possui e criar as variáveis que serão necessárias para cálculo entre as matrizes e para pesquisa e inserção na Tabela Hash. Segue o corpo de código desta parte:

```C++
vector<string> token;
string numb;
ifstream file;

int initialLine, initialColumn, finalLine, finalColumn;
int count = 0, countColumn = 0;

cout << "Insira o número da linha inicial da matriz interna: ";
cin >> initialLine;

cout << "Insira o número da linha final da matriz interna: ";
cin >> finalLine;

cout << "Insira o número da coluna inicial da matriz interna: ";
cin >> initialColumn;

cout << "Insira o número da coluna final da matriz interna: ";
cin >> finalColumn;

int maxElements = ((finalLine+1) - initialLine) * ((finalColumn+1) - initialColumn);
int dynamicLine, dynamicColumn;
int **dynamicMatrix, **transposedMatrix, **calculatedMatrix;

unordered_map <int, int**> hashMatrix;
int key;
int **matrixAux;
```

Logo após, a variável <code>key</code> recebe a função <code>keyFunction()</code> para gerar uma chave única. Gerando a chave única, é feita a pesquisa desta chave na Tabela Hash usando a função <code>verify()</code> em uma condição, onde se a função retornar 1, a chave já está registrada e a matriz já foi calculada, logo o valor é retornado. Segue o corpo de código desta parte da função:

```C++
key = keyFunction(initialLine, initialColumn, finalLine, finalColumn);

if(verify(key, hashMatrix) == 1){
	matrixAux = hashMatrix[key];

	for(int i = 0; i < ((finalLine - initialLine) + 1); i++){
		for(int j = 0; j < ((finalLine - initialLine) + 1); j++){
			cout << matrixAux[i][j];
		}
	}
}
```

Se a função <code>verify()</code> retornar 0, é porque a chave não está registrada e a matriz ainda não foi calculada, então o arquivo <code>.txt</code> é aberto para ser feita a leitura da matriz, usando as coordenadas que o usuário passou para ser feito o recorte, iniciando-se pelas linhas e logo após pelas colunas. A partir do ponto que o caminhamento está nas coordenadas certas, é feita a tokenização de cada elemento até que atinja o máximo de elementos da matriz. Segue o corpo de código desta parte: 

```C++
file.open("matrix.txt");

if(file.is_open()){ 	//Abrindo o arquivo txt
	for(int i = 0; i < initialLine; i++){
		getline(file, numb);
	}

	while(! file.eof()){
		getline(file, numb, '\t');

		if(count < maxElements){
			if((countColumn >= initialColumn) && (countColumn <= finalColumn)){
				token.push_back(numb);
				count++;
			}
		}

		countColumn++;

		if(countColumn == MAXTAM){
			countColumn = 0;
		}	
	}
```

Sendo feita a tokenização, temos os elementos da matriz tokenizados como <code>string</code>, o passo agora é transformá-los em inteiros e para isso, foi criado um vetor do tamanho do número de elementos da matriz para armazená-los. A transformação foi feita da seguinte forma: 

```C++
int size = token.size();
int vetNumbers[size];

for(int i = 0; i < size; i++){
  vetNumbers[i] = stoi(token[i]);
}
```

Possuindo todos os elementos da matriz tokenizados e do tipo inteiro, mas ainda em um vetor simples, é feita a criação da matriz dinâmica para armazenar os elementos e fechando o arquivo <code>.txt</code>. Para criar essa matriz dinâmica, foi necessário a criação de duas variáveis, <i>dynamicLine</i> e <i>dynamicColumn</i> que irão auxiliar na criação da matriz simples e da matriz transposta, que é o tamanho do caminhamento da linha e da coluna. Segue o corpo de código desta parte:

```C++
dynamicLine = (finalLine - initialLine) + 1;
dynamicColumn = (finalColumn - initialColumn) + 1;


				/* Matriz Dinâmica */

dynamicMatrix = new int *[dynamicLine];

for(int i = 0; i < dynamicLine; i++){
	dynamicMatrix[i] = new int[dynamicColumn];
}

cout << "___________________________________________" << endl << "\tMatriz normal" << endl << endl;

int x = 0;

for(int i = 0; i < dynamicLine; i++){
	for(int j = 0; j < dynamicColumn; j++){
		dynamicMatrix[i][j] = vetNumbers[x];
		cout << dynamicMatrix[i][j] << "\t";
		x ++;
	}
	cout << endl;
}

file.close(); //Fecha o arquivo txt
```

Possuindo a matriz normal pronta, para criar a matriz transposta foi necessário apenas inverter linha e coluna. Segue o corpo de código desta parte:

```C++
				/* Matriz Transposta */

transposedMatrix = new int *[dynamicColumn];

for(int i = 0; i < dynamicColumn; i++){
	transposedMatrix[i] = new int[dynamicLine];
}

cout << "___________________________________________" << endl << "\tMatriz transposta" << endl << endl;

for(int i = 0; i < dynamicColumn; i++){
	for(int j = 0; j < dynamicLine; j++){
		transposedMatrix[i][j] = dynamicMatrix[j][i];
		cout << transposedMatrix[i][j] << "\t";
	}
	cout << endl;
}

```

Possuindo a matriz normal e a matriz transposta prontas, podemos fazer a multiplicação e armazenar essa multiplicação em uma nova matriz dinâmica e na Tabela Hash. Segue o corpo de código desta parte:

```C++
				/* Multiplicação das matrizes */

calculatedMatrix = new int *[dynamicLine];

for(int i = 0; i < dynamicLine; i++){
	calculatedMatrix[i] = new int[dynamicLine];
}

cout << "___________________________________________" << endl << "\tMatriz calculada" << endl << endl;

for(int i = 0; i < dynamicLine; i++){
	for(int k = 0; k < dynamicLine; k++){
		calculatedMatrix[i][k] = 0;
		for(int j = 0; j < dynamicColumn; j++){
			calculatedMatrix[i][k] += dynamicMatrix[i][j] * transposedMatrix[j][k];
		}
	}
}

for(int i = 0; i < dynamicLine; i++){
	for(int j = 0; j < dynamicLine; j++){
		cout << calculatedMatrix[i][j] << "\t";
	}
	cout << endl;
}

hashMatrix.emplace(key, calculatedMatrix);
```

## Observações

<ul>
  <li>Ao ser pedido ao usuário as coordenadas, o mesmo deverá inseri-las de forma que as coordenadas iniciais sejam menores que as coordenadas finais. Por exemplo: <strong>Linha inicial: 1, Linha final: 5, Coluna inicial: 2, Coluna final: 7.</strong></li>
  <li>A contagem das coordenadas se inicia em 0, então se o usuário deseja, por exemplo, que a linha inicial seja a terceira, deverá inserir a coordenada de linha inicial como 4.</li>
</ul>

## Compilação e Execução

O repositório possui um arquivo <i>Makefile</i> que realiza todo o procedimento de compilação e execução. Para tanto, temos as seguintes diretrizes de execução:

<table align="center">
  <tr>
    <td><strong>Comando</strong></td>
    <td><strong>Função</strong></td>
  </tr>
  <tr>
    <td><code>make clean</code></td>
    <td>Apaga a última compilação realizada contida na pasta build.</td>
  </tr>
  <tr>
    <td><code>make</code></td>
    <td>Executa a compilação do programa utilizando o g++, e o resultado vai para a pasta build.</td>
  </tr>
  <tr>
    <td><code>make run</code></td>
    <td>Executa o programa da pasta build após a realização da compilação.</td>
  </tr>
</table>
