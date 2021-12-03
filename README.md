# Quantização de Imagens
Repositório destinado á Atividade Avaliativa II de Programação de Software Básico

  ## Introdução
  O objetivo deste trabalho é a implementação de um algoritmo para quantização de imagens, isto é, redução da quantidade de cores. A principal aplicação desse algoritmo é a redução no espaço de armazenamento de uma imagem, com alguma perda de qualidade.
  
  ## Lógica Utilizada
  Para atingir o objetivo, vamos pegar a imagem passada e substituir os seus pixels pela cor RGB mais semelhante a ela, dentro das 256 cores que mais aparecem na imagem original. Para isso, seguiremos o seguinte passo a passo.
  
  ### 1º - Mapear todas as cores da imagem original
  <p> Realizamos uma varredura (laço FOR) por todos os pixels da imagem e armazenamos a cor de cada pixel em um vetor do tipo RGB.<p>

  ### 2º - Separar as top 256 cores que mais aparecem
  <p> Fazer o levantamento da quantidade de vezes que cada cor aparece.<p>
  <p> Armazenamos as 256 cores que mais aparecem em um novo vetor.<p>
  
  ### 3º - Substituir cada pixel/cor da imagem original pela cor mais semelhante dentro das top 256 cores que mais aparecem
  <p> Realizamos uma varredura (laço FOR) por todos os pixels da imagem novamente e descobrimos com qual das 256 cores cada pixel tem maior semelhança.<p>
  <p> Substituimos cada pixel da imagem pela cor RGB mais semelhante.<p>
