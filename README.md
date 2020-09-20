# Computacao_Grafica_UFLA
Exercícios feitos na disciplina Computação Gráfica - UFLA

Exercicios teoricos da **"Lista de Exercícios de Computação Gráfica"** - http://professores.dcc.ufla.br/~bruno/aulas/cg/exerc/

## Exercicios 14 e 15

**14. As duas figuras ao lado são projeções do mesmo cubo no mesmo plano. Qual é a projeção paralela? Qual é a projeção perspectiva? Explique.**

A imagem "a" é a projeção paralela pois todas as retas paralelas do cubo continuam paralelas na projeção em duas dimensões.
A imagem "b" é a projeção perspectiva pois as únicas retas que continuam paralelas são as paralelas ao plano de projeção, assim não paralelas convergem para um    ponto de fuga.  

**15. Uma projeção perspectiva pode ser definida em termos de um ponto e um plano, de tal forma que o plano tenha embutido um sistema de coordenadas de duas dimensões. Várias bibliotecas gráficas definem uma câmera virtual através de um ponto e dois vetores. O ponto indica onde a câmera está. Um dos vetores indica a direção "para onde a câmera está olhando" e o outro indica qual a direção "para cima" relativa à câmera. Invente uma forma de associar os elementos de tal câmera virtual aos elementos de uma projeção perspectiva. Explique essa associação que você inventou.**

_Feedback do professor: O foco do exercício 15 era que você notasse que um ponto e dois vetores não são suficientes para definir uma projeção. O exercício 16 (que migrou para o Dredd) dava um reforço importante nisso, porque mostrava explicitamente que é preciso mais que isso para definir uma projeção. Então porque é comum essa estrutura para representar câmeras? Câmeras não são projeções, é preciso alguma informação extra, geralmente escondida, para completar as informações da projeção. Algumas respostas chegaram a incluir desenhos onde fica claro que faltava informação para posicionar o plano de projeção no espaço (ou faltava informação para definir o centro de projeção no espaço, dependendo da associação escolhida). Uma forma fácil de prover a informação que falta é determinar uma distância (informação oculta da câmera) de tal forma que o plano de projeção, ortogonal à direção para onde a câmera está olhando, teria sua origem._


## Exercicios 17, 18, 20, 21 e 22

**17. O algoritmo de Cohen-Sutherland para o recorte de segmentos retas no plano, classifica uma extremidade de segmento de reta com um dos nove códigos apresentados ao lado (números no sistema binário). Explique quais são os casos em que os segmentos não precisam ser processados. Explique como identificar estes casos em um programa de computador.**

Para realizar o recorte de um segmento de reta, classifica-se as duas extremidades do segmento de acordo com o rótulo da região onde a extremidade se encontra.
Se ambos os códigos forem zero, o segmento está todo dentro da região de recorte e não é necessário calcular nenhum ponto de interseção. Além disso, se o resultado de um operação de “e” lógico bit a bit for diferente de zero, então os dois códigos tem um bit em comum e portanto o segmento está totalmente fora do retângulo de recorte, assim, também não é preciso calcular a interseção.

Para identificar estes casos, primeiro basta verificar se os códigos das duas extremidades é igual a 0000, se sim, o segmento está todo dentro da região de recorte e então não é necessário calcular a interseção. Se não, utilizamos a operação de “e” lógico bit a bit. Se o resultado da operação for 0000, devemos calcular uma interseção do segmento de reta com um dos lados do retângulo de recorte. Se o resultado for diferente de 0000 o segmento está totalmente fora do retângulo de recorte, logo, não é necessário calcular a interseção.

**18. O algoritmo de Cyrus-Beck para o recorte paramétrico de retas foi aperfeiçoado por Liang e Barsky que simplesmente fizeram simplificações matemáticas para um caso especial. Cite qual foi este caso especial.**

Liang e Barsky tornaram o algoritmo de Cyrus-Beck mais eficiente nos casos em que o volume de recorte é um retângulo alinhado com os eixos do sistema de coordenadas.

**20. Explique qual a simplificação apresentada por Liang e Barsky em seu algoritmo de recorte (em relação ao algoritmo de Cyrus-Beck), deduzindo o cálculo da interseção de um segmento de reta (que vai do ponto P1 ao ponto P2) com um retângulo de recorte definido pelos limites (xmin, xmax, ymin, ymax).**

A simplificação ocorre por sabemos que a normal N_i sempre tem uma coordenada com valor 0, o que significa que o produto escalar N_i · (P_0 − P_Li )não precisa considerar a coordenada correspondente no vetor (P_0 − P_Li ), justamente a coordenada que precisaria ser aleatóriamente escolhida. Assim o denominador do cálculo de t, fica reduzido o que representa uma boa economia de operações aritméticas em relação à formula geral apresentada antes.

Para deduzir basta substituir os valores na formula geral e simplificar.

| RECORTE           | NORMAL N_i | P_Ei      | P_0 - P_Ei        | t = N_i*(P_0-P_Ei)/-N_i*D |
| ----------------- | ---------- | --------- | ----------------- | ------------------------- |
| Esquerda: x=x_min | (-1,0)     | (x_min,y) | (x_0-x_min,y_0-y) | (-1,0)*(x_0-x_min)/-(-1,0)*(x-x_0) => -(x_0-x_min)/(x-x_0) |
| Direita: x=x_max  | (1,0)      | (x_max,y) | (x_0-x_max,y_0-y) | (1,0)*(x_0-x_max)/-(1,0)*(x-x_0) => (x_0-x_max)/-(x-x_0)   |
| Baixo: y=y_min    | (0,-1)     | (x,y_min) | (x_0-x,y_0-y_min) | (0,-1)*(y_0-y_min)/-(0,-1)*(y-y_0) => -(y_0-y_max)/(y-y_0) |
| Cima: y=y_max     | (0,1)      | (x,y_max) | (x_0-x,y_0-y_max) | (0,1)*(y_0-y_max)/-(0,1)*(y-y_0) => (y_0-y_max)/-(y-y_0)   |


**21. O segmento ao lado tem 4 interseções com os lados de uma área de recorte. Explique como o algoritmo do recorte paramétrico pode saber quais dos seis pontos envolvidos definem o segmento recortado (o segmento vai de P0 a P1).**

Primeiro deve-se utilizar a equação do método e classificar os pontos em Potencialmente entrando e Potencialmente saindo.
Depois disso os pontos de entrada e saída do segmento na área de recorte podem ser inicializados respectivamente com valores de 0 e 1 para t. Assim somente valores entre 0 e 1 serão usados e os pontos P_0 e P_1 farão parte do resultado a menos que pontos mais internos ao segmento sejam encontrados. Ao final do recorte em relação aos quatros lados, teremos um valor de t para o ponto de entrada, cujas coordenadas devem ser calculadas se t > 0 
(se t = 0, o ponto de entrada é P_0 e portanto tem coordenadas conhecidas). Teremos também um valor de t para o ponto de saída, cujas coordenadas devem ser calculadas se t < 1. Assim não são calculadas coordenadas que não façam parte do resultado.

**22. Quantos segmentos de elipse podem ser definidos pelo recorte de uma elipse em relação a um retângulo? Mostre graficamente.**

Esta em um pdf no repositorio
