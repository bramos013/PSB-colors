/*
void process()
{
    //
    // EXEMPLO: preenche a imagem 8 bits com pixels de cores diversas
    //
    //
    // SUBSTITUA este código pelos algoritmos a serem implementados
    //    
    int tam = pic.width * pic.height;
    int vet[10];
    int corAtual;
    
    //Passa por todos os pixels da imagem
    for (int i = 0; i < 10; i++)
    {

       cor.intensidade.r = pic.pixels[i].r;
       int valida=0;

        //vet[i].intensidade.r = cor.intensidade.r;        

        //Passa por todo o vetor de cores
        //Verifica se a cor já existe

        //CORRIGIR ESPAÇO QUE ESTÁ SENDO ARMAZENADO NO VETOR
       for (int j = 0; j < 10; j++)
       {
            if (cor.intensidade.r == vet[j].intensidade.r)            
            {
                valida = 1;
                vet[j].quantidade++;                                                
                break;
            }               
            
       }

       for (int i = 0; i < vet; i++)
       {
           if (vet[i] != )
           {
               /* code */
           }
           
       }
       
          if (valida == 0)
            {
                vet[i] = cor;
                vet[i].quantidade++;
            }
       
          

    }   
        for (int i= 0; i < 10; i++)
    {
            printf("\nVetor = %d ",vet[i].intensidade.r);
    }

//Feito isso temos a lista com os tons de vermelho da imagem
//Já com os tons de vermelho na paleta de cores, verificar quais os tons de verde que mais se repetem com o vermelho
//Repetir o processo para os tons de azul
/*

----------------------------    
PALETA DE CORES = (10 20 30 40 50 60 70 80 90 100) <- Tons de vermelho
IMAGEM = (10 20 25 30 35 40 45 50 55 60 65) <- Tons de vermelho

TOM 10 Esta na paleta ? Sim -> Verificas os tons de verde que mais se repetem com o tom de vermelho 10
TOM 25 Esta na paleta ? Não -> Avança pro próximo pixel


----------------------------*/

    //
    // NÃO ALTERAR A PARTIR DAQUI!!!!
    //
    buildTex();
    
}