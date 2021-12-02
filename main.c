#include <math.h>
#include <string.h>		// para usar strings
#include "include/SOIL.h"

// Rotinas para acesso da OpenGL
#include "opengl.h"

// Variáveis globais a serem utilizadas:

// Dimensões da imagem de entrada
int sizeX, sizeY;

// Imagem de entrada
Image24 pic;

// Imagem de 8 bits
Image8 pic8;

// Color
//Color cor;

// Modo de exibição atual
int modo;


// Protótipos
void load(char* name, Image24* pic);
void process();

// Carrega uma imagem para a struct Img
void load(char* name, Image24* pic)
{
    int chan;
    pic->pixels = (RGB8*) SOIL_load_image(name, &pic->width, &pic->height, &chan, SOIL_LOAD_RGB);
    if(!pic->pixels)
    {
        printf( "SOIL loading error: '%s'\n", SOIL_last_result() );
        exit(1);
    }
    printf("Load: %d x %d x %d\n", pic->width, pic->height, chan);
}
  

// Função principal de processamento: ela deve chamar outras funções
// quando for necessário

void process()
{
    //int tam = pic.width * pic.height;
    int tam = 10000;
    int cor[tam];
    RGB8 paletaCompleta[tam];
    RGB8 amostra[tam];
    int count;
    int corAtual = 0;
    

//ATUALMENTE ESTE CÓDIGO CAPTURA O TOM DE VERMELHO E A QUANTIDADE DE VEZES QUE ELE APARECE
    
    //Preencher a paleta de cores com todas as cores
    for(int i = 0; i < tam; i++){
        paletaCompleta[i] = pic.pixels[i];            
        //printf("R=%d G=%d B=%d\n", paletaCompleta[0].r, paletaCompleta[0].g, paletaCompleta[0].b);
    }
    
    //Ordenar a paleta de cores
    int continua =1;
    while(continua){
        continua = 0;
        //Ordenar do MAIOR R para o MENOR
        for(int i = 0; i < tam; i++){
            if(paletaCompleta[i].r < paletaCompleta[i+1].r){
                RGB8 tmp;;
                continua = 1;
                tmp = paletaCompleta[i];
                paletaCompleta[i] = paletaCompleta[i + 1];
                paletaCompleta[i + 1] = tmp;
            }            
        }
        //Ordenar do MAIOR G para o MENOR
        for (int i = 0; i < tam; i++)
        {
            if(paletaCompleta[i].r == paletaCompleta[i+1].r){                
                if (paletaCompleta[i].g < paletaCompleta[i+1].g)
                {
                    RGB8 tmp;;
                    continua = 1;
                    tmp = paletaCompleta[i];
                    paletaCompleta[i] = paletaCompleta[i + 1];
                    paletaCompleta[i + 1] = tmp;
                }                                
            }
        }        
        //Ordenar do MAIOR B para o MENOR
        for (int i = 0; i < tam; i++)
        {
            if(paletaCompleta[i].r == paletaCompleta[i+1].r){                
                if (paletaCompleta[i].g == paletaCompleta[i+1].g)
                {
                    if (paletaCompleta[i].b < paletaCompleta[i+1].b){
                    RGB8 tmp;;
                    continua = 1;
                    tmp = paletaCompleta[i];
                    paletaCompleta[i] = paletaCompleta[i + 1];
                    paletaCompleta[i + 1] = tmp;
                }                                
            }
        }

        //Verificar a quantidade de vezes que cada RGB aparece
        for (int i = 0; i < tam; i++)
        {
            count = 0;
            for (int j = 0; j < tam; j++)
            {
                if(paletaCompleta[i].r == paletaCompleta[j].r){
                    if(paletaCompleta[i].g == paletaCompleta[j].g){
                        if(paletaCompleta[i].b == paletaCompleta[j].b){
                            count++;
                        }
                    }
                }
            }
            paletaCompleta[i].quantidade = count;
        }

        //Criar um vetor com uma amostra de cada RGB
        
        int p = 0;
        for (int i = 0; i < tam; i++)
        {
            int valida=1;
            for (int j = 0; j < tam; j++)
            {
                if(paletaCompleta[i].r == amostra[j].r && paletaCompleta[i].g == amostra[j].g && paletaCompleta[i].b == amostra[j].b){                    
                    valida = 0;                                        
                }
            }
            //Se o RGB não for repetido no vetor, adicionar na posicao p             
            if(valida == 1){                
                amostra[p] = paletaCompleta[i];
                p++;                
            }            
        }
        
        
    }
    //Ordenar o vetor de amostras pela quantidade de vezes que aparece
    int continua =1;
    while(continua){
        continua = 0;
        //Ordenar da MAIOR quantidade para o MENOR
        for(int i = 0; i < tam; i++){
            if(amostra[i].quantidade < amostra[i+1].quantidade){
                RGB8 tmp;;
                continua = 1;
                tmp = amostra[i];
                amostra[i] = amostra[i + 1];
                amostra[i + 1] = tmp;
            }            
        }
    }

    //Preencher a paleta final com as 256 cores maiormente repetidas
    for(int i = 0; i < 256; i++){
        if(amostra[i].quantidade > 0 && amostra[i].quantidade < 48){
            pic8.pal[i] = amostra[i];
        }
    }

    //Imprime ordenado
    for(int i = 0; i < 256; i++){
           printf("R=%d G=%d B=%d\n", pic8.pal[i].r, pic8.pal[i].g, pic8.pal[i].b);        
    }


    
    
    /*
    
    //Passa por todos os pixels da imagem    
    for (int i = 0; i < 10; i++){      
        count = 0;

        //Percorre a imagem e acrescenta cada tom de vermelho ao vetor cor
       for (int j = 0; j < (int)( sizeof(cor) / sizeof(cor[0])); j++){
            cor[i] = pic.pixels[i].r;                     
            corAtual = pic.pixels[j].r;

            //Verifica se o tom de vermelho atual é igual ao tom de vermelho da imagem
            if (cor[i] == cor[j]){
                count++;                             
            }               
       }                     
            //printf("\nCor=%d Count=%d", cor[i],count);
            
    }
        

pal[0] = {0,0,0};

    printf("\nORDENAÇÃO");
    ordenaVetor(cor, tam);
    
    for (int i = 0; i < 20; i++)
    {
        printf("\n%d", cor[i]);
    }
    
      */ 
    //
    // NÃO ALTERAR A PARTIR DAQUI!!!!
    //
    buildTex();
    
    }
}
int main(int argc, char** argv)
{
    if(argc==1) {
        printf("quant [image file]\n");
        exit(1);
    }

    // Inicialização da janela gráfica
    init(argc,argv);

    load(argv[1], &pic);
    sizeX = pic.width;
    sizeY = pic.height;

    // Aloca memória para imagem de 8 bits
    pic8.width  = sizeX;
    pic8.height = sizeY;
    pic8.pixels = (unsigned char*) malloc(sizeX * sizeY);

    modo = IMG24;

    // Aplica processamento inicial
    process();

    // Não retorna... a partir daqui, interação via teclado e mouse apenas, na janela gráfica
    glutMainLoop();
    return 0;
}