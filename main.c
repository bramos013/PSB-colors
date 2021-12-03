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

double distanciaRGB(RGB8* p1, RGB8* p2){
    return pow(p1->r - p2->r, 2) + pow(p1->g - p2->g, 2) + pow(p1->b - p2->b, 2);
}

// Função principal de processamento: ela deve chamar outras funções
// quando for necessário

void process()
{
    //int tam = 5000;
    int tam = pic.width * pic.height;    
    int cor[tam];
    int count;
    int continua=1;
    RGB8 paletaCompleta[tam];
    RGB8 amostra[tam];
    RGB8 aux;
    
        //CRIAÇÃO DO ARRAY DE CORES 
        for(int i = 0; i < tam; i++){
            //ORDENAÇÃO DO ARRAY
            for(int j = 0; j < tam; j++){                                     
                //ORDENAÇÃO POR VERMELHO
                if(paletaCompleta[i].r < paletaCompleta[j].r){                    
                    aux = paletaCompleta[i];
                    paletaCompleta[i] = paletaCompleta[j];
                    paletaCompleta[j] = aux;                    
                }                            
                //ORDENAÇÃO POR VERDE
                if(paletaCompleta[i].r == paletaCompleta[j].r){                
                    if (paletaCompleta[i].g < paletaCompleta[j].g){
                        aux = paletaCompleta[i];
                        paletaCompleta[i] = paletaCompleta[j];
                        paletaCompleta[j] = aux;                                        
                    }                                
                }
                //ORDENAÇÃO POR AZUL
                if(paletaCompleta[i].r == paletaCompleta[j].r){                
                    if (paletaCompleta[i].g == paletaCompleta[j].g){
                        if (paletaCompleta[i].b < paletaCompleta[j].b){                           
                            aux = paletaCompleta[i];
                            paletaCompleta[i] = paletaCompleta[j];
                            paletaCompleta[j] = aux;
                        }                                
                    }    
                }
            }
        }        
        //ARMAZENA A QUANTIDADE DE CADA COR
        for(int i = 0; i < tam; i++){
            count = 0;
            for (int j = 0; j < tam; j++){
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
        //ARMAZENA UMA VEZ CADA COR  NO ARRAY DE AMOSTRA  
        int p = 0;
        for (int i = 0; i < tam; i++){
            int valida=1;
            for (int j = 0; j < tam; j++){
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

        //ORDENA A QUANTIDADE DE CADA COR
        for(int i = 0; i < tam; i++){
            if(amostra[i].quantidade < amostra[i+1].quantidade){                                
                aux = amostra[i];
                amostra[i] = amostra[i + 1];
                amostra[i + 1] = aux;
            }            
        }

        for(int i = 0; i < 256; i++){
        if(amostra[i].quantidade > 0 && amostra[i].quantidade < 48){
            pic8.pal[i] = amostra[i];
        }
    }

    //VARIAVEL AUXILIAR PARA VERIFICAR A DISTANCIA ENTRE OS PIXELS
    int menor=255;
    RGB8 corSemelhante;

    //CAPTA PIXELS DA IMAGEM DE ENTRADA
    for (int i = 0; i < 100000; i++){
        //VERIFICA NA PALETA DE CORES QUAL A COR DO PIXEL ORIGEM É MAIS SEMELHANTE 
        for (int j = 0; j < 256; j++){
            printf("I=$%d J=$%d\n", i, j);

            if(menor > distanciaRGB(&pic.pixels[i], &pic8.pal[j])){
               pic.pixels[i] = pic8.pal[j];
               menor = distanciaRGB(&pic.pixels[i], &pic8.pal[j]);
               corSemelhante = pic8.pal[j];
            }
        }
        //TROCA O PIXEL ORIGEM PELA COR MAIS SEMELHANTE
        //pic.pixels[i] = corSemelhante;

    }
        
    //
    // NÃO ALTERAR A PARTIR DAQUI!!!!
    //
    buildTex();
    
    
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
