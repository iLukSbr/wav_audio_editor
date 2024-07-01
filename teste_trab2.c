#define SCORE_MINIMO 0.5

int buscaPadrao (double* dados, int n_amostras, double* padrao, int n_amostras_padrao, double* score);

int main()
{
    double dados={1, -3, 5, -2, 4, -1, 3, -5, 2, -8, 6, -7, 8, -20, 19, -10, 0, -2}
}

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
