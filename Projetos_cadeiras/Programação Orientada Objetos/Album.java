
/**
 * Escreva uma descrição da classe Album aqui.
 * 
 * @author (seu nome) 
 * @version (um número da versão ou uma data)
 */
import java.io.Serializable;
import java.util.*;
import java.util.List;

public class Album implements Serializable {
    private String nome;
    private String artista;
    private List<Musica> musicas;

    public Album(String nome, String artista) {
        this.nome = nome;
        this.artista = artista;
        this.musicas = new ArrayList<>();
    }
    
    public void adicionarMusica(Musica musica) {
        this.musicas.add(musica);
    }

    // Fazer mais metodos como por exemplo um de busca 
}
