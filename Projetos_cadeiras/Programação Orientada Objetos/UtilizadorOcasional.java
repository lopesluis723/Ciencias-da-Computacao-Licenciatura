
/**
 * Escreva uma descrição da classe UtilizadorOcasional aqui.
 * 
 * @author (seu nome) 
 * @version (um número da versão ou uma data)
 */

import java.io.Serializable;
import java.util.*;
import java.util.List;

public class UtilizadorOcasional extends Utilizador {
    public UtilizadorOcasional(String nome, String email, String morada) {
        super(nome, email, morada);
    }
    
    @Override
    public void reproduzirMusica(Musica musica) {
        musica.reproduzir();
        // Ex: adicionar 5 pontos por reprodução
        pontos += 5;
    }
}
