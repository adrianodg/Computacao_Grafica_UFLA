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

Esta em pdf no repositorio - "exerc22.pdf".  

_Feedback do professor: Questão 21: Fez uma explicação geral mas respondeu a pergunta, quais pontos do exemplo eram PS e quais eram PE? Quais tinha t maior e quais tinham t menor?_


## Exercicios 24, 26, 27 e 28

**24. Alguns programas de computador definem cores em relação a valores intitulados RGB, alguns usam valores intitulados CMYK e alguns usam os dois. Explique o que esses valores significam, para exemplificar, cite quais seriam os valores (nos dois sistemas) para definir as cores preto e branco.**

RGB corresponde às iniciais das 3 cores Red (vermelho), Green (verde) e Blue (azul). Uma cor no modelo de cores é descrita indicando quanto de cada cor está incluído. A cor é expressa por três valores (r, g, b), que podem variar de zero a um valor máximo definido. Se todos os componentes estiverem em zero, o resultado será preto, e se todos estiverem no máximo, o resultado será o branco mais brilhante possível. Nos computadores, os valores muitas vezes são armazenados como números inteiros no intervalo de 0 a 255, o intervalo que um único byte de 8 bits pode oferecer. Os valores no sistema geralmente são representados como números decimais ou hexadecimais. Na notação decimal a cor preta pode ser representada por (0,0,0) e a branca (255,255,255).

CMYK corresponde às letras das cores Cian (ciano), Magenta (magenta), Yellow (amarelo) and Black (preto). ​ O modelo funciona devido à absorção de luz, pelo fato de que as colorações que são vistas vêm da parte da luz que não é absorvida. É definido como um sistema subtrativo de cores. ​ Uma cor no modelo de cores é descrita indicando quanto de cada cor está incluído. A cor é expressa por quatro valores que representam a porcentagem da cor específica incluída. Os valores podem variar de 0 a 100 ou de 0 a 1. Assim, no primeiro intervalo a cor preta pode ser representada por (0,0,0,100) e a branca (0,0,0,0).

**26. [ENADE 2017] Em computação gráfica, existem vários modelos de iluminação diferentes que expressam e controlam os fatores que determinam a cor de uma superfície em função de um determinado conjunto de luzes. Uma vez definido um modelo de iluminação, pode-se aplicar luz sobre as várias faces dos objetos de uma cena, processo denominado sombreamento. A figura à esquerda ilustra a aplicação de dois modelos de iluminação, a saber: o modelo de sombreamento constante (à esquerda) e o modelo de Phong (à direita).**

A alternativa correta é a B.  

A afirmação I está correta, pois as Bandas de Mach são a tendência do olho humano de ver faixas claras ou escuras perto dos limites entre áreas com iluminação nitidamente diferente.  

A afirmação II está incorreta, pois o método Phong produz resultados bons, ele é um meio-termo entre aplicar o modelo de iluminação em cada ponto e o método de Gouraud.  

A afirmação III está correta, pois o modelo de sombreamento constante, gera as Bandas de Mach, esse efeito é uma das desvantagem do modelo, que o torna indesejável mesmo para objetos compostos de polígonos pequenos. Assim o cérebro humano tende a destacar as variações de intensidade de luz. Isso gera um destaque para a linha divisória onde a intensidade muda, deixando a imagem menos realista.  

A afirmação IV está incorreta, pois no método de Phong não é necessária a suposição. Ele é um método que faz a interpolação d​ as normais da superfície entre polígonos rasterizados e calcula as cores dos pixels. A definição é que o modelo de iluminação precisa ser aplicado a cada pixel do polígono.

**27. Na imagem ao lado, temos a vista frontal de um armário muito distante do observador, à frente de uma parede de tijolos brancos. Observa-se que em determinados pontos, o programa que gerou a imagem "achou" que a parede estava à frente do armário. A parede é representada por um único retângulo e toda a parte frontal do armário é representa por outro retângulo. Supondo que o programador deseja resolver este problema através da troca do algoritmo de determinação de superfícies visíveis, que características deve ter o novo algoritmo escolhido?**

