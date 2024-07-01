/*============================================================================*/
/* Exemplo: gera uma vers�o do sinal com a metade do tamanho original. */

#include <stdlib.h>
#include "wavfile.h"

#include "trabalho2.h"

/*============================================================================*/

#define INPUT_FILE "data/sonic1.wav"
#define OUTPUT_FILE "data/teste3_dobra.wav"

/*============================================================================*/

int main ()
{
	WavHeader header_in; /* Cabe�alho para as informa��es sobre o arquivo. */
	double* dados_l_in; /* Dados do canal esquerdo. Alocado na readWavFile. */
	double* dados_r_in; /* Dados do canal direito. Alocado na readWavFile, se necess�rio. */
	int n_amostras_in; /* N�mero de amostras nos buffers. */

	WavHeader header_out; /* Cabe�alho para as informa��es sobre o arquivo. */
	double* dados_l_out; /* Dados do canal esquerdo. Alocado na generateSignal. */
	double* dados_r_out; /* Dados do canal direito. Alocado na generateSignal, se necess�rio. */
	int n_amostras_out; /* N�mero de amostras nos buffers. */

    /* L� um arquivo. */
    n_amostras_in = readWavFile (INPUT_FILE, &header_in, &dados_l_in, &dados_r_in);
    if (!n_amostras_in)
    {
        printf ("Erro lendo %s.\n", INPUT_FILE);
        return (1);
    }

    if (n_amostras_in % 2) /* Precisamos de um tamanho par. */
        n_amostras_in--;

    /* Gera um sinal com o dobro do tamanho. */
    n_amostras_out = n_amostras_in/2;
    header_out = generateSignal (&n_amostras_out, header_in.num_channels, header_in.sample_rate, &dados_l_out, &dados_r_out);
    if (n_amostras_out != n_amostras_in/2)
    {
        printf ("Erro gerando o sinal de saida.\n");
        return (1);
    }

    /* Preenche o sinal de saida. */
    dobraVelocidade (dados_l_in, n_amostras_in, dados_l_out);
    if (dados_r_in)
        dobraVelocidade (dados_r_in, n_amostras_in, dados_r_out);

    /* Escreve em outro arquivo. */
    if (!writeWavFile (OUTPUT_FILE, &header_out, dados_l_out, dados_r_out))
    {
        printf ("Erro salvando %s.\n", OUTPUT_FILE);
        return (1);
    }

    /* Desaloca os vetores. O direito s� vai ter sido alocado se o arquivo for est�reo. */
	free (dados_l_in);
	if (dados_r_in)
        free (dados_r_in);
    free (dados_l_out);
	if (dados_r_out)
        free (dados_r_out);

	return (0);
}

/*============================================================================*/
