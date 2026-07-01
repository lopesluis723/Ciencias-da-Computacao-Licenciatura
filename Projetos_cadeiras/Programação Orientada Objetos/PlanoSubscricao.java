
/**
 * Escreva uma descrição da classe PlanoSubscricao aqui.
 * 
 * @author (seu nome) 
 * @version (um número da versão ou uma data)
 */

import java.io.Serializable;
import java.util.*;
import java.util.List;

public interface PlanoSubscricao extends Serializable {
    // Método para calcular pontos a serem atribuídos por reprodução
    int calcularPontosReproducao(int pontosAtuais);
    String getNomePlano();
}