O algoritmo deve ordenar todos os polígonos da cena em relação à distância entre eles e o observador, depois desenhar os polígonos em ordem, do mais distante do observador até o mais próximo. Pode-se processar a representação dos polígonos, produzindo novos polígonos que podem efetivamente ser ordenados e então desenhados de trás para frente.

**28. Assinale como V ou F**

a. (V) Para um objeto cuja superfície é polida, os raios de luz tendem a ser refletidos de maneira previsível. Porém nenhuma superfície é um espelho perfeito, mas a luzrefletida num objeto polido fica mais concentrada numa direção simétrica (em relação à normal) à direção de incidência. Logo gera-se um reflexo.  

b. (F) Em sistemas 32 bits para identificar um pixel na tela, neste caso, os 8 bits restantes possivelmente servem para identificar transparência, possibilitando que, ao ser desenhado, a cor de um pixel na tela dependa da cor que estava previamente naquela posição. Isso não necessariamente deixa os resultados “bem mais realísticos que os sistemas que usam 24 bits” é apenas uma abordagem diferente.  

c. (V) Apesar dos muitos modelos de representação de cores, a conversão de um para outro é teoricamente sempre possível. Assim uma imagem colorida pode ser tratada de forma parecida a uma preto e branca, uma vez que a computação gráfica se preocupa mais em como gerar a imagem ou modelo do que as cores dos mesmos.  

d. (F) Não existe problema algum em usar o sistema CMYK em arquivos que armazenam imagens, pois se for preciso em outro sistema, basta converter.

_Feedback do professor: Q26 II - fala de eficiência, justificativa fala de "resultados bons".  
 Q26 IV - a justifica não aborda a fonte de luz no infinito.  
 Q28 b - justifica com uma consequência ao invés de uma causa; é comum o uso de 24 bits de cor + 8 de transparência porque 32 bits de cor não necessariamente trariam benefícios e não o contrário.  
 Q28 c - justificativa sem sentido já que imagens PeB não seguem um sistema de representação de cores, não concordo que CG se preocupe mais com as formas que as cores._
 
## Exercicio 30

**30. Escolha os pixels para desenhar o segmento entre (2, 1) e (7, 4), seguindo o algoritmo do ponto médio.**

Esta em pdf no repositorio - "pontos_ex30.pdf".  

## Exercicio 31

**31. Observe esse vídeo em que a tela de um celular foi filmada por uma câmera digital. Explique o aparecimento de linhas e curvas na imagem da tela do celular.**

O aparecimento de linhas e curvas na imagem da tela ocorre por um efeito chamado Aliasing que é o resultado da perda de informação na conversão de informações de natureza contínua em informações discretas. Nesse caso em específico o efeito é o aliasing espacial que também é responsável pelo aparecimento de padrões moiré, comuns em função da popularização de fotos e filmes digitais. Televisores, câmeras digitais e celulares usam uma técnica de digitalização para produzir ou capturar imagens com linhas horizontais de varredura, logo, quando se filma uma tela os conjuntos de linhas conflitantes causam os padrões moiré. Além disso o celular apresenta uma imagem com uma resolução relativamente baixa o que implica na baixa quantidade de elementos discretos presentes no espaço de apresentação isso gera uma acentuação dos padrões. Quando a câmera aproxima-se do celular, assim, aumentando ainda mais a percepção da baixa densidade dos pixels na tela, o padrão moiré se torna mais visível. Quando a câmera se afasta ocorre o efeito contrário e nota-se uma diminuição dos padrões. Há várias formas de evitar o aliasing, como aumentar a resolução do dispositivo ou aplicar filtros anti-aliasing.


# Locais com conteudos relacionados a disciplina:

- Canal **ChiliTomatoNoodle:** https://www.youtube.com/user/ChiliTomatoNoodle
- Canal **Bisqwit:** https://www.youtube.com/user/Bisqwit
- Repositorios: https://github.com/samurai-753
