
/**
 * Escreva uma descrição da classe Playlist aqui.
 * 
 * @author (seu nome) 
 * @version (um número da versão ou uma data)
 */

import java.io.Serializable;
import java.util.*;
import java.util.List;

public abstract class Playlist implements Serializable {
    protected String nome;
    protected List<Musica> musicas;
    protected boolean publica;  // indica se a playlist é pública ou não
    
    public Playlist(String nome, boolean publica) {
        this.nome = nome;
        this.publica = publica;
        this.musicas = new ArrayList<>();
    }
    
    public void adicionarMusica(Musica musica) {
        this.musicas.add(musica);
    }
    
    // Método abstrato para reproduzir a playlist – comportamento pode variar
    public abstract void reproduzirPlaylist();
    
    // Getters e setters FAZER !!!!!!!!!
}