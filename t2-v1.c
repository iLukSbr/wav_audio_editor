/* Aluno: Omar Zagonel El Laden - Matricula: 2505649                          */
/* Aluno: Lucas Yukio Fukuda Matsumoto - Matricula: 2516977                   */
/*============================================================================*/
/* CSF13 - 2022-2 - TRABALHO 2                                                */
/*----------------------------------------------------------------------------*/
/* Bogdan T. Nassu - btnassu@utfpr.edu.br                                     */
/* Leyza E. B. Dorini - leyza@utfpr.edu.br                                    */
/*============================================================================*/
/* Funcoes pedidas para o 2o trabalho da disciplina Fundamentos de Programacao*/
/* 1, 2o semestre de 2022, prof. Bogdan T. Nassu e Leyza E. B. Dorini,        */
/* Universidade Tecnologica Federal do Parana.                                */
/*============================================================================*/

#include "trabalho2.h"
#include "wavfile.h"

#define SCORE_MINIMO 0.5

/*============================================================================*/
/* Funcao 1                                                                   */

void mudaGanho (double* dados, int n_amostras, double ganho)
{
    int i;
    if(ganho != 1)// se quiser algum ganho, sera diferente de 1
        for(i=0; i < n_amostras; i++)// percorre dados do inicio ao fim
            dados[i] *= ganho;// multiplica dados na posicao i por ganho
}

/*============================================================================*/
/* Funcao 2                                                                   */

void meiaVelocidade (double* dados, int n_amostras, double* saida)
{
    int i, j;
    for(i=0, j=0; i < n_amostras; i++, j+=2)// perorre dados de 1 em 1 do inicio ao fim e saida de 2 em 2
    {
        saida[j+1] = saida[j] = dados[i];// as duas posicoes de saida, j e j+1, recebem dados da posicao i
    }
}

/*============================================================================*/
/* Funcao 3                                                                   */

void dobraVelocidade (double* dados, int n_amostras, double* saida)
{
    int i, j;
    for(i=0, j=0; i < n_amostras; i+=2, j++)// do inicio ao fim do dados, pulando uma amostra a cada iteracao
        saida[j] = dados[i];// guarda o valor do dados na saida
}

/*============================================================================*/
/* Funcao 4                                                                   */

void fade (double* dados, int n_amostras, int inicio, int fim, int in_out)
{
    int i, j;
    if(in_out < 0)// fade out, de inicio ate fim
        for(i=inicio, j=fim - inicio; i<=fim && i<n_amostras; i++, j--)// ate fim ou ate acabar dados
            dados[i] *= (double) j/(fim - inicio);// reduz dados proporcional a posicao entre fim e inicio, de 100% a 0
    else if(in_out > 0)// fade in, de inicio ate fim
        for(i=inicio, j=0; i<=fim && i<n_amostras; i++, j++)// ate fim ou ate acabar dados
            dados[i] *= (double) j/(fim - inicio);// reduz dados proporcional a posicao entre fim e inicio, de 0 a 100%
}

/*============================================================================*/
/* Funcao 5                                                                   */

int buscaPadrao (double* dados, int n_amostras, double* padrao, int n_amostras_padrao, double* score)
{
    int pos, i, j;
    double deno=0, score_buffer=0;
    *score = 0;// remove lixo do score
    for(i=0; i<n_amostras; i++)// do inicio ao fim do dados
    {
        for(j=0; j<n_amostras_padrao && (i + j)<n_amostras; j++)// do inicio ao fim do padrao ou ate acabar dados
            score_buffer += dados[i + j]*padrao[j];// somatorio do numerador
        if(score_buffer > *score)// se for o maior score obtido
        {
            *score = score_buffer;// substitui o maior score anterior
            pos = i;// guarda a posicao desse score
        }
        score_buffer = 0;// reinicia o buffer para a proxima iteracao
    }
    for(i=0; i<n_amostras_padrao; i++)// do inicio ao fim do padrao
        deno += padrao[i]*padrao[i];// somatorio do denominador
    *score /= deno;// divide numerador pelo denominador
    if(*score > SCORE_MINIMO)// se o score nao for fraco
        return pos;// retorna a posicao do maior score
    else// se o score nao atendeu ao requisito
        return (-1);
}

/*============================================================================*/
