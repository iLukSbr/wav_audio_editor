#include<stdio.h>

#define N 12
#define N_PADRAO 6

#define SCORE_MIN 0.5

int buscaPadrao (double* dados, int n_amostras, double* padrao, int n_amostras_padrao, double* score);

int main()
{
    int i, pos;
    double score, dados[N]={1,-2,3,-4,5, -1, 5, 0, -6}, padrao[N_PADRAO] = {5, 3, 0, -3, -6};

    // preenche
//    for(i=0; i<N; i++)
//    {
//        dados[i] = i;
//        printf("%lf\n", dados[i]);
//    }
    pos = buscaPadrao(dados, N, padrao, N_PADRAO, &score);
    // print
    printf("\npos=%d\nscore=%lf\n", pos, score);

    return 0;
}

int buscaPadrao (double* dados, int n_amostras, double* padrao, int n_amostras_padrao, double* score)
{
    int i, j, pos=-1;
    double deno=0, score_buffer=0, dif_min=0, dif;
    for(i=0; i<n_amostras_padrao; i++)// do inicio ao fim do padrao
    {
        deno += padrao[i]*padrao[i];// somatorio do denominador
        printf("deno=%lf\n",deno);
    }
    for(i=0; i<n_amostras; i++)// do inicio ao fim do dados
    {
        for(j=0; j<n_amostras_padrao && (i + j)<n_amostras; j++)// do inicio ao fim do padrao ou ate acabar dados
            score_buffer += dados[i + j]*padrao[j];// somatorio do numerador
        dif = score_buffer - deno;// diferenca entre numerador e denominador, quanto mais proximo de 0, melhor o score, que aproxima-se de 1
        if(dif < 0)
            dif *= -1;
        if(dif < dif_min || pos == -1)
        {
            *score = score_buffer;// substitui pelo melhor score
            pos = i;// guarda a posicao desse score
            dif_min = dif;// guarda a menor diferenca
        }
        printf("\ni=%d\ndif=%lf\nscore_buffer=%lf\nmelhor pos=%d\nmelhor score=%lf\n", i, dif, score_buffer, pos, *score);
        score_buffer = 0;// reinicia o buffer para a proxima iteracao
    }
    *score /= deno;// divide numerador pelo denominador
    if(*score > SCORE_MIN || *score < 1 + SCORE_MIN)// se o score nao for fraco
        return pos;// retorna a posicao do melhor score
    else// se o score nao atendeu ao requisito
        return (-1);
}
