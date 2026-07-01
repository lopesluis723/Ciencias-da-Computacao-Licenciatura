/**
 * Escreva uma descrição da classe Musica_Explicita aqui.
 * 
 * @author (seu nome) 
 * @version (um número da versão ou uma data)
 */
import java.io.Serializable;
import java.util.*;
import java.util.List;

public class MusicaExplicita extends Musica {
    private boolean avisoExplícito;

    public MusicaExplicita(String nome, String interprete, String editora, String letra,
                            List<String> linhasMusicais, String genero, int duracaoSegundos, Album album) {
        super(nome, interprete, editora, letra, linhasMusicais, genero, duracaoSegundos, album);
        this.avisoExplícito = true;
    }

    @Override
    public void reproduzir() {
        System.out.println("Atenção: Esta música é explícita!");
        super.reproduzir();
    }
}
