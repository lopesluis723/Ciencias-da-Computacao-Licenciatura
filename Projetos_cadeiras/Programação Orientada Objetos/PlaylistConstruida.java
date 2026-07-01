
/**
 * Escreva uma descrição da classe PlaylistConstruida aqui.
 * 
 * @author (seu nome) 
 * @version (um número da versão ou uma data)
 */

import java.io.Serializable;
import java.util.*;
import java.util.List;

public class PlaylistConstruida extends Playlist {
    private int posicaoAtual;  // controle da posição na playlist
    
    public PlaylistConstruida(String nome, boolean publica) {
        super(nome, publica);
        this.posicaoAtual = 0;
    }
    
    @Override
    public void reproduzirPlaylist() {
        // Exemplo: reproduzir a partir da posição atual sem embaralhar
        if(posicaoAtual < musicas.size()){
            musicas.get(posicaoAtual).reproduzir();
            posicaoAtual++;
        }
    }
    
    // Métodos para avançar ou retroceder
    public void avancar() {
        if(posicaoAtual < musicas.size()-1) posicaoAtual++;
    }
    
    public void retroceder() {
        if(posicaoAtual > 0) posicaoAtual--;
    }
}
