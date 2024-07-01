/*============================================================================*/
/* Exemplo (gerador): gera um arquivo contendo ru�do, e "cola" sobre ele uma
 * trilha de �udio. */

#include <stdlib.h>
#include "wavfile.h"

#include "trabalho2.h"

/*============================================================================*/

#define INPUT_FILE "data/teste.wav" /* �udio ru�do */
#define PASTE_FILE "data/sonic1.wav" /* �udio onde o ru�do ser� colado */
#define OUTPUT_FILE "data/teste5.wav" /* �udio resultante */

#define MUTA_PASTE 0 /* 1 muta o �udio destino onde for colar o ru�do, 0 mistura os �udios */
#define ATENUACAO_RUIDO 0.8 /* Fator de atenua��o para o ru�do. Quanto menor, menos ru�do. */
#define ATENUACAO_PASTE 0.9 /* Fator de atenua��o para o paste. Quanto menor, menos paste. */
#define POSICAO_INICIAL 44100*30 /* Posi��o inicial para os dados do arquivo. */

/*============================================================================*/

void misturaDados (double* dados1, double* dados2, double* saida, int n_amostras);

int main ()
{
    WavHeader header_in; /* Cabe�alho para as informa��es sobre o arquivo ru�do. */
    WavHeader header_ps; /* Cabe�alho para as informa��es sobre o arquivo paste. */
    double* dados_in_l; /* Dados do canal esquerdo ru�do. Alocado na readWavFile. */
    double* dados_in_r; /* Dados do canal direito ru�do. Alocado na readWavFile. */
    double* dados_ps_l; /* Dados do canal esquerdo paste. Alocado na readWavFile. */
    double* dados_ps_r; /* Dados do canal direito paste. Alocado na readWavFile. */
	int n_amostras_in; /* N�mero de amostras nos buffers ru�do. */
	int n_amostras_ps; /* N�mero de amostras nos buffers paste. */

    /* L� o arquivo. */
    n_amostras_in = readWavFile (INPUT_FILE, &header_in, &dados_in_l, &dados_in_r);
    if (!n_amostras_in)
    {
        printf ("Erro lendo %s.\n", INPUT_FILE);
        return (1);
    }

    n_amostras_ps = readWavFile (PASTE_FILE, &header_ps, &dados_ps_l, &dados_ps_r);
    if (!n_amostras_ps)
    {
        printf ("Erro lendo %s.\n", PASTE_FILE);
        return (1);
    }

    if (n_amostras_in + POSICAO_INICIAL > n_amostras_ps)
    {
        printf ("Os dados do arquivo nao cabem no sinal a partir da posicao %d.\n", POSICAO_INICIAL);
        return (1);
    }

    /* Preenche o sinal com ru�do, e "cola" os dados do arquivo no sinal. */
    mudaGanho (dados_in_l, n_amostras_in, ATENUACAO_RUIDO);
    mudaGanho (&(dados_ps_l[POSICAO_INICIAL]), n_amostras_in, ATENUACAO_PASTE);
    misturaDados (&(dados_in_l [0]), &(dados_ps_l[POSICAO_INICIAL]), &(dados_ps_l [POSICAO_INICIAL]), n_amostras_in);
    if (dados_in_r && dados_ps_r)
    {
        mudaGanho (dados_in_r, n_amostras_in, ATENUACAO_RUIDO);
        mudaGanho (&(dados_ps_r[POSICAO_INICIAL]), n_amostras_in, ATENUACAO_PASTE);
        misturaDados (&(dados_in_r [0]), &(dados_ps_r[POSICAO_INICIAL]), &(dados_ps_r [POSICAO_INICIAL]), n_amostras_in);
    }

    /* Escreve em outro arquivo. */
    if (!writeWavFile (OUTPUT_FILE, &header_ps, dados_ps_r, dados_ps_l))
    {
        printf ("Erro salvando %s.\n", OUTPUT_FILE);
        return (1);
    }

    /* Desaloca os vetores. O direito s� vai ter sido alocado se o arquivo for est�reo. */
	free (dados_in_l);
	free (dados_ps_l);
	if (dados_in_r)
        free (dados_in_r);
    if (dados_ps_r)
        free (dados_ps_r);
	return (0);
}

/*----------------------------------------------------------------------------*/
/** Mistura duas trilhas. Simplesmente soma os dados posi��o-a-posi��o. Os dois
 * vetores de entrada devem ter o mesmo tamanho.
 *
 * Par�metros: double* dados1: vetor de dados 1.
 *             double* dados2: vetor de dados 2.
 *             double* saida: vetor de sa�da.
 *             int n_amostras: n�mero de amostras nos vetores.
 *
 * Valor de Retorno: nenhum. */

void misturaDados (double* dados1, double* dados2, double* saida, int n_amostras)
{
	while (n_amostras--)
	{
        if(MUTA_PASTE)
            *saida = *dados1;
        else
            *saida = *dados1 + *dados2;
		saida++;
		dados1++;
		dados2++;
	}
}

/*============================================================================*/
